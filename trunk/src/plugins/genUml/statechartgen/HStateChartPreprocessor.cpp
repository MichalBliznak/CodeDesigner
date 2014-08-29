#include "HStateChartPreprocessor.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udHStateChartPreprocessor, udPreprocessor);

udHStateChartPreprocessor::udHStateChartPreprocessor()
{
	// set default optimization tasks
}

udHStateChartPreprocessor::udHStateChartPreprocessor(udGenerator *gen)
: udPreprocessor(gen)
{
}

udHStateChartPreprocessor::~udHStateChartPreprocessor()
{
}

udDiagramItem* udHStateChartPreprocessor::Process(udDiagramItem *src)
{
	// create local copy of the optimized diagram
	m_pPreprocessedDiagram = (udDiagramItem*)src->Clone();

	// process diagram (the order of following steps is crucial!)
	AssignStateActions( m_pPreprocessedDiagram );
	
	ReconnectOutputs( m_pPreprocessedDiagram );
	ReconnectInputs( m_pPreprocessedDiagram );
	
	SortStateActions( m_pPreprocessedDiagram );

    return m_pPreprocessedDiagram;
}

void udHStateChartPreprocessor::ReconnectInputs(udDiagramItem* diag)
{
	// get all hierarchical state elements
	wxSFLineShape *pInitTrans;
	wxSFShapeBase *pState, *pInitialState;
	
	ShapeList lstStates, lstInitTrans;
	//diag->GetDiagramManager().GetShapes( CLASSINFO( umlCompStateItem ), lstStates );
	diag->GetDiagramManager().GetShapes( CLASSINFO( umlSimpleStateItem ), lstStates );
	
	// find all transition starting in initial state located in the hierarchical states and reconnect them
	// to those ones.
	ShapeList::compatibility_iterator node = lstStates.GetFirst();
	while( node )
	{
		pState = node->GetData();
		
		// get initial state in this hierarchical state
		pInitialState = (wxSFShapeBase*)pState->GetFirstChild( CLASSINFO( umlInitialItem ) );
		if( pInitialState )
		{
			lstInitTrans.Clear();
			
			// get transition connected to the initial state
			diag->GetDiagramManager().GetAssignedConnections( pInitialState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstInitTrans );
				
			// reconnect them to the parent hierarchical state
			ShapeList::compatibility_iterator inode = lstInitTrans.GetFirst();
			while( inode )
			{
				pInitTrans = (wxSFLineShape*)inode->GetData();
					
				pInitTrans->SetSrcShapeId( pState->GetId() );
					
				inode = inode->GetNext();
			}
		}
		node = node->GetNext();
	}
	
}

void udHStateChartPreprocessor::ReconnectOutputs(udDiagramItem* diag)
{
	bool fReconnected;
	wxSFShapeBase *pState, *pChild, *pCompState;
	wxSFLineShape *pTrans, *pNewTrans;
	ShapeList lstStates, lstOutTrans, lstChildren, lstFinals;
	ShapeList::compatibility_iterator cnode;
	SerializableList::compatibility_iterator anode;
	udTransElementItem *pElement, *pNewElement;
	udStateActionLinkItem *pActionLink, *pNewActionLink;
	size_t nIndex;
	
	// get all hierarchical states in given diagram (use BFS algorithm so we will obtain
	// all states in one level grouped together).
	diag->GetDiagramManager().GetShapes( CLASSINFO( umlCompStateItem ), lstStates, xsSerializable::searchBFS );
	//diag->GetDiagramManager().GetShapes( CLASSINFO( umlSimpleStateItem ), lstStates, xsSerializable::searchBFS );
	
	// create copies of transition staring in the hierarchical state and connect them to all 
	// (next level) child states. we must process states from the top level to the bottom level.
	ShapeList::compatibility_iterator node = lstStates.GetLast();
	while( node )
	{
		pState = node->GetData();
		
		// get transition starting in this h. state
		lstOutTrans.Clear();
		diag->GetDiagramManager().GetAssignedConnections( pState, CLASSINFO( umlTransitionItem ), wxSFShapeBase::lineSTARTING, lstOutTrans );
		
		// get all first level children
		lstChildren.Clear();
		lstFinals.Clear();
		
		//pState->GetChildShapes( CLASSINFO( umlCompStateItem ), lstChildren, sfNORECURSIVE );
		pState->GetChildShapes( CLASSINFO( umlSimpleStateItem ), lstChildren, sfNORECURSIVE );
		pState->GetChildShapes( CLASSINFO( umlSubStateItem ), lstChildren, sfNORECURSIVE );
		pState->GetChildShapes( CLASSINFO( umlFinalItem ), lstFinals, sfNORECURSIVE );
		
		ShapeList::compatibility_iterator tnode = lstOutTrans.GetFirst();
		while( tnode )
		{
			fReconnected = false;
			
			// get original outcomming transition
			pTrans = (wxSFLineShape*)tnode->GetData();
			pElement = (udTransElementItem*)pTrans->GetUserData();
			
			// condition-less transitions connect to final states only and
			// the others connect to state items
			if( pElement->HasCondition() ) cnode = lstChildren.GetFirst();
			else
				cnode = lstFinals.GetFirst();
				
			while( cnode )
			{
				pChild = cnode->GetData();
				
				if( diag->GetDiagramManager().FindShape( pTrans->GetTrgShapeId() )->GetParentShape() != pState )
				{
					// create new copy of outcomming transition and connect it to a child shape
					pNewTrans = (wxSFLineShape*)pTrans->Clone();
					pNewTrans->SetId( diag->GetDiagramManager().GetNewId() );
					
					pNewTrans->SetSrcShapeId( pChild->GetId() );
					
					// assign output actions to source composite state if exist
					pCompState = wxDynamicCast( pChild, umlCompStateItem );
					if( pCompState )
					{
						nIndex = 0;
						anode = pCompState->GetUserData()->GetFirstChildNode();
						while( anode )
						{
							pActionLink = (udStateActionLinkItem*) anode->GetData();
			
							if( pActionLink->GetActionType() == udStateActionLinkItem::saEXIT )
							{
								pNewElement = (udTransElementItem*) pNewTrans->GetUserData();
								
								pNewActionLink = (udStateActionLinkItem*) pActionLink->Clone();
								pNewElement->InsertChild( nIndex++, (xsSerializable*) pNewActionLink );
							}
							
							anode = anode->GetNext();
						}
					}
					
					// add new transition to a diagram manager
					diag->GetDiagramManager().AddItem( (xsSerializable*)NULL, pNewTrans );
					
					fReconnected = true;
				}
				
				cnode = cnode->GetNext();
			}
			
			tnode = tnode->GetNext();
			
			// remove original transition in new copies have been created
			if(fReconnected) diag->GetDiagramManager().RemoveShape( pTrans, false );
		}
		
		node = node->GetPrevious();
	}
	
}

