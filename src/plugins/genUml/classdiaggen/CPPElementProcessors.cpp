#include "CPPElementProcessors.h"
#include "ClassAlgorithm.h"
#include "../../diagUml/DiagUml.h"

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
    if(!m_pParentGenerator) return;
	
	wxASSERT(element);
	if(!element) return;
	
	udClassElementItem *pClass = (udClassElementItem*) udPROJECT::GetDiagramElement( element, udfOMIT_LINKS );
	if( !pClass || !pClass->IsGenerated() ) return;
	
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	// check whether the class is already processed
    if( pAlg->GetProcessedElements().IndexOf(element) != wxNOT_FOUND ) return;
	
	// process child classes recursivelly first
	ShapeList lstBases;
	umlClassDiagram::GetOuterClasses( (umlClassItem*)element, lstBases );

	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		ProcessElement( *it );
	}

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
	
	// process template bindings
	ShapeList lstConnections;
	element->GetShapeManager()->GetAssignedConnections( element, CLASSINFO(umlTemplateBindItem), wxSFShapeBase::lineSTARTING, lstConnections );
	
	for( ShapeList::iterator it = lstConnections.begin(); it != lstConnections.end(); ++it )
	{
		udElementProcessor *pProcessor = pAlg->GetElementProcessor((*it)->GetClassInfo()->GetClassName());
		if(pProcessor)
		{
			pProcessor->ProcessElement(*it);
		}
	}

    // set the state as processes
	pAlg->GetProcessedElements().Append(element);
}

void udCPPClassElementProcessor::ProcessClassDeclaration(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	// get base classes if exists
	ShapeList lstBases;
	umlClassDiagram::GetBaseClasses( (umlClassItem*)element, lstBases );
	
	int nTemplateIndex = 0;
	
	wxString sBases;
	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		if( it != lstBases.begin() ) sBases << wxT(", ");
		
		sBases << pLang->MakeValidIdentifier( udPROJECT::GetDiagramElement(*it)->GetName() );
		
		// add template parameter if exists
		umlClassTemplateItem *pTemplate = wxDynamicCast( *it, umlClassTemplateItem );
		if( pTemplate )
		{
			// find corespondent template binding connection
			ShapeList lstConnections;
			element->GetShapeManager()->GetAssignedConnections( element, CLASSINFO(umlTemplateBindItem), wxSFShapeBase::lineSTARTING, lstConnections );
			if( !lstConnections.IsEmpty() )
			{
				// append bind type to the base name
				udTemplateBindElementItem *pBindElement = wxDynamicCast( udPROJECT::GetDiagramElement( lstConnections.Item(nTemplateIndex)->GetData() ), udTemplateBindElementItem );
				if( pBindElement )
				{
					sBases << wxT("<") << pBindElement->GetBindType() << wxT(">");
				}
			}
			nTemplateIndex++;
		}
	}
	
	udClassElementItem *pClass = (udClassElementItem*) udPROJECT::GetDiagramElement(element);
	
	//generate comment if requested
	pLang->WriteCodeBlocks( udGenerator::GetComment( pClass, pLang) );
	
	// write template definition if needed
	udClassTemplateElementItem *pClassTempl = wxDynamicCast( pClass, udClassTemplateElementItem );
	if( pClassTempl )
	{
		pLang->WriteCodeBlocks( wxT("template <typename ") + pClassTempl->GetTemplateName() + wxT(">") );
	}
	
	// generate class declaration
	pLang->ClassDeclCmd( pLang->MakeValidIdentifier( pClass->GetName() ), sBases );
	
	pLang->BeginCmd();
	
	// declare class members
	int nAccessType = 0;
	wxClassInfo *pPrevType;
	
	SerializableList lstMembers;
	ShapeList lstAssocs;
	
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
		pLang->WriteCodeBlocks( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(":") );
		pLang->IncIndentation();
		
		lstMembers.Clear();
		lstAssocs.Clear();
		pPrevType = NULL;
		
		// process associations
		umlClassDiagram::GetClassAssociations( (umlClassItem*) element, CLASSINFO(wxSFLineShape), wxSFLineShape::lineSTARTING, (udLanguage::ACCESSTYPE) nAccessType, lstAssocs );
		for( ShapeList::iterator it = lstAssocs.begin(); it != lstAssocs.end(); ++it )
		{
			udElementProcessor *pProcessor = pAlg->GetElementProcessor( (*it)->GetClassInfo()->GetClassName() );
			if( pProcessor ) pProcessor->ProcessElement( *it );
		}
		
		// process class members
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberDataLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberFunctionLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
		{
			if( pPrevType && ((*it)->GetClassInfo() != pPrevType) ) pLang->NewLine();
			
			// generate comment
			pLang->WriteCodeBlocks( udGenerator::GetComment( ((udCodeLinkItem*)*it)->GetOriginal(), pLang ) );
			// generate function decl
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
	
	int nAccessType = 0;
	udFunctionItem *pFcn;
	
	SerializableList lstMembers;
	
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
		lstMembers.Clear();
		
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
			udClassTemplateElementItem *pClassTempl = wxDynamicCast( udPROJECT::GetDiagramElement(element), udClassTemplateElementItem );
			if( pClassTempl )
			{
				pLang->WriteCodeBlocks( wxT("template <typename ") + pClassTempl->GetTemplateName() + wxT(">") );
			}
			
			if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
			{
				pLang->WriteCodeBlocks( pFcn->ToString( udCodeItem::cfDEFINITION, pLang ) );
				pLang->BeginCmd();
				
				if( pFcn->IsKindOf( CLASSINFO(udConstructorFunctionItem) ) ) ProcessClassMembers( element );
				
				/*if( pFcn->GetCode().IsEmpty() ) pLang->WriteCodeBlocks( pLang->Dummy() );
				else
				{*/
					// insert code marks here needed for code synchronization
					pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pFcn ) );
						
					pLang->WriteCodeBlocks( pFcn->GetCode() );
					
					pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pFcn ) );
					
				/*}*/
					
				pLang->EndCmd();
				pLang->NewLine();
			}
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

