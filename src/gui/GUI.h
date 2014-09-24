///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  6 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/aui/auibook.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/stc/stc.h>
#include <wx/listctrl.h>
#include <wx/toolbar.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/splitter.h>
#include <wx/stattext.h>
#include <wx/treectrl.h>
#include <wx/dialog.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/checklst.h>
#include <wx/clrpicker.h>
#include <wx/notebook.h>
#include <wx/gbsizer.h>

///////////////////////////////////////////////////////////////////////////

#define IDM_FILE_EXPORT 6000
#define IDM_EDIT_SELECTALL 6001
#define IDM_EDIT_PREFERENCES 6002
#define IDM_VIEW_RESET 6003
#define IDM_VIEW_PROJECT_PANEL 6004
#define IDM_VIEW_LOG_PANEL 6005
#define IDM_VIEW_THUMBNAIL_PANEL 6006
#define IDM_VIEW_EDITOR 6007
#define IDM_VIEW_FILE_TB 6008
#define IDM_VIEW_DIAGRAM_TB 6009
#define IDM_VIEW_LAYOUT_TB 6010
#define IDM_VIEW_GENERATOR_TB 6011
#define IDM_PROJ_PACKAGE 6012
#define IDM_PROJ_CODEPACKAGE 6013
#define IDM_PROJ_VARIABLE 6014
#define IDM_PROJ_FUNCTION 6015
#define IDM_PROJ_EDIT 6016
#define IDM_PROJ_REMOVE 6017
#define IDM_PROJ_REMOVEALL 6018
#define IDM_PROJ_SETTINGS 6019
#define IDM_BANK_MANAGE 6020
#define IDM_DIAG_STORETOBANK 6021
#define IDM_DIAG_INSERTFROMBANK 6022
#define IDM_BANK_IMPORT 6023
#define IDM_BANK_EXPORT 6024
#define IDM_CODE_PREVIEW 6025
#define IDM_CODE_GENERATE 6026
#define IDM_CODE_SYNCHRONIZE 6027
#define IDM_PLUGINS_MANAGE 6028
#define IDC_AUINTB_PALETTES 6029
#define IDC_AUINTB_DESIGNAREA 6030
#define IDC_ZOOM 6031
#define IDT_PROJMAN_LINK 6032
#define IDT_PROJMAN_EXPAND 6033
#define IDT_PROJMAN_SHOWPROPS 6034
#define IDT_PROJMAN_ORGANIZECI 6035
#define IDC_AUINTB_PROJMAN 6036
#define IDT_INSTEDITOR_SAVE 6037
#define IDC_SETTINGSDLG_PROPGRID 6038
#define IDM_DBANK_SELECTALL 6039
#define IDM_DBANK_DESELECTALL 6040
#define IDM_DBANK_SHOWDEPS 6041
#define IDC_CATEGORY_CREATE 6042
#define IDC_CAT_CREATE 6043
#define IDC_CAT_RENAME 6044
#define IDC_CAT_REMOVE 6045
#define IDC_DIAG_REMOVE 6046
#define IDM_DIAG_REMOVEALL 6047
#define IDM_DIAG_COPY 6048
#define IDC_DIAG_MOVE 6049
#define IDM_SYNCHRO_SELECT_ALL 6050
#define IDM_SYNCHRO_DESELECT_ALL 6051

