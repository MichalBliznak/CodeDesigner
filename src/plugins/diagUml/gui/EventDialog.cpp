#include <wx/valgen.h>

#include "EventDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udEventDialog::udEventDialog(wxWindow *parent, udLanguage *lang) : _EventDialog( parent )
{
	m_pLang = lang;
}

udEventDialog::~udEventDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udEventDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	
	m_chEventType->SetSelection( (int)m_EventType );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
	
}

void udEventDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udEventDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udEventDialog::OnOk(wxCommandEvent& event)
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
		
		// ... and via direct functions
		m_EventType = (udEventItem::TYPE) m_chEventType->GetSelection();
		
		EndModal( wxID_OK );
	}
}

void udEventDialog::OnTypeChange(wxCommandEvent& event)
{
	event.Skip();
}

