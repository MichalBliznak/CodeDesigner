#include "ClassDiagramGenerator.h"
#include "CPPClassAlgorithm.h"
#include "CPPElementProcessors.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udClassAlgorithm, udAlgorithm);

// constructor and destructor ///////////////////////////////////////////////////////

udClassAlgorithm::udClassAlgorithm()
{
}

udClassAlgorithm::udClassAlgorithm(udGenerator *parent) : udAlgorithm(parent)
{
}

udClassAlgorithm::~udClassAlgorithm()
{
}

// public functions /////////////////////////////////////////////////////////////////

void udClassAlgorithm::ProcessAlgorithm(udDiagramItem *src)
{
   // test "prerequisites"
    wxASSERT(m_pParentGenerator);
    if(!m_pParentGenerator)return;
	
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    wxASSERT(pLang);
    if(!pLang)return;
	
	wxSFDiagramManager *pDiagManager = &src->GetDiagramManager();
	
	ShapeList lstElements;
	ShapeList lstAssocs;
	
	// generate stand-alone enumerations
	pDiagManager->GetShapes(CLASSINFO(umlEnumItem), lstElements);
	
	for( ShapeList::iterator it = lstElements.begin(); it != lstElements.end(); ++it )
	{
		lstAssocs.Clear();
		
		pDiagManager->GetAssignedConnections( *it, CLASSINFO(wxSFLineShape), wxSFLineShape::lineENDING, lstAssocs );
		if( lstAssocs.IsEmpty() )
		{
			udElementProcessor *pProcessor = GetElementProcessor( (*it)->GetClassInfo()->GetClassName() );
			if(pProcessor)
			{
				pProcessor->ProcessElement( *it );
			}
			else
			{
				pLang->SingleLineCommentCmd(wxString::Format(wxT( "!!! WARNING: UNSUPPORTED ELEMENT ('%s') !!!"), ((udProjectItem*)(*it)->GetUserData())->GetName().c_str()));
				IPluginManager::Get()->Log(wxString::Format(wxT("WARNING: '%s' element is not supported by this algorithm."), ((udProjectItem*)(*it)->GetUserData())->GetName().c_str()));
			}
		}
	}
	
	// generate outer classes
	lstElements.Clear();
    pDiagManager->GetShapes(CLASSINFO(umlClassItem), lstElements);
	
	for( ShapeList::iterator it = lstElements.begin(); it != lstElements.end(); ++it )
	{
		lstAssocs.Clear();
		
		pDiagManager->GetAssignedConnections( *it, CLASSINFO(umlIncludeAssocItem), wxSFLineShape::lineENDING, lstAssocs );
		if( lstAssocs.IsEmpty() )
		{
			udElementProcessor *pProcessor = GetElementProcessor( (*it)->GetClassInfo()->GetClassName() );
			if(pProcessor)
			{
				pProcessor->ProcessElement( *it );
			}
			else
			{
				pLang->SingleLineCommentCmd(wxString::Format(wxT( "!!! WARNING: UNSUPPORTED ELEMENT ('%s') !!!"), ((udProjectItem*)(*it)->GetUserData())->GetName().c_str()));
				IPluginManager::Get()->Log(wxString::Format(wxT("WARNING: '%s' element is not supported by this algorithm."), ((udProjectItem*)(*it)->GetUserData())->GetName().c_str()));
			}
		}
	}
}

// protected functions /////////////////////////////////////////////////////////////////

bool udClassAlgorithm::Initialize()
{
	m_lstProcessedElements.Clear();
	
    return true;
}
