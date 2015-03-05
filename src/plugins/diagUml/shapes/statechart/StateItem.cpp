#include "StateItem.h"
#include "projectbase/ProjectBase.h"
#include "../../gui/ActionTypeDialog.h"
#include "../../gui/ClassInstanceDialog.h"
#include "../../DiagSCH.h"
#include "../../DiagCD.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlCompStateItem, umlSimpleStateItem);

umlCompStateItem::umlCompStateItem()
{
    Initialize();
	DisableUselessProperties();
}

umlCompStateItem::umlCompStateItem(const umlCompStateItem &obj)
: umlSimpleStateItem(obj)
{
	m_pGrid = (wxSFGridShape*)obj.m_pGrid->Clone();
	m_pEntryActions = (uddLabelElement*)obj.m_pEntryActions->Clone();
	m_pExitActions = (uddLabelElement*)obj.m_pExitActions->Clone();
	
	if( m_pGrid && m_pEntryActions && m_pExitActions )
	{
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pEntryActions, wxT("entry_actions"));
		XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pExitActions, wxT("exit_actions"));
		
		// re-initialize grid
		m_pGrid->ClearGrid();
		m_pGrid->SetDimensions( 2, 1 );
		
		SF_ADD_COMPONENT( m_pGrid, wxT("actions_grid") );
		
		m_pGrid->AppendToGrid( m_pEntryActions );
		m_pGrid->AppendToGrid( m_pExitActions );
		
		m_pGrid->Update();
		
		DisableUselessProperties();
	}
}

umlCompStateItem::~umlCompStateItem()
{
}

void umlCompStateItem::Initialize()
{
    // set basic properties
	SetFill(wxBrush(wxColour(254, 253, 211)));

	AcceptChild(wxT("uddDnDElement"));
	
	// accepted shapes
    AcceptChild(wxT("umlSimpleStateItem"));
    AcceptChild(wxT("umlCompStateItem"));
    AcceptChild(wxT("umlSubStateItem"));
    AcceptChild(wxT("umlInitialItem"));
	AcceptChild(wxT("umlFinalItem"));
	//AcceptChild(wxT("umlEntryItem"));
    //AcceptChild(wxT("umlExitItem"));
    AcceptChild(wxT("umlHistoryItem"));
    AcceptChild(wxT("umlDecisionItem"));
    //AcceptChild(wxT("umlForkJoinHItem"));
    //AcceptChild(wxT("umlForkJoinVItem"));
	
	// set accepted project items (USED INTERNALLY)
	AcceptChild(wxT("udActionItem"));
	AcceptChild(wxT("udGenericFunctionItem"));
	AcceptChild(wxT("udSStateChartDiagramItem"));
	AcceptChild(wxT("udHStateChartDiagramItem"));
	AcceptChild(wxT("udClassElementItem"));
	AcceptChild(wxT("udSCHSubDiagramElementItem"));
	
    AddStyle(sfsSHOW_SHADOW);
	
	m_pGrid = new wxSFGridShape();
	m_pEntryActions = new uddLabelElement();
	m_pExitActions = new uddLabelElement();
	
	if( m_pGrid && m_pEntryActions && m_pExitActions )
	{
		// initialize grid
		m_pGrid->SetDimensions(2, 1);
		m_pGrid->SetFill( *wxTRANSPARENT_BRUSH );
		m_pGrid->SetBorder( *wxTRANSPARENT_PEN );
		
		m_pGrid->SetStyle( sfsALWAYS_INSIDE | sfsPROCESS_DEL );
		
		m_pGrid->SetRelativePosition(0, 20);
		m_pGrid->SetHAlign( wxSFShapeBase::halignLEFT );
		m_pGrid->SetVBorder(5);
		m_pGrid->SetHBorder(5);
		m_pGrid->SetCellSpace(3);
		
		m_pGrid->AcceptChild( wxT("All") );
		
		// initialize entry actions
	    m_pEntryActions->SetLabelType( udLABEL::ltSTATE_ENTRYACTIONS );
		m_pEntryActions->SetId( -2 );
		m_pEntryActions->SetText(wxT("entry / []"));

		m_pEntryActions->SetHAlign(wxSFShapeBase::halignLEFT);
		m_pEntryActions->SetVAlign(wxSFShapeBase::valignTOP);
		
		m_pEntryActions->SetStyle( sfsHOVERING | sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsSHOW_HANDLES);

        m_pEntryActions->EnableSerialization(false);
        XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pEntryActions, wxT("entry_actions"));
		
		// initialize exit actions
	    m_pExitActions->SetLabelType( udLABEL::ltSTATE_EXITACTIONS );
	    m_pExitActions->SetId( -3 );
		m_pExitActions->SetText(wxT("exit / []"));
		
		m_pExitActions->SetHAlign(wxSFShapeBase::halignLEFT);
		m_pExitActions->SetVAlign(wxSFShapeBase::valignTOP);

		m_pExitActions->SetStyle( sfsHOVERING | sfsALWAYS_INSIDE | sfsPROCESS_DEL | sfsSHOW_HANDLES);

        m_pExitActions->EnableSerialization(false);
        XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pExitActions, wxT("exit_actions"));

		SF_ADD_COMPONENT( m_pGrid, wxT("actions_grid") );
		
		m_pGrid->AppendToGrid(m_pEntryActions);
        m_pGrid->AppendToGrid(m_pExitActions);
		
		m_pGrid->Update();
	}
}

