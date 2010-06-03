#include "ClassTemplItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlClassTemplateItem, umlClassItem);

umlClassTemplateItem::umlClassTemplateItem()
{
    Initialize();
}

umlClassTemplateItem::umlClassTemplateItem(const umlClassTemplateItem &obj)
: umlClassItem(obj)
{	
	m_pTemplate = (uddLabelElement*)obj.m_pTemplate->Clone();
	if( m_pTemplate )
	{
		SF_ADD_COMPONENT( m_pTemplate, wxT("template") );
	}
}

umlClassTemplateItem::~umlClassTemplateItem()
{
}

void umlClassTemplateItem::Initialize()
{
	ClearAcceptedChilds();
	ClearAcceptedConnections();
	ClearAcceptedSrcNeighbours();
	ClearAcceptedTrgNeighbours();
	
	AcceptChild(wxT("uddDnDElement"));
	
	AcceptConnection(wxT("umlTemplateBindItem"));
	AcceptConnection(wxT("uddNoteConnItem"));
	
	AcceptSrcNeighbour(wxT("umlClassItem"));
	AcceptTrgNeighbour(wxT("uddNoteItem"));
    AcceptSrcNeighbour(wxT("uddNoteItem"));
	
	// set accepted project items (USED INTERNALLY)
	AcceptChild(wxT("udGenericVariableItem"));
	AcceptChild(wxT("udGenericFunctionItem"));
	AcceptChild(wxT("udMemberDataItem"));
	AcceptChild(wxT("udMemberFunctionItem"));
	AcceptChild(wxT("udSStateChartDiagramItem"));
	AcceptChild(wxT("udHStateChartDiagramItem"));
	AcceptChild(wxT("udConstructorFunctionItem"));
	AcceptChild(wxT("udDestructorFunctionItem"));
	
	m_pTemplate = new uddLabelElement();
	if( m_pTemplate )
	{
		m_pTemplate->SetBorder( wxPen( *wxBLACK, 1, wxDOT ) );
		m_pTemplate->SetFill( *wxWHITE_BRUSH );
		
		UpdateTemplateCtrl( wxT("Template") );
		
		m_pTemplate->SetHAlign( wxSFShapeBase::halignRIGHT );
		m_pTemplate->SetVAlign( wxSFShapeBase::valignTOP );
		m_pTemplate->SetVBorder( -8 );
		
		m_pTemplate->SetLabelType( udLABEL::ltCLASS_TEMPLATE );
		
		m_pTemplate->RemoveStyle( wxSFShapeBase::sfsALWAYS_INSIDE );
		m_pTemplate->RemoveStyle( wxSFShapeBase::sfsPARENT_CHANGE );
		
		SF_ADD_COMPONENT( m_pTemplate, wxT("template") );
	}
}

void umlClassTemplateItem::UpdateTemplateCtrl( const wxString& txt )
{
	if( m_pTemplate )
	{
		m_pTemplate->SetText( txt );
		
		/*wxRect rctBB = m_pTemplate->GetBoundingBox();
		if(rctBB.GetWidth() > 20 ) m_pTemplate->SetHBorder( (rctBB.GetWidth() - 20)*-1 );
		else
			m_pTemplate->SetHBorder( 0 );*/
	}
}