///////////////////////////////////////////////////////////////////////////////
/// Class _MainFrame
///////////////////////////////////////////////////////////////////////////////
class _MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* recentFilesMenu;
		wxMenu* editMenu;
		wxMenu* viewMenu;
		wxMenu* projMenu;
		wxMenu* bankMenu;
		wxMenu* codeGenMenu;
		wxMenu* pluginsMenu;
		wxMenu* helpMenu;
		wxStatusBar* statusBar;
		wxPanel* m_mainPanel;
		wxAuiNotebook* m_auintbPalettes;
		wxAuiNotebook* m_auintbDesignArea;
		wxBitmapButton* btnZoom100;
		wxBitmapButton* btnZoomAll;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void OnNewProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveProject( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveProjectAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExportDiagram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateCanvasActivated( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPreferences( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnResetLayout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToggleGUI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateToggleGUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCreateProjectItem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateCreatePackage( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnUpdateCreateCodeItem( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnEditItem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateProjectItemSelected( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemoveItem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnManageBank( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStoreToBank( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateStoreToBank( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnInsertFromBank( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateInsertFromBank( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnImportBank( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExportBank( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPreviewClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateGeneratorActivated( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnGenerateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSynchronizeCode( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnManagePlugins( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPageChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnPageClosing( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnZoom100( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateZoomSlider( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnZoomAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoom( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		wxSlider* m_sliderZoom;
		
		_MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CodeDesigner"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,480 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~_MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EditorFrame
///////////////////////////////////////////////////////////////////////////////
class _EditorFrame : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* m_statusBar;
		wxMenuBar* m_menuBar;
		wxMenu* m_menuFile;
		wxMenu* m_menuEdit;
		wxStyledTextCtrl* m_scintillaEditor;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnCloseClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCutClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateCut( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCopyClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateCopy( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnPasteClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdatePaste( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Code preview"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,450 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxTAB_TRAVERSAL );
		
		~_EditorFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _LogPanel
///////////////////////////////////////////////////////////////////////////////
class _LogPanel : public wxPanel 
{
	private:
	
	protected:
		wxListCtrl* m_pLogList;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRightClick( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		_LogPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~_LogPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ProjManPanel
///////////////////////////////////////////////////////////////////////////////
class _ProjManPanel : public wxPanel 
{
	private:
	
	protected:
		wxToolBar* m_toolBar;
		wxToolBarToolBase* m_toolLinkEditor; 
		wxToolBarToolBase* m_toolExpandAll; 
		wxToolBarToolBase* m_toolProperties; 
		wxToolBarToolBase* m_toolOrganizeCI; 
		wxSplitterWindow* m_pSplitter;
		wxPanel* m_pPanelTree;
		wxAuiNotebook* m_auintbViews;
		wxPanel* m_pPanelProperties;
		wxPropertyGrid* m_pPropertiesGrid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnLinkedEditor( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateLinkedEditor( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnExpandAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowProperties( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateShowProperties( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnOrganizeCI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateOrganizeCI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnPropsSashChanged( wxSplitterEvent& event ) { event.Skip(); }
		virtual void OnViewChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		virtual void OnPGActivated( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ProjManPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,445 ), long style = wxTAB_TRAVERSAL ); 
		~_ProjManPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _EditorPanel
///////////////////////////////////////////////////////////////////////////////
class _EditorPanel : public wxPanel 
{
	private:
	
	protected:
		wxToolBar* m_toolActions;
		wxToolBarToolBase* m_toolSave; 
		wxStaticText* m_stCodeItem;
		wxStyledTextCtrl* m_scintillaEditor;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateSave( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnKeyDown( wxKeyEvent& event ) { event.Skip(); }
		
	
	public:
		
		_EditorPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,150 ), long style = wxTAB_TRAVERSAL ); 
		~_EditorPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _SettingsDialog
///////////////////////////////////////////////////////////////////////////////
class _SettingsDialog : public wxDialog 
{
	private:
	
	protected:
		wxSplitterWindow* m_pSplitter;
		wxPanel* m_pPanelTree;
		wxTreeCtrl* m_pCategoryTree;
		wxPanel* m_pPanelProps;
		wxPropertyGrid* m_pPropertyGrid;
		wxButton* m_btnDefaults;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnChangeCategory( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnDefaults( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_SettingsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_SettingsDialog();
		
		void m_pSplitterOnIdle( wxIdleEvent& )
		{
			m_pSplitter->SetSashPosition( 205 );
			m_pSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( _SettingsDialog::m_pSplitterOnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _InsertFromBankDialog
///////////////////////////////////////////////////////////////////////////////
class _InsertFromBankDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText69;
		wxChoice* m_chCategory;
		wxStaticText* m_staticText70;
		wxListCtrl* m_lstDiagrams;
		wxMenu* m_menuDiagrams;
		wxButton* m_btnInsert;
		wxButton* m_btnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCategoryChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnShowDeps( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateShowDeps( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnInsertClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_InsertFromBankDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Select diagrams for insertion"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_InsertFromBankDialog();
		
		void m_lstDiagramsOnContextMenu( wxMouseEvent &event )
		{
			m_lstDiagrams->PopupMenu( m_menuDiagrams, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _StoreToBankDialog
///////////////////////////////////////////////////////////////////////////////
class _StoreToBankDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText69;
		wxChoice* m_chCategory;
		wxButton* m_btnCreateCat;
		wxStaticText* m_stDiagName;
		wxStaticText* m_staticText76;
		wxTextCtrl* m_textDescription;
		wxStaticText* m_staticText70;
		wxListCtrl* m_lstDeps;
		wxButton* m_btnInsert;
		wxButton* m_btnCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCreateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStoreClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_StoreToBankDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Store diagram to bank"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 435,450 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_StoreToBankDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _DependenciesDialog
///////////////////////////////////////////////////////////////////////////////
class _DependenciesDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText77;
		wxTextCtrl* m_textDescription;
		wxStaticText* m_staticText70;
		wxListCtrl* m_lstDeps;
		wxButton* m_btnCancel;
	
	public:
		
		_DependenciesDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Diagram Info"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_DependenciesDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ManageBankDialog
///////////////////////////////////////////////////////////////////////////////
class _ManageBankDialog : public wxDialog 
{
	private:
	
	protected:
		wxListBox* m_lbCategories;
		wxButton* m_btnCreateCat;
		wxButton* m_btnRenameCat;
		wxButton* m_btnRemoveCat;
		wxListCtrl* m_lstDiagrams;
		wxStaticText* m_staticText78;
		wxTextCtrl* m_textDescription;
		wxStaticText* m_staticText75;
		wxListCtrl* m_lstDeps;
		wxButton* m_btnRemoveDiag;
		wxButton* m_btnRemoveAllDiag;
		wxStaticLine* m_staticline1;
		wxButton* m_btnCopyDiag;
		wxButton* m_btnMoveDiag;
		wxButton* m_btnClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCategoryChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCreateCat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRenameCat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRenameCat( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemoveCat( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemoveCat( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnDiagramChange( wxListEvent& event ) { event.Skip(); }
		virtual void OnRemoveDiag( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemoveDiag( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnRemoveAllDiag( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemoveAllDiag( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnCopyDiag( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateCopyTo( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnMoveDiag( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateMoveTo( wxUpdateUIEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ManageBankDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Manage diagram bank"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 710,400 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ManageBankDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _ManagePluginsDialog
///////////////////////////////////////////////////////////////////////////////
class _ManagePluginsDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText13;
		wxCheckListBox* m_checkListPlugins;
		wxListCtrl* m_listCtrlPluginInfo;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnPluginSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_ManagePluginsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Manage plugins"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_ManagePluginsDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _SynchronizeDialog
///////////////////////////////////////////////////////////////////////////////
class _SynchronizeDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText16;
		wxCheckListBox* m_checkList;
		wxMenu* menuCheckList;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText15;
		wxStyledTextCtrl* m_scintillaModified;
		wxStyledTextCtrl* m_scintillaOriginal;
		wxStdDialogButtonSizer* buttonSizer;
		wxButton* buttonSizerOK;
		wxButton* buttonSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSelectCodeItem( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSelectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_SynchronizeDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Synchronize code"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_SynchronizeDialog();
		
		void m_checkListOnContextMenu( wxMouseEvent &event )
		{
			m_checkList->PopupMenu( menuCheckList, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class _GroupDialog
///////////////////////////////////////////////////////////////////////////////
class _GroupDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxTextCtrl* m_eName;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_eDescription;
		wxNotebook* m_pNotebook;
		wxPanel* m_pageAdv;
		wxStaticText* m_staticText70;
		wxColourPickerCtrl* m_colourPicker;
		wxStdDialogButtonSizer* bntSizer;
		wxButton* bntSizerOK;
		wxButton* bntSizerCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		_GroupDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Group element properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~_GroupDialog();
	
};

#endif //__GUI_H__
