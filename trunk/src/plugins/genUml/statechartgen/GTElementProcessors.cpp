#include "GTElementProcessors.h"
#include "StateChartGenerator.h"
#include "../../diagUml/DiagUml.h"

/////////////////////////////////////////////////////////////////////////////////////
// udGTTransitionProcessor class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGTTransitionProcessor, udStateChartElementProcessor);

udGTTransitionProcessor::udGTTransitionProcessor()
{
    m_pParentGenerator = NULL;
}

udGTTransitionProcessor::udGTTransitionProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udGTTransitionProcessor::~udGTTransitionProcessor()
{
}

void udGTTransitionProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

	udAlgorithm *pAlg = m_pParentGenerator->GetActiveAlgorithm();
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    wxSFDiagramManager *pDiagManager = element->GetShapeManager();
    wxSFShapeBase *pNext = pAlg->GetNextElement();
	
	// find history state at the same level like processed element
	wxSFShapeBase *pHistory = NULL;
	if( element->GetParentShape() )
	{
		pHistory = (wxSFShapeBase*)element->GetParentShape()->GetFirstChild( CLASSINFO( umlHistoryItem ) );
	}

    // process all states transition
	bool fIndent, fJump;

	wxString sCond;
	wxArrayString arrActions;
	/*SerializableList lstActions;*/

	wxSFShapeBase *pTrgShape;
    wxSFLineShape *pTrans = NULL;
	wxSFLineShape *pCondLess = GetConditionlessPath(element);

    udTransElementItem *pTransElement;

    ShapeList lstTransitions;
    pDiagManager->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

	// sort transitions
	((udStateChartGenerator*)m_pParentGenerator)->SortTransitions(lstTransitions, sortDESC);

    ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
    while(node)
    {
        pTrans = (wxSFLineShape*)node->GetData();
        pTransElement = (udTransElementItem*)pTrans->GetUserData();

		// get current condition and actions
		arrActions.Clear();
		/*lstActions.Clear();*/
		
		sCond = pTransElement->GetConditionAsString( udCodeItem::cfCALL, pLang );
		
		pTransElement->GetActionsAsStrings( udCodeItem::cfCALL, pLang, udfCODEMARKS, arrActions );
		/*pTransElement->GetActions( lstActions, udfORIGINAL );*/

		fIndent = true;
		fJump = true;
		
		if( pNext &&
			(pCondLess && (pTrans->GetTrgShapeId() == pCondLess->GetTrgShapeId() )) &&
			(pTrans->GetTrgShapeId() == pNext->GetId()) &&
			(pAlg->GetProcessedElements().IndexOf(pNext) == wxNOT_FOUND) ) fJump = false;
		
		
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
			{
				if( pTransElement->HasActions() || fJump )
				{
					pLang->ElseCmd();
				}
				else
					fIndent = false;
			}
        }
        else
            pLang->ElseIfCmd( sCond );

        if( fIndent )pLang->BeginCmd();

		if( !arrActions.IsEmpty() )
		{
			pLang->SingleLineCommentCmd(wxString::Format(wxT("Actions of transition ID: %s"), m_pParentGenerator->MakeIDName(pTransElement).c_str()));
			
			for( size_t i = 0; i < arrActions.GetCount(); i++ )
			{
				pLang->WriteCodeBlocks( arrActions[i] );
			}
			
			/*size_t i = 0;
			for( SerializableList::iterator it = lstActions.begin(); it != lstActions.end(); ++it, ++i )
			{
				udActionItem *pAct = (udActionItem*) *it;
				
				if( pAct->IsInline() )
				{
					pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pAct ) );
					pLang->WriteCodeBlocks( pAct->GetCode() );
					pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pAct ) );
				}
				else
					pLang->WriteCodeBlocks( arrActions[i] );
			}*/
		}

		if( fJump )
		{
			pTrgShape = pDiagManager->FindShape(((wxSFLineShape*)pTrans)->GetTrgShapeId());
			
			if( pHistory && ( pTrgShape->GetParentShape() != pHistory->GetParentShape() ))
				pLang->VariableAssignCmd( pLang->MakeValidIdentifier( udLABEL::GetContent( pHistory, udLABEL::ltTITLE ).Lower() ), m_pParentGenerator->MakeIDName(element));

			if( (pTrgShape != element) || pCondLess )
				pLang->GotoCmd(m_pParentGenerator->MakeIDName(pTrgShape) + wxT("_L"));
		}

        if( fIndent ) pLang->EndCmd();

        node = node->GetNext();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udGTSimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGTSimpleStateProcessor, udStateChartElementProcessor);

udGTSimpleStateProcessor::udGTSimpleStateProcessor()
{
    m_pParentGenerator = NULL;
}

udGTSimpleStateProcessor::udGTSimpleStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udGTSimpleStateProcessor::~udGTSimpleStateProcessor()
{
}

void udGTSimpleStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();

	bool fOmitLabel = false;
	bool fSelfJump = !GetConditionlessPath(element) || (!pNext && !HasOutput(element) );
	
	if( !fSelfJump ) fOmitLabel = ShouldOmitLabel(element);

    // create code label
    if( fSelfJump || !fOmitLabel ) pLang->LabelCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

	if( fSelfJump )
	{
		pLang->GotoCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));
	}

    pLang->NewLine();
}

bool udGTSimpleStateProcessor::HasOutput(wxSFShapeBase* element)
{
	ShapeList lstTrans;
	element->GetShapeManager()->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTrans);
	
	return !lstTrans.IsEmpty();
}

bool udGTSimpleStateProcessor::ShouldOmitLabel(wxSFShapeBase *element)
{	
	bool fOnlyOneSource = true;
	int nPrevStateId = -1;
	ShapeList lstTrans;
	
	udSettings &Settings = IPluginManager::Get()->GetProjectSettings();
	if( !Settings.GetProperty( wxT("Omit unused labels") )->AsBool() ) return false;

	wxSFDiagramManager *pManager = element->GetShapeManager();
	wxSFShapeBase *pPrev = m_pParentGenerator->GetActiveAlgorithm()->GetPrevElement();
	
	wxSFShapeBase *pParent = element->GetParentShape();
	if( pParent && pParent->GetFirstChild( CLASSINFO( umlHistoryItem ) ) && !element->IsKindOf( CLASSINFO(umlFinalItem) ) ) return false;
	
	pManager->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTrans);
	if( lstTrans.IsEmpty() && !element->IsKindOf(CLASSINFO(umlFinalItem)) ) return false;
	
	lstTrans.Clear();
	pManager->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineENDING, lstTrans);
	
	((udStateChartGenerator*)m_pParentGenerator)->SortTransitions(lstTrans, sortASC);

	wxSFLineShape *pTrans = NULL;
	ShapeList::compatibility_iterator node = lstTrans.GetLast();
	while( node )
	{
		pTrans = (wxSFLineShape*)node->GetData();
		if( node == lstTrans.GetLast() )
		{
			nPrevStateId = pTrans->GetSrcShapeId();
		}
		else
		{
			if( nPrevStateId != pTrans->GetSrcShapeId() )
			{
				fOnlyOneSource = false;
			}
		}
		node  = node->GetPrevious();
	}
	
	if( fOnlyOneSource )
	{
		if( pPrev )
		{
			return ( pPrev->GetId() == nPrevStateId ) && ( GetConditionlessPath(pPrev) == pTrans );
		}
		else
			return ( nPrevStateId == -1 ) && GetConditionlessPath(element);
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////
// udGTSubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGTSubStateProcessor, udGTSimpleStateProcessor);

udGTSubStateProcessor::udGTSubStateProcessor()
{
    m_pParentGenerator = NULL;
}

udGTSubStateProcessor::udGTSubStateProcessor(udGenerator *parent)
: udGTSimpleStateProcessor(parent)
{
}

udGTSubStateProcessor::~udGTSubStateProcessor()
{
}

void udGTSubStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();
	
    udSubDiagramElementItem *pSubElement = (udSubDiagramElementItem*) udPROJECT::GetDiagramElement( element );

	// do not store return value if required
	bool fStoreRetVal = false;
	if( pSubElement->IsKindOf(CLASSINFO(udSCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udSCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
		
	} else if( pSubElement->IsKindOf(CLASSINFO(udHCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udHCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
	}
	
	bool fOmitLabel = ShouldOmitLabel(element);

    // create label statement
    if( !fOmitLabel )pLang->LabelCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));
    pLang->SingleLineCommentCmd(wxT("call substate function"));
	
	// assign value of submachine final state ID to local variable
	wxString sFcnCall;
	
	pLang->PushCode();
	
	udFunctionItem *pFcn = IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( pSubElement->GetSubDiagram() );
	if( pFcn ) pLang->WriteCodeBlocks( pFcn->ToString(udCodeItem::cfCALL, pLang) );
	else
		pLang->FunctionCallCmd(m_pParentGenerator->MakeValidIdentifier(pSubElement->GetSubDiagram()->GetName()), wxEmptyString);
		
	sFcnCall = pLang->GetCodeBuffer().Trim(false);
	
	pLang->PopCode();
	
	if( fStoreRetVal && pSubElement->GetSubDiagram()->GetDiagramManager().Contains(CLASSINFO(umlFinalItem)) )
	{
		wxString sRetVar = sFcnCall.BeforeFirst('(').MakeLower() + wxT("_retval");
		//wxString sRetVar = pLang->MakeValidIdentifier( udLABEL::GetContent(element, udLABEL::ltTITLE) + wxT("_retval") );
		
		if( !pLang->Delimiter().IsEmpty() ) sFcnCall.Replace( pLang->Delimiter(), wxT("") );
		if( pFcn ) pLang->VariableDeclAssignCmd( pFcn->GetDataTypeString(pLang), sRetVar, sFcnCall.Trim().Trim(false) );
		else
			pLang->VariableDeclAssignCmd( wxT("STATE_T"), sRetVar, sFcnCall.Trim() );
	}
	else
		pLang->WriteCodeBlocks( sFcnCall );

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

	if( !GetConditionlessPath(element) || !pNext)
	{
		pLang->GotoCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));
	}

    pLang->NewLine();
}

