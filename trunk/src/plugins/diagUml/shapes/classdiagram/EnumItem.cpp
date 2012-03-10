#include "EnumItem.h"

#include "../../DiagUml.h"

#include "projectbase/ProjectBase.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlEnumItem, uddRectElement);

umlEnumItem::umlEnumItem()
{
    Initialize();
	DisableUselessProperties();
}

umlEnumItem::umlEnumItem(const umlEnumItem &obj)
: uddRectElement(obj)
{
	m_pStereotype = (uddLabelElement*)obj.m_pStereotype->Clone();
	if( m_pStereotype )
	{
		SF_ADD_COMPONENT( m_pStereotype, wxT("stereotype") );
	}
	
	m_pElementsGrid = (wxSFGridShape*)obj.m_pElementsGrid->Clone();
	if( m_pElementsGrid )
	{
		SF_ADD_COMPONENT( m_pElementsGrid, wxT("elements_grid") );
		
		m_pElementsGrid->Update();
		
		DisableUselessProperties();
	}
}

umlEnumItem::~umlEnumItem()
{
}

void umlEnumItem::Initialize()
{
	SetFill(wxBrush(wxColour(254, 253, 211)));
	
	ClearAcceptedChilds();
	ClearAcceptedConnections();
	ClearAcceptedSrcNeighbours();
	ClearAcceptedTrgNeighbours();
	
	AcceptConnection(wxT("umlIncludeAssocItem"));
	AcceptConnection(wxT("uddNoteConnItem"));
	
	AcceptSrcNeighbour(wxT("umlClassItem"));
	AcceptTrgNeighbour(wxT("uddNoteItem"));
    AcceptSrcNeighbour(wxT("uddNoteItem"));
	
	// set accepted project items (USED INTERNALLY)
	/*AcceptChild(wxT("udEnumValueItem"));*/
	
    AddStyle(sfsSHOW_SHADOW);

    // update title
	m_pTitle->GetFont().SetWeight(wxFONTWEIGHT_BOLD);
	m_pTitle->SetVBorder( 20 );
	
	// create stereotype
	m_pStereotype = new uddLabelElement();
	
	if( m_pStereotype )
	{
		m_pStereotype->SetLabelType( udLABEL::ltSTEREOTYPE );
		m_pStereotype->SetText( wxT("<< enumeration >>") );
		m_pStereotype->SetHAlign( halignCENTER );
		m_pStereotype->SetVAlign( valignTOP );
		m_pStereotype->SetHBorder( 5 );
		m_pStereotype->SetVBorder( 5 );
		m_pStereotype->SetEditType( wxSFEditTextShape::editDISABLED );
		m_pStereotype->AddStyle( sfsALWAYS_INSIDE );
		m_pStereotype->RemoveStyle( sfsPOSITION_CHANGE );
		
		SF_ADD_COMPONENT( m_pStereotype, wxT("stereotype") );
	}
	
	// create grid 
	m_pElementsGrid = new wxSFGridShape();
	
	if( m_pElementsGrid )
	{
		// set grid
		m_pElementsGrid->SetRelativePosition( 0, 40 );
		m_pElementsGrid->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL );
		m_pElementsGrid->SetDimensions( 1, 1 );
		
		m_pElementsGrid->SetFill( *wxTRANSPARENT_BRUSH );
		m_pElementsGrid->SetBorder( *wxTRANSPARENT_PEN );
		
		m_pElementsGrid->SetHAlign( halignLEFT );
		m_pElementsGrid->SetHBorder( 5 );
		m_pElementsGrid->SetVBorder( 5 );
		m_pElementsGrid->SetCellSpace( 2 );
		
		m_pElementsGrid->AcceptChild( wxT("uddLabelElement") );
		
		SF_ADD_COMPONENT( m_pElementsGrid, wxT("elements_grid") );
		
		m_pElementsGrid->Update();
	}
}

