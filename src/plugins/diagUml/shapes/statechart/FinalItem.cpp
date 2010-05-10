#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "FinalItem.h"

using namespace wxSFCommonFcn;

XS_IMPLEMENT_CLONABLE_CLASS(umlFinalItem, uddCircleElement);

umlFinalItem::umlFinalItem()
{
    Initialize();
}

umlFinalItem::umlFinalItem(const umlFinalItem &obj)
: uddCircleElement(obj)
{
}


umlFinalItem::~umlFinalItem()
{
}

void umlFinalItem::Initialize()
{
    // set basic properties
    AcceptConnection(wxT("umlTransitionItem"));
	
	ClearAcceptedTrgNeighbours();
	AcceptTrgNeighbour(wxT("umlNoteItem"));

    m_pTitle->SetText(wxT("Final"));
    m_pTitle->SetRelativePosition( 0, 25 );
}

void umlFinalItem::DrawNormal(wxDC& dc)
{
    uddCircleElement::DrawNormal(dc);

    // draw inner circle
	dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(Conv2Point(GetCenter()), 5);
    dc.SetBrush(wxNullBrush);
	dc.SetPen(wxNullPen);
}

void umlFinalItem::DrawHover(wxDC& dc)
{
    uddCircleElement::DrawHover(dc);

    // draw inner circle
    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(Conv2Point(GetCenter()), 5);
    dc.SetBrush(wxNullBrush);
    dc.SetPen(wxNullPen);
}
