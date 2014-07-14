#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "shapes/NoteItem.h"
#include "Ids.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddNoteItem, uddPolygonElement);

// define star shape
const wxRealPoint note[5]={wxRealPoint(0, 0), wxRealPoint(90, 0),
                            wxRealPoint(100, 10), wxRealPoint(100, 50),
                            wxRealPoint(0, 50)};


uddNoteItem::uddNoteItem()
{
    Initialize();

    EnablePropertySerialization(wxT("vertices"), false);
    SetVertices(5, note);
}

uddNoteItem::uddNoteItem(const uddNoteItem &obj)
: uddPolygonElement(obj)
{
	m_pContent = (uddLabelElement*)obj.m_pContent->Clone();
	if( m_pContent )
	{
		SF_ADD_COMPONENT( m_pContent, wxT("content") );
	}
}

uddNoteItem::~uddNoteItem()
{
}

void uddNoteItem::Initialize()
{
    // set basic properties
    RemoveStyle(sfsPARENT_CHANGE);
	SetConnectToVertex(false);

    AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

    AddStyle(sfsSHOW_SHADOW);

    // initialize shape components
    m_pTitle->SetText(wxT("Note"));
    m_pTitle->SetRelativePosition(0, 0);
	//m_pTitle->GetFont().SetPointSize(7);
	m_pTitle->GetFont().SetWeight(wxFONTWEIGHT_BOLD);

    m_pTitle->SetVAlign(wxSFShapeBase::valignTOP);
    m_pTitle->SetHAlign(wxSFShapeBase::halignLEFT);
    m_pTitle->SetVBorder(5);
    m_pTitle->SetHBorder(5);

    m_pTitle->SetStyle( sfsHOVERING | sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsSHOW_HANDLES );

	m_pContent = new uddLabelElement();
	if( m_pContent )
	{
	    m_pContent->SetLabelType( udLABEL::ltNOTE_CONTENT );
		m_pContent->SetText(wxT("Content:\nInsert description here..."));
		m_pContent->SetEditType( wxSFEditTextShape::editDIALOG );

		m_pContent->SetRelativePosition(0, 23);

		m_pContent->SetHAlign(wxSFShapeBase::halignLEFT);
		m_pContent->SetVBorder(5);
		m_pContent->SetHBorder(5);

		m_pContent->ForceMultiline(true);
		m_pContent->SetStyle( sfsHOVERING | sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsSHOW_HANDLES);

        SF_ADD_COMPONENT( m_pContent, wxT("content") );
	}
}

bool uddNoteItem::OnKey(int key)
{
    switch(key)
    {
        case WXK_F2:
            if(m_pContent->IsActive() && m_pContent->IsVisible())
            {
                m_pContent->EditLabel();
            }
            break;

        default:
            break;
    }

    return true;
}

void uddNoteItem::DrawNormal(wxDC& dc)
{
    wxRect bb = UpdateRightCorner();
    // draw standard rectangle
    wxSFPolygonShape::DrawNormal(dc);
    // draw right corner
	dc.SetPen(*wxBLACK_PEN);
    DrawRightCorner(bb, dc);
	dc.SetPen(wxNullPen);
}

void uddNoteItem::DrawHover(wxDC& dc)
{
    wxRect bb = UpdateRightCorner();
    // draw standard rectangle
    wxSFPolygonShape::DrawHover(dc);
    // draw right corner
    dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
    DrawRightCorner(bb, dc);
    dc.SetPen(wxNullPen);
}

void uddNoteItem::DrawRightCorner(const wxRect& bb, wxDC& dc)
{
    dc.DrawLine(bb.GetRight()-9, bb.GetTop(), bb.GetRight()-9, bb.GetTop()+10);
    dc.DrawLine(bb.GetRight()-9, bb.GetTop()+10, bb.GetRight()+1, bb.GetTop()+10);
}

wxRect uddNoteItem::UpdateRightCorner()
{
    wxRect bb = GetBoundingBox();

    m_arrVertices[1].x = bb.GetWidth()-10;
    m_arrVertices[2].y = 10;

    return bb;
}


