#include "ForkJoinVItem.h"

// define star shape
const wxRealPoint vforkshape[12]={wxRealPoint(0, 0), wxRealPoint(10, 0), wxRealPoint(10, 20),
                            wxRealPoint(10, 40), wxRealPoint(10, 60), wxRealPoint(10, 80),
                            wxRealPoint(10, 100), wxRealPoint(0, 100), wxRealPoint(0, 80),
                            wxRealPoint(0, 60), wxRealPoint(0, 40), wxRealPoint(0, 20)};

XS_IMPLEMENT_CLONABLE_CLASS(umlForkJoinVItem, uddPolygonElement);

umlForkJoinVItem::umlForkJoinVItem()
{
    EnablePropertySerialization(wxT("vertices"), false);
    SetVertices(12, vforkshape);

    Initialize();
}

umlForkJoinVItem::umlForkJoinVItem(const umlForkJoinVItem &obj)
: uddPolygonElement(obj)
{
    EnablePropertySerialization(wxT("vertices"), false);
}

umlForkJoinVItem::~umlForkJoinVItem()
{
}

void umlForkJoinVItem::Initialize()
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

void umlForkJoinVItem::CreateHandles()
{
    AddHandle(wxSFShapeHandle::hndLEFTTOP);
}


