///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_pch.h"

#include "GUI.h"

#include "res/gui/Zoom100.xpm"
#include "res/gui/Zoom100Dis.xpm"
#include "res/gui/ZoomAll.xpm"
#include "res/gui/ZoomAllDis.xpm"
#include "res/gui/actionrun.xpm"
#include "res/gui/collapse.xpm"
#include "res/gui/configure.xpm"
#include "res/gui/editcopy.xpm"
#include "res/gui/editcut.xpm"
#include "res/gui/editpaste.xpm"
#include "res/gui/exit.xpm"
#include "res/gui/filenew.xpm"
#include "res/gui/fileopen.xpm"
#include "res/gui/filepreview.xpm"
#include "res/gui/fileprint.xpm"
#include "res/gui/filesave.xpm"
#include "res/gui/form_blue.xpm"
#include "res/gui/helpindex.xpm"
#include "res/gui/link_editor.xpm"
#include "res/gui/organisation.xpm"
#include "res/gui/redo.xpm"
#include "res/gui/spellcheck.xpm"
#include "res/gui/undo.xpm"
#include "res/project/Function.xpm"
#include "res/project/Variable.xpm"
#include "res/project/cube_green.xpm"
#include "res/project/cube_yellow.xpm"

///////////////////////////////////////////////////////////////////////////

