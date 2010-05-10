#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "ExitItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlExitItem, uddCircleElement);

umlExitItem::umlExitItem()
{
    Initialize();
}

umlExitItem::umlExitItem(const umlExitItem &obj)
: uddCircleElement(obj)
{
}

umlExitItem::~umlExitItem()
{
}

void umlExitItem::Initialize()
{
    // set basic properties
    AcceptConnection(wxT("umlTransitionItem"));
	
	ClearAcceptedTrgNeighbours();
	AcceptTrgNeighbour(wxT("umlNoteItem"));

    m_pTitle->SetText(wxT("Exit"));
    m_pTitle->SetRelativePosition( 0, 25 );
}

void umlExitItem::DrawNormal(wxDC& dc)
{
    uddCircleElement::DrawNormal(dc);

	dc.SetPen(*wxBLACK_PEN);
    DrawCross(dc);
	dc.SetPen(wxNullPen);
}

void umlExitItem::DrawHover(wxDC& dc)
{
    uddCircleElement::DrawHover(dc);

    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    DrawCross(dc);
    dc.SetPen(wxNullPen);
}

void umlExitItem::DrawCross(wxDC& dc)
{
    wxRealPoint center = GetCenter();

    dc.DrawLine(center.x + 7.071, center.y - 7.071, center.x - 7.071, center.y + 7.071);
    dc.DrawLine(center.x - 7.071, center.y - 7.071, center.x + 7.071, center.y + 7.071);
}


