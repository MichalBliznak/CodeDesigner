#include "codegen/CodeItemsGenerator.h"
#include "codegen/Language.h"
#include "ProjectBase.h"

#include <wx/txtstrm.h>
#include <wx/sstream.h>

// constructor and destructor///////////////////////////////////////////////////////////////////////////////

udCodeItemsGenerator::udCodeItemsGenerator()
{
	m_sName = wxT("Code items generator");
}

udCodeItemsGenerator::~udCodeItemsGenerator()
{
    udGenerator::CleanUp();
}

// protected virtual functions /////////////////////////////////////////////////////////////////////////////

bool udCodeItemsGenerator::Initialize()
{
    // initialize output language
    if(m_pOutLang)
    {
        m_pOutLang->ClearCodeBuffer();
        m_pOutLang->SetIndentation(0);
    }
    else
        return false;

    return udGenerator::Initialize();
}

bool udCodeItemsGenerator::ProcessDiagram(udDiagramItem *src)
{
	switch( m_nMode )
	{
		case genCOMMON_DECLARATION:
			return GenerateCommonDeclaration();
			
		case genCOMMON_DEFINITION:
			return GenerateCommonDefinition();
			
		case genDECLARATION:
		case genDEFINITION:
			return true;
			
		default:
			IPluginManager::Get()->Log( wxT("ERROR: No valid generation target has been specified.") );
			return false;
	}
}

void udCodeItemsGenerator::CleanUp()
{
	udGenerator::CleanUp();
}

// protected functions /////////////////////////////////////////////////////////////////////////////////////

bool udCodeItemsGenerator::GenerateCommonDeclaration()
{	
	wxClassInfo *pPrevType = NULL;
	udCodeItem *pCodeItem;
	wxString sOut;
	
	// initialize output stream
    wxTextOutputStream textOut(*m_pOut);
	
	// create declarations of non-inlined conditions and functions
	m_pOutLang->SingleLineCommentCmd( wxT("Generic code items' declarations") );
	
	SerializableList lstCodeItems;
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udGenericVariableItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udGenericFunctionItem), lstCodeItems );
	
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udCodeItem*) node->GetData();

		if( !pCodeItem->IsInline() )
		{
			if( pCodeItem->IsKindOf(CLASSINFO(udVariableItem)) )
			{
				sOut = pCodeItem->ToString( udCodeItem::cfDECLARATION, m_pOutLang);
				if( !sOut.IsEmpty() )
				{
					if( pPrevType && (pPrevType != pCodeItem->GetClassInfo()) ) m_pOutLang->NewLine();
					m_pOutLang->WriteCodeBlocks( sOut );
				}
			}
			else if( pCodeItem->IsKindOf(CLASSINFO(udFunctionItem)) )
			{
				udFunctionItem *pFcn = (udFunctionItem*) pCodeItem;
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					sOut = pCodeItem->ToString( udCodeItem::cfDECLARATION, m_pOutLang);
					if( !sOut.IsEmpty() )
					{
						if( pPrevType && (pPrevType != pCodeItem->GetClassInfo()) ) m_pOutLang->NewLine();
						m_pOutLang->WriteCodeBlocks( sOut );
					}
				}
			}
				
			pPrevType = pCodeItem->GetClassInfo();
		}
			
		node = node->GetNext();
	}
	
	textOut << m_pOutLang->GetCodeBuffer();
	
	return true;
}

bool udCodeItemsGenerator::GenerateCommonDefinition()
{	
	wxString sOut;
	wxClassInfo *pPrevType = NULL;
	udCodeItem *pCodeItem;
	
	// initialize output stream
    wxTextOutputStream textOut(*m_pOut);

	// create declarations of non-inlined conditions and functions
	m_pOutLang->SingleLineCommentCmd( wxT("Generic code items' definitions") );
	
	SerializableList lstCodeItems;
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udGenericVariableItem), lstCodeItems );
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udGenericFunctionItem), lstCodeItems );
	
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udCodeItem*) node->GetData();

		if( !pCodeItem->IsInline() )
		{
			if( pCodeItem->IsKindOf(CLASSINFO(udVariableItem)) )
			{
				sOut = pCodeItem->ToString( udCodeItem::cfDEFINITION, m_pOutLang);
				if( !sOut.IsEmpty() )
				{
					if( pPrevType && (pPrevType != pCodeItem->GetClassInfo()) ) m_pOutLang->NewLine();
					m_pOutLang->WriteCodeBlocks( sOut );
				}
			}
			else if( pCodeItem->IsKindOf(CLASSINFO(udFunctionItem)) )
			{
				udFunctionItem *pFcn = (udFunctionItem*) pCodeItem;
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					if( pPrevType && (pPrevType != pCodeItem->GetClassInfo()) ) m_pOutLang->NewLine();
					
					m_pOutLang->WriteCodeBlocks( pCodeItem->ToString( udCodeItem::cfDEFINITION, m_pOutLang) );
					m_pOutLang->BeginCmd();
					/*if( pCodeItem->GetCode().IsEmpty() ) m_pOutLang->WriteCodeBlocks( m_pOutLang->Dummy() );
					else
					{*/
						// insert code marks here needed for code synchronization
						m_pOutLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pCodeItem ) );
						
						m_pOutLang->WriteCodeBlocks( pCodeItem->GetCode() );
						
						m_pOutLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pCodeItem ) );
					/*}*/
					m_pOutLang->EndCmd();
				}
			}
				
			pPrevType = pCodeItem->GetClassInfo();
		}
			
		node = node->GetNext();
	}
	
	textOut << m_pOutLang->GetCodeBuffer();
	
	return true;
}