_MainFrame::_MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	mbar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* menuFileNew;
	menuFileNew = new wxMenuItem( fileMenu, wxID_NEW, wxString( wxT("&New project") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFileNew->SetBitmaps( wxBitmap( filenew_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFileNew->SetBitmap( wxBitmap( filenew_xpm ) );
	#endif
	fileMenu->Append( menuFileNew );
	
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( fileMenu, wxID_OPEN, wxString( wxT("&Open project...") ) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFileOpen->SetBitmaps( wxBitmap( fileopen_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFileOpen->SetBitmap( wxBitmap( fileopen_xpm ) );
	#endif
	fileMenu->Append( menuFileOpen );
	
	wxMenuItem* menuFileSave;
	menuFileSave = new wxMenuItem( fileMenu, wxID_SAVE, wxString( wxT("Save") ) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFileSave->SetBitmaps( wxBitmap( filesave_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFileSave->SetBitmap( wxBitmap( filesave_xpm ) );
	#endif
	fileMenu->Append( menuFileSave );
	
	wxMenuItem* menuFileSaveAs;
	menuFileSaveAs = new wxMenuItem( fileMenu, wxID_SAVEAS, wxString( wxT("&Save project as...") ) + wxT('\t') + wxT("Ctrl+Shift+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFileSaveAs->SetBitmaps( wxBitmap( filesave_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFileSaveAs->SetBitmap( wxBitmap( filesave_xpm ) );
	#endif
	fileMenu->Append( menuFileSaveAs );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileExportBMP;
	menuFileExportBMP = new wxMenuItem( fileMenu, IDM_FILE_EXPORT, wxString( wxT("Export diagram to image...") ) , wxT("Export active diagram to BMP file"), wxITEM_NORMAL );
	fileMenu->Append( menuFileExportBMP );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFilePrint;
	menuFilePrint = new wxMenuItem( fileMenu, wxID_PRINT, wxString( wxT("&Print...") ) + wxT('\t') + wxT("Ctrl+P"), wxT("Print active diagram"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFilePrint->SetBitmaps( wxBitmap( fileprint_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFilePrint->SetBitmap( wxBitmap( fileprint_xpm ) );
	#endif
	fileMenu->Append( menuFilePrint );
	
	wxMenuItem* menuFilePreview;
	menuFilePreview = new wxMenuItem( fileMenu, wxID_PREVIEW, wxString( wxT("Preview...") ) + wxT('\t') + wxT("Alt+P"), wxT("Preview active diagram"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFilePreview->SetBitmaps( wxBitmap( filepreview_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFilePreview->SetBitmap( wxBitmap( filepreview_xpm ) );
	#endif
	fileMenu->Append( menuFilePreview );
	
	wxMenuItem* menuFilePageSetup;
	menuFilePageSetup = new wxMenuItem( fileMenu, wxID_PAGE_SETUP, wxString( wxT("Page setup...") ) , wxT("Set page properties"), wxITEM_NORMAL );
	fileMenu->Append( menuFilePageSetup );
	
	fileMenu->AppendSeparator();
	
	recentFilesMenu = new wxMenu();
	wxMenuItem* recentFilesMenuItem = new wxMenuItem( fileMenu, wxID_ANY, wxT("Recent projects"), wxEmptyString, wxITEM_NORMAL, recentFilesMenu );
	fileMenu->Append( recentFilesMenuItem );
	
	fileMenu->AppendSeparator();
	
	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, wxID_EXIT, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuFileQuit->SetBitmaps( wxBitmap( exit_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuFileQuit->SetBitmap( wxBitmap( exit_xpm ) );
	#endif
	fileMenu->Append( menuFileQuit );
	
	mbar->Append( fileMenu, wxT("&File") ); 
	
	editMenu = new wxMenu();
	wxMenuItem* menuEditUndo;
	menuEditUndo = new wxMenuItem( editMenu, wxID_UNDO, wxString( wxT("&Undo") ) + wxT('\t') + wxT("Ctrl+Z"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditUndo->SetBitmaps( wxBitmap( undo_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditUndo->SetBitmap( wxBitmap( undo_xpm ) );
	#endif
	editMenu->Append( menuEditUndo );
	
	wxMenuItem* menuEditRedo;
	menuEditRedo = new wxMenuItem( editMenu, wxID_REDO, wxString( wxT("&Redo") ) + wxT('\t') + wxT("Ctrl+Y"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditRedo->SetBitmaps( wxBitmap( redo_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditRedo->SetBitmap( wxBitmap( redo_xpm ) );
	#endif
	editMenu->Append( menuEditRedo );
	
	editMenu->AppendSeparator();
	
	wxMenuItem* menuEditCopy;
	menuEditCopy = new wxMenuItem( editMenu, wxID_COPY, wxString( wxT("&Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditCopy->SetBitmaps( wxBitmap( editcopy_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditCopy->SetBitmap( wxBitmap( editcopy_xpm ) );
	#endif
	editMenu->Append( menuEditCopy );
	
	wxMenuItem* menuEditCut;
	menuEditCut = new wxMenuItem( editMenu, wxID_CUT, wxString( wxT("Cut") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditCut->SetBitmaps( wxBitmap( editcut_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditCut->SetBitmap( wxBitmap( editcut_xpm ) );
	#endif
	editMenu->Append( menuEditCut );
	
	wxMenuItem* menuEditPaste;
	menuEditPaste = new wxMenuItem( editMenu, wxID_PASTE, wxString( wxT("&Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditPaste->SetBitmaps( wxBitmap( editpaste_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditPaste->SetBitmap( wxBitmap( editpaste_xpm ) );
	#endif
	editMenu->Append( menuEditPaste );
	
	editMenu->AppendSeparator();
	
	wxMenuItem* menuEditSelectAll;
	menuEditSelectAll = new wxMenuItem( editMenu, IDM_EDIT_SELECTALL, wxString( wxT("Select &all") ) + wxT('\t') + wxT("CTRL+A"), wxT("Select all items in current diagram"), wxITEM_NORMAL );
	editMenu->Append( menuEditSelectAll );
	
	editMenu->AppendSeparator();
	
	wxMenuItem* menuEditPreferences;
	menuEditPreferences = new wxMenuItem( editMenu, IDM_EDIT_PREFERENCES, wxString( wxT("Preferences...") ) + wxT('\t') + wxT("Ctrl+Alt+P"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuEditPreferences->SetBitmaps( wxBitmap( configure_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuEditPreferences->SetBitmap( wxBitmap( configure_xpm ) );
	#endif
	editMenu->Append( menuEditPreferences );
	
	mbar->Append( editMenu, wxT("&Edit") ); 
	
	viewMenu = new wxMenu();
	wxMenuItem* menuViewReset;
	menuViewReset = new wxMenuItem( viewMenu, IDM_VIEW_RESET, wxString( wxT("Reset layout") ) , wxEmptyString, wxITEM_NORMAL );
	viewMenu->Append( menuViewReset );
	
	viewMenu->AppendSeparator();
	
	wxMenuItem* menuViewProjectPanel;
	menuViewProjectPanel = new wxMenuItem( viewMenu, IDM_VIEW_PROJECT_PANEL, wxString( wxT("Project inspector") ) + wxT('\t') + wxT("Ctrl+1"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewProjectPanel );
	
	wxMenuItem* menuViewLogPanel;
	menuViewLogPanel = new wxMenuItem( viewMenu, IDM_VIEW_LOG_PANEL, wxString( wxT("Log window") ) + wxT('\t') + wxT("Ctrl+2"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewLogPanel );
	
	wxMenuItem* menuViewThumbPanel;
	menuViewThumbPanel = new wxMenuItem( viewMenu, IDM_VIEW_THUMBNAIL_PANEL, wxString( wxT("Thumbnail") ) + wxT('\t') + wxT("Ctrl+3"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewThumbPanel );
	
	wxMenuItem* menuViewEditor;
	menuViewEditor = new wxMenuItem( viewMenu, IDM_VIEW_EDITOR, wxString( wxT("Code editor") ) + wxT('\t') + wxT("Ctrl+4"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewEditor );
	
	wxMenuItem* menuViewFileTB;
	menuViewFileTB = new wxMenuItem( viewMenu, IDM_VIEW_FILE_TB, wxString( wxT("File toolbar") ) + wxT('\t') + wxT("Ctrl+5"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewFileTB );
	
	wxMenuItem* menuViewDiagramTB;
	menuViewDiagramTB = new wxMenuItem( viewMenu, IDM_VIEW_DIAGRAM_TB, wxString( wxT("Diagram toolbar") ) + wxT('\t') + wxT("Ctrl+6"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewDiagramTB );
	
	wxMenuItem* menuViewLayoutTB;
	menuViewLayoutTB = new wxMenuItem( viewMenu, IDM_VIEW_LAYOUT_TB, wxString( wxT("Layout toolbar") ) + wxT('\t') + wxT("Ctrl+7"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewLayoutTB );
	
	wxMenuItem* menuViewGeneratorTB;
	menuViewGeneratorTB = new wxMenuItem( viewMenu, IDM_VIEW_GENERATOR_TB, wxString( wxT("Generator toolbar") ) + wxT('\t') + wxT("Ctrl+8"), wxEmptyString, wxITEM_CHECK );
	viewMenu->Append( menuViewGeneratorTB );
	
	mbar->Append( viewMenu, wxT("&View") ); 
	
	projMenu = new wxMenu();
	wxMenuItem* menuProjPackage;
	menuProjPackage = new wxMenuItem( projMenu, IDM_PROJ_PACKAGE, wxString( wxT("Create diagram package") ) , wxT("Crate new package"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjPackage->SetBitmaps( wxBitmap( cube_green_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjPackage->SetBitmap( wxBitmap( cube_green_xpm ) );
	#endif
	projMenu->Append( menuProjPackage );
	
	wxMenuItem* menuProjCodePackage;
	menuProjCodePackage = new wxMenuItem( projMenu, IDM_PROJ_CODEPACKAGE, wxString( wxT("Create code package") ) , wxT("Create new code package"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjCodePackage->SetBitmaps( wxBitmap( cube_yellow_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjCodePackage->SetBitmap( wxBitmap( cube_yellow_xpm ) );
	#endif
	projMenu->Append( menuProjCodePackage );
	
	projMenu->AppendSeparator();
	
	projMenu->AppendSeparator();
	
	wxMenuItem* menuProjVariable;
	menuProjVariable = new wxMenuItem( projMenu, IDM_PROJ_VARIABLE, wxString( wxT("Create generic variable") ) , wxT("Create user-defined variable"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjVariable->SetBitmaps( wxBitmap( Variable_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjVariable->SetBitmap( wxBitmap( Variable_xpm ) );
	#endif
	projMenu->Append( menuProjVariable );
	
	wxMenuItem* menuProjFunction;
	menuProjFunction = new wxMenuItem( projMenu, IDM_PROJ_FUNCTION, wxString( wxT("Create generic function") ) , wxT("Create user-defined function"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjFunction->SetBitmaps( wxBitmap( Function_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjFunction->SetBitmap( wxBitmap( Function_xpm ) );
	#endif
	projMenu->Append( menuProjFunction );
	
	projMenu->AppendSeparator();
	
	wxMenuItem* menuProjEdit;
	menuProjEdit = new wxMenuItem( projMenu, IDM_PROJ_EDIT, wxString( wxT("Edit selected item") ) , wxT("Edit properties of seleceted project item"), wxITEM_NORMAL );
	projMenu->Append( menuProjEdit );
	
	wxMenuItem* menuProjRemove;
	menuProjRemove = new wxMenuItem( projMenu, IDM_PROJ_REMOVE, wxString( wxT("Remove selected item") ) + wxT('\t') + wxT("CTRL+D"), wxT("Remove item selected in the project view from current project"), wxITEM_NORMAL );
	projMenu->Append( menuProjRemove );
	
	projMenu->AppendSeparator();
	
	wxMenuItem* menuProjRemoveAll;
	menuProjRemoveAll = new wxMenuItem( projMenu, IDM_PROJ_REMOVEALL, wxString( wxT("Remove all") ) , wxT("Clear project (permanently remove all project items)"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjRemoveAll->SetBitmaps( wxNullBitmap );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjRemoveAll->SetBitmap( wxNullBitmap );
	#endif
	projMenu->Append( menuProjRemoveAll );
	
	projMenu->AppendSeparator();
	
	wxMenuItem* menuProjSettings;
	menuProjSettings = new wxMenuItem( projMenu, IDM_PROJ_SETTINGS, wxString( wxT("Settings...") ) + wxT('\t') + wxT("Ctrl+Alt+S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuProjSettings->SetBitmaps( wxBitmap( configure_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuProjSettings->SetBitmap( wxBitmap( configure_xpm ) );
	#endif
	projMenu->Append( menuProjSettings );
	
	mbar->Append( projMenu, wxT("&Project") ); 
	
	bankMenu = new wxMenu();
	wxMenuItem* menuBankManage;
	menuBankManage = new wxMenuItem( bankMenu, IDM_BANK_MANAGE, wxString( wxT("Manage bank...") ) + wxT('\t') + wxT("Ctrl+B"), wxEmptyString, wxITEM_NORMAL );
	bankMenu->Append( menuBankManage );
	
	bankMenu->AppendSeparator();
	
	wxMenuItem* menuBankStore;
	menuBankStore = new wxMenuItem( bankMenu, IDM_DIAG_STORETOBANK, wxString( wxT("Store diagram to bank") ) , wxT("Store currently selected diagram to bank"), wxITEM_NORMAL );
	bankMenu->Append( menuBankStore );
	
	wxMenuItem* menuBankInsert;
	menuBankInsert = new wxMenuItem( bankMenu, IDM_DIAG_INSERTFROMBANK, wxString( wxT("Insert diagram from bank") ) , wxT("Insert diagram from bank to currently selected package"), wxITEM_NORMAL );
	bankMenu->Append( menuBankInsert );
	
	bankMenu->AppendSeparator();
	
	wxMenuItem* menuBankImport;
	menuBankImport = new wxMenuItem( bankMenu, IDM_BANK_IMPORT, wxString( wxT("Import bank...") ) , wxEmptyString, wxITEM_NORMAL );
	bankMenu->Append( menuBankImport );
	
	wxMenuItem* menuBankExport;
	menuBankExport = new wxMenuItem( bankMenu, IDM_BANK_EXPORT, wxString( wxT("Export bank...") ) , wxEmptyString, wxITEM_NORMAL );
	bankMenu->Append( menuBankExport );
	
	mbar->Append( bankMenu, wxT("&Diagram bank") ); 
	
	codeGenMenu = new wxMenu();
	wxMenuItem* menuCodePreview;
	menuCodePreview = new wxMenuItem( codeGenMenu, IDM_CODE_PREVIEW, wxString( wxT("&Preview") ) + wxT('\t') + wxT("Ctrl+Shift+G"), wxT("Generate code from active diagram"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuCodePreview->SetBitmaps( wxBitmap( spellcheck_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuCodePreview->SetBitmap( wxBitmap( spellcheck_xpm ) );
	#endif
	codeGenMenu->Append( menuCodePreview );
	
	wxMenuItem* menuCodeGenerate;
	menuCodeGenerate = new wxMenuItem( codeGenMenu, IDM_CODE_GENERATE, wxString( wxT("&Generate") ) + wxT('\t') + wxT("Ctrl+G"), wxT("Generate code for an active chart"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuCodeGenerate->SetBitmaps( wxBitmap( actionrun_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuCodeGenerate->SetBitmap( wxBitmap( actionrun_xpm ) );
	#endif
	codeGenMenu->Append( menuCodeGenerate );
	
	codeGenMenu->AppendSeparator();
	
	wxMenuItem* menuCodeSynchronize;
	menuCodeSynchronize = new wxMenuItem( codeGenMenu, IDM_CODE_SYNCHRONIZE, wxString( wxT("Synchronize code") ) , wxT("Synchronize changes in code items' source code."), wxITEM_NORMAL );
	codeGenMenu->Append( menuCodeSynchronize );
	
	mbar->Append( codeGenMenu, wxT("&Code generation") ); 
	
	pluginsMenu = new wxMenu();
	wxMenuItem* menuPluginsManage;
	menuPluginsManage = new wxMenuItem( pluginsMenu, IDM_PLUGINS_MANAGE, wxString( wxT("Manage plugins...") ) , wxT("Manage available plugins"), wxITEM_NORMAL );
	pluginsMenu->Append( menuPluginsManage );
	
	mbar->Append( pluginsMenu, wxT("&Plugins") ); 
	
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, wxID_ABOUT, wxString( wxT("&About...") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	#ifdef __WXMSW__
	menuHelpAbout->SetBitmaps( wxBitmap( helpindex_xpm ) );
	#elif (defined( __WXGTK__ ) || defined( __WXOSX__ ))
	menuHelpAbout->SetBitmap( wxBitmap( helpindex_xpm ) );
	#endif
	helpMenu->Append( menuHelpAbout );
	
	mbar->Append( helpMenu, wxT("&Help") ); 
	
	this->SetMenuBar( mbar );
	
	statusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_mainPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* mainDsgnSizer;
	mainDsgnSizer = new wxFlexGridSizer( 3, 1, 0, 0 );
	mainDsgnSizer->AddGrowableCol( 0 );
	mainDsgnSizer->AddGrowableRow( 1 );
	mainDsgnSizer->SetFlexibleDirection( wxBOTH );
	mainDsgnSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_auintbPalettes = new wxAuiNotebook( m_mainPanel, IDC_AUINTB_PALETTES, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_WINDOWLIST_BUTTON|wxNO_BORDER );
	m_auintbPalettes->SetMinSize( wxSize( -1,50 ) );
	
	
	mainDsgnSizer->Add( m_auintbPalettes, 1, wxEXPAND, 5 );
	
	m_auintbDesignArea = new wxAuiNotebook( m_mainPanel, IDC_AUINTB_DESIGNAREA, wxDefaultPosition, wxDefaultSize, wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_TAB_MOVE|wxAUI_NB_WINDOWLIST_BUTTON|wxNO_BORDER );
	
	mainDsgnSizer->Add( m_auintbDesignArea, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* zoomSizer;
	zoomSizer = new wxFlexGridSizer( 1, 3, 0, 0 );
	zoomSizer->AddGrowableCol( 2 );
	zoomSizer->SetFlexibleDirection( wxBOTH );
	zoomSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	btnZoom100 = new wxBitmapButton( m_mainPanel, wxID_ZOOM_100, wxBitmap( Zoom100_xpm ), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	
	btnZoom100->SetBitmapDisabled( wxBitmap( Zoom100Dis_xpm ) );
	btnZoom100->SetToolTip( wxT("Zoom diagram to its original size") );
	
	zoomSizer->Add( btnZoom100, 0, 0, 5 );
	
	btnZoomAll = new wxBitmapButton( m_mainPanel, wxID_ZOOM_FIT, wxBitmap( ZoomAll_xpm ), wxDefaultPosition, wxSize( 24,24 ), wxBU_AUTODRAW );
	
	btnZoomAll->SetBitmapDisabled( wxBitmap( ZoomAllDis_xpm ) );
	btnZoomAll->SetToolTip( wxT("Zoom diagram to fit the design area") );
	
	zoomSizer->Add( btnZoomAll, 0, 0, 5 );
	
	m_sliderZoom = new wxSlider( m_mainPanel, IDC_ZOOM, 50, 10, 99, wxDefaultPosition, wxSize( -1,20 ), wxSL_HORIZONTAL );
	m_sliderZoom->SetToolTip( wxT("Design area zoom") );
	
	zoomSizer->Add( m_sliderZoom, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5 );
	
	
	mainDsgnSizer->Add( zoomSizer, 1, wxEXPAND, 5 );
	
	
	m_mainPanel->SetSizer( mainDsgnSizer );
	m_mainPanel->Layout();
	mainDsgnSizer->Fit( m_mainPanel );
	mainSizer->Add( m_mainPanel, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _MainFrame::OnClose ) );
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( _MainFrame::OnIdle ) );
	this->Connect( menuFileNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnNewProject ) );
	this->Connect( menuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnOpenProject ) );
	this->Connect( menuFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSaveProject ) );
	this->Connect( menuFileSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSaveProjectAs ) );
	this->Connect( menuFileExportBMP->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnExportDiagram ) );
	this->Connect( menuFileExportBMP->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Connect( menuFilePrint->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Connect( menuFilePreview->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Connect( menuFilePageSetup->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnQuit ) );
	this->Connect( menuEditSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSelectAll ) );
	this->Connect( menuEditSelectAll->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Connect( menuEditPreferences->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnPreferences ) );
	this->Connect( menuViewReset->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnResetLayout ) );
	this->Connect( menuViewProjectPanel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewProjectPanel->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewLogPanel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewLogPanel->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewThumbPanel->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewThumbPanel->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewEditor->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewEditor->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewFileTB->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewFileTB->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewDiagramTB->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewDiagramTB->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewLayoutTB->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewLayoutTB->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuViewGeneratorTB->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Connect( menuViewGeneratorTB->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Connect( menuProjPackage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Connect( menuProjPackage->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreatePackage ) );
	this->Connect( menuProjCodePackage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Connect( menuProjCodePackage->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreatePackage ) );
	this->Connect( menuProjVariable->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Connect( menuProjVariable->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreateCodeItem ) );
	this->Connect( menuProjFunction->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Connect( menuProjFunction->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreateCodeItem ) );
	this->Connect( menuProjEdit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnEditItem ) );
	this->Connect( menuProjEdit->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateProjectItemSelected ) );
	this->Connect( menuProjRemove->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnRemoveItem ) );
	this->Connect( menuProjRemove->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateProjectItemSelected ) );
	this->Connect( menuProjRemoveAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnRemoveAll ) );
	this->Connect( menuProjSettings->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSettings ) );
	this->Connect( menuBankManage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnManageBank ) );
	this->Connect( menuBankStore->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnStoreToBank ) );
	this->Connect( menuBankStore->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateStoreToBank ) );
	this->Connect( menuBankInsert->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnInsertFromBank ) );
	this->Connect( menuBankInsert->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateInsertFromBank ) );
	this->Connect( menuBankImport->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnImportBank ) );
	this->Connect( menuBankExport->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnExportBank ) );
	this->Connect( menuCodePreview->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnPreviewClick ) );
	this->Connect( menuCodePreview->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateGeneratorActivated ) );
	this->Connect( menuCodeGenerate->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnGenerateClick ) );
	this->Connect( menuCodeSynchronize->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSynchronizeCode ) );
	this->Connect( menuPluginsManage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnManagePlugins ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnAbout ) );
	m_auintbDesignArea->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( _MainFrame::OnPageChanged ), NULL, this );
	m_auintbDesignArea->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( _MainFrame::OnPageClosing ), NULL, this );
	btnZoom100->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _MainFrame::OnZoom100 ), NULL, this );
	btnZoom100->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
	btnZoomAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _MainFrame::OnZoomAll ), NULL, this );
	btnZoomAll->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
}

_MainFrame::~_MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _MainFrame::OnClose ) );
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( _MainFrame::OnIdle ) );
	this->Disconnect( wxID_NEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnNewProject ) );
	this->Disconnect( wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnOpenProject ) );
	this->Disconnect( wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSaveProject ) );
	this->Disconnect( wxID_SAVEAS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSaveProjectAs ) );
	this->Disconnect( IDM_FILE_EXPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnExportDiagram ) );
	this->Disconnect( IDM_FILE_EXPORT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Disconnect( wxID_PRINT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Disconnect( wxID_PREVIEW, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Disconnect( wxID_PAGE_SETUP, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnQuit ) );
	this->Disconnect( IDM_EDIT_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSelectAll ) );
	this->Disconnect( IDM_EDIT_SELECTALL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCanvasActivated ) );
	this->Disconnect( IDM_EDIT_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnPreferences ) );
	this->Disconnect( IDM_VIEW_RESET, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnResetLayout ) );
	this->Disconnect( IDM_VIEW_PROJECT_PANEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_PROJECT_PANEL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_LOG_PANEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_LOG_PANEL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_THUMBNAIL_PANEL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_THUMBNAIL_PANEL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_EDITOR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_EDITOR, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_FILE_TB, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_FILE_TB, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_DIAGRAM_TB, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_DIAGRAM_TB, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_LAYOUT_TB, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_LAYOUT_TB, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_VIEW_GENERATOR_TB, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnToggleGUI ) );
	this->Disconnect( IDM_VIEW_GENERATOR_TB, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateToggleGUI ) );
	this->Disconnect( IDM_PROJ_PACKAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Disconnect( IDM_PROJ_PACKAGE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreatePackage ) );
	this->Disconnect( IDM_PROJ_CODEPACKAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Disconnect( IDM_PROJ_CODEPACKAGE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreatePackage ) );
	this->Disconnect( IDM_PROJ_VARIABLE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Disconnect( IDM_PROJ_VARIABLE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreateCodeItem ) );
	this->Disconnect( IDM_PROJ_FUNCTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnCreateProjectItem ) );
	this->Disconnect( IDM_PROJ_FUNCTION, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateCreateCodeItem ) );
	this->Disconnect( IDM_PROJ_EDIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnEditItem ) );
	this->Disconnect( IDM_PROJ_EDIT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateProjectItemSelected ) );
	this->Disconnect( IDM_PROJ_REMOVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnRemoveItem ) );
	this->Disconnect( IDM_PROJ_REMOVE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateProjectItemSelected ) );
	this->Disconnect( IDM_PROJ_REMOVEALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnRemoveAll ) );
	this->Disconnect( IDM_PROJ_SETTINGS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSettings ) );
	this->Disconnect( IDM_BANK_MANAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnManageBank ) );
	this->Disconnect( IDM_DIAG_STORETOBANK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnStoreToBank ) );
	this->Disconnect( IDM_DIAG_STORETOBANK, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateStoreToBank ) );
	this->Disconnect( IDM_DIAG_INSERTFROMBANK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnInsertFromBank ) );
	this->Disconnect( IDM_DIAG_INSERTFROMBANK, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateInsertFromBank ) );
	this->Disconnect( IDM_BANK_IMPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnImportBank ) );
	this->Disconnect( IDM_BANK_EXPORT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnExportBank ) );
	this->Disconnect( IDM_CODE_PREVIEW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnPreviewClick ) );
	this->Disconnect( IDM_CODE_PREVIEW, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateGeneratorActivated ) );
	this->Disconnect( IDM_CODE_GENERATE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnGenerateClick ) );
	this->Disconnect( IDM_CODE_SYNCHRONIZE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnSynchronizeCode ) );
	this->Disconnect( IDM_PLUGINS_MANAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnManagePlugins ) );
	this->Disconnect( wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _MainFrame::OnAbout ) );
	m_auintbDesignArea->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( _MainFrame::OnPageChanged ), NULL, this );
	m_auintbDesignArea->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler( _MainFrame::OnPageClosing ), NULL, this );
	btnZoom100->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _MainFrame::OnZoom100 ), NULL, this );
	btnZoom100->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
	btnZoomAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _MainFrame::OnZoomAll ), NULL, this );
	btnZoomAll->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( _MainFrame::OnZoom ), NULL, this );
	m_sliderZoom->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _MainFrame::OnUpdateZoomSlider ), NULL, this );
	
}

_EditorFrame::_EditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetExtraStyle( wxWS_EX_BLOCK_EVENTS );
	this->SetExtraStyle( wxFRAME_EX_CONTEXTHELP );
	
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* menuFileClose;
	menuFileClose = new wxMenuItem( m_menuFile, wxID_CLOSE, wxString( wxT("Close") ) + wxT('\t') + wxT("Alt+X"), wxT("Close editor window"), wxITEM_NORMAL );
	m_menuFile->Append( menuFileClose );
	
	m_menuBar->Append( m_menuFile, wxT("&File") ); 
	
	m_menuEdit = new wxMenu();
	wxMenuItem* menuEditCut;
	menuEditCut = new wxMenuItem( m_menuEdit, wxID_CUT, wxString( wxT("Cu&t") ) + wxT('\t') + wxT("Ctrl+X"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuEditCut );
	
	wxMenuItem* menuEditCopy;
	menuEditCopy = new wxMenuItem( m_menuEdit, wxID_COPY, wxString( wxT("&Copy") ) + wxT('\t') + wxT("Ctrl+C"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuEditCopy );
	
	wxMenuItem* menuEditPaste;
	menuEditPaste = new wxMenuItem( m_menuEdit, wxID_PASTE, wxString( wxT("&Paste") ) + wxT('\t') + wxT("Ctrl+V"), wxEmptyString, wxITEM_NORMAL );
	m_menuEdit->Append( menuEditPaste );
	
	m_menuBar->Append( m_menuEdit, wxT("&Edit") ); 
	
	this->SetMenuBar( m_menuBar );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_scintillaEditor = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_scintillaEditor->SetUseTabs( true );
	m_scintillaEditor->SetTabWidth( 4 );
	m_scintillaEditor->SetIndent( 4 );
	m_scintillaEditor->SetTabIndents( true );
	m_scintillaEditor->SetBackSpaceUnIndents( true );
	m_scintillaEditor->SetViewEOL( false );
	m_scintillaEditor->SetViewWhiteSpace( false );
	m_scintillaEditor->SetMarginWidth( 2, 0 );
	m_scintillaEditor->SetIndentationGuides( true );
	m_scintillaEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_scintillaEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_scintillaEditor->SetMarginWidth( 1, 16);
	m_scintillaEditor->SetMarginSensitive( 1, true );
	m_scintillaEditor->SetProperty( wxT("fold"), wxT("1") );
	m_scintillaEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_scintillaEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_scintillaEditor->SetMarginWidth( 0, m_scintillaEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_scintillaEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_scintillaEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	mainSizer->Add( m_scintillaEditor, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _EditorFrame::OnClose ) );
	this->Connect( menuFileClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCloseClick ) );
	this->Connect( menuEditCut->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCutClick ) );
	this->Connect( menuEditCut->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdateCut ) );
	this->Connect( menuEditCopy->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCopyClick ) );
	this->Connect( menuEditCopy->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdateCopy ) );
	this->Connect( menuEditPaste->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnPasteClick ) );
	this->Connect( menuEditPaste->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdatePaste ) );
}

_EditorFrame::~_EditorFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( _EditorFrame::OnClose ) );
	this->Disconnect( wxID_CLOSE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCloseClick ) );
	this->Disconnect( wxID_CUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCutClick ) );
	this->Disconnect( wxID_CUT, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdateCut ) );
	this->Disconnect( wxID_COPY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnCopyClick ) );
	this->Disconnect( wxID_COPY, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdateCopy ) );
	this->Disconnect( wxID_PASTE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _EditorFrame::OnPasteClick ) );
	this->Disconnect( wxID_PASTE, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorFrame::OnUpdatePaste ) );
	
}

