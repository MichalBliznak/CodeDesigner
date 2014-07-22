#include "LCEITransitionProcessor.h"
#include "StateChartGenerator.h"
#include "LoopCaseAlgorithm.h"
#include "ElifAlgorithm.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udLCEITransitionProcessor, udStateChartElementProcessor);

udLCEITransitionProcessor::udLCEITransitionProcessor()
{
    m_pParentGenerator = NULL;
}

udLCEITransitionProcessor::udLCEITransitionProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCEITransitionProcessor::~udLCEITransitionProcessor()
{
}

void udLCEITransitionProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	bool fIndent;
	bool fOneTarget = true;
	bool fNonBlocking = false;
	bool fHasFinalState = false;
	long nPrevTrgId = -1;

	//SerializableList lstActs;
	wxString sCond;
	wxArrayString arrActions;

    wxSFLineShape *pTrans = NULL;
	wxSFShapeBase *pTrgShape = NULL;
	wxSFShapeBase *pSrcShape = NULL;
    udTransElementItem *pTransElement;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    wxSFDiagramManager *pDiagManager = element->GetShapeManager();
	wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();
	
	udSStateChartDiagramItem *pSCH = wxDynamicCast( ((udLoopCaseAlgorithm*)m_pParentGenerator->GetActiveAlgorithm())->GetProcessedDiagram(), udSStateChartDiagramItem );
	if( pSCH ) fNonBlocking = pSCH->IsNonBlocking();
	
	fHasFinalState = pDiagManager->Contains(CLASSINFO(umlFinalItem));
	
	// find history state at the same level like processed element
	wxSFShapeBase *pHistory = NULL;
	if( element->GetParentShape() )
	{
		pHistory = (wxSFShapeBase*)element->GetParentShape()->GetFirstChild( CLASSINFO( umlHistoryItem ) );
	}

    // process all states transition
    ShapeList lstTransitions;
    pDiagManager->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

	// sort transitions
	((udStateChartGenerator*)m_pParentGenerator)->SortTransitions(lstTransitions, sortDESC);

    ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
    while(node)
    {
        pTrans = (wxSFLineShape*)node->GetData();
        pTransElement = (udTransElementItem*)pTrans->GetUserData();
		
		// try to determine whether all transitions have the same target
		if( node != lstTransitions.GetFirst() )
		{
			if( nPrevTrgId != pTrans->GetTrgShapeId() )
			{
				fOneTarget = false;
			}
		}
		nPrevTrgId = pTrans->GetTrgShapeId();

		// get current condition and actions
		arrActions.Clear();
		
		// determine whether the transition is guarded by event flag
		udEventLinkItem *pEvtLink = wxDynamicCast( pTransElement->GetCondition(), udEventLinkItem );
		
		sCond = pTransElement->GetConditionAsString( udCodeItem::cfCALL, pLang );
		pTransElement->GetActionsAsStrings( udCodeItem::cfCALL, pLang, udfCODEMARKS, arrActions );

		fIndent = true;

        if(node == lstTransitions.GetFirst())
        {
			if( !sCond.IsEmpty() )
			{
				pLang->IfCmd( sCond );
			}
			else
				fIndent = false;
        }
        else if(node == lstTransitions.GetLast())
        {
			if( !sCond.IsEmpty() )
			{
				pLang->ElseIfCmd( sCond );
			}
			else
				pLang->ElseCmd();
        }
        else
            pLang->ElseIfCmd( sCond );

        if( fIndent )pLang->BeginCmd();

        pLang->SingleLineCommentCmd(wxString::Format(wxT("Transition ID: %s"), m_pParentGenerator->MakeIDName(pTransElement).c_str()));

		// clear event flag if required
		if( pEvtLink && pEvtLink->IsClearFlag() ) {
			pLang->SingleLineCommentCmd( wxT("Clear event flag") );
			pLang->VariableAssignCmd( pEvtLink->ToString( udCodeItem::cfCALL, pLang ), pLang->False() );
		}
		
		// write actions
		if( !arrActions.IsEmpty() )
		{
			pLang->SingleLineCommentCmd(wxT("Actions:"));
			
			for( size_t i = 0; i < arrActions.GetCount(); i++ )
			{
				pLang->WriteCodeBlocks( arrActions[i] );
			}
		}
		
		// set state variable to target emlement
		pTrgShape = pDiagManager->FindShape(((wxSFLineShape*)pTrans)->GetTrgShapeId());
		
		if( !pSrcShape ) {
			pSrcShape = pDiagManager->FindShape(((wxSFLineShape*)pTrans)->GetSrcShapeId());
		}
	
		if( pHistory && ( pTrgShape->GetParentShape() != pHistory->GetParentShape() ) )
			pLang->VariableAssignCmd( pLang->MakeValidIdentifier( udLABEL::GetContent( pHistory, udLABEL::ltTITLE ).Lower() ), m_pParentGenerator->MakeIDName(element));
		
		if( pTrgShape != element )
			pLang->VariableAssignCmd( wxT("state"), m_pParentGenerator->MakeIDName(pTrgShape));
		
        if( fIndent ) pLang->EndCmd();

        node = node->GetNext();
    }

    // close the 'case' statement with 'break' if neccessary
    if( m_pParentGenerator->GetActiveAlgorithm()->IsKindOf(CLASSINFO(udLoopCaseAlgorithm)) )
    {
		if( fNonBlocking && fHasFinalState ) {
			pLang->ReturnCmd( m_pParentGenerator->MakeIDName(pSrcShape) );
			
		} else {
			wxSFLineShape* pCondlessPath = GetConditionlessPath(element);
			if( !pCondlessPath ||
				!pNext ||
				(pNext && (pCondlessPath->GetTrgShapeId() != pNext->GetId())) ||
				!fOneTarget ||
				fNonBlocking ) //(lstTransitions.GetCount() > 1) )
			{
				pLang->BreakCmd();
			}
		}
    }
	else if( m_pParentGenerator->GetActiveAlgorithm()->IsKindOf(CLASSINFO(udElifAlgorithm)) ) {
		if( fNonBlocking && fHasFinalState ) {
			pLang->ReturnCmd( m_pParentGenerator->MakeIDName(pSrcShape) );
		}
	}
}
