#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/SynchronizeDialog.h"
#include "Project.h"
#include "UMLDesignerApp.h"

// constructor and destructor ///////////////////////////////////////////////////////

udSynchronizeDialog::udSynchronizeDialog(wxWindow *parent, udLanguage *lang) : _SynchronizeDialog(parent)
{
	m_Lang = lang;
	
	m_nUpdated = 0;
	m_nAmbiguous = 0;
	
	// initialize scintilla editors
	udFRAME::InitStyledTextCtrl( m_scintillaModified, m_Lang );
	udFRAME::InitStyledTextCtrl( m_scintillaOriginal, m_Lang );
	
	// get mofified user code
	udProjectGenerator::GetModifiedUserCode(m_Lang, m_lstFunctions, m_arrOriginal, m_arrModified, &m_nAmbiguous );
	
	for( SerializableList::iterator it = m_lstFunctions.begin(); it != m_lstFunctions.end(); ++it )
	{
		udCodeItem *pCodeItem = (udCodeItem*) *it;
		m_checkList->Append( wxString::Format( wxT("%s::%s"), pCodeItem->GetScope().c_str(), pCodeItem->GetName().c_str() ) );
	}
	
	if( m_lstFunctions.IsEmpty() )
	{
		m_checkList->Enable( false );
		m_scintillaModified->Enable( false );
		m_scintillaOriginal->Enable( false );
	}
}

udSynchronizeDialog::~udSynchronizeDialog()
{
}

// virtual event handlers ///////////////////////////////////////////////////////////

void udSynchronizeDialog::OnOk(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkList->GetCount(); ++i )
	{
		udFunctionItem *pFcn;
		
		if( m_checkList->IsChecked( i ) )
		{
			pFcn = (udFunctionItem*) m_lstFunctions.Item( i )->GetData();
			
			pFcn->SetCode( m_arrModified[i] );
			m_nUpdated++;
			
			UMLDesignerApp::Log( wxString::Format( wxT("User-defined code of '%s::%s' has been updated."), pFcn->GetScope().c_str(), pFcn->GetName().c_str() ) );
		}
	}
	
	if( m_nAmbiguous ) EndModal( wxID_ABORT );
	else if( m_nUpdated ) EndModal( wxID_OK );
	else EndModal( wxID_NONE );
}

void udSynchronizeDialog::OnSelectCodeItem(wxCommandEvent& event)
{
	int nSelection =  m_checkList->GetSelection();
	if( nSelection != wxNOT_FOUND )
	{
		m_scintillaModified->SetReadOnly( false );
		m_scintillaOriginal->SetReadOnly( false );
	
		m_scintillaModified->SetText( m_arrModified[nSelection] );
		m_scintillaOriginal->SetText( m_arrOriginal[nSelection] );
		
		m_scintillaModified->SetReadOnly( true );
		m_scintillaOriginal->SetReadOnly( true );
	}
}

void udSynchronizeDialog::OnDeselectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkList->GetCount(); ++i )
	{
		m_checkList->Check( i, false );
	}
}

void udSynchronizeDialog::OnSelectAll(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkList->GetCount(); ++i )
	{
		m_checkList->Check( i, true );
	}
}

