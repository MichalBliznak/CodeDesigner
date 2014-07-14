#include "SubStateItem.h"
#include "../../res/SubSign.xpm"

XS_IMPLEMENT_CLONABLE_CLASS(umlSubStateItem, uddRoundRectElement);

umlSubStateItem::umlSubStateItem()
{
    Initialize();
	DisableUselessProperties();
}

umlSubStateItem::umlSubStateItem(const umlSubStateItem &obj)
: uddRoundRectElement(obj)
{
	m_pSign = (wxSFBitmapShape*)obj.m_pSign->Clone();
	if( m_pSign )
	{
		SF_ADD_COMPONENT( m_pSign, wxT("sign") );
	}

	DisableUselessProperties();
}

umlSubStateItem::~umlSubStateItem()
{
}

void umlSubStateItem::Initialize()
{
	SetFill(wxBrush(wxColour(254, 253, 211)));
	
	//AcceptChild(wxT("umlEntryItem"));
    //AcceptChild(wxT("umlExitItem"));

	AcceptConnection(wxT("umlTransitionItem"));

    AddStyle(sfsSHOW_SHADOW);

    // initialize shape components
    m_pTitle->SetText(wxT("SubState"));

    m_pSign = new wxSFBitmapShape();
    if(m_pSign)
    {
        m_pSign->Activate(false);

        m_pSign->SetRelativePosition(0, 0);
        m_pSign->CreateFromXPM(SubSign_xpm);

        m_pSign->SetVAlign(wxSFShapeBase::valignBOTTOM);
        m_pSign->SetHAlign(wxSFShapeBase::halignRIGHT);
        m_pSign->SetVBorder(15);
        m_pSign->SetHBorder(15);

        m_pSign->SetStyle( sfsALWAYS_INSIDE );
        m_pSign->EnableScale(false);

        SF_ADD_COMPONENT( m_pSign, wxT("sign") );
    }
}

void umlSubStateItem::DisableUselessProperties()
{
    if(m_pSign)
    {
        // reduce project file size
        m_pSign->EnablePropertySerialization(wxT("halign"), false);
        m_pSign->EnablePropertySerialization(wxT("valign"), false);
        m_pSign->EnablePropertySerialization(wxT("hborder"), false);
        m_pSign->EnablePropertySerialization(wxT("vborder"), false);
        m_pSign->EnablePropertySerialization(wxT("style"), false);
        m_pSign->EnablePropertySerialization(wxT("scale_image"), false);
    }
}

void umlSubStateItem::DrawNormal(wxDC& dc)
{
    uddRoundRectElement::DrawNormal(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

	dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
	dc.SetPen(wxNullPen);
}

void umlSubStateItem::DrawHover(wxDC& dc)
{
    uddRoundRectElement::DrawHover(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
    dc.SetPen(wxNullPen);
}

void umlSubStateItem::DrawHighlighted(wxDC& dc)
{
    uddRoundRectElement::DrawHighlighted(dc);

    // draw title line
    wxRect shapeBB = GetBoundingBox();

    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + m_nRadius,
                shapeBB.GetRight(), shapeBB.GetTop() + m_nRadius);
    dc.SetPen(wxNullPen);
}


