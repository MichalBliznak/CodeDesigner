#include "RenameVirtualDialog.h"
#include <wx/valgen.h>

udRenameVirtualDialog::udRenameVirtualDialog(wxWindow *parent, udMemberFunctionItem *fcn, udLanguage *lang)
: _RenameVirtualDialog(parent)
{
	wxASSERT( fcn );
	wxASSERT( lang );
	
	m_Lang = lang;
	m_Name = fcn->GetName();
	
	m_textCtrlName->SetValidator( wxGenericValidator( &m_Name) );
	
	// initialize rename candidates
	SerializableList lstMembers;
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udMemberFunctionItem), lstMembers );
	
	int nIndex = 0;
	for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
	{
		udMemberFunctionItem *pCand = (udMemberFunctionItem*)*it;
		
		if( ( pCand->GetFunctionModifer() == udLanguage::FM_ABSTRACT ||
			  pCand->GetFunctionModifer() == udLanguage::FM_VIRTUAL ) &&
			  pCand->GetName() == m_Name )
		{
			m_checkListCandidates->Append( wxString::Format( wxT("%s::%s"), pCand->GetScope().c_str(), pCand->GetName().c_str() ) );
			m_checkListCandidates->Check( nIndex++ );
		}
	}
}

udRenameVirtualDialog::~udRenameVirtualDialog()
{
}

void udRenameVirtualDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_textCtrlName->GetValue() ) && m_chbMakeValid->GetValue() && m_Lang)
	{
		long nFrom, nTo;
		m_textCtrlName->GetSelection(&nFrom, &nTo);
		
		m_textCtrlName->ChangeValue( m_Lang->MakeValidIdentifier( IPluginManager::Get()->GetProject()->MakeUniqueName(  m_textCtrlName->GetValue() ) ) );
		
		m_textCtrlName->SetSelection( nFrom, nTo );
	}
}

void udRenameVirtualDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udRenameVirtualDialog::OnOk(wxCommandEvent& event)
{	if( m_textCtrlName->GetValue() == wxT("") )
	{
		wxMessageBox(wxT("Name cannot be empty."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		m_textCtrlName->SetFocus();
	}
	else
	{
		// get data via validators...
		TransferDataFromWindow();
		
		// get candidates
		for( size_t i = 0; i < m_checkListCandidates->GetCount(); ++i )
		{
			if( m_checkListCandidates->IsChecked( i ) ) m_arrCandidates.Add( m_checkListCandidates->GetString( i ) );
		}
		
		EndModal( wxID_OK );
	}
}

void udRenameVirtualDialog::OnDeselectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListCandidates->GetCount(); ++i )
	{
		m_checkListCandidates->Check( i, false );
	}
}

void udRenameVirtualDialog::OnSelectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListCandidates->GetCount(); ++i )
	{
		m_checkListCandidates->Check( i );
	}
}

