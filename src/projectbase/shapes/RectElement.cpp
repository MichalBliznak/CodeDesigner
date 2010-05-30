#include "RectElement.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddRectElement, wxSFRectShape);

uddRectElement::uddRectElement()
{
    Initialize();
	DisableUselessProperties();
}

uddRectElement::uddRectElement(const uddRectElement &obj)
: wxSFRectShape(obj)
{
	m_pTitle = (uddLabelElement*)obj.m_pTitle->Clone();
	if( m_pTitle )
	{
		SF_ADD_COMPONENT( m_pTitle, wxT("title") );
	}

	DisableUselessProperties();
}

uddRectElement::~uddRectElement()
{
}

void uddRectElement::Initialize()
{
	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));
	
	AddStyle( sfsLOCK_CHILDREN );
	
	// initialize shape components
    m_pTitle = new uddLabelElement();
    if(m_pTitle)
    {
        m_pTitle->SetVAlign(wxSFShapeBase::valignTOP);
        m_pTitle->SetHAlign(wxSFShapeBase::halignCENTER);
        m_pTitle->SetVBorder(5);
		m_pTitle->SetHBorder(5);

        m_pTitle->SetStyle( sfsHOVERING | sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsSHOW_HANDLES );

        SF_ADD_COMPONENT( m_pTitle, wxT("title") );
    }

}

void uddRectElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("accepted_connections"), false);
    EnablePropertySerialization(wxT("accepted_children"), false);
    EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
    EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
    EnablePropertySerialization(wxT("style"), false);
	EnablePropertySerialization(wxT("hover_color"), false);
}

bool uddRectElement::OnKey(int key)
{
    switch(key)
    {
        case WXK_F2:
            if(m_pTitle->IsActive() && m_pTitle->IsVisible())
            {
                m_pTitle->EditLabel();
            }
            break;

        default:
            break;
    }

    return true;
}

