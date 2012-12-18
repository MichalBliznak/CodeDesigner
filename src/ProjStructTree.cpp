#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "ProjStructTree.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "Art.h"

#include <wx/wupdlock.h>

// constructor and destructor ///////////////////////////////////////////////////////

udProjStructTree::udProjStructTree(wxWindow *parent, wxWindowID id)
: udProjectTree( parent, id, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS | wxTR_DEFAULT_STYLE | wxNO_BORDER )
{

}

udProjStructTree::~udProjStructTree()
{
}

// public functions ////////////////////////////////////////////////////////////////

void udProjStructTree::CreateDiagramItems(udProjectItem* item, wxTreeItemId parent)
{
    udDiagramItem* pDiagramItem = wxDynamicCast(item, udDiagramItem);
    if(pDiagramItem)
    {
		// insert diagram-specific items if contained
		InsertPaletteItems(pDiagramItem->GetDiagramType(), pDiagramItem, parent);
        // insert common items if contained
        InsertPaletteItems(udnCOMMON_ITEMS, pDiagramItem, parent);
    }
}

void udProjStructTree::CreateElementItem(wxSFShapeBase* item)
{
    wxASSERT(item);

	wxTreeItemId treeItem;

	// find suitable parent tree node
    udDiagramManager *pManager = wxDynamicCast( item->GetParentManager(), udDiagramManager );
    if( pManager)
    {
        if( pManager->GetParentProjItem()->GetSubdiagramElement() )
        {
            treeItem = FindTreeItem( (pManager->GetParentProjItem()->GetSubdiagramElement() ) );
        }
        else
            treeItem = FindTreeItem( pManager->GetParentProjItem() );
    }

	// create new tree icon
    if(treeItem.IsOk())
    {
		wxString sName;
		
		#ifdef __WXMSW__
		wxWindowUpdateLocker noUpdate( this );
		#endif

        udProjectItem *pUserData = (udProjectItem*)item->GetUserData();

        sName = item->GetClassInfo()->GetClassName();
        int index = udArt::GetImageIndex(sName);

        if( pUserData && (index > -1) )
        {
			m_fSelectedOutside = true;
            wxTreeItemId newItem = CreateItem( treeItem, pUserData, index );

			if(newItem.IsOk()) EnsureVisible(newItem);
        }
    }
}

void udProjStructTree::CreateElementsItems(const ShapeList& list)
{
	ShapeList::compatibility_iterator node = list.GetFirst();
	while(node)
	{
		CreateElementItem(node->GetData());
		node = node->GetNext();
	}
}

void udProjStructTree::UpdateElementItem(wxSFShapeBase *item)
{
    wxASSERT(item);

    if(item)
    {
		wxTreeItemId treeId = FindTreeItem((udProjectItem*)item->GetUserData());
        if(treeId.IsOk())
        {
            SetItemText(treeId, udLABEL::GetContent(item, udLABEL::ltTITLE));
        }
    }
}

void udProjStructTree::UpdateDiagramItem(udDiagramItem *item)
{
	wxASSERT(item);

	if( item )
	{
		wxTreeItemId diagTreeItem;

		// find suitable parent tree node
		if( item->GetSubdiagramElement() )
		{
		    diagTreeItem = FindTreeItem( item->GetSubdiagramElement() );
		}
		else
			diagTreeItem = FindTreeItem(item);

		if( diagTreeItem.IsOk() )
		{
			DeleteChildren(diagTreeItem);
			CreateDiagramItems(item, diagTreeItem);

			ExpandAllChildren(diagTreeItem);
		}
	}
}

// protected functions ////////////////////////////////////////////////////////////////

