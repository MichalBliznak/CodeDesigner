/***************************************************************
 * Name:      UMLDesignerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-10
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/

#include "wx_pch.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/artprov.h>
#include <wx/filedlg.h>
#include <wx/wupdlock.h>
#include <wx/aboutdlg.h>
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/txtstrm.h>
#include <wx/settings.h>
#include <wx/dcsvg.h>

#include <wx/arrimpl.cpp>
#include <wx/listimpl.cpp>

#include "BuildNum.h"

#include "Art.h"
#include "Ids.h"
#include "UMLDesignerMain.h"
#include "gui/SettingsDialog.h"
#include "projectbase/gui/AccessTypeDialog.h"
#include "gui/StoreToBankDialog.h"
#include "gui/InsertFromBankDialog.h"
#include "gui/Editor.h"
#include "gui/ManageBankDialog.h"
#include "gui/ManagePluginsDialog.h"
#include "gui/SynchronizeDialog.h"
#include "gui/TabArt.h"
#include "projectbase/shapes/DnDElement.h"

WX_DEFINE_OBJARRAY(DiagramsArray);

WX_DEFINE_LIST(ListenerList);

// short term todos:
//------------------

// TODO: support for namespace in class diagram (implemented as a uml package)

// long term todos:
//-----------------

// TODO: implement languages by using XML templates/XSLT(???)
// TODO: implement parallel states in HSCH
// TODO: implement QuantumLeaps code generator
// TODO: implement re-arrangement of elements in diagram for code generation (???)

// global static objects
bool UMLDesignerFrame::m_fDispatchEvents = true;

enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

////////////////////////////////////////////////////////////////////////////////
// Main frame

BEGIN_EVENT_TABLE(UMLDesignerFrame, _MainFrame)
    EVT_MENU_RANGE(IDM_PROJ_MIN_DIAG_ID, IDM_PROJ_MAX_DIAG_ID,  UMLDesignerFrame::OnCreateDiagram)
	EVT_MENU(IDM_DELAYED_REMOVE, UMLDesignerFrame::OnDelayedRemove)
	EVT_MENU(IDM_DELAYED_REMOVEELEMENT, UMLDesignerFrame::OnDelayedRemoveElement)
	EVT_MENU(IDM_DELAYED_REMOVEALL, UMLDesignerFrame::OnDelayedRemoveAll)
	EVT_MENU(IDM_DELAYED_EDIT, UMLDesignerFrame::OnDelayedEdit)
	EVT_MENU(IDM_DELAYED_EDITELEMENT, UMLDesignerFrame::OnDelayedEdit)
	EVT_MENU(IDM_DELAYED_CUTELEMENT, UMLDesignerFrame::OnDelayedCutElement)
	EVT_MENU_RANGE(IDM_DELAYED_EDITCODE, IDM_DELAYED_EDITCODE + udvMAX_ITEMS - 1, UMLDesignerFrame::OnDelayedEditCode)

	EVT_MENU(IDM_DIAG_SHOW, UMLDesignerFrame::OnShowDiagram)
	EVT_MENU(IDM_DIAG_SHOWPREVIEW, UMLDesignerFrame::OnShowPreviewDiagram)
	EVT_MENU(IDM_DIAG_NAVIGATETO, UMLDesignerFrame::OnNavigateTo)
	EVT_MENU(IDM_DIAG_REMOVEELEMENT, UMLDesignerFrame::OnRemoveElement)
	EVT_MENU(IDM_DIAG_STORETOBANK, UMLDesignerFrame::OnStoreToBank)
	EVT_MENU(IDM_DIAG_INSERTFROMBANK, UMLDesignerFrame::OnInsertFromBank)
	EVT_MENU_RANGE(IDM_DIAG_CLEARVARIABLES, IDM_DIAG_CLEARFUNCTIONS, UMLDesignerFrame::OnClearCodeItems)
	EVT_MENU(IDM_PROJ_EDIT, UMLDesignerFrame::OnEditItem)

	EVT_MENU(wxID_ZOOM_100, UMLDesignerFrame::OnZoom100)
	EVT_MENU(wxID_ZOOM_FIT, UMLDesignerFrame::OnZoomAll)
	
	EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, UMLDesignerFrame::OnRecentFile)

	EVT_MENU_RANGE(IDT_PALETTE_MIN_TOOL_ID + udvTOOLS_CNT, IDT_PALETTE_MAX_TOOL_ID + udvTOOLS_CNT, UMLDesignerFrame::OnCreateDiagramElement)
	
	EVT_MENU_RANGE(IDM_VIEW_MIN_PLUGINPANE_ID, IDM_VIEW_MIN_PLUGINPANE_ID + udvMAX_ITEMS, UMLDesignerFrame::OnToggleGUI)

    EVT_TOOL(IDT_GRID, UMLDesignerFrame::OnGrid)
    EVT_TOOL_RANGE(wxID_PRINT, wxID_PREVIEW, UMLDesignerFrame::OnStandardOpp)
    EVT_TOOL_RANGE(wxID_UNDO, wxID_REDO, UMLDesignerFrame::OnStandardOpp)
    EVT_TOOL_RANGE(wxID_CUT, wxID_PASTE, UMLDesignerFrame::OnStandardOpp)
    EVT_TOOL_RANGE(IDT_PALETTE_MIN_TOOL_ID, IDT_PALETTE_MAX_TOOL_ID, UMLDesignerFrame::OnPalettes)
    EVT_TOOL_RANGE(IDT_ALIGN_LEFT, IDT_ALIGN_CENTER, UMLDesignerFrame::OnAlignSelected)
    EVT_TOOL_RANGE(IDT_ALIGN_CIRCLE, IDT_ALIGN_HTREE, UMLDesignerFrame::OnAutolayout)

    EVT_CHOICE(IDC_CHOICE_LANGUAGES, UMLDesignerFrame::OnLanguageChoice)
    EVT_CHOICE(IDC_CHOICE_GENERATORS, UMLDesignerFrame::OnGeneratorChoice)
    EVT_CHOICE(IDC_CHOICE_ALGORITHMS, UMLDesignerFrame::OnAlgorithmChoice)

    EVT_UPDATE_UI(IDT_GRID, UMLDesignerFrame::OnUpdateGrid)
    EVT_UPDATE_UI_RANGE(IDC_CHOICE_LANGUAGES, IDC_CHOICE_GENERATORS, UMLDesignerFrame::OnUpdateChoices)
    EVT_UPDATE_UI_RANGE(IDM_PROJ_MIN_DIAG_ID, IDM_PROJ_MAX_DIAG_ID, UMLDesignerFrame::OnUpdateCreateDiagram)
    EVT_UPDATE_UI_RANGE(wxID_UNDO, wxID_REDO, UMLDesignerFrame::OnUpdateStandardOpp)
    EVT_UPDATE_UI_RANGE(wxID_CUT, wxID_PASTE, UMLDesignerFrame::OnUpdateStandardOpp)
    EVT_UPDATE_UI_RANGE(IDT_ALIGN_LEFT, IDT_ALIGN_CENTER, UMLDesignerFrame::OnUpdateAlignSelected)
    EVT_UPDATE_UI_RANGE(IDT_ALIGN_CIRCLE, IDT_ALIGN_HTREE, UMLDesignerFrame::OnUpdateCanvasActivated)
    EVT_UPDATE_UI_RANGE(IDT_PALETTE_MIN_TOOL_ID, IDT_PALETTE_MAX_TOOL_ID, UMLDesignerFrame::OnUpdatePalettes)
	EVT_UPDATE_UI_RANGE(IDM_VIEW_MIN_PLUGINPANE_ID, IDM_VIEW_MIN_PLUGINPANE_ID + udvMAX_ITEMS, UMLDesignerFrame::OnUpdateToggleGUI)
	
	EVT_CD_ITEM_SELECTED( wxID_ANY, UMLDesignerFrame::OnProjectItemSelected )
	EVT_CD_ITEM_CHANGED( wxID_ANY, UMLDesignerFrame::OnProjectItemChanged )
	EVT_CD_ITEM_ADDED( wxID_ANY, UMLDesignerFrame::OnProjectItemAdded)
	EVT_CD_ITEM_REMOVED( wxID_ANY, UMLDesignerFrame::OnProjectItemRemoved )
	EVT_CD_TASK_REMOVE( wxID_ANY, UMLDesignerFrame::OnProjectTaskRemove )
END_EVENT_TABLE()

void UMLDesignerFrame::InitializeComponents()
{
	// create palettes map infos

	// Common palette
	PaletteArray *arrCPalette = new PaletteArray();
	m_mapElementPalettes[udnCOMMON_ITEMS] = arrCPalette;

	arrCPalette->Add(udPaletteItem(udPluginManager::GetNewComponentId(), wxT("app/elements/Bound.xpm"), wxT("Group"), wxT("uddGroupItem"), wxT("udGroupElementItem"), udPaletteItem::pitELEMENT));
	arrCPalette->Add(udPaletteItem(udPluginManager::GetNewComponentId(), wxT("app/elements/Note.xpm"), wxT("Note"), wxT("uddNoteItem"), wxT("udNoteElementItem"), udPaletteItem::pitELEMENT));
	arrCPalette->Add(udPaletteItem(udPluginManager::GetNewComponentId(), wxT("app/elements/LineNote.xpm"), wxT("Note connection"), wxT("uddNoteConnItem"), wxT("udNoteConnElementItem"), udPaletteItem::pitCONNECTION));

	// create GUI components' info
	m_mapGUIComponents[IDM_VIEW_PROJECT_PANEL] = new udPanelItem(wxT("project_manager"), wxT("Project manager"));
    m_mapGUIComponents[IDM_VIEW_LOG_PANEL] = new udPanelItem(wxT("log_window"), wxT("Log window"));
    m_mapGUIComponents[IDM_VIEW_THUMBNAIL_PANEL] = new udPanelItem(wxT("thumbnail_window"), wxT("Thumbnail"));
    m_mapGUIComponents[IDM_VIEW_EDITOR] = new udPanelItem(wxT("editor_window"), wxT("Code editor"));
    m_mapGUIComponents[IDM_VIEW_FILE_TB] = new udPanelItem(wxT("file_toolbar"), wxT("File toolbar"));
    m_mapGUIComponents[IDM_VIEW_DIAGRAM_TB] = new udPanelItem(wxT("diagram_toolbar"), wxT("Diagram toolbar"));
    m_mapGUIComponents[IDM_VIEW_LAYOUT_TB] = new udPanelItem(wxT("layout_toolbar"), wxT("Layout toolbar"));
    m_mapGUIComponents[IDM_VIEW_GENERATOR_TB] = new udPanelItem(wxT("generator_toolbar"), wxT("Generator toolbar"));

	// initialize code items types
	m_mapProjectItems[IDM_PROJ_PACKAGE] = new udProjectItemType(wxT("udPackageItem"), wxT("Project items"), udProjectItemType::pitPROJITEM);
	m_mapProjectItems[IDM_PROJ_CODEPACKAGE] = new udProjectItemType(wxT("udCodePackageItem"), wxT("Code items"), udProjectItemType::pitCODEITEM);
	m_mapProjectItems[IDM_PROJ_VARIABLE] = new udProjectItemType(wxT("udGenericVariableItem"), wxT("Code items"), udProjectItemType::pitCODEITEM);
	m_mapProjectItems[IDM_PROJ_FUNCTION] = new udProjectItemType(wxT("udGenericFunctionItem"), wxT("Code items"), udProjectItemType::pitCODEITEM);
	
	m_mapProjectItems[IDM_DIAG_CLEARVARIABLES] = new udProjectItemType(wxT("udVariableItem"), wxT("Code items"), udProjectItemType::pitCODEITEM);
	m_mapProjectItems[IDM_DIAG_CLEARFUNCTIONS] = new udProjectItemType(wxT("udFunctionItem"), wxT("Code items"), udProjectItemType::pitCODEITEM);
	
	// default package names
	m_mapDefaultPkgNames[wxT("udGenericVariableItem")] = wxT("Generic variables");
	m_mapDefaultPkgNames[wxT("udGenericFunctionItem")] = wxT("Generic functions");
}

void UMLDesignerFrame::CleanUpComponents()
{
	wxArrayInt arrAlreadyDeleted;
	
	// clean component info
	PalettesMap::iterator it;
	for( it = m_mapElementPalettes.begin(); it != m_mapElementPalettes.end(); ++it )
    {
		if(it->second)
		{
			it->second->Clear();
			delete it->second;
		}
	}
	
	// clean code items info
	ProjectItemMap::iterator it2;
	for( it2 = m_mapProjectItems.begin(); it2 != m_mapProjectItems.end(); ++it2 )
	{
		if( it2->second && (arrAlreadyDeleted.Index((wxUIntPtr)it2->second) == wxNOT_FOUND) )
		{
			arrAlreadyDeleted.Add( (wxUIntPtr)it2->second );
			delete it2->second;
		}
	}
	
	// clear gui info
	PanelMap::iterator it3;
	for( it3 = m_mapGUIComponents.begin(); it3 != m_mapGUIComponents.end(); ++it3 )
    {
		if(it3->second)
		{
			delete it3->second;
		}
	}
}

void UMLDesignerFrame::InitializeLayoutAlgorithms()
{
	wxSFAutoLayout layout;
	
	// "Mesh" algorithm
	wxSFLayoutMesh *pMeshAlg = wxDynamicCast( layout.GetAlgorithm( wxT("Mesh") ), wxSFLayoutMesh );
	if( pMeshAlg )
	{
		pMeshAlg->SetHSpace( 50 );
		pMeshAlg->SetVSpace( 50 );
	}
	
	// "Horizontal Tree" algorithm
	wxSFLayoutHorizontalTree *pHTAlg = wxDynamicCast( layout.GetAlgorithm( wxT("Horizontal Tree") ), wxSFLayoutHorizontalTree );
	if( pHTAlg )
	{
		pHTAlg->SetHSpace( 50 );
		pHTAlg->SetVSpace( 50 );
	}
	
	// "Vertical Tree" algorithm
	wxSFLayoutVerticalTree *pVTAlg = wxDynamicCast( layout.GetAlgorithm( wxT("Vertical Tree") ), wxSFLayoutVerticalTree );
	if( pVTAlg )
	{
		pVTAlg->SetHSpace( 50 );
		pVTAlg->SetVSpace( 50 );
	}
}

UMLDesignerFrame::UMLDesignerFrame(wxFrame *frame)
    : _MainFrame(frame)
{
	m_fClosing = false;
	m_fResetLayout = false;
	m_pProcessedItem = NULL;
	m_nCurrentToolId = IDT_DESIGN_TOOL_ID;
	
	SetTitle( wxT("CodeDesigner RAD") );
	
	udSettings &Settings = wxGetApp().GetSettings();
//	const wxString &sAppPath = wxGetApp().GetPath();
	wxString sResPath = wxGetApp().GetResourcesPath();
	
	// initialize application's components
	InitializeComponents();
	InitializeLayoutAlgorithms();
	
	// initialize artwork
	udArt::Initialize();
	
	// register main frame as a internal events listener
	RegisterEventListener( this );
	
	// initialize plugins
	wxGetApp().GetPluginManager().SetManagedFrame( this );
	wxGetApp().GetPluginManager().InitializePlugins();
	
	//SetSize( wxSystemSettings::GetMetric( wxSYS_SCREEN_X ), wxSystemSettings::GetMetric( wxSYS_SCREEN_Y ) );
	SetSize( 1024, 786 );
	
	// set application icon
	#ifdef __WXMSW__
	SetIcon(wxIcon(sResPath + wxT("app/gui/application-icon.ico"), wxBITMAP_TYPE_ICO));
	#else
	SetIcon(wxIcon(sResPath + wxT("app/gui/application-icon.png"), wxBITMAP_TYPE_PNG));
	#endif

    m_AUIManager.SetManagedWindow(this);
	// set some commont AUI attributes

    m_AUIManager.SetFlags( m_AUIManager.GetFlags() | wxAUI_MGR_ALLOW_ACTIVE_PANE );
	m_AUIManager.GetArtProvider()->SetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE, 0);
	m_AUIManager.GetArtProvider()->SetMetric(wxAUI_DOCKART_SASH_SIZE, 4);
	
	wxColour col = Settings.GetProperty( wxT("Background colour") )->AsColour();
	
	m_AUIManager.GetArtProvider()->SetColour( wxAUI_DOCKART_BACKGROUND_COLOUR, col );
	m_AUIManager.GetArtProvider()->SetColour( wxAUI_DOCKART_SASH_COLOUR, col );
	//m_AUIManager.GetArtProvider()->SetColour( wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR, col );
	
	m_auintbPalettes->SetArtProvider( new udTabArt() );
	m_auintbDesignArea->SetArtProvider( new udTabArt() );

    // main dynamicaly created application components...
    CreateDynMenu();
	CreatePopupMenu();
    CreateMainToolbars();
	CreateMainMenus();
	CreateRecentFilesMenu();
    CreatePalettes();
    CreateProjectManager();
	CreateLogWindow();
    CreateThumbnail();
	CreateInstantEditor();
	
	udPluginManager& Mgr = wxGetApp().GetPluginManager();

    // ... and attach them into managed panes
    m_AUIManager.AddPane(m_mainPanel, wxAuiPaneInfo().Name(wxT("design_area")).
                        Caption(wxT("Design area")).MaximizeButton().MinimizeButton().
						CloseButton(false).Center());

	m_AUIManager.AddPane(m_pProjectManager, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("project_manager")).Caption(wxT("Project inspector")).
						BestSize(wxSize(250,400)).MinSize(wxSize(250,400)).
						Left().Layer(1));
						
    m_AUIManager.AddPane(m_pLogPanel, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("log_window")).Caption(wxT("Log window")).
						BestSize(wxSize(640,100)).Bottom().Position(0));
						
    m_AUIManager.AddPane(m_pInstantEditor, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("editor_window")).Caption(wxT("Code editor")).
						BestSize(wxSize(300,100)).Bottom().Position(1).Show(false));
						
    m_AUIManager.AddPane(m_pThumbnail, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("thumbnail_window")).Caption(wxT("Thumbnail")).
                        BestSize(wxSize(200,100)).Bottom().Position(2));
						
	// add plugins' panes
	long nIndex = 0;
	for( PluginList::iterator it = Mgr.GetPluginsList().begin(); it != Mgr.GetPluginsList().end(); ++it )
	{
		udPaneInfo Info = (*it)->CreateAuiPane( this );
		if( Info.GetPane() )
		{
			m_AUIManager.AddPane( Info.GetPane(), wxAuiPaneInfo().DestroyOnClose(false).Name(Info.GetName()).
								  Caption(Info.GetName()).BestSize(Info.GetBestSize()).MinSize(Info.GetBestSize()).
								  Left().Layer(2) );
			// create menu item
			if( nIndex == 0 ) viewMenu->AppendSeparator();
			viewMenu->AppendCheckItem( IDM_VIEW_MIN_PLUGINPANE_ID + nIndex, Info.GetName() );
			// update GUI components info
			m_mapGUIComponents[IDM_VIEW_MIN_PLUGINPANE_ID + nIndex++] = new udPanelItem( Info.GetName(), Info.GetName() );
		}
	}
						
	// add standard toolbars
	m_AUIManager.AddPane(m_tbMainFrame, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("file_toolbar")).Caption(wxT("File toolbar")).
                        Top().LeftDockable(false).RightDockable(false).ToolbarPane());

	m_AUIManager.AddPane(m_tbProjectItems, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("diagram_toolbar")).Caption(wxT("Diagram toolbar")).
                        Top().LeftDockable(false).RightDockable(false).ToolbarPane());

	m_AUIManager.AddPane(m_tbDesign, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("layout_toolbar")).Caption(wxT("Layout toolbar")).
                        Top().LeftDockable(false).RightDockable(false).ToolbarPane());

	m_AUIManager.AddPane(m_tbGenerator, wxAuiPaneInfo().DestroyOnClose(false).
                        Name(wxT("generator_toolbar")).Caption(wxT("Generator toolbar")).
                        Top().Row(1).LeftDockable(false).RightDockable(false).ToolbarPane());
						
	// add plugins' toolbars
	for( PluginList::iterator it = Mgr.GetPluginsList().begin(); it != Mgr.GetPluginsList().end(); ++it )
	{
		udToolbarInfo TbInfo = (*it)->CreateToolbar( this );
		if( TbInfo.GetToolbar() )
		{
			TbInfo.GetToolbar()->SetArtProvider( new udToolArt() );
			
			m_AUIManager.AddPane( TbInfo.GetToolbar(), wxAuiPaneInfo().DestroyOnClose(false).
								 Name(TbInfo.GetName()).Caption(TbInfo.GetName()).Top().Row(2).LeftDockable(false).
								 RightDockable(false).ToolbarPane());
								 
			// create menu item
			if( nIndex == 0 ) viewMenu->AppendSeparator();
			viewMenu->AppendCheckItem( IDM_VIEW_MIN_PLUGINPANE_ID + nIndex, TbInfo.GetName() );
			// update GUI components info
			m_mapGUIComponents[IDM_VIEW_MIN_PLUGINPANE_ID + nIndex++] = new udPanelItem( TbInfo.GetName(), TbInfo.GetName() );
		}
	}

    // fill language choice box
    LanguageMap::iterator lit = wxGetApp().GetLanguages().begin();
    while(lit != wxGetApp().GetLanguages().end())
    {
        m_chLanguages->Append(((udLanguage*)lit->second)->GetName());
        lit++;
    }
    m_chLanguages->SetStringSelection(wxGetApp().GetLanguages().find(udProject::Get()->GetSettings().GetPropertyAsString( wxT("active_language"), wxT("udCLanguage") ))->second->GetName());

#if wxUSE_STATUSBAR
    statusBar->SetStatusText(wxT("Ready"), 0);
#endif

	// set palettes min size
#ifdef __WXGTK__
#if wxVERSION_NUMBER >= 2904
	m_auintbPalettes->SetMinSize( wxSize( -1, 68 ) );
#else
	m_auintbPalettes->SetMinSize( wxSize( -1, 62 ) );
#endif
	btnZoom100->SetMinSize( wxSize( -1, 27 ) );
	btnZoomAll->SetMinSize( wxSize( -1, 27 ) );
#elif defined(__WXMSW__)
	m_auintbPalettes->SetMinSize( wxSize( -1, 58 ) );
#elif defined(__WXMAC__)
	m_auintbPalettes->SetMinSize( wxSize( -1, 58 ) );
#endif

	// maximize and center frame
	Center();
	Maximize();

	SetSelectedProjectItem( (udProjectItem*)udProject::Get()->GetRootItem() );
	
	// restore perspective if saved
	const wxString& sPerspective = Settings.GetProperty(wxT("Perspective"))->AsString();
	
	if( !sPerspective.IsEmpty() ) m_AUIManager.LoadPerspective( sPerspective, true );
	else
		m_AUIManager.Update();
	
	SetProjectModified( false );
}

UMLDesignerFrame::~UMLDesignerFrame()
{	
	// store current perspective
	udSettings& settings = wxGetApp().GetSettings();
	
	if( !m_fResetLayout ) settings.GetProperty(wxT("Perspective"))->AsString() = m_AUIManager.SavePerspective();	
	else
	{
		settings.GetProperty(wxT("Perspective"))->AsString() = wxEmptyString;	
		udWindowManager::Clear();
	}
		
	settings.GetProperty(wxT("Show elements in thumbnail"))->AsBool() = m_pThumbnail->GetThumbStyle() & wxSFThumbnail::tsSHOW_ELEMENTS;
	settings.GetProperty(wxT("Show connections in thumbnail"))->AsBool() = m_pThumbnail->GetThumbStyle() & wxSFThumbnail::tsSHOW_CONNECTIONS;
	
	// uninitialize plugins
	wxGetApp().GetPluginManager().UninitializePlugins();
	
	// perform clean-up
	m_AUIManager.UnInit();
	//wxFlatNotebook::CleanUp();

	delete m_pPopupMenu;

	// clean-up application's components
	CleanUpComponents();
	
	// clean-up artwork
	udArt::CleanUp();
	
	// clean-up layouting algorithms
	wxSFAutoLayout::CleanUp();
}

// gui creation /////////////////////////////////////////////////////////////////////

void UMLDesignerFrame::CreateDynMenu()
{
	wxMenuItem *pItem;

	for( int i = m_arrDiagrams.GetCount() - 1; i >= 0 ; i-- )
	{
        pItem = new wxMenuItem(projMenu, m_arrDiagrams[i].m_nId, wxT("Create ") + m_arrDiagrams[i].m_sName, wxT("Create new ") + m_arrDiagrams[i].m_sName + wxT(" and add it to the current package."));
        pItem->SetBitmap(udArt::GetBitmap(m_arrDiagrams[i].m_sClassName));
        projMenu->Insert(3, pItem);
	}
}

void UMLDesignerFrame::CreatePopupMenu()
{
	wxMenuItem *pItem;
	m_pPopupMenu = new wxMenu;
	
	wxString sResPath = wxGetApp().GetResourcesPath();

	// add 'Create' submenu
	m_pPopupMenu->Append(wxID_ANY, wxT("Create"), new wxMenu);
	// add static menu items

	m_pPopupMenu->AppendSeparator();

	pItem = new wxMenuItem(m_pPopupMenu, IDM_CODE_PREVIEW, wxT("Code preview"));
	//pItem->SetBitmap(udArt::GetBitmap(wxT("udICON_PREVIEW")));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/gui/spellcheck.png"), wxBITMAP_TYPE_PNG));
	m_pPopupMenu->Append(pItem);

	m_pPopupMenu->AppendSeparator();

	pItem = new wxMenuItem(m_pPopupMenu, wxID_UNDO, wxT("Undo\tCtrl+Z"));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/gui/undo.png"), wxBITMAP_TYPE_PNG));
	m_pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(m_pPopupMenu, wxID_REDO, wxT("Redo\tCtrl+Y"));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/gui/redo.png"), wxBITMAP_TYPE_PNG));
	m_pPopupMenu->Append(pItem);

	m_pPopupMenu->AppendSeparator();

	pItem = new wxMenuItem(m_pPopupMenu, wxID_PASTE, wxT("Paste\tCtrl+V"));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/gui/editpaste.png"), wxBITMAP_TYPE_PNG));
	m_pPopupMenu->Append(pItem);

	m_pPopupMenu->AppendSeparator();

	pItem = new wxMenuItem(m_pPopupMenu, wxID_ZOOM_100, wxT("Zoom 100%"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udICON_ZOOM100")));
	m_pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(m_pPopupMenu, wxID_ZOOM_FIT, wxT("Zoom to all"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udICON_ZOOMALL")));
	m_pPopupMenu->Append(pItem);

	m_pPopupMenu->AppendSeparator();

	m_pPopupMenu->Append(IDM_PROJ_EDIT, wxT("Edit properties..."));

	m_pPopupMenu->AppendSeparator();

	m_pPopupMenu->Append(wxID_ANY, wxT("Remove all"));
}

int UMLDesignerFrame::UpdateCreateSubmenu(wxMenu *submenu, const wxArrayString& items, bool clear)
{
	wxASSERT(submenu);
	if( !submenu )return 0;

	wxMenuItem *pItem;
	int nCount = 0;

	// delete previous menu content
	if( clear )
	{
        while( submenu->GetMenuItemCount() > 0 )
        {
            pItem = submenu->FindItemByPosition(0);
            submenu->Destroy(pItem);
        }
	}

	// create new menu items from the palette info
	udPaletteItem *pPaletteItem;

	for( size_t i = 0; i < items.GetCount(); i++)
	{
		pPaletteItem = GetPaletteTool(items[i]);
		if( pPaletteItem )
		{
			pItem = new wxMenuItem(submenu, pPaletteItem->m_nId + udvTOOLS_CNT, pPaletteItem->m_sDesc);
			pItem->SetBitmap(udArt::GetBitmap(pPaletteItem->m_sClassName));
			submenu->Append(pItem);
			nCount++;
		}
	}
	return nCount;
}

int UMLDesignerFrame::UpdateCreateSubmenu(wxMenu *submenu, PaletteArray *palette, int itemmask, bool clear)
{
	wxASSERT(submenu);
	if( !submenu )return 0;
	wxASSERT(palette);
	if( !palette )return 0;

	wxMenuItem *pItem;
	udPaletteItem *pPaletteItem;
	int nCount = 0;

	// delete previous menu content
	if( clear )
	{
        while( submenu->GetMenuItemCount() > 0 )
        {
            pItem = submenu->FindItemByPosition(0);
            submenu->Destroy(pItem);
        }
	}

	// create new menu items from the palette info
	for( size_t i = 0; i < palette->GetCount(); i++)
	{
		pPaletteItem = &palette->Item(i);
		
		if( itemmask & pPaletteItem->m_nType)
		{
			pItem = new wxMenuItem(submenu, pPaletteItem->m_nId + udvTOOLS_CNT, pPaletteItem->m_sDesc);
			pItem->SetBitmap(udArt::GetBitmap(pPaletteItem->m_sClassName));
			submenu->Append(pItem);
			nCount++;
		}
	}

	bool fFirstRun = true;
	// create new menu items for common palette
	palette = m_mapElementPalettes[udnCOMMON_ITEMS];
	for( size_t i = 0; i < palette->GetCount(); i++)
	{
		pPaletteItem = &palette->Item(i);
		
		if( itemmask & pPaletteItem->m_nType)
		{
			if( fFirstRun )
			{
				submenu->AppendSeparator();
				fFirstRun = false;
			}
			pItem = new wxMenuItem(submenu, pPaletteItem->m_nId + udvTOOLS_CNT, pPaletteItem->m_sDesc);
			pItem->SetBitmap(udArt::GetBitmap(pPaletteItem->m_sClassName));
			submenu->Append(pItem);
			nCount++;
		}
	}
	
	return nCount;
}

void UMLDesignerFrame::CreateMainToolbars()
{
	wxString sResPath = wxGetApp().GetResourcesPath();
	
    // main toolbar
	/*#ifdef __WXGTK__*/
	m_tbMainFrame = new wxAuiToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	m_tbMainFrame->SetArtProvider( new udToolArt() );
	/*#else
	m_tbMainFrame = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);
	#endif*/
	m_tbMainFrame->SetToolBitmapSize(wxSize(udnIMG_SIZE, udnIMG_SIZE));
	m_tbMainFrame->AddTool(wxID_NEW, wxT("New"), wxBitmap(sResPath + wxT("app/gui/filenew.png"), wxBITMAP_TYPE_PNG), wxT("New project"));
	m_tbMainFrame->AddTool(wxID_OPEN, wxT("Load"), wxBitmap(sResPath + wxT("app/gui/fileopen.png"), wxBITMAP_TYPE_PNG), wxT("Open project..."));
	m_tbMainFrame->AddTool(wxID_SAVE, wxT("Save"), wxBitmap(sResPath + wxT("app/gui/filesave.png"), wxBITMAP_TYPE_PNG), wxT("Save project"));
	m_tbMainFrame->AddTool(wxID_SAVEAS, wxT("Save as..."), wxBitmap(sResPath + wxT("app/gui/filesaveas.png"), wxBITMAP_TYPE_PNG), wxT("Save project as..."));
	m_tbMainFrame->AddSeparator();
	m_tbMainFrame->AddTool(wxID_PRINT, wxT("Print"), wxBitmap(sResPath + wxT("app/gui/fileprint.png"), wxBITMAP_TYPE_PNG), wxT("Print active diagram..."));
	m_tbMainFrame->AddTool(wxID_PREVIEW, wxT("Preview"), wxBitmap(sResPath + wxT("app/gui/filepreview.png"), wxBITMAP_TYPE_PNG), wxT("Preview active diagram..."));
	m_tbMainFrame->AddSeparator();
	m_tbMainFrame->AddTool(wxID_COPY, wxT("Copy"), wxBitmap(sResPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_PNG), wxT("Copy to clipboard"));
	m_tbMainFrame->AddTool(wxID_CUT, wxT("Cut"), wxBitmap(sResPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_PNG), wxT("Cut to clipboard"));
	m_tbMainFrame->AddTool(wxID_PASTE, wxT("Paste"), wxBitmap(sResPath + wxT("app/gui/editpaste.png"), wxBITMAP_TYPE_PNG), wxT("Paste from clipboard"));
	m_tbMainFrame->AddSeparator();
	m_tbMainFrame->AddTool(wxID_UNDO, wxT("Undo"), wxBitmap(sResPath + wxT("app/gui/undo.png"), wxBITMAP_TYPE_PNG), wxT("Undo"));
	m_tbMainFrame->AddTool(wxID_REDO, wxT("Redo"), wxBitmap(sResPath + wxT("app/gui/redo.png"), wxBITMAP_TYPE_PNG), wxT("Redo"));
	m_tbMainFrame->Realize();

	// project toolbar
	/*#ifdef __WXGTK__*/
	m_tbProjectItems = new wxAuiToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	m_tbProjectItems->SetArtProvider( new udToolArt() );
	/*#else
	m_tbProjectItems = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);
	#endif*/
	m_tbProjectItems->SetToolBitmapSize(wxSize(udnIMG_SIZE, udnIMG_SIZE));
	m_tbProjectItems->AddTool(IDM_PROJ_PACKAGE, wxT("Package"), udArt::GetBitmap(wxT("udPackageItem")), wxT("Create new package")); //Folder_xpm
	m_tbProjectItems->AddTool(IDM_PROJ_CODEPACKAGE, wxT("Code package"), udArt::GetBitmap(wxT("udCodePackageItem")), wxT("Create new code package")); //Folder_xpm
	m_tbProjectItems->AddSeparator();
    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        m_tbProjectItems->AddTool(m_arrDiagrams[i].m_nId, m_arrDiagrams[i].m_sName, udArt::GetBitmap(m_arrDiagrams[i].m_sClassName), wxT("Create new ") + m_arrDiagrams[i].m_sName);
    }
	m_tbProjectItems->AddSeparator();
	m_tbProjectItems->AddTool(IDM_PROJ_VARIABLE, wxT("Variable"), udArt::GetBitmap(wxT("udGenericVariableItem")), wxT("Create user-defined generic variable"));
	m_tbProjectItems->AddTool(IDM_PROJ_FUNCTION, wxT("Function"), udArt::GetBitmap(wxT("udGenericFunctionItem")), wxT("Create user-defined generic function"));
	m_tbProjectItems->AddSeparator();
	m_tbProjectItems->AddTool(IDM_PROJ_SETTINGS, wxT("Project settings"), wxBitmap(sResPath + wxT("app/gui/configure.png"), wxBITMAP_TYPE_PNG), wxT("Project settings"));

    m_tbProjectItems->Realize();

	// design toolbar
	/*#ifdef __WXGTK__*/
	m_tbDesign = new wxAuiToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	m_tbDesign->SetArtProvider( new udToolArt() );
	/*#else
	m_tbDesign = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);
	#endif*/
	m_tbDesign->SetToolBitmapSize(wxSize(udnIMG_SIZE, udnIMG_SIZE));
	m_tbDesign->AddTool(IDT_GRID, wxT("Grid"), udArt::GetBitmap(wxT("udICON_GRID")), wxT("Show/hide grid"), wxITEM_CHECK );
	m_tbDesign->AddSeparator();
	m_tbDesign->AddTool(IDT_ALIGN_LEFT, wxT("Align left"), udArt::GetBitmap(wxT("udICON_ALIGNLEFT")), wxT("Align selected items to the left"));
	m_tbDesign->AddTool(IDT_ALIGN_RIGHT, wxT("Align right"), udArt::GetBitmap(wxT("udICON_ALIGNRIGHT")), wxT("Align selected items to the right"));
	m_tbDesign->AddTool(IDT_ALIGN_TOP, wxT("Align top"), udArt::GetBitmap(wxT("udICON_ALIGNTOP")), wxT("Align selected items to the top"));
	m_tbDesign->AddTool(IDT_ALIGN_BOTTOM, wxT("Align bottom"), udArt::GetBitmap(wxT("udICON_ALIGNBOTTOM")), wxT("Align selected items to the bottom"));
	m_tbDesign->AddTool(IDT_ALIGN_CENTER, wxT("Align center"), udArt::GetBitmap(wxT("udICON_ALIGNCENTER")), wxT("Align selected items to the center"));
	m_tbDesign->AddTool(IDT_ALIGN_MIDDLE, wxT("Align middle"), udArt::GetBitmap(wxT("udICON_ALIGNMIDDLE")), wxT("Align selected items to the middle"));
	m_tbDesign->AddSeparator();
	m_tbDesign->AddTool(IDT_ALIGN_CIRCLE, wxT("Align into circle"), udArt::GetBitmap(wxT("udICON_ALIGNCIRCLE")), wxT("Align selected items into circle"));
	m_tbDesign->AddTool(IDT_ALIGN_MESH, wxT("Align into mesh"), udArt::GetBitmap(wxT("udICON_ALIGNMESH")), wxT("Align selected items into mesh"));
	m_tbDesign->AddTool(IDT_ALIGN_VTREE, wxT("Align into vertical tree"), udArt::GetBitmap(wxT("udICON_ALIGNVTREE")), wxT("Align selected items into vertical tree"));
	m_tbDesign->AddTool(IDT_ALIGN_HTREE, wxT("Align into horizontal tree"), udArt::GetBitmap(wxT("udICON_ALIGNHTREE")), wxT("Align selected items into horizontal tree"));
	m_tbDesign->Realize();

	// generator toolbar
	/*#ifdef __WXGTK__*/
	m_tbGenerator = new wxAuiToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
	m_tbGenerator->SetArtProvider( new udToolArt() );
	/*#else
	m_tbGenerator = new wxToolBar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);
	#endif*/
	m_tbGenerator->SetToolBitmapSize(wxSize(udnIMG_SIZE, udnIMG_SIZE));
	m_tbGenerator->AddTool(IDM_CODE_PREVIEW, wxT("Code preview"), wxBitmap(sResPath + wxT("app/gui/spellcheck.png"), wxBITMAP_TYPE_PNG), wxT("Generate code preview for an active chart"));
	m_tbGenerator->AddTool(IDM_CODE_GENERATE, wxT("Generate"), wxBitmap(sResPath + wxT("app/gui/actionrun.png"), wxBITMAP_TYPE_PNG), wxT("Generate code for an active project"));
	m_tbGenerator->AddSeparator();
	wxArrayString dummy; // This is just because gcc 4.3 does not like the num at 0 and the cont wxString* at NULL
	m_chLanguages = new wxChoice(m_tbGenerator, IDC_CHOICE_LANGUAGES, wxDefaultPosition, wxSize(200, -1), dummy);
	m_chLanguages->SetToolTip(wxT("Select output programming language"));
	m_tbGenerator->AddControl(m_chLanguages);
	m_chGenerators = new wxChoice(m_tbGenerator, IDC_CHOICE_GENERATORS, wxDefaultPosition, wxSize(300, -1), dummy);
	m_chGenerators->SetToolTip(wxT("Select generator"));
	m_tbGenerator->AddControl(m_chGenerators);
	m_chAlgorithms = new wxChoice(m_tbGenerator, IDC_CHOICE_ALGORITHMS, wxDefaultPosition, wxSize(300, -1), dummy);
	m_chAlgorithms->SetToolTip(wxT("Select algorithm"));
	m_tbGenerator->AddControl(m_chAlgorithms);
	m_tbGenerator->Realize();
}

