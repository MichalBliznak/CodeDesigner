#include "DecisionItem.h"

// diamond shape
const wxRealPoint diamond[4]={wxRealPoint(0,25), wxRealPoint(50,0), wxRealPoint(100, 25), wxRealPoint(50, 50)};

XS_IMPLEMENT_CLONABLE_CLASS(umlDecisionItem, uddPolygonElement);

umlDecisionItem::umlDecisionItem()
{
	EnablePropertySerialization(wxT("vertices"), false);
	SetVertices(4, diamond);

    Initialize();
}

umlDecisionItem::umlDecisionItem(const umlDecisionItem  &obj)
: uddPolygonElement(obj)
{
}

umlDecisionItem::~umlDecisionItem()
{
}

void umlDecisionItem::Initialize()
{
    // set basic properties
    m_nRectSize = wxRealPoint(40, 40);
    FitVerticesToBoundingBox();

    AcceptConnection(wxT("umlTransitionItem"));
	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

    // initialize shape components
    m_pTitle->SetRelativePosition(0, 45);
    m_pTitle->SetText(wxT("Decision"));
}


