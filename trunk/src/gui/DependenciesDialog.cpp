#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/DependenciesDialog.h"

udDependenciesDialog::udDependenciesDialog(wxWindow *parent, SerializableList& records) : _DependenciesDialog(parent)
{
	// fill dependencies
	SerializableList lstDeps;
	udDiagramRecord *pRec;
	wxString sDesc;
	
	for( SerializableList::iterator it = records.begin(); it != records.end(); ++it )
	{
		pRec = (udDiagramRecord*)*it;
		
		pRec->GetDiagramDependencies( lstDeps );
		sDesc << pRec->GetDiagram()->GetName() << wxT(":\n") << pRec->GetDescription() << wxT("\n\n");
	}
	
	InsertProjectItems( m_lstDeps, lstDeps, udfSORT );
	m_textDescription->SetValue( sDesc );
}

udDependenciesDialog::~udDependenciesDialog()
{
}

