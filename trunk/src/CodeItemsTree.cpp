#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "CodeItemsTree.h"
#include "Art.h"
#include "Project.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"

#include <wx/wupdlock.h>

// constructor and destructor ///////////////////////////////////////////////////////

udCodeItemsTree::udCodeItemsTree(wxWindow *parent, wxWindowID id)
: udProjectTree( parent, id, wxDefaultPosition, wxDefaultSize,  wxTR_EDIT_LABELS | wxTR_DEFAULT_STYLE | wxNO_BORDER )
{
}

udCodeItemsTree::~udCodeItemsTree()
{
}

// protected virtual functions ////////////////////////////////////////////////////////////////

wxTreeItemId udCodeItemsTree::CreateTreeItems(udProjectItem* item, wxTreeItemId parent)
{
	wxTreeItemId treeId;

    if( item )
    {
		#ifdef __WXMSW__
		wxWindowUpdateLocker noUpdate( this );
		#endif

		int nImageIndex = udArt::GetImageIndex(item->GetClassInfo()->GetClassName());
		
        // create tree item relevat to project items
        if( item->IsKindOf( CLASSINFO(udRootItem)) )
        {
			treeId = AddRoot( wxT("Reusable code fragments"), nImageIndex, nImageIndex, new udTreeItem(this, item));
			//EnsureVisible( treeId );
			//Expand( treeId );
			m_mapTreeItems[ (wxUIntPtr)item ] = treeId;
        }
		else if( item->IsKindOf( CLASSINFO(udCodePackageItem)) )
		{
			treeId = CreateItem( parent, item, nImageIndex );
			//EnsureVisible( treeId );
			//Expand( treeId );
		}
		else if( item->IsKindOf( CLASSINFO(udVariableItem)) || 
				 item->IsKindOf( CLASSINFO(udFunctionItem)) ) 
		{
			treeId = CreateItem( parent, item, nImageIndex );
		}
		
		// show new tree item
		if( treeId.IsOk() )
		{
			EnsureVisible( treeId );
			Expand( treeId );
		
			// create item's children as well
			SerializableList::compatibility_iterator node = item->GetFirstChildNode();
			while(node)
			{
				CreateTreeItems((udProjectItem*)node->GetData(), treeId);
				node = node->GetNext();
			}
		}
	}
	
	return treeId;
}
