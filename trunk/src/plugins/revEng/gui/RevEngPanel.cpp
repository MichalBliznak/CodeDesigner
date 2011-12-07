#include "RevEngPanel.h"
#include "RevEng.h"
#include "projectbase/gui/ProgressDialog.h"

#include <wx/process.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>

udRevEngPanel::udRevEngPanel( wxWindow *parent ) : _RevEngPanel( parent )
{
	m_fExpanded = false;
	m_LangType = udCTAGS::ltUNKNOWN;
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

		size_t nPrevIndex = m_checkListFiles->GetCount();
		m_checkListFiles->Append( arrFiles );
		size_t nCurrIndex = m_checkListFiles->GetCount();

		for( size_t i = nPrevIndex; i < nCurrIndex; i++) m_checkListFiles->Check( i );
	}
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
	IPluginManager::Get()->ClearLog();
	
	// check files for programming language
	wxArrayString arrFiles;
	GetCheckedFiles( arrFiles );
	m_LangType = GetLanguageFromFiles( arrFiles );

	if( m_LangType == udCTAGS::ltUNKNOWN )
	{
		wxString exts = IPluginManager::Get()->GetAppSettings().GetProperty( wxT("C/C++ file extensions") )->AsString() + wxT(" ") +
						IPluginManager::Get()->GetAppSettings().GetProperty( wxT("Python file extensions") )->AsString();

		IPluginManager::Get()->Log( wxT("ERROR: Unable to determine programing language from source files. Known file extensions are:") +
									exts +
									wxT(". List of known file extensions can be changed via Reverse Engineering plugin settings. ") + 
									wxT("Moreover, just one programming language can be used at the time.") );
		
		wxMessageBox( wxT("Unable to determine programing language from source files. See the log window for more details."), wxT("Reverse Engineering"), wxOK | wxICON_ERROR );
		return;
	}

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
	int res = ExecCtags( wxT("--fields=+a+i+S+z+K --excmd=pattern"), arrOutput );
	if( res != 0 )
	{
		wxMessageBox( wxT("CTAGS utility failed. Please see the log window for more details."), wxT("Reverse Engineering"), wxOK | wxICON_ERROR );
		return;
	}

	ParseEnums( arrOutput );
	ParseClasses( arrOutput );
	ParseFunctions( arrOutput );
	ParseVariables( arrOutput );
	
	m_treeSymbols->Expand( m_treeIdClasses);
	m_treeSymbols->Expand( m_treeIdFunctions);
	m_treeSymbols->Expand( m_treeIdVariables);
}

