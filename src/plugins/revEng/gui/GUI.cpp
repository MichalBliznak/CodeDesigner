///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 16 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

#include "../res/project/ClassDiag.xpm"
#include "../res/project/SimpleStateChartDiag.xpm"
#include "res/gui/collapse.xpm"

///////////////////////////////////////////////////////////////////////////

_RevEngPanel::_RevEngPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetExtraStyle( wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( _RevEngPanel::m_splitterOnIdle ), NULL, this );
	
	m_panelFiles = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* panelSizerFiles;
	panelSizerFiles = new wxFlexGridSizer( 0, 1, 0, 0 );
	panelSizerFiles->AddGrowableCol( 0 );
	panelSizerFiles->AddGrowableRow( 2 );
	panelSizerFiles->SetFlexibleDirection( wxBOTH );
	panelSizerFiles->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( m_panelFiles, wxID_ANY, wxT("Choose source files:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	panelSizerFiles->Add( m_staticText1, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAddFiles = new wxButton( m_panelFiles, IDB_ADDFILES, wxT("Add files"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_buttonAddFiles, 1, wxALL, 5 );
	
	m_buttonRemoveFiles = new wxButton( m_panelFiles, IDB_REMOVEFILES, wxT("Remove selected"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_buttonRemoveFiles, 1, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	panelSizerFiles->Add( buttonSizer, 0, wxEXPAND, 5 );
	
	wxArrayString m_checkListFilesChoices;
	m_checkListFiles = new wxCheckListBox( m_panelFiles, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), m_checkListFilesChoices, wxLB_ALWAYS_SB|wxLB_MULTIPLE );
	m_checkListFiles->SetToolTip( wxT("Files to be parsed by CTAGS.") );
	m_checkListFiles->SetMinSize( wxSize( -1,100 ) );
	
	m_menuFiles = new wxMenu();
	wxMenuItem* menuFilesAdd;
	menuFilesAdd = new wxMenuItem( m_menuFiles, IDM_ADD_FILES, wxString( wxT("Add files") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesAdd );
	
	wxMenuItem* menuFilesRemoveAllFiles;
	menuFilesRemoveAllFiles = new wxMenuItem( m_menuFiles, wxID_ANY, wxString( wxT("Remove all files") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesRemoveAllFiles );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menuFiles->AppendSeparator();
	
	wxMenuItem* menuFilesSelectAll;
	menuFilesSelectAll = new wxMenuItem( m_menuFiles, IDM_FILES_SELECTALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesSelectAll );
	
	wxMenuItem* menuFilesDeselectAll;
	menuFilesDeselectAll = new wxMenuItem( m_menuFiles, IDM_FILES_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesDeselectAll );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menuFiles->AppendSeparator();
	
	wxMenuItem* menuFilesCheckAll;
	menuFilesCheckAll = new wxMenuItem( m_menuFiles, IDM_FILES_CHECKALL, wxString( wxT("Check all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesCheckAll );
	
	wxMenuItem* menuFilesUncheckAll;
	menuFilesUncheckAll = new wxMenuItem( m_menuFiles, IDM_FILES_UNCHECKALL, wxString( wxT("Uncheck all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFiles->Append( menuFilesUncheckAll );
	
	m_checkListFiles->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _RevEngPanel::m_checkListFilesOnContextMenu ), NULL, this ); 
	
	panelSizerFiles->Add( m_checkListFiles, 1, wxEXPAND|wxBOTTOM, 5 );
	
	m_staticText3 = new wxStaticText( m_panelFiles, wxID_ANY, wxT("Identifiers:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	panelSizerFiles->Add( m_staticText3, 0, wxALL, 5 );
	
	m_textIdentifiers = new wxTextCtrl( m_panelFiles, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,50 ), wxTE_MULTILINE );
	m_textIdentifiers->SetToolTip( wxT("Specifies a list of identifiers which are to be specially handled by CTAGS while parsing C and C++ source files.") );
	m_textIdentifiers->SetMinSize( wxSize( -1,50 ) );
	
	panelSizerFiles->Add( m_textIdentifiers, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_buttonParse = new wxButton( m_panelFiles, IDB_PARSE, wxT("Parse checked files"), wxDefaultPosition, wxDefaultSize, 0 );
	panelSizerFiles->Add( m_buttonParse, 1, wxALL|wxEXPAND, 5 );
	
	m_panelFiles->SetSizer( panelSizerFiles );
	m_panelFiles->Layout();
	panelSizerFiles->Fit( m_panelFiles );
	m_panelSymbols = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* panelSizerSymbols;
	panelSizerSymbols = new wxFlexGridSizer( 0, 1, 0, 0 );
	panelSizerSymbols->AddGrowableCol( 0 );
	panelSizerSymbols->AddGrowableRow( 2 );
	panelSizerSymbols->SetFlexibleDirection( wxBOTH );
	panelSizerSymbols->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( m_panelSymbols, wxID_ANY, wxT("Found symbols:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	panelSizerSymbols->Add( m_staticText2, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_toolBarSymbols = new wxToolBar( m_panelSymbols, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolBarSymbols->AddTool( IDT_SYMBOLS_EXPANDALL, wxT("Expand/Collapse All"), wxBitmap( collapse_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Expand/collapse all tree items"), wxEmptyString, NULL ); 
	
	m_toolBarSymbols->AddSeparator(); 
	
	m_toolBarSymbols->AddTool( IDT_SYMBOLS_CREATE_CLASSDIAG, wxT("Create class diagram"), wxBitmap( ClassDiag_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Create class diagram for all selected classes"), wxEmptyString, NULL ); 
	
	m_checkBoxMembers = new wxCheckBox( m_toolBarSymbols, wxID_ANY, wxT("Members "), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxMembers->SetToolTip( wxT("Create also class members") );
	
	m_toolBarSymbols->AddControl( m_checkBoxMembers );
	m_toolBarSymbols->AddSeparator(); 
	
	m_toolBarSymbols->AddTool( IDT_SYMBOLS_CREATE_STATECHART, wxT("Create state chart"), wxBitmap( SimpleStateChartDiag_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Create state charts for all listed functions"), wxEmptyString, NULL ); 
	
	m_toolBarSymbols->Realize(); 
	
	panelSizerSymbols->Add( m_toolBarSymbols, 0, wxEXPAND, 5 );
	
	m_treeSymbols = new wxTreeCtrl( m_panelSymbols, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), wxTR_DEFAULT_STYLE|wxTR_MULTIPLE );
	m_treeSymbols->SetMinSize( wxSize( -1,100 ) );
	
	m_menuSymbols = new wxMenu();
	wxMenuItem* menuSymbolsClassDiagram;
	menuSymbolsClassDiagram = new wxMenuItem( m_menuSymbols, IDM_SYMBOLS_CREATE_CLASSDIAG, wxString( wxT("Create class diagram") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSymbols->Append( menuSymbolsClassDiagram );
	
	wxMenuItem* menuSymbolsCreateStateChart;
	menuSymbolsCreateStateChart = new wxMenuItem( m_menuSymbols, IDM_SYMBOLS_CREATE_STATECHART, wxString( wxT("Create state chart") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSymbols->Append( menuSymbolsCreateStateChart );
	
	wxMenuItem* m_separator3;
	m_separator3 = m_menuSymbols->AppendSeparator();
	
	wxMenuItem* menuSymbolsRemoveAll;
	menuSymbolsRemoveAll = new wxMenuItem( m_menuSymbols, IDM_SYMBOLS_REMOVE_ALL, wxString( wxT("Remove all symbols") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSymbols->Append( menuSymbolsRemoveAll );
	
	m_treeSymbols->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _RevEngPanel::m_treeSymbolsOnContextMenu ), NULL, this ); 
	
	panelSizerSymbols->Add( m_treeSymbols, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	m_panelSymbols->SetSizer( panelSizerSymbols );
	m_panelSymbols->Layout();
	panelSizerSymbols->Fit( m_panelSymbols );
	m_splitter->SplitHorizontally( m_panelFiles, m_panelSymbols, 0 );
	mainSizer->Add( m_splitter, 1, wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	// Connect Events
	m_buttonAddFiles->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ), NULL, this );
	m_buttonRemoveFiles->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnRemoveFilesClick ), NULL, this );
	m_buttonRemoveFiles->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateRemoveFiles ), NULL, this );
	this->Connect( menuFilesAdd->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ) );
	this->Connect( menuFilesRemoveAllFiles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnRemoveAllFilesClick ) );
	this->Connect( menuFilesSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnSelectAllFilesClick ) );
	this->Connect( menuFilesDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnDeselectAllFilesClick ) );
	this->Connect( menuFilesCheckAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCheckAllFilesClick ) );
	this->Connect( menuFilesUncheckAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnUncheckAllFilesClick ) );
	m_buttonParse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnParseClick ), NULL, this );
	m_buttonParse->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateParse ), NULL, this );
	this->Connect( IDT_SYMBOLS_EXPANDALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnExpandTreeClick ) );
	this->Connect( IDT_SYMBOLS_CREATE_CLASSDIAG, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnCreateClassDiagClick ) );
	this->Connect( IDT_SYMBOLS_CREATE_STATECHART, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnCreateStateChartClick ) );
	this->Connect( menuSymbolsClassDiagram->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCreateClassDiagClick ) );
	this->Connect( menuSymbolsCreateStateChart->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCreateStateChartClick ) );
	this->Connect( menuSymbolsRemoveAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnRemoveAllSymbolsClick ) );
}