/////////////////////////////////////////////////////////////////////////////////////
// udTemplBindElementProcessor class ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udCPPTemplBindElementProcessor, udElementProcessor);

udCPPTemplBindElementProcessor::udCPPTemplBindElementProcessor()
{
    m_pParentGenerator = NULL;
}

udCPPTemplBindElementProcessor::udCPPTemplBindElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udCPPTemplBindElementProcessor::~udCPPTemplBindElementProcessor()
{
}

void udCPPTemplBindElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	if( pAlg->GetGenMode() == udGenerator::genDEFINITION )
	{
		umlTemplateBindItem *pLine = wxDynamicCast( element, umlTemplateBindItem );
		if( pLine )
		{
			// get target class template
			umlClassTemplateItem *pTemplate = wxDynamicCast( pLine->GetShapeManager()->FindShape( pLine->GetTrgShapeId() ), umlClassTemplateItem );
			if( pTemplate )
			{
				udClassTemplateElementItem *pTemplElement = (udClassTemplateElementItem*) udPROJECT::GetDiagramElement( pTemplate );
				udTemplateBindElementItem *pBindElement = (udTemplateBindElementItem*) udPROJECT::GetDiagramElement( pLine );
				
				udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
				
				pLang->WriteCodeBlocks( wxT("template class ") +
										pLang->MakeValidIdentifier( pTemplElement->GetName() ) +
										wxT("<") +
										pBindElement->GetBindType() +
										wxT(">;") );
										
				pLang->NewLine();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udEnumElementProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udCPPEnumElementProcessor, udElementProcessor);

udCPPEnumElementProcessor::udCPPEnumElementProcessor()
{
    m_pParentGenerator = NULL;
}

udCPPEnumElementProcessor::udCPPEnumElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udCPPEnumElementProcessor::~udCPPEnumElementProcessor()
{
}

void udCPPEnumElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	/*// check whether the enum is already processed
    if( pAlg->GetProcessedElements().IndexOf(element) != wxNOT_FOUND ) return;*/
	
	if( pAlg->GetGenMode() == udGenerator::genDECLARATION )
	{
		udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
		udEnumElementItem *pEnum = (udEnumElementItem*) udPROJECT::GetDiagramElement( element, udfOMIT_LINKS );
		if( pEnum )
		{
			// get enumeration values
			wxArrayString arrValues;
			SerializableList::compatibility_iterator node = pEnum->GetFirstChildNode();
			while( node )
			{
				arrValues.Add( ((udCodeItem*)node->GetData())->ToString(udCodeItem::cfDECLARATION, pLang) );
				node = node->GetNext();
			}
			
			// write enumeration code
			//pLang->SingleLineCommentCmd( wxT("Enumeration '") + pEnum->GetName() + wxT("'") );
			
			pLang->EnumCmd( pLang->MakeValidIdentifier( pEnum->GetName() ), arrValues, pLang->MakeValidIdentifier( pEnum->GetInstanceName() ) );
			pLang->NewLine();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udIncludeAssocProcessor class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udCPPIncludeAssocProcessor, udElementProcessor);

udCPPIncludeAssocProcessor::udCPPIncludeAssocProcessor()
{
	m_pParentGenerator = NULL;
}

udCPPIncludeAssocProcessor::udCPPIncludeAssocProcessor(udGenerator* parent)
: udElementProcessor(parent)
{
}

udCPPIncludeAssocProcessor::~udCPPIncludeAssocProcessor()
{
}

void udCPPIncludeAssocProcessor::ProcessElement(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	udIncludeAssocElementItem *pAssoc = wxDynamicCast( udPROJECT::GetDiagramElement( element ), udIncludeAssocElementItem );
	
	if( pAssoc && pAssoc->GetIncludeClass() )
	{
		pLang->SingleLineCommentCmd( pAssoc->GetName() );
		
		// get target element
		wxSFLineShape *pConnection = wxDynamicCast( element, wxSFLineShape );
		if( pConnection )
		{
			wxSFShapeBase *pTrgShape = pConnection->GetShapeManager()->FindShape( pConnection->GetTrgShapeId() );
			if( pTrgShape )
			{
				udElementProcessor *pProcessor = pAlg->GetElementProcessor( pTrgShape->GetClassInfo()->GetClassName() ); 
				if( pProcessor )
				{
					pProcessor->ProcessElement( pTrgShape );
				}
			}
		}
	}
}