void UMLDesignerFrame::CreateMainMenus()
{
	bool fFirstItem = true;
	udPluginManager& Mgr = wxGetApp().GetPluginManager();
	
	for( PluginList::iterator it = Mgr.GetPluginsList().begin(); it != Mgr.GetPluginsList().end(); ++it )
	{
		IPlugin *pPlugin = *it;
		
		wxMenu *pMenu = pPlugin->CreateMenu();
		if( pMenu )
		{
			if( fFirstItem ) pluginsMenu->AppendSeparator();
			pluginsMenu->Append( wxID_ANY, pPlugin->GetInfo().GetName(), pMenu );
			
			fFirstItem = false;
		}
	}
}

void UMLDesignerFrame::CreateRecentFilesMenu()
{
	// clear current content (only 9 menu items are allowed)
	for( int id = wxID_FILE1; id <= wxID_FILE9; id++ )
	{
		if( recentFilesMenu->FindItem(id) ) recentFilesMenu->Delete(id);
	}
	
	// insert recent files stored in application settings
	udSettings &Settings = wxGetApp().GetSettings();
	
	if( Settings.GetProperty(wxT("Recent files")) )
	{
		wxArrayString &arrRecentFiles = Settings.GetProperty(wxT("Recent files"))->AsStringArray();
		
		size_t nIndex = 0;
		while( nIndex < arrRecentFiles.GetCount() )
		{
			if( wxFileExists( arrRecentFiles[nIndex] ) )
			{
				recentFilesMenu->Append( wxID_FILE1 + nIndex, wxString::Format(wxT("&%d %s"), nIndex + 1, arrRecentFiles[nIndex].c_str()) );
				nIndex++;
			}
			else
				arrRecentFiles.RemoveAt( nIndex );
		}
	}
}