_LogPanel::_LogPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pLogList = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxSUNKEN_BORDER );
	mainSizer->Add( m_pLogList, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	// Connect Events
	m_pLogList->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _LogPanel::OnRightClick ), NULL, this );
}

_LogPanel::~_LogPanel()
{
	// Disconnect Events
	m_pLogList->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _LogPanel::OnRightClick ), NULL, this );
	
}

_ProjManPanel::_ProjManPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 2, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 1 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL ); 
	m_toolLinkEditor = m_toolBar->AddTool( IDT_PROJMAN_LINK, wxT("Link on/off"), wxBitmap( link_editor_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Link project manager with design area"), wxEmptyString, NULL ); 
	
	m_toolExpandAll = m_toolBar->AddTool( IDT_PROJMAN_EXPAND, wxT("Expand/Collapse all"), wxBitmap( collapse_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Expand/collapse all tree items"), wxEmptyString, NULL ); 
	
	m_toolBar->AddSeparator(); 
	
	m_toolProperties = m_toolBar->AddTool( IDT_PROJMAN_SHOWPROPS, wxT("Show properies"), wxBitmap( form_blue_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Inspect properties of selected tree item"), wxEmptyString, NULL ); 
	
	m_toolOrganizeCI = m_toolBar->AddTool( IDT_PROJMAN_ORGANIZECI, wxT("Organize code items"), wxBitmap( organisation_xpm ), wxNullBitmap, wxITEM_CHECK, wxT("Organize code items"), wxEmptyString, NULL ); 
	
	m_toolBar->Realize(); 
	
	mainSizer->Add( m_toolBar, 0, wxEXPAND, 5 );
	
	m_pSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pSplitter->SetSashGravity( 0 );
	m_pSplitter->SetMinimumPaneSize( 100 );
	
	m_pPanelTree = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxSize( -1,300 ), wxTAB_TRAVERSAL );
	m_pPanelTree->SetMinSize( wxSize( -1,300 ) );
	
	wxBoxSizer* treeSizer;
	treeSizer = new wxBoxSizer( wxVERTICAL );
	
	m_auintbViews = new wxAuiNotebook( m_pPanelTree, IDC_AUINTB_PROJMAN, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_TAB_MOVE|wxNO_BORDER );
	
	treeSizer->Add( m_auintbViews, 1, wxEXPAND, 5 );
	
	
	m_pPanelTree->SetSizer( treeSizer );
	m_pPanelTree->Layout();
	m_pPanelProperties = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxSize( -1,100 ), wxTAB_TRAVERSAL );
	m_pPanelProperties->SetMinSize( wxSize( -1,100 ) );
	
	wxBoxSizer* propertiesSizer;
	propertiesSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pPropertiesGrid = new wxPropertyGrid(m_pPanelProperties, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER|wxPG_TOOLTIPS);
	propertiesSizer->Add( m_pPropertiesGrid, 1, wxEXPAND, 5 );
	
	
	m_pPanelProperties->SetSizer( propertiesSizer );
	m_pPanelProperties->Layout();
	m_pSplitter->SplitHorizontally( m_pPanelTree, m_pPanelProperties, -1 );
	mainSizer->Add( m_pSplitter, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( m_toolLinkEditor->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnLinkedEditor ) );
	this->Connect( m_toolLinkEditor->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateLinkedEditor ) );
	this->Connect( m_toolExpandAll->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnExpandAll ) );
	this->Connect( m_toolProperties->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnShowProperties ) );
	this->Connect( m_toolProperties->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateShowProperties ) );
	this->Connect( m_toolOrganizeCI->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnOrganizeCI ) );
	this->Connect( m_toolOrganizeCI->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateOrganizeCI ) );
	m_pSplitter->Connect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( _ProjManPanel::OnPropsSashChanged ), NULL, this );
	m_auintbViews->Connect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( _ProjManPanel::OnViewChanged ), NULL, this );
	m_pPropertiesGrid->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( _ProjManPanel::OnPGActivated ), NULL, this );
}

