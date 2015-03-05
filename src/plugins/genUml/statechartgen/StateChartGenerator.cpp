#include "StateChartGenerator.h"
#include "StateChartVerifier.h"
#include "StateChartOptimizer.h"
#include "LoopCaseAlgorithm.h"
#include "../../diagUml/DiagUml.h"

#include <wx/txtstrm.h>

IMPLEMENT_DYNAMIC_CLASS(udStateChartGenerator, udGenerator);

// static functions ////////////////////////////////////////////////////////////////////////////////////////

int SortByPriorityDesc(const wxSFShapeBase **t1, const wxSFShapeBase **t2)
{
	wxSFShapeBase *pTrans1 = *(wxSFShapeBase**)t1;
	wxSFShapeBase *pTrans2 = *(wxSFShapeBase**)t2;
	
	udTransElementItem *pElement1 = wxDynamicCast( pTrans1->GetUserData(), udTransElementItem );
	udTransElementItem *pElement2 = wxDynamicCast( pTrans2->GetUserData(), udTransElementItem );
	
	if( pElement1 && pElement2 )
	{
		if( !pElement1->HasCondition() && pElement2->HasCondition() ) return 1;
		else if( !pElement2->HasCondition() && pElement1->HasCondition() ) return -1;
		//else if( !pElement2->HasCondition() && !pElement1->HasCondition() ) return 0;
		else return pElement1->GetPriority() - pElement2->GetPriority();
	}
	else
		return 0;
}

int SortByPriorityAsc(const wxSFShapeBase **t1, const wxSFShapeBase **t2)
{
	wxSFShapeBase *pTrans1 = *(wxSFShapeBase**)t1;
	wxSFShapeBase *pTrans2 = *(wxSFShapeBase**)t2;
	
	udTransElementItem *pElement1 = wxDynamicCast( pTrans1->GetUserData(), udTransElementItem );
	udTransElementItem *pElement2 = wxDynamicCast( pTrans2->GetUserData(), udTransElementItem );
	
	if( pElement1 && pElement2 )
	{
		if( !pElement1->HasCondition() && pElement2->HasCondition() ) return -1;
		else if( !pElement2->HasCondition() && pElement1->HasCondition() ) return 1;
		//else if( !pElement2->HasCondition() && !pElement1->HasCondition() ) return 0;
		else return pElement2->GetPriority() - pElement1->GetPriority();
	}
	else
		return 0;
}

// constructor and destructor///////////////////////////////////////////////////////////////////////////////

udStateChartGenerator::udStateChartGenerator()
{
}

udStateChartGenerator::~udStateChartGenerator()
{
    udGenerator::CleanUp();
}

// protected virtual functions /////////////////////////////////////////////////////////////////////////////

bool udStateChartGenerator::Initialize()
{
	// initialize verifier
	m_pVerifier = new udStateChartVerifier(this);

	// initialize optimizer
	m_pOptimizer = new udStateChartOptimizer(this);

    return udGenerator::Initialize();
}

bool udStateChartGenerator::ProcessDiagram(udDiagramItem *src)
{		
	switch( m_nMode )
	{
		case genCOMMON_DECLARATION:
			return GenerateCommonDeclaration();
			
		case genCOMMON_DEFINITION:
			return GenerateCommonDefinition();
			
		case genDECLARATION:
			return GenerateDeclaration( src );
			
		case genDEFINITION:
			return GenerateDefinition( src );
			
		default:
			IPluginManager::Get()->Log( wxT("ERROR: No valid generation target has been specified.") );
			return false;
	}
}

void udStateChartGenerator::CleanUp()
{
	delete m_pVerifier;
	delete m_pOptimizer;
}

void udStateChartGenerator::SortTransitions(ShapeList &transitions, bool desc)
{
	if( desc ) transitions.Sort( SortByPriorityDesc );
	else
		 transitions.Sort( SortByPriorityAsc );
}

// protected functions /////////////////////////////////////////////////////////////////////////////////////

