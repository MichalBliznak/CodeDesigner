#include "DiagUml.h"
#include "gui/ActionTypeDialog.h"
#include "gui/RenameVirtualDialog.h"
#include "projectbase/gui/AccessTypeDialog.h"
#include "DiagIds.h"
#include "Ids.h"

void udUmlDiagramPlugin::OnAssignAction(wxCommandEvent& event)
{
	udDiagElementItem *pElement = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udDiagElementItem );
	if( pElement )
	{
		SerializableList lstActions;
		IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udActionItem), lstActions);

		SerializableList::compatibility_iterator node = lstActions.Item( event.GetId() - IDM_TRANS_ASSIGNACTION );
		if( node )
		{
			// assign the link to selected diagram element
			if( pElement->IsKindOf(CLASSINFO(udCompStateElementItem)) )
			{
				udActionTypeDialog dlg(IPluginManager::Get()->GetMainFrame());
				dlg.ShowModal();
				
				pElement->AssignCodeItem( new udStateActionLinkItem((udCodeItem*)node->GetData(), (udStateActionLinkItem::TYPE)dlg.GetChoice()) );
			}
			else
				pElement->AssignCodeItem( new udActionLinkItem((udCodeItem*)node->GetData()) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignFunction(wxCommandEvent& event)
{
	udDiagElementItem *pElement = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udDiagElementItem );
	if( pElement )
	{
		udProjectItem *pFcn;
		SerializableList lstFunctions;
		
		IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udFunctionItem), lstFunctions);
		
		// remove already included items
		SerializableList::compatibility_iterator node = lstFunctions.GetFirst();
		while( node )
		{
			pFcn = (udProjectItem*)node->GetData();
			node = node->GetNext();
			
			if( udPROJECT::GetProjectItem(pElement, CLASSINFO(udCodeLinkItem), pFcn->GetName()) ) lstFunctions.DeleteObject(pFcn);
		}
		
		node = lstFunctions.Item( event.GetId() - IDM_DIAG_ASSIGNFUNCTION);
		if( node )
		{
			// assign the link to selected diagram element
			udAccessTypeDialog dlg(IPluginManager::Get()->GetMainFrame());
			dlg.ShowModal();
				
			pElement->AssignCodeItem( new udMemberFunctionLinkItem((udCodeItem*)node->GetData(), (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignGuard(wxCommandEvent& event)
{
	udTransElementItem *pTrans = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udTransElementItem );
	if( pTrans )
	{
		SerializableList lstGuards;
		IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udConditionItem), lstGuards);
		IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udEventItem), lstGuards);

		SerializableList::compatibility_iterator node = lstGuards.Item( event.GetId() - IDM_TRANS_ASSIGNGUARD );
		if( node )
		{
			pTrans->ClearCodeItems(CLASSINFO(udConditionItem));
			pTrans->ClearCodeItems(CLASSINFO(udEventItem));
			
			// assign the link to selected transition
			if( node->GetData()->IsKindOf(CLASSINFO(udEventItem)) )	pTrans->AssignCodeItem( new udEventLinkItem( (udCodeItem*)node->GetData() ) );
			else
				pTrans->AssignCodeItem( new udConditionLinkItem( (udCodeItem*)node->GetData() ) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pTrans );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewAction(wxCommandEvent& event)
{
	udTransElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udTransElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new condition
		udActionItem* pAction = (udActionItem*) pProj->CreateProjectItem( wxT("udActionItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pAction )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pAction, (udProjectItem*) pProj->GetRootItem() );
			
			// assign the link to selected transition
			pParent->AssignCodeItem( new udActionLinkItem(pAction) );
			
			pAction->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewStateAction(wxCommandEvent& event)
{
	udCompStateElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udCompStateElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new state action
		udActionItem* pAction = (udActionItem*)  pProj->CreateProjectItem( wxT("udActionItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pAction )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pAction, (udProjectItem*) pProj->GetRootItem() );
			
			udActionTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
			dlg.ShowModal();
			
			// assign the link to selected composite state
			pParent->AssignCodeItem( new udStateActionLinkItem(pAction, (udStateActionLinkItem::TYPE)dlg.GetChoice()) );
			
			pAction->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewCondition(wxCommandEvent& event)
{
	udTransElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udTransElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new condition
		udConditionItem* pCondition = (udConditionItem*) pProj->CreateProjectItem( wxT("udConditionItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pCondition )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pCondition, (udProjectItem*) pProj->GetRootItem() );
			
			// assign the link to selected transition
			pParent->ClearCodeItems(CLASSINFO(udConditionItem));
			pParent->ClearCodeItems(CLASSINFO(udEventItem));
			pParent->AssignCodeItem( new udConditionLinkItem(pCondition) );
			
			pCondition->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewEvent(wxCommandEvent& event)
{
	udTransElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udTransElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new condition
		udEventItem* pEvent = (udEventItem*) pProj->CreateProjectItem( wxT("udEventItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pEvent )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pEvent, (udProjectItem*) pProj->GetRootItem() );
			
			// assign the link to selected transition
			pParent->ClearCodeItems(CLASSINFO(udConditionItem));
			pParent->ClearCodeItems(CLASSINFO(udEventItem));
			pParent->AssignCodeItem( new udEventLinkItem(pEvent) );
			
			pEvent->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewFunction(wxCommandEvent& event)
{
	udClassElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udClassElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new variable
		udMemberFunctionItem* pFcn = (udMemberFunctionItem*)pProj->CreateProjectItem( wxT("udMemberFunctionItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pFcn )
		{
			pFcn->SetScope( pParent->GetName() );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pFcn, (udProjectItem*)pProj->GetRootItem() );
			
			udAccessTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
			dlg.ShowModal();
		
			// assign the link to selected transition
			pParent->AssignCodeItem( new udMemberFunctionLinkItem(pFcn, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
			
			pFcn->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignNewVariable(wxCommandEvent& event)
{
	udClassElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udClassElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new variable
		udMemberDataItem* pVar = (udMemberDataItem*)pProj->CreateProjectItem( wxT("udMemberDataItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pVar )
		{
			pVar->SetScope( pParent->GetName() );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pVar, (udProjectItem*)pProj->GetRootItem() );
			
			udAccessTypeDialog dlg(IPluginManager::Get()->GetMainFrame() );
			dlg.ShowModal();
		
			// assign the link to selected transition
			pParent->AssignCodeItem( new udMemberDataLinkItem(pVar, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );

			pVar->OnEditItem( IPluginManager::Get()->GetMainFrame() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnAssignVariable(wxCommandEvent& event)
{
	udClassElementItem *pElement = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udClassElementItem );
	
	if( pElement )
	{
		udCodeItem *pVar;
		SerializableList lstVariables;
		
		IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udMemberDataItem), lstVariables);
		
		// remove already included items
		SerializableList::compatibility_iterator node = lstVariables.GetFirst();
		while( node )
		{
			pVar = (udCodeItem*) node->GetData();
			node = node->GetNext();
			
			if( udPROJECT::GetProjectItem(pElement, CLASSINFO(udCodeLinkItem), pVar->GetName()) ) lstVariables.DeleteObject(pVar);
			if( pVar->GetScope() != pElement->GetName() ) lstVariables.DeleteObject(pVar);
		}
		
		node = lstVariables.Item( event.GetId() - IDM_DIAG_ASSIGNVARIABLE );
		if( node )
		{
			// assign the link to selected diagram element
			udAccessTypeDialog dlg(IPluginManager::Get()->GetMainFrame());
			dlg.ShowModal();
				
			pElement->AssignCodeItem( new udMemberDataLinkItem((udCodeItem*)node->GetData(), (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnCreateConstructor(wxCommandEvent& event)
{
	udClassElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udClassElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new class constructor
		udConstructorFunctionItem* pFcn = (udConstructorFunctionItem*)pProj->CreateProjectItem( wxT("udConstructorFunctionItem"),pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pFcn )
		{
			pFcn->SetScope( pParent->GetName() );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pFcn, (udProjectItem*)pProj->GetRootItem() );
			
			udAccessTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
			dlg.ShowModal();
		
			// assign the link to selected transition
			pParent->AssignCodeItem( new udMemberFunctionLinkItem(pFcn, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnCreateDestructor(wxCommandEvent& event)
{
	udClassElementItem *pParent = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udClassElementItem );
	
	if( pParent )
	{
		IProject *pProj = IPluginManager::Get()->GetProject();
		
		// create new class destructor
		udDestructorFunctionItem* pFcn = (udDestructorFunctionItem*)pProj->CreateProjectItem( wxT("udDestructorFunctionItem"), pProj->GetRootItem()->GetId() );
		// create relevant tree item
		if( pFcn )
		{
			pFcn->SetScope( pParent->GetName() );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pFcn, (udProjectItem*)pProj->GetRootItem() );
			
			udAccessTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
			dlg.ShowModal();
		
			// assign the link to selected transition
			pParent->AssignCodeItem( new udMemberFunctionLinkItem(pFcn, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );
				
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent );
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}

void udUmlDiagramPlugin::OnClearCodeItems(wxCommandEvent& event)
{
	udDiagElementItem *pElement = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udDiagElementItem );
	if( pElement )
	{
		if( event.GetId() == IDM_DIAG_CLEARACTIONS )
		{
			pElement->ClearCodeItems( CLASSINFO(udActionItem) );
		}
		else if( event.GetId() == IDM_DIAG_CLEARCONDITIONS )
		{
			pElement->ClearCodeItems( CLASSINFO(udEventItem) );
			pElement->ClearCodeItems( CLASSINFO(udConditionItem) );
		}
		else if( event.GetId() == IDM_ENUM_CLEARELEMENTS )
		{
			pElement->ClearCodeItems( CLASSINFO(udEnumValueItem) );
		}
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
		IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
	}
}

void udUmlDiagramPlugin::OnRefactorVirtualFcn(wxCommandEvent& event)
{
	udMemberFunctionItem *pVirtFcn = NULL;
	
	udProjectItem *pItem = IPluginManager::Get()->GetSelectedProjectItem();
	if( !pItem ) return;
	
	if( pItem->IsKindOf( CLASSINFO(udLinkItem) ) ) pVirtFcn = wxDynamicCast( ((udLinkItem*)pItem)->GetOriginal(), udMemberFunctionItem );
	else
		pVirtFcn = wxDynamicCast( pItem, udMemberFunctionItem );
	if( !pVirtFcn ) return;
	
	udRenameVirtualDialog dlg( IPluginManager::Get()->GetMainFrame(), pVirtFcn, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager mgr( dlg, wxT("refactor_virtual_function") );
	
	if( dlg.ShowModal() == wxID_OK && (pVirtFcn->GetName() != dlg.GetName() ) )
	{
		const wxArrayString &arrCandidates = dlg.GetCandidates();
		
		SerializableList lstRenamedFcns;
		
		lstRenamedFcns.Append( pVirtFcn );
		
		// find another functions to rename
		SerializableList lstMembers;
		IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udMemberFunctionItem), lstMembers );
	
		for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
		{
			udMemberFunctionItem *pCand = (udMemberFunctionItem*)*it;
			
			if( ( pCand->GetFunctionModifer() == udLanguage::FM_ABSTRACT ||
				  pCand->GetFunctionModifer() == udLanguage::FM_VIRTUAL ) &&
				  arrCandidates.Index( pCand->GetScope() + wxT("::") + pCand->GetName() ) != wxNOT_FOUND ) 
			{
				lstRenamedFcns.Append( pCand );
			}
		}
		// rename the functions
		for( SerializableList::iterator it = lstRenamedFcns.begin(); it != lstRenamedFcns.end(); ++ it )
		{
			udFunctionItem *pFcn = (udFunctionItem*)*it;
			
			pFcn->OnTreeTextChange( dlg.GetName() );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pFcn );
		}
	}
}

void udUmlDiagramPlugin::OnChangeAccessType(wxCommandEvent& event)
{
	// set access type to code link
	udCodeLinkItem *pLink = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udCodeLinkItem );
	if( pLink )
	{
		pLink->SetAccessType( (udLanguage::ACCESSTYPE)(event.GetId() - IDM_CODE_ACCESSTYPE) );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pLink->GetOriginal() );
	}
	// .. or to diagram element
	udDiagElementItem *pElement= wxDynamicCast(  IPluginManager::Get()->GetSelectedProjectItem(), udDiagElementItem );
	if( pElement )
	{
		pElement->SetAccessType( (udLanguage::ACCESSTYPE)(event.GetId() - IDM_CODE_ACCESSTYPE) );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pElement );
	}
}

void udUmlDiagramPlugin::OnAddEnumElement(wxCommandEvent& event)
{
	udEnumElementItem *pEnum = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udEnumElementItem );
	if( pEnum )
	{
		wxTextEntryDialog dlg( IPluginManager::Get()->GetMainFrame(), wxT("Enumeration element:"), wxT("Enter new enumeration element") );
		
		if( dlg.ShowModal() == wxID_OK )
		{
			pEnum->AddElementString( dlg.GetValue() );
			
			IPluginManager::Get()->SaveDiagramState( IPluginManager::Get()->GetActiveDiagram() );
		}
	}
}
