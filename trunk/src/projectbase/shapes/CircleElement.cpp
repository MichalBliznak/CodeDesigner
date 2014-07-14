#include "CircleElement.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddCircleElement, wxSFCircleShape);

uddCircleElement::uddCircleElement()
{
    Initiliaze();
	DisableUselessProperties();
}

uddCircleElement::uddCircleElement(const uddCircleElement &obj)
: wxSFCircleShape(obj)
{
	m_pTitle = (uddLabelElement*)obj.m_pTitle->Clone();
	if( m_pTitle )
	{
		SF_ADD_COMPONENT( m_pTitle, wxT("title") );
	}

	DisableUselessProperties();
}

uddCircleElement::~uddCircleElement()
{
}

void uddCircleElement::Initiliaze()
{
    // set basic properties
    m_nRectSize = wxRealPoint(20, 20);
    RemoveStyle(sfsSIZE_CHANGE);
	
	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

    // initialize shape components
    m_pTitle = new uddLabelElement();
    if(m_pTitle)
    {
        SF_ADD_COMPONENT( m_pTitle, wxT("title") );
    }
}

void uddCircleElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("accepted_connections"), false);
    EnablePropertySerialization(wxT("accepted_children"), false);
    EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
    EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
    EnablePropertySerialization(wxT("style"), false);
	EnablePropertySerialization(wxT("hover_color"), false);
}

void uddCircleElement::CreateHandles()
{
	AddHandle(wxSFShapeHandle::hndLEFTTOP);
}

bool uddCircleElement::OnKey(int key)
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


