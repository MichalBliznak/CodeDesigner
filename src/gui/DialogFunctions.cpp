#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/DialogFunctions.h"

int CompareTypeAndName(const void *elem1, const void *elem2)
{
	udProjectItem *pItem1 = *(udProjectItem**)elem1;
	udProjectItem *pItem2 = *(udProjectItem**)elem2;
	
	int res = wxString( pItem1->GetClassInfo()->GetClassName() ).Cmp( pItem2->GetClassInfo()->GetClassName() );
	if( res == 0) res = pItem1->GetName().Cmp( pItem2->GetName() );
	
	return res;
}

void udDialogFunctions::SelectAllItems(wxListCtrl* ctrl)
{
	for( int i = 0; i < ctrl->GetItemCount(); i++ )
	{
		ctrl->SetItemState( i, wxLIST_STATE_SELECTED , wxLIST_STATE_SELECTED );
	}
}

void udDialogFunctions::DeselectAllItems(wxListCtrl* ctrl)
{
	for( int i = 0; i < ctrl->GetItemCount(); i++ )
	{
		ctrl->SetItemState( i, 0 , wxLIST_STATE_SELECTED );
	}
}

void udDialogFunctions::GetSelectedItems(const wxListCtrl* ctrl, wxArrayInt& selection)
{
	selection.Clear();
	
	for( int i = 0; i < ctrl->GetItemCount(); i++ )
	{
		if( ctrl->GetItemState( i, wxLIST_STATE_SELECTED ) ) selection.Add( i );
	}
}

void udDialogFunctions::InsertProjectItems(wxListCtrl* ctrl, SerializableList& items, bool sort)
{
	// sort items' list if required
	if( sort ) items.Sort( CompareTypeAndName );
	
	// initialize list control
	ctrl->ClearAll();
	ctrl->SetImageList( udArt::GetImageList(), wxIMAGE_LIST_SMALL );
	
	ctrl->InsertColumn(0, wxT("Type") );
	ctrl->InsertColumn(1, wxT("Name") );

	// fill it with (sorted) items
	if( !items.IsEmpty() )
	{
		int nIndex = 0;
		udProjectItem *pItem;
		
		for( SerializableList::iterator it = items.begin(); it != items.end(); ++it )
		{
			pItem = (udProjectItem*) *it;
			if( pItem )
			{
				ctrl->InsertItem( nIndex,
								  udXS2PG::GetFriendlyName( wxT("classname"), pItem->GetClassInfo()->GetClassName() ),
								  udArt::GetImageIndex( pItem->GetClassInfo()->GetClassName() ) );
								
				ctrl->SetItem( nIndex++, 1, pItem->GetName() );
			}
		}
		
		ctrl->SetColumnWidth( 0, wxLIST_AUTOSIZE );
		ctrl->SetColumnWidth( 1, wxLIST_AUTOSIZE );
	}
	else
	{
		ctrl->SetColumnWidth( 0, wxLIST_AUTOSIZE_USEHEADER );
		ctrl->SetColumnWidth( 1, wxLIST_AUTOSIZE_USEHEADER );
	}
}


void udDialogFunctions::DeselectAllItems(wxListBox* ctrl)
{
	for( size_t i = 0; i < ctrl->GetCount(); i++ ) ctrl->Deselect(i);
}

void udDialogFunctions::SelectAllItems(wxListBox* ctrl)
{
	for( size_t i = 0; i < ctrl->GetCount(); i++ ) ctrl->Select(i);
}

