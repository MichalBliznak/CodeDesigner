#include "PythonElementProcessors.h"
#include "ClassAlgorithm.h"

/////////////////////////////////////////////////////////////////////////////////////
// udPythonClassElementProcessor class //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udPyClassElementProcessor, udElementProcessor);

udPyClassElementProcessor::udPyClassElementProcessor()
{
    m_pParentGenerator = NULL;
}

udPyClassElementProcessor::udPyClassElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udPyClassElementProcessor::~udPyClassElementProcessor()
{
}

void udPyClassElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
    // check existing parent generator
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	wxASSERT(element);
	if(!element) return;

	udClassElementItem *pClass = (udClassElementItem*) udPROJECT::GetDiagramElement( element, udfOMIT_LINKS );
	if( !pClass || !pClass->IsGenerated() ) return;
	
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	// check whether the class is already processed
    if( pAlg->GetProcessedElements().IndexOf(element) != wxNOT_FOUND ) return;
	
	// process child classes recursivelly first
	ShapeList lstBases;
	umlClassDiagram::GetBaseClasses( (umlClassItem*)element, lstBases );

	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		ProcessElement( *it );
	}
	
	switch( pAlg->GetGenMode() )
	{
		case udGenerator::genDEFINITION:
			ProcessClassDefinition( element );
			break;
			
		default:
			break;
	}
	
	// set the state as processes
	pAlg->GetProcessedElements().Append(element);
}

void udPyClassElementProcessor::ProcessClassDefinition(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	// get base classes if exists
	ShapeList lstBases;
	umlClassDiagram::GetBaseClasses( (umlClassItem*)element, lstBases );
	
	wxString sBases;
	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		if( it != lstBases.begin() ) sBases << wxT(", ");
		sBases << pLang->MakeValidIdentifier( udPROJECT::GetDiagramElement(*it)->GetName() );
	}
	
	udClassElementItem *pClass = (udClassElementItem*) udPROJECT::GetDiagramElement(element);
	// generate class declaration
	pLang->ClassDeclCmd( pLang->MakeValidIdentifier( pClass->GetName() ), sBases );
	
	pLang->BeginCmd();
	
	//generate comment if requested
	pLang->WriteCodeBlocks( udGenerator::GetComment( pClass, pLang) );
	
	bool fPass = true;
	int nAccessType = 0;
	wxClassInfo *pPrevType;
	udVariableItem *pVar;
	udFunctionItem *pFcn;
	wxString sOut;
	
	SerializableList lstMembers;
	ShapeList lstAssocs;
	
	// declare class data members
	while( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) != wxEmptyString )
	{
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
		
		// process data members
		umlClassDiagram::GetClassMembers( (umlClassItem*) element, CLASSINFO(udMemberDataLinkItem), (udLanguage::ACCESSTYPE) nAccessType, lstMembers);
		
		if( !lstMembers.IsEmpty() )
		{
			pLang->SingleLineCommentCmd( pLang->GetAccessTypeString( (udLanguage::ACCESSTYPE) nAccessType ) + wxT(" data members:") );
			
			for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
			{
				if( pPrevType && ((*it)->GetClassInfo() != pPrevType) ) pLang->NewLine();
				
				pVar = (udVariableItem*)((udCodeLinkItem*)*it)->GetOriginal();
				
				// generate comment
				pLang->WriteCodeBlocks( udGenerator::GetComment( pVar, pLang ) );
				// generate variable
				sOut = pVar->ToString( udCodeItem::cfDECLARATION, pLang );
				if( nAccessType != udLanguage::AT_PUBLIC ) sOut.Replace( pLang->MakeValidIdentifier(pVar->GetName()), wxT("__") + pLang->MakeValidIdentifier(pVar->GetName()) );
				//if( pVar->GetDataModifer() != udLanguage::DM_STATIC ) sOut = wxT("self.") + sOut;
				
				pLang->WriteCodeBlocks( sOut );
			
				pPrevType = (*it)->GetClassInfo();
			}
			pLang->NewLine();
			
			fPass = false;
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
				
				// generate function
				sOut = pFcn->ToString( udCodeItem::cfDECLARATION, pLang );
				if( nAccessType != udLanguage::AT_PUBLIC ) sOut.Replace( pLang->MakeValidIdentifier(pFcn->GetName()), wxT("__") + pLang->MakeValidIdentifier(pFcn->GetName()) );
				
				pLang->WriteCodeBlocks( sOut );
				pLang->BeginCmd();
				// generate comment
				pLang->WriteCodeBlocks( udGenerator::GetComment( pFcn, pLang ) );
				
				if( pFcn->GetImplementation() == uddvFUNCTION_USERIMPLEMENTATION )
				{
					/*if( pFcn->GetCode().IsEmpty() ) pLang->WriteCodeBlocks( pLang->Dummy() );
					else
					{*/
						pLang->SingleLineCommentCmd( udGenerator::GetBeginCodeMark( pFcn ) );
						
						pLang->WriteCodeBlocks( pFcn->GetCode() );
						
						pLang->SingleLineCommentCmd( udGenerator::GetEndCodeMark( pFcn ) );
					/*}*/
				}
				else
					pLang->WriteCodeBlocks( pFcn->ToString( udCodeItem::cfCALL, pLang) );
				pLang->EndCmd();
			
				pPrevType = (*it)->GetClassInfo();
			}
			pLang->NewLine();
			
			fPass = false;
		}
		
		nAccessType++;
	}
	
	if( fPass ) pLang->WriteCodeBlocks( wxT("pass" ) );
	
	// insert class ending with delimiter
	pLang->EndCmd();
	
	pLang->NewLine();	
}

/////////////////////////////////////////////////////////////////////////////////////
// udPyEnumElementProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udPyEnumElementProcessor, udElementProcessor);

udPyEnumElementProcessor::udPyEnumElementProcessor()
{
    m_pParentGenerator = NULL;
}

udPyEnumElementProcessor::udPyEnumElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udPyEnumElementProcessor::~udPyEnumElementProcessor()
{
}

void udPyEnumElementProcessor::ProcessElement(wxSFShapeBase *element)
{	
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	/*// check whether the enum is already processed
    if( pAlg->GetProcessedElements().IndexOf(element) != wxNOT_FOUND ) return;*/
	
	if( pAlg->GetGenMode() == udGenerator::genDEFINITION )
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
			pLang->EnumCmd( pLang->MakeValidIdentifier( pEnum->GetName() ), arrValues, pLang->MakeValidIdentifier( pEnum->GetInstanceName() ) );
			pLang->NewLine();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udPyIncludeAssocProcessor class //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udPyIncludeAssocProcessor, udElementProcessor);

udPyIncludeAssocProcessor::udPyIncludeAssocProcessor()
{
	m_pParentGenerator = NULL;
}

udPyIncludeAssocProcessor::udPyIncludeAssocProcessor(udGenerator* parent)
: udElementProcessor(parent)
{
}

udPyIncludeAssocProcessor::~udPyIncludeAssocProcessor()
{
}

void udPyIncludeAssocProcessor::ProcessElement(wxSFShapeBase* element)
{
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	udClassAlgorithm *pAlg = (udClassAlgorithm*) m_pParentGenerator->GetActiveAlgorithm();
	
	udProjectItem *pAssoc = udPROJECT::GetDiagramElement( element );
	
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
				/*pAlg->GetProcessedElements().Append( pTrgShape );*/
			}
		}
	}
}
