#include "StateChartVerifier.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udStateChartVerifier, udVerifier);

udStateChartVerifier::udStateChartVerifier()
{
}

udStateChartVerifier::udStateChartVerifier(udGenerator *gen) :
udVerifier(gen)
{
}

udStateChartVerifier::~udStateChartVerifier()
{
}

bool udStateChartVerifier::Verify(udDiagramItem *diagram)
{
	if( !diagram ) return false;

	if( !CheckInitialStates(diagram) ) return false;
	else if( !CheckHistoryStates(diagram) ) return false;
	else if( !CheckEndingStates(diagram) ) return false;
	else if( !CheckUnconnectedStates(diagram) ) return false;
	else if( !CheckConnections(diagram) ) return false;
	else if( !CheckGOTOConstraints(diagram) ) return false;
	else if( !CheckLanguageConstraints(diagram) ) return false;

    return true;
}

bool udStateChartVerifier::CheckInitialStates(udDiagramItem *diagram)
{
	// check initial states

	bool fSuccess = true;

	wxSFShapeBase *pShape;
	udProjectItem *pElement;

	ShapeList lstInitialStates;
	ShapeList lstParents;

	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlEntryItem), lstInitialStates);
	//diagram->GetDiagramManager().GetShapes(CLASSINFO(umlHistoryItem), lstInitialStates);

	ShapeList::compatibility_iterator node = lstInitialStates.GetFirst();
	if( !node )
	{
		IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: there is no initial state in diagram '%s'."), diagram->GetName().c_str()));
		fSuccess = false;
	}
	while(node)
	{
		pShape = node->GetData();
		if( lstParents.IndexOf(pShape->GetParentShape()) != wxNOT_FOUND )
		{
			pElement = (udProjectItem*) udPROJECT::GetDiagramElement( pShape );
			IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: more than one initial state in a parent object (state: '%s')"), pElement->GetName().c_str()));

			fSuccess = false;
		}
		else
			lstParents.Append(pShape->GetParentShape());

		node = node->GetNext();
	}

	return fSuccess;
}

bool udStateChartVerifier::CheckEndingStates(udDiagramItem *diagram)
{
	// check ending states
	ShapeList lstEndingStates;
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlFinalItem), lstEndingStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlExitItem), lstEndingStates);

	if( lstEndingStates.GetCount() < 1 )
	{
		IPluginManager::Get()->Log(wxString::Format(wxT("WARNING: there should be at least one ending state in diagram '%s'."), diagram->GetName().c_str()));
	}

	return true;
}

bool udStateChartVerifier::CheckUnconnectedStates(udDiagramItem *diagram)
{
	bool fSuccess = true;

	udDiagElementItem *pElement;

	ShapeList lstStates;
	ShapeList lstOuttrans;

	// get all possible non-initial (pseudo)states ...
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlSimpleStateItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlCompStateItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlSubStateItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlFinalItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlExitItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlDecisionItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlForkJoinHItem), lstStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlForkJoinVItem), lstStates);

	// ... and check whether there are some transitions leading to these states
	ShapeList::compatibility_iterator node = lstStates.GetFirst();
	while(node)
	{
		lstOuttrans.Clear();
		diagram->GetDiagramManager().GetAssignedConnections(node->GetData(), CLASSINFO(umlTransitionItem), wxSFShapeBase::lineENDING, lstOuttrans);
		if( lstOuttrans.IsEmpty() )
		{
			fSuccess = false;
			pElement = (udDiagElementItem*) udPROJECT::GetDiagramElement( node->GetData() );
			IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: there is unconnected state '%s' in diagram '%s'."), pElement->GetName().c_str(), diagram->GetName().c_str()));
		}

		node = node->GetNext();
	}

	return fSuccess;
}

