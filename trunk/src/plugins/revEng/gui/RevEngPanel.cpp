#include "RevEngPanel.h"
#include "RevEng.h"

#include <wx/filename.h>

udRevEngPanel::udRevEngPanel( wxWindow *parent ) : _RevEngPanel( parent )
{
}

udRevEngPanel::~udRevEngPanel()
{
}

void udRevEngPanel::OnAddFilesClick(wxCommandEvent& event)
{
	wxFileDialog dlg( m_checkListFiles, wxT("Choose source files"), wxT(""), wxT(""), wxT("Source files (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		wxArrayString arrFiles;
		dlg.GetPaths( arrFiles );
		
		m_checkListFiles->Append( arrFiles );
	}
}

void udRevEngPanel::OnBeginDrag(wxTreeEvent& event)
{
}

void udRevEngPanel::OnCheckAllFilesClick(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListFiles->GetCount(); i++ ) m_checkListFiles->Check( i );
}

void udRevEngPanel::OnDeselectAllFilesClick(wxCommandEvent& event)
{
	m_checkListFiles->DeselectAll();
}

void udRevEngPanel::OnParseClick(wxCommandEvent& event)
{
	// get path to CTAGS utility
	wxString sCTAGS = IPluginManager::Get()->GetAppSettings().GetProperty( wxT("CTAGS path") )->AsString();
	
	if( sCTAGS.IsEmpty() )
	{
		wxMessageBox( wxT("Please, specify path to CTAGS utility in Reverse Engineering plugin's settings"), wxT("Reverse Engineering"), wxOK | wxICON_WARNING );
		return;
	}
	
	// run CTAGS
	wxString sOutFile = wxFileName::CreateTempFileName( wxT("cdreveng") );
	
	// construct CTAGS command
	wxString sCmd;
	wxArrayString arrFiles;
	
	GetCheckedFiles( arrFiles );
	
	sCmd = sCTAGS + wxT(" -f \"") + sOutFile + wxT("\"");
	if( !m_textIdentifiers->IsEmpty() ) sCmd += wxT(" -I \"") + m_textIdentifiers->GetValue() + wxT("\"");
	for( size_t i = 0; i < arrFiles.GetCount(); i++ ) sCmd += ( wxT(" \"") + arrFiles[i] + wxT("\"") );
	
	wxMessageBox( sCmd );

}

void udRevEngPanel::OnRemoveFilesClick(wxCommandEvent& event)
{
	wxArrayString arrFiles;
	GetSelectedFiles( arrFiles );
	
	for( size_t i = 0; i < arrFiles.GetCount(); i++ ) m_checkListFiles->Delete( m_checkListFiles->FindString( arrFiles[i] ) );
}

void udRevEngPanel::OnRightClick(wxTreeEvent& event)
{
}

void udRevEngPanel::OnSelectAllFilesClick(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListFiles->GetCount(); i++ ) m_checkListFiles->Select( i );
}

void udRevEngPanel::OnUncheckAllFilesClick(wxCommandEvent& event)
{
	for( size_t i = 0; i < m_checkListFiles->GetCount(); i++ ) m_checkListFiles->Check( i, false );
}

void udRevEngPanel::OnUpdateParse(wxUpdateUIEvent& event)
{
	wxArrayString arrFiles;
	GetCheckedFiles( arrFiles );
	
	event.Enable( !arrFiles.IsEmpty() );
}

void udRevEngPanel::OnUpdateRemoveFiles(wxUpdateUIEvent& event)
{
	wxArrayInt arrSelection;
	event.Enable( m_checkListFiles->GetSelections( arrSelection ) );
}

void udRevEngPanel::GetCheckedFiles(wxArrayString& files)
{
	files.Clear();
	
	for( size_t i = 0; i < m_checkListFiles->GetCount(); i++ )
	{
		if( m_checkListFiles->IsChecked( i ) ) files.Add( m_checkListFiles->GetString( i ) );
	}
}

void udRevEngPanel::GetSelectedFiles(wxArrayString& files)
{
	files.Clear();
	
	for( size_t i = 0; i < m_checkListFiles->GetCount(); i++ )
	{
		if( m_checkListFiles->IsSelected( i ) ) files.Add( m_checkListFiles->GetString( i ) );
	}
}

void udRevEngPanel::InitializeSymbolsTree()
{
	m_treeSymbols->DeleteAllItems();
	m_treeSymbols->SetImageList( IPluginManager::Get()->GetArt() );
	
	wxTreeItemId rootId = m_treeSymbols->AddRoot( wxT("Symbols") );
	
	m_treeIdClasses = m_treeSymbols->AppendItem( rootId, wxT("Classes"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
	m_treeIdFunctions = m_treeSymbols->AppendItem( rootId, wxT("Functions"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
	m_treeIdVariables = m_treeSymbols->AppendItem( rootId, wxT("Variables"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
}

