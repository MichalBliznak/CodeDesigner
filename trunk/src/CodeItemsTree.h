#ifndef __udcodeitemstree__
#define __udcodeitemstree__

#include "ProjectTree.h"

class udCodeItemsTree : public udProjectTree
{
public:
	udCodeItemsTree(wxWindow *parent, wxWindowID id);
	virtual ~udCodeItemsTree();
	
	// public virtual functions
	virtual wxTreeItemId CreateTreeItems(udProjectItem* item, wxTreeItemId parent);
};

#endif // __udcodeitemstree__
