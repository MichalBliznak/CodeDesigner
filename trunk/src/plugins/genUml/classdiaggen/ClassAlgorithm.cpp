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

    wxASSERT(m_pParentGenerator->GetActiveLanguage());
    if(!m_pParentGenerator->GetActiveLanguage())return;
	
	wxSFDiagramManager *pDiagManager = &src->GetDiagramManager();
	
	// get class elements
    ShapeList lstClasses;
    pDiagManager->GetShapes(CLASSINFO(umlClassItem), lstClasses);
	
	for( ShapeList::iterator it = lstClasses.begin(); it != lstClasses.end(); ++it )
	{
		ProcessClass( (umlClassItem*)*it );
	}
}

// protected functions /////////////////////////////////////////////////////////////////

bool udClassAlgorithm::Initialize()
{
	m_lstProcessedElements.Clear();
	
    return true;
}

void udClassAlgorithm::ProcessClass(umlClassItem *shape)
{
	wxASSERT(shape);
	if(!shape) return;
	
	// check whether the class is already processed
    if( m_lstProcessedElements.IndexOf(shape) != wxNOT_FOUND )return;
	
	// process child classes recursivelly
	ShapeList lstBases;
	umlClassDiagram::GetBaseClasses( shape, lstBases );

	for( ShapeList::iterator it = lstBases.begin(); it != lstBases.end(); ++it )
	{
		ProcessClass( (umlClassItem*)*it );
	}
	
    //wxSFDiagramManager *pDiagManager = shape->GetShapeManager();
    udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();

    // process given element
    udElementProcessor *pProcessor = GetElementProcessor(shape->GetClassInfo()->GetClassName());
    if(pProcessor)
    {
        pProcessor->ProcessElement(shape);
    }
    else
    {
        pLang->SingleLineCommentCmd(wxString::Format(wxT( "!!! WARNING: UNSUPPORTED ELEMENT ('%s') !!!"), ((udProjectItem*)shape->GetUserData())->GetName().c_str()));
        IPluginManager::Get()->Log(wxString::Format(wxT("WARNING: '%s' element is not supported by this algorithm."), ((udProjectItem*)shape->GetUserData())->GetName().c_str()));
    }

    // set the state as processes
    m_lstProcessedElements.Append(shape);

}