void udRevEngPanel::OnRemoveFilesClick(wxCommandEvent& event)
{
	wxArrayString arrFiles;
	GetSelectedFiles( arrFiles );

	for( size_t i = 0; i < arrFiles.GetCount(); i++ ) m_checkListFiles->Delete( m_checkListFiles->FindString( arrFiles[i] ) );
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

void udRevEngPanel::GetSelectedTreeIds(udCTAGS::TYPE type, wxArrayTreeItemIds& items)
{
	// get selected tree items
	wxArrayTreeItemIds arrIds;

	if( m_treeSymbols->GetSelections( arrIds ) )
	{
		for( size_t i = 0; i < arrIds.GetCount(); i++ )
		{
			ctagClass *data = (ctagClass*) m_treeSymbols->GetItemData( arrIds[i] );
			if( data && data->m_Type == type ) items.Add( arrIds[i] );
		}
	}
}

void udRevEngPanel::GetMemberIds(udCTAGS::TYPE type, wxTreeItemId classId, wxArrayTreeItemIds& items)
{
	items.Clear();

	wxTreeItemIdValue cookie;

	wxTreeItemId treeChild = m_treeSymbols->GetFirstChild( classId, cookie );
	while( treeChild.IsOk() )
	{
		udCTAGS *ctag = (udCTAGS*) m_treeSymbols->GetItemData( treeChild );
		if( ctag && ctag->m_Type == type ) items.Add( treeChild );

		treeChild = m_treeSymbols->GetNextChild( classId, cookie );
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
	
	if( sCTAGS == wxT("<built-in>") )
	{
		#ifdef __WXMSW__
		sCTAGS = IPluginManager::Get()->GetAppPath() + wxT("ctags.exe");
		#else
		sCTAGS = IPluginManager::Get()->GetAppPath() + wxT("ctags");
		#endif
	}

	if( ! wxFileExists(sCTAGS) )
	{
		IPluginManager::Get()->Log( wxT("ERROR: Unable to find CTAGS under path ") + sCTAGS );
		IPluginManager::Get()->Log( wxT("ERROR: Please, specify correct path to CTAGS utility in Reverse Engineering plugin's settings") );
		return -1;
	}

	// construct CTAGS command
	wxString sCmd;

	wxArrayString arrFiles;
	GetCheckedFiles( arrFiles );

	sCmd = sCTAGS + wxT(" -f - ") + cmd;
	if( !m_textIdentifiers->IsEmpty() ) sCmd += wxT(" -I \"") + m_textIdentifiers->GetValue() + wxT("\"");
	for( size_t i = 0;
	        i < arrFiles.GetCount();
	        i++ ) sCmd += ( wxT(" \"") + arrFiles[i] + wxT("\"") );

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
	wxString name;
	
	udProgressDialog progressDlg( NULL );
	
	progressDlg.SetLabel( wxT("Parsing classes...") );
	progressDlg.Clear();

	progressDlg.Show();
	progressDlg.Raise();

	// process classes
	for( size_t i = 0; i < ctags.GetCount(); i++ )
	{
		arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );

		/* MainApp	main.h	26;"	kind:class	inherits:wxApp
		   SharedClass	test.cpp	/^		class SharedClass$/;"	kind:class	class:StaticData::InnerClass	file:	access:public */

		if( FindTagValue( arrFields, wxT("kind") ) == wxT("class") )
		{
			ctagClass *item = new ctagClass();
			item->m_Name = arrFields[0].Trim();
			if( m_LangType == udCTAGS::ltCPP )
			{
				item->m_Inherits = FindTagValue( arrFields, wxT("inherits") ).AfterLast( ':' );
			}
			else if( m_LangType == udCTAGS::ltPYTHON )
			{
				item->m_Inherits = FindTagValue( arrFields, wxT("inherits") ).AfterLast( '.' );
			}
			item->m_Namespace = FindTagValue( arrFields, wxT("class") );
			item->m_Access = FindTagValue( arrFields, wxT("access") );
			item->m_Pattern = FindTagPattern( ctags[i] );

			progressDlg.SetLabel( wxString::Format( wxT("Parsing classes... %s"), item->m_Name.c_str() ) );
			progressDlg.Pulse();
			
			name = item->m_Name;
			if( !item->m_Inherits.IsEmpty() ) name += wxT(" : ") + item->m_Inherits;
			wxTreeItemId treeClass = m_treeSymbols->AppendItem( m_treeIdClasses, name, IPluginManager::Get()->GetArtIndex( wxT("umlClassItem") ), -1, item );

			// process class members
			ParseMemberData( treeClass, ctags );

			// process class functions
			ParseMemberFunctions( treeClass, ctags );
		}
	}

	//m_treeSymbols->Expand( m_treeIdClasses );
}

void udRevEngPanel::ParseMemberFunctions(wxTreeItemId parent, const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString parentName;
	
	ctagClass *parentClass = (ctagClass*) m_treeSymbols->GetItemData( parent );

	if( parentClass && parentClass->m_Type == udCTAGS::ttCLASS )
	{
		// process classes
		for( size_t i = 0; i < ctags.GetCount(); i++ )
		{
			/* OnCloseFrame	gui.h	/^		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }$/;"	kind:function	class:MainFrameBase	access:protected	signature:( wxCloseEvent& event ) 
			   foo	test.cpp	/^			void foo() {;}$/;"	kind:function	class:StaticData::InnerClass::SharedClass	access:public	signature:() */

			arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
			
			if( !parentClass->m_Namespace.IsEmpty() ) parentName = parentClass->m_Namespace + wxT("::") + parentClass->m_Name;
			else
				parentName = parentClass->m_Name;

			if( FindTagValue( arrFields, wxT("class") ) == parentName && 
				( ( ( m_LangType == udCTAGS::ltCPP ) && ( FindTagValue( arrFields, wxT("kind") ) == wxT("function") ) ) ||
				  ( ( m_LangType == udCTAGS::ltPYTHON ) && ( FindTagValue( arrFields, wxT("kind") ) == wxT("member") ) ) ) )
			{
				ctagClassFunction *item = new ctagClassFunction();
				item->m_Name = arrFields[0].Trim();
				item->m_File = arrFields[1];
				item->m_Access = FindTagValue( arrFields, wxT("access") );
				item->m_ParentClass = FindTagValue( arrFields, wxT("class") );
				item->m_Signature = FindTagValue( arrFields, wxT("signature") );
				item->m_Pattern = FindTagPattern( ctags[i] );
				
				ParseFunctionBody( item );

				m_treeSymbols->AppendItem( parent, item->m_Name + item->m_Signature, IPluginManager::Get()->GetArtIndex( wxT("udMemberFunctionItem") ), -1, item );
			}
		}
	}
}

void udRevEngPanel::ParseMemberData(wxTreeItemId parent, const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString parentName;
	
	ctagClass *parentClass = (ctagClass*) m_treeSymbols->GetItemData( parent );

	if( parentClass && parentClass->m_Type == udCTAGS::ttCLASS )
	{
		// process classes
		for( size_t i = 0; i < ctags.GetCount(); i++ )
		{
			/* m_gridData	gui.h	/^		wxGrid* m_gridData;$/;"	kind:member	class:MainFrameBase	access:protected */

			arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
			
			if( !parentClass->m_Namespace.IsEmpty() ) parentName = parentClass->m_Namespace + wxT("::") + parentClass->m_Name;
			else
				parentName = parentClass->m_Name;

			if( FindTagValue( arrFields, wxT("class") ) == parentName && 
				( ( ( m_LangType == udCTAGS::ltCPP ) && ( FindTagValue( arrFields, wxT("kind") ) == wxT("member") ) ) ||
				  ( ( m_LangType == udCTAGS::ltPYTHON ) && ( FindTagValue( arrFields, wxT("kind") ) == wxT("variable") ) ) ) )
			{
				ctagClassMember *item = new ctagClassMember();
				item->m_Name = arrFields[0].Trim();
				item->m_Access = FindTagValue( arrFields, wxT("access") );
				item->m_ParentClass = FindTagValue( arrFields, wxT("class") );
				item->m_Pattern = FindTagPattern( ctags[i] );

				m_treeSymbols->AppendItem( parent, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("udMemberDataItem") ), -1, item );
			}
		}
	}
}

