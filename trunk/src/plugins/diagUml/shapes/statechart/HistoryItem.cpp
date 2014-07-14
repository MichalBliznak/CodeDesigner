#include "HistoryItem.h"

using namespace wxSFCommonFcn;

XS_IMPLEMENT_CLONABLE_CLASS(umlHistoryItem, uddCircleElement);

umlHistoryItem::umlHistoryItem()
{
    Initiliaze();
}

umlHistoryItem::umlHistoryItem(const umlHistoryItem &obj)
: uddCircleElement(obj)
{
}

umlHistoryItem::~umlHistoryItem()
{
}

void umlHistoryItem::Initiliaze()
{
    // set basic properties

    AcceptConnection(wxT("umlTransitionItem"));

    m_pTitle->SetText(wxT("History"));
    m_pTitle->SetRelativePosition( 0, 25 );
}

void umlHistoryItem::DrawNormal(wxDC& dc)
{
    uddCircleElement::DrawNormal(dc);

    // draw "H" sign
    DrawSign(dc);
}

void umlHistoryItem::DrawHover(wxDC& dc)
{
    uddCircleElement::DrawHover(dc);

    // draw "H" sign
    DrawSign(dc);
}

void umlHistoryItem::DrawSign(wxDC& dc)
{
    wxFont font = *wxSWISS_FONT;
    font.SetPointSize(8);

    dc.SetFont(font);
    dc.DrawText(wxT("H"), Conv2Point(GetAbsolutePosition() + wxRealPoint(6, 4)));
    dc.SetFont(wxNullFont);
}



