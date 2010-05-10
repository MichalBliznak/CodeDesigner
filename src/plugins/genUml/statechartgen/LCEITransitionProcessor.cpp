#include "LCEITransitionProcessor.h"
#include "StateChartGenerator.h"
#include "LoopCaseAlgorithm.h"
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
	long nPrevTrgId = -1;

	//SerializableList lstActs;
	wxString sCond;
	//wxArrayString arrActions;
	SerializableList lstActions;

    wxSFLineShape *pTrans = NULL;
	wxSFShapeBase *pTrgShape = NULL;
    udTransElementItem *pTransElement;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    wxSFDiagramManager *pDiagManager = element->GetShapeManager();
	wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();
	
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
	((udStateChartGenerator*)m_pParentGenerator)->SortTransitions(lstTransitions);

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
		//arrActions.Clear();
		lstActions.Clear();
		
		sCond = pTransElement->GetConditionAsString( udCodeItem::cfCALL, pLang );
		//pTransElement->GetActionsAsStrings( udCodeItem::cfCALL, pLang, arrActions );
		pTransElement->GetActions( lstActions, udfORIGINAL );

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

		/*if( !arrActions.IsEmpty() )
		{
			pLang->SingleLineCommentCmd(wxT("Actions:"));
			
			for( size_t i = 0; i < arrActions.GetCount(); i++ )
			{
				pLang->WriteCodeBlocks( arrActions[i] );
			}
		}*/
		
		if( !lstActions.IsEmpty() ) pLang->SingleLineCommentCmd(wxT("Actions:"));
		
		for( SerializableList::iterator it = lstActions.begin(); it != lstActions.end(); ++it )
		{
			udActionItem *pAct = (udActionItem*) *it;
			
			if( pAct->IsInline() )
			{
				pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pAct ) );
				pLang->WriteCodeBlocks( pAct->GetCode() );
				pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pAct ) );
			}
			else
				pLang->WriteCodeBlocks( pAct->ToString(  udCodeItem::cfCALL, pLang) );
		}
		
		// set state variable to target emlement
		pTrgShape = pDiagManager->FindShape(((wxSFLineShape*)pTrans)->GetTrgShapeId());
	
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
        wxSFLineShape* pCondlessPath = GetConditionlessPath(element);
        if( !pCondlessPath || !pNext || (pNext && (pCondlessPath->GetTrgShapeId() != pNext->GetId())) || !fOneTarget ) //(lstTransitions.GetCount() > 1) )
        {
            pLang->BreakCmd();
        }
    }
}
