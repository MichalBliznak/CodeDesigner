#include <wx/valgen.h>

#include "CompStateDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udCompStateDialog::udCompStateDialog(wxWindow *parent, udCompStateElementItem *state, udLanguage *lang) : _CompStateDialog( parent )
{
	m_pLang = lang;
	m_pState = state;
}

udCompStateDialog::~udCompStateDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udCompStateDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	
	udStateActionLinkItem *pActLink;
	IProject *pProj = IPluginManager::Get()->GetProject();
	
	SerializableList lstCodeItems;
	
	// initialize available actions
	lstCodeItems.Clear();
	pProj->GetItems( CLASSINFO(udActionItem), lstCodeItems );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		m_listAvailable->Append( ((udProjectItem*)*it)->GetName() );
	}
	
	// initialize used actions
	lstCodeItems.Clear();
	m_pState->GetCodeItems( CLASSINFO(udStateActionLinkItem), lstCodeItems );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		pActLink = (udStateActionLinkItem*)*it;
		if( pActLink->GetActionType() == udStateActionLinkItem::saENTRY ) m_listUsedEntry->Append( pActLink->GetOriginal()->GetName() );
		else
			 m_listUsedExit->Append( pActLink->GetOriginal()->GetName() );
	}
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageActions->TransferDataToWindow();
}

void udCompStateDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udCompStateDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udCompStateDialog::OnOk(wxCommandEvent& event)
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
		m_pageActions->TransferDataFromWindow();
		
		// ... and via direct functions
		
		EndModal( wxID_OK );
	}
}

void udCompStateDialog::OnAdd(wxCommandEvent& event)
{
	wxArrayInt arrAvailableSelection;
	m_listAvailable->GetSelections( arrAvailableSelection );
	
	for( size_t i = 0; i < arrAvailableSelection.GetCount(); i++ )
	{
		GetActiveUsedList()->Append( m_listAvailable->GetString( arrAvailableSelection[i] ) );
	}
}

void udCompStateDialog::OnDeselectAllAvailable(wxCommandEvent& event)
{
	//m_listAvailable->SetSelection( wxNOT_FOUND );
	
	for( size_t i = 0; i < m_listAvailable->GetCount(); i++ ) m_listAvailable->Deselect( i );
}

void udCompStateDialog::OnDeselectAllUsed(wxCommandEvent& event)
{
	//GetActiveUsedList()->SetSelection( wxNOT_FOUND );
	
	wxListBox *m_listUsed = GetActiveUsedList();
	for( size_t i = 0; i < m_listUsed->GetCount(); i++ ) m_listUsed->Deselect( i );
}

void udCompStateDialog::OnDown(wxCommandEvent& event)
{
	size_t nIndex;
	wxString sItem;
	wxArrayInt arrUsedSelection;
	
	wxListBox *m_listUsed = GetActiveUsedList();
	
	m_listUsed->GetSelections( arrUsedSelection );
	
	// move list items
	for( int i = arrUsedSelection.GetCount()-1; i >= 0 ; i-- )
	{
		nIndex = arrUsedSelection[i];
		if( nIndex < (m_listUsed->GetCount() - 1) )
		{
			sItem = m_listUsed->GetString( nIndex );
			
			m_listUsed->Delete( nIndex );
			m_listUsed->Insert( sItem, nIndex + 1);
		}
	}	
	
	// restore selection
	for( int i = arrUsedSelection.GetCount()-1; i >= 0 ; i-- )
	{
		if( (size_t)(arrUsedSelection[i]+1) < (m_listUsed->GetCount()-1) ) m_listUsed->SetSelection( arrUsedSelection[i]+1 );
		else
		{
			m_listUsed->SetSelection( wxNOT_FOUND );
			break;
		}
	}
}

void udCompStateDialog::OnRemove(wxCommandEvent& event)
{
	int nDelCount = 0;
	
	wxListBox *m_listUsed = GetActiveUsedList();
	
	wxArrayInt arrUsedSelection;
	m_listUsed->GetSelections( arrUsedSelection );
	
	for( size_t i = 0; i < arrUsedSelection.GetCount(); i++ )
	{
		m_listUsed->Delete( arrUsedSelection[i - nDelCount] );
		nDelCount++;
	}
}

void udCompStateDialog::OnRemoveAllUsed(wxCommandEvent& event)
{
	GetActiveUsedList()->Clear();
}

void udCompStateDialog::OnSelectAllAvailable(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_listAvailable->GetCount(); i++ ) m_listAvailable->SetSelection( i );
}

void udCompStateDialog::OnSelectAllUsed(wxCommandEvent& event)
{
	wxListBox *m_listUsed = GetActiveUsedList();
	
	for( size_t i = 0; i < m_listUsed->GetCount(); i++ ) m_listUsed->SetSelection( i );
}

void udCompStateDialog::OnUp(wxCommandEvent& event)
{
	size_t nIndex;
	wxString sItem;
	wxArrayInt arrUsedSelection;
	
	wxListBox *m_listUsed = GetActiveUsedList();
	
	m_listUsed->GetSelections( arrUsedSelection );
	
	// move list items
	for( size_t i = 0; i < arrUsedSelection.GetCount(); i++ )
	{
		nIndex = arrUsedSelection[i];
		if( nIndex > 0 )
		{
			sItem = m_listUsed->GetString( nIndex );
			
			m_listUsed->Delete( nIndex );
			m_listUsed->Insert( sItem, nIndex - 1);
		}
	}	
	
	// restore selection
	for( size_t i = 0; i < arrUsedSelection.GetCount(); i++ )
	{
		if( (size_t)(arrUsedSelection[i]-1) > 0 ) m_listUsed->SetSelection( arrUsedSelection[i]-1 );
		else
		{
			m_listUsed->SetSelection( wxNOT_FOUND );
			break;
		}
	}
}

void udCompStateDialog::OnUpdateAdd(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	m_listAvailable->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udCompStateDialog::OnUpdateDown(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	GetActiveUsedList()->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udCompStateDialog::OnUpdateRemove(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	GetActiveUsedList()->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udCompStateDialog::OnUpdateUp(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	GetActiveUsedList()->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udCompStateDialog::OnConditionChange(wxCommandEvent& event)
{
	event.Skip();
}

// public functions //////////////////////////////////////////////////////////////////////////

wxString udCompStateDialog::GetEntryActionsString()
{
	wxString sOut;
	
	for( size_t i = 0; i < m_listUsedEntry->GetCount(); i++ )
	{
		if( i > 0 ) sOut << wxT(", ");
		sOut << m_listUsedEntry->GetString( i );
	}
	
	return sOut;
}

wxString udCompStateDialog::GetExitActionsString()
{
	wxString sOut;
	
	for( size_t i = 0; i < m_listUsedExit->GetCount(); i++ )
	{
		if( i > 0 ) sOut << wxT(", ");
		sOut << m_listUsedExit->GetString( i );
	}
	
	return sOut;
}

// protected functions ///////////////////////////////////////////////////////////////////////

wxListBox* udCompStateDialog::GetActiveUsedList()
{
	wxString sPageName = m_notebookActions->GetPageText( m_notebookActions->GetSelection() );
	
	if( sPageName == wxT("Entry") ) return m_listUsedEntry;
	else
		return m_listUsedExit;
}