_ProjManPanel::~_ProjManPanel()
{
	// Disconnect Events
	this->Disconnect( m_toolLinkEditor->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnLinkedEditor ) );
	this->Disconnect( m_toolLinkEditor->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateLinkedEditor ) );
	this->Disconnect( m_toolExpandAll->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnExpandAll ) );
	this->Disconnect( m_toolProperties->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnShowProperties ) );
	this->Disconnect( m_toolProperties->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateShowProperties ) );
	this->Disconnect( m_toolOrganizeCI->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _ProjManPanel::OnOrganizeCI ) );
	this->Disconnect( m_toolOrganizeCI->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ProjManPanel::OnUpdateOrganizeCI ) );
	m_pSplitter->Disconnect( wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED, wxSplitterEventHandler( _ProjManPanel::OnPropsSashChanged ), NULL, this );
	m_auintbViews->Disconnect( wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler( _ProjManPanel::OnViewChanged ), NULL, this );
	m_pPropertiesGrid->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( _ProjManPanel::OnPGActivated ), NULL, this );
	
}

_EditorPanel::_EditorPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 2, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 1 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_toolActions = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTB_FLAT|wxTB_HORIZONTAL ); 
	m_toolSave = m_toolActions->AddTool( IDT_INSTEDITOR_SAVE, wxT("tool"), wxBitmap( filesave_xpm ), wxNullBitmap, wxITEM_NORMAL, wxT("Save changes (Alt+S)"), wxEmptyString, NULL ); 
	
	m_toolActions->AddSeparator(); 
	
	m_stCodeItem = new wxStaticText( m_toolActions, wxID_ANY, wxT("Code item:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stCodeItem->Wrap( -1 );
	m_stCodeItem->SetFont( wxFont( 8, 74, 90, 90, false, wxT("Sans") ) );
	
	m_toolActions->AddControl( m_stCodeItem );
	m_toolActions->Realize(); 
	
	mainSizer->Add( m_toolActions, 0, wxEXPAND, 5 );
	
	m_scintillaEditor = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxEmptyString );
	m_scintillaEditor->SetUseTabs( true );
	m_scintillaEditor->SetTabWidth( 4 );
	m_scintillaEditor->SetIndent( 4 );
	m_scintillaEditor->SetTabIndents( true );
	m_scintillaEditor->SetBackSpaceUnIndents( true );
	m_scintillaEditor->SetViewEOL( false );
	m_scintillaEditor->SetViewWhiteSpace( false );
	m_scintillaEditor->SetMarginWidth( 2, 0 );
	m_scintillaEditor->SetIndentationGuides( true );
	m_scintillaEditor->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_scintillaEditor->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_scintillaEditor->SetMarginWidth( 1, 16);
	m_scintillaEditor->SetMarginSensitive( 1, true );
	m_scintillaEditor->SetProperty( wxT("fold"), wxT("1") );
	m_scintillaEditor->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_scintillaEditor->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_scintillaEditor->SetMarginWidth( 0, m_scintillaEditor->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_scintillaEditor->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_scintillaEditor->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_scintillaEditor->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_scintillaEditor->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_scintillaEditor->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	mainSizer->Add( m_scintillaEditor, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( m_toolSave->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _EditorPanel::OnSave ) );
	this->Connect( m_toolSave->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorPanel::OnUpdateSave ) );
	m_scintillaEditor->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( _EditorPanel::OnKeyDown ), NULL, this );
}