void udProjStructTree::InsertPaletteItems(const wxString& fromPalette, udDiagramItem* item, wxTreeItemId parent)
{
	int index;
	wxString sClassName;
    ShapeList lstDiagItems;
    wxTreeItemId newItem;
    wxSFShapeBase *pItem = NULL;
    udProjectItem *pUserData = NULL;

    // create diamgram-specific item icons
	PaletteArray *palette = m_mapElementPalettes[fromPalette];
	if( !palette ) return;

	for(size_t i = 0; i < palette->GetCount(); i++)
    {
        // get diagram items of given type
        lstDiagItems.Clear();
		sClassName = palette->Item(i).m_sClassName;

		if( sClassName != wxEmptyString )
		{
			item->GetDiagramManager().GetShapes(wxClassInfo::FindClass(sClassName), lstDiagItems);
		}

		index = udArt::GetImageIndex(sClassName);

        wxShapeListNode* node = lstDiagItems.GetFirst();
        while(node)
        {
            pItem = node->GetData();
            pUserData = (udProjectItem*)pItem->GetUserData();

			// we must test exact class name
            if(pUserData && (pItem->GetClassInfo()->GetClassName() == sClassName) )
            {
				newItem = CreateItem( parent, pUserData, index );

				if( newItem.IsOk() )
				{
					if( pUserData->IsKindOf( CLASSINFO(udSubDiagramElementItem) ) )
					{
						udSubDiagramElementItem *pSubElemenet = (udSubDiagramElementItem*)pUserData;
						CreateDiagramItems( pSubElemenet->GetSubDiagram(), newItem );
					}
					else
					{
						SerializableList::compatibility_iterator cnode = pUserData->GetFirstChildNode();
						while( cnode )
						{
							CreateTreeItems( (udProjectItem*)cnode->GetData(), newItem );
							cnode = cnode->GetNext();
						}
					}
                }
            }

            node = node->GetNext();
        }
    }
}

// protected virtual functions ////////////////////////////////////////////////////////////////

wxTreeItemId udProjStructTree::CreateTreeItems(udProjectItem* item, wxTreeItemId parent)
{
    wxTreeItemId newItem;

    if( item )
    {
		#ifdef __WXMSW__
		wxWindowUpdateLocker noUpdate( this );
		#endif

		int nImageIndex = udArt::GetImageIndex( item->GetClassInfo()->GetClassName() );
		
        // create tree item relevat to project items
        if( item->IsKindOf(CLASSINFO(udRootItem)) )
        {
            newItem = AddRoot(item->GetName(), nImageIndex, nImageIndex, new udTreeItem(this, item) );
			EnsureVisible( newItem );
			Expand( newItem );
			m_mapTreeItems[ (wxUIntPtr)item ] = newItem;
        }
        else if( item->IsKindOf(CLASSINFO(udPackageItem)) )
        {
			newItem = CreateItem( parent, item, nImageIndex );
        }
        else if( item->IsKindOf(CLASSINFO(udDiagramItem)) )
        {
			newItem = CreateItem( parent, item, nImageIndex );
			EnsureVisible(newItem);
			
			CreateDiagramItems(item, newItem);
        }
        else if( item->IsKindOf(CLASSINFO(udCodeLinkItem)) || 
				 item->IsKindOf(CLASSINFO(udCodeItem)) )
		{
			udTreeItem *parentItem = (udTreeItem*) GetItemData( parent );
			if( parentItem && parentItem->GetProjectItem()->IsKindOf(CLASSINFO(udDiagElementItem) ) ) newItem = CreateItem( parent, item, nImageIndex );
		}

        if(newItem.IsOk())
        {
            // EnsureVisible(newItem);
        
			// create item's children as well
			SerializableList::compatibility_iterator node = item->GetFirstChildNode();
			while(node)
			{
				CreateTreeItems((udProjectItem*)node->GetData(), newItem);
				node = node->GetNext();
			}
		}
    }

    return newItem;
}

void udProjStructTree::UpdateItem(udProjectItem* item)
{
	wxTreeItemId treeId = FindTreeItem( item );
	if( treeId.IsOk() )
	{
		// update tree item's label
		wxString sText = item->GetName();
		SetItemText( treeId, sText );
		
		// re-create its child items
		DeleteChildren(treeId);
		
		if( item->IsKindOf( CLASSINFO(udDiagramItem) ) )
		{			
			this->CreateDiagramItems( item, treeId );
		}
		else if( item->IsKindOf( CLASSINFO(udSubDiagramElementItem) ) )
		{
			udSubDiagramElementItem *pSubElemenet = (udSubDiagramElementItem*)item;
			CreateDiagramItems( pSubElemenet->GetSubDiagram(), treeId );
		}
		else
		{
			SerializableList::compatibility_iterator node = item->GetFirstChildNode();
			while( node )
			{
				this->CreateTreeItems( (udProjectItem*)node->GetData(), treeId );
				node = node->GetNext();
			}
		}
	}
}
