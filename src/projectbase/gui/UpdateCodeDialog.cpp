#include "UpdateCodeDialog.h"

#include "../Common.h"

// constructor and destructor ////////////////////////////////////////////////////////////////

udUpdateCodeDialog::udUpdateCodeDialog(wxWindow *parent, udLanguage *lang) : _UpdateCodeDialog( parent )
{
	wxASSERT( lang );
	m_Lang = lang;
}

udUpdateCodeDialog::~udUpdateCodeDialog()
{
}

// virtual functions /////////////////////////////////////////////////////////////////////////

void udUpdateCodeDialog::OnInit(wxInitDialogEvent& event)
{
	// initialize static text
	m_staticText->SetLabel( wxT("Reference to '") + m_Pattern + wxT("' has been found in these code items:") );
	
	// initialize scintilla 
	udFRAME::InitStyledTextCtrl( m_scintillaCode, m_Lang );
	
	// fill checklist
	for( SerializableList::iterator it = m_References.begin(); it != m_References.end(); ++it )
	{
		udCodeItem *pItem = (udCodeItem*)*it;
		m_checkListCodeItems->Append( pItem->GetScope() + wxT("::") + pItem->GetName() );
	}
	if( !m_References.IsEmpty() )
	{
		m_checkListCodeItems->SetSelection( 0 );
		UpdateCodePreview( 0 );
	}
}

void udUpdateCodeDialog::OnChangeCodeitem(wxCommandEvent& event)
{
	UpdateCodePreview( m_checkListCodeItems->GetSelection() );
}

void udUpdateCodeDialog::OnCancel(wxCommandEvent& event)
{
	EndModal( wxID_CANCEL );
}

void udUpdateCodeDialog::OnUpdate(wxCommandEvent& event)
{
	// update code in referenced code items
	udCodeItem *pItem;
	wxString sCode;
	
	for( size_t i = 0; i < m_checkListCodeItems->GetCount(); ++i )
	{
		if( m_checkListCodeItems->IsChecked( i ) )
		{
			pItem = (udCodeItem*)m_References.Item( i )->GetData();
			
			sCode = pItem->GetCode();
			sCode.Replace( m_Pattern + wxT(" "), m_NewPattern + wxT(" ") );
			
			pItem->SetCode( sCode );
		}
	}
	
	EndModal( wxID_OK );
}

// protected functions ///////////////////////////////////////////////////////////////////////

void udUpdateCodeDialog::UpdateCodePreview(int selection)
{
	if( selection > -1 && selection < m_References.GetCount() )
	{
		udCodeItem *pItem = (udCodeItem*)m_References.Item( selection )->GetData();
		
		// set content
		m_scintillaCode->SetReadOnly( false );
		m_scintillaCode->SetText( pItem->GetCode() );
		m_scintillaCode->SetReadOnly( true );
		
		// highlight patters
		/*int patternStart = 0;
		while( (patternStart = m_scintillaCode->FindText( patternStart, m_scintillaCode->GetTextLength(), m_Pattern )) != wxSCI_INVALID_POSITION )
		{
			m_scintillaCode->SetSelection( patternStart, patternStart + m_Pattern.Len() );
			patternStart += m_Pattern.Len();
		}*/
		
		int patternStart = m_scintillaCode->FindText( 0, m_scintillaCode->GetTextLength(), m_Pattern, wxSCI_FIND_MATCHCASE );
		if( patternStart != wxSCI_INVALID_POSITION )
		{
			m_scintillaCode->SetSelection( patternStart, patternStart + m_Pattern.Len() );
		}
	}
}

void udUpdateCodeDialog::OnNext(wxCommandEvent& event)
{
	m_scintillaCode->SearchAnchor();
	if( m_scintillaCode->SearchNext( wxSCI_FIND_MATCHCASE, m_Pattern ) == wxSCI_INVALID_POSITION )
	{
		wxMessageBox( wxT("The end of the code preview has been reached."), wxT("CodeDesigner"), wxOK );
	}
}

void udUpdateCodeDialog::OnPrevious(wxCommandEvent& event)
{
	m_scintillaCode->SearchAnchor();
	if( m_scintillaCode->SearchPrev( wxSCI_FIND_MATCHCASE, m_Pattern ) == wxSCI_INVALID_POSITION )
	{
		wxMessageBox( wxT("The begin of the code preview has been reached."), wxT("CodeDesigner"), wxOK );
	}
}

void udUpdateCodeDialog::ShowIfNeeded()
{
	udPROJECT::FindCodeReferences( m_Pattern, m_References );
	if( !m_References.IsEmpty() )
	{
		ShowModal();
	}
}

void udUpdateCodeDialog::OnDeselectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListCodeItems->GetCount(); ++i )
	{
		m_checkListCodeItems->Check( i, false );
	}
}

void udUpdateCodeDialog::OnSelectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListCodeItems->GetCount(); ++i )
	{
		m_checkListCodeItems->Check( i, true );
	}
}

