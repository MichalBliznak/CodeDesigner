#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/StoreToBankDialog.h"
#include "UMLDesignerApp.h"
#include "Art.h"
#include "XS2PG.h"

// constructor and destructor //////////////////////////////////////////////////

udStoreToBankDialog::udStoreToBankDialog(wxWindow *parent, udDiagramItem *diag) : _StoreToBankDialog( parent )
{
	wxASSERT( diag );
	
	m_Diagram = diag;
	
	// initialize categories
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	wxArrayString arrCategories;
	Bank.GetCategoriesNames( arrCategories );
	
	for( size_t i = 0; i < arrCategories.GetCount(); i++ )
	{
		m_chCategory->Append( arrCategories[i] );
	}
	m_chCategory->Select(0);
	
	// initialize static text
	m_stDiagName->SetLabel( wxT("Name: ") + diag->GetName() );
	
	// initialize description
	m_textDescription->SetValue( diag->GetDescription() );
	
	// initialize dependecies
	SerializableList lstDeps;
	udProject::Get()->GetDiagramCodeItems( diag, CLASSINFO(udCodeItem), lstDeps );
	
	InsertProjectItems( m_lstDeps, lstDeps, udfSORT );
}

udStoreToBankDialog::~udStoreToBankDialog()
{
}

// virtual event handlers //////////////////////////////////////////////////////

void udStoreToBankDialog::OnCreateClick(wxCommandEvent& event)
{
	wxTextEntryDialog dlg( this, wxT("Category name:"), wxT("CodeDesigner") );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		udDiagramBank& Bank = wxGetApp().GetDiagramBank();
		
		if( Bank.CreateCategory( dlg.GetValue() ) )
		{
			m_chCategory->Append( dlg.GetValue() );
			m_chCategory->SetStringSelection( dlg.GetValue() );
		}
	}
}

void udStoreToBankDialog::OnStoreClick(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	// get selected category
	
	udDiagramCategory *pCat = Bank.GetCategory( m_chCategory->GetStringSelection() );
	if( pCat )
	{
		pCat->AddDiagram( m_Diagram, m_textDescription->GetValue() );
	}
	
	EndModal( wxID_OK );
}

