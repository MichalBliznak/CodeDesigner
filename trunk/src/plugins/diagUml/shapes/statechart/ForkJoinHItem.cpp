#include "ForkJoinHItem.h"

// define star shape
const wxRealPoint hforkshape[12]={wxRealPoint(0, 0), wxRealPoint(20, 0), wxRealPoint(40, 0),
                            wxRealPoint(60, 0), wxRealPoint(80, 0), wxRealPoint(100, 0),
                            wxRealPoint(100, 10), wxRealPoint(80, 10), wxRealPoint(60, 10),
                            wxRealPoint(40, 10), wxRealPoint(20, 10), wxRealPoint(0, 10)};


XS_IMPLEMENT_CLONABLE_CLASS(umlForkJoinHItem, uddPolygonElement);

umlForkJoinHItem::umlForkJoinHItem()
{
    EnablePropertySerialization(wxT("vertices"), false);
    SetVertices(12, hforkshape);

    Initialize();
}

umlForkJoinHItem::umlForkJoinHItem(const umlForkJoinHItem &obj)
: uddPolygonElement(obj)
{
    EnablePropertySerialization(wxT("vertices"), false);
}

umlForkJoinHItem::~umlForkJoinHItem()
{
}

void umlForkJoinHItem::Initialize()
{
    // set basic properties
    m_Fill = *wxBLACK_BRUSH;

    AcceptConnection(wxT("umlTransitionItem"));
	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

    RemoveStyle(sfsSIZE_CHANGE);

    // hide title control
    m_pTitle->Activate(false);
    m_pTitle->Show(false);
}

void umlForkJoinHItem::CreateHandles()
{
    AddHandle(wxSFShapeHandle::hndLEFTTOP);
}