void udRevEngPanel::ParseEnums(const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString name;
	
	udProgressDialog progressDlg( NULL );
	
	progressDlg.SetLabel( wxT("Parsing enums...") );
	progressDlg.Clear();

	progressDlg.Show();
	progressDlg.Raise();

	// process classes
	for( size_t i = 0; i < ctags.GetCount(); i++ )
	{
		arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );

		/* InnerEnum	test.cpp	/^	enum InnerEnum$/;"	kind:enum	class:Data	file:	access:public */

		if( FindTagValue( arrFields, wxT("kind") ) == wxT("enum") )
		{
			ctagEnum *item = new ctagEnum();
			item->m_Name = arrFields[0].Trim();
			item->m_Namespace = FindTagValue( arrFields, wxT("class") );
			item->m_Access = FindTagValue( arrFields, wxT("access") );
			item->m_Pattern = FindTagPattern( ctags[i] );
			
			progressDlg.SetLabel( wxString::Format( wxT("Parsing enums... %s"), item->m_Name.c_str() ) );
			progressDlg.Pulse();

			wxTreeItemId treeEnum = m_treeSymbols->AppendItem( m_treeIdClasses, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("umlEnumItem") ), -1, item );

			// process enum items
			ParseEnumItems( treeEnum, ctags );
		}
	}

	//m_treeSymbols->Expand( m_treeIdClasses );
}

void udRevEngPanel::ParseEnumItems(wxTreeItemId parent, const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString parentName;
	
	ctagEnum *parentEnum = (ctagEnum*) m_treeSymbols->GetItemData( parent );

	if( parentEnum && parentEnum->m_Type == udCTAGS::ttENUM )
	{
		// process classes
		for( size_t i = 0; i < ctags.GetCount(); i++ )
		{
			/* itemONE	test.cpp	/^		itemONE,$/;"	kind:enumerator	enum:Data::InnerEnum	file: */

			arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );
			
			if( !parentEnum->m_Namespace.IsEmpty() ) parentName = parentEnum->m_Namespace + wxT("::") + parentEnum->m_Name;
			else
				parentName = parentEnum->m_Name;

			if( FindTagValue( arrFields, wxT("enum") ) == parentName && 
				FindTagValue( arrFields, wxT("kind") ) == wxT("enumerator") ) 
			{
				ctagEnumItem *item = new ctagEnumItem();
				item->m_Name = arrFields[0].Trim();
				item->m_ParentEnum = FindTagValue( arrFields, wxT("enum") );
				item->m_Pattern = FindTagPattern( ctags[i] );
				
				// parse item value
				if( item->m_Pattern.Contains( wxT("=") ) )
				{
					item->m_Value = item->m_Pattern.AfterLast( '=' ).Trim().Trim(false);
					item->m_Value.Replace( wxT(","), wxT("") );
				}

				m_treeSymbols->AppendItem( parent, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("udEnumValueItem") ), -1, item );
			}
		}
	}
}

