#include "ClassDialog.h"

#include "projectbase/ProjectBase.h"

#include <wx/valgen.h>

// constructor and destructor //////////////////////////////////////////////////

udClassDialog::udClassDialog(wxWindow *parent, udLanguage *lang) : _ClassDialog(parent)
{
	m_pLang = lang;
}

udClassDialog::~udClassDialog()
{
}

// virtual functions ///////////////////////////////////////////////////////////

void udClassDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_chbGenerate->SetValidator(wxGenericValidator(&m_Generate));
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udClassDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udClassDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier(  m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udClassDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
//	else if( (m_Name != m_eName->GetValue()) && !IPluginManager::Get()->GetProject()->IsUniqueName( m_eName->GetValue() ) )
//	{
//		wxMessageBox(wxT("Name must be unique."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
//		m_eName->SetFocus();		
//	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		m_pageAdv->TransferDataFromWindow();
		
		EndModal( wxID_OK );
	}
}