bool udStateChartGenerator::GenerateCommonDeclaration()
{	
	udCodeItem *pCodeItem;
	
	// initialize output stream
    wxTextOutputStream textOut(*m_pOut);
	
	// define STATE_T type
	m_pOutLang->SingleLineCommentCmd( wxT("State ID data type") );
	m_pOutLang->TypedefCmd( wxT("STATE_T"), m_pOutLang->GetDataTypeString(udLanguage::DT_UINT32) );
	m_pOutLang->NewLine();
	
	// create declarations of non-inlined conditions and functions
	m_pOutLang->SingleLineCommentCmd( wxT("Declaration of code items used in state charts") );
	
	SerializableList lstCodeItems;
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udActionItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udConditionItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udEventItem), lstCodeItems );
	
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udCodeItem*) node->GetData();
		
		if( !pCodeItem->IsInline() ) 
		{
			if( pCodeItem->IsKindOf(CLASSINFO(udVariableItem)) )
			{
				m_pOutLang->WriteCodeBlocks( pCodeItem->ToString( udCodeItem::cfDECLARATION, m_pOutLang) );
			}
			else if( pCodeItem->IsKindOf(CLASSINFO(udFunctionItem)) )
			{
				udFunctionItem *pFcn = (udFunctionItem*) pCodeItem;
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					// generate comment if exists
					m_pOutLang->WriteCodeBlocks( GetComment( pFcn, m_pOutLang ) );
					// generate function decl
					m_pOutLang->WriteCodeBlocks( pCodeItem->ToString( udCodeItem::cfDECLARATION, m_pOutLang) );
				}
			}
		}
			
		node = node->GetNext();
	}
	
	textOut << m_pOutLang->GetCodeBuffer();
	
	return true;
}

bool udStateChartGenerator::GenerateCommonDefinition()
{	
	udCodeItem *pCodeItem;
	
	// initialize output stream
    wxTextOutputStream textOut(*m_pOut);
	
	// create declarations of non-inlined functions
	m_pOutLang->SingleLineCommentCmd( wxT("Code items' definitions") );
	
	SerializableList lstCodeItems;
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udActionItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udConditionItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udEventItem), lstCodeItems );
	
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udCodeItem*) node->GetData();

		if( !pCodeItem->IsInline() )
		{
			if( pCodeItem->IsKindOf(CLASSINFO(udVariableItem)) )
			{
				m_pOutLang->WriteCodeBlocks( pCodeItem->ToString( udCodeItem::cfDEFINITION, m_pOutLang) );
			}
			else if( pCodeItem->IsKindOf(CLASSINFO(udFunctionItem)) )
			{
				udFunctionItem *pFcn = (udFunctionItem*) pCodeItem;
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					m_pOutLang->WriteCodeBlocks( pCodeItem->ToString( udCodeItem::cfDEFINITION, m_pOutLang) );
					m_pOutLang->BeginCmd();
					/*if( pCodeItem->GetCode().IsEmpty() ) m_pOutLang->WriteCodeBlocks( m_pOutLang->Dummy() );
					else
					{*/
						// insert code marks here needed for code synchronization
						m_pOutLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pCodeItem ) );
						// insert user-defined code
						m_pOutLang->WriteCodeBlocks( pCodeItem->GetCode() );
						
						m_pOutLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pCodeItem ) );
					/*}*/
					m_pOutLang->EndCmd();
				}
			}
		}
		
		node = node->GetNext();
	}
	
	textOut << m_pOutLang->GetCodeBuffer();
	
	return true;
}

