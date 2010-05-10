#ifndef PROJSTRUCTTREE_H
#define PROJSTRUCTTREE_H

#include "ProjectTree.h"

class udProjStructTree : public udProjectTree
{
public:
    udProjStructTree(wxWindow *parent, wxWindowID id);
    virtual ~udProjStructTree();
		
	// public functions
    void CreateDiagramItems(udProjectItem* item, wxTreeItemId parent);
    void CreateElementItem(wxSFShapeBase* item);
	void CreateElementsItems(const ShapeList& list);
    void UpdateElementItem(wxSFShapeBase* item);
	void UpdateDiagramItem(udDiagramItem* item);
	
    // public virtual functions
	virtual wxTreeItemId CreateTreeItems(udProjectItem* item, wxTreeItemId parent);
	virtual void UpdateItem(udProjectItem *item);
	
protected:
	// protected functions
	void InsertPaletteItems(const wxString &fromPalette, udDiagramItem* item, wxTreeItemId parent);
};


#endif // PROJSTRUCTTREE_H
