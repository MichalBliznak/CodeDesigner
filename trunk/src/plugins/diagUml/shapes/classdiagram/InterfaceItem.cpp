#include "InterfaceItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlInterfaceItem, wxSFOrthoLineShape);

umlInterfaceItem::umlInterfaceItem()
{
    Initialize();
}

umlInterfaceItem::umlInterfaceItem(const umlInterfaceItem &obj)
: wxSFOrthoLineShape(obj)
{
}

umlInterfaceItem::~umlInterfaceItem()
{
}

void umlInterfaceItem::Initialize()
{
    // initialize shape	
	SetTrgArrow(CLASSINFO(wxSFSolidArrow));

	AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = *wxBLACK_DASHED_PEN;
}
