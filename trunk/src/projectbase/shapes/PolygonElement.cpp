#include "PolygonElement.h"
#include "../Ids.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddPolygonElement, wxSFPolygonShape);

uddPolygonElement::uddPolygonElement()
{
    Initialize();
	DisableUselessProperties();
}

uddPolygonElement::uddPolygonElement(const uddPolygonElement &obj)
: wxSFPolygonShape(obj)
{
	m_pTitle = (uddLabelElement*)obj.m_pTitle->Clone();
	if( m_pTitle )
	{
		SF_ADD_COMPONENT( m_pTitle, wxT("title") );
	}

	DisableUselessProperties();
}

uddPolygonElement::~uddPolygonElement()
{
}

void uddPolygonElement::Initialize()
{
    m_nRectSize = wxRealPoint(20, 20);
	
	AddStyle( sfsLOCK_CHILDREN );

    // initialize shape components
    m_pTitle = new uddLabelElement();
    if(m_pTitle)
    {
        SF_ADD_COMPONENT( m_pTitle, wxT("title") );
    }
}

void uddPolygonElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("accepted_connections"), false);
    EnablePropertySerialization(wxT("accepted_children"), false);
    EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
    EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
    EnablePropertySerialization(wxT("style"), false);
	EnablePropertySerialization(wxT("hover_color"), false);
}

bool uddPolygonElement::OnKey(int key)
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


