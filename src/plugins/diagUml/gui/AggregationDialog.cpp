#include <wx/valgen.h>

#include "AggregationDialog.h"
#include "projectbase/ProjectBase.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udAggregationDialog::udAggregationDialog(wxWindow *parent, udLanguage *lang) : _AggregationDialog(parent)
{
	m_Lang = lang;
}

udAggregationDialog::~udAggregationDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udAggregationDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_chbIncludeClass->SetValidator(wxGenericValidator(&m_IncludeClass));
	
	// initialize choice
	wxString sAT;
	int i = 0;
	
	while( (sAT = m_Lang->GetAccessTypeString( (udLanguage::ACCESSTYPE)i++ )) != wxEmptyString )
	{
		m_chAccess->Append( sAT );
	}
	if( i ) m_chAccess->SetSelection( m_AccessType );
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageAdv->TransferDataToWindow();
}

void udAggregationDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );	
}

void udAggregationDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_Lang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_Lang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udAggregationDialog::OnOk(wxCommandEvent& event)
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
		
		m_AccessType = m_chAccess->GetSelection();
		
		EndModal( wxID_OK );
	}
}