void UMLDesignerFrame::CreatePalettes()
{
    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        CreatePaletteToolbar(m_arrDiagrams[i].m_sName);
    }

    CreatePaletteToolbar(udnCOMMON_ITEMS);
}

void UMLDesignerFrame::CreatePaletteToolbar(const wxString& title)
{
	/*#ifdef __WXMSW__
	wxToolBar* toolbar = new wxToolBar(m_auintbPalettes, -1, wxDefaultPosition, wxSize(-1, 24), wxTB_FLAT | wxTB_HORIZONTAL | wxTB_NODIVIDER );
	#else*/
	wxAuiToolBar* toolbar = new wxAuiToolBar(m_auintbPalettes, -1, wxDefaultPosition, wxSize(-1, 24), wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW );
	/*#endif*/
	
	// insert design tool (common for all palettes)
	toolbar->AddTool(IDT_DESIGN_TOOL_ID, wxT("Design tool"), udArt::GetBitmap(wxT("udICON_TOOL")), wxT("Design tool"), wxITEM_RADIO);
	// insert palette tools
	PaletteArray *palette = m_mapElementPalettes[title];
	if( palette )
	{
		for(size_t i = 0; i < palette->GetCount(); i++)
		{
			toolbar->AddTool(palette->Item(i).m_nId, palette->Item(i).m_sDesc,
				udArt::GetBitmap(palette->Item(i).m_sClassName), palette->Item(i).m_sDesc, wxITEM_RADIO);
		}
	}
	toolbar->Realize();
	
	m_auintbPalettes->AddPage( toolbar, title, false );
}

void UMLDesignerFrame::CreateProjectManager()
{
	m_pProjectManager = new udProjectManager(this);
	
	// project structure tree
	m_pProjectManager->InsertView( new udProjStructTree(m_pProjectManager->GetNotebook(), wxID_ANY ), wxT("Project items") );

	// code items
	m_pProjectManager->InsertView( new udCodeItemsTree(m_pProjectManager->GetNotebook(), wxID_ANY ), wxT("Code items") );
	
	m_pProjectManager->BuildFromProject( udProject::Get() );
	m_pProjectManager->SetActiveView( wxT("Project items") );
	
	// register listeners
	RegisterEventListener( m_pProjectManager );
	RegisterEventListener( m_pProjectManager->GetView(wxT("Project items")) );
	RegisterEventListener( m_pProjectManager->GetView(wxT("Code items")) );	
}

void UMLDesignerFrame::CreateThumbnail()
{
	int nStyle = 0;
	udSettings &Settings = wxGetApp().GetSettings();
	
    m_pThumbnail = new wxSFThumbnail(this);
	
	if( Settings.GetProperty(wxT("Show elements in thumbnail"))->AsBool() )	nStyle |= wxSFThumbnail::tsSHOW_ELEMENTS;
	if( Settings.GetProperty(wxT("Show connections in thumbnail"))->AsBool() ) nStyle |= wxSFThumbnail::tsSHOW_CONNECTIONS;
	
	m_pThumbnail->SetThumbStyle(nStyle);
}

void UMLDesignerFrame::CreateLogWindow()
{
	m_pLogPanel = new udLog(this, wxID_ANY);
}

void UMLDesignerFrame::CreateInstantEditor()
{
	m_pInstantEditor = new udCodeEditorPanel(this, wxID_ANY, wxPoint(0,0));
	
	// register listeners
	RegisterEventListener( m_pInstantEditor );
}

