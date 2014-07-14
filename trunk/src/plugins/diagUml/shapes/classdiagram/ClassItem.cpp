#include "ClassItem.h"

#include "../../DiagUml.h"
#include "projectbase/gui/AccessTypeDialog.h"

#include "projectbase/ProjectBase.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlClassItem, uddRectElement);

umlClassItem::umlClassItem()
{
    Initialize();
	DisableUselessProperties();
}

umlClassItem::umlClassItem(const umlClassItem &obj)
: uddRectElement(obj)
{
	m_pGrid = (wxSFFlexGridShape*)obj.m_pGrid->Clone();
	m_pVariablesGrid = (wxSFGridShape*)obj.m_pVariablesGrid->Clone();
	m_pFunctionsGrid = (wxSFGridShape*)obj.m_pFunctionsGrid->Clone();
	
	if( m_pGrid && m_pVariablesGrid && m_pFunctionsGrid )
	{
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pVariablesGrid, wxT("variables_grid"));
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pFunctionsGrid, wxT("functions_grid"));
		
		// re-initialize grid
		m_pGrid->ClearGrid();
		m_pGrid->SetDimensions( 2, 1 );
		
		m_pGrid->AppendToGrid( m_pVariablesGrid );
		m_pGrid->AppendToGrid( m_pFunctionsGrid );
		
		m_pGrid->Update();
		
		SF_ADD_COMPONENT( m_pGrid, wxT("main_grid") );
		
		DisableUselessProperties();
	}
}

umlClassItem::~umlClassItem()
{
}

void umlClassItem::Initialize()
{
	SetFill(wxBrush(wxColour(254, 253, 211)));
	
	AcceptChild(wxT("uddDnDElement"));
	AcceptConnection(wxT("umlInheritanceItem"));
	AcceptConnection(wxT("umlInterfaceItem"));
	AcceptConnection(wxT("umlBiDirectAssocItem"));
	AcceptConnection(wxT("umlUniDirectAssocItem"));
	AcceptConnection(wxT("umlBasicAggregItem"));
	AcceptConnection(wxT("umlCompAggregItem"));
	AcceptConnection(wxT("umlTemplateBindItem"));
	AcceptConnection(wxT("umlIncludeAssocItem"));
	
	// set accepted project items (USED INTERNALLY)
	AcceptChild(wxT("udGenericVariableItem"));
	AcceptChild(wxT("udGenericFunctionItem"));
	AcceptChild(wxT("udMemberDataItem"));
	AcceptChild(wxT("udMemberFunctionItem"));
	AcceptChild(wxT("udSStateChartDiagramItem"));
	AcceptChild(wxT("udHStateChartDiagramItem"));
	AcceptChild(wxT("udConstructorFunctionItem"));
	AcceptChild(wxT("udDestructorFunctionItem"));
	
    AddStyle(sfsSHOW_SHADOW);

    // initialize shape's components
    m_pTitle->SetText(wxT("Class"));
	m_pTitle->GetFont().SetWeight(wxFONTWEIGHT_BOLD);
	
	// create grid and managed text fields
	m_pGrid = new wxSFFlexGridShape();
	m_pVariablesGrid = new wxSFGridShape();
	m_pFunctionsGrid = new wxSFGridShape();
	
	if( m_pGrid && m_pVariablesGrid && m_pFunctionsGrid )
	{
		// set grid
		m_pGrid->SetRelativePosition( 0, 20 );
		m_pGrid->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL );
		m_pGrid->SetDimensions( 2, 1 );
		
		m_pGrid->SetFill( *wxTRANSPARENT_BRUSH );
		m_pGrid->SetBorder( *wxTRANSPARENT_PEN );
		
		m_pGrid->SetHAlign( wxSFShapeBase::halignLEFT );
		m_pGrid->SetHBorder( 0 );
		m_pGrid->SetVBorder( 5 );
		m_pGrid->SetCellSpace( 10 );
		
		m_pGrid->AcceptChild( wxT("All") );
		
		// initialize variables' grid
		m_pVariablesGrid->SetId( -2 );
		m_pVariablesGrid->SetDimensions( 1, 1 );
		m_pVariablesGrid->SetCellSpace( 2 );

		m_pVariablesGrid->SetHAlign(wxSFShapeBase::halignLEFT);
		m_pVariablesGrid->SetVAlign(wxSFShapeBase::valignTOP);
		
		m_pVariablesGrid->SetFill(*wxTRANSPARENT_BRUSH);
		m_pVariablesGrid->SetBorder(*wxTRANSPARENT_PEN);

		m_pVariablesGrid->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL );
		
		m_pVariablesGrid->AcceptChild( wxT("uddLabelElement") );

        m_pVariablesGrid->EnableSerialization(false);
        XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pVariablesGrid, wxT("variables_grid"));
		
		// initialize functions' grid
		m_pFunctionsGrid->SetId( -3 );
		m_pFunctionsGrid->SetDimensions( 1, 1 );
		m_pFunctionsGrid->SetCellSpace( 2 );

		m_pFunctionsGrid->SetHAlign(wxSFShapeBase::halignLEFT);
		m_pFunctionsGrid->SetVAlign(wxSFShapeBase::valignTOP);
		
		m_pFunctionsGrid->SetFill(*wxTRANSPARENT_BRUSH);
		m_pFunctionsGrid->SetBorder(*wxTRANSPARENT_PEN);

		m_pFunctionsGrid->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL );
		
		m_pFunctionsGrid->AcceptChild( wxT("uddLabelElement") );

        m_pFunctionsGrid->EnableSerialization(false);
        XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pFunctionsGrid, wxT("functions_grid"));
		
		SF_ADD_COMPONENT( m_pGrid, wxT("main_grid") );
		
		m_pGrid->AppendToGrid( m_pVariablesGrid );
		m_pGrid->AppendToGrid( m_pFunctionsGrid );
		
		m_pGrid->Update();
	}
}

