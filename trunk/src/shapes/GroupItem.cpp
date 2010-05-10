#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "shapes/GroupItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddGroupItem, uddRectElement);

uddGroupItem::uddGroupItem()
{
	Initialize();
}

uddGroupItem::uddGroupItem(const uddGroupItem& obj) : uddRectElement(obj)
{
}

uddGroupItem::~uddGroupItem()
{
}

void uddGroupItem::Initialize()
{
	SetBorder( wxPen( *wxBLACK, 1, wxDOT) );
	SetFill( wxBrush( wxColour(200, 255, 200) ) );
	
	AddStyle( sfsSHOW_SHADOW );
	
	ClearAcceptedChilds();
	ClearAcceptedSrcNeighbours();
	ClearAcceptedTrgNeighbours();
	
	AcceptChild(wxT("All"));
    AcceptSrcNeighbour(wxT("uddNoteItem"));
    AcceptTrgNeighbour(wxT("uddNoteItem"));
}
