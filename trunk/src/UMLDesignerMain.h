/***************************************************************
 * Name:      UMLDesignerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-10
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/

#ifndef UMLDESIGNERMAIN_H
#define UMLDESIGNERMAIN_H

#define udfCLEAR_CONTENT true
#define udfDONT_CLEAR_CONTENT false
#define udfUNIQUE_NAME true
#define udfAMBIGUOUS_NAME false
#define udfDELAYED true
#define udfNON_DELAYED false

#define udnSTATE_CHART wxT("State Chart")
#define udnSIMPLE_STATE_CHART wxT("Simple State Chart")
#define udnUSE_CASE_DIAGRAM wxT("Use Case Diagram")
#define udnCLASS_DIAGRAM wxT("Class Diagram")
#define udnCOMMON_ITEMS wxT("Common Items")
#define udnUNKNOWN wxT("Unknown")

#define udvID_OFFSET 500000
#define udvPROJECT_VERSION 2

#ifdef __WXMSW__
#define udnIMG_SIZE 16
#else
#define udnIMG_SIZE 24
#endif

#include <wx/aui/aui.h>
#include <wx/mstream.h>
#include <wx/dynarray.h>
#include <wx/hashmap.h>
#include <wx/toolbar.h>
#include <wx/list.h>

#include "UMLDesignerApp.h"
#include "gui/GUI.h"
#include "gui/EditorPanel.h"
#include "ProjectManager.h"
#include "ProjStructTree.h"
#include "CodeItemsTree.h"
#include "Log.h"
#include "projectbase/codegen/Generator.h"
#include "projectbase/FrameBase.h"

WX_DECLARE_LIST(wxEvtHandler, ListenerList);

class udPanelItem
{
public:
	udPanelItem(const wxString &name, const wxString &desc) : m_sName(name), m_sDesc(desc) {;}
    wxString m_sName;
    wxString m_sDesc;
};

//WX_DECLARE_OBJARRAY( udPanelItem, PanelsArray );
WX_DECLARE_HASH_MAP( int, udPanelItem*, wxIntegerHash, wxIntegerEqual, PanelMap ); 

class udDiagramType
{
public:
    udDiagramType(long id, const wxString& name, const wxString classname ) :
        m_nId(id), m_sName(name), m_sClassName(classname) {;}

    long m_nId;
    wxString m_sName;
    wxString m_sClassName;
};

WX_DECLARE_OBJARRAY( udDiagramType, DiagramsArray );

class udProjectItemType
{
public:

	enum PROJITEMTYPE
	{
		pitPROJITEM,
		pitCODEITEM
	};
	
	udProjectItemType(const wxString& classname, const wxString& viewname, PROJITEMTYPE type) 
	: m_sClassName(classname), m_sViewName(viewname), m_nProjItemType(type) {;}
	
	wxString m_sClassName;
	wxString m_sViewName;
	PROJITEMTYPE m_nProjItemType;
};

WX_DECLARE_HASH_MAP( int, udProjectItemType*, wxIntegerHash, wxIntegerEqual, ProjectItemMap ); 

class UMLDesignerFrame: public _MainFrame
{
    public:
        UMLDesignerFrame(wxFrame *frame);
        ~UMLDesignerFrame();

		udLanguage* GetSelectedLanguage();
        udDiagramItem* GetActiveDiagram();
        udDiagramCanvas* GetActiveCanvas();
        
		udLog* GetLogWindow(){return m_pLogPanel;}
		
		udProjectManager* GetProjectManager(){ return m_pProjectManager; }
		udProjStructTree* GetProjectTree(){ return (udProjStructTree*)m_pProjectManager->GetView( wxT("Project items") ); }
		udCodeItemsTree* GetCodeTree(){ return (udCodeItemsTree*)m_pProjectManager->GetView( wxT("Code items") ); }
		wxAuiNotebook* GetMainNotebook(){ return m_auintbDesignArea; }
		wxSFThumbnail* GetThumbnail(){	return m_pThumbnail; }
		
		void OpenProjectFile(const wxString& path);
		
		static void EnableInternalEvents(bool enab) { m_fDispatchEvents = enab; }
		static bool InternalEventsEnabled() { return m_fDispatchEvents; }
		
		void ConnectDiagramEvents(udDiagramCanvas *diagram, bool enable);
		void DispatchEvent(wxEvent& evt, bool delayed);
		void RegisterEventListener(wxEvtHandler *handler);
		void UnregisterEventListener(wxEvtHandler *handler);
		static void SendProjectEvent( wxEventType cmdType = wxEVT_NULL, int id = 0, udProjectItem *item = NULL, udProjectItem *parent = NULL, const wxString& data = wxEmptyString, bool delayed = false );

        void InitializeProject(udProject *proj);
        void InitializeChoices();
		
		void SetProjectModified(bool modified);
		bool IsProjectModified(){return m_fModified;}
		void SaveDiagramState(udDiagramItem *diag);

		static int UpdateCreateSubmenu(wxMenu *submenu, PaletteArray *palette, int itemmask, bool clear);
		static int UpdateCreateSubmenu(wxMenu *submenu, const wxArrayString& items, bool clear);

		udGenerator* CreateSelectedGenerator();
		void CreateDiagramElement(long id, const wxPoint& pos);

		bool CanRemove(udProjectItem *item);

		udDiagramType* FindDiagramInfoById(long id);
		udDiagramType* FindDiagramInfoByName(const wxString& name);
		udDiagramType* FindDiagramInfoByClassName(const wxString& name);
		
		udGeneratorInfo* FindGeneratorInfoByName(const wxString& name);
		udGeneratorInfo* FindGeneratorInfoByClassName(const wxString& classname);
		
		DiagramsArray& GetDiagrams(){return m_arrDiagrams;}
		GeneratorsArray& GetGenerators(){return m_arrGenerators;}
		
		StringMap& GetCodePackages(){return m_mapDefaultPkgNames;}
		
		void SetSelectedProjectItem(udProjectItem *item){m_pProcessedItem = item;}
		udProjectItem* GetSelectedProjectItem(){return m_pProcessedItem;}

        void OnDiagramLeftClick( wxMouseEvent &event );
        void OnDiagramRightClick( wxMouseEvent &event );
        void OnDiagramLeftDoubleClick( wxMouseEvent &event );
		void OnDiagramMouseWheel( wxMouseEvent &event );
        void OnDiagramKeyDown( wxKeyEvent &event );
        void OnConnectionFinished( wxSFShapeEvent& event );
        void OnShapeTextChanged( wxSFShapeTextEvent& event );
		void OnDropShapes( wxSFShapeDropEvent& event );
		void OnPasteShapes( wxSFShapePasteEvent& event );

    protected:
		udLog* m_pLogPanel;
		udProjectManager* m_pProjectManager;
		udProjectItem* m_pProcessedItem;
		
		wxSFThumbnail* m_pThumbnail;
		udCodeEditorPanel* m_pInstantEditor;
		
		/*#ifdef __WXGTK__*/
		wxAuiToolBar* m_tbMainFrame;
        wxAuiToolBar* m_tbProjectItems;
        wxAuiToolBar* m_tbDesign;
        wxAuiToolBar* m_tbGenerator;
		/*#else
		wxToolBar* m_tbMainFrame;
        wxToolBar* m_tbProjectItems;
        wxToolBar* m_tbDesign;
        wxToolBar* m_tbGenerator;
		#endif*/
	
        wxChoice* m_chGenerators;
        wxChoice* m_chAlgorithms;
        wxChoice* m_chLanguages;

		wxMenu* m_pPopupMenu;

        wxAuiManager m_AUIManager;

		//PanelsArray m_arrGUIComponents;
		DiagramsArray m_arrDiagrams;
		GeneratorsArray m_arrGenerators;
		
		PanelMap m_mapGUIComponents;
		ProjectItemMap m_mapProjectItems;
		StringMap m_mapDefaultPkgNames;
		
		ListenerList m_lstListeners;

		bool m_fModified;
		bool m_fClosing;
		bool m_fResetLayout;
        long m_nCurrentToolId;
		wxPoint m_nLastClickedPosition;

        void CreatePalettes();
        void CreatePaletteToolbar(const wxString& title);
        void CreateMainToolbars();
		void CreateMainMenus();
		void CreateRecentFilesMenu();
        void CreateProjectManager();
        void CreateThumbnail();
        void CreateDynMenu();
		void CreatePopupMenu();
		void CreateLogWindow();
		void CreateInstantEditor();

		void UpdateAfterCopy(ShapeList& elements);
		
		void InsertIntoRecentFiles(wxString file);
		
		// static protected members
		static bool m_fDispatchEvents;

    private:
        virtual void OnNewProject( wxCommandEvent &event );
        virtual void OnOpenProject( wxCommandEvent &event );
        virtual void OnSaveProject( wxCommandEvent &event );
		virtual void OnSaveProjectAs( wxCommandEvent &event );
        virtual void OnClose( wxCloseEvent &event );
        virtual void OnQuit( wxCommandEvent &event );
        virtual void OnAbout( wxCommandEvent &event );
        virtual void OnIdle( wxIdleEvent &event );
		virtual void OnCreateProjectItem( wxCommandEvent &event );
        virtual void OnRemoveAll( wxCommandEvent &event );
        virtual void OnRemoveItem( wxCommandEvent &event );
        virtual void OnEditItem( wxCommandEvent &event );
        virtual void OnSelectAll( wxCommandEvent &event );
        virtual void OnZoom ( wxScrollEvent &event );
		virtual void OnZoom100( wxCommandEvent& event );
		virtual void OnZoomAll( wxCommandEvent& event );
        virtual void OnExportDiagram( wxCommandEvent &event );
        virtual void OnPreviewClick( wxCommandEvent &event );
        virtual void OnGenerateClick( wxCommandEvent &event );
		virtual void OnToggleGUI( wxCommandEvent& event );
		virtual void OnPreferences( wxCommandEvent& event );
		virtual void OnSettings( wxCommandEvent& event );
		virtual void OnStoreToBank(wxCommandEvent& event);
		virtual void OnInsertFromBank(wxCommandEvent& event);
		virtual void OnManageBank( wxCommandEvent& event );
		virtual void OnManagePlugins(wxCommandEvent& event);
		virtual void OnResetLayout(wxCommandEvent& event);
		virtual void OnSynchronizeCode(wxCommandEvent& event);
		virtual void OnExportBank(wxCommandEvent& event);
		virtual void OnImportBank(wxCommandEvent& event);

        virtual void OnUpdateCreatePackage( wxUpdateUIEvent &event );
		virtual void OnUpdateCreateCodeItem( wxUpdateUIEvent &event );
        virtual void OnUpdateZoomSlider( wxUpdateUIEvent &event );
        virtual void OnUpdateToggleGUI( wxUpdateUIEvent& event );

        virtual void OnUpdateProjectItemSelected( wxUpdateUIEvent &event );
        virtual void OnUpdateCanvasActivated( wxUpdateUIEvent &event );
        virtual void OnUpdateGeneratorActivated( wxUpdateUIEvent &event );
		
		virtual void OnUpdateStoreToBank( wxUpdateUIEvent& event );
		virtual void OnUpdateInsertFromBank( wxUpdateUIEvent& event );
		
		virtual void OnPageClosing( wxAuiNotebookEvent &event );
        virtual void OnPageChanged( wxAuiNotebookEvent &event );

        void OnCreateDiagram( wxCommandEvent &event );
		void OnCreateDiagramElement( wxCommandEvent &event );
        void OnShowDiagram( wxCommandEvent &event );
        void OnShowPreviewDiagram( wxCommandEvent &event );
		void OnNavigateTo( wxCommandEvent &event );
		void OnClearCodeItems( wxCommandEvent &event );

		void OnDelayedRemove( wxCommandEvent &event );
		void OnDelayedRemoveElement( wxCommandEvent &event );
		void OnDelayedRemoveAll( wxCommandEvent &event );
		void OnDelayedEdit( wxCommandEvent &event );
		void OnDelayedEditCode( wxCommandEvent &event );
		void OnDelayedCutElement( wxCommandEvent &event );

        void OnStandardOpp( wxCommandEvent &event );
        void OnPalettes( wxCommandEvent &event );
        void OnAlignSelected( wxCommandEvent &event );
        void OnAutolayout( wxCommandEvent &event );
        void OnGrid( wxCommandEvent &event );
        void OnRemoveElement( wxCommandEvent &event );
		void OnRecentFile( wxCommandEvent &event );

        void OnLanguageChoice( wxCommandEvent &event );
        void OnGeneratorChoice( wxCommandEvent &event );
        void OnAlgorithmChoice( wxCommandEvent &event );

		void OnUpdateChoices( wxUpdateUIEvent &event );
        void OnUpdateCreateDiagram( wxUpdateUIEvent &event );
        void OnUpdateStandardOpp( wxUpdateUIEvent& event );
        void OnUpdatePalettes( wxUpdateUIEvent &event );
        void OnUpdateAlignSelected( wxUpdateUIEvent &event );
        void OnUpdateGrid( wxUpdateUIEvent &event );
		
		void OnProjectItemSelected(udProjectEvent& event);
		void OnProjectItemChanged(udProjectEvent& event);
		void OnProjectItemAdded(udProjectEvent& event);
		void OnProjectItemRemoved(udProjectEvent& event);
		void OnProjectTaskRemove(udProjectEvent& event);

		void InitializeComponents();
		void InitializeLayoutAlgorithms();
		void CleanUpComponents();

    DECLARE_EVENT_TABLE()
};

#endif // UMLDESIGNERMAIN_H