void UMLDesignerFrame::InsertIntoRecentFiles(wxString file)
{
	udSettings &Settings = wxGetApp().GetSettings();

	if( Settings.GetProperty(wxT("Recent files")) )
	{
		wxArrayString &arrRecentFiles = Settings.GetProperty(wxT("Recent files"))->AsStringArray();
		
		if( arrRecentFiles.Index( file ) == wxNOT_FOUND )
		{
			if( arrRecentFiles.GetCount() < 9 )
			{
				arrRecentFiles.Insert( file, 0 );
			}
			else
			{
				arrRecentFiles.RemoveAt( 8 );
				arrRecentFiles.Insert( file, 0 );
			}
		}
		else
		{
			arrRecentFiles.Remove( file );
			arrRecentFiles.Insert( file, 0 );
		}
		
		// update menu content
		CreateRecentFilesMenu();
	}
}

// public functions /////////////////////////////////////////////////////////////////

void UMLDesignerFrame::UnregisterEventListener(wxEvtHandler* handler)
{
	m_lstListeners.DeleteObject(handler);
}

void UMLDesignerFrame::RegisterEventListener(wxEvtHandler* handler)
{
	m_lstListeners.Append(handler);
}

void UMLDesignerFrame::DispatchEvent(wxEvent& evt, bool delayed)
{
	if( m_fDispatchEvents )
	{
		wxEvtHandler *pListener;
		
		// send the event to all registered listeners
		ListenerList::compatibility_iterator node = m_lstListeners.GetFirst();
		while( node )
		{	
			pListener = node->GetData();
			
			delayed ? pListener->AddPendingEvent( evt ) : (void)pListener->ProcessEvent( evt );
			
			node = node->GetNext();
		}
	}
}

void UMLDesignerFrame::SendProjectEvent(wxEventType cmdType, int id, udProjectItem* item, udProjectItem* parent, const wxString& data, bool delayed)
{
	// static funtion: we need to determine whether the main frame already exists
	if( m_fDispatchEvents )
	{
		UMLDesignerFrame *pFrame = wxGetApp().GetMainFrame();
		if( pFrame )
		{
			udProjectEvent evt( cmdType, id, item, parent );
			evt.SetString( data );
			
			pFrame->DispatchEvent( evt, delayed );
			
			#ifdef DEBUG_EVENTS
			wxString sItem, sParent;
			if( item ) sItem = item->GetName();
			if( parent ) sParent = parent->GetName();
			pFrame->GetLogWindow()->AddMessage( wxString::Format( wxT("DEBUG: Event type: %d, item: %s, parent: %s\n"), (int)cmdType, sItem.c_str(), sParent.c_str()) );
			#endif
		}
	}
}

void UMLDesignerFrame::ConnectDiagramEvents(udDiagramCanvas *diagram, bool enable)
{
	if( !diagram ) return;
	
	if( enable )
	{
		// connect the event handlers
		diagram->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(UMLDesignerFrame::OnDiagramLeftClick), NULL, this);
		diagram->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(UMLDesignerFrame::OnDiagramRightClick), NULL, this);
		diagram->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(UMLDesignerFrame::OnDiagramLeftDoubleClick), NULL, this);
		diagram->Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(UMLDesignerFrame::OnDiagramMouseWheel), NULL, this);
		diagram->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(UMLDesignerFrame::OnDiagramKeyDown), NULL, this);
		diagram->Connect(wxEVT_SF_LINE_DONE, wxSFShapeEventHandler(UMLDesignerFrame::OnConnectionFinished), NULL, this);
		diagram->Connect(wxEVT_SF_TEXT_CHANGE, wxSFShapeTextEventHandler(UMLDesignerFrame::OnShapeTextChanged), NULL, this);
		diagram->Connect(wxEVT_SF_ON_DROP, wxSFShapeDropEventHandler(UMLDesignerFrame::OnDropShapes), NULL, this);
		diagram->Connect(wxEVT_SF_ON_PASTE, wxSFShapePasteEventHandler(UMLDesignerFrame::OnPasteShapes), NULL, this);
	}
	else
	{
		// disconnect the event handlers
		diagram->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(UMLDesignerFrame::OnDiagramLeftClick), NULL, this);
		diagram->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(UMLDesignerFrame::OnDiagramRightClick), NULL, this);
		diagram->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(UMLDesignerFrame::OnDiagramLeftDoubleClick), NULL, this);
		diagram->Disconnect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(UMLDesignerFrame::OnDiagramMouseWheel), NULL, this);
		diagram->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(UMLDesignerFrame::OnDiagramKeyDown), NULL, this);
		diagram->Disconnect(wxEVT_SF_LINE_DONE, wxSFShapeEventHandler(UMLDesignerFrame::OnConnectionFinished), NULL, this);
		diagram->Disconnect(wxEVT_SF_TEXT_CHANGE, wxSFShapeTextEventHandler(UMLDesignerFrame::OnShapeTextChanged), NULL, this);
		diagram->Disconnect(wxEVT_SF_ON_DROP, wxSFShapeDropEventHandler(UMLDesignerFrame::OnDropShapes), NULL, this);
		diagram->Disconnect(wxEVT_SF_ON_PASTE, wxSFShapePasteEventHandler(UMLDesignerFrame::OnPasteShapes), NULL, this);
	}
}

udDiagramItem* UMLDesignerFrame::GetActiveDiagram()
{
	if( m_auintbDesignArea->GetSelection() != wxNOT_FOUND )
	{
		return udProject::Get()->GetDiagram( ( udDiagramCanvas* )m_auintbDesignArea->GetPage( m_auintbDesignArea->GetSelection() ));
	}
	else
		return NULL;
}

udDiagramCanvas* UMLDesignerFrame::GetActiveCanvas()
{
	if( m_auintbDesignArea->GetSelection() != wxNOT_FOUND )
	{
		return (udDiagramCanvas*) m_auintbDesignArea->GetPage( m_auintbDesignArea->GetSelection() );
	}
	else
		return NULL;
}

void UMLDesignerFrame::InitializeProject(udProject *proj)
{
	udProject::Get()->CloseAllDiagrams();
	
	m_pThumbnail->SetCanvas(NULL);
	
	// remove current content
    proj->RemoveAll();
    proj->CreateRootItem();
	// update project settings
	wxGetApp().GetPluginManager().AppendPluginsSettings( proj->GetSettings() );
	
	UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, (udProjectItem*)proj->GetRootItem() );

}

void UMLDesignerFrame::InitializeChoices()
{
    m_chLanguages->SetStringSelection(wxGetApp().GetLanguages().find(udProject::Get()->GetSettings().GetPropertyAsString( wxT("active_language"), wxT("udCLanguage") ))->second->GetName());

    udFRAME::FillGeneratorsChoice(m_chGenerators, GetSelectedLanguage(), GetActiveDiagram());
	// simulate usage of generator choice control...
	wxCommandEvent evt(0);
	OnGeneratorChoice(evt);

    udGenerator *pGen = CreateSelectedGenerator();
    if(pGen)
    {
        udFRAME::FillAlgorithmsChoice(m_chAlgorithms, GetSelectedLanguage(), GetActiveDiagram(), pGen);
		// simulate usage of algorithm choice control...
		wxCommandEvent evt(0);
		OnAlgorithmChoice(evt);
	
        delete pGen;
    }
    else
        m_chAlgorithms->Clear();
}

udLanguage* UMLDesignerFrame::GetSelectedLanguage()
{
    return wxGetApp().GetLanguage(m_chLanguages->GetStringSelection());
}

udGenerator* UMLDesignerFrame::CreateSelectedGenerator()
{
	return udPROJECT::CreateGenerator( m_chGenerators->GetStringSelection() );
}

void UMLDesignerFrame::CreateDiagramElement(long id, const wxPoint& pos)
{
    udDiagramItem* diagram = GetActiveDiagram();
	udDiagramCanvas *canvas = GetActiveCanvas();

    if( diagram )
    {
        wxSFShapeBase* pItem = NULL;
		udPaletteItem *pPaletteItem = GetPaletteTool(id);

		if( pPaletteItem->m_nType == udPaletteItem::pitCONNECTION )
        {
            canvas->StartInteractiveConnection(wxClassInfo::FindClass(pPaletteItem->m_sClassName), pos);
        }
        else
        {
            // create new shape at given position
            pItem = diagram->GetDiagramManager().AddShape(wxClassInfo::FindClass(pPaletteItem->m_sClassName), pos, sfDONT_SAVE_STATE);
            if(pItem)
            {
                // assign user data
				pItem->SetUserData((xsSerializable*)wxCreateDynamicObject(pPaletteItem->m_sDataClassName));
                udDiagElementItem* pUserData = (udDiagElementItem*)pItem->GetUserData();
                if(pUserData)
                {
					// create (unique if required) name
					pUserData->SetName(pPaletteItem->m_sDesc);
                    // set unique name to the element
                    udLABEL::SetContent(pUserData->GetName(), pItem, udLABEL::ltTITLE);
                    // perform user initialization steps...
                    pUserData->OnCreate();
                }
                pItem->Update();
				canvas->UpdateVirtualSize();

				if( canvas->GetMode() == wxSFShapeCanvas::modeREADY )SaveDiagramState(diagram);

                // create tree icon
				GetProjectTree()->CreateElementItem(pItem);
            }
			else
				wxMessageBox(wxString::Format(wxT("Couldn't add '%s' item to this diagram"), pPaletteItem->m_sDesc.c_str()), wxT("CodeDesigner"), wxOK | wxICON_WARNING);
        }
    }
}

bool UMLDesignerFrame::CanRemove(udProjectItem *item)
{
	udDiagElementItem *pElement = wxDynamicCast( item, udDiagElementItem );
    if( pElement)
    {
        // check whether there exist links to this item
        SerializableList lstLinks;
        udProject::Get()->GetElementLinks(udPROJECT::GetParentDiagram(pElement)->GetName(), pElement->GetName(), lstLinks);
        if( lstLinks.GetCount() > 0 )
        {
            if( wxMessageBox(wxString::Format(wxT("Element '%s' is linked by other elements. Do you realy want to remove it?"), item->GetName().c_str()), wxT("CodeDesigner"), wxYES_NO | wxICON_WARNING ) == wxNO )
            {
                return false;
            }
        }
		// check whether there exist code items refering to this item's ID
		wxString sOwners;
		udLanguage *pLang = wxGetApp().GetMainFrame()->GetSelectedLanguage();
		wxString sCurrentID = pElement->GetUniqueId( pLang );

		lstLinks.Clear();
		udProject::Get()->GetItems( CLASSINFO(udCodeItem), lstLinks );
		SerializableList::compatibility_iterator node = lstLinks.GetFirst();
		while( node )
		{
			udCodeItem *pCI = wxDynamicCast(node->GetData(), udCodeItem);
			if( pCI )
			{
				if( pCI->GetCode().Contains( sCurrentID ) ) sOwners << wxT("'") << pCI->GetName() << wxT("'\n");
			}
			node = node->GetNext();
		}
        if( !sOwners.IsEmpty() )
        {
            if( wxMessageBox(wxString::Format(wxT("Element '%s' is referenced by code items:\n%sDo you realy want to remove the element?"), item->GetName().c_str(), sOwners.c_str()), wxT("CodeDesigner"), wxYES_NO | wxICON_WARNING ) == wxNO )
            {
                return false;
            }
        }
    }
    return true;
}

void UMLDesignerFrame::SaveDiagramState(udDiagramItem *diag)
{
	if( !diag || !diag->IsKindOf(CLASSINFO(udDiagramItem)) ) return;

	wxSFShapeCanvas *pCanvas = diag->GetDiagramManager().GetShapeCanvas();
	if( pCanvas )pCanvas->SaveCanvasState();

	// perform this function recursively on all parent diagrams
	if( diag->GetSubdiagramElement() )
	{
		udDiagElementItem *pParentElement = diag->GetSubdiagramElement();
		SaveDiagramState(((udDiagramManager*)((wxSFShapeBase*)pParentElement->GetParent())->GetParentManager())->GetParentProjItem());
	}
}

void UMLDesignerFrame::SetProjectModified(bool modified)
{
	m_fModified = modified;
	if( modified ) SetStatusText( wxT("Modified"), 2 );
	else
		SetStatusText( wxT("Saved"), 2 );
}

// event handlers ///////////////////////////////////////////////////////////////////

void UMLDesignerFrame::OnProjectItemSelected(udProjectEvent& event)
{
	SetSelectedProjectItem( wxDynamicCast( event.GetProjectItem(), udProjectItem ) );
}

void UMLDesignerFrame::OnProjectItemChanged(udProjectEvent& event)
{
	// update choices' content...
	udDiagramItem *pDiagram = wxDynamicCast( event.GetProjectItem(), udDiagramItem );
	if( pDiagram )
	{
		InitializeChoices();
		if( pDiagram->GetDiagramPage() )
		{
			pDiagram->GetDiagramPage()->InitializeBackground();
			pDiagram->GetDiagramPage()->UpdateVirtualSize();
			pDiagram->GetDiagramPage()->InvalidateVisibleRect();
			pDiagram->GetDiagramPage()->RefreshInvalidatedRect();
			pDiagram->UpdateDiagramPageLabel();
		}
	}
	// update element's content
	udDiagElementItem *pElement = wxDynamicCast( event.GetProjectItem(), udDiagElementItem );
	if( pElement )
	{
		pElement->UpdateInnerContent();
		// update parent shape if exists
		wxSFShapeBase *pShape = wxDynamicCast( pElement->GetParent(), wxSFShapeBase );
		if( pShape )
		{
			pShape->Update();
			
			wxSFShapeCanvas *pCanvas = GetActiveCanvas();
			if( pCanvas )
			{
				wxRect rctCompBB;
				pShape->GetGrandParentShape()->GetCompleteBoundingBox( rctCompBB, wxSFShapeBase::bbALL );
				pCanvas->RefreshCanvas( false, rctCompBB );
			}
		}
	}
	// update content of code item's owners (diagram elements)
	udCodeItem *pCode = wxDynamicCast( event.GetProjectItem(), udCodeItem );
	if( pCode )
	{		
		// update also children of this code items
		SerializableList lstLinks;
		udProject::Get()->GetCodeLinks( udfVALID, pCode->GetClassInfo(), pCode->GetSignature(), pCode->GetScope(), lstLinks );
		
		SerializableList::compatibility_iterator node = lstLinks.GetFirst();
		while( node )
		{
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, wxDynamicCast(node->GetData()->GetParent(), udDiagElementItem), NULL, wxEmptyString, udfDELAYED );
			node = node->GetNext();
		}
		
		// update diagram page name if necessary
		udFunctionItem *pFcn = wxDynamicCast( pCode, udFunctionItem );
		if( pFcn && (pFcn->GetImplementation() != uddvFUNCTION_USERIMPLEMENTATION) )
		{
			udDiagramItem *pDiag = udProject::Get()->GetDiagram( pFcn->GetImplementation() );
			if( pDiag ) pDiag->UpdateDiagramPageLabel();
		}
		
		// update signature of new code item
		pCode->UpdateSignature();
	}
	
	SetProjectModified( true );
}

