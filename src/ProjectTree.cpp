#include "wx_pch.h"

#include "ProjectTree.h"

#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "Art.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE(udProjectTree, wxTreeCtrl)
    EVT_TREE_ITEM_MENU( wxID_ANY, udProjectTree::OnContextMenu )
    EVT_TREE_ITEM_ACTIVATED( wxID_ANY, udProjectTree::OnActivation )
    EVT_TREE_SEL_CHANGED( wxID_ANY, udProjectTree::OnSelectionChanged )
    EVT_TREE_BEGIN_LABEL_EDIT( wxID_ANY, udProjectTree::OnBeginLabelEdit )
    EVT_TREE_END_LABEL_EDIT( wxID_ANY, udProjectTree::OnEndLabelEdit )
    EVT_TREE_KEY_DOWN( wxID_ANY, udProjectTree::OnKeyDown )
    EVT_TREE_BEGIN_DRAG( wxID_ANY, udProjectTree::OnBeginDrag )
	EVT_TREE_END_DRAG( wxID_ANY, udProjectTree::OnEndDrag )
	
	EVT_CD_ITEM_ADDED( wxID_ANY, udProjectTree::OnProjectItemAdded )
	EVT_CD_ITEM_CHANGED( wxID_ANY, udProjectTree::OnProjectItemChanged )
	EVT_CD_ITEM_REMOVED( wxID_ANY, udProjectTree::OnProjectItemRemoved )
	EVT_CD_ITEM_SELECTED( wxID_ANY, udProjectTree::OnProjectItemSelected )
END_EVENT_TABLE();

// constructor and destructor ///////////////////////////////////////////////////////

udProjectTree::udProjectTree(wxWindow *parent, wxWindowID id, wxPoint pos, wxSize size, int style)
: wxTreeCtrl( parent, id, pos, size, style )
{
	//this->SetExtraStyle( wxWS_EX_BLOCK_EVENTS );
	
    // initialize image list
	SetImageList( udArt::GetImageList() );

    m_fSelectedOutside = false;
}

udProjectTree::~udProjectTree()
{
}

// public functions ////////////////////////////////////////////////////////////////

void udProjectTree::BuildFromProject(udProject* project)
{
    wxASSERT(project);

    if( project )
    {
		udProjectItem *selItem = NULL;

        // try to remember last selected tree item
        wxTreeItemId lastItem = GetSelection();
        if(lastItem.IsOk())
        {
            udTreeItem* itemData = (udTreeItem*)GetItemData(lastItem);
            if(itemData)
            {
                selItem = itemData->GetProjectItem();
            }
        }
       
		//CollapseAll();
		
		// clear current content
        DeleteAllItems();
		 // create new tree content
        this->CreateTreeItems((udProjectItem*)project->GetRootItem(), wxTreeItemId(0L));

        // try to find previously remembered tree item
        if( selItem )
        {
            lastItem = FindTreeItem(selItem);
            if(lastItem.IsOk())
            {
                EnsureVisible(lastItem);
                Expand(lastItem);
                SelectItem(lastItem, true);
            }
        }

        m_fSelectedOutside = false;
    }
}

wxTreeItemId udProjectTree::CreateItem(wxTreeItemId parent, udProjectItem* item, int image)
{
	wxTreeItemId treeId = AppendItem( parent, item->GetName(), image, image, new udTreeItem(this, item) );
	m_mapTreeItems[ (wxUIntPtr)item ] = treeId;
	
	return treeId;
}

udProjectItem* udProjectTree::GetSelectedProjectItem()
{
	wxTreeItemId selItem = GetSelection();
	if( selItem.IsOk() )
	{
		return ((udTreeItem*)GetItemData(selItem))->GetProjectItem();
	}
	else
		return NULL;
}

wxTreeItemId udProjectTree::FindTreeItem(udProjectItem *item)
{
	ObjectMap::iterator it = m_mapTreeItems.find( (wxUIntPtr)item );
	if(  it != m_mapTreeItems.end() )
	{
		return it->second;
	}
	else
		return wxTreeItemId(0L);
	
    /*m_fFound = false;

    wxTreeItemId start = GetRootItem();
    if( item && start.IsOk() )
    {
        return _FindTreeItem(item, start);
    }
    else
        return wxTreeItemId(0L);*/
}