void udRevEngPanel::ParseFunctions(const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString name;
	
	udProgressDialog progressDlg( NULL );
	
	progressDlg.SetLabel( wxT("Parsing global functions...") );
	progressDlg.Clear();

	progressDlg.Show();
	progressDlg.Raise();

	// process classes
	for( size_t i = 0; i < ctags.GetCount(); i++ )
	{
		arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );

		/* GlobalFunction	test.cpp	/^int GlobalFunction( int n )$/;"	kind:function	signature:( int n )
		   GlobalFunction	wxFBTest.py	/^def GlobalFunction(n):$/;"	kind:function	access:public */

		if( FindTagValue( arrFields, wxT("kind") ) == wxT("function") && 
			FindTagValue( arrFields, wxT("class") ) == wxEmptyString )
		{
			ctagFunction *item = new ctagFunction();
			item->m_Name = arrFields[0].Trim();
			item->m_File = arrFields[1];
			item->m_Pattern = FindTagPattern( ctags[i] );
			item->m_Signature = FindTagValue( arrFields, wxT("signature") );
			
			if( m_LangType == udCTAGS::ltPYTHON && item->m_Signature.IsEmpty() )
			{
				item->m_Signature = wxT("(") + item->m_Pattern.AfterLast( wxT('(') );
				item->m_Signature.Truncate( item->m_Signature.Len() + 1 );
			}
			
			progressDlg.SetLabel( wxString::Format( wxT("Parsing global functions... %s"), item->m_Name.c_str() ) );
			progressDlg.Pulse();
			
			ParseFunctionBody( item );

			m_treeSymbols->AppendItem( m_treeIdFunctions, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("udGenericFunctionItem") ), -1, item );;
		}
	}

	//m_treeSymbols->Expand( m_treeIdFunctions);
}

void udRevEngPanel::ParseVariables(const wxArrayString& ctags)
{
	wxArrayString arrFields;
	wxString name;
	
	udProgressDialog progressDlg( NULL );
	
	progressDlg.SetLabel( wxT("Parsing global variables...") );
	progressDlg.Clear();

	progressDlg.Show();
	progressDlg.Raise();

	// process classes
	for( size_t i = 0; i < ctags.GetCount(); i++ )
	{
		arrFields = wxStringTokenize( ctags[i], wxT("\t"), wxTOKEN_STRTOK );

		/* GlobalVarible	test.cpp	/^static int GlobalVarible = 10;$/;"	kind:variable	file: */

		if( FindTagValue( arrFields, wxT("kind") ) == wxT("variable") && 
			FindTagValue( arrFields, wxT("class") ) == wxEmptyString )
		{
			ctagVariable *item = new ctagVariable();
			item->m_Name = arrFields[0].Trim();
			item->m_Pattern = FindTagPattern( ctags[i] );
			
			progressDlg.SetLabel( wxString::Format( wxT("Parsing global variables... %s"), item->m_Name.c_str() ) );
			progressDlg.Pulse();

			m_treeSymbols->AppendItem( m_treeIdVariables, item->m_Name, IPluginManager::Get()->GetArtIndex( wxT("udGenericVariableItem") ), -1, item );;
		}
	}

	//m_treeSymbols->Expand( m_treeIdFunctions);
}