void UMLDesignerFrame::OnProjectItemAdded(udProjectEvent& event)
{
	#ifdef DEBUG_EVENTS
	UMLDesignerApp::Log( wxT("DEBUG: Item '") + event.GetProjectItem()->GetName() + wxT("' has been added.") );
	#endif
	
	if( GetProjectManager()->IsOrganized() )
	{
		udProjectItem *pItem = event.GetProjectItem();
		
		wxASSERT( pItem );
		if( !pItem ) return;
		
		udProject *pProj = udProject::Get();
		
		if( pItem->IsKindOf(CLASSINFO(udVariableItem)) ||
			pItem->IsKindOf(CLASSINFO(udFunctionItem)) )
		{
			bool fNewPkg = false;
			
			wxString sPkgName = m_mapDefaultPkgNames[pItem->GetClassInfo()->GetClassName()];
			
			udProjectItem *pPkg =  pProj->GetProjectItem(CLASSINFO(udCodePackageItem), sPkgName);
			if( !pPkg )
			{
				fNewPkg = true;
				
				pPkg = pProj->CreateProjectItem( wxT("udCodePackageItem"), pProj->GetRootItem()->GetId() );
				pPkg->SetName( sPkgName ); 
				
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pPkg, (udProjectItem*)pProj->GetRootItem(), wxEmptyString, udfDELAYED );
			}
			
			if( event.GetParentItem() != pPkg )
			{
				pItem->Reparent( pPkg );
				
				if( !fNewPkg ) UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pPkg, NULL, wxEmptyString, udfDELAYED );
				
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, event.GetParentItem(), NULL, wxEmptyString, udfDELAYED );
			}
		}
	}
	
	// update signature of new code item
	udCodeItem *pCi = wxDynamicCast( event.GetProjectItem(), udCodeItem );
	if( pCi ) pCi->UpdateSignature();
	
	SetProjectModified( true );
}

void UMLDesignerFrame::OnProjectItemRemoved(udProjectEvent& event)
{
	SetProjectModified( true );
}

void UMLDesignerFrame::OnProjectTaskRemove(udProjectEvent& event)
{
	// remove project item from its parent
	if( event.GetProjectItem() && event.GetParentItem() )
	{
		event.GetParentItem()->GetChildrenList().DeleteObject( event.GetProjectItem() );
		delete event.GetProjectItem();
		
		// notify other listeners about this event
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_REMOVED, wxID_ANY, event.GetProjectItem() );
	}
}

void UMLDesignerFrame::OnNewProject( wxCommandEvent &event )
{
    OnRemoveAll(event);
		
	SetTitle( wxT("CodeDesigner RAD") );
	
	SetProjectModified( false );
}

void UMLDesignerFrame::OpenProjectFile(const wxString& path)
{	
	if( wxFileExists( path ) )
	{
		wxSetCursor( *wxHOURGLASS_CURSOR );
				
		udProject *pProj = udProject::Get();
				
		pProj->CloseAllDiagrams();
		InitializeProject(pProj);

		if( !((wxXmlSerializer*)pProj)->DeserializeFromXml( path ) )
		{
			wxMessageBox( pProj->GetErrMessage(), wxT("CodeDesigner RAD"), wxICON_ERROR | wxOK );
		}
		
		EnableInternalEvents( false );
		
		// check whether all diagrams included in the loaded project are supported
		bool fSuccess = true;
		
		udDiagramItem *pDiag;
		SerializableList lstDiagrams;
		pProj->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
		SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
		while( node )
		{
			pDiag = (udDiagramItem*) node->GetData();
			
			if( !pDiag->GetSubdiagramElement() )
			{
				if( !FindDiagramInfoByClassName( pDiag->GetClassInfo()->GetClassName() ) ) fSuccess = false;
			}
			node = node->GetNext();
		}
		
		if( !fSuccess )
		{
			pProj->RemoveAll();
			pProj->CreateRootItem();
			
			wxMessageBox(wxT("Unable to load the project file due to unsupported diagram types."), wxT("CodeDesigner"), wxOK | wxICON_WARNING);
		}
		else
		{
			// do project update if needed
			switch( pProj->GetSettings().GetProperty( wxT("project_version") )->AsLong() )
			{
				// 1 -> 2
				case 1:
				{
					// update code items signatures
					SerializableList lstCodeItems;
					pProj->GetItems( CLASSINFO(udCodeItem), lstCodeItems );
					for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
					{
						((udCodeItem*)(*it))->UpdateSignature();
					}
					
					// try to recover invalid links (import older projects)
					SerializableList lstCodeLinks;
					pProj->GetCodeLinks(udfINVALID, CLASSINFO(udCodeItem), wxT(""), wxT(""), lstCodeLinks );
					
					for( SerializableList::iterator it = lstCodeLinks.begin(); it != lstCodeLinks.end(); ++it )
					{
						udCodeLinkItem *lnk = (udCodeLinkItem*)*it;
						for( SerializableList::iterator it2 = lstCodeItems.begin(); it2 != lstCodeItems.end(); ++it2 )
						{
							udCodeItem *ci = (udCodeItem*)*it2;
							if( ci->GetName() == lnk->GetOrigCodeItem() )
							{
								lnk->SetOrigCodeItem( ci->GetSignature() );
								break;
							}
						}
					}
					break;
				}
					
				default:
					break;
			}
			
			// validate project items
			pProj->CheckCodeLinks();
			pProj->CheckElementLinks();
		}

		EnableInternalEvents( true );
		
		wxGetApp().GetPluginManager().AppendPluginsSettings( udProject::Get()->GetSettings() );
		m_pProjectManager->BuildFromProject(pProj);

		InitializeChoices();
				
		pProj->SetProjectDirectory( path.BeforeLast( wxFileName::GetPathSeparator() ) );
		pProj->SetProjectPath( path );
				
		InsertIntoRecentFiles( path );
				
		SetTitle( wxT("CodeDesigner RAD [") + path + wxT("]") );
				
		SetProjectModified( false );
				
		wxSetCursor( *wxSTANDARD_CURSOR );
	}
}

