#include <wx/valgen.h>

#include "EventLinkDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udEventLinkDialog::udEventLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang)
: _EventLinkDialog( parent )
{
	m_pOriginal = orig;
	m_pLang = lang;
	m_fClearFlag = false;
}

udEventLinkDialog::~udEventLinkDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udEventLinkDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator( wxGenericValidator(&m_sName) );
	m_checkBoxClearFlag->SetValidator( wxGenericValidator(&m_fClearFlag) );
	
	// initialize other components
	m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang ) );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udEventLinkDialog::OnEditOriginal(wxCommandEvent& event)
{
	if( m_pOriginal )
	{
		wxString sPrevOrigName = m_pOriginal->GetName();
		
		m_pOriginal->OnEditItem( this );
		
		if( sPrevOrigName == m_eName->GetValue() ) m_eName->SetValue( m_pOriginal->GetName() );
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang) );
	}
}

void udEventLinkDialog::OnOk(wxCommandEvent& event)
{
	if( m_eName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_eName->SetFocus();
	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		m_pageAdv->TransferDataFromWindow();
		
		EndModal( wxID_OK );
	}
}