_EditorPanel::~_EditorPanel()
{
	// Disconnect Events
	this->Disconnect( m_toolSave->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( _EditorPanel::OnSave ) );
	this->Disconnect( m_toolSave->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _EditorPanel::OnUpdateSave ) );
	m_scintillaEditor->Disconnect( wxEVT_KEY_DOWN, wxKeyEventHandler( _EditorPanel::OnKeyDown ), NULL, this );
	
}

_SettingsDialog::_SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 670,420 ), wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 2, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 0 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_pSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_pSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( _SettingsDialog::m_pSplitterOnIdle ), NULL, this );
	m_pSplitter->SetMinimumPaneSize( 205 );
	
	m_pPanelTree = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* treeSizer;
	treeSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pCategoryTree = new wxTreeCtrl( m_pPanelTree, wxID_ANY, wxDefaultPosition, wxSize( 200,350 ), wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxSIMPLE_BORDER );
	m_pCategoryTree->SetMinSize( wxSize( 200,350 ) );
	
	treeSizer->Add( m_pCategoryTree, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	
	m_pPanelTree->SetSizer( treeSizer );
	m_pPanelTree->Layout();
	treeSizer->Fit( m_pPanelTree );
	m_pPanelProps = new wxPanel( m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* propsSizer;
	propsSizer = new wxBoxSizer( wxVERTICAL );
	
	m_pPropertyGrid = new wxPropertyGrid(m_pPanelProps, IDC_SETTINGSDLG_PROPGRID, wxDefaultPosition, wxSize( 450,350 ), wxPG_BOLD_MODIFIED|wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
	m_pPropertyGrid->SetMinSize( wxSize( 450,350 ) );
	
	propsSizer->Add( m_pPropertyGrid, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	m_pPanelProps->SetSizer( propsSizer );
	m_pPanelProps->Layout();
	propsSizer->Fit( m_pPanelProps );
	m_pSplitter->SplitVertically( m_pPanelTree, m_pPanelProps, 205 );
	mainSizer->Add( m_pSplitter, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* buttonGridSizer;
	buttonGridSizer = new wxFlexGridSizer( 1, 2, 0, 0 );
	buttonGridSizer->AddGrowableCol( 0 );
	buttonGridSizer->SetFlexibleDirection( wxBOTH );
	buttonGridSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_btnDefaults = new wxButton( this, wxID_ANY, wxT("Defaults"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonGridSizer->Add( m_btnDefaults, 0, wxALIGN_RIGHT|wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	buttonSizer = new wxStdDialogButtonSizer();
	buttonSizerOK = new wxButton( this, wxID_OK );
	buttonSizer->AddButton( buttonSizerOK );
	buttonSizerCancel = new wxButton( this, wxID_CANCEL );
	buttonSizer->AddButton( buttonSizerCancel );
	buttonSizer->Realize();
	
	buttonGridSizer->Add( buttonSizer, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	mainSizer->Add( buttonGridSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _SettingsDialog::OnInit ) );
	m_pCategoryTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( _SettingsDialog::OnChangeCategory ), NULL, this );
	m_btnDefaults->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnDefaults ), NULL, this );
	buttonSizerCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnCancel ), NULL, this );
	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnOk ), NULL, this );
}