// public virtual functions  /////////////////////////////////////////////////////////////////////

wxTreeItemId udProjectTree::CreateTreeItems(udProjectItem* item, wxTreeItemId parent)
{
    return wxTreeItemId(0);
}

void udProjectTree::UpdateItem(udProjectItem* item)
{
	wxTreeItemId treeId = FindTreeItem( item );
	if( treeId.IsOk() )
	{
		Collapse( treeId );
		
		// update tree item's label
		if( !item->IsKindOf( CLASSINFO(udRootItem) ) )
		{
			wxString sText = item->GetName();
			SetItemText( treeId, sText );
		}
		
		// re-create its child items
		DeleteChildren(treeId);

		SerializableList::compatibility_iterator node = item->GetFirstChildNode();
		while( node )
		{
			this->CreateTreeItems( (udProjectItem*)node->GetData(), treeId );
			node = node->GetNext();
		}
		
		Expand( treeId );
	}
}

void udProjectTree::RemoveItem(udProjectItem *item)
{
    wxTreeItemId treeItem = FindTreeItem(item);

    if( treeItem.IsOk() )
    {
        Delete(treeItem);
    }
}

// protected functions //////////////////////////////////////////////////////////////

void udProjectTree::OnContextMenu(wxTreeEvent& event)
{
    wxTreeItemId item = event.GetItem();

    if( item.IsOk() )
    {
        SelectItem(item);
        udTreeItem* itemData = (udTreeItem*)GetItemData(item);

        if(itemData)
        {
            // get associated project item
			udProjectItem* assocItem = itemData->GetProjectItem();
            if( assocItem )
            {
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, assocItem );
				
                assocItem->OnContextMenu(this, event.GetPoint());
            }

            wxGetApp().GetMainFrame()->UpdateWindowUI(wxUPDATE_UI_RECURSE);
        }
    }
}

void udProjectTree::OnActivation(wxTreeEvent& event)
{
    wxTreeItemId item = event.GetItem();

    if( item.IsOk() )
    {
        SelectItem(item);
        udTreeItem* itemData = (udTreeItem*)GetItemData(item);

        if(itemData)
        {
            // get associated project item
			udProjectItem* assocItem = itemData->GetProjectItem();
            if( assocItem )
            {		
                assocItem->OnActivation();
            }

            wxGetApp().GetMainFrame()->UpdateWindowUI(wxUPDATE_UI_RECURSE);
        }
    }
}

void udProjectTree::OnSelectionChanged(wxTreeEvent& event)
{
    if(!m_fSelectedOutside)
    {
        wxTreeItemId selItem = GetSelection();

        if( selItem.IsOk() )
        {
            udTreeItem* itemData = (udTreeItem*)GetItemData(selItem);
            if(itemData)
            {
				udProjectItem* assocItem = itemData->GetProjectItem();
                if( assocItem )
                {
					if( wxGetApp().GetMainFrame() )
					{
						UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, assocItem );
					}
					
                    assocItem->OnSelection();
                }
				
				//wxGetApp().GetMainFrame()->UpdateWindowUI(wxUPDATE_UI_RECURSE);
            }
        }
    }
    else
        m_fSelectedOutside = false;
}

void udProjectTree::OnBeginLabelEdit(wxTreeEvent &event)
{
	// do not edit element links manualy

    wxTreeItemId treeId = event.GetItem();
    if(treeId.IsOk())
    {
        udTreeItem* itemData = (udTreeItem*)GetItemData(treeId);
        if( itemData && itemData->GetProjectItem() && itemData->GetProjectItem()->IsKindOf(CLASSINFO(udElementLinkItem)) ) event.Veto();
		else
			event.Skip();
    }
}

void udProjectTree::OnEndLabelEdit(wxTreeEvent &event)
{
    if(!event.IsEditCancelled())
    {
        wxTreeItemId treeId = event.GetItem();
        if(treeId.IsOk())
        {
            udTreeItem* itemData = (udTreeItem*)GetItemData(treeId);
            if(itemData)
            {
				udProjectItem *pProjItem = itemData->GetProjectItem();
                if(pProjItem)
                {
					event.Veto();
					pProjItem->OnTreeTextChange(event.GetLabel());
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pProjItem );
                }
            }
        }
    }
}