bool udStateChartGenerator::GenerateDeclaration(udDiagramItem* src)
{	
	udSStateChartDiagramItem *pSCH = wxDynamicCast( src, udSStateChartDiagramItem );
	if( pSCH )
	{
		// initialize output stream
		wxTextOutputStream textOut(*m_pOut);
		
		// generate IDs (if suitable)
		if( m_pOutLang->HasSeparatedDecl() ) GenerateIDs( pSCH );
		
		if( !pSCH->IsInline() )
		{
			udFunctionItem *pFcn = IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( pSCH );
			if( pFcn )
			{
				// class member functions are declared at other place (in the class declaration)
				if( !pFcn->IsKindOf(CLASSINFO(udMemberFunctionItem)) || !m_pOutLang->HasSeparatedDecl() )
				{
					// generate comment if exists
					m_pOutLang->WriteCodeBlocks( GetComment( pFcn, m_pOutLang ) );
					// generate function decl
					m_pOutLang->WriteCodeBlocks( pFcn->ToString( udCodeItem::cfDECLARATION, m_pOutLang) );
				}
			}
			else
			{
				if( pSCH->GetDiagramManager().Contains(CLASSINFO(umlFinalItem)) )
					m_pOutLang->FunctionDeclCmd(wxT("STATE_T"), m_pOutLang->MakeValidIdentifier( pSCH->GetName() ), wxEmptyString );
				else
					m_pOutLang->FunctionDeclCmd(m_pOutLang->GetDataTypeString(udLanguage::DT_VOID), m_pOutLang->MakeValidIdentifier( pSCH->GetName() ), wxEmptyString );
			}
		}
			
		textOut << m_pOutLang->GetCodeBuffer();		
	}
	
	return true;
}

bool udStateChartGenerator::GenerateDefinition(udDiagramItem* src)
{
	// initialize output stream
	wxTextOutputStream textOut(*m_pOut);

	if( m_fRecursive )
	{
		// find substates if exist
		udSubDiagramElementItem *pSubElement;
		ShapeList lstSubStates;
		src->GetDiagramManager().GetShapes(CLASSINFO(umlSubStateItem), lstSubStates);
			
		// generate all substate machines recursively
		ShapeList::compatibility_iterator node = lstSubStates.GetFirst();
		while(node)
		{
			pSubElement = (udSubDiagramElementItem*) udPROJECT::GetDiagramElement( node->GetData(), udfOMIT_LINKS );
			if(pSubElement)
			{
				if( !_Generate(pSubElement->GetSubDiagram()) )
				{
					textOut << wxT("");
					return false;
				}
				else
					textOut << ENDL;
			}
			node = node->GetNext();
		}
	}

	// clear output language processor's buffer
	m_pOutLang->ClearCodeBuffer();
	
	// generate IDs (if suitable)
	if( !m_pOutLang->HasSeparatedDecl() ) GenerateIDs( src );

	// initialize algorithm and process digram
	if( src->GetActiveAlgorithm() != wxT("<default>") )
	{
		SetActiveAlgorithm( GetAlgorithms()[src->GetActiveAlgorithm()] );
		if(m_pAlgorithm)
		{
			if(!m_pAlgorithm->GetParentGenerator()) m_pAlgorithm->SetParentGenerator(this);
		}
		else
		{
			IPluginManager::Get()->Log( wxT("ERROR: Unable to set '") + src->GetActiveAlgorithm() + wxT("' algorithm in '") + src->GetName() + wxT("' diagram.") );
			return false;
		}
	}
	
	m_pAlgorithm->Process(src);

	// write generated code to the output stream
	textOut << m_pOutLang->GetCodeBuffer();

	return true;
}

void udStateChartGenerator::GenerateIDs(udDiagramItem *src)
{
	ShapeList lstElements;
	udProjectItem *pElement;
	
	// create identifiers
	if( src )
	{
		m_pOutLang->SingleLineCommentCmd( wxT("State IDs") );
	
		src->GetDiagramManager().GetShapes( CLASSINFO(umlInitialItem), lstElements );
		src->GetDiagramManager().GetShapes( CLASSINFO(umlHistoryItem), lstElements  );
		src->GetDiagramManager().GetShapes( CLASSINFO(umlFinalItem), lstElements  );
		src->GetDiagramManager().GetShapes( CLASSINFO(umlSimpleStateItem), lstElements  );
		src->GetDiagramManager().GetShapes( CLASSINFO(umlSubStateItem), lstElements  );
		src->GetDiagramManager().GetShapes( CLASSINFO(umlDecisionItem), lstElements  );
		
		ShapeList::compatibility_iterator node = lstElements.GetFirst();
		while( node )
		{
			pElement = (udProjectItem*) node->GetData()->GetUserData();
			m_pOutLang->DefineCmd( pElement->GetUniqueId( m_pOutLang ), wxString::Format( wxT("%d"), m_nIDCounter++ ) );
			node = node->GetNext();
		}
	}
	
	m_pOutLang->NewLine();
}

