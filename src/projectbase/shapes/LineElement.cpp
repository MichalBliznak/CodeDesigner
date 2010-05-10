#include "LineElement.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddLineElement, wxSFCurveShape);

uddLineElement::uddLineElement()
{
    Initiliaze();
	DisableUselessProperties();
}

uddLineElement::uddLineElement(const uddLineElement &obj)
: wxSFCurveShape(obj)
{
	m_pLabel = (uddLabelElement*)obj.m_pLabel->Clone();
	if( m_pLabel )
	{
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pLabel, wxT("label"));
		AddChild(m_pLabel);
	}

	DisableUselessProperties();
}

uddLineElement::~uddLineElement()
{
}

void uddLineElement::Initiliaze()
{
    // initialize shape components
	m_pLabel = new uddLabelElement();
    if(m_pLabel)
    {
        m_pLabel->SetText(wxT("<< >>"));

        m_pLabel->SetLabelType( udLABEL::ltGUARD_CONTENT );

        m_pLabel->EnableSerialization(false);
        XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pLabel, wxT("label"));

        AddChild(m_pLabel);
    }
}

void uddLineElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("accepted_connections"), false);
    EnablePropertySerialization(wxT("accepted_children"), false);
    EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
    EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
    EnablePropertySerialization(wxT("style"), false);
	EnablePropertySerialization(wxT("hover_color"), false);
}

bool uddLineElement::OnKey(int key)
{
    switch(key)
    {
        case WXK_F2:
            if(m_pLabel->IsActive() && m_pLabel->IsVisible())
            {
                m_pLabel->EditLabel();
            }
            break;

        default:
            break;
    }

    return true;
}


