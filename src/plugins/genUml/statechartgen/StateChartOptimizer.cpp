#include "StateChartOptimizer.h"
#include "../../diagUml/DiagUml.h"
#include "projectbase/ProjectBase.h"

#include <wx/listimpl.cpp>

IMPLEMENT_DYNAMIC_CLASS(udStateChartOptimizer, udOptimizer);

WX_DEFINE_LIST(BranchList);

udStateChartOptimizer::udStateChartOptimizer()
{
	// set default optimization tasks
	m_nFlags = optMERGE_TRANSITIONS | optMERGE_DIRECT_BRANCHES | optINVERT_CONDITIONS;
	m_pOptimizedDiagram = NULL;
}

udStateChartOptimizer::udStateChartOptimizer(udGenerator *gen)
: udOptimizer(gen)
{
	// set default optimization tasks
	m_nFlags = optMERGE_TRANSITIONS | optMERGE_DIRECT_BRANCHES | optINVERT_CONDITIONS;
	m_pOptimizedDiagram = NULL;
}

udStateChartOptimizer::~udStateChartOptimizer()
{
}

udDiagramItem* udStateChartOptimizer::Optimize(udDiagramItem *src)
{
	bool fTryMore;
	int nMaxOptCycles = 10;
	
	udSettings &Settings = IPluginManager::Get()->GetProjectSettings();

	// create local copy of the optimized diagram
	//m_pOptimizedDiagram = new udDiagramItem(*src);
	m_pOptimizedDiagram = (udDiagramItem*)src->Clone();

	// process optimization cycles
	do
	{
		fTryMore = false;

		IPluginManager::Get()->Log(wxString::Format(wxT(">>> Iteration %d ..."), 11 - nMaxOptCycles));
		// perform required optimization steps
		if( Settings.GetProperty( wxT("Merge direct branches") )->AsBool() && (m_nFlags & optMERGE_DIRECT_BRANCHES) )
		{
			fTryMore |= MergeDirectBranches( m_pOptimizedDiagram );
		}
		if( Settings.GetProperty( wxT("Merge parallel transitions") )->AsBool() && (m_nFlags & optMERGE_TRANSITIONS) )
		{
			fTryMore |= MergeTransitions( m_pOptimizedDiagram );
		}
		if( Settings.GetProperty( wxT("Invert conditions") )->AsBool() && (m_nFlags & optINVERT_CONDITIONS) )
		{
			fTryMore |= InvertConditions( m_pOptimizedDiagram );
		}

		nMaxOptCycles--;
	}
	while( fTryMore && (nMaxOptCycles > 1) );

    return m_pOptimizedDiagram;
}

