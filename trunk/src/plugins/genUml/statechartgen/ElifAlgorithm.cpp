#include "ElifAlgorithm.h"
#include "EIElementProcessors.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udElifAlgorithm, udAlgorithm);

udElifAlgorithm::udElifAlgorithm()
{
    // initialize element processors
    m_mapElementProcessors[wxT("umlSimpleStateItem")] = new udEISimpleStateProcessor();
    m_mapElementProcessors[wxT("umlSubStateItem")] = new udEISubStateProcessor();
    m_mapElementProcessors[wxT("umlInitialItem")] = new udEISimpleStateProcessor();
    m_mapElementProcessors[wxT("umlFinalItem")] = new udEIFinalItemProcessor();
	
    m_mapElementProcessors[wxT("umlCompStateItem")] = new udEISimpleStateProcessor();
    m_mapElementProcessors[wxT("umlDecisionItem")] = new udEISimpleStateProcessor();
    m_mapElementProcessors[wxT("umlHistoryItem")] = new udEIHistoryProcessor();
    m_mapElementProcessors[wxT("umlEntryItem")] = new udEISimpleStateProcessor();
    m_mapElementProcessors[wxT("umlExitItem")] = new udEIFinalItemProcessor();

    m_sName = wxT("Else-If algorithm");

    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udElifAlgorithm::udElifAlgorithm(udGenerator *parent) : udAlgorithm(parent)
{
    // initialize element processors
    m_mapElementProcessors[wxT("umlSimpleStateItem")] = new udEISimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlSubStateItem")] = new udEISubStateProcessor(parent);
    m_mapElementProcessors[wxT("umlInitialItem")] = new udEISimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlFinalItem")] = new udEIFinalItemProcessor(parent);
	
    m_mapElementProcessors[wxT("umlCompStateItem")] = new udEISimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlDecisionItem")] = new udEISimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlHistoryItem")] = new udEIHistoryProcessor(parent);
    m_mapElementProcessors[wxT("umlEntryItem")] = new udEISimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlExitItem")] = new udEIFinalItemProcessor(parent);

    m_sName = wxT("Else-If algorithm");

    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udElifAlgorithm::~udElifAlgorithm()
{
}

bool udElifAlgorithm::Initialize()
{
    m_pPrevElement = NULL;
    m_pNextElement = NULL;

    return true;
}

