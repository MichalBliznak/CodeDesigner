#include "InheritanceItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlInheritanceItem, wxSFOrthoLineShape);

umlInheritanceItem::umlInheritanceItem()
{
    Initialize();
}

umlInheritanceItem::umlInheritanceItem(const umlInheritanceItem &obj)
: wxSFOrthoLineShape(obj)
{
}

umlInheritanceItem::~umlInheritanceItem()
{
}

void umlInheritanceItem::Initialize()
{
    // initialize shape	
	SetTrgArrow(CLASSINFO(wxSFSolidArrow));

	AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = *wxBLACK_PEN;
}
