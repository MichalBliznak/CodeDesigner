#include "GoToAlgorithm.h"
#include "StateChartGenerator.h"
#include "GTElementProcessors.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udGOTOAlgorithm, udAlgorithm);

udGOTOAlgorithm::udGOTOAlgorithm()
{
    // initialize element processors
    m_mapElementProcessors[wxT("umlSimpleStateItem")] = new udGTSimpleStateProcessor();
    m_mapElementProcessors[wxT("umlSubStateItem")] = new udGTSubStateProcessor();
    m_mapElementProcessors[wxT("umlInitialItem")] = new udGTSimpleStateProcessor();
    m_mapElementProcessors[wxT("umlFinalItem")] = new udGTFinalItemProcessor();
	
    m_mapElementProcessors[wxT("umlCompStateItem")] = new udGTSimpleStateProcessor();
    m_mapElementProcessors[wxT("umlDecisionItem")] = new udGTSimpleStateProcessor();
    m_mapElementProcessors[wxT("umlHistoryItem")] = new udGTHistoryProcessor();
    m_mapElementProcessors[wxT("umlEntryItem")] = new udGTSimpleStateProcessor();
    m_mapElementProcessors[wxT("umlExitItem")] = new udGTFinalItemProcessor();

    m_sName = wxT("GOTO algorithm");

    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udGOTOAlgorithm::udGOTOAlgorithm(udGenerator *parent) : udAlgorithm(parent)
{
    // initialize element processors
    m_mapElementProcessors[wxT("umlSimpleStateItem")] = new udGTSimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlSubStateItem")] = new udGTSubStateProcessor(parent);
    m_mapElementProcessors[wxT("umlInitialItem")] = new udGTSimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlFinalItem")] = new udGTFinalItemProcessor(parent);
	
    m_mapElementProcessors[wxT("umlCompStateItem")] = new udGTSimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlDecisionItem")] = new udGTSimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlHistoryItem")] = new udGTHistoryProcessor(parent);
    m_mapElementProcessors[wxT("umlEntryItem")] = new udGTSimpleStateProcessor(parent);
    m_mapElementProcessors[wxT("umlExitItem")] = new udGTFinalItemProcessor(parent);

    m_sName = wxT("GOTO algorithm");

    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udGOTOAlgorithm::~udGOTOAlgorithm()
{
}

bool udGOTOAlgorithm::Initialize()
{
    m_pPrevElement = NULL;
    m_pNextElement = NULL;

    return true;
}

void udGOTOAlgorithm::ProcessAlgorithm(udDiagramItem *src)
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
			if( pDiagManager->Contains(CLASSINFO(umlFinalItem)) )
				pLang->FunctionDefCmd(wxT("STATE_T"), m_pParentGenerator->MakeValidIdentifier(pSCH->GetName()), wxEmptyString );
			else
				pLang->FunctionDefCmd(pLang->GetDataTypeString(udLanguage::DT_VOID), m_pParentGenerator->MakeValidIdentifier(pSCH->GetName()), wxEmptyString );
		}
		pLang->BeginCmd();
	}

    if( !lstInitialStates.IsEmpty() )
    {
        m_lstProcessedElements.Clear();
		
		// declare all history states and set history variables to proper values
		if( pSCH->IsKindOf( CLASSINFO(udHStateChartDiagramItem) ) )
		{
			wxSFShapeBase *pHistory, *pTarget;
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
				
					pLang->VariableDeclAssignCmd( wxT("STATE_T"), pLang->MakeValidIdentifier( udLABEL::GetContent( pHistory, udLABEL::ltTITLE ) ).Lower(), m_pParentGenerator->MakeIDName(pTarget) );
				}
				
				node = node->GetNext();
			}
		}
		pLang->NewLine();

        wxSFShapeBase *pInitial = lstInitialStates.GetFirst()->GetData();

         // process diagram items (only one initial state is assumed)
        ProcessState(pInitial);
    }

	if( !pSCH->IsInline() )pLang->EndCmd();
}

void udGOTOAlgorithm::ProcessState(wxSFShapeBase *state)
{
    wxASSERT(state);
    if(!state)return;

    // check whether the state is already processed
    if( m_lstProcessedElements.IndexOf(state) != wxNOT_FOUND )return;

    wxSFDiagramManager *pDiagManager = state->GetShapeManager();
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    // find state neighbours	
	ShapeList lstTransitions;
    pDiagManager->GetAssignedConnections(state, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

	// sort transitions
	((udStateChartGenerator*)m_pParentGenerator)->SortTransitions(lstTransitions, sortASC);
	
	// find next processed state
	m_pNextElement = NULL;
	
    if( !lstTransitions.IsEmpty() )
    {
		// 
		wxSFShapeBase *pNext;
		ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
		while( node )
		{
			pNext = pDiagManager->FindShape( ((umlTransitionItem*)node->GetData())->GetTrgShapeId() );
			if( m_lstProcessedElements.IndexOf( pNext ) == wxNOT_FOUND && pNext != state )
			{
				m_pNextElement = pNext;
				break;
			}
			node = node->GetNext();
		}
    }        

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
    ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
    while(node)
    {
        ProcessState( pDiagManager->FindShape( ((umlTransitionItem*)node->GetData())->GetTrgShapeId() ) );
        node = node->GetNext();
    }
}