void udProjectTree::OnKeyDown(wxTreeEvent& event)
{
    wxTreeItemId treeId = GetSelection();

    if(treeId.IsOk())
    {
        switch(event.GetKeyCode())
        {
            case WXK_F2:
				if( GetWindowStyle() & wxTR_EDIT_LABELS ) EditLabel(treeId);
                break;

            default:
                event.Skip();
        }
    }
}

void udProjectTree::OnBeginDrag(wxTreeEvent& event)
{
	// in this case event.GetItem() returns SOURCE tree item!!!
    wxTreeItemId treeId = event.GetItem();

    if( treeId.IsOk() )
    {		
        udTreeItem* itemData = (udTreeItem*)GetItemData( treeId );
		
        if( itemData && itemData->GetProjectItem() )
		{
			UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_SELECTED, wxID_ANY, itemData->GetProjectItem() );
			
			if( !itemData->GetProjectItem()->OnTreeItemBeginDrag( event.GetPoint() ) ) event.Allow();
		}
    }
}

void udProjectTree::OnEndDrag(wxTreeEvent& event)
{
	// in this case event.GetItem() returns DESTINATION tree item!!!
    wxTreeItemId treeId = event.GetItem();

    if( treeId.IsOk() )
    {
        udTreeItem* itemData = (udTreeItem*)GetItemData( treeId );
		udProjectItem *pProjItem = itemData->GetProjectItem();
		
        if( itemData && pProjItem)
		{
			pProjItem->OnTreeItemEndDrag( event.GetPoint() );
			
			//UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pProjItem );
		}
    }
}

void udProjectTree::OnProjectItemAdded(udProjectEvent& event)
{
	if( event.GetProjectItem() && event.GetParentItem() ) 
	{
		wxTreeItemId treeId = FindTreeItem( event.GetParentItem() );
		
		if( treeId.IsOk() )
		{
			if( this->CreateTreeItems( event.GetProjectItem(), treeId ).IsOk() )
			{
				EnsureVisible( treeId );
				Expand( treeId );
			}
		}
	}
}

void udProjectTree::OnProjectItemChanged(udProjectEvent& event)
{
	if( event.GetProjectItem() )
	{
		this->UpdateItem( event.GetProjectItem() );
	}
}

void udProjectTree::OnProjectItemRemoved(udProjectEvent& event)
{
	if( event.GetProjectItem() ) 
	{
		m_fSelectedOutside = true;
		this->RemoveItem( event.GetProjectItem() );
		m_fSelectedOutside = false;
	}
}

void udProjectTree::OnProjectItemSelected(udProjectEvent& event)
{
	if( wxGetApp().GetMainFrame()->GetProjectManager()->IsLinked() && event.GetProjectItem() )
	{
		wxTreeItemId treeId = FindTreeItem( event.GetProjectItem() );
		
		if( treeId.IsOk() )
		{
			m_fSelectedOutside = true; // needed for __WXMSW__ only ???
			SelectItem( treeId );
			EnsureVisible( treeId );
			//Expand( treeId );
			m_fSelectedOutside = false;
		}
		else
			this->UnselectAll();
	}
}


// private functions ////////////////////////////////////////////////////////////////

/*wxTreeItemId udProjectTree::_FindTreeItem(udProjectItem *item, wxTreeItemId treeId)
{
	wxTreeItemId ret, newret;

	if( !m_fFound && treeId.IsOk() )
	{
		udTreeItem *pData = (udTreeItem*)GetItemData(treeId);
		if( pData && ( pData->GetProjectItem() ==item ) )
		{
			m_fFound = true;
			ret =  treeId;
		}
		else
		{
			wxTreeItemId nChild = GetFirstChild(treeId, treeCookie);
			wxTreeItemId nSibling = GetNextSibling(treeId);
			if(nChild.IsOk())
			{
				newret = _FindTreeItem(item, nChild);
				if(newret)ret = newret;
			}
			if(nSibling.IsOk())
			{
				newret = _FindTreeItem(item, nSibling);
				if(newret)ret = newret;
			}
		}
		return ret;
	}
	else
		return wxTreeItemId(0L);
}*/