void udHStateChartPreprocessor::AssignStateActions(udDiagramItem* diag)
{
	// check all states in the diagram wherher they include entry/exit actions and assign those actions to
	// incomming/outcomming state's transitions.
	
	wxSFShapeBase *pState, *pTrgShape;
	wxSFLineShape *pTransShape;
	udTransElementItem *pTransElement;
	udStateActionLinkItem *pActionLink;

	ShapeList lstCompStates, lstInTrans, lstOutTrans;
	
	diag->GetDiagramManager().GetShapes( CLASSINFO( umlCompStateItem ), lstCompStates, xsSerializable::searchBFS );
	
	SerializableList::compatibility_iterator anode;
	ShapeList::compatibility_iterator tnode, node = lstCompStates.GetFirst();
	while( node )
	{
		pState = (wxSFShapeBase*) node->GetData();
		
		lstInTrans.Clear();
		lstOutTrans.Clear();
		
		diag->GetDiagramManager().GetAssignedConnections( pState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstOutTrans );
		diag->GetDiagramManager().GetAssignedConnections( pState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineENDING, lstInTrans );
		
		anode = pState->GetUserData()->GetFirstChildNode();
		while( anode )
		{
			pActionLink = (udStateActionLinkItem*) anode->GetData();
			
			if( pActionLink->GetActionType() == udStateActionLinkItem::saENTRY )
			{
				tnode = lstInTrans.GetFirst();
				while( tnode )
				{
					pTransElement = (udTransElementItem*) tnode->GetData()->GetUserData();
					pTransShape = (wxSFLineShape*) tnode->GetData();
					
					// insert new copy of state action to this transition element
					if( pTransShape->GetSrcShapeId() != pTransShape->GetTrgShapeId() ) pTransElement->AddChild( (xsSerializable*) pActionLink->Clone() );
					
					tnode = tnode->GetNext();
				}
			}
			else if( pActionLink->GetActionType() == udStateActionLinkItem::saEXIT )
			{
				tnode = lstOutTrans.GetFirst();
				while( tnode )
				{
					pTransElement = (udTransElementItem*) tnode->GetData()->GetUserData();
					pTransShape = (wxSFLineShape*) tnode->GetData();
					pTrgShape = diag->GetDiagramManager().FindShape( ((umlTransitionItem*) tnode->GetData())->GetTrgShapeId() );
					
					// insert exit action to the top of the children list
					if( !pTrgShape->IsDescendant( pState ) && ( pTransShape->GetSrcShapeId() != pTransShape->GetTrgShapeId() ) ) pTransElement->AddChild( (xsSerializable*) pActionLink->Clone() );
					
					tnode = tnode->GetNext();
				}
			}
			
			anode = anode->GetNext();
		}
		
		node = node->GetNext();
	}
}

void udHStateChartPreprocessor::SortStateActions(udDiagramItem* diag)
{
	// state actions assigned to transitions must by sorted in such way that EXIT actions must be at the top of the list
	// followed by ENTRY actions.
	
	udTransElementItem *pTransElement;
	udStateActionLinkItem *pActionLink;
	SerializableList::compatibility_iterator anode;
	size_t nIndex;
	
	ShapeList lstTrans;
	diag->GetDiagramManager().GetShapes( CLASSINFO( umlTransitionItem ), lstTrans );
	
	ShapeList::compatibility_iterator tnode = lstTrans.GetFirst();
	while( tnode )
	{
		pTransElement = (udTransElementItem*) tnode->GetData()->GetUserData();
	
		nIndex = 0;
		anode = pTransElement->GetFirstChildNode();
		while( anode )
		{
			pActionLink = wxDynamicCast( anode->GetData(), udStateActionLinkItem );
			if( pActionLink && (pActionLink->GetActionType() == udStateActionLinkItem::saEXIT) )
			{
				anode = anode->GetNext();
				
				pTransElement->GetChildrenList().DeleteObject( pActionLink );
				pTransElement->GetChildrenList().Insert( nIndex++, pActionLink );
			}
			else
				anode = anode->GetNext();
		}
		
		tnode = tnode->GetNext();
	}
}