void udRevEngPanel::ParseFunctionBody(ctagFunction* ctag)
{
	if( wxFileExists( ctag->m_File ) )
	{
		wxFileInputStream in( ctag->m_File );
		if( in.IsOk() )
		{
			wxString sFileContent;
			wxChar c;
			
			// read whole file to string
			wxTextInputStream tin( in );
			while( !in.Eof() ) sFileContent += ( tin.ReadLine() + wxT("\n") );
			
			int fcnpos = sFileContent.Find( ctag->m_Pattern );
			if( fcnpos != wxNOT_FOUND )
			{
				if( m_LangType == udCTAGS::ltCPP )
				{
					int nBraceCnt = 0;
					bool fFirstChar = true;
					
					while( fcnpos < (int) sFileContent.Len() )
					{
						c = sFileContent[ fcnpos++ ];
						
						if( c == wxT('{') )
						{
							nBraceCnt++;
							if( nBraceCnt > 1 ) ctag->m_Content += c;
						}
						else if( nBraceCnt )
						{
							if( c == wxT('}') )
							{
								if( --nBraceCnt == 0 ) break;
								else
									ctag->m_Content += c;
							}
							else
							{
								if( c != wxT('\n') || !fFirstChar ) ctag->m_Content += c;
								fFirstChar = false;
							}
						}
					}
				}
				else if( m_LangType == udCTAGS::ltPYTHON )
				{
					int nIndentWidth = 0;
					int nIndent = 0;
					bool fFirstLine = false;
					bool fInside = false;
					bool fNewLine = false;
					
					while( fcnpos < (int) sFileContent.Len() )
					{
						c = sFileContent[ fcnpos++ ];
						
						if( !fInside && !fFirstLine && c == wxT('\n') )
						{
							fFirstLine = true;
						}
						else if( fFirstLine )
						{
							if( fNewLine )
							{
								if( c == wxT(' ') || c == wxT('\t') )
								{
									nIndentWidth++;
								}
								else
								{
									ctag->m_Content += c;
									fNewLine = false;
								}
							}
							else 
							{
								ctag->m_Content += c;
								if( c == wxT('\n') )
								{
									fFirstLine = false;
									fInside = true;
								}
							}
						}
						else if( fInside )
						{
							if( fNewLine )
							{
								if( nIndent >= nIndentWidth )
								{
									ctag->m_Content += c;
									if( c != wxT('\n') ) fNewLine = false;
								}
								else if( c == wxT(' ') || c == wxT('\t') )
								{
									nIndent++;
								}
								else
									break;
							}
							else
								ctag->m_Content += c;
						}
						
						if( c == wxT('\n') )
						{
							fNewLine = true;
							nIndent = 0;
						}
					}
				}
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

wxString udRevEngPanel::FindTagPattern(const wxString& ctag)
{
	int start = ctag.Find( wxT("/^") );
	int end = ctag.Find( wxT("$/") );

	if( start != wxNOT_FOUND && end != wxNOT_FOUND )
	{
		wxString pattern = ctag.Mid( start, end - start );
		pattern.Replace( wxT("/^"), wxT("") );
		if( pattern.EndsWith( wxT(";") ) ) pattern.Truncate( pattern.Len() - 1);
		pattern.Trim().Trim(false);

		return pattern;
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

void udRevEngPanel::OnImportSymbolsClick(wxCommandEvent& event)
{
	wxArrayTreeItemIds arrItems;
	wxSFAutoLayout layout;
	int cnt = 0;
	
	IPluginManager::Get()->ClearLog();
	m_mapProjectItems.clear();
		
	udProgressDialog progressDlg( NULL );
	
	IProject *proj = IPluginManager::Get()->GetProject();

	IPluginManager::Get()->Log( wxT("Starting reverse code engineering...") );
	
	// create diagram package
	udProjectItem *package = proj->CreateProjectItem( wxT("udPackageItem"), proj->GetRootItem()->GetId(), udfUNIQUE_NAME );
	if( package )
	{
		// create class diagram
		udClassDiagramItem *diag = (udClassDiagramItem*) proj->CreateProjectItem( wxT("udClassDiagramItem"), package->GetId(), udfUNIQUE_NAME );
		if( diag )
		{
			GetSelectedTreeIds( udCTAGS::ttCLASS, arrItems );
			if( !arrItems.IsEmpty() )
			{
				cnt += arrItems.GetCount();
				
				progressDlg.SetLabel( wxT("Importing classes...") );
				progressDlg.Clear();
				progressDlg.SetStepCount( arrItems.GetCount() * 3 );
			
				progressDlg.Show();
				progressDlg.Raise();

				// create classes
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					umlClassItem *classShape = CreateClassElement( arrItems[i] );
					if( classShape ) diag->GetDiagramManager().AddShape( classShape, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );
					progressDlg.Step();
				}

				// create inheritance
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					CreateClassAssociations( diag, arrItems[i] );
					progressDlg.Step();
				}

				// create associations
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					CreateMemberAssociations( diag, arrItems[i] );
					progressDlg.Step();
				}
			}
			
			arrItems.Clear();
			
			GetSelectedTreeIds( udCTAGS::ttENUM, arrItems );
			if( !arrItems.IsEmpty() )
			{
				cnt += arrItems.GetCount();
				
				progressDlg.SetLabel( wxT("Importing enums...") );
				progressDlg.Clear();
				progressDlg.SetStepCount( arrItems.GetCount() * 3 );
			
				if( ! progressDlg.IsShown() )
				{
					progressDlg.Show();
					progressDlg.Raise();
				}
				
				// create enums
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					umlEnumItem *enumShape = CreateEnumElement( arrItems[i] );
					if( enumShape ) diag->GetDiagramManager().AddShape( enumShape, NULL, wxDefaultPosition, sfINITIALIZE, sfDONT_SAVE_STATE );
					progressDlg.Step();
				}

				// create inheritance
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					CreateEnumAssociations( diag, arrItems[i] );
					progressDlg.Step();
				}
			}
			
			arrItems.Clear();
			
			GetSelectedTreeIds( udCTAGS::ttFUNCTION, arrItems );
			if( !arrItems.IsEmpty() )
			{
				cnt += arrItems.GetCount();
				
				progressDlg.SetLabel( wxT("Importing functions...") );
				progressDlg.Clear();
				progressDlg.SetStepCount( arrItems.GetCount() );
			
				if( ! progressDlg.IsShown() )
				{
					progressDlg.Show();
					progressDlg.Raise();
				}
				
				// create functions
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					CreateFunctions( arrItems[i] );
					progressDlg.Step();
				}
			}
			
			arrItems.Clear();
			
			GetSelectedTreeIds( udCTAGS::ttVARIABLE, arrItems );
			if( !arrItems.IsEmpty() )
			{
				cnt += arrItems.GetCount();
				
				progressDlg.SetLabel( wxT("Importing variables...") );
				progressDlg.Clear();
				progressDlg.SetStepCount( arrItems.GetCount() );
			
				if( ! progressDlg.IsShown() )
				{
					progressDlg.Show();
					progressDlg.Raise();
				}
				
				// create functions
				for( size_t i = 0; i < arrItems.GetCount(); i++ )
				{
					CreateVariables( arrItems[i] );
					progressDlg.Step();
				}
			}

			// layout diagram
			layout.Layout( diag->GetDiagramManager(), wxT("Vertical Tree") );
			
			progressDlg.SetLabel( wxT("Updating project...") );

			// update project structure tree
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, (udProjectItem*) proj->GetRootItem() );//, NULL, wxEmptyString, udfDELAYED );
					
			if( cnt == 0 )
			{
				IPluginManager::Get()->Log( wxT("Done.") );
				wxMessageBox( wxT("Select symbols to be processed."), wxT("Reverse Engineering"), wxOK | wxICON_WARNING );
			}
			else
			{
				IPluginManager::Get()->Log( wxString::Format( wxT("Number of symbols: %d"), cnt ) );
				IPluginManager::Get()->Log( wxT("WARNING: Manual check of parsed project items is strongly recommended due to possible simplifications done during the import process.") );
			}
		}
	}
}