/////////////////////////////////////////////////////////////////////////////////////
// udGTHistoryProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGTHistoryProcessor, udGTSimpleStateProcessor);

udGTHistoryProcessor::udGTHistoryProcessor()
{
    m_pParentGenerator = NULL;
}

udGTHistoryProcessor::udGTHistoryProcessor(udGenerator *parent)
: udGTSimpleStateProcessor(parent)
{
}

udGTHistoryProcessor::~udGTHistoryProcessor()
{
}

void udGTHistoryProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	udCompStateElementItem *pStateElement;
	udStateActionLinkItem *pAction;
	SerializableList lstActions;
	SerializableList::compatibility_iterator anode;

	wxString sCondition, sJump;
	// bool fOmitLabel = ShouldOmitLabel(element);
	bool fActionExist;

    // create label statement
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    // if( !fOmitLabel )pLang->LabelCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));
	
	// create direct jumps to all states managed by this history state
	wxSFShapeBase *pTrg, *pParent = element->GetParentShape();
	
	ShapeList lstTargets;
	pParent->GetChildShapes( CLASSINFO( umlCompStateItem ), lstTargets );
	pParent->GetChildShapes( CLASSINFO( umlSimpleStateItem ), lstTargets );
	
	ShapeList::compatibility_iterator node = lstTargets.GetFirst();
	while( node )
	{
		pTrg = node->GetData();
		
		sCondition.Printf( wxT("%s %s %s"), pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ).c_str(), 
											pLang->Equal().c_str(),
											m_pParentGenerator->MakeIDName( pTrg ).c_str() );
											
		if( node == lstTargets.GetFirst() )
		{
			pLang->IfCmd( sCondition );
		}
		else
		{
			pLang->ElseIfCmd( sCondition );
		}
		
		pLang->BeginCmd();
		
		// generate entry actions for all possible target elements
		pStateElement = (udCompStateElementItem*) pTrg->GetUserData();
		
		fActionExist = false;
		lstActions.Clear();
		pStateElement->GetChildren( CLASSINFO(udStateActionLinkItem), lstActions );
		anode = lstActions.GetFirst();
		while( anode )
		{
			pAction = (udStateActionLinkItem*) anode->GetData();
			if( pAction->GetActionType() == udStateActionLinkItem::saENTRY )
			{
				pLang->WriteCodeBlocks( pAction->ToString( udCodeItem::cfCALL, pLang ) );
				fActionExist = true;
			}
			anode = anode->GetNext();
			if( !fActionExist ) pLang->WriteCodeBlocks( pLang->Dummy() );
		}
		
		pLang->GotoCmd( m_pParentGenerator->MakeIDName( pTrg ) + wxT("_L") );
		pLang->EndCmd();
		
		node = node->GetNext();
	}

    pLang->NewLine();
}

/////////////////////////////////////////////////////////////////////////////////////
// udGTFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGTFinalItemProcessor, udGTSimpleStateProcessor);

udGTFinalItemProcessor::udGTFinalItemProcessor()
{
    m_pParentGenerator = NULL;
}

udGTFinalItemProcessor::udGTFinalItemProcessor(udGenerator *parent)
: udGTSimpleStateProcessor(parent)
{
}

udGTFinalItemProcessor::~udGTFinalItemProcessor()
{
}

void udGTFinalItemProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

	if( !ShouldOmitLabel(element) )pLang->LabelCmd(m_pParentGenerator->MakeIDName(element) + wxT("_L"));
	
	wxSFShapeBase *pParent = element->GetParentShape();
	if( !pParent )
	{
		udFinalElementItem *pFinalElement = (udFinalElementItem*) udPROJECT::GetDiagramElement(element);
		
		if( pFinalElement->GetRetVal() == wxT("<default>") )
			pLang->ReturnCmd( m_pParentGenerator->MakeIDName(element) );
		else
			pLang->ReturnCmd( pFinalElement->GetRetVal() );
	}
	else
	{
		// process connected transitions
		m_transProcessor.SetParentGenerator(m_pParentGenerator);
		m_transProcessor.ProcessElement(element);
	}
	
	pLang->NewLine();
}