_RevEngPanel::~_RevEngPanel()
{
	// Disconnect Events
	m_buttonAddFiles->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ), NULL, this );
	m_buttonRemoveFiles->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnRemoveFilesClick ), NULL, this );
	m_buttonRemoveFiles->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateRemoveFiles ), NULL, this );
	this->Disconnect( IDM_ADD_FILES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnRemoveAllFilesClick ) );
	this->Disconnect( IDM_FILES_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnSelectAllFilesClick ) );
	this->Disconnect( IDM_FILES_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnDeselectAllFilesClick ) );
	this->Disconnect( IDM_FILES_CHECKALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCheckAllFilesClick ) );
	this->Disconnect( IDM_FILES_UNCHECKALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnUncheckAllFilesClick ) );
	m_buttonParse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnParseClick ), NULL, this );
	m_buttonParse->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateParse ), NULL, this );
	this->Disconnect( IDT_SYMBOLS_EXPANDALL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnExpandTreeClick ) );
	this->Disconnect( IDT_SYMBOLS_CREATE_CLASSDIAG, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnCreateClassDiagClick ) );
	this->Disconnect( IDT_SYMBOLS_CREATE_STATECHART, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _RevEngPanel::OnCreateStateChartClick ) );
	this->Disconnect( IDM_SYMBOLS_CREATE_CLASSDIAG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCreateClassDiagClick ) );
	this->Disconnect( IDM_SYMBOLS_CREATE_STATECHART, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCreateStateChartClick ) );
	this->Disconnect( IDM_SYMBOLS_REMOVE_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnRemoveAllSymbolsClick ) );
	
}