void UMLDesignerFrame::OnOpenProject( wxCommandEvent &event )
{
    wxFileDialog dlg(this, wxT("Open project..."), wxT(""), wxT(""), wxT("CodeDesigner project (*.cdp)|*.cdp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if(dlg.ShowModal() == wxID_OK)
    {
		OpenProjectFile( dlg.GetPath() );
    }
}

void UMLDesignerFrame::OnRecentFile( wxCommandEvent &event )
{
	udSettings &Settings = wxGetApp().GetSettings();
	
	if( Settings.GetProperty(wxT("Recent files")) )
	{
		wxArrayString &arrRecentFiles = Settings.GetProperty(wxT("Recent files"))->AsStringArray();
		
		size_t nIndex = event.GetId() - wxID_FILE1;
		if( nIndex < arrRecentFiles.GetCount() )
		{
			if( IsProjectModified() && (wxMessageBox(wxT("Current unsaved changes will be lost. Would you like to load the project anyway?"), wxT("CodeDesigner"), wxICON_WARNING | wxYES_NO) == wxNO) ) return;
			
			OpenProjectFile( arrRecentFiles[nIndex] );
		}
	}
}

void UMLDesignerFrame::OnSaveProject( wxCommandEvent &event )
{
	wxBusyCursor busy;

	udProject *pProj = udProject::Get();
	
	// set current project version
	pProj->GetSettings().GetProperty( wxT("project_version") )->AsLong() = udvPROJECT_VERSION;
	
	// save project
	if( wxFileExists( pProj->GetProjectPath() ) )
	{
		pProj->SerializeToXml(  pProj->GetProjectPath(), true );
		
		SetTitle( wxT("CodeDesigner RAD [") + pProj->GetProjectPath() + wxT("]") );
		
		SetProjectModified( false );
	}
	else
		OnSaveProjectAs( event );
}

void UMLDesignerFrame::OnSaveProjectAs( wxCommandEvent &event )
{
	udProject *pProj = udProject::Get();
	
    wxFileDialog dlg(this, wxT("Save project..."), pProj->GetProjectDirectory(), wxT(""), wxT("CodeDesigner project (*.cdp)|*.cdp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if(dlg.ShowModal() == wxID_OK)
    {
		wxBusyCursor busy;
		
		wxString sPath = dlg.GetPath();
		wxFileName fnPath(sPath);
		if( fnPath.GetExt() == wxEmptyString )
		{
			sPath += wxT(".cdp");
		}
		
		pProj->SetProjectDirectory( dlg.GetDirectory() );
		pProj->SetProjectPath( sPath );
		
		pProj->SerializeToXml( pProj->GetProjectPath(), true );
		
		SetTitle( wxT("CodeDesigner RAD [") + pProj->GetProjectPath() + wxT("]") );
		
		SetProjectModified( false );
    }
}

void UMLDesignerFrame::OnExportDiagram( wxCommandEvent &event )
{
	static wxString dirpath = wxGetCwd();
	wxFileDialog dlg(this, wxT("Export diagram to image..."), dirpath, wxT(""), wxT("BMP Files (*.bmp)|*.bmp|GIF Files (*.gif)|(*.gif)|XPM Files (*.xpm)|*.xpm|PNG Files (*.png)|*.png|JPEG Files (*.jpg)|*.jpg|SVG Files (*.svg)|*.svg"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if(dlg.ShowModal() == wxID_OK)
	{
		dirpath = dlg.GetDirectory();
		
		wxBitmapType type = wxBITMAP_TYPE_ANY;
		int filterIndex = dlg.GetFilterIndex();
		
		if( filterIndex < 5 ) {
			switch( filterIndex )
			{
				case 0:
					type = wxBITMAP_TYPE_BMP;
					break;
				case 1:
					type = wxBITMAP_TYPE_GIF;
					break;
				case 2:
					type = wxBITMAP_TYPE_XPM;
					break;
				case 3:
					type = wxBITMAP_TYPE_PNG;
					break;
				case 4:
					type = wxBITMAP_TYPE_JPEG;
					break;
			}
			
			GetActiveCanvas()->SaveCanvasToImage( dlg.GetPath(), type, wxGetApp().GetSettings().GetProperty( wxT("Export canvas background") )->AsBool() );
			
		} else {
			udDiagramCanvas *canvas = GetActiveCanvas();
			
			wxRect bb = canvas->GetTotalBoundingBox();
			bb.Inflate( 10 );
			
			wxSVGFileDC dc( dlg.GetPath(), bb.width + bb.GetLeft(), bb.height + bb.GetTop() );
			if( dc.IsOk() ) {
				if( wxGetApp().GetSettings().GetProperty( wxT("Export canvas background") )->AsBool() ) {
					canvas->DrawBackground( dc, sfNOT_FROM_PAINT );
				}
				canvas->DrawContent( dc, sfNOT_FROM_PAINT );
				canvas->DrawForeground( dc, sfNOT_FROM_PAINT );
				
				wxMessageBox( wxString::Format( wxT("The image has been saved to '%s'."), dlg.GetPath() ), wxT("CodeDesigner") );
			}
		}
	}
}

void UMLDesignerFrame::OnClose( wxCloseEvent &event ) 
{
	wxCommandEvent evt(0);
	OnQuit( evt );
}

void UMLDesignerFrame::OnQuit( wxCommandEvent &event )
{
	udProject *pProj = udProject::Get();
	
	if( IsProjectModified() && ( wxMessageBox( wxT("Project is changed. Do you want to save it?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION) == wxYES ) )
	{
		if( wxFileExists( pProj->GetProjectPath() ) )
		{
			OnSaveProject( event );
		}
		else
			OnSaveProjectAs( event );
	}
	
	m_fClosing = true;
	
	m_pThumbnail->SetCanvas(NULL);

    pProj->CloseAllDiagrams();
    pProj->RemoveAll();

    Destroy();
}

void UMLDesignerFrame::OnPreferences(wxCommandEvent& event)
{
	udSettingsDialog dlg( this, wxGetApp().GetSettings(), wxT("Application preferences") );
	udWindowManager dlgman( dlg, wxT("preferences_dialog") );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		// re-initialize opened canvases
		udDiagramItem *pDiagram;
		
		SerializableList lstDiagrams;
		udProject::Get()->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
		
		SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
		while( node )
		{
			pDiagram = (udDiagramItem*) node->GetData();
			
			// first, re-initialize canvas if shown
			if( pDiagram->GetDiagramPage() ) pDiagram->GetDiagramPage()->InitializeCanvas();
			// second, update all shapes in the diagrams (some Update() functions need info from canvas)
			pDiagram->GetDiagramManager().UpdateAll();
			// refresh canvas if shown
			if( pDiagram->GetDiagramPage() ) pDiagram->GetDiagramPage()->Refresh( false );
			
			node = node->GetNext();
		}
		
		// re-initialize languages
		wxGetApp().ClearLanguages();
		wxGetApp().InitLanguages();
	}
}

void UMLDesignerFrame::OnSettings(wxCommandEvent& event)
{
	udSettingsDialog dlg( this, udProject::Get()->GetSettings(), wxT("Project settings") );
	udWindowManager dlgman( dlg, wxT("project_settings_dialog") );
	
	dlg.ShowModal();
}

void UMLDesignerFrame::OnAbout( wxCommandEvent &event )
{
	// retrieve svn num
	wxString svn = udvSVN_REVISION;
	svn = svn.SubString( 6, svn.Len() - 2 );
	svn.Trim().Trim(false);
	
	wxString version = wxString::Format( wxT("1.6.5.%d Beta (SVN: %s) "), udvBUILD_NUMBER, svn.c_str() );

    wxString desc = wxT("Cross-platform CASE tool designed for drawing of UML diagrams, code generation and reverse code engineering.\n\n");
	desc << wxbuildinfo(long_f) << wxT("\n\n");
    desc << wxT("Available diagrams:\n");

    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        desc << m_arrDiagrams[i].m_sName;
		if( i < m_arrDiagrams.GetCount() - 1) desc << wxT(", ");
    }
	desc << wxT("\n\nAvailable generators:\n");
    for( size_t i = 0; i < m_arrGenerators.GetCount(); i++ )
    {
        desc << m_arrGenerators[i].GetDescription();
		if( i < m_arrGenerators.GetCount() - 1) desc << wxT(", ");
    }
	desc << wxT("\n");

    wxAboutDialogInfo info;
    info.SetName(wxT("CodeDesigner RAD"));
    info.SetVersion(version);
    info.SetDescription(desc);
    info.SetCopyright(wxT("2007 - 2014 (C) Michal Bližňák, Tomas Bata University, Zlin, Czech Republic"));
    info.SetWebSite(wxT("http://www.codedesigner.org"));
    info.AddDeveloper(wxT("Michal Bližňák"));

    wxAboutBox(info);
}

void UMLDesignerFrame::OnIdle( wxIdleEvent &event )
{
	if( m_nCurrentToolId == IDT_DESIGN_TOOL_ID ) SetStatusText(wxT("Current tool: Design tool"), 1);
	else
		SetStatusText(wxString::Format(wxT("Current tool: %s"), GetPaletteTool(m_nCurrentToolId)->m_sDesc.c_str()), 1);
}

void UMLDesignerFrame::OnPageClosing( wxAuiNotebookEvent &event )
{	
    udDiagramItem *pDiag = udProject::Get()->GetDiagram( ( udDiagramCanvas* )m_auintbDesignArea->GetPage(event.GetSelection()));

    if(pDiag)
    {
        pDiag->OnDestroyDiagramPage();
    }

    m_chGenerators->Clear();
    m_chAlgorithms->Clear();
}

void UMLDesignerFrame::OnPageChanged( wxAuiNotebookEvent &event )
{
	if( m_fClosing ) return;

	m_pThumbnail->SetCanvas( ( udDiagramCanvas* )m_auintbDesignArea->GetPage(event.GetSelection()) );
	
    InitializeChoices();
}

void UMLDesignerFrame::OnLanguageChoice( wxCommandEvent &event )
{
    udProject::Get()->GetSettings().GetProperty(wxT("active_language"))->AsString() = GetSelectedLanguage()->GetClassInfo()->GetClassName();

    InitializeChoices();
	
	//EnableInternalEvents(false);
	
	udDiagramItem *pDiag;
	SerializableList lstDiagrams;
	udProject::Get()->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
	
	SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
	while( node )
	{
		pDiag = (udDiagramItem*) node->GetData();
		
		if( pDiag->GetDiagramPage() )
		{
			pDiag->GetDiagramManager().UpdateAllInnerContent();
			pDiag->GetDiagramManager().UpdateAll();
		
			pDiag->GetDiagramPage()->Refresh(false);
		}
		
		node = node->GetNext();
	}
	
	//EnableInternalEvents(true);

	UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetSelectedProjectItem() );
}

void UMLDesignerFrame::OnGeneratorChoice( wxCommandEvent &event )
{
	if( GetActiveDiagram() )
	{
		udGenerator *pGen = CreateSelectedGenerator();

		if(pGen)
		{
			GetActiveDiagram()->SetActiveGenerator(pGen->GetClassInfo()->GetClassName());
			delete pGen;
		}
		else
			GetActiveDiagram()->SetActiveGenerator(wxT(""));
			
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetSelectedProjectItem() );
	}
}

void UMLDesignerFrame::OnAlgorithmChoice( wxCommandEvent &event )
{
	if( GetActiveDiagram() )
	{
		udGenerator *pGen = CreateSelectedGenerator();

		if(pGen)
		{
			udAlgorithm *pAlg = pGen->FindAlgorithm(m_chAlgorithms->GetStringSelection());
			if(pAlg)
			{
				GetActiveDiagram()->SetActiveAlgorithm(pAlg->GetClassInfo()->GetClassName());
			}
			delete pGen;
		}
		else
			GetActiveDiagram()->SetActiveGenerator(wxT(""));
			
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetSelectedProjectItem() );
	}
}

void UMLDesignerFrame::OnPalettes( wxCommandEvent &event )
{
    long id = event.GetId();
    if((id >= IDT_PALETTE_MIN_TOOL_ID) && (id < IDT_PALETTE_MAX_TOOL_ID))
    {
        m_nCurrentToolId = id;
    }
}

void UMLDesignerFrame::OnCreateDiagram( wxCommandEvent &event )
{
	udPackageItem *pParent = wxDynamicCast( GetSelectedProjectItem(), udPackageItem );

    if( pParent ) 
    {
        udDiagramType *pType = FindDiagramInfoById(event.GetId());
		if( pType )
		{
			// create new diagram
			udDiagramItem* pDiagram = (udDiagramItem*) udProject::Get()->CreateProjectItem( pType->m_sClassName, pParent->GetId() );
			// create relevant tree item
			if( pDiagram )
			{
				pDiagram->SetDiagramType( pType->m_sName );
				m_pProjectManager->SetActiveView( wxT("Project items") );
				
				SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pDiagram, pParent );
				//pDiagram->ShowDiagramPage();
			}
		}
    }
}

void UMLDesignerFrame::OnCreateProjectItem( wxCommandEvent &event )
{
	udProjectItem *pParent = GetSelectedProjectItem();
	udProjectItemType *pItemType = m_mapProjectItems[event.GetId()];
	
	if( pParent && pItemType )
	{
		// code items can be assigned only to root or code package
		if( (pItemType->m_nProjItemType == udProjectItemType::pitCODEITEM) &&
			!pParent->IsKindOf( CLASSINFO(udRootItem) ) &&
			!pParent->IsKindOf( CLASSINFO(udCodePackageItem) ) ) return;
			
		// project items can be assigned only to root or project package
		if( (pItemType->m_nProjItemType == udProjectItemType::pitPROJITEM) &&
			!pParent->IsKindOf( CLASSINFO(udRootItem) ) &&
			!pParent->IsKindOf( CLASSINFO(udPackageItem) ) ) return;
		
		udProjectItem *pItem = udProject::Get()->CreateProjectItem( pItemType->m_sClassName, pParent->GetId() );
		if( pItem )
		{
			m_pProjectManager->SetActiveView( pItemType->m_sViewName );
			
			SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pItem, pParent );
			//SaveDiagramState( GetActiveDiagram() );
		}
	}
}

void UMLDesignerFrame::OnClearCodeItems(wxCommandEvent& event)
{
	udDiagElementItem *pElement = wxDynamicCast( GetSelectedProjectItem(), udDiagElementItem );
	if( pElement )
	{
		wxClassInfo *pClassInfo = wxClassInfo::FindClass( m_mapProjectItems[event.GetId()]->m_sClassName );
		if( pClassInfo )
		{
			pElement->ClearCodeItems( pClassInfo );
	
			SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
			SaveDiagramState( GetActiveDiagram() );
		}
	}
}

void UMLDesignerFrame::OnCreateDiagramElement( wxCommandEvent &event )
{
	udPaletteItem *pPaletteItem = GetPaletteTool(event.GetId() - udvTOOLS_CNT);
	if( pPaletteItem )
	{
		CreateDiagramElement(pPaletteItem->m_nId, m_nLastClickedPosition);
	}
}

void UMLDesignerFrame::OnShowDiagram( wxCommandEvent &event )
{
	udProjectItem *pProjItem = GetSelectedProjectItem();

	if( !pProjItem ) return;

	if( pProjItem->IsKindOf(CLASSINFO(udDiagramItem)) )
	{
		((udDiagramItem*)pProjItem)->ShowDiagramPage();
	}
	else
	{
	    pProjItem = udPROJECT::GetDiagramElement( wxDynamicCast( pProjItem->GetParent(), wxSFShapeBase) );

        if( pProjItem && pProjItem->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
        {
            udDiagramItem* pDiagram = ((udSubDiagramElementItem*)pProjItem)->GetSubDiagram();
            if( pDiagram )
            {
                pDiagram->ShowDiagramPage();
            }
        }
	}
}

void UMLDesignerFrame::OnNavigateTo( wxCommandEvent &event )
{
	udProjectItem *pProjItem = GetSelectedProjectItem();
	
	if( pProjItem )
	{
		udDiagramItem *pDiag = udPROJECT::GetParentDiagram( pProjItem );
		
		pDiag->ShowDiagramPage();
		pDiag->GetDiagramPage()->ScrollToShape( (wxSFShapeBase*)pProjItem->GetParent() );
	}
	
}

void UMLDesignerFrame::OnShowPreviewDiagram( wxCommandEvent &event )
{
    OnShowDiagram(event);
    OnPreviewClick(event);
}

void UMLDesignerFrame::OnRemoveAll( wxCommandEvent &event )
{
    if(wxMessageBox(wxT("Are you sure you want to remove all project items?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION) == wxYES)
    {
        InitializeProject( udProject::Get() );
		
        m_pProjectManager->BuildFromProject(udProject::Get());		
    }
}

void UMLDesignerFrame::OnDelayedRemoveAll( wxCommandEvent &event )
{
	wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, IDM_PROJ_REMOVEALL);
	AddPendingEvent(evt);
}

void UMLDesignerFrame::OnRemoveItem( wxCommandEvent &event )
{
    udProjectItem* selItem = GetSelectedProjectItem();

    if(selItem && !selItem->IsKindOf(CLASSINFO(udRootItem)))
    {
        if( selItem->IsKindOf(CLASSINFO(udDiagElementItem)) )
        {
            OnRemoveElement( event );
        }
        else if(wxMessageBox(wxString::Format(wxT("Are you sure you want to remove '%s' from the project?"), selItem->GetName().c_str()), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION) == wxYES)
        {
			// first close diagram page if exists...
			udDiagramItem *pDiag = wxDynamicCast( selItem, udDiagramItem );
			if( pDiag ) pDiag->CloseDiagramPage();
			// ... then remove item from the project.
			udProject::Get()->RemoveItem(selItem);
			udProject::Get()->CheckElementLinks();
			udProject::Get()->CheckCodeLinks();
			
			//SetSelectedProjectItem( NULL );
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, NULL );
        }
    }
}

void UMLDesignerFrame::OnDelayedRemove( wxCommandEvent &event )
{
	wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, IDM_PROJ_REMOVE);
	AddPendingEvent(evt);
}

void UMLDesignerFrame::OnRemoveElement( wxCommandEvent &event )
{
	udProjectItem *pDiagElementItem = wxDynamicCast(GetSelectedProjectItem(), udProjectItem);
	
	if(pDiagElementItem && CanRemove( pDiagElementItem) )
    {
		wxSFShapeBase *pElement = (wxSFShapeBase*)pDiagElementItem->GetParent();
		if(pElement)
		{
			udDiagramManager *pManager = (udDiagramManager*)pElement->GetParentManager();

			pManager->RemoveShape(pElement);
			udProject::Get()->CheckElementLinks();
            // save canvas state if the canvas is created (even not active)
			SaveDiagramState(pManager->GetParentProjItem());
			
			if( GetActiveCanvas() ) GetActiveCanvas()->UpdateVirtualSize();
        }
		
		//SetSelectedProjectItem( NULL );
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, NULL );
    }
}

void UMLDesignerFrame::OnDelayedRemoveElement( wxCommandEvent &event )
{
	wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, IDM_DIAG_REMOVEELEMENT);
	AddPendingEvent(evt);
}

void UMLDesignerFrame::OnEditItem( wxCommandEvent &event )
{
	udProjectItem *pProjItem = GetSelectedProjectItem();
    if(pProjItem)
    {
		pProjItem->OnEditItem(this);
    }
}

void UMLDesignerFrame::OnDelayedEdit( wxCommandEvent &event )
{
	wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, IDM_PROJ_EDIT);
	AddPendingEvent(evt);
}

void UMLDesignerFrame::OnDelayedEditCode( wxCommandEvent &event )
{
	udDiagElementItem *pElement = wxDynamicCast( GetSelectedProjectItem(), udDiagElementItem );
	if( pElement && pElement->HasChildren() )
	{
		SerializableList::compatibility_iterator node = pElement->GetChildrenList().Item( event.GetId() - IDM_DELAYED_EDITCODE );
		if( node )
		{
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, (udProjectItem*)node->GetData() );
			
			wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, IDM_PROJ_EDIT);
			AddPendingEvent(evt);
		}
	}
}

void UMLDesignerFrame::OnDelayedCutElement( wxCommandEvent &event )
{
	wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, wxID_CUT);
	AddPendingEvent(evt);
}

void UMLDesignerFrame::OnDiagramLeftClick( wxMouseEvent &event )
{
    if( m_nCurrentToolId != IDT_DESIGN_TOOL_ID )
    {
		// create new diagram element
		CreateDiagramElement(m_nCurrentToolId, event.GetPosition());

        if( !event.ControlDown() )m_nCurrentToolId = IDT_DESIGN_TOOL_ID;
    }
    else
    {
		udDiagramCanvas *canvas = GetActiveCanvas();

        // get shape under the mouse cursor
        if( !event.ControlDown() && !canvas->GetMultiselectionBox().IsVisible() &&
			!canvas->GetTopmostHandleAtPosition(canvas->DP2LP(event.GetPosition())) )
        {
			wxSFShapeBase *pShapeUnder = udPROJECT::GetParentElement( canvas->GetShapeUnderCursor() );
			if(pShapeUnder)
			{				
				if(!pShapeUnder->IsSelected())
				{
					// highlight hit diagram element in the project tree view
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, (udProjectItem*)pShapeUnder->GetUserData() );
				}
				else
					SetSelectedProjectItem( (udProjectItem*)pShapeUnder->GetUserData() );
			}
			else
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
        }

        event.Skip();
    }
	
	SetProjectModified( true );
}

void UMLDesignerFrame::OnDiagramRightClick( wxMouseEvent &event )
{
	event.Skip();
	
	m_nLastClickedPosition = event.GetPosition();

	wxSFShapeBase *pShape = udPROJECT::GetParentElement( GetActiveCanvas()->GetShapeAtPosition(GetActiveCanvas()->DP2LP(event.GetPosition())) );
    if( pShape )
    {
		// get element for further processing ...
		udProjectItem *pElement = wxDynamicCast( pShape->GetUserData(), udProjectItem );
		if( pElement )
        {
			//pElement->OnSelection();
			
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, pElement );
			
            pElement->OnContextMenu(GetActiveCanvas(), event.GetPosition());
        }
    }
	else
	{
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
		
		GetActiveCanvas()->DeselectAll();
		
		if( m_pPopupMenu )
		{
			// create and show diagram's context menu
			UpdateCreateSubmenu(m_pPopupMenu->FindItemByPosition(0)->GetSubMenu(), m_mapElementPalettes[GetActiveDiagram()->GetDiagramType()], udPaletteItem::pitELEMENT, udfCLEAR_CONTENT);
			GetActiveCanvas()->PopupMenu(m_pPopupMenu, event.GetPosition());
		}
	}
	
	SetProjectModified( true );
}

void UMLDesignerFrame::OnDiagramLeftDoubleClick( wxMouseEvent &event )
{		
    wxSFShapeBase *pShape = GetActiveCanvas()->GetShapeUnderCursor();
    if( pShape &&
		!pShape->IsKindOf(CLASSINFO(wxSFEditTextShape)) &&
		!pShape->IsKindOf(CLASSINFO(wxSFLineShape)) )
    {
		pShape = udPROJECT::GetParentElement( pShape );
		if( pShape )
		{
			udDiagElementItem *pElement = wxDynamicCast( pShape->GetUserData(), udDiagElementItem);
			if( pElement )
			{
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, pElement );
				
				pElement->OnActivation();
			}
		}
    }
	else
	{
		UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
		event.Skip();
	}
	
	SetProjectModified( true );
}