void umlEnumItem::DisableUselessProperties()
{
	// reduce project file size
	m_pElementsGrid->EnablePropertySerialization(wxT("accepted_connections"), false);
	m_pElementsGrid->EnablePropertySerialization(wxT("accepted_children"), false);
	m_pElementsGrid->EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
	m_pElementsGrid->EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
	m_pElementsGrid->EnablePropertySerialization(wxT("style"), false);
	
    m_pElementsGrid->EnablePropertySerialization(wxT("border"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("fill"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("hborder"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("vborder"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("halign"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("valign"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("hover_color"), false);
	
    m_pElementsGrid->EnablePropertySerialization(wxT("rows"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("cols"), false);
    //m_pElementsGrid->EnablePropertySerialization(wxT("cells"), false);
    m_pElementsGrid->EnablePropertySerialization(wxT("cell_space"), false);
}

void umlEnumItem::DrawNormal(wxDC& dc)
{
    uddRectElement::DrawNormal(dc);

	dc.SetPen(*wxBLACK_PEN);
	
    DrawSeparators( dc );
}

void umlEnumItem::DrawHover(wxDC& dc)
{
    uddRectElement::DrawHover( dc );

	dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
	
    DrawSeparators( dc );
} 

void umlEnumItem::DrawHighlighted(wxDC& dc)
{
    uddRectElement::DrawHighlighted( dc );
	
	dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));

	DrawSeparators( dc );
}

void umlEnumItem::DrawSeparators(wxDC& dc)
{
    // draw title line
    wxRect shapeBB = GetBoundingBox();
				
	// draw line between variables and functions
	wxRect fcnBB = m_pElementsGrid->GetBoundingBox();
	
    dc.DrawLine(shapeBB.GetLeft(), fcnBB.GetTop() - 5,
                shapeBB.GetRight(), fcnBB.GetTop() - 5);
	
    dc.SetPen(wxNullPen);
}

void umlEnumItem::ClearElementCtrls()
{
	SerializableList::compatibility_iterator node;
	while( (node = m_pElementsGrid->GetFirstChildNode()) )
	{
		GetParentManager()->RemoveItem( node->GetData() );
	}
	// re-initialize grid control
	m_pElementsGrid->ClearGrid();
	m_pElementsGrid->SetDimensions( 1, 1 );
	
	m_pElementsGrid->Update();
}

uddLabelElement* umlEnumItem::CreateElementCtrl(const wxString& content, long parentid)
{
	uddLabelElement *pLabel = new uddLabelElement();
	if( pLabel )
	{
		pLabel->SetId( parentid + udvID_OFFSET);
		
		if( m_pElementsGrid->AppendToGrid( pLabel ) )
		{
			pLabel->SetLabelType( udLABEL::ltENUM_ELEMENT );
			pLabel->SetText( content );
		
			pLabel->SetHAlign(wxSFShapeBase::halignLEFT);
			pLabel->SetVAlign(wxSFShapeBase::valignTOP);
		
			pLabel->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsHOVERING | sfsSHOW_HANDLES );

			pLabel->EnableSerialization(false);
			
			m_pElementsGrid->Update();
		}
		else
		{
			delete pLabel;
			pLabel = NULL;
		}
	}
	
	return pLabel;
}


void umlEnumItem::OnChildDropped(const wxRealPoint& pos, wxSFShapeBase* child)
{
/*	udLinkItem *pLink = wxDynamicCast( child->GetUserData(), udLinkItem );
	if( !pLink ) return;
	
	udProjectItem *pOriginal = pLink->GetOriginal();
	if( !pOriginal ) return;
	
	udClassElementItem *pElement = wxDynamicCast( GetUserData(), udClassElementItem );
	if( !pElement ) return;
	
	if( !IsChildAccepted( pOriginal->GetClassInfo()->GetClassName()) )
	{
		wxMessageBox( wxString::Format( wxT("'%s' is not accepted by '%s'"), pOriginal->GetName().c_str(), pElement->GetName().c_str() ), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		return;
	}
	
	// only one instance of each code item is allowed
	if( udPROJECT::GetProjectItem( pElement, CLASSINFO(udCodeLinkItem), pOriginal->GetName()) ) return;
		
	// assign dropped code link to parent element
	if( pLink->IsKindOf( CLASSINFO(udMemberDataLinkItem) ) )
	{
		wxString sOrigClassName = ((udMemberDataItem*)pOriginal)->GetScope();
		if( sOrigClassName == pElement->GetName() )
		{
			pElement->AssignCodeItem( (udMemberDataLinkItem*)pLink->Clone() );
		}
		else
			pElement->AssignMemberCopy( pLink );
	}
	else if( pLink->IsKindOf( CLASSINFO(udMemberFunctionLinkItem) ) )
	{
		wxString sOrigClassName = ((udMemberFunctionItem*)pOriginal)->GetScope();
		if( sOrigClassName == pElement->GetName() )
		{
			pElement->AssignCodeItem( (udMemberFunctionLinkItem*)pLink->Clone() );
		}
		else
			pElement->AssignMemberCopy( pLink );
	}
	else if( pLink->IsKindOf( CLASSINFO(udVariableLinkItem) ) || pLink->IsKindOf( CLASSINFO(udFunctionLinkItem) ) )
	{
		pElement->AssignMemberCopy( pLink );

		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), udfDELAYED );
	}
	else if( pLink->IsKindOf( CLASSINFO(udDiagramLinkItem) ) )
	{
		IProject *pProject = IPluginManager::Get()->GetProject();
		
		// only one instance of each code item is allowed
		if( udPROJECT::GetProjectItem( pElement, CLASSINFO(udMemberFunctionLinkItem), pOriginal->GetName() + wxT("_Wrapper") ) ) return;
		
		// find diagram wrapper if exists, otherwise create a new one
		udCodeItem *pWrapper = (udCodeItem*)pProject->GetProjectItem( CLASSINFO(udMemberFunctionItem), pOriginal->GetName() + wxT("_Wrapper") );
		if( pWrapper )
		{
			udAccessTypeDialog dlg( GetParentCanvas() );
			dlg.ShowModal();

			pElement->AssignCodeItem( new udMemberFunctionLinkItem( pWrapper, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
		}
		else
		{
			udAccessTypeDialog dlg( GetParentCanvas() );
			dlg.ShowModal();
			
			// create new instance of action function
			udMemberFunctionItem *pNewFcn = new udMemberFunctionItem();
			pNewFcn->SetScope( pElement->GetName() );
			pNewFcn->SetName( pOriginal->GetName() + wxT("_Wrapper") );
			pNewFcn->SetRetValDataType( udLanguage::DT_USERDEFINED );
			pNewFcn->SetUserRetValDataType( wxT("STATE_T") );
			pNewFcn->SetImplementation( pOriginal->GetName() );
					
			pProject->AddItem( (xsSerializable*)NULL, pNewFcn );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewFcn, (udProjectItem*)pProject->GetRootItem() );

			pElement->AssignCodeItem( new udMemberFunctionLinkItem((udCodeItem*)pNewFcn, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
		}
	}
	
	// delayed element update (due to unfinished processing of target class shape which will be changed by this event)
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement, NULL, udfDELAYED );*/
}
