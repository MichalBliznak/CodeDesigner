#include "ClassTemplDialog.h"
#include "interfaces/IPluginManager.h"

#include <wx/valgen.h>

udClassTemplateDialog::udClassTemplateDialog(wxWindow *parent, udLanguage *lang) : _ClassTemplateDialog(parent)
{
	m_pLang = lang;
}

udClassTemplateDialog::~udClassTemplateDialog()
{
}

void udClassTemplateDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_txtTemplateName->SetValidator(wxGenericValidator(&m_TemplateName));
	
	TransferDataToWindow();
	m_pageTempl->TransferDataToWindow();
}

void udClassTemplateDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udClassTemplateDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udClassTemplateDialog::OnOk(wxCommandEvent& event)
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
		m_pageTempl->TransferDataFromWindow();
		
		EndModal( wxID_OK );
	}
}
