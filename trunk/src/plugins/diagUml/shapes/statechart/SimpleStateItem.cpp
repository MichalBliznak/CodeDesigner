#include "SimpleStateItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlSimpleStateItem, uddRoundRectElement);

umlSimpleStateItem::umlSimpleStateItem()
{
    Initialize();
}

umlSimpleStateItem::umlSimpleStateItem(const umlSimpleStateItem &obj)
: uddRoundRectElement(obj)
{
}

umlSimpleStateItem::~umlSimpleStateItem()
{
}

void umlSimpleStateItem::Initialize()
{
	SetFill(wxBrush(wxColour(254, 253, 211)));

    AcceptConnection(wxT("umlTransitionItem"));

    AddStyle(sfsSHOW_SHADOW);

    // initialize shape's components
    m_pTitle->SetText(wxT("State"));
}

void umlSimpleStateItem::DrawNormal(wxDC& dc)
{
    uddRoundRectElement::DrawNormal(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

	dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
	dc.SetPen(wxNullPen);
}

void umlSimpleStateItem::DrawHover(wxDC& dc)
{
    uddRoundRectElement::DrawHover(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
    dc.SetPen(wxNullPen);
}

void umlSimpleStateItem::DrawHighlighted(wxDC& dc)
{
    uddRoundRectElement::DrawHighlighted(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
    dc.SetPen(wxNullPen);
}

