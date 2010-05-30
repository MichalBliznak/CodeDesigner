#include "CPPElementProcessors.h"
#include "ClassAlgorithm.h"

/////////////////////////////////////////////////////////////////////////////////////
// udCPPClassElementProcessor class /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udCPPClassElementProcessor, udElementProcessor);

udCPPClassElementProcessor::udCPPClassElementProcessor()
{
    m_pParentGenerator = NULL;
}

udCPPClassElementProcessor::udCPPClassElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udCPPClassElementProcessor::~udCPPClassElementProcessor()
{
}

void udCPPClassElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	switch( pAlg->GetGenMode() )
	{
		case udGenerator::genDECLARATION:
			ProcessClassDeclaration( element );
			break;
			
		case udGenerator::genDEFINITION:
			ProcessClassDefinition( element );
			break;
			
		default:
			break;
	}
}

void udCPPClassElementProcessor::ProcessClassDeclaration(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	//udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	// get base classes if exists
	ShapeList lstBases;
	umlClassDiagram::GetBaseClasses( (umlClassItem*)element, lstBases );
	
	wxString sBases;
	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		if( it != lstBases.begin() ) sBases << wxT(", ");
		sBases << pLang->MakeValidIdentifier( udPROJECT::GetDiagramElement(*it)->GetName() );
	}
	
	udClassElementItem *pClass = (udClassElementItem*)udPROJECT::GetDiagramElement(element);
	
	// write template definition if needed
	if( pClass->GetIsTemplate() )
	{
		pLang->WriteCodeBlocks( wxT("template<typename ") + pClass->GetTemplateName() + wxT(">") );
	}
	
	pLang->ClassDeclCmd( pLang->MakeValidIdentifier( pClass->GetName() ), sBases );
	
	pLang->BeginCmd();
	
	// declare class members
	int nAccessType = 0;
	wxClassInfo *pPrevType;
	
	SerializableList lstMembers;
	
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
		pLang->WriteCodeBlocks( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(":") );
		pLang->IncIndentation();
		
		lstMembers.Clear();
		pPrevType = NULL;
		
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberDataLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberFunctionLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
		{
			if( pPrevType && ((*it)->GetClassInfo() != pPrevType) ) pLang->NewLine();
			
			pLang->WriteCodeBlocks( ((udCodeLinkItem*)*it)->ToString( udCodeItem::cfDECLARATION, pLang ) );
			
			pPrevType = (*it)->GetClassInfo();
		}
		
		nAccessType++;
		
		pLang->DecIndentation();
		pLang->NewLine();
	}
	
	// insert class ending with delimiter
	pLang->PushCode();
	pLang->EndCmd();
	wxString sEnding = pLang->GetCodeBuffer().Trim() + pLang->Delimiter();
	pLang->PopCode();
	
	pLang->WriteCodeBlocks( sEnding );
	
	pLang->NewLine();	
}


void udCPPClassElementProcessor::ProcessClassDefinition(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	udClassElementItem *pClass = (udClassElementItem*)udPROJECT::GetDiagramElement(element);
	
	int nAccessType = 0;
	wxClassInfo *pPrevType;
	udFunctionItem *pFcn;
	
	SerializableList lstMembers;
	
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
		lstMembers.Clear();
		pPrevType = NULL;
		
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberFunctionLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		
		if( !lstMembers.IsEmpty() )
		{
			pLang->SingleLineCommentCmd( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(" function members of '") + udPROJECT::GetDiagramElement(element)->GetName() + wxT("' class") );
		}
		
		for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
		{
			pFcn = (udFunctionItem*)((udCodeLinkItem*)*it)->GetOriginal();
			
			// generate non-abstract functions only
			if( pFcn->GetFunctionModifer() == udLanguage::FM_ABSTRACT ) continue;
			
			// write template definition if needed
			if( pClass->GetIsTemplate() )
			{
				pLang->WriteCodeBlocks( wxT("template<typename ") + pClass->GetTemplateName() + wxT(">") );
			}
			
			if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
			{
				pLang->WriteCodeBlocks( pFcn->ToString( udCodeItem::cfDEFINITION, pLang ) );
				pLang->BeginCmd();
				
				if( pFcn->IsKindOf( CLASSINFO(udConstructorFunctionItem) ) ) ProcessClassMembers( element );
				
				if( pFcn->GetCode().IsEmpty() ) pLang->WriteCodeBlocks( pLang->Dummy() );
				else
				{
					// insert code marks here needed for code synchronization
					pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pFcn ) );
						
					pLang->WriteCodeBlocks( pFcn->GetCode() );
					
					pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pFcn ) );
					
				}
					
				pLang->EndCmd();
				pLang->NewLine();
			}
			
			pPrevType = (*it)->GetClassInfo();
		}
		
		nAccessType++;
	}
}

void udCPPClassElementProcessor::ProcessClassMembers(wxSFShapeBase* element)
{
	SerializableList lstMembers;
	umlClassDiagram::GetClassMembers( (umlClassItem*)element, CLASSINFO(udMemberDataLinkItem), (udLanguage::ACCESSTYPE)-1, lstMembers );
	
	if( !lstMembers.IsEmpty() )
	{
		udMemberDataItem *pVar;
		udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
		
		pLang->SingleLineCommentCmd( wxT("member data initialization") );
		
		for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
		{
			pVar = (udMemberDataItem*)((udMemberDataLinkItem*)*it)->GetOriginal();
			if( !pVar->GetValue().IsEmpty() ) pLang->WriteCodeBlocks( pVar->ToString( udCodeItem::cfDEFINITION, pLang ) );
		}
		
		pLang->NewLine();
	}
}
