#include "LCElementProcessors.h"
#include "LoopCaseAlgorithm.h"
#include "../../diagUml/DiagUml.h"

/////////////////////////////////////////////////////////////////////////////////////
// udLCSimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udLCSimpleStateProcessor, udStateChartElementProcessor);

udLCSimpleStateProcessor::udLCSimpleStateProcessor()
{
    m_pParentGenerator = NULL;
}

udLCSimpleStateProcessor::udLCSimpleStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCSimpleStateProcessor::~udLCSimpleStateProcessor()
{
}

void udLCSimpleStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();

	// create 'case' statement
    pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
    //pLang->IncIndentation();
	pLang->BeginCmd();

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

	/*wxSFLineShape* pCondlessPath = GetConditionlessPath(element);
	if( !pCondlessPath || (pNext && (pCondlessPath->GetTrgShapeId() != pNext->GetId())) )
	{
		pLang->BreakCmd();
	}*/

    //pLang->NewLine();
	pLang->EndCmd();
    //pLang->DecIndentation();
}

/////////////////////////////////////////////////////////////////////////////////////
// udLCSubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udLCSubStateProcessor, udStateChartElementProcessor);

udLCSubStateProcessor::udLCSubStateProcessor()
{
    m_pParentGenerator = NULL;
}

udLCSubStateProcessor::udLCSubStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCSubStateProcessor::~udLCSubStateProcessor()
{
}

void udLCSubStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();

    udSubDiagramElementItem *pSubElement = (udSubDiagramElementItem*) udPROJECT::GetDiagramElement( element );

	// do not store return value if required
	bool fStoreRetVal = false;
	if( pSubElement->IsKindOf(CLASSINFO(udSCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udSCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
		
	} else if( pSubElement->IsKindOf(CLASSINFO(udHCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udHCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
	}
	
    // create 'case' statement
    pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
    //pLang->IncIndentation();
	pLang->BeginCmd();
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

	pLang->EndCmd();
    //pLang->NewLine();
    //pLang->DecIndentation();
}

/////////////////////////////////////////////////////////////////////////////////////
// udLCStateProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*IMPLEMENT_DYNAMIC_CLASS(udLCStateProcessor, udStateChartElementProcessor);

udLCStateProcessor::udLCStateProcessor()
{
    m_pParentGenerator = NULL;
}

udLCStateProcessor::udLCStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCStateProcessor::~udLCStateProcessor()
{
}

void udLCStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetActiveAlgorithm()->GetNextElement();

	// create 'case' statement
	pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
	pLang->IncIndentation();

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

    pLang->NewLine();
    pLang->DecIndentation();
}*/

/////////////////////////////////////////////////////////////////////////////////////
// udLCDecisionProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*IMPLEMENT_DYNAMIC_CLASS(udLCDecisionProcessor, udStateChartElementProcessor);

udLCDecisionProcessor::udLCDecisionProcessor()
{
    m_pParentGenerator = NULL;
}

udLCDecisionProcessor::udLCDecisionProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCDecisionProcessor::~udLCDecisionProcessor()
{
}

void udLCDecisionProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

	// create 'case' statement
    pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
    pLang->IncIndentation();

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

    pLang->NewLine();
    pLang->DecIndentation();
}*/

/////////////////////////////////////////////////////////////////////////////////////
// udLCHistoryProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udLCHistoryProcessor, udStateChartElementProcessor);

udLCHistoryProcessor::udLCHistoryProcessor()
{
    m_pParentGenerator = NULL;
}

udLCHistoryProcessor::udLCHistoryProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCHistoryProcessor::~udLCHistoryProcessor()
{
}

void udLCHistoryProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    // create 'case' statement
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	bool fActionExist;

    pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
    pLang->IncIndentation();
	
	// generate entry actions for all possible target elements
	udCompStateElementItem *pStateElement;
	udStateActionLinkItem *pAction;
	SerializableList lstActions;
	SerializableList::compatibility_iterator anode;
	
	ShapeList lstCompStates;
	element->GetParentShape()->GetChildShapes(CLASSINFO(umlCompStateItem), lstCompStates);
	
	pLang->SingleLineCommentCmd( wxT("call entry actions of possible target states") );
	pLang->SwitchCmd( pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ) );
	pLang->BeginCmd();
	
	ShapeList::compatibility_iterator node = lstCompStates.GetFirst();
	while( node )
	{
		pStateElement = (udCompStateElementItem*) node->GetData()->GetUserData();
		
		lstActions.Clear();
		pStateElement->GetChildren( CLASSINFO(udStateActionLinkItem), lstActions );
		
		if( !lstActions.IsEmpty() )
		{
			pLang->CaseCmd( m_pParentGenerator->MakeIDName(pStateElement) );
			pLang->IncIndentation();
			
			fActionExist = false;
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
			
			pLang->BreakCmd();
			pLang->NewLine();
			pLang->DecIndentation();
		}
		
		node = node->GetNext();
	}
	
	pLang->EndCmd();
	
	pLang->VariableAssignCmd( wxT("state"), pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ) );
	
	pLang->BreakCmd();
    pLang->NewLine();
    pLang->DecIndentation();
}

/////////////////////////////////////////////////////////////////////////////////////
// udLCFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udLCFinalItemProcessor, udStateChartElementProcessor);

udLCFinalItemProcessor::udLCFinalItemProcessor()
{
    m_pParentGenerator = NULL;
}

udLCFinalItemProcessor::udLCFinalItemProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udLCFinalItemProcessor::~udLCFinalItemProcessor()
{
}

void udLCFinalItemProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	bool fNonBlocking = false;

    // create 'case' statement
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	wxSFShapeBase *pParent = element->GetParentShape();
	wxSFDiagramManager *pDiagManager = (wxSFDiagramManager*) element->GetParentManager();
	
	// get inital states
    ShapeList lstInitialStates;
    pDiagManager->GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);
	wxSFShapeBase *pInitial = lstInitialStates.GetFirst()->GetData();
	
	udSStateChartDiagramItem *pSCH = wxDynamicCast( ((udLoopCaseAlgorithm*)m_pParentGenerator->GetActiveAlgorithm())->GetProcessedDiagram(), udSStateChartDiagramItem );
	if( pSCH ) fNonBlocking = pSCH->IsNonBlocking();

    pLang->CaseCmd(m_pParentGenerator->MakeIDName(element));
    //pLang->IncIndentation();
	pLang->BeginCmd();
	
	// reset "state" variable in non-blocking state chart to the initial value
	if( fNonBlocking ) pLang->VariableAssignCmd( wxT("state"), m_pParentGenerator->MakeIDName(pInitial));
	
	// generate "return" statement
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
    //pLang->NewLine();
    //pLang->DecIndentation();
	pLang->EndCmd();
}