void udRevEngPanel::OnRemoveAllSymbolsClick(wxCommandEvent& event)
{
	InitializeSymbolsTree();
}

udCTAGS::LANGTYPE udRevEngPanel::GetLanguageFromFiles(const wxArrayString& files)
{
	size_t cntCPP = 0;
	size_t cntPY = 0;
	size_t cntUNK = 0;
	
	wxArrayString arrCPPExts = wxStringTokenize( IPluginManager::Get()->GetAppSettings().GetProperty( wxT("C/C++ file extensions") )->AsString(), wxT(" ") );
	wxArrayString arrPyExts = wxStringTokenize( IPluginManager::Get()->GetAppSettings().GetProperty( wxT("Python file extensions") )->AsString(), wxT(" ") );

	if( !files.IsEmpty() )
	{
		for( size_t i = 0; i < files.GetCount(); i++ )
		{
			if( arrCPPExts.Index( files[i].AfterLast('.') ) != wxNOT_FOUND ) cntCPP++;
			else if( arrPyExts.Index( files[i].AfterLast('.') ) != wxNOT_FOUND ) cntPY++;
			else cntUNK++;
		}
		
		if( cntUNK ) return udCTAGS::ltUNKNOWN;
		if( cntCPP && !cntPY) return udCTAGS::ltCPP;
		if( cntPY && !cntCPP) return udCTAGS::ltPYTHON;
	}

	return udCTAGS::ltUNKNOWN;
}
