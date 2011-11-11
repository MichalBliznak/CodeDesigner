#include "RevEngPanel.h"
#include "RevEng.h"

#include <wx/filename.h>
#include <wx/process.h>
#include <wx/txtstrm.h>

udRevEngPanel::udRevEngPanel( wxWindow *parent ) : _RevEngPanel( parent )
{
	m_fExpanded = false;
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
	wxArrayString arrOutput;
	
	/* CTAGS patters:
	 * command: --fields=+a+i+S+z+K --excmd=number --c-kinds=c
	 * output:
			MainApp	main.h	26;"	kind:class	inherits:wxApp
			MainFrame	main.h	39;"	kind:class	inherits:MainFrameBase
			MainFrameBase	gui.h	34;"	kind:class	inherits:wxFrame
	 * 
	 * command: --fields=+a+i+S+z+K --excmd=number --c-kinds=m
	 * output:
			m_gridData	gui.h	41;"	kind:member	class:MainFrameBase	access:protected
			m_menuBar	gui.h	39;"	kind:member	class:MainFrameBase	access:protected
			m_menuFile	gui.h	40;"	kind:member	class:MainFrameBase	access:protected
			m_statusBar	gui.h	42;"	kind:member	class:MainFrameBase	access:protected
	 * 
	 * command: --fields=+a+i+S+z+K --excmd=pattern --c-kinds=m
	 * output:
			m_gridData	gui.h	/^		wxGrid* m_gridData;$/;"	kind:member	class:MainFrameBase	access:protected
			m_menuBar	gui.h	/^		wxMenuBar* m_menuBar;$/;"	kind:member	class:MainFrameBase	access:protected
			m_menuFile	gui.h	/^		wxMenu* m_menuFile;$/;"	kind:member	class:MainFrameBase	access:protected
			m_statusBar	gui.h	/^		wxStatusBar* m_statusBar;$/;"	kind:member	class:MainFrameBase	access:protected

	 * command: --fields=+a+i+S+z+K --excmd=number --c-kinds=f
	 * output:
			MainFrame	main.cpp	38;"	kind:function	class:MainFrame	signature:(wxWindow *parent)
			MainFrameBase	gui.cpp	12;"	kind:function	class:MainFrameBase	signature:( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
			OnCloseFrame	gui.h	45;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCloseEvent& event )
			OnCloseFrame	main.cpp	52;"	kind:function	class:MainFrame	signature:(wxCloseEvent& event)
			OnExitClick	gui.h	46;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCommandEvent& event )
			OnExitClick	main.cpp	57;"	kind:function	class:MainFrame	signature:(wxCommandEvent& event)
			OnInit	main.cpp	25;"	kind:function	class:MainApp	signature:()
			~MainFrame	main.cpp	48;"	kind:function	class:MainFrame	signature:()
			~MainFrameBase	gui.cpp	66;"	kind:function	class:MainFrameBase	signature:()
	 *
	 * command: --fields=+a+i+S+z+K --excmd=pattern --c-kinds=f
	 * output:
			MainFrame	main.cpp	/^MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )$/;"	kind:function	class:MainFrame	signature:(wxWindow *parent)
			MainFrameBase	gui.cpp	/^MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )$/;"	kind:function	class:MainFrameBase	signature:( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
			OnCloseFrame	gui.h	/^		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }$/;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCloseEvent& event )
			OnCloseFrame	main.cpp	/^void MainFrame::OnCloseFrame(wxCloseEvent& event)$/;"	kind:function	class:MainFrame	signature:(wxCloseEvent& event)
			OnExitClick	gui.h	/^		virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }$/;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCommandEvent& event )
			OnExitClick	main.cpp	/^void MainFrame::OnExitClick(wxCommandEvent& event)$/;"	kind:function	class:MainFrame	signature:(wxCommandEvent& event)
			OnInit	main.cpp	/^bool MainApp::OnInit()$/;"	kind:function	class:MainApp	signature:()
			~MainFrame	main.cpp	/^MainFrame::~MainFrame()$/;"	kind:function	class:MainFrame	signature:()
			~MainFrameBase	gui.cpp	/^MainFrameBase::~MainFrameBase()$/;"	kind:function	class:MainFrameBase	signature:()
	 */
	
	InitializeSymbolsTree();
	
	//	get list of all classes
	int res = ExecCtags( wxT("--fields=+a+i+S+z+K --excmd=number"), arrOutput );
	if( res != 0 )
	{
		wxMessageBox( wxT("CTAGS utility failed. Please see the log window for more details."), wxT("Reverse Engineering"), wxOK | wxICON_ERROR );
		return;
	}
	
	ParseClasses( arrOutput );
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
	
	wxTreeItemId rootId = m_treeSymbols->AddRoot( wxT("Symbols"), IPluginManager::Get()->GetArtIndex( wxT("udRootItem") )  );
	
	m_treeIdClasses = m_treeSymbols->AppendItem( rootId, wxT("Classes"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
	m_treeIdFunctions = m_treeSymbols->AppendItem( rootId, wxT("Functions"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
	m_treeIdVariables = m_treeSymbols->AppendItem( rootId, wxT("Variables"), IPluginManager::Get()->GetArtIndex( wxT("udCodePackageItem") ) );
	
	m_treeSymbols->ExpandAll();
}

int udRevEngPanel::ExecCtags(const wxString& cmd, wxArrayString& output)
{
	// get path to CTAGS utility
	wxString sCTAGS = IPluginManager::Get()->GetAppSettings().GetProperty( wxT("CTAGS path") )->AsString();
	
	if( sCTAGS.IsEmpty() )
	{
		IPluginManager::Get()->Log( wxT("ERROR: Please, specify path to CTAGS utility in Reverse Engineering plugin's settings") );
		return -1;
	}
	
	// construct CTAGS command
	wxString sCmd;
	
	wxArrayString arrFiles;
	GetCheckedFiles( arrFiles );
	
	sCmd = sCTAGS + wxT(" -f - ") + cmd;;
	if( !m_textIdentifiers->IsEmpty() ) sCmd += wxT(" -I \"") + m_textIdentifiers->GetValue() + wxT("\"");
	for( size_t i = 0; i < arrFiles.GetCount(); i++ ) sCmd += ( wxT(" \"") + arrFiles[i] + wxT("\"") );
	
	// IPluginManager::Get()->Log( wxT("DEBUG: ") + sCmd );
	
	// run CTAGS
	output.Clear();
	
	wxProcess process;
	process.Redirect();
	
	int res = wxExecute( sCmd, wxEXEC_SYNC, &process);
	if( res == 0 )
	{
		wxInputStream *in = process.GetInputStream();
		if( in && in->IsOk() )
		{
			wxTextInputStream tin( *in );

			while( !in->Eof() )
			{
				wxString line = tin.ReadLine();
				if( !line.IsEmpty() ) output.Add( line );
			}
		}
	}
	else
	{
		IPluginManager::Get()->Log( wxString::Format(wxT("ERROR: CTAGS failed with return value %d."), res ) );
	}
	
	return res;
}

void udRevEngPanel::ParseClasses(const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxArrayString arrCtags;
	wxString name;
	
	// process classes
	for( size_t i = 0; i < ctags.GetCount(); i++ )
	{
		arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
		
		/* MainApp	main.h	26;"	kind:class	inherits:wxApp */
		
		if( FindTagValue( arrFields, wxT("kind") ) == wxT("class") )
		{
			ctagClass *item = new ctagClass();
			item->m_Name = arrFields[0].Trim();
			item->m_Inherits = FindTagValue( arrFields, wxT("inherits") );
			
			name = item->m_Name;
			if( !item->m_Inherits.IsEmpty() ) name += + wxT(" ( inherits ") + item->m_Inherits + wxT(" )");
			wxTreeItemId treeClass = m_treeSymbols->AppendItem( m_treeIdClasses, name, IPluginManager::Get()->GetArtIndex( wxT("umlClassItem") ), -1, item );
			
			// process class members
			
			int res = ExecCtags( wxT("--fields=+a+i+S+z+K --excmd=pattern"), arrCtags );
			if( res != 0 )
			{
				wxMessageBox( wxT("CTAGS utility failed. Please see the log window for more details."), wxT("Reverse Engineering"), wxOK | wxICON_ERROR );
				return;
			}
			
			ParseMembers( treeClass, arrCtags );
			
			// process class functions
			
			res = ExecCtags( wxT("--fields=+a+i+S+z+K --excmd=pattern"), arrCtags );
			if( res != 0 )
			{
				wxMessageBox( wxT("CTAGS utility failed. Please see the log window for more details."), wxT("Reverse Engineering"), wxOK | wxICON_ERROR );
				return;
			}
			
			ParseFunctions( treeClass, arrCtags );
		}
	}
	
	m_treeSymbols->Expand( m_treeIdClasses );
}

void udRevEngPanel::ParseFunctions(wxTreeItemId parent, const wxArrayString& ctags)
{
	wxArrayString arrFields;
	ctagClass *parentClass = (ctagClass*) m_treeSymbols->GetItemData( parent );
	
	if( parentClass )
	{
		// process classes
		for( size_t i = 0; i < ctags.GetCount(); i++ )
		{
			/* OnCloseFrame	gui.h	/^		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }$/;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCloseEvent& event ) */
			
			arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
			
			if( FindTagValue( arrFields, wxT("class") ) == parentClass->m_Name && FindTagValue( arrFields, wxT("kind") ) == wxT("function") )
			{
				ctagFunction *item = new ctagFunction();
				item->m_Name = arrFields[0].Trim();
				item->m_Access = FindTagValue( arrFields, wxT("access") );
				item->m_ParentClass = FindTagValue( arrFields, wxT("class") );
				item->m_Signature = FindTagValue( arrFields, wxT("signature") );
				
				m_treeSymbols->AppendItem( parent, item->m_Name + item->m_Signature, IPluginManager::Get()->GetArtIndex( wxT("udMemberFunctionItem") ), -1, item );
			}
		}
	}
}

void udRevEngPanel::ParseMembers(wxTreeItemId parent, const wxArrayString& ctags)
{	
	wxArrayString arrFields;
	ctagClass *parentClass = (ctagClass*) m_treeSymbols->GetItemData( parent );
	
	if( parentClass )
	{
		// process classes
		for( size_t i = 0; i < ctags.GetCount(); i++ )
		{
			/* m_gridData	gui.h	/^		wxGrid* m_gridData;$/;"	kind:member	class:MainFrameBase	access:protected */
			
			arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
			
			if( FindTagValue( arrFields, wxT("class") ) == parentClass->m_Name && FindTagValue( arrFields, wxT("kind") ) == wxT("member")  )
			{
				ctagMember *item = new ctagMember();
				item->m_Name = arrFields[0].Trim();
				item->m_Access = FindTagValue( arrFields, wxT("access") );
				item->m_ParentClass = FindTagValue( arrFields, wxT("class") );
				
				m_treeSymbols->AppendItem( parent, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("udMemberDataItem") ), -1, item );
			}
		}
	}
}

wxString udRevEngPanel::FindTagValue(const wxArrayString& items, const wxString& key)
{
	for( size_t i = 0; i < items.GetCount(); i++ )
	{
		if( items[i].Contains( key + wxT(":") ) ) return items[i].AfterFirst(':').Trim();
	}
	
	return wxEmptyString;
}

void udRevEngPanel::OnExpandTreeClick(wxCommandEvent& event)
{
	m_fExpanded = !m_fExpanded;
	if( m_fExpanded )
	{
		m_treeSymbols->ExpandAll();
	}
	else
		m_treeSymbols->CollapseAll();
}

void udRevEngPanel::OnRemoveAllFilesClick(wxCommandEvent& event)
{
	while( m_checkListFiles->GetCount() ) m_checkListFiles->Delete( 0 );
}

void udRevEngPanel::OnCreateClassDiagClick(wxCommandEvent& event)
{
}

void udRevEngPanel::OnCreateStateChartClick(wxCommandEvent& event)
{
}

