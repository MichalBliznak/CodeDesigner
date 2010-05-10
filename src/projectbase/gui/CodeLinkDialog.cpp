#include <wx/valgen.h>

#include "CodeLinkDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udCodeLinkDialog::udCodeLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang) : _CodeLinkDialog( parent )
{
	m_pOriginal = orig;
	m_pLang = lang;
}

udCodeLinkDialog::~udCodeLinkDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udCodeLinkDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	
	// initialize original label
	m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang ) );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udCodeLinkDialog::OnEditOriginal(wxCommandEvent& event)
{
	if( m_pOriginal )
	{
		wxString sPrevOrigName = m_pOriginal->GetName();
		
		m_pOriginal->OnEditItem( this );
		
		if( sPrevOrigName == m_eName->GetValue() ) m_eName->SetValue( m_pOriginal->GetName() );
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang) );
	}
}

void udCodeLinkDialog::OnOk(wxCommandEvent& event)
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