_SettingsDialog::~_SettingsDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _SettingsDialog::OnInit ) );
	m_pCategoryTree->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( _SettingsDialog::OnChangeCategory ), NULL, this );
	m_btnDefaults->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnDefaults ), NULL, this );
	buttonSizerCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnCancel ), NULL, this );
	buttonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SettingsDialog::OnOk ), NULL, this );
	
}

_InsertFromBankDialog::_InsertFromBankDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 420,300 ), wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 5, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 3 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText69 = new wxStaticText( this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	mainSizer->Add( m_staticText69, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_chCategoryChoices;
	m_chCategory = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 400,-1 ), m_chCategoryChoices, 0 );
	m_chCategory->SetSelection( 0 );
	m_chCategory->SetMinSize( wxSize( 400,-1 ) );
	
	mainSizer->Add( m_chCategory, 0, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText70 = new wxStaticText( this, wxID_ANY, wxT("Available diagrams:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	mainSizer->Add( m_staticText70, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_lstDiagrams = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	m_lstDiagrams->SetMinSize( wxSize( -1,150 ) );
	
	m_menuDiagrams = new wxMenu();
	wxMenuItem* menuDiagSelectAll;
	menuDiagSelectAll = new wxMenuItem( m_menuDiagrams, IDM_DBANK_SELECTALL, wxString( wxT("Selec all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuDiagrams->Append( menuDiagSelectAll );
	
	wxMenuItem* menuDiagDeselectAll;
	menuDiagDeselectAll = new wxMenuItem( m_menuDiagrams, IDM_DBANK_DESELECTALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuDiagrams->Append( menuDiagDeselectAll );
	
	m_menuDiagrams->AppendSeparator();
	
	wxMenuItem* menuDiagDeps;
	menuDiagDeps = new wxMenuItem( m_menuDiagrams, IDM_DBANK_SHOWDEPS, wxString( wxT("Show info") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuDiagrams->Append( menuDiagDeps );
	
	m_lstDiagrams->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _InsertFromBankDialog::m_lstDiagramsOnContextMenu ), NULL, this ); 
	
	mainSizer->Add( m_lstDiagrams, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	
	buttonsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnInsert = new wxButton( this, wxID_OK, wxT("Insert selected"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_btnInsert, 0, wxALL, 5 );
	
	m_btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_btnCancel, 0, wxALL, 5 );
	
	
	mainSizer->Add( buttonsSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_chCategory->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnCategoryChange ), NULL, this );
	this->Connect( menuDiagSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnSelectAll ) );
	this->Connect( menuDiagDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnDeselectAll ) );
	this->Connect( menuDiagDeps->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnShowDeps ) );
	this->Connect( menuDiagDeps->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _InsertFromBankDialog::OnUpdateShowDeps ) );
	m_btnInsert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _InsertFromBankDialog::OnInsertClick ), NULL, this );
}

_InsertFromBankDialog::~_InsertFromBankDialog()
{
	// Disconnect Events
	m_chCategory->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnCategoryChange ), NULL, this );
	this->Disconnect( IDM_DBANK_SELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnSelectAll ) );
	this->Disconnect( IDM_DBANK_DESELECTALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnDeselectAll ) );
	this->Disconnect( IDM_DBANK_SHOWDEPS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _InsertFromBankDialog::OnShowDeps ) );
	this->Disconnect( IDM_DBANK_SHOWDEPS, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _InsertFromBankDialog::OnUpdateShowDeps ) );
	m_btnInsert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _InsertFromBankDialog::OnInsertClick ), NULL, this );
	
	delete m_menuDiagrams; 
}

_StoreToBankDialog::_StoreToBankDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 435,450 ), wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 4, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 2 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText69 = new wxStaticText( this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText69->Wrap( -1 );
	mainSizer->Add( m_staticText69, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* categorySizer;
	categorySizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxArrayString m_chCategoryChoices;
	m_chCategory = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), m_chCategoryChoices, 0 );
	m_chCategory->SetSelection( 0 );
	categorySizer->Add( m_chCategory, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_btnCreateCat = new wxButton( this, IDC_CATEGORY_CREATE, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	categorySizer->Add( m_btnCreateCat, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	mainSizer->Add( categorySizer, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Diagram info") ), wxVERTICAL );
	
	m_stDiagName = new wxStaticText( this, wxID_ANY, wxT("Diagram"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stDiagName->Wrap( -1 );
	m_stDiagName->SetFont( wxFont( 9, 74, 90, 92, false, wxT("Sans") ) );
	
	sbSizer7->Add( m_stDiagName, 0, wxALL, 5 );
	
	m_staticText76 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText76->Wrap( -1 );
	sbSizer7->Add( m_staticText76, 0, wxALL, 5 );
	
	m_textDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE );
	m_textDescription->SetMaxLength( 0 ); 
	m_textDescription->SetMinSize( wxSize( -1,100 ) );
	
	sbSizer7->Add( m_textDescription, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText70 = new wxStaticText( this, wxID_ANY, wxT("Dependencies:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	sbSizer7->Add( m_staticText70, 0, wxRIGHT|wxLEFT, 5 );
	
	m_lstDeps = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	m_lstDeps->SetMinSize( wxSize( 400,100 ) );
	
	sbSizer7->Add( m_lstDeps, 1, wxALL|wxEXPAND, 5 );
	
	
	mainSizer->Add( sbSizer7, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );
	
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	
	buttonsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnInsert = new wxButton( this, wxID_OK, wxT("Store to bank"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_btnInsert, 0, wxALL, 5 );
	
	m_btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_btnCancel, 0, wxALL, 5 );
	
	
	mainSizer->Add( buttonsSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_btnCreateCat->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StoreToBankDialog::OnCreateClick ), NULL, this );
	m_btnInsert->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StoreToBankDialog::OnStoreClick ), NULL, this );
}

_StoreToBankDialog::~_StoreToBankDialog()
{
	// Disconnect Events
	m_btnCreateCat->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StoreToBankDialog::OnCreateClick ), NULL, this );
	m_btnInsert->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _StoreToBankDialog::OnStoreClick ), NULL, this );
	
}

