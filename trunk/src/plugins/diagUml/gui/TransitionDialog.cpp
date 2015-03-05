#include <wx/valgen.h>

#include "TransitionDialog.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udTransitionDialog::udTransitionDialog(wxWindow *parent, udTransElementItem *trans, udLanguage *lang) : _TransitionDialog( parent )
{
	m_pLang = lang;
	m_pTransition = trans;
}

udTransitionDialog::~udTransitionDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udTransitionDialog::OnInit(wxInitDialogEvent& event)
{
	// set validators
	m_eName->SetValidator(wxGenericValidator(&m_Name));
	m_eDescription->SetValidator(wxGenericValidator(&m_Description));
	m_spinPriority->SetValidator(wxGenericValidator(&m_Priority));
	
	IProject *pProj = IPluginManager::Get()->GetProject();
	
	// initialize available conditions
	SerializableList lstCodeItems;
	pProj->GetItems( CLASSINFO(udConditionItem), lstCodeItems );
	pProj->GetItems( CLASSINFO(udEventItem), lstCodeItems );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		m_chConditions->Append( ((udCodeItem*)*it)->GetName() );
	}
	udCodeLinkItem *pCurrCond = wxDynamicCast( m_pTransition->GetCondition(), udCodeLinkItem );
	if( pCurrCond ) m_chConditions->SetStringSelection( pCurrCond->GetOriginal()->GetName() );
	
	// initialize available actions
	lstCodeItems.Clear();
	pProj->GetItems( CLASSINFO(udActionItem), lstCodeItems );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		m_listAvailable->Append( ((udProjectItem*)*it)->GetName() );
	}
	
	// initialize used actions
	lstCodeItems.Clear();
	m_pTransition->GetCodeItems( CLASSINFO(udActionLinkItem), lstCodeItems );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		m_listUsed->Append( ((udActionLinkItem*)*it)->GetOriginal()->GetName() );
	}
	
	// use validators to transfer a data
	TransferDataToWindow();
	m_pageCondition->TransferDataToWindow();
	m_pageActions->TransferDataToWindow();
}

void udTransitionDialog::OnNameChange(wxCommandEvent& event)
{
	if( ( m_Name != m_eName->GetValue() ) && m_cbMakeValid->GetValue() && m_pLang)
	{
		long nFrom, nTo;
		m_eName->GetSelection(&nFrom, &nTo);
		
		m_eName->ChangeValue( m_pLang->MakeValidIdentifier( m_eName->GetValue() ) );
		
		m_eName->SetSelection( nFrom, nTo );
	}
}

void udTransitionDialog::OnMakeValid(wxCommandEvent& event)
{
	OnNameChange( event );
}

void udTransitionDialog::OnOk(wxCommandEvent& event)
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
		m_pageCondition->TransferDataFromWindow();
		m_pageActions->TransferDataFromWindow();
		
		// ... and via direct functions
		
		EndModal( wxID_OK );
	}
}

void udTransitionDialog::OnAdd(wxCommandEvent& event)
{
	wxArrayInt arrAvailableSelection;
	m_listAvailable->GetSelections( arrAvailableSelection );
	
	for( size_t i = 0; i < arrAvailableSelection.GetCount(); i++ )
	{
		m_listUsed->Append( m_listAvailable->GetString( arrAvailableSelection[i] ) );
	}
}

void udTransitionDialog::OnDeselectAllAvailable(wxCommandEvent& event)
{
	//m_listAvailable->SetSelection( wxNOT_FOUND );
	
	for( size_t i = 0; i < m_listAvailable->GetCount(); i++ ) m_listAvailable->Deselect( i );
}

void udTransitionDialog::OnDeselectAllUsed(wxCommandEvent& event)
{
	//m_listUsed->SetSelection( wxNOT_FOUND );
	
	for( size_t i = 0; i < m_listUsed->GetCount(); i++ ) m_listUsed->Deselect( i );
}

void udTransitionDialog::OnDown(wxCommandEvent& event)
{
	size_t nIndex;
	wxString sItem;
	wxArrayInt arrUsedSelection;
	
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

void udTransitionDialog::OnRemove(wxCommandEvent& event)
{
	int nDelCount = 0;
	
	wxArrayInt arrUsedSelection;
	m_listUsed->GetSelections( arrUsedSelection );
	
	for( size_t i = 0; i < arrUsedSelection.GetCount(); i++ )
	{
		m_listUsed->Delete( arrUsedSelection[i - nDelCount] );
		nDelCount++;
	}
}

void udTransitionDialog::OnRemoveAllUsed(wxCommandEvent& event)
{
	m_listUsed->Clear();
}

void udTransitionDialog::OnSelectAllAvailable(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_listAvailable->GetCount(); i++ ) m_listAvailable->SetSelection( i );
}

void udTransitionDialog::OnSelectAllUsed(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_listUsed->GetCount(); i++ ) m_listUsed->SetSelection( i );
}

void udTransitionDialog::OnUp(wxCommandEvent& event)
{
	size_t nIndex;
	wxString sItem;
	wxArrayInt arrUsedSelection;
	
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

void udTransitionDialog::OnUpdateAdd(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	m_listAvailable->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udTransitionDialog::OnUpdateDown(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	m_listUsed->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udTransitionDialog::OnUpdateRemove(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	m_listUsed->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udTransitionDialog::OnUpdateUp(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelections;
	m_listUsed->GetSelections( arrSelections );
	
	event.Enable( !arrSelections.IsEmpty() );
}

void udTransitionDialog::OnConditionChange(wxCommandEvent& event)
{
	event.Skip();
}

// public functions //////////////////////////////////////////////////////////////////////////

wxString udTransitionDialog::GetActionsString()
{
	wxString sOut;
	
	for( size_t i = 0; i < m_listUsed->GetCount(); i++ )
	{
		if( i > 0 ) sOut << wxT(", ");
		sOut << m_listUsed->GetString( i );
	}
	
	return sOut;
}

wxString udTransitionDialog::GetConditionString()
{
	return m_chConditions->GetStringSelection();
}
