#include "TransitionItem.h"
#include "SubStateItem.h"
#include "projectbase/ProjectBase.h"
#include "../../gui/AssignAsDialog.h"
#include "../../gui/ClassInstanceDialog.h"
#include "../../DiagSCH.h"
#include "../../DiagCD.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlTransitionItem, uddLineElement);

umlTransitionItem::umlTransitionItem()
{
    Initialize();
}

umlTransitionItem::umlTransitionItem(const umlTransitionItem &obj)
: uddLineElement(obj)
{
    // create target arrow
    SetTrgArrow(new wxSFSolidArrow());
	EnablePropertySerialization(wxT("target_arrow"), false);
}

umlTransitionItem::~umlTransitionItem()
{
}

void umlTransitionItem::Initialize()
{
	// set basic properties
	
	// accepted shapes
	AcceptChild(wxT("uddDnDElement"));
	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("uddNoteItem"));
    AcceptTrgNeighbour(wxT("uddNoteItem"));
	
	// set accepted project items (USED INTERNALLY)
	AcceptChild(wxT("udActionItem"));
	AcceptChild(wxT("udConditionItem"));
	AcceptChild(wxT("udEventItem"));
	AcceptChild(wxT("udFinalElementItem"));
	AcceptChild(wxT("udGenericVariableItem"));
	AcceptChild(wxT("udGenericFunctionItem"));
	AcceptChild(wxT("udSStateChartDiagramItem"));
	AcceptChild(wxT("udHStateChartDiagramItem"));
	AcceptChild(wxT("udClassElementItem"));
	AcceptChild(wxT("udSCHSubDiagramElementItem"));
	
    // create target arrow
    SetTrgArrow(new wxSFSolidArrow());
	EnablePropertySerialization(wxT("target_arrow"), false);

    // initialize shape components
    m_pLabel->SetText(wxT("<< / [] >>"));
}