bool udStateChartOptimizer::InvertConditions(udDiagramItem *src)
{
	bool fInverted = false;
	long nTmpId;

	ShapeList lstStates, lstTrans;
	umlTransitionItem *pFirstTrans, *pSecondTrans;
	udTransElementItem *pFirstTranElement, *pSecondTranElement;

	// get all (pseudo) states in the source diagram
	PaletteArray *pDiagramElements = m_mapElementPalettes[src->GetDiagramType()];
	if( !pDiagramElements ) return false;

	for( size_t i = 0; i < pDiagramElements->GetCount(); i++ )
	{
		if( pDiagramElements->Item(i).m_nType == udPaletteItem::pitELEMENT )
		{
			src->GetDiagramManager().GetShapes(wxClassInfo::FindClass(pDiagramElements->Item(i).m_sClassName), lstStates);
		}
	}

	ShapeList::compatibility_iterator snode = lstStates.GetFirst();
	while( snode )
	{
		lstTrans.Clear();
		src->GetDiagramManager().GetAssignedConnections(snode->GetData(), CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTrans);

		// optimize only states with two outcomming transitions
		if( lstTrans.GetCount() == 2 )
		{
			pFirstTrans = (umlTransitionItem*)lstTrans.Item(0)->GetData();
			pFirstTranElement = (udTransElementItem*)pFirstTrans->GetUserData();

			pSecondTrans = (umlTransitionItem*)lstTrans.Item(1)->GetData();
			pSecondTranElement = (udTransElementItem*)pSecondTrans->GetUserData();

			if( !pSecondTranElement->HasCondition() )
			{
				if( pSecondTranElement->HasActions() &&
					pFirstTranElement->HasCondition() &&
					!pFirstTranElement->HasActions() )
				{
					// create new condition
					udCodeItem *pCond = (udCodeItem*)pFirstTranElement->GetCondition( udfORIGINAL )->Clone();
					pCond->SetInverted( true );
					// clear previous condition and assign the new one
					pFirstTranElement->ClearCodeItems( CLASSINFO(udConditionItem) );
					pFirstTranElement->ClearCodeItems( CLASSINFO(udEventItem) );
					pFirstTranElement->AssignCodeItem( pCond );
					// copy actions form second transition to the first
					pFirstTranElement->CopyActionItems( pSecondTranElement );
					// clear actions in the second transition
					pSecondTranElement->ClearCodeItems( CLASSINFO(udActionItem) );

					// swap targets
					nTmpId = pFirstTrans->GetTrgShapeId();
					pFirstTrans->SetTrgShapeId(pSecondTrans->GetTrgShapeId());
					pSecondTrans->SetTrgShapeId(nTmpId);

					fInverted = true;
				}
			}
			else if( !pFirstTranElement->HasCondition() )
			{
				if( pFirstTranElement->HasActions() &&
					pSecondTranElement->HasCondition() &&
					!pSecondTranElement->HasActions() )
				{
					// create new condition
					udCodeItem *pCond = (udCodeItem*)pSecondTranElement->GetCondition( udfORIGINAL )->Clone();
					pCond->SetInverted( true );
					// clear previous condition and assign the new one
					pSecondTranElement->ClearCodeItems( CLASSINFO(udConditionItem) );
					pSecondTranElement->ClearCodeItems( CLASSINFO(udEventItem) );
					pSecondTranElement->AssignCodeItem( pCond );
					// copy actions form second transition to the first
					pSecondTranElement->CopyActionItems( pFirstTranElement );
					// clear actions in the second transition
					pFirstTranElement->ClearCodeItems( CLASSINFO(udActionItem) );				

					// swap targets
					nTmpId = pSecondTrans->GetTrgShapeId();
					pSecondTrans->SetTrgShapeId(pFirstTrans->GetTrgShapeId());
					pFirstTrans->SetTrgShapeId(nTmpId);

					fInverted = true;
				}
			}
		}

		snode = snode->GetNext();
	}

	return fInverted;
}