void UMLDesignerFrame::OnDiagramMouseWheel( wxMouseEvent& event )
{
	event.Skip();
	
	udDiagramCanvas *pCanvas = GetActiveCanvas();
	if( pCanvas )
	{
		m_sliderZoom->SetValue( pCanvas->GetScale() * 50 );
	}
}

void UMLDesignerFrame::OnDiagramKeyDown( wxKeyEvent &event )
{
    switch( event.GetKeyCode() )
    {
        case WXK_DELETE:
        {
            ShapeList lstSelection;
            GetActiveCanvas()->GetSelectedShapes(lstSelection);

            ShapeList::compatibility_iterator node = lstSelection.GetFirst();
            while( node )
            {
                if( !CanRemove((udDiagElementItem*)node->GetData()->GetUserData()) )
                {
                    node->GetData()->Select(false);
                }
                node = node->GetNext();
            }

            GetActiveCanvas()->OnKeyDown( event );
            udProject::Get()->CheckElementLinks();
			
			//SetSelectedProjectItem( NULL );
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
			
			GetActiveCanvas()->UpdateVirtualSize();
        }
        break;

        default:
            //GetActiveCanvas()->OnKeyDown( event );
			event.Skip();
            break;
    }
}

void UMLDesignerFrame::OnConnectionFinished( wxSFShapeEvent& event )
{
    wxSFShapeBase *pConnection = event.GetShape();
    if(pConnection)
    {		
		udPaletteItem *pPaletteItem = GetPaletteTool(pConnection->GetClassInfo()->GetClassName());

        // assign user data
		pConnection->SetUserData((xsSerializable*)wxCreateDynamicObject(pPaletteItem->m_sDataClassName));
        udProjectItem* pUserData = (udProjectItem*)pConnection->GetUserData();
        if(pUserData)
        {
            // create (unique) name
			pUserData->SetName(pPaletteItem->m_sDesc);
        }
		
		// try to set some specialized more properties...
		uddLineElement *pLine = wxDynamicCast( pConnection, uddLineElement );
		if( pLine )
		{
			pLine->GetLabel()->SetHAlign(wxSFShapeBase::halignCENTER);
			pLine->GetLabel()->SetVAlign(wxSFShapeBase::valignMIDDLE);
		}

        // create tree icon
        GetProjectTree()->CreateElementItem(pConnection);
    }
}

void UMLDesignerFrame::OnShapeTextChanged( wxSFShapeTextEvent& event )
{
    uddLabelElement *pLabel = wxDynamicCast( event.GetShape(), uddLabelElement );

    if( !pLabel ) return;

    wxSFShapeBase *pLabelParent = udPROJECT::GetParentElement(pLabel);

    // assume text shapes are child shapes of grand parent uml shapes...
	if(pLabelParent)
	{
		udProjectItem *pElement = wxDynamicCast(pLabelParent->GetUserData(), udProjectItem);
		if(pElement)
		{
			pElement->OnShapeTextChange( event.GetText(), pLabel->GetLabelType(), pLabel->GetId() );
			// the update must be delayed due to unfinished processing of this event in wxSF...
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement, NULL, wxEmptyString, udfDELAYED );
		}
	}
}

void UMLDesignerFrame::OnDropShapes( wxSFShapeDropEvent& event )
{
    ShapeList lstElements = event.GetDroppedShapes();
	
	// remove non-element shapes from a list of dropped shapes
	ShapeList::compatibility_iterator node = lstElements.GetFirst();
	while( node )
	{
		if( node->GetData()->IsKindOf( CLASSINFO(uddDnDElement) ) ) 
		{
			event.GetDropTarget()->GetDiagramManager()->RemoveShape( node->GetData() );
			lstElements.DeleteNode( node );

			node = lstElements.GetFirst();
		}
		else
		{	
			udDiagElementItem *pElement = wxDynamicCast( node->GetData()->GetUserData(), udDiagElementItem );
			if( pElement ) pElement->UpdateInnerContent();
			
			node = node->GetNext();
		}
	}
	
	// update dropped element shapes
    udProject::AppendSubDiagramsShapes( lstElements );

	if( event.GetDragResult() == wxDragCopy )
	{
		UpdateAfterCopy( lstElements );
		
		udProject::Get()->CheckElementLinks();
		udProject::Get()->CheckCodeLinks();
	}
	// rebuild modified diagram tree content...
	UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram() );
	// update all diagram elements
	GetActiveDiagram()->GetDiagramManager().UpdateAll();
}

void UMLDesignerFrame::OnPasteShapes( wxSFShapePasteEvent& event )
{
    ShapeList lstElements = event.GetPastedShapes();
    udProject::AppendSubDiagramsShapes( lstElements );

	UpdateAfterCopy( lstElements );
}

void UMLDesignerFrame::OnZoom( wxScrollEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if( canvas )
    {
        canvas->SetScale(double(m_sliderZoom->GetValue())/50);
        canvas->Refresh(false);
    }
}

void UMLDesignerFrame::OnZoom100( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if( canvas )
    {
        canvas->SetScale(1.f);
        canvas->Refresh(false);
    }
}

void UMLDesignerFrame::OnZoomAll( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if( canvas )
    {
		canvas->SetScaleToViewAll();
        canvas->Refresh(false);
    }
}

void UMLDesignerFrame::OnSelectAll( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if(canvas)
    {
        canvas->SelectAll();
    }
}

void UMLDesignerFrame::OnAlignSelected( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if(canvas)
    {
        switch(event.GetId())
        {
        case IDT_ALIGN_LEFT:
            canvas->AlignSelected(wxSFShapeCanvas::halignLEFT, wxSFShapeCanvas::valignNONE);
            break;

        case IDT_ALIGN_RIGHT:
            canvas->AlignSelected(wxSFShapeCanvas::halignRIGHT, wxSFShapeCanvas::valignNONE);
            break;

        case IDT_ALIGN_CENTER:
            canvas->AlignSelected(wxSFShapeCanvas::halignCENTER, wxSFShapeCanvas::valignNONE);
            break;

        case IDT_ALIGN_TOP:
            canvas->AlignSelected(wxSFShapeCanvas::halignNONE, wxSFShapeCanvas::valignTOP);
            break;

        case IDT_ALIGN_BOTTOM:
            canvas->AlignSelected(wxSFShapeCanvas::halignNONE, wxSFShapeCanvas::valignBOTTOM);
            break;

        case IDT_ALIGN_MIDDLE:
            canvas->AlignSelected(wxSFShapeCanvas::halignNONE, wxSFShapeCanvas::valignMIDDLE);
            break;
        }
    }
}

void UMLDesignerFrame::OnAutolayout( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if(canvas)
    {
		wxString sAlgName;
		
        switch(event.GetId())
        {
			case IDT_ALIGN_CIRCLE:
				sAlgName = wxT("Circle");
				break;
				
			case IDT_ALIGN_MESH:
				sAlgName = wxT("Mesh");
				break;
				
			case IDT_ALIGN_VTREE:
				sAlgName = wxT("Vertical Tree");
				break;
				
			case IDT_ALIGN_HTREE:
				sAlgName = wxT("Horizontal Tree");
				break;
		}
		
		wxSFAutoLayout layout;
		
		ShapeList lstSelection;
		canvas->GetSelectedShapes( lstSelection );
		
		if( lstSelection.IsEmpty() )
		{
			layout.Layout( canvas, sAlgName );
		}
		else
		{
			layout.Layout( lstSelection, sAlgName );
			canvas->MoveShapesFromNegatives();
			canvas->UpdateMultieditSize();
			canvas->Refresh( false );
		}
		
		SaveDiagramState( GetActiveDiagram() );
	}
}

void UMLDesignerFrame::OnGrid( wxCommandEvent &event )
{
    udDiagramCanvas *pCanvas = GetActiveCanvas();
	
    if(pCanvas)
    {
		if( pCanvas->ContainsStyle(wxSFShapeCanvas::sfsGRID_SHOW) )
		{
			pCanvas->RemoveStyle(wxSFShapeCanvas::sfsGRID_SHOW);
		}
		else
			pCanvas->AddStyle(wxSFShapeCanvas::sfsGRID_SHOW);

		if( pCanvas->ContainsStyle(wxSFShapeCanvas::sfsGRID_USE) )
		{
			pCanvas->RemoveStyle(wxSFShapeCanvas::sfsGRID_USE);
		}
		else
			pCanvas->AddStyle(wxSFShapeCanvas::sfsGRID_USE);

        pCanvas->Refresh(false);
    }
}

void UMLDesignerFrame::OnStandardOpp( wxCommandEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if(canvas)
    {
        switch(event.GetId())
        {
            case wxID_UNDO:
            {
                // do not update the project tree view during following operations
                wxWindowUpdateLocker noUpdate(GetProjectTree());

				udProject::Get()->CloseAllSubdiagrams( GetActiveDiagram() );
				
                canvas->Undo();
				
                udProject::Get()->CheckElementLinks();
				udProject::Get()->CheckCodeLinks();
				
				//SetSelectedProjectItem( NULL );
				
				canvas->GetDiagramManager()->UpdateAll();
				canvas->GetManager()->UpdateAllInnerContent();
				
				// rebuild modified diagram tree content...
				if( GetActiveDiagram()->GetSubdiagramElement() )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
				}
				else
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram() );
				}
            }
            break;

            case wxID_REDO:
            {
                // do not update the project tree view during following operations
                wxWindowUpdateLocker noUpdate(GetProjectTree());

				udProject::Get()->CloseAllSubdiagrams( GetActiveDiagram() );
				
                canvas->Redo();
				
                udProject::Get()->CheckElementLinks();
				udProject::Get()->CheckCodeLinks();
				
				//SetSelectedProjectItem( NULL );
				
				canvas->GetDiagramManager()->UpdateAll();
				canvas->GetManager()->UpdateAllInnerContent();
				
				if( GetActiveDiagram()->GetSubdiagramElement() )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
				}
				else
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram() );
				}
            }
            break;

            case wxID_COPY:
                canvas->Copy();
				break;

            case wxID_CUT:
            {
                // do not update the project tree view during following operations
                wxWindowUpdateLocker noUpdate(GetProjectTree());
				
                canvas->Cut();
				
                udProject::Get()->CheckElementLinks();
				
				//SetSelectedProjectItem( NULL );
				
				if( GetActiveDiagram()->GetSubdiagramElement() )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
				}
				else
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, GetActiveDiagram() );
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram() );
				}
            }
            break;

            case wxID_PASTE:
            {
                // do not update the project tree view during following operations
                wxWindowUpdateLocker noUpdate(GetProjectTree());

				canvas->Paste();
				udProject::Get()->CheckElementLinks();
				udProject::Get()->CheckCodeLinks();
				
				canvas->GetDiagramManager()->UpdateAll();
				canvas->GetManager()->UpdateAllInnerContent();
				
				// rebuild modified diagram tree content...
				if( GetActiveDiagram()->GetSubdiagramElement() )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram()->GetSubdiagramElement() );
				}
				else
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, GetActiveDiagram() );
            }
            break;

            case wxID_PRINT:
                canvas->Print();
                break;

            case wxID_PREVIEW:
                canvas->PrintPreview();
                break;

            case wxID_PAGE_SETUP:
                canvas->PageSetup();
                break;

            default:
                event.Skip();
                break;
        }
    }
}

void UMLDesignerFrame::OnPreviewClick( wxCommandEvent &event )
{
    //udGenerator *pGenerator = CreateSelectedGenerator();
	udDiagramItem *pDiagram = GetActiveDiagram();
	udGenerator *pGenerator = udPROJECT::CreateGenerator( pDiagram );

    if(pGenerator)
    {
		wxSetCursor( *wxHOURGLASS_CURSOR );
		
        wxStringOutputStream outstr(NULL);

        if(outstr.IsOk())
        {
			bool fSuccess = true;
			
            udLanguage *pSelLanguage = GetSelectedLanguage();

            // set generators properties
            pGenerator->SetOutputStream(&outstr);
            pGenerator->SetActiveLanguage(pSelLanguage);
			
			udGenerator::ResetIDCounter();

			m_pLogPanel->ClearMessages();
			m_pLogPanel->Freeze();
			
			EnableInternalEvents( false );
			
			// generate declaration code if needed
			if( pSelLanguage->HasSeparatedDecl() )
			{
				wxTextOutputStream tout(outstr);
				
				tout.WriteString( wxT(">>> DECLARATION CODE PREVIEW: \n\n") );
				
				pGenerator->SetMode( udGenerator::genDECLARATION );
				fSuccess = pGenerator->Generate( pDiagram, sfRECURSIVE );
				
				tout.WriteString( wxT("\n>>> DEFINITION CODE PREVIEW: \n\n") );
			}
			
			pGenerator->SetMode( udGenerator::genDEFINITION );

            // generate definition code
            if( fSuccess && pGenerator->Generate( pDiagram, sfRECURSIVE ) )
			{
				// create and show the preview editor windows
				udCodeEditor *pEdit = new udCodeEditor( this, wxID_ANY, wxT("Code preview"), wxDefaultPosition, wxSize(800, 600) );

				udFRAME::InitStyledTextCtrl( pEdit->GetScintilla(), pSelLanguage);
				pEdit->GetScintilla()->SetText( outstr.GetString() );
				pEdit->GetScintilla()->SetReadOnly( true );
				pEdit->Show(true);

				m_pLogPanel->Thaw();
			}
			else
			{
				m_pLogPanel->Thaw();
				wxMessageBox(wxT("Generation process finished with ERROR status. See the log window for more details."), wxT("CodeDesigner"), wxOK | wxICON_WARNING);
			}
			
			EnableInternalEvents( true );
        }
        else
            wxMessageBox(wxT("Unable to initialize output stream."), wxT("CodeDesigner"), wxOK | wxICON_ERROR);

        delete pGenerator;
		
		wxSetCursor( *wxSTANDARD_CURSOR );
    }
    else
        wxMessageBox(wxT("Unable to create selected code generator."), wxT("CodeDesigner"), wxOK | wxICON_ERROR);
}