void umlTransitionItem::OnChildDropped(const wxRealPoint& pos, wxSFShapeBase* child)
{
	udLinkItem *pLink = wxDynamicCast( child->GetUserData(), udLinkItem );
	if( !pLink ) return;
	
	udProjectItem *pOriginal = pLink->GetOriginal();
	if( !pOriginal ) return;
	
	udTransElementItem *pTransElement = wxDynamicCast( GetUserData(), udTransElementItem );
	if( !pTransElement ) return;
	
	IProject *pProject = IPluginManager::Get()->GetProject();
	
	if( !IsChildAccepted( pOriginal->GetClassInfo()->GetClassName()) )
	{
		wxMessageBox( wxString::Format( wxT("'%s' is not accepted by '%s'"), pOriginal->GetName().c_str(), pTransElement->GetName().c_str() ), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		return;
	}
	
	if( pOriginal->IsKindOf(CLASSINFO(udActionItem)) ||
		pOriginal->IsKindOf(CLASSINFO(udConditionItem)) ||
		pOriginal->IsKindOf(CLASSINFO(udEventItem)) )
	{
		if( pOriginal->IsKindOf(CLASSINFO(udConditionItem)) || pOriginal->IsKindOf(CLASSINFO(udEventItem)) )
		{
			pTransElement->ClearCodeItems(CLASSINFO(udConditionItem));
			pTransElement->ClearCodeItems(CLASSINFO(udEventItem));
		}
		pTransElement->AssignCodeItem( (udCodeLinkItem*)pLink->Clone() );		
	}
	else if( pLink->IsKindOf(CLASSINFO(udVariableLinkItem)) )
	{
		// clear previous condition
		pTransElement->ClearCodeItems(CLASSINFO(udConditionItem));
		pTransElement->ClearCodeItems(CLASSINFO(udEventItem));
			
		// create new instance of event flag and remove the source generic variable
		udEventItem *pNewEvt = new udEventItem( *(udEventItem*)pOriginal );
		pNewEvt->SetId( -1 );
		pNewEvt->SetName( wxT("event ") + pLink->GetName() );
		
		pProject->AddItem( pOriginal->GetParent(), pNewEvt );
		
		//IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );

		pNewEvt->UpdateSignature();
		pTransElement->AssignCodeItem( new udEventLinkItem((udCodeItem*)pNewEvt) );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewEvt, (udProjectItem*)pProject->GetRootItem() );

	}
	else if( pLink->IsKindOf(CLASSINFO(udFunctionLinkItem)) )
	{
		udAssignAsDialog dlg( GetParentCanvas());
		dlg.ShowModal();
		
		if( dlg.GetChoiceString() == wxT("Condition function") )
		{
			// clear previous condition
			pTransElement->ClearCodeItems(CLASSINFO(udConditionItem));
			pTransElement->ClearCodeItems(CLASSINFO(udEventItem));
			
			// create new instance of condition and remove the source generic function
			udConditionItem *pNewCond = new udConditionItem( *(udConditionItem*)pOriginal );
			pNewCond->SetId( -1 );
			pNewCond->SetName( wxT("condition ") + pLink->GetName() );
			
			pProject->AddItem( pOriginal->GetParent(), pNewCond );
			
			//IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );

			pNewCond->UpdateSignature();
			pTransElement->AssignCodeItem( new udConditionLinkItem((udCodeItem*)pNewCond) );
		
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewCond, (udProjectItem*)pProject->GetRootItem() );
		}
		else
		{
			// create new instance of action and remove the source generic function
			udActionItem *pNewAct = new udActionItem( *(udActionItem*)pOriginal );
			pNewAct->SetId( -1 );
			pNewAct->SetName( wxT("action ") + pLink->GetName() );
			
			pProject->AddItem( pOriginal->GetParent(), pNewAct );
			
			//IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pOriginal, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );

			pNewAct->UpdateSignature();
			pTransElement->AssignCodeItem( new udActionLinkItem((udCodeItem*)pNewAct) );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, (udProjectItem*)pProject->GetRootItem() );
		}
	}
	else if( pLink->IsKindOf( CLASSINFO(udElementLinkItem) ) ||
			 pLink->IsKindOf( CLASSINFO(udDiagramLinkItem) ) )
	{
		// FINAL STATE /////////////////////////////////////////////////////////
		
		udFinalElementItem *pFinalElement = wxDynamicCast( pOriginal, udFinalElementItem );
		if(pFinalElement)
		{
			// check whether a dropped final state belongs to the transition's source substate
			umlSubStateItem *pSrcShape = wxDynamicCast( GetShapeManager()->FindShape( GetSrcShapeId() ), umlSubStateItem );
			if( !pSrcShape ) return;
			
			udDiagramItem *pSubDiagram = ((udSubDiagramElementItem*) udPROJECT::GetDiagramElement(pSrcShape))->GetSubDiagram();
			if( !pSubDiagram->GetDiagramManager().Contains( pFinalElement->GetParent() ) )
			{
				wxMessageBox( wxT("Only final states from source sub machine can be dropped here."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
				return;
			}

			// create new condition
			udConditionItem* pCondition = (udConditionItem*)pProject->CreateProjectItem( wxT("udConditionItem"), pProject->GetRootItem()->GetId() );
			if( pCondition )
			{
				pCondition->SetName( wxT("on ") + pLink->GetName() );
				pCondition->SetInline( true );
				
				// construct condition's code
				udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
				
				wxString sRetVar = pLang->MakeValidIdentifier( pSubDiagram->GetName() ).MakeLower() + wxT("_retval ");
				
				if( pFinalElement->GetRetVal() == wxT("<default>") )
					pCondition->SetCode(sRetVar + pLang->Equal() + wxT(" ") + pOriginal->GetUniqueId( pLang ) );
				else
					pCondition->SetCode(sRetVar + pLang->Equal() + pFinalElement->GetRetVal() );
				
				// assign the link to the transition
				pCondition->UpdateSignature();
				pTransElement->AssignCodeItem( new udConditionLinkItem( pCondition ) );

				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pCondition, (udProjectItem*)pProject->GetRootItem() );
			}
		}
		
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

			// create new condition
			udActionItem* pAction = (udActionItem*)pProject->CreateProjectItem( wxT("udActionItem"), pProject->GetRootItem()->GetId() );
			if( pAction )
			{
				pAction->SetName( wxT("instantiate ") + pLink->GetName() );
				pAction->SetInline( true );
				
				udClassInstanceDialog dlg( IPluginManager::Get()->GetActiveCanvas() );
				udWindowManager dlgman( dlg, wxT("class_instance_dialog") );
				
				dlg.ShowModal();
				
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
				pTransElement->AssignCodeItem( new udActionLinkItem( pAction ) );

				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pAction, (udProjectItem*)pProject->GetRootItem() );
			}
		}
		
		// DIAGRAM AND SUBDIAGRAM ITEM //////////////////////////////////////////////////////////
		
		if( pOriginal->IsKindOf(CLASSINFO(udDiagramItem)) ||
			pOriginal->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
		{
			// find diagram wrapper if exists, otherwise create a new one
			udCodeItem *pWrapper = (udCodeItem*)pProject->GetProjectItem( CLASSINFO(udCodeItem), pOriginal->GetName() + wxT("_Wrapper") );
			if( pWrapper )
			{
				if( pWrapper->IsKindOf(CLASSINFO(udConditionItem)) )
				{
					pTransElement->ClearCodeItems(CLASSINFO(udConditionItem));
					pTransElement->ClearCodeItems(CLASSINFO(udEventItem));
					
					pTransElement->AssignCodeItem( new udConditionLinkItem( pWrapper ) );
				}
				else
					pTransElement->AssignCodeItem( new udActionLinkItem( pWrapper ) );
			}
			else
			{
				udAssignAsDialog dlg( GetParentCanvas());
				dlg.ShowModal();
			
				if( dlg.GetChoiceString() == wxT("Condition function") )
				{
					// clear previous condition
					pTransElement->ClearCodeItems(CLASSINFO(udConditionItem));
					pTransElement->ClearCodeItems(CLASSINFO(udEventItem));
				
					// create new instance of condition function
					udConditionItem *pNewCond = new udConditionItem();
					pNewCond->SetName( pOriginal->GetName() + wxT("_Wrapper") );
					pNewCond->SetRetValDataType( udLanguage::DT_USERDEFINED );
					pNewCond->SetUserRetValDataType( wxT("STATE_T") );
					pNewCond->SetImplementation( pOriginal->GetName() );
					
					pProject->AddItem( (xsSerializable*)NULL, pNewCond );
				
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewCond, (udProjectItem*)pProject->GetRootItem() );

					pNewCond->UpdateSignature();
					pTransElement->AssignCodeItem( new udConditionLinkItem((udCodeItem*)pNewCond) );
				}
				else
				{
					// create new instance of action function
					udActionItem *pNewAct = new udActionItem();
					pNewAct->SetName( pOriginal->GetName() + wxT("_Wrapper") );
					pNewAct->SetRetValDataType( udLanguage::DT_USERDEFINED );
					pNewAct->SetUserRetValDataType( wxT("STATE_T") );
					pNewAct->SetImplementation( pOriginal->GetName() );
					
					pProject->AddItem( (xsSerializable*)NULL, pNewAct );
				
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewAct, (udProjectItem*)pProject->GetRootItem() );

					pNewAct->UpdateSignature();
					pTransElement->AssignCodeItem( new udActionLinkItem((udCodeItem*)pNewAct) );
				}
			}
		}
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pTransElement, NULL, wxEmptyString, udfDELAYED );
}