void udElifAlgorithm::ProcessAlgorithm(udDiagramItem *src)
{
    // test "prerequisites"
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

    wxASSERT(m_pParentGenerator->GetActiveLanguage());
    if(!m_pParentGenerator->GetActiveLanguage())return;

    wxSFDiagramManager *pDiagManager = &src->GetDiagramManager();
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	
	udSStateChartDiagramItem *pSCH = wxDynamicCast( src, udSStateChartDiagramItem );
	if( ! pSCH ) return;
	
	bool fNonBlocking = pSCH->IsNonBlocking();
	bool fHasFinalState = pDiagManager->Contains(CLASSINFO(umlFinalItem));

    // get inital states
    ShapeList lstInitialStates;
    pDiagManager->GetShapes(CLASSINFO(umlInitialItem), lstInitialStates);

    // create diagram function declaration
	if( !pSCH->IsInline() )
	{
		udFunctionItem *pDeclFcn = IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( pSCH );
		if( pDeclFcn )
		{
			pLang->WriteCodeBlocks( pDeclFcn->ToString( udCodeItem::cfDEFINITION, pLang ) );
		}
		else
		{
			if( fHasFinalState )
				pLang->FunctionDefCmd(wxT("STATE_T"), m_pParentGenerator->MakeValidIdentifier(pSCH->GetName()), wxEmptyString );
			else
				pLang->FunctionDefCmd(pLang->GetDataTypeString(udLanguage::DT_VOID), m_pParentGenerator->MakeValidIdentifier(pSCH->GetName()), wxEmptyString );
		}
		pLang->BeginCmd();
	}

    if( lstInitialStates.GetCount() > 0)
    {
        m_lstProcessedElements.Clear();

        wxSFShapeBase *pHistory, *pTarget, *pInitial = lstInitialStates.Item(0)->GetData();
		
        // declare state variable
        pLang->SingleLineCommentCmd(wxT("set initial state"));
        //pLang->VariableDeclAssignCmd(wxT("STATE_T"), wxT("state"), wxString::Format(wxT("%d"), ((udDiagElementItem*)pInitial->GetUserData())->GetElementId()));
		if( fNonBlocking )
			pLang->VariableDeclAssignCmd(wxT("static STATE_T"), wxT("state"), m_pParentGenerator->MakeIDName(pInitial));
		else
			pLang->VariableDeclAssignCmd(wxT("STATE_T"), wxT("state"), m_pParentGenerator->MakeIDName(pInitial));
		
		// declare all history states and set history variables to proper values
		if( src->IsKindOf( CLASSINFO(udHStateChartDiagramItem) ) )
		{
			ShapeList lstHistoryStates, lstOutTrans;
			pDiagManager->GetShapes( CLASSINFO( umlHistoryItem ), lstHistoryStates );
			
			if( !lstHistoryStates.IsEmpty() ) pLang->SingleLineCommentCmd(wxT("set history states"));
			
			ShapeList::compatibility_iterator node = lstHistoryStates.GetFirst();
			while( node )
			{
				// find first processed state in a history level
				pHistory = node->GetData();
				
				lstOutTrans.Clear();
				pDiagManager->GetNeighbours( pHistory, lstOutTrans, CLASSINFO( umlTransitionItem ),  wxSFShapeBase::lineSTARTING, sfDIRECT );
				// there can be only one outcomming transition in hierarchical state with history
				if( !lstOutTrans.IsEmpty() )
				{
					pTarget = lstOutTrans.GetFirst()->GetData();
					if( fNonBlocking )
						pLang->VariableDeclAssignCmd( wxT("static STATE_T"), pLang->MakeValidIdentifier( udLABEL::GetContent( pHistory, udLABEL::ltTITLE ) ).Lower(), m_pParentGenerator->MakeIDName(pTarget) );
					else
						pLang->VariableDeclAssignCmd( wxT("STATE_T"), pLang->MakeValidIdentifier( udLABEL::GetContent( pHistory, udLABEL::ltTITLE ) ).Lower(), m_pParentGenerator->MakeIDName(pTarget) );
				}
				
				node = node->GetNext();
			}
		}
		
        pLang->NewLine();
        // create infinite loop
		if( !fNonBlocking )
		{
			pLang->InfiniteLoopCmd();
			pLang->BeginCmd();
		}
		// try to generate input action if set
		udFunctionItem *pInputAction = (udFunctionItem*) IPluginManager::Get()->GetProject()->GetProjectItem( CLASSINFO(udFunctionItem), pSCH->GetInputAction() );
		if( pInputAction )
		{
			pLang->SingleLineCommentCmd( wxT("Input action") );
			if( !pInputAction->IsInline() )  pLang->WriteCodeBlocks( pInputAction->ToString( udCodeItem::cfCALL, pLang ) );
			else
			{
				pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pInputAction ) );
				pLang->WriteCodeBlocks( pInputAction->GetCode() );
				pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pInputAction ) );
			}
			pLang->SingleLineCommentCmd( wxT("State machine") );
		}

        // process diagram items (only one initial state is assumed)
        ProcessState(pInitial);

		if( !fNonBlocking ) pLang->EndCmd();
		/*else if( !pSCH->IsInline() && fHasFinalState )
		{
			pLang->NewLine();
			pLang->ReturnCmd( wxT("state") );
		}*/
    }

    //pLang->ReturnCmd(wxT("(STATE_T)") + pLang->NullValue());

   if( !pSCH->IsInline() )pLang->EndCmd();
}

void udElifAlgorithm::ProcessState(wxSFShapeBase *state)
{
    wxASSERT(state);
    if(!state)return;

    // check whether the state is already processed
    if( m_lstProcessedElements.IndexOf(state) != wxNOT_FOUND )return;

    wxSFDiagramManager *pDiagManager = state->GetShapeManager();
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    // find state neighbours
    ShapeList lstNeighbours;
    pDiagManager->GetNeighbours(state, lstNeighbours, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, sfDIRECT);
    if( !lstNeighbours.IsEmpty() && ( m_lstProcessedElements.IndexOf(lstNeighbours.GetFirst()->GetData()) == wxNOT_FOUND ) )
    {
        m_pNextElement = lstNeighbours.GetFirst()->GetData();
    }
    else
        m_pNextElement = NULL;

	pLang->SingleLineCommentCmd(wxT("State ID: ") + m_pParentGenerator->MakeIDName(state));

    // process given element
    udElementProcessor *pProcessor = GetElementProcessor(state->GetClassInfo()->GetClassName());
    if(pProcessor)
    {
        pProcessor->ProcessElement(state);
    }
    else
    {
        pLang->SingleLineCommentCmd(wxString::Format(wxT( "!!! WARNING: UNSUPPORTED ELEMENT ('%s') !!!"), ((udProjectItem*)state->GetUserData())->GetName().c_str()));
        IPluginManager::Get()->Log(wxString::Format(wxT("WARNING: '%s' element is not supported by this algorithm."), ((udProjectItem*)state->GetUserData())->GetName().c_str()));
    }

    // set the state as processes
    m_lstProcessedElements.Append(state);
    m_pPrevElement = state;

    // process connected states
	ShapeList::compatibility_iterator node = lstNeighbours.GetFirst();
    while(node)
    {
        ProcessState(node->GetData());
        node = node->GetNext();
    }
}


