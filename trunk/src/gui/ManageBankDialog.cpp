#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/ManageBankDialog.h"
#include "projectbase/gui/ChoiceDialog.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"

// constructor and destructor ///////////////////////////////////////////////////////////

udManageBankDialog::udManageBankDialog(wxWindow *parent) : _ManageBankDialog( parent )
{
	UMLDesignerFrame::EnableInternalEvents( false );
	
	// initialize categories
	FillCategories();
}

udManageBankDialog::~udManageBankDialog()
{
	UMLDesignerFrame::EnableInternalEvents( true );
}

// virtual event handlers ///////////////////////////////////////////////////////////////

void udManageBankDialog::OnCreateCat(wxCommandEvent& event)
{
	wxTextEntryDialog dlg( this, wxT("Category name:"), wxT("CodeDesigner") );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		udDiagramBank& Bank = wxGetApp().GetDiagramBank();
		
		if( Bank.CreateCategory( dlg.GetValue() ) )
		{
			m_lbCategories->Append( dlg.GetValue() );
			m_lbCategories->SetStringSelection( dlg.GetValue() );
		}
		
		FillCategories();
	}
}

void udManageBankDialog::OnRemoveCat(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
	if( pCat )
	{
		// check whether also non-empty category can be removed
		if( pCat->HasChildren() )
		{
			if( wxMessageBox( wxT("Selected category is not empty. Are you sure you want to remove it?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION ) == wxNO ) return;		
		}
		
		Bank.RemoveCategory( pCat->GetName() );
		
		FillCategories();
	}
}

void udManageBankDialog::OnRenameCat(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
	if( pCat )
	{
		wxTextEntryDialog dlg( this, wxT("New category name:"), wxT("CodeDesigner"), pCat->GetName() );
	
		if( dlg.ShowModal() == wxID_OK )
		{
			pCat->SetName( dlg.GetValue() );
			
			FillCategories();
		}
	}
}

void udManageBankDialog::OnRemoveDiag(wxCommandEvent& event)
{
	if( wxMessageBox( wxT("Are you sure you want to remove selected diagram?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION ) == wxYES )
	{
		udDiagramRecord *pRec = GetSelectedRecord();
		if( pRec )
		{
			udDiagramItem *pDiag = pRec->GetDiagram();
			if( pDiag )
			{
				udDiagramBank& Bank = wxGetApp().GetDiagramBank();
				Bank.GetCategory( m_lbCategories->GetStringSelection() )->RemoveDiagram( pDiag->GetName() );
				
				FillDiagrams( m_lbCategories->GetStringSelection() );
				m_lstDeps->ClearAll();
			}
		}
	}
}

void udManageBankDialog::OnRemoveAllDiag(wxCommandEvent& event)
{
	if( wxMessageBox( wxT("Are you sure you want to remove all diagrams from this category?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION ) == wxYES )
	{
		udDiagramBank& Bank = wxGetApp().GetDiagramBank();
		udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
		if( pCat )
		{
			pCat->GetChildrenList().DeleteContents(true);
			pCat->GetChildrenList().Clear();
			pCat->GetChildrenList().DeleteContents(false);
			
			m_lstDiagrams->ClearAll();
			m_lstDeps->ClearAll();
		}
	}
}

void udManageBankDialog::OnMoveDiag(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
	if( pCat )
	{
		udDiagramRecord *pRec = CopyRecord();
		if( pRec )
		{
			pCat->GetChildrenList().DeleteObject( pRec );
		
			FillDiagrams( pCat->GetName() );
			m_lstDeps->ClearAll();
		}
	}
}

void udManageBankDialog::OnCopyDiag(wxCommandEvent& event)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
	if( pCat )
	{
		if( CopyRecord() )
		{
			FillDiagrams( pCat->GetName() );
			m_lstDeps->ClearAll();
		}
	}
}

void udManageBankDialog::OnCategoryChange(wxCommandEvent& event)
{
	m_lstDiagrams->ClearAll();
	m_lstDeps->ClearAll();
	m_textDescription->Clear();
	
	FillDiagrams( m_lbCategories->GetStringSelection() );
}

void udManageBankDialog::OnDiagramChange(wxListEvent& event)
{
	udDiagramRecord *pRec = GetSelectedRecord();
	if( pRec )
	{
		// fill descriprion
		m_textDescription->SetValue( pRec->GetDescription() );
		// fill dependencies
		FillDependencies( pRec->GetDiagram() );
	}
}

void udManageBankDialog::OnUpdateMoveTo(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelection;
	GetSelectedItems( m_lstDiagrams, arrSelection );
	
	event.Enable( !arrSelection.IsEmpty() );
}

void udManageBankDialog::OnUpdateRemoveCat(wxUpdateUIEvent& event)
{
	event.Enable( m_lbCategories->GetSelection() != wxNOT_FOUND );
}

void udManageBankDialog::OnUpdateRemoveDiag(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelection;
	GetSelectedItems( m_lstDiagrams, arrSelection );
	
	event.Enable( !arrSelection.IsEmpty() );
}

void udManageBankDialog::OnUpdateRemoveAllDiag(wxUpdateUIEvent& event)
{
	event.Enable( m_lstDiagrams->GetItemCount() > 0 );
}

void udManageBankDialog::OnUpdateRenameCat(wxUpdateUIEvent& event)
{
	event.Enable( m_lbCategories->GetSelection() != wxNOT_FOUND );
}

void udManageBankDialog::OnUpdateCopyTo(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelection;
	GetSelectedItems( m_lstDiagrams, arrSelection );
	
	event.Enable( !arrSelection.IsEmpty() );
}

// protected functions //////////////////////////////////////////////////////////////////

void udManageBankDialog::FillDependencies(udDiagramItem *diagram)
{
	wxASSERT(diagram);
	
	udDiagramRecord *pRec = (udDiagramRecord*) diagram->GetParent();
	if( pRec )
	{
		SerializableList lstDeps;
		pRec->GetDiagramDependencies( lstDeps );
		
		InsertProjectItems( m_lstDeps, lstDeps, udfSORT );
	}
}

void udManageBankDialog::FillDiagrams(const wxString& category)
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	// insert diagrams
	SerializableList lstDiags;
	udDiagramCategory *pCat = Bank.GetCategory( category );
	if( pCat )
	{
		SerializableList::compatibility_iterator node =  pCat->GetFirstChildNode();
		while( node )
		{
			lstDiags.Append( ((udDiagramRecord*) node->GetData())->GetDiagram() );
			node = node->GetNext();
		}
		
		InsertProjectItems( m_lstDiagrams, lstDiags, udfSORT );
	}
}

void udManageBankDialog::FillCategories()
{
	m_lbCategories->Clear();
	
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	wxArrayString arrCategories;
	Bank.GetCategoriesNames( arrCategories );
	
	for( size_t i = 0; i < arrCategories.GetCount(); i++ )
	{
		m_lbCategories->Append( arrCategories[i] );
	}
}

udDiagramRecord* udManageBankDialog::GetSelectedRecord()
{
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	
	udDiagramCategory *pCat = Bank.GetCategory( m_lbCategories->GetStringSelection() );
	if( pCat )
	{
		wxArrayInt arrSelection;
		GetSelectedItems( m_lstDiagrams, arrSelection );
		
		return (udDiagramRecord*) pCat->GetChildrenList().Item( arrSelection[0] )->GetData();
	}
	
	return NULL;
}

udDiagramRecord* udManageBankDialog::CopyRecord()
{
	wxArrayString arrCategories;
	
	udDiagramBank& Bank = wxGetApp().GetDiagramBank();
	Bank.GetCategoriesNames( arrCategories );
	
	udChoiceDialog dlg( this );
	
	dlg.SetChoices( arrCategories );
	dlg.SetTitle( wxT("Move diagram") );
	dlg.SetComment( wxT("Select target category:") );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		udDiagramCategory *pDestCat = Bank.GetCategory( dlg.GetChoiceString() );
		udDiagramRecord *pRec = GetSelectedRecord();
		
		pDestCat->AddChild( (xsSerializable*) pRec->Clone() );
		
		return pRec;
	}
	
	return NULL;
}
