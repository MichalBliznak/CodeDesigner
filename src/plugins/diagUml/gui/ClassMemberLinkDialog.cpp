#include <wx/valgen.h>

#include "ClassMemberLinkDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udClassMemberLinkDialog::udClassMemberLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang) : _ClassMemberLinkDialog( parent )
{
	m_pOriginal = orig;
	m_pLang = lang;
	m_AccessType = 0;
}

udClassMemberLinkDialog::~udClassMemberLinkDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udClassMemberLinkDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	
	// initialize other components
	m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang ) );
	m_chType->SetSelection( m_AccessType );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udClassMemberLinkDialog::OnEditOriginal(wxCommandEvent& event)
{
	if( m_pOriginal )
	{
		wxString sPrevOrigName = m_pOriginal->GetName();
		
		m_pOriginal->OnEditItem( this );
		
		if( sPrevOrigName == m_eName->GetValue() ) m_eName->SetValue( m_pOriginal->GetName() );
		m_stOriginal->SetLabel( m_pOriginal->ToString( udCodeItem::cfFORMAL, m_pLang) );
	}
}

void udClassMemberLinkDialog::OnOk(wxCommandEvent& event)
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
		
		// ... and via direct functions
		m_AccessType = m_chType->GetSelection();
		
		EndModal( wxID_OK );
	}
}
