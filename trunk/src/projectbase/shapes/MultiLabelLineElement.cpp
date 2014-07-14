#include "MultiLabelLineElement.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddMultiLabelLineElement, wxSFOrthoLineShape);

uddMultiLabelLineElement::uddMultiLabelLineElement()
{
	m_nCounter = 0;
	m_pLabels = NULL;
	
	m_nMaxLabelCount = 0;
	
	DisableUselessProperties();
}

uddMultiLabelLineElement::uddMultiLabelLineElement(const uddMultiLabelLineElement &obj)
: wxSFOrthoLineShape(obj)
{
	m_nCounter = 0;
	m_pLabels = NULL;
	
	SetMaxLabelCount( obj.GetMaxLabelCount() );

	SerializableList::compatibility_iterator node = obj.GetFirstChildNode();
	while( node )
	{
		*(m_pLabels + m_nCounter) = wxDynamicCast( node->GetData()->Clone(), uddLabelElement );
		if( *(m_pLabels + m_nCounter) )
		{
			XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(*(m_pLabels + m_nCounter), wxString::Format(wxT("label%d"), m_nCounter));
			AddChild(*(m_pLabels + m_nCounter++));
		}
		
		node = node->GetNext();
	}

	DisableUselessProperties();
}

uddMultiLabelLineElement::~uddMultiLabelLineElement()
{
	delete [] m_pLabels;
}

void uddMultiLabelLineElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("accepted_connections"), false);
    EnablePropertySerialization(wxT("accepted_children"), false);
    EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
    EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
    EnablePropertySerialization(wxT("style"), false);
	EnablePropertySerialization(wxT("hover_color"), false);
}

bool uddMultiLabelLineElement::OnKey(int key)
{
    switch(key)
    {
        case WXK_F2:
			{
				uddLabelElement *pLabel;
				
				ShapeList lstLabels;
				GetChildShapes(CLASSINFO(uddLabelElement), lstLabels);
				
				ShapeList::compatibility_iterator node = lstLabels.GetFirst();
				while( node )
				{
					pLabel = (uddLabelElement*) node->GetData();
					
					if( pLabel->IsActive() && pLabel->IsVisible() && pLabel->IsSelected() )
					{
						pLabel->EditLabel();
						break;
					}
					
					node = node->GetNext();
				}
			}
            break;

        default:
            break;
    }

    return true;
}


uddLabelElement* uddMultiLabelLineElement::CreateLabel(udLABEL::TYPE type)
{
	wxASSERT( m_nMaxLabelCount );
	
	if( m_nCounter < m_nMaxLabelCount )
	{
		*(m_pLabels + m_nCounter) = new uddLabelElement();
		if( *(m_pLabels + m_nCounter) )
		{
			(*(m_pLabels + m_nCounter))->SetLabelType( type );
			(*(m_pLabels + m_nCounter))->SetText(wxT("<< >>"));
			
			(*(m_pLabels + m_nCounter))->EnableSerialization( false );
			
			XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(*(m_pLabels + m_nCounter), wxString::Format(wxT("label%d"), m_nCounter));

			AddChild(*(m_pLabels + m_nCounter));

			return *(m_pLabels + m_nCounter++);
		}
	}

	return NULL;
}

uddLabelElement* uddMultiLabelLineElement::GetLabel(udLABEL::TYPE type)
{
	uddLabelElement *pLabel;
	
	ShapeList lstLabels;
	GetChildShapes(CLASSINFO(uddLabelElement), lstLabels);
	
	ShapeList::compatibility_iterator node = lstLabels.GetFirst();
	while( node )
	{
		pLabel = (uddLabelElement*) node->GetData();
		if( pLabel->GetLabelType() == type ) return pLabel;
		
		node = node->GetNext();
	}
	
	return NULL;
}

void uddMultiLabelLineElement::SetMaxLabelCount(int count)
{
	wxASSERT( count > 0 );
	
	if( count > 0 )
	{
		m_nMaxLabelCount = count;
		
		delete [] m_pLabels;
		
		m_pLabels = new uddLabelElement*[m_nMaxLabelCount];
		memset(m_pLabels, 0, m_nMaxLabelCount * sizeof(uddLabelElement*));
	}
}
