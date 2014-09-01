#include "EIElementProcessors.h"
#include "ElifAlgorithm.h"
#include "projectbase/GeneratorBase.h"
#include "../../diagUml/DiagUml.h"

/////////////////////////////////////////////////////////////////////////////////////
// udEISimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udEISimpleStateProcessor, udStateChartElementProcessor);

udEISimpleStateProcessor::udEISimpleStateProcessor()
{
    m_pParentGenerator = NULL;
}

udEISimpleStateProcessor::udEISimpleStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udEISimpleStateProcessor::~udEISimpleStateProcessor()
{
}

void udEISimpleStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetAlgorithm()->GetNextElement();
    wxSFShapeBase *pPrev = m_pParentGenerator->GetActiveAlgorithm()->GetPrevElement();

    // create 'if' statement
    if(!pPrev)
    {
        pLang->IfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
    else
    {
        pLang->ElseIfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }

    pLang->BeginCmd();
    //pLang->SingleLineCommentCmd(wxString::Format(wxT("state action ID: %s"), m_pParentGenerator->MakeIDName(element).c_str()));

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

    pLang->EndCmd();
}

/////////////////////////////////////////////////////////////////////////////////////
// udEISubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udEISubStateProcessor, udStateChartElementProcessor);

udEISubStateProcessor::udEISubStateProcessor()
{
    m_pParentGenerator = NULL;
}

udEISubStateProcessor::udEISubStateProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udEISubStateProcessor::~udEISubStateProcessor()
{
}

void udEISubStateProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetAlgorithm()->GetNextElement();
    wxSFShapeBase *pPrev = m_pParentGenerator->GetActiveAlgorithm()->GetPrevElement();

    udSubDiagramElementItem *pSubElement = (udSubDiagramElementItem*)udPROJECT::GetDiagramElement( element );

	// do not store return value if required
	bool fStoreRetVal = false;
	if( pSubElement->IsKindOf(CLASSINFO(udSCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udSCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
		
	} else if( pSubElement->IsKindOf(CLASSINFO(udHCHSubDiagramElementItem)) ) {
		fStoreRetVal = ((udHCHSubDiagramElementItem*)pSubElement)->GetStoreRetVal();
	}
	
    if(!pPrev)
    {
        pLang->IfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
    else
    {
        pLang->ElseIfCmd(wxT("state")  + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
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
		
	/*udLanguage *pTmpLang = pLang->Clone();
	pTmpLang->FunctionCallCmd(m_pParentGenerator->MakeValidIdentifier(pSubElement->GetSubDiagram()->GetName()), wxEmptyString);
	if( pLang->Delimiter().IsEmpty() )
	{
		pLang->VariableDeclAssignCmd( wxT("STATE_T"), wxT("exit_point"), pTmpLang->GetCodeBuffer().Trim() );
	}
	else
	{
		wxString sBuff = pTmpLang->GetCodeBuffer();
		sBuff.Replace( pLang->Delimiter(), wxT("") );
		pLang->VariableDeclAssignCmd( wxT("STATE_T"), wxT("exit_point"), sBuff.Trim() );
	}
	delete pTmpLang;*/

    // process connected transitions
    m_transProcessor.SetParentGenerator(m_pParentGenerator);
    m_transProcessor.ProcessElement(element);

    pLang->EndCmd();
}

/////////////////////////////////////////////////////////////////////////////////////
// udEIHistoryProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udEIHistoryProcessor, udStateChartElementProcessor);

udEIHistoryProcessor::udEIHistoryProcessor()
{
    m_pParentGenerator = NULL;
}

udEIHistoryProcessor::udEIHistoryProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udEIHistoryProcessor::~udEIHistoryProcessor()
{
}

void udEIHistoryProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
    //wxSFShapeBase *pNext = m_pParentGenerator->GetAlgorithm()->GetNextElement();
    wxSFShapeBase *pPrev = m_pParentGenerator->GetActiveAlgorithm()->GetPrevElement();
	
	bool fActionExist;

    // create 'if' statement
    if(!pPrev)
    {
        pLang->IfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
    else
    {
        pLang->ElseIfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }

    pLang->BeginCmd();	
	
	// generate entry actions for all possible target elements
	bool fFirstRun = true;
	
	udCompStateElementItem *pStateElement;
	udStateActionLinkItem *pAction;
	SerializableList lstActions;
	SerializableList::compatibility_iterator anode;
	
	ShapeList lstCompStates;
	element->GetParentShape()->GetChildShapes(CLASSINFO(umlCompStateItem), lstCompStates);
	
	pLang->SingleLineCommentCmd( wxT("call entry actions of possible target states") );
	
	ShapeList::compatibility_iterator node = lstCompStates.GetFirst();
	while( node )
	{
		pStateElement = (udCompStateElementItem*) node->GetData()->GetUserData();
		
		lstActions.Clear();
		pStateElement->GetChildren( CLASSINFO(udStateActionLinkItem), lstActions );
		
		if( !lstActions.IsEmpty() )
		{
			if( fFirstRun )
			{
				pLang->IfCmd( pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ) + pLang->Equal() + m_pParentGenerator->MakeIDName(pStateElement) );
				fFirstRun = false;
			}
			else
				pLang->ElseIfCmd( pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ) + pLang->Equal() + m_pParentGenerator->MakeIDName(pStateElement) );
				
			pLang->BeginCmd();
			
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
			}
			if( !fActionExist ) pLang->WriteCodeBlocks( pLang->Dummy() );
			
			pLang->EndCmd();
		}
		
		node = node->GetNext();
	}
	
    pLang->VariableAssignCmd( wxT("state"), pLang->MakeValidIdentifier( udLABEL::GetContent( element, udLABEL::ltTITLE ).Lower() ) );
    pLang->EndCmd();
}

/////////////////////////////////////////////////////////////////////////////////////
// udEIFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udEIFinalItemProcessor, udStateChartElementProcessor);

udEIFinalItemProcessor::udEIFinalItemProcessor()
{
    m_pParentGenerator = NULL;
}

udEIFinalItemProcessor::udEIFinalItemProcessor(udGenerator *parent)
: udStateChartElementProcessor(parent)
{
}

udEIFinalItemProcessor::~udEIFinalItemProcessor()
{
}

void udEIFinalItemProcessor::ProcessElement(wxSFShapeBase *element)
{
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	bool fNonBlocking = false;

    wxSFShapeBase *pPrev = m_pParentGenerator->GetActiveAlgorithm()->GetPrevElement();
	wxSFShapeBase *pParent = element->GetParentShape();
	wxSFDiagramManager *pDiagManager = (wxSFDiagramManager*) element->GetParentManager();
	
	// get inital states
    ShapeList lstInitialStates;
    pDiagManager->GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);
	wxSFShapeBase *pInitial = lstInitialStates.GetFirst()->GetData();
	
	udSStateChartDiagramItem *pSCH = wxDynamicCast( ((udElifAlgorithm*)m_pParentGenerator->GetActiveAlgorithm())->GetProcessedDiagram(), udSStateChartDiagramItem );
	if( pSCH ) fNonBlocking = pSCH->IsNonBlocking();

    // create 'if' statement
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    if(!pPrev)
    {
        pLang->IfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
    else
    {
        pLang->ElseIfCmd(wxT("state") + pLang->Equal() + m_pParentGenerator->MakeIDName(element));
    }
    pLang->BeginCmd();
	
	// reset "state" variable in non-blocking state chart to the initial value
	if( fNonBlocking ) pLang->VariableAssignCmd( wxT("state"), m_pParentGenerator->MakeIDName(pInitial));
	
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
	
    pLang->EndCmd();
}