_DependenciesDialog::_DependenciesDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 420,350 ), wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 5, 1, 0, 0 );
	mainSizer->AddGrowableCol( 0 );
	mainSizer->AddGrowableRow( 3 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText77 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText77->Wrap( -1 );
	mainSizer->Add( m_staticText77, 0, wxALL, 5 );
	
	m_textDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,100 ), wxTE_MULTILINE|wxTE_READONLY );
	m_textDescription->SetMaxLength( 0 ); 
	m_textDescription->SetMinSize( wxSize( -1,100 ) );
	
	mainSizer->Add( m_textDescription, 0, wxBOTTOM|wxRIGHT|wxLEFT|wxEXPAND, 5 );
	
	m_staticText70 = new wxStaticText( this, wxID_ANY, wxT("Used code items:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	mainSizer->Add( m_staticText70, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_lstDeps = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 400,150 ), wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	m_lstDeps->SetMinSize( wxSize( 400,150 ) );
	
	mainSizer->Add( m_lstDeps, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* buttonsSizer;
	buttonsSizer = new wxBoxSizer( wxHORIZONTAL );
	
	
	buttonsSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnCancel = new wxButton( this, wxID_OK, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	buttonsSizer->Add( m_btnCancel, 0, wxALL, 5 );
	
	
	mainSizer->Add( buttonsSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
}

_DependenciesDialog::~_DependenciesDialog()
{
}

_ManageBankDialog::_ManageBankDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 710,400 ), wxDefaultSize );
	
	wxFlexGridSizer* mainSizer;
	mainSizer = new wxFlexGridSizer( 2, 2, 0, 0 );
	mainSizer->AddGrowableCol( 1 );
	mainSizer->AddGrowableRow( 0 );
	mainSizer->SetFlexibleDirection( wxBOTH );
	mainSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Categories") ), wxVERTICAL );
	
	m_lbCategories = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 200,250 ), 0, NULL, wxLB_SINGLE ); 
	m_lbCategories->SetMinSize( wxSize( 200,250 ) );
	
	sbSizer5->Add( m_lbCategories, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnCreateCat = new wxButton( this, IDC_CAT_CREATE, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnCreateCat->SetToolTip( wxT("Create new category") );
	
	bSizer74->Add( m_btnCreateCat, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	m_btnRenameCat = new wxButton( this, IDC_CAT_RENAME, wxT("Rename"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( m_btnRenameCat, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND, 5 );
	
	m_btnRemoveCat = new wxButton( this, IDC_CAT_REMOVE, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnRemoveCat->SetToolTip( wxT("Remove selected categories") );
	
	bSizer74->Add( m_btnRemoveCat, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );
	
	
	sbSizer5->Add( bSizer74, 0, wxEXPAND, 5 );
	
	
	mainSizer->Add( sbSizer5, 1, wxEXPAND|wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Diagrams") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer22->AddGrowableCol( 0 );
	fgSizer22->AddGrowableRow( 0 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxVERTICAL );
	
	m_lstDiagrams = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	m_lstDiagrams->SetMinSize( wxSize( 300,-1 ) );
	
	bSizer76->Add( m_lstDiagrams, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	m_staticText78 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText78->Wrap( -1 );
	bSizer76->Add( m_staticText78, 0, wxTOP|wxRIGHT, 5 );
	
	m_textDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,75 ), wxTE_MULTILINE|wxTE_READONLY );
	m_textDescription->SetMaxLength( 0 ); 
	bSizer76->Add( m_textDescription, 0, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	m_staticText75 = new wxStaticText( this, wxID_ANY, wxT("Dependencies:"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_staticText75->Wrap( -1 );
	bSizer76->Add( m_staticText75, 0, wxTOP|wxRIGHT, 5 );
	
	m_lstDeps = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VRULES );
	bSizer76->Add( m_lstDeps, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	fgSizer22->Add( bSizer76, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer77;
	bSizer77 = new wxBoxSizer( wxVERTICAL );
	
	m_btnRemoveDiag = new wxButton( this, IDC_DIAG_REMOVE, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnRemoveDiag->SetToolTip( wxT("Remove selected diagrams") );
	
	bSizer77->Add( m_btnRemoveDiag, 0, wxBOTTOM, 5 );
	
	m_btnRemoveAllDiag = new wxButton( this, IDM_DIAG_REMOVEALL, wxT("Remove all"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer77->Add( m_btnRemoveAllDiag, 0, wxBOTTOM, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer77->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	m_btnCopyDiag = new wxButton( this, IDM_DIAG_COPY, wxT("Copy to..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnCopyDiag->SetToolTip( wxT("Copy dialog to another category") );
	
	bSizer77->Add( m_btnCopyDiag, 0, wxTOP|wxBOTTOM, 5 );
	
	m_btnMoveDiag = new wxButton( this, IDC_DIAG_MOVE, wxT("Move to..."), wxDefaultPosition, wxDefaultSize, 0 );
	m_btnMoveDiag->SetToolTip( wxT("Move to another category") );
	
	bSizer77->Add( m_btnMoveDiag, 0, wxEXPAND|wxBOTTOM, 5 );
	
	
	fgSizer22->Add( bSizer77, 1, wxEXPAND, 5 );
	
	
	sbSizer6->Add( fgSizer22, 1, wxEXPAND, 5 );
	
	
	mainSizer->Add( sbSizer6, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	mainSizer->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_btnClose = new wxButton( this, wxID_OK, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	mainSizer->Add( m_btnClose, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_lbCategories->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ManageBankDialog::OnCategoryChange ), NULL, this );
	m_btnCreateCat->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnCreateCat ), NULL, this );
	m_btnRenameCat->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRenameCat ), NULL, this );
	m_btnRenameCat->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRenameCat ), NULL, this );
	m_btnRemoveCat->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveCat ), NULL, this );
	m_btnRemoveCat->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveCat ), NULL, this );
	m_lstDiagrams->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( _ManageBankDialog::OnDiagramChange ), NULL, this );
	m_btnRemoveDiag->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveDiag ), NULL, this );
	m_btnRemoveDiag->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveDiag ), NULL, this );
	m_btnRemoveAllDiag->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveAllDiag ), NULL, this );
	m_btnRemoveAllDiag->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveAllDiag ), NULL, this );
	m_btnCopyDiag->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnCopyDiag ), NULL, this );
	m_btnCopyDiag->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateCopyTo ), NULL, this );
	m_btnMoveDiag->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnMoveDiag ), NULL, this );
	m_btnMoveDiag->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateMoveTo ), NULL, this );
}

_ManageBankDialog::~_ManageBankDialog()
{
	// Disconnect Events
	m_lbCategories->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ManageBankDialog::OnCategoryChange ), NULL, this );
	m_btnCreateCat->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnCreateCat ), NULL, this );
	m_btnRenameCat->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRenameCat ), NULL, this );
	m_btnRenameCat->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRenameCat ), NULL, this );
	m_btnRemoveCat->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveCat ), NULL, this );
	m_btnRemoveCat->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveCat ), NULL, this );
	m_lstDiagrams->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( _ManageBankDialog::OnDiagramChange ), NULL, this );
	m_btnRemoveDiag->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveDiag ), NULL, this );
	m_btnRemoveDiag->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveDiag ), NULL, this );
	m_btnRemoveAllDiag->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnRemoveAllDiag ), NULL, this );
	m_btnRemoveAllDiag->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateRemoveAllDiag ), NULL, this );
	m_btnCopyDiag->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnCopyDiag ), NULL, this );
	m_btnCopyDiag->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateCopyTo ), NULL, this );
	m_btnMoveDiag->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManageBankDialog::OnMoveDiag ), NULL, this );
	m_btnMoveDiag->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( _ManageBankDialog::OnUpdateMoveTo ), NULL, this );
	
}

_ManagePluginsDialog::_ManagePluginsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* recordsSizer;
	recordsSizer = new wxFlexGridSizer( 1, 2, 0, 0 );
	recordsSizer->AddGrowableCol( 0 );
	recordsSizer->AddGrowableCol( 1 );
	recordsSizer->AddGrowableRow( 0 );
	recordsSizer->SetFlexibleDirection( wxBOTH );
	recordsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* pluginsSizer;
	pluginsSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Available plugins:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	pluginsSizer->Add( m_staticText13, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_checkListPluginsChoices;
	m_checkListPlugins = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 200,300 ), m_checkListPluginsChoices, 0 );
	m_checkListPlugins->SetMinSize( wxSize( 200,300 ) );
	
	pluginsSizer->Add( m_checkListPlugins, 1, wxEXPAND|wxALL, 5 );
	
	
	recordsSizer->Add( pluginsSizer, 1, wxEXPAND, 5 );
	
	m_listCtrlPluginInfo = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 350,-1 ), wxLC_HRULES|wxLC_REPORT|wxSUNKEN_BORDER );
	m_listCtrlPluginInfo->SetFont( wxFont( 9, 77, 90, 90, false, wxT("Arial") ) );
	m_listCtrlPluginInfo->SetBackgroundColour( wxColour( 229, 229, 229 ) );
	m_listCtrlPluginInfo->SetMinSize( wxSize( 350,-1 ) );
	
	recordsSizer->Add( m_listCtrlPluginInfo, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	mainSizer->Add( recordsSizer, 1, wxEXPAND, 5 );
	
	buttonSizer = new wxStdDialogButtonSizer();
	buttonSizerOK = new wxButton( this, wxID_OK );
	buttonSizer->AddButton( buttonSizerOK );
	buttonSizerCancel = new wxButton( this, wxID_CANCEL );
	buttonSizer->AddButton( buttonSizerCancel );
	buttonSizer->Realize();
	
	mainSizer->Add( buttonSizer, 0, wxEXPAND|wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ManagePluginsDialog::OnInitDialog ) );
	m_checkListPlugins->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ManagePluginsDialog::OnPluginSelected ), NULL, this );
	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManagePluginsDialog::OnOk ), NULL, this );
}

_ManagePluginsDialog::~_ManagePluginsDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _ManagePluginsDialog::OnInitDialog ) );
	m_checkListPlugins->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _ManagePluginsDialog::OnPluginSelected ), NULL, this );
	buttonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _ManagePluginsDialog::OnOk ), NULL, this );
	
}