void umlCompStateItem::OnChildDropped(const wxRealPoint& pos, wxSFShapeBase* child)
{
	udLinkItem *pLink = wxDynamicCast( child->GetUserData(), udLinkItem );
	if( !pLink ) return;
	
	udProjectItem *pOriginal = pLink->GetOriginal();
	if( !pOriginal ) return;
	
	udCompStateElementItem *pElement = wxDynamicCast( GetUserData(), udCompStateElementItem );
	if( !pElement ) return;
	
	if( !IsChildAccepted( pOriginal->GetClassInfo()->GetClassName()) )
	{
		wxMessageBox( wxString::Format( wxT("'%s' is not accepted by '%s'"), pOriginal->GetName().c_str(), pElement->GetName().c_str() ), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		return;
	}
		
	// assign dropped code link to parent element
	if( pLink->IsKindOf( CLASSINFO(udStateActionLinkItem) ) )
	{
		pElement->AssignCodeItem( (udStateActionLinkItem*)pLink->Clone() );
	}
	else if( pLink->IsKindOf( CLASSINFO(udActionLinkItem) ) || pLink->IsKindOf( CLASSINFO(udFunctionLinkItem) ))
	{
		udStateActionLinkItem::TYPE nActionType;
		
		// "pos" is absolute here...
		if( m_pEntryActions->GetBoundingBox().Contains( wxSFCommonFcn::Conv2Point(pos) ) ) nActionType = udStateActionLinkItem::saENTRY;
		else if( m_pExitActions->GetBoundingBox().Contains( wxSFCommonFcn::Conv2Point(pos) ) ) nActionType = udStateActionLinkItem::saEXIT;
		else
		{
			udActionTypeDialog dlg(IPluginManager::Get()->GetMainFrame() );
			udWindowManager dlgman( dlg, wxT("action_type_dialog") );
			
			dlg.ShowModal();
			
			nActionType = (udStateActionLinkItem::TYPE)dlg.GetChoice();
		}
		
		if( pLink->IsKindOf(CLASSINFO(udActionLinkItem)) )
		{
			pElement->AssignCodeItem( new udStateActionLinkItem((udCodeItem*)pOriginal, nActionType) );
		}
		else
		{
			// create new instance of action function and remove the source generic variable
			udActionItem *pNewAct = new udActionItem( *(udActionItem*)pOriginal );
			IPluginManager::Get()->GetProject()->AddItem( pOriginal->GetParent(), pNewAct );

			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );

			pNewAct->UpdateSignature();
			pElement->AssignCodeItem( new udStateActionLinkItem((udCodeItem*)pNewAct, nActionType) );
		}
	}
	else if( pLink->IsKindOf( CLASSINFO(udElementLinkItem) ) ||
			 pLink->IsKindOf( CLASSINFO(udDiagramLinkItem) ) )
	{
		// CLASS ITEM //////////////////////////////////////////////////////////
		
		udClassElementItem *pClassElement = wxDynamicCast( pOriginal, udClassElementItem );
		if( pClassElement )
		{
			udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
			
			if( !pLang->HasClasses() )
			{
				wxMessageBox( wxT("Selected language doesn't support class instantiation."), wxT("CodeDesigner"), wxOK | wxICON_ERROR );
				return;
			}
			
			IProject *pProject = IPluginManager::Get()->GetProject();
			
			// create new condition
			udActionItem* pAction = (udActionItem*)pProject->CreateProjectItem( wxT("udActionItem"), pProject->GetRootItem()->GetId() );
			if( pAction )
			{
				pAction->SetName( wxT("instantiate ") + pLink->GetName() );
				pAction->SetInline( true );
				
				udClassInstanceDialog dlg( IPluginManager::Get()->GetActiveCanvas() );
				udWindowManager dlgman( dlg, wxT("class_instance_dialog") );
				
				dlg.ShowModal();
				
				udActionTypeDialog dlga(IPluginManager::Get()->GetMainFrame() );
				udWindowManager dlgaman( dlga, wxT("action_type_dialog") );
				
				dlga.ShowModal();
				
				udStateActionLinkItem::TYPE nActionType = (udStateActionLinkItem::TYPE)dlga.GetChoice();
				
				// construct wrapper's code				
				pLang->PushCode();
				pLang->ClassInstanceCmd( pLang->MakeValidIdentifier( dlg.GetInstanceName() ),
										 pLang->MakeValidIdentifier( pClassElement->GetName() ),
										 dlg.GetParameters(),
										 dlg.GetIsDynamic() );
										 
				pAction->SetCode( pLang->GetCodeBuffer() );
				pLang->PopCode();
				
				// assign the link to the transition
				pAction->UpdateSignature();
				pElement->AssignCodeItem( new udStateActionLinkItem( (udCodeItem*)pAction, nActionType ) );

				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pAction, (udProjectItem*)pProject->GetRootItem() );
			}
		}
		
		// SUBDIAGRAM ITEM //////////////////////////////////////////////////////////
		
		if( pOriginal->IsKindOf(CLASSINFO(udDiagramItem)) ||
			pOriginal->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
		{
			IProject *pProject = IPluginManager::Get()->GetProject();
		
			// find diagram wrapper if exists, otherwise create a new one
			udCodeItem *pWrapper = (udCodeItem*)pProject->GetProjectItem( CLASSINFO(udActionItem), pOriginal->GetName() + wxT("_Wrapper") );
			if( pWrapper )
			{
				udActionTypeDialog dlg(IPluginManager::Get()->GetMainFrame() );
				dlg.ShowModal();

				pElement->AssignCodeItem( new udStateActionLinkItem( pWrapper, (udStateActionLinkItem::TYPE)dlg.GetChoice()) );
			}
			else
			{
				udActionTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
				udWindowManager dlgman( dlg, wxT("action_type_dialog") );
				
				dlg.ShowModal();

				// create new instance of action function
				udActionItem *pNewAct = new udActionItem();
				pNewAct->SetName( pOriginal->GetName() + wxT("_Wrapper") );
				pNewAct->SetRetValDataType( udLanguage::DT_USERDEFINED );
				pNewAct->SetUserRetValDataType( wxT("STATE_T") );
				pNewAct->SetImplementation( pOriginal->GetName() );
						
				pProject->AddItem( (xsSerializable*)NULL, pNewAct );
					
				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, (udProjectItem*)pProject->GetRootItem() );

				pNewAct->UpdateSignature();
				pElement->AssignCodeItem( new udStateActionLinkItem((udCodeItem*)pNewAct, (udStateActionLinkItem::TYPE)dlg.GetChoice()) );
			}
		}
	}
		
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
}


void umlCompStateItem::DisableUselessProperties()
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
}