void umlClassItem::DisableUselessProperties()
{
	// reduce project file size
	m_pGrid->EnablePropertySerialization(wxT("accepted_connections"), false);
	m_pGrid->EnablePropertySerialization(wxT("accepted_children"), false);
	m_pGrid->EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
	m_pGrid->EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
	m_pGrid->EnablePropertySerialization(wxT("style"), false);
	
    m_pGrid->EnablePropertySerialization(wxT("border"), false);
    m_pGrid->EnablePropertySerialization(wxT("fill"), false);
    m_pGrid->EnablePropertySerialization(wxT("hborder"), false);
    m_pGrid->EnablePropertySerialization(wxT("vborder"), false);
    m_pGrid->EnablePropertySerialization(wxT("halign"), false);
    m_pGrid->EnablePropertySerialization(wxT("valign"), false);
    m_pGrid->EnablePropertySerialization(wxT("hover_color"), false);
	
    m_pGrid->EnablePropertySerialization(wxT("rows"), false);
    m_pGrid->EnablePropertySerialization(wxT("cols"), false);
    //m_pGrid->EnablePropertySerialization(wxT("cells"), false);
    m_pGrid->EnablePropertySerialization(wxT("cell_space"), false);
	
	m_pVariablesGrid->EnablePropertySerialization(wxT("accepted_connections"), false);
	m_pVariablesGrid->EnablePropertySerialization(wxT("accepted_children"), false);
	m_pVariablesGrid->EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
	m_pVariablesGrid->EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
	m_pVariablesGrid->EnablePropertySerialization(wxT("style"), false);
	
    m_pVariablesGrid->EnablePropertySerialization(wxT("border"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("fill"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("hborder"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("vborder"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("halign"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("valign"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("hover_color"), false);
	
    m_pVariablesGrid->EnablePropertySerialization(wxT("rows"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("cols"), false);
    //m_pVariablesGrid->EnablePropertySerialization(wxT("cells"), false);
    m_pVariablesGrid->EnablePropertySerialization(wxT("cell_space"), false);
	
	m_pFunctionsGrid->EnablePropertySerialization(wxT("accepted_connections"), false);
	m_pFunctionsGrid->EnablePropertySerialization(wxT("accepted_children"), false);
	m_pFunctionsGrid->EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
	m_pFunctionsGrid->EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
	m_pFunctionsGrid->EnablePropertySerialization(wxT("style"), false);
	
    m_pFunctionsGrid->EnablePropertySerialization(wxT("border"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("fill"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("hborder"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("vborder"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("halign"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("valign"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("hover_color"), false);
	
    m_pFunctionsGrid->EnablePropertySerialization(wxT("rows"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("cols"), false);
    //m_pFunctionsGrid->EnablePropertySerialization(wxT("cells"), false);
    m_pFunctionsGrid->EnablePropertySerialization(wxT("cell_space"), false);
}

void umlClassItem::DrawNormal(wxDC& dc)
{
    uddRectElement::DrawNormal(dc);

	dc.SetPen(*wxBLACK_PEN);
	
    DrawSeparators( dc );
}

void umlClassItem::DrawHover(wxDC& dc)
{
    uddRectElement::DrawHover( dc );

	dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));
	
    DrawSeparators( dc );
} 

void umlClassItem::DrawHighlighted(wxDC& dc)
{
    uddRectElement::DrawHighlighted( dc );
	
	dc.SetPen(wxPen(m_nHoverColor, 1, wxSOLID));

	DrawSeparators( dc );
}

void umlClassItem::DrawSeparators(wxDC& dc)
{
    // draw title line
    wxRect shapeBB = GetBoundingBox();

    dc.DrawLine(shapeBB.GetLeft(), shapeBB.GetTop() + 22,
                shapeBB.GetRight(), shapeBB.GetTop() + 22);
				
	// draw line between variables and functions
	wxRect fcnBB = m_pFunctionsGrid->GetBoundingBox();
	
    dc.DrawLine(shapeBB.GetLeft(), fcnBB.GetTop() - 5,
                shapeBB.GetRight(), fcnBB.GetTop() - 5);
	
    dc.SetPen(wxNullPen);
}

void umlClassItem::ClearFunctionCtrls()
{
	SerializableList::compatibility_iterator node;
	while( node = m_pFunctionsGrid->GetFirstChildNode() )
	{
		GetParentManager()->RemoveItem( node->GetData() );
	}
	// re-initialize grid control
	m_pFunctionsGrid->ClearGrid();
	m_pFunctionsGrid->SetDimensions( 1, 1 );
	
	m_pFunctionsGrid->Update();
}

void umlClassItem::ClearVariableCtrls()
{
	SerializableList::compatibility_iterator node;
	while( node = m_pVariablesGrid->GetFirstChildNode() )
	{
		GetParentManager()->RemoveItem( node->GetData() );
	}
	// re-initialize grid control
	m_pVariablesGrid->ClearGrid();
	m_pVariablesGrid->SetDimensions( 1, 1 );
	
	m_pVariablesGrid->Update();
}

uddLabelElement* umlClassItem::CreateFunctionCtrl(const wxString& content, long parentid)
{
	uddLabelElement *pLabel = new uddLabelElement();
	if( pLabel )
	{
		pLabel->SetId( parentid + udvID_OFFSET);
		
		if( m_pFunctionsGrid->AppendToGrid( pLabel ) )
		{
			pLabel->SetLabelType( udLABEL::ltCLASS_FUNCTIONS );
			pLabel->SetText( content );
		
			pLabel->SetHAlign(wxSFShapeBase::halignLEFT);
			pLabel->SetVAlign(wxSFShapeBase::valignTOP);
		
			pLabel->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsHOVERING | sfsSHOW_HANDLES );

			pLabel->EnableSerialization(false);
			
			m_pFunctionsGrid->Update();
		}
		else
		{
			delete pLabel;
			pLabel = NULL;
		}
	}
	
	return pLabel;
}

uddLabelElement* umlClassItem::CreateVariableCtrl(const wxString& content, long parentid)
{
	uddLabelElement *pLabel = new uddLabelElement();
	if( pLabel )
	{
		pLabel->SetId( parentid + udvID_OFFSET);
		
		if( m_pVariablesGrid->AppendToGrid( pLabel ) )
		{
			pLabel->SetLabelType( udLABEL::ltCLASS_VARIABLES );
			pLabel->SetText( content );
			
			pLabel->SetHAlign(wxSFShapeBase::halignLEFT);
			pLabel->SetVAlign(wxSFShapeBase::valignTOP);
		
			pLabel->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsHOVERING | sfsSHOW_HANDLES );

			pLabel->EnableSerialization(false);
			
			m_pVariablesGrid->Update();
		}
		else
		{
			delete pLabel;
			pLabel = NULL;
		}
	}
	
	return pLabel;
}

void umlClassItem::OnChildDropped(const wxRealPoint& pos, wxSFShapeBase* child)
{
	udLinkItem *pLink = wxDynamicCast( child->GetUserData(), udLinkItem );
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

		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );
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
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement, NULL, wxEmptyString, udfDELAYED );
}
