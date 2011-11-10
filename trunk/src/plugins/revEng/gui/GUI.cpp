///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  8 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

_RevEngPanel::_RevEngPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetExtraStyle( wxWS_EX_BLOCK_EVENTS );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Choose source files:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	mainSizer->Add( m_staticText1, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonAddFiles = new wxButton( this, IDB_ADDFILES, wxT("Add files"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_buttonAddFiles, 1, wxALL, 5 );
	
	m_buttonRemoveFiles = new wxButton( this, IDB_REMOVEFILES, wxT("Remove selected"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonSizer->Add( m_buttonRemoveFiles, 1, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	mainSizer->Add( buttonSizer, 0, wxEXPAND, 5 );
	
	wxArrayString m_checkListFilesChoices;
	m_checkListFiles = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,250 ), m_checkListFilesChoices, wxLB_ALWAYS_SB|wxLB_MULTIPLE );
	m_checkListFiles->SetToolTip( wxT("Files to be parsed by CTAGS.") );
	m_checkListFiles->SetMaxSize( wxSize( -1,250 ) );
	
	m_menuFiles = new wxMenu();
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
	
	mainSizer->Add( m_checkListFiles, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Identifiers:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	mainSizer->Add( m_staticText3, 0, wxALL, 5 );
	
	m_textIdentifiers = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,50 ), wxTE_MULTILINE );
	m_textIdentifiers->SetToolTip( wxT("Specifies a list of identifiers which are to be specially handled by CTAGS while parsing C and C++ source files.") );
	m_textIdentifiers->SetMinSize( wxSize( -1,50 ) );
	
	mainSizer->Add( m_textIdentifiers, 0, wxEXPAND|wxBOTTOM, 5 );
	
	m_buttonParse = new wxButton( this, IDB_PARSE, wxT("Parse checked files"), wxDefaultPosition, wxDefaultSize, 0 );
	mainSizer->Add( m_buttonParse, 0, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	mainSizer->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Found symbols:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	mainSizer->Add( m_staticText2, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_treeSymbols = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxTR_LINES_AT_ROOT );
	mainSizer->Add( m_treeSymbols, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	// Connect Events
	m_buttonAddFiles->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ), NULL, this );
	m_buttonRemoveFiles->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnRemoveFilesClick ), NULL, this );
	m_buttonRemoveFiles->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateRemoveFiles ), NULL, this );
	this->Connect( menuFilesSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnSelectAllFilesClick ) );
	this->Connect( menuFilesDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnDeselectAllFilesClick ) );
	this->Connect( menuFilesCheckAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCheckAllFilesClick ) );
	this->Connect( menuFilesUncheckAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnUncheckAllFilesClick ) );
	m_buttonParse->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnParseClick ), NULL, this );
	m_buttonParse->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateParse ), NULL, this );
	m_treeSymbols->Connect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( _RevEngPanel::OnBeginDrag ), NULL, this );
	m_treeSymbols->Connect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( _RevEngPanel::OnRightClick ), NULL, this );
}

_RevEngPanel::~_RevEngPanel()
{
	// Disconnect Events
	m_buttonAddFiles->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnAddFilesClick ), NULL, this );
	m_buttonRemoveFiles->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnRemoveFilesClick ), NULL, this );
	m_buttonRemoveFiles->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateRemoveFiles ), NULL, this );
	this->Disconnect( IDM_FILES_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnSelectAllFilesClick ) );
	this->Disconnect( IDM_FILES_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnDeselectAllFilesClick ) );
	this->Disconnect( IDM_FILES_CHECKALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnCheckAllFilesClick ) );
	this->Disconnect( IDM_FILES_UNCHECKALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _RevEngPanel::OnUncheckAllFilesClick ) );
	m_buttonParse->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _RevEngPanel::OnParseClick ), NULL, this );
	m_buttonParse->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _RevEngPanel::OnUpdateParse ), NULL, this );
	m_treeSymbols->Disconnect( wxEVT_COMMAND_TREE_BEGIN_DRAG, wxTreeEventHandler( _RevEngPanel::OnBeginDrag ), NULL, this );
	m_treeSymbols->Disconnect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( _RevEngPanel::OnRightClick ), NULL, this );
	
	delete m_menuFiles; 
}