bool udStateChartVerifier::CheckConnections(udDiagramItem *diagram)
{
	// check ending states
	bool fSuccess = true;
	ShapeList lstInitialStates;

	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);
	diagram->GetDiagramManager().GetShapes(CLASSINFO(umlEntryItem), lstInitialStates);
	//diagram->GetDiagramManager().GetShapes(CLASSINFO(umlHistoryItem), lstInitialStates);

	m_lstProcessedStates.Clear();

	// check all diagram branches starting in initial states
	ShapeList::compatibility_iterator node = lstInitialStates.GetFirst();
	while(node)
	{
		fSuccess &= _CheckOutcommingPaths(diagram->GetDiagramManagerPointer(), node->GetData());
		node = node->GetNext();
	}

	return fSuccess;
}

bool udStateChartVerifier::_CheckOutcommingPaths(wxSFDiagramManager *manager, wxSFShapeBase *parent)
{
	if( !manager || !parent )return true;

	// test whether the state is not processed yet
	if( m_lstProcessedStates.IndexOf( parent ) != wxNOT_FOUND ) return true;
	m_lstProcessedStates.Append( parent );

	// get all assigned transitions
	ShapeList lstTransitions;
	manager->GetAssignedConnections(parent, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

	bool fSuccess = true;
	int nConditionLess = 0;

	wxString sCondition;
	wxArrayString arrConditions;
	wxArrayInt arrPriorities;

	wxSFLineShape *pLine;
	udTransElementItem *pElement;
	udDiagElementItem *pStateElement = (udDiagElementItem*) udPROJECT::GetDiagramElement( parent );

	ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
	while(node)
	{
		pLine = (wxSFLineShape*)node->GetData();
		pElement = (udTransElementItem*) udPROJECT::GetDiagramElement( pLine );

		sCondition = pElement->GetConditionString();

		// test transition's guard
		if( sCondition == wxEmptyString )
		{
			nConditionLess++;
		}
		else
		{
			// check duplicated conditions
			if( arrConditions.Index(sCondition) == wxNOT_FOUND )
			{
				arrConditions.Add(sCondition);
			}
			else
			{
				IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: there are tansitions with duplicated guard condition in state '%s'."), pStateElement->GetName().c_str()));
				fSuccess = false;
			}
			
			// check duplicated priorities
			if( arrPriorities.Index( pElement->GetPriority() ) == wxNOT_FOUND )
			{
				if( pElement->GetPriority() != uddvPRIORITY_MIN ) arrPriorities.Add( pElement->GetPriority() );
			}
			else
			{
				IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: there are tansitions with duplicated priority level in state '%s'."), pStateElement->GetName().c_str()));
				fSuccess = false;
			}
		}

		// perform the test recursively
		if( pLine->GetTrgShapeId() != -1 )
		{
			fSuccess &= _CheckOutcommingPaths( manager, manager->FindShape(pLine->GetTrgShapeId()) );
		}

		node = node->GetNext();
	}

	// check number of conditionless transitions
	if( nConditionLess > 1 )
	{
		IPluginManager::Get()->Log(wxString::Format(wxT("ERROR: there are more than one conditionless transitions in state '%s'."), pStateElement->GetName().c_str()));
		fSuccess = false;
	}

	return fSuccess;
}

bool udStateChartVerifier::CheckHistoryStates(udDiagramItem *diagram)
{
	// check history states in the following way:
	// 1) history state must have a parent
	// 2) there can be only one incoming transition in the history state which must be conditionless
	//   and must start in its parent or initial state
	// 3) there can be only one outcoming transition in the history state which must be conditionless
	
	bool fSuccess = true;
	
	wxSFShapeBase *pHistory;
	
	ShapeList lstHistoryStates, lstStates, lstTrans;
	diagram->GetDiagramManager().GetShapes( CLASSINFO( umlHistoryItem ), lstHistoryStates );
	
	ShapeList::compatibility_iterator node = lstHistoryStates.GetFirst();
	while( node )
	{
		pHistory = node->GetData();
		
		// check parent shape
		if( !pHistory->GetParentShape() )
		{
			IPluginManager::Get()->Log( wxString::Format( wxT("ERROR: history state '%s' has no parent."), udLABEL::GetContent( pHistory, udLABEL::ltTITLE ).c_str() ) );
			fSuccess = false;
		}
		
		// check incoming states
		bool fPartSuccess = true;
		lstStates.Clear();
		
		diagram->GetDiagramManager().GetNeighbours( pHistory, lstStates, CLASSINFO( umlTransitionItem ), wxSFShapeBase::lineENDING, sfDIRECT );
		if( lstStates.GetCount() == 1 ) 
		{
			wxSFShapeBase *pSrcShape = lstStates.GetFirst()->GetData();
			if( pSrcShape != pHistory->GetParentShape() ) fPartSuccess = false;
			
			// also test whether this transition has no condition
			if( fPartSuccess )
			{
				lstTrans.Clear();
				
				diagram->GetDiagramManager().GetAssignedConnections( pHistory, CLASSINFO( umlTransitionItem ), wxSFShapeBase::lineENDING, lstTrans );
				udTransElementItem *pTransElement = (udTransElementItem*) udPROJECT::GetDiagramElement( lstTrans.GetFirst()->GetData() );
				
				if( pTransElement->HasCondition() ) fPartSuccess = false;
			}
		}
		else
			fPartSuccess = false;
			
		if( !fPartSuccess )
		{
			IPluginManager::Get()->Log( wxString::Format( wxT("ERROR: there must by exactly one conditionless incoming transition in history state '%s' which starts either in an initial state or in parent composite state."), udLABEL::GetContent( pHistory, udLABEL::ltTITLE ).c_str() ) );
			fSuccess = false;
		}
			
		// check incoming states
		lstTrans.Clear();
					
		diagram->GetDiagramManager().GetAssignedConnections( pHistory, CLASSINFO( umlTransitionItem ), wxSFShapeBase::lineSTARTING, lstTrans );
		udTransElementItem *pTransElement = (udTransElementItem*) udPROJECT::GetDiagramElement( lstTrans.GetFirst()->GetData() );
					
		if( (lstTrans.GetCount() != 1) || pTransElement->HasCondition() )
		{
			IPluginManager::Get()->Log( wxString::Format( wxT("ERROR: there must by exactly one conditionless outcoming transition in history state '%s'."), udLABEL::GetContent( pHistory, udLABEL::ltTITLE ).c_str() ) );
			fSuccess = false;				
		}

		node = node->GetNext();
	}
	
	return fSuccess;
}

bool udStateChartVerifier::CheckGOTOConstraints(udDiagramItem* diagram)
{
	// Check whether a state machine with defined input action has activated code generation algorithm supporting the 
	// input actions and non-blocking state charts.
	udSStateChartDiagramItem *pSSCh = wxDynamicCast( diagram, udSStateChartDiagramItem);
	if( pSSCh && (pSSCh->GetActiveAlgorithm() == wxT("udGOTOAlgorithm")) )
	{
		if( pSSCh->GetInputAction() != wxT("<none>") )
		{
			IPluginManager::Get()->Log( wxString::Format( wxT("ERROR: 'GOTO' code generation algorithm set in diagram '%s' doesn't support input actions."), diagram->GetName().c_str() ) );
			return false;
		}
		if( pSSCh->IsNonBlocking() )
		{
			IPluginManager::Get()->Log( wxString::Format( wxT("ERROR: 'GOTO' code generation algorithm set in diagram '%s' doesn't support non-blocking state charts."), diagram->GetName().c_str() ) );
			return false;
		}
	}
	return true;
}

bool udStateChartVerifier::CheckLanguageConstraints(udDiagramItem* diagram)
{
	// Check whether selected output language allows required features.
	udSStateChartDiagramItem *pSSCh = wxDynamicCast( diagram, udSStateChartDiagramItem);
	if( pSSCh && ( IPluginManager::Get()->GetSelectedLanguage()->GetName() == wxT("Python Language") ) )
	{
		if( pSSCh->IsNonBlocking() )
		{
			IPluginManager::Get()->Log( wxT("ERROR: Python language doesn't support non-blocking state charts.") );
			return false;
		}
	}
	return true;
}
