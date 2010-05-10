#include "PythonElementProcessors.h"
#include "ClassAlgorithm.h"

/////////////////////////////////////////////////////////////////////////////////////
// udPythonClassElementProcessor class //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udPythonClassElementProcessor, udElementProcessor);

udPythonClassElementProcessor::udPythonClassElementProcessor()
{
    m_pParentGenerator = NULL;
}

udPythonClassElementProcessor::udPythonClassElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udPythonClassElementProcessor::~udPythonClassElementProcessor()
{
}

void udPythonClassElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;

	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	switch( pAlg->GetGenMode() )
	{
		case udGenerator::genDEFINITION:
			ProcessClassDefinition( element );
			break;
			
		default:
			break;
	}
}

void udPythonClassElementProcessor::ProcessClassDefinition(wxSFShapeBase* element)
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
	
	pLang->ClassDeclCmd( pLang->MakeValidIdentifier( udPROJECT::GetDiagramElement(element)->GetName() ), sBases );
	
	pLang->BeginCmd();
	
	int nAccessType = 0;
	wxClassInfo *pPrevType;
	udVariableItem *pVar;
	udFunctionItem *pFcn;
	wxString sOut;
	
	SerializableList lstMembers;
	
	// declare class data members
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
		lstMembers.Clear();
		pPrevType = NULL;
		
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberDataLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		
		if( !lstMembers.IsEmpty() )
		{
			pLang->SingleLineCommentCmd( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(" data members:") );
			
			for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
			{
				if( pPrevType && ((*it)->GetClassInfo() != pPrevType) ) pLang->NewLine();
				
				pVar = (udVariableItem*)((udCodeLinkItem*)*it)->GetOriginal();
				
				sOut = pVar->ToString( udCodeItem::cfDECLARATION, pLang );
				if( nAccessType != udLanguage::AT_PUBLIC ) sOut.Replace( pLang->MakeValidIdentifier(pVar->GetName()), wxT("__") + pLang->MakeValidIdentifier(pVar->GetName()) );
				if( pVar->GetDataModifer() != udLanguage::DM_STATIC ) sOut = wxT("self.") + sOut;
				
				pLang->WriteCodeBlocks( sOut );
			
				pPrevType = (*it)->GetClassInfo();
			}
			pLang->NewLine();
		}
		
		nAccessType++;
	}
	
	// declare class functions members
	 nAccessType = 0;
	 
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{		
		lstMembers.Clear();
		pPrevType = NULL;
		
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberFunctionLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		
		if( !lstMembers.IsEmpty() )
		{
			pLang->SingleLineCommentCmd( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(" function members:") );
		
			for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
			{
				if( pPrevType && ((*it)->GetClassInfo() != pPrevType) ) pLang->NewLine();
				
				pFcn = (udFunctionItem*)((udCodeLinkItem*)*it)->GetOriginal();
				
				sOut = pFcn->ToString( udCodeItem::cfDECLARATION, pLang );
				if( nAccessType != udLanguage::AT_PUBLIC ) sOut.Replace( pLang->MakeValidIdentifier(pFcn->GetName()), wxT("__") + pLang->MakeValidIdentifier(pFcn->GetName()) );
				
				pLang->WriteCodeBlocks( sOut );
				pLang->BeginCmd();
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					if( pFcn->GetCode().IsEmpty() ) pLang->WriteCodeBlocks( pLang->Dummy() );
					else
					{
						pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pFcn ) );
						
						pLang->WriteCodeBlocks( pFcn->GetCode() );
						
						pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pFcn ) );
					}
				}
				else
					pLang->WriteCodeBlocks( pFcn->ToString( udCodeItem::cfCALL, pLang) );
				pLang->EndCmd();
			
				pPrevType = (*it)->GetClassInfo();
			}
			pLang->NewLine();
		}
		
		nAccessType++;
	}
	
	// insert class ending with delimiter
	pLang->EndCmd();
	
	pLang->NewLine();	
}