_SynchronizeDialog::_SynchronizeDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Select code items which should be updated:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	mainSizer->Add( m_staticText16, 0, wxTOP|wxRIGHT|wxLEFT, 5 );
	
	wxArrayString m_checkListChoices;
	m_checkList = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), m_checkListChoices, 0 );
	m_checkList->SetMinSize( wxSize( -1,150 ) );
	
	menuCheckList = new wxMenu();
	wxMenuItem* menuSelectAll;
	menuSelectAll = new wxMenuItem( menuCheckList, IDM_SYNCHRO_SELECT_ALL, wxString( wxT("Select all") ) , wxEmptyString, wxITEM_NORMAL );
	menuCheckList->Append( menuSelectAll );
	
	wxMenuItem* menuDeselectAll;
	menuDeselectAll = new wxMenuItem( menuCheckList, IDM_SYNCHRO_DESELECT_ALL, wxString( wxT("Deselect all") ) , wxEmptyString, wxITEM_NORMAL );
	menuCheckList->Append( menuDeselectAll );
	
	m_checkList->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( _SynchronizeDialog::m_checkListOnContextMenu ), NULL, this ); 
	
	mainSizer->Add( m_checkList, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* compareSizer;
	compareSizer = new wxFlexGridSizer( 2, 2, 0, 0 );
	compareSizer->AddGrowableCol( 0 );
	compareSizer->AddGrowableCol( 1 );
	compareSizer->AddGrowableRow( 1 );
	compareSizer->SetFlexibleDirection( wxBOTH );
	compareSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("In generated files:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	compareSizer->Add( m_staticText14, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("In CodeDesigner:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	compareSizer->Add( m_staticText15, 0, wxALL, 5 );
	
	m_scintillaModified = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,200 ), 0, wxEmptyString );
	m_scintillaModified->SetUseTabs( true );
	m_scintillaModified->SetTabWidth( 4 );
	m_scintillaModified->SetIndent( 4 );
	m_scintillaModified->SetTabIndents( true );
	m_scintillaModified->SetBackSpaceUnIndents( true );
	m_scintillaModified->SetViewEOL( false );
	m_scintillaModified->SetViewWhiteSpace( false );
	m_scintillaModified->SetMarginWidth( 2, 0 );
	m_scintillaModified->SetIndentationGuides( true );
	m_scintillaModified->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_scintillaModified->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_scintillaModified->SetMarginWidth( 1, 16);
	m_scintillaModified->SetMarginSensitive( 1, true );
	m_scintillaModified->SetProperty( wxT("fold"), wxT("1") );
	m_scintillaModified->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_scintillaModified->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_scintillaModified->SetMarginWidth( 0, m_scintillaModified->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_scintillaModified->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_scintillaModified->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_scintillaModified->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_scintillaModified->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_scintillaModified->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_scintillaModified->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_scintillaModified->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_scintillaModified->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_scintillaModified->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_scintillaModified->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_scintillaModified->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	compareSizer->Add( m_scintillaModified, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	m_scintillaOriginal = new wxStyledTextCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,200 ), 0, wxEmptyString );
	m_scintillaOriginal->SetUseTabs( true );
	m_scintillaOriginal->SetTabWidth( 4 );
	m_scintillaOriginal->SetIndent( 4 );
	m_scintillaOriginal->SetTabIndents( true );
	m_scintillaOriginal->SetBackSpaceUnIndents( true );
	m_scintillaOriginal->SetViewEOL( false );
	m_scintillaOriginal->SetViewWhiteSpace( false );
	m_scintillaOriginal->SetMarginWidth( 2, 0 );
	m_scintillaOriginal->SetIndentationGuides( true );
	m_scintillaOriginal->SetMarginType( 1, wxSTC_MARGIN_SYMBOL );
	m_scintillaOriginal->SetMarginMask( 1, wxSTC_MASK_FOLDERS );
	m_scintillaOriginal->SetMarginWidth( 1, 16);
	m_scintillaOriginal->SetMarginSensitive( 1, true );
	m_scintillaOriginal->SetProperty( wxT("fold"), wxT("1") );
	m_scintillaOriginal->SetFoldFlags( wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED );
	m_scintillaOriginal->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	m_scintillaOriginal->SetMarginWidth( 0, m_scintillaOriginal->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDER, wxSTC_MARK_BOXPLUS );
	m_scintillaOriginal->MarkerSetBackground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("BLACK") ) );
	m_scintillaOriginal->MarkerSetForeground( wxSTC_MARKNUM_FOLDER, wxColour( wxT("WHITE") ) );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_BOXMINUS );
	m_scintillaOriginal->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("BLACK") ) );
	m_scintillaOriginal->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPEN, wxColour( wxT("WHITE") ) );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_EMPTY );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUS );
	m_scintillaOriginal->MarkerSetBackground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("BLACK") ) );
	m_scintillaOriginal->MarkerSetForeground( wxSTC_MARKNUM_FOLDEREND, wxColour( wxT("WHITE") ) );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUS );
	m_scintillaOriginal->MarkerSetBackground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("BLACK") ) );
	m_scintillaOriginal->MarkerSetForeground( wxSTC_MARKNUM_FOLDEROPENMID, wxColour( wxT("WHITE") ) );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY );
	m_scintillaOriginal->MarkerDefine( wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_EMPTY );
	m_scintillaOriginal->SetSelBackground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );
	m_scintillaOriginal->SetSelForeground( true, wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHTTEXT ) );
	compareSizer->Add( m_scintillaOriginal, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );
	
	
	mainSizer->Add( compareSizer, 1, wxEXPAND, 5 );
	
	buttonSizer = new wxStdDialogButtonSizer();
	buttonSizerOK = new wxButton( this, wxID_OK );
	buttonSizer->AddButton( buttonSizerOK );
	buttonSizerCancel = new wxButton( this, wxID_CANCEL );
	buttonSizer->AddButton( buttonSizerCancel );
	buttonSizer->Realize();
	
	mainSizer->Add( buttonSizer, 0, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_checkList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnSelectCodeItem ), NULL, this );
	this->Connect( menuSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnSelectAll ) );
	this->Connect( menuDeselectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnDeselectAll ) );
	buttonSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SynchronizeDialog::OnOk ), NULL, this );
}

_SynchronizeDialog::~_SynchronizeDialog()
{
	// Disconnect Events
	m_checkList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnSelectCodeItem ), NULL, this );
	this->Disconnect( IDM_SYNCHRO_SELECT_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnSelectAll ) );
	this->Disconnect( IDM_SYNCHRO_DESELECT_ALL, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( _SynchronizeDialog::OnDeselectAll ) );
	buttonSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _SynchronizeDialog::OnOk ), NULL, this );
	
	delete menuCheckList; 
}

_GroupDialog::_GroupDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 460,-1 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxGridBagSizer* controlSizer;
	controlSizer = new wxGridBagSizer( 0, 0 );
	controlSizer->SetFlexibleDirection( wxBOTH );
	controlSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	controlSizer->Add( m_staticText1, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_eName->SetMaxLength( 0 ); 
	controlSizer->Add( m_eName, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Description:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	controlSizer->Add( m_staticText2, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxTOP|wxRIGHT|wxLEFT, 5 );
	
	m_eDescription = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 400,100 ), wxTE_MULTILINE );
	m_eDescription->SetMaxLength( 0 ); 
	m_eDescription->SetMinSize( wxSize( 400,100 ) );
	
	controlSizer->Add( m_eDescription, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxEXPAND|wxALL, 5 );
	
	m_pNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_pageAdv = new wxPanel( m_pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* groupSizer;
	groupSizer = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText70 = new wxStaticText( m_pageAdv, wxID_ANY, wxT("Group color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText70->Wrap( -1 );
	groupSizer->Add( m_staticText70, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_colourPicker = new wxColourPickerCtrl( m_pageAdv, wxID_ANY, wxColour( 200, 255, 200 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	groupSizer->Add( m_colourPicker, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_pageAdv->SetSizer( groupSizer );
	m_pageAdv->Layout();
	groupSizer->Fit( m_pageAdv );
	m_pNotebook->AddPage( m_pageAdv, wxT("Advanced"), true );
	
	controlSizer->Add( m_pNotebook, wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );
	
	bntSizer = new wxStdDialogButtonSizer();
	bntSizerOK = new wxButton( this, wxID_OK );
	bntSizer->AddButton( bntSizerOK );
	bntSizerCancel = new wxButton( this, wxID_CANCEL );
	bntSizer->AddButton( bntSizerCancel );
	bntSizer->Realize();
	
	controlSizer->Add( bntSizer, wxGBPosition( 5, 0 ), wxGBSpan( 1, 1 ), wxALIGN_RIGHT|wxEXPAND|wxBOTTOM|wxRIGHT, 5 );
	
	
	controlSizer->AddGrowableCol( 0 );
	controlSizer->AddGrowableRow( 3 );
	
	mainSizer->Add( controlSizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	mainSizer->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _GroupDialog::OnInitDialog ) );
	bntSizerOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _GroupDialog::OnOk ), NULL, this );
}

_GroupDialog::~_GroupDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( _GroupDialog::OnInitDialog ) );
	bntSizerOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( _GroupDialog::OnOk ), NULL, this );
	
}
