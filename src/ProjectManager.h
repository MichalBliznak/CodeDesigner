#ifndef __udprojectmanager__
#define __udprojectmanager__

#include "gui/GUI.h"
#include "ProjectTree.h"

#include <wx/hashmap.h>

WX_DECLARE_STRING_HASH_MAP( udProjectTree*, ViewsMap );

class udProjectManager : public _ProjManPanel
{
public:
	// constructor and destructor
	udProjectManager(wxWindow *parent);
	virtual ~udProjectManager();
	
	// public functions
	void BuildFromProject( udProject *project );
	
	void SetActiveView( const wxString& name );
	udProjectTree* GetActiveView();
	udProjectTree* GetView( const wxString& name );
	wxString GetActiveViewName();
	
	ViewsMap& GetViews(){ return m_mapViews; }
	
	wxAuiNotebook* GetNotebook(){ return m_auintbViews; }
	
	void InsertView( udProjectTree *ctrl, const wxString& name );
	void RemoveView( const wxString& name );
	void ClearAllViews();
	
	void UpdatePropertiesView( udProjectItem *item );
	
	// public member data accessors
	bool IsLinked(){ return m_fLinked; }
	bool IsOrganized(){ return m_fOrganizeCI; }
	
protected:
	// protected data members
	ViewsMap m_mapViews;
	
	bool m_fExpanded;
	bool m_fLinked;
	bool m_fShowProperties;
	bool m_fOrganizeCI;
	int m_nPropsSashPosition;
	
	// protected event handlers
	virtual void OnExpandAll( wxCommandEvent& event );
	virtual void OnViewChanged( wxAuiNotebookEvent& event );
	virtual void OnLinkedEditor( wxCommandEvent& event );
	virtual void OnUpdateLinkedEditor( wxUpdateUIEvent& event );
	virtual void OnShowProperties( wxCommandEvent& event );
	virtual void OnUpdateShowProperties( wxUpdateUIEvent& event );
	virtual void OnPropsSashChanged( wxSplitterEvent& event );
	virtual void OnPGActivated( wxMouseEvent& event );
	virtual void OnOrganizeCI( wxCommandEvent& event );
	virtual void OnUpdateOrganizeCI( wxUpdateUIEvent& event );
	
	void OnIdle( wxIdleEvent& event );
	
	void OnProjectItemSelected(udProjectEvent& event);
	
	DECLARE_EVENT_TABLE();
};

#endif // __udprojectmanager__
