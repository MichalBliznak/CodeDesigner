#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/valgen.h>

#include "CADialog.h"
#include "projectbase/Common.h"
#include "interfaces/IPluginManager.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udCodeDialog::udCodeDialog(wxWindow *parent, udLanguage *lang) : _CodeDialog( parent )
{
	m_pLang = lang;
	m_Inline = false;
}

udCodeDialog::~udCodeDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udCodeDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_cbInline->SetValidator(wxGenericValidator(&m_Inline));
	
	m_sciEditor->SetText( m_Code );
	
	// initialize code editor
	udFRAME::InitStyledTextCtrl( m_sciEditor, m_pLang );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udCodeDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udCodeDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udCodeDialog::OnOk(wxCommandEvent& event)
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
		m_Code = m_sciEditor->GetText();
		
		EndModal( wxID_OK );
	}
}