bool udStateChartOptimizer::MergeTransitions(udDiagramItem *src)
{
	bool fFirstRun, fConditionLess, fMerged = false;
	int nIndex;
	wxString sNewCondition;//, sCondString;

	//udCodeItem *pCondition;
	udConditionItem *pNewCond;
	wxSFShapeBase *pState;
	wxSFLineShape *pTrans;
	udTransElementItem *pLineElement;
	ShapeList lstStates, lstTransitions, lstSubTrans, lstSubActs;
	
	udLanguage *pLang = m_pGenerator->GetActiveLanguage();

	// get all (pseudo) states in the source diagram
	PaletteArray *pDiagramElements = m_mapElementPalettes[src->GetDiagramType()];
	if( !pDiagramElements ) return false;

	for( size_t i = 0; i < pDiagramElements->GetCount(); i++ )
	{
		if( pDiagramElements->Item(i).m_nType == udPaletteItem::pitELEMENT )
		{
			src->GetDiagramManager().GetShapes(wxClassInfo::FindClass(pDiagramElements->Item(i).m_sClassName), lstStates);
		}
	}

	ShapeList::compatibility_iterator snode = lstStates.GetFirst();
	while(snode)
	{
		pState = snode->GetData();
		// get all transitions starting in this state
		src->GetDiagramManager().GetAssignedConnections(pState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

		while( lstTransitions.GetFirst() )
		{
			// get subsets with identical targets
			FindTransWithIdenticalTarget(lstTransitions, lstSubTrans);
			if( lstSubTrans.GetCount() > 1 )
			{
				nIndex = 1;
				while( lstSubTrans.GetFirst() )
				{
					// get subsets with actions
					FindTransWithIdenticalActions(lstSubTrans, lstSubActs);
					if( lstSubActs.GetCount() > 1 )
					{
						// create combined action
						fFirstRun = true;
						fConditionLess = false;
						sNewCondition = wxT("");

						ShapeList::compatibility_iterator anode = lstSubActs.GetFirst();
						while( anode )
						{
							pTrans = (wxSFLineShape*)anode->GetData();
							pLineElement = (udTransElementItem*)pTrans->GetUserData();
							
							//pCondition = ((udTransElementItem*)pTrans->GetUserData())->GetCondition();
							//sCondString = ((udTransElementItem*)pTrans->GetUserData())->GetConditionString( pLang );
							if( !pLineElement->HasCondition() )
							{
								sNewCondition = wxT("");
								fConditionLess = true;
							}

							if( fFirstRun )
							{
								if( !fConditionLess )sNewCondition << wxT("( ") << pLineElement->GetConditionAsString( udCodeItem::cfCALL, pLang ); //pCondition->ToString( udCodeItem::cfCALL, pLang );
								fFirstRun = false;
							}
							else
							{
								if( !fConditionLess )sNewCondition << wxT(" ) ") << pLang->Or() << wxT(" ( ") << pLineElement->GetConditionAsString( udCodeItem::cfCALL, pLang );//pCondition->ToString( udCodeItem::cfCALL, pLang );
								// remove partial transition
								src->GetDiagramManager().RemoveShape(pTrans, false);
							}

							anode = anode->GetNext();
						}
						if( !fConditionLess )sNewCondition << wxT(" )");

						pLineElement = (udTransElementItem*)lstSubActs.GetFirst()->GetData()->GetUserData();
						// create new guard string
						//pLineElement->SetConditionString(sNewCondition);
						pNewCond = new udConditionItem();
						pNewCond->SetInline( true );
						pNewCond->SetCode( sNewCondition );
						// clear previous condition
						pLineElement->ClearCodeItems( CLASSINFO(udConditionItem) );
						pLineElement->ClearCodeItems( CLASSINFO(udEventItem) );
						// set new condition
						pLineElement->AssignCodeItem( pNewCond );
						
						pLineElement->SetName(wxString::Format(wxT("Optimized transition %d"), nIndex));

						nIndex++;
						fMerged = true;
					}
				}
			}
		}

		snode = snode->GetNext();
	}

	return fMerged;
}

bool udStateChartOptimizer::MergeDirectBranches(udDiagramItem *src)
{
	bool fMerged = false;
	wxString sNewAction;

	m_lstProcessed.Clear();
	m_lstBranches.Clear();

	// find all direct diagram branches
	ShapeList *pBranch, lstST, lstET;
	ShapeList lstInitialStates;
	src->GetDiagramManager().GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);
	src->GetDiagramManager().GetShapes(CLASSINFO(umlEntryItem), lstInitialStates);
	src->GetDiagramManager().GetShapes(CLASSINFO(umlHistoryItem), lstInitialStates);

	ShapeList::compatibility_iterator node = lstInitialStates.GetFirst();
	while( node )
	{
		TrackBranch(node->GetData(), NULL, NULL);
		node = node->GetNext();
	}

	if( m_lstBranches.GetFirst() )
	{
		wxSFShapeBase *pFirst, *pLast, *pState;
		wxSFLineShape *pUpdatedTransition, *pTrans;
		udTransElementItem *pUpdTransElement, *pTransElement;

		// process all branches containing more than one state
		BranchList::compatibility_iterator bnode = m_lstBranches.GetFirst();
		while( bnode )
		{
			pBranch = bnode->GetData();
			if( pBranch->GetCount() > 1 )
			{
				pFirst = pBranch->GetFirst()->GetData();
				pLast = pBranch->GetLast()->GetData();

				// get previous state of the first state
				lstET.Clear();
				src->GetDiagramManager().GetAssignedConnections(pFirst, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineENDING, lstET);

				pUpdatedTransition = (wxSFLineShape*)lstET.GetFirst()->GetData();
				pUpdTransElement = (udTransElementItem*)pUpdatedTransition->GetUserData();

				// reconnect updated transition
				pUpdatedTransition->SetTrgShapeId(pLast->GetId());

				ShapeList::compatibility_iterator snode = pBranch->GetFirst();
				while( snode && (snode != pBranch->GetLast()) )
				{
					pState = snode->GetData();

					// get outcomming transition
					lstST.Clear();
					src->GetDiagramManager().GetAssignedConnections(pState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstST);
					pTrans = (wxSFLineShape*)lstST.GetFirst()->GetData();

					// get action list from the transition
					pTransElement = (udTransElementItem*)pTrans->GetUserData();
					if( pTransElement->HasActions() )
					{
						if( !pUpdTransElement->HasActions() )
						{
							//pUpdTransElement->SetActionString(pTransElement->GetActionsString());
							pUpdTransElement->ClearCodeItems( CLASSINFO(udActionItem) );
							pUpdTransElement->CopyActionItems( pTransElement );
						}
						else
							//pUpdTransElement->SetActionString(pUpdTransElement->GetActionsString() + wxT(", ") + pTransElement->GetActionsString());
							pUpdTransElement->CopyActionItems( pTransElement );
					}

					// remove ununsed states and transition from automaton
					src->GetDiagramManager().RemoveShape(pState);

					fMerged = true;

					snode = snode->GetNext();
				}
			}

			bnode = bnode->GetNext();
		}
	}

	// clean up
	m_lstProcessed.Clear();

	m_lstBranches.DeleteContents(true);
	m_lstBranches.Clear();
	m_lstBranches.DeleteContents(false);

	return fMerged;
}

