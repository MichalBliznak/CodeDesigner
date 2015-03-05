#include <wx/valgen.h>

#include "FinalStateDialog.h"
#include "interfaces/IPluginManager.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udFinalStateDialog::udFinalStateDialog(wxWindow *parent, udLanguage *lang) : _FinalStateDialog( parent )
{
	m_pLang = lang;
}

udFinalStateDialog::~udFinalStateDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udFinalStateDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_textRetValue->SetValidator(wxGenericValidator(&m_ReturnValue));
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udFinalStateDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udFinalStateDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udFinalStateDialog::OnOk(wxCommandEvent& event)
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

void udFinalStateDialog::OnDefault(wxCommandEvent& event)
{
	m_textRetValue->SetValue( wxT("<default>") );
}
