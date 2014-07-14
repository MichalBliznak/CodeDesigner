#ifndef __udprojecttree__
#define __udprojecttree__

#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include <wx/hashmap.h>

#include "Ids.h"
#include "Project.h"
#include "projectbase/Events.h"

WX_DECLARE_HASH_MAP( wxUIntPtr, wxTreeItemId, wxIntegerHash, wxIntegerEqual, ObjectMap );

class udProjectTree : public wxTreeCtrl
{
public:
	friend class udTreeItem;
	
	// constructor and destructor
	udProjectTree(wxWindow *parent, wxWindowID id, wxPoint pos, wxSize size, int style);
	virtual ~udProjectTree();
	
	// public functions
	void BuildFromProject(udProject* project);
	
	wxTreeItemId FindTreeItem(udProjectItem *item);

	udProjectItem* GetSelectedProjectItem();
	
	void SuppresNextSelectEvent(bool outside){m_fSelectedOutside = outside;}
	
	// virtual public functions
	virtual wxTreeItemId CreateTreeItems(udProjectItem* item, wxTreeItemId parent);
	virtual void UpdateItem(udProjectItem *item);
	virtual void RemoveItem(udProjectItem *item);
	wxTreeItemId CreateItem(wxTreeItemId parent, udProjectItem *item, int image);
	
protected:
    // protected data members
    bool m_fSelectedOutside;
	
	ObjectMap m_mapTreeItems;
	
	// protected event handlers
    virtual void OnContextMenu(wxTreeEvent& event);
    virtual void OnActivation(wxTreeEvent& event);
    virtual void OnSelectionChanged(wxTreeEvent& event);
    virtual void OnBeginLabelEdit(wxTreeEvent& event);
    virtual void OnEndLabelEdit(wxTreeEvent& event);
    virtual void OnKeyDown(wxTreeEvent& event);
    virtual void OnBeginDrag(wxTreeEvent& event);
	virtual void OnEndDrag(wxTreeEvent& event);
	
	void OnProjectItemAdded(udProjectEvent& event);
	void OnProjectItemChanged(udProjectEvent& event);
	void OnProjectItemRemoved(udProjectEvent& event);
	void OnProjectItemSelected(udProjectEvent& event);

    DECLARE_EVENT_TABLE();
};

class udTreeItem : public wxTreeItemData
{
public:
	udTreeItem(udProjectTree* parent, udProjectItem *item) : m_pProjectItem(item), m_pParentTree(parent)
	{;}
    virtual ~udTreeItem()
	{
		m_pParentTree->m_mapTreeItems.erase( (wxUIntPtr)m_pProjectItem );
	}

    // public member data accessors
	udProjectItem* GetProjectItem() { return m_pProjectItem; }
	
protected:
	// protected data members
	udProjectItem *m_pProjectItem;
	udProjectTree *m_pParentTree;
};

#endif // __udprojecttree__