void udStateChartOptimizer::FindTransWithIdenticalTarget(ShapeList& transitions, ShapeList& sublist)
{
	sublist.Clear();

	ShapeList::compatibility_iterator node = transitions.GetFirst();
	if( !node ) return;

	wxSFLineShape *pTrans = (wxSFLineShape*)node->GetData();
	int nTrgId = pTrans->GetTrgShapeId();
	while(node)
	{
		pTrans = (wxSFLineShape*)node->GetData();
		if( pTrans->GetTrgShapeId() == nTrgId )
		{
			node = node->GetNext();
			transitions.DeleteObject(pTrans);
			sublist.Append(pTrans);
		}
		else
			node = node->GetNext();
	}
}

void udStateChartOptimizer::FindTransWithIdenticalActions(ShapeList& transitions, ShapeList& sublist)
{
	sublist.Clear();

	ShapeList::compatibility_iterator node = transitions.GetFirst();
	if( !node ) return;

	udTransElementItem *pTransElement;
	wxSFLineShape *pTrans = (wxSFLineShape*)node->GetData();
	wxString sActions, sTemplate = ((udTransElementItem*)pTrans->GetUserData())->GetActionsString();
	sTemplate.Replace(wxT(" "), wxT(""));

	while(node)
	{
		pTrans = (wxSFLineShape*)node->GetData();
		pTransElement = (udTransElementItem*)pTrans->GetUserData();

		sActions = pTransElement->GetActionsString();
		sActions.Replace(wxT(" "), wxT(""));

		if( sActions == sTemplate )
		{
			node = node->GetNext();
			transitions.DeleteObject(pTrans);
			sublist.Append(pTrans);
		}
		else
			node = node->GetNext();
	}
}

void udStateChartOptimizer::TrackBranch(wxSFShapeBase *state, wxSFLineShape *intrans, ShapeList *branch)
{
	wxASSERT(state);
	if( !state ) return;

	wxSFDiagramManager *pManager = (wxSFDiagramManager*)state->GetParentManager();
	wxASSERT(pManager);
	if( !pManager ) return;

	wxSFShapeBase *pSrcState;
	wxSFLineShape *pTrans;
	udTransElementItem *pTransElement;

	ShapeList lstST, lstET, lstST2;
	pManager->GetAssignedConnections(state, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstST);
	pManager->GetAssignedConnections(state, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineENDING, lstET);

	//if there are any ending transitions in the state then we can proceed to another step...
	if( intrans && lstET.GetFirst()
        && !udPROJECT::GetDiagramElement( state )->IsKindOf(CLASSINFO(udSubDiagramElementItem))
        && !state->IsKindOf(CLASSINFO(umlCompStateItem)))
	{
		pTransElement = (udTransElementItem*)intrans->GetUserData();

		// if the transition is conditionless then insert it into branch buffer
		if( pTransElement && !pTransElement->HasCondition() )
		{
			lstST2.Clear();
			// determine whether this transition is only one path from previous state
			pSrcState = pManager->FindShape(intrans->GetSrcShapeId());
			pManager->GetAssignedConnections(pSrcState, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstST2);
			if( lstST2.GetCount() == 1 )
			{
				// if current branch list exists then use it, otherwise create new branch and append it to branches list
				if(branch)
				{
					branch->Append(state);
				}
				else
				{
					branch = new ShapeList;
					branch->Append(state);
					m_lstBranches.Append(branch);
				}
				if((lstST.GetCount()>1)||(lstET.GetCount()>1)||state->IsKindOf(CLASSINFO(umlHistoryItem)))branch = NULL;
			}
			else
				branch = NULL;
		}
		else
		{
			// this state is not part of direct branch so reset the current branch list
			branch = NULL;
		}
	}
	else
	{
		// this state is not part of direct branch so reset the current branch list
		branch = NULL;
	}

	// add state to 'processed' list
	if(m_lstProcessed.IndexOf(state)==wxNOT_FOUND)
	{
		m_lstProcessed.Append(state);
		// check next states
		ShapeList::compatibility_iterator node = lstST.GetFirst();
		while(node)
		{
			pTrans = (wxSFLineShape*)node->GetData();
			TrackBranch(pManager->FindShape(pTrans->GetTrgShapeId()), pTrans, branch);

			node = node->GetNext();
		}
	}
}