void UMLDesignerFrame::OnGenerateClick( wxCommandEvent &event )
{	
    udLanguage *pLang = GetSelectedLanguage();
    if(pLang)
    {
        udProjectGenerator *pProjGen = wxGetApp().GetProjectGenerators()[pLang->GetClassInfo()->GetClassName()];
        if(pProjGen)
        {
			pProjGen->ClearGeneratedFiles();
			
			// send event
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_PROJECT_BEFORE_GENERATION, wxID_ANY );
			
			// synchronize code if requested
			udSettings& Settings = udProject::Get()->GetSettings();
			
			if( Settings.GetProperty( wxT("Synchronize before generation") )->AsBool() )
			{
				SerializableList lstFunctions;
				wxArrayString arrModified;
				wxArrayString arrOriginal;
				int nAmbiguous = 0;
				
				udProjectGenerator::GetModifiedUserCode( pLang, lstFunctions, arrOriginal, arrModified, &nAmbiguous );
				
				if( !lstFunctions.IsEmpty() )
				{
					udSynchronizeDialog dlg( this, GetSelectedLanguage() );
					udWindowManager dlgman( dlg, wxT("synchronize_dialog") );
					
					switch( dlg.ShowModal() )
					{				
						case wxID_ABORT:
							wxMessageBox( wxT("Code generation process has been aborted because some user-defined code items' content located in generated files is ambiguous. Please see the log window for more details."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
							return;
							
						case wxID_CANCEL:
							wxMessageBox( wxT("Code generation process has been aborted by the user."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
							return;
						
						default:
							break;
					}
				}
				else if( nAmbiguous > 0 )
				{
					wxMessageBox( wxT("Code generation process has been aborted because some user-defined code items' content placed in generated files is ambiguous. Please see the log window for more details."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
					return;
				}
			}
			
			EnableInternalEvents( false );
			
			pProjGen->SetActiveLanguage( pLang );
            pProjGen->Generate( udProject::Get() );
			
			EnableInternalEvents( true );
			
			for( size_t i = 0; i < pProjGen->GetGeneratedFiles().GetCount(); ++i )
			{
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_PROJECT_FILE_ADDED, wxID_ANY, NULL, NULL, pProjGen->GetGeneratedFiles()[i] );
			}
			
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_PROJECT_AFTER_GENERATION, wxID_ANY );
        }
        else
            wxMessageBox(wxT("Unable to create the project generator for selected language."), wxT("CodeDesigner"), wxOK | wxICON_ERROR);
    }
    else
        wxMessageBox(wxT("Unable to retrieve selected language processor."), wxT("CodeDesigner"), wxOK | wxICON_ERROR);
}

void UMLDesignerFrame::OnToggleGUI( wxCommandEvent &event )
{
	wxString sCompName = m_mapGUIComponents[event.GetId()]->m_sName;
	m_AUIManager.GetPane(sCompName).Show(!m_AUIManager.GetPane(sCompName).IsShown());

	m_AUIManager.Update();
}

void UMLDesignerFrame::OnInsertFromBank(wxCommandEvent& event)
{
	udPackageItem *pPackage = wxDynamicCast( GetSelectedProjectItem(), udPackageItem );
	if( pPackage )
	{
		udInsertFromBankDialog dlg(this, pPackage);
		udWindowManager dlgman( dlg, wxT("insert_from_bank_dialog") );
		
		if( dlg.ShowModal() == wxID_ABORT )
		{
			wxMessageBox( wxT("Some diagrams couldn't be inserted into the projet. Please, see the log for more details."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		}
	}
}

void UMLDesignerFrame::OnStoreToBank(wxCommandEvent& event)
{
	udDiagramItem *pDiag = NULL;
	
	if( GetSelectedProjectItem()->IsKindOf( CLASSINFO(udDiagramItem) ) )
	{
		pDiag = (udDiagramItem*) GetSelectedProjectItem();
	}
	else if( GetSelectedProjectItem()->IsKindOf( CLASSINFO(udSubDiagramElementItem) ) ) 
	{
		pDiag = ((udSubDiagramElementItem*) GetSelectedProjectItem())->GetSubDiagram();
	}
		
	if( pDiag )
	{
		udStoreToBankDialog dlg(this, pDiag);
		udWindowManager dlgman( dlg, wxT("store_to_bank_dialog") );
		
		if( dlg.ShowModal() == wxID_OK )
		{
			wxMessageBox( wxString::Format( wxT("Diagram '%s' was stored into bank."), pDiag->GetName().c_str() ), wxT("CodeDesigner"), wxOK | wxICON_INFORMATION );
		}
	}
}

void UMLDesignerFrame::OnManageBank( wxCommandEvent& event )
{
	udManageBankDialog dlg(this);
	udWindowManager dlgman( dlg, wxT("diagram_bank_dialog") );
	
	dlg.ShowModal();
}

void UMLDesignerFrame::OnExportBank(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("Export diagram bank..."), wxT(""), wxT(""),
		wxT("Diagram bank (*.cdbank)|*.cdbank|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
		
	if( dlg.ShowModal() == wxID_OK )
	{
		if( wxGetApp().GetDiagramBank().SerializeToXml( dlg.GetPath() ) )
		{
			wxMessageBox( wxT("Diagram bank has been exported to '") + dlg.GetPath() + wxT("'."), wxT("CodeDesigner") );
		}
		else
			wxMessageBox( wxT("Unable to export diagram bank to '") + dlg.GetPath() + wxT("'."), wxT("CodeDesigner"), wxOK | wxICON_ERROR );
	}
}

void UMLDesignerFrame::OnImportBank(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("Import diagram bank..."), wxT(""), wxT(""),
		wxT("Diagram bank (*.cdbank)|*.cdbank|All files (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST );
		
	if( dlg.ShowModal() == wxID_OK )
	{
		wxCopyFile( wxGetApp().GetDiagramBankPath(), wxGetApp().GetDiagramBankPath() + wxT(".backup") );
		
		if( wxGetApp().GetDiagramBank().DeserializeFromXml( dlg.GetPath() ) )
		{
			wxMessageBox( wxT("Imported data has been merged with current diagram bank content."), wxT("CodeDesigner") );
		}
		else
		{
			wxMessageBox( wxT("Diagram bank file couldn't be read correctly (probably some previously used plugins aren't loaded at this time)."), wxT("CodeDesigner"), wxOK | wxICON_ERROR );
			wxCopyFile( wxGetApp().GetDiagramBankPath() + wxT(".backup"), wxGetApp().GetDiagramBankPath() );
		}
	}
}

void UMLDesignerFrame::OnManagePlugins(wxCommandEvent& event)
{
	udManagePluginsDialog dlg( this );
	udWindowManager dlgman( dlg, wxT("plugin_dialog") );
	
	dlg.ShowModal();
}

void UMLDesignerFrame::OnResetLayout(wxCommandEvent& event)
{
	if( wxMessageBox( wxT("Are you sure you want to reset current layout?"), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION ) == wxYES )
	{
		m_fResetLayout = true;
		wxMessageBox( wxT("The change will take an effect after application's restart"), wxT("CodeDesigner") );
	}
}

void UMLDesignerFrame::OnSynchronizeCode(wxCommandEvent& event)
{
	udSynchronizeDialog dlg( this, GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("synchronize_dialog") );
	
	switch( dlg.ShowModal() )
	{
		case wxID_NONE:
			wxMessageBox( wxT("There is nothing to update."), wxT("CodeDesigner"), wxOK | wxICON_INFORMATION );
			break;
			
		case wxID_OK:
			SetProjectModified( true );
			wxMessageBox( wxT("Some code items have been updated. Please, see the log window."), wxT("CodeDesigner"), wxOK | wxICON_INFORMATION );
			break;
			
		case wxID_ABORT:
			wxMessageBox( wxT("Some code items couldn't be updated due to their ambiguous instances. Please, see the log window."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
			break;
		
		default:
			break;
	}
}

// update event handlers ////////////////////////////////////////////////////////////

void UMLDesignerFrame::OnUpdatePalettes( wxUpdateUIEvent &event )
{
    event.Check(event.GetId() == m_nCurrentToolId);
}

void UMLDesignerFrame::OnUpdateCreatePackage( wxUpdateUIEvent &event )
{
	udProjectItem *pItem = GetProjectManager()->GetActiveView()->GetSelectedProjectItem();
	// check whether selected item really exists
	if( pItem && !udProject::Get()->Contains( pItem ) ) pItem = NULL;
	
	switch( event.GetId() )
	{
		case IDM_PROJ_PACKAGE:
			event.Enable( pItem && ( pItem->IsKindOf(CLASSINFO(udRootItem)) || pItem->IsKindOf(CLASSINFO(udPackageItem)) ) );
			break;
			
		case IDM_PROJ_CODEPACKAGE:
			event.Enable( !GetProjectManager()->IsOrganized() && pItem && ( pItem->IsKindOf(CLASSINFO(udRootItem)) || pItem->IsKindOf(CLASSINFO(udCodePackageItem)) ) );
			break;
		
		default:
			break;
	};
}

void UMLDesignerFrame::OnUpdateCreateCodeItem( wxUpdateUIEvent &event )
{
	udProjectItem *pItem = GetProjectManager()->GetActiveView()->GetSelectedProjectItem();
	// check whether selected item really exists
	if( pItem && !udProject::Get()->Contains( pItem ) ) pItem = NULL;
	
	event.Enable( pItem && ( pItem->IsKindOf(CLASSINFO(udRootItem)) ||  pItem->IsKindOf(CLASSINFO(udCodePackageItem)) ) );
}

void UMLDesignerFrame::OnUpdateCreateDiagram( wxUpdateUIEvent &event )
{
	udProjectItem *pItem = GetProjectManager()->GetActiveView()->GetSelectedProjectItem();
	// check whether selected item really exists
	if( pItem && !udProject::Get()->Contains( pItem ) ) pItem = NULL;
	
	event.Enable( pItem && pItem->IsKindOf(CLASSINFO(udPackageItem)) );
}

void UMLDesignerFrame::OnUpdateProjectItemSelected( wxUpdateUIEvent &event )
{
	event.Enable( GetProjectManager()->GetActiveView()->GetSelectedProjectItem() );
}

void UMLDesignerFrame::OnUpdateZoomSlider( wxUpdateUIEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if(canvas)
    {
        m_sliderZoom->SetValue(int(canvas->GetScale()*50));
		event.Enable(true);
    }
	else
		event.Enable(false);

}

void UMLDesignerFrame::OnUpdateCanvasActivated( wxUpdateUIEvent &event )
{
    event.Enable( GetActiveCanvas() != NULL );
}

void UMLDesignerFrame::OnUpdateGeneratorActivated( wxUpdateUIEvent &event )
{
	udDiagramItem *pDiag = udPROJECT::GetSuperDiagram(udProject::Get()->GetDiagram(GetActiveCanvas()));
	event.Enable( pDiag && (pDiag->GetActiveGenerator() != wxEmptyString) );
}

void UMLDesignerFrame::OnUpdateChoices( wxUpdateUIEvent &event )
{
	udDiagramItem *pDiag = udProject::Get()->GetDiagram(GetActiveCanvas());
	event.Enable( pDiag && !pDiag->GetSubdiagramElement() );
}


void UMLDesignerFrame::OnUpdateAlignSelected( wxUpdateUIEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if( canvas )
    {
        event.Enable(canvas->CanAlignSelected());
    }
    else
        event.Enable(false);
}

void UMLDesignerFrame::OnUpdateStandardOpp( wxUpdateUIEvent &event )
{
    udDiagramCanvas* canvas = GetActiveCanvas();

    if( canvas )
    {
        switch(event.GetId())
        {
            case wxID_UNDO:
                event.Enable(canvas->CanUndo());
                break;

            case wxID_REDO:
                event.Enable(canvas->CanRedo());
                break;

            case wxID_COPY:
                event.Enable(canvas->CanCopy());
                break;

            case wxID_CUT:
                event.Enable(canvas->CanCut());
                break;

            case wxID_PASTE:
                event.Enable(canvas->CanPaste());
                break;

            default:
                event.Skip();
                break;
        }
    }
    else
        event.Enable(false);
}

void UMLDesignerFrame::OnUpdateGrid( wxUpdateUIEvent &event )
{
    udDiagramCanvas* pCanvas = GetActiveCanvas();
	
    if( pCanvas )
    {
        event.Enable(true);
		event.Check(pCanvas->ContainsStyle(wxSFShapeCanvas::sfsGRID_SHOW));
    }
    else
        event.Enable(false);
}

void UMLDesignerFrame::OnUpdateToggleGUI( wxUpdateUIEvent &event )
{
	wxAuiPaneInfo info = m_AUIManager.GetPane(m_mapGUIComponents[event.GetId()]->m_sName);

    if( info.IsOk() )
    {
        event.Enable(true);
        event.Check(info.IsShown());
    }
    else
        event.Enable(false);
}

void UMLDesignerFrame::OnUpdateInsertFromBank(wxUpdateUIEvent& event)
{
	event.Enable( GetSelectedProjectItem() && GetSelectedProjectItem()->IsKindOf(CLASSINFO(udPackageItem)) );
}

void UMLDesignerFrame::OnUpdateStoreToBank(wxUpdateUIEvent& event)
{
	event.Enable( GetSelectedProjectItem() &&
				  ( GetSelectedProjectItem()->IsKindOf(CLASSINFO(udDiagramItem)) ||
				    GetSelectedProjectItem()->IsKindOf(CLASSINFO(udSubDiagramElementItem)) ) );
}

// other functions ////////////////////////////////////////////////////////////

void UMLDesignerFrame::UpdateAfterCopy(ShapeList& elements)
{
	// make unique names
	wxSFShapeBase *pShape;
	udProjectItem *pDiagElement;

	ShapeList::compatibility_iterator node = elements.GetFirst();
	while( node )
	{
		pShape = node->GetData();
		pDiagElement = (udProjectItem*)pShape->GetUserData();
		if( pDiagElement )
		{
			pDiagElement->OnCreateCopy();
			
		    if( pDiagElement->IsKindOf(CLASSINFO(udElementLinkItem)) )
		    {
                udLABEL::SetContent( pDiagElement->GetName(), pShape, udLABEL::ltTITLE );
            }
		}
		node = node->GetNext();
	}
}

udDiagramType* UMLDesignerFrame::FindDiagramInfoById(long id)
{
    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        if( m_arrDiagrams[i].m_nId == id )return &m_arrDiagrams[i];
    }
    return NULL;
}

udDiagramType* UMLDesignerFrame::FindDiagramInfoByName(const wxString& name)
{
    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        if( m_arrDiagrams[i].m_sName == name )return &m_arrDiagrams[i];
    }
    return NULL;
}

udDiagramType* UMLDesignerFrame::FindDiagramInfoByClassName(const wxString& name)
{
    for( size_t i = 0; i < m_arrDiagrams.GetCount(); i++ )
    {
        if( m_arrDiagrams[i].m_sClassName == name )return &m_arrDiagrams[i];
    }
    return NULL;
}

udGeneratorInfo* UMLDesignerFrame::FindGeneratorInfoByClassName(const wxString& classname)
{
	for( size_t i = 0; i < m_arrGenerators.GetCount(); i++ )
	{
		if( m_arrGenerators[i].GetClassName() == classname ) return &m_arrGenerators[i];
	}
	return NULL;
}

udGeneratorInfo* UMLDesignerFrame::FindGeneratorInfoByName(const wxString& name)
{
	for( size_t i = 0; i < m_arrGenerators.GetCount(); i++ )
	{
		if( m_arrGenerators[i].GetDescription() == name ) return &m_arrGenerators[i];
	}
	return NULL;
}
