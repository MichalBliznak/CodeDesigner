/*********************************************************************
 * Name:      	ProjectBase.cpp
 * Purpose:    
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note, that preprocessor symbol WXMAKINGDLL_MYLIB
 * 				tested in defs.h file must be defined in the compiler
 * 				settings if the symbols should be exported from 
 * 				DYNAMIC library. If not defined then all declarations
 * 				will be local (usefull for STATIC library).
 *********************************************************************/
 
// include main wxWidgets header file
#include <wx/wx.h>
#include <wx/wupdlock.h>

#include "ProjectBase.h"
#include "FrameBase.h"

#include "../Ids.h"
#include "../gui/GUI.h"

// gui
#include "gui/CodeLinkDialog.h"
#include "gui/VariableDialog.h"
#include "gui/FunctionDialog.h"
#include "gui/FunctionLinkDialog.h"
#include "gui/DiagramDialog.h"
#include "gui/ElementDialog.h"

// codegen
#include "codegen/Generator.h"

using namespace wxSFCommonFcn;

DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_ADDED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_REMOVED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_SELECTED )
DEFINE_EVENT_TYPE( wxEVT_CD_TASK_REMOVE )
/*DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_ADDED )
DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_REMOVED )
DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_CHANGED )*/

IPluginManager *IPluginManager::m_PluginManager = NULL;

////////////////////////////////////////////////////////////////////////////////
// udProjectItem class /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udProjectItem, IProjectItem);

udProjectItem::udProjectItem()
{
	m_sName = wxT("");
	m_sDescription = wxT("");
	m_fMustBeUnique = true;
	
	XS_SERIALIZE(m_sName, wxT("name"));
	XS_SERIALIZE(m_sDescription, wxT("description"));
}

udProjectItem::udProjectItem(const udProjectItem& obj) : IProjectItem(obj)
{
	m_sName = obj.m_sName;
	m_sDescription = obj.m_sDescription;
	m_fMustBeUnique = obj.m_fMustBeUnique;
	
	m_arrAcceptedChild = obj.m_arrAcceptedChild;
	m_arrAcceptedSibbling = obj.m_arrAcceptedSibbling;

	XS_SERIALIZE(m_sName, wxT("name"));
	XS_SERIALIZE(m_sDescription, wxT("description"));
}

udProjectItem::~udProjectItem()
{
	IPluginManager *pManager = IPluginManager::Get();
	if( pManager )
	{
		pManager->SendProjectEvent( wxEVT_CD_ITEM_REMOVED, wxID_ANY, this );
			
		udProjectItem *pParent = wxDynamicCast( GetParent(), udProjectItem );
		if( pParent ) pManager->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pParent ); //, NULL, udfDELAYED );*/
	}
}

// virtual functions ////////////////////////////////////////////////////////////////

void udProjectItem::OnCreate()
{
}

void udProjectItem::OnCreateCopy()
{
	 this->OnTreeTextChange( IPluginManager::Get()->GetProject()->MakeUniqueName(this->GetName(), 1) );
}

void udProjectItem::OnSelection()
{
}

void udProjectItem::OnActivation()
{
}

void udProjectItem::OnContextMenu(wxWindow* parent, const wxPoint& pos)
{
	wxMenu *pPopupMenu = this->CreateMenu();
	
	if( pPopupMenu && parent )
	{
		parent->PopupMenu(pPopupMenu, pos);
	}
	
	delete pPopupMenu;
}

void udProjectItem::OnEditItem(wxWindow* parent)
{
	wxASSERT_MSG(false, wxString::Format(wxT("Properties dialog for '%s' isn't implemented yet."), this->GetClassInfo()->GetClassName()));
}

void udProjectItem::OnTreeTextChange(const wxString &txt)
{
	m_sName = txt;
}

void udProjectItem::OnShapeTextChange(const wxString &txt, udLABEL::TYPE type, int id)
{
}

bool udProjectItem::OnTreeItemBeginDrag(const wxPoint &event)
{
	// signalise that the event have been handled by this item so DnD on a parent tree should NOT be started
	
	return true;
}

void udProjectItem::OnTreeItemEndDrag(const wxPoint &pos)
{
}

wxMenu* udProjectItem::CreateMenu()
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// udLinkItem class ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udLinkItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udLinkItem::udLinkItem()
{
}

udLinkItem::udLinkItem(const udLinkItem &obj) : udProjectItem( obj )
{
}

udLinkItem::~udLinkItem()
{
}

// public virtual functions ///////////////////////////////////////////////////////

wxMenu* udLinkItem::CreateMenu()
{
    udProjectItem *pOriginal = this->GetOriginal();
    if( pOriginal ) return pOriginal->CreateMenu();
    else
        return NULL;
}

void udLinkItem::OnTreeTextChange(const wxString& txt)
{
	// do nothing
}

udProjectItem* udLinkItem::GetOriginal()
{
    return NULL;
}

void udLinkItem::OnActivation()
{
    udProjectItem *pOriginal = GetOriginal();
    if( pOriginal ) pOriginal->OnActivation();
}

void udLinkItem::OnContextMenu(wxWindow* parent, const wxPoint& pos)
{
    udProjectItem *pOriginal = GetOriginal();
	if( pOriginal ) pOriginal->OnContextMenu(parent, pos);
}

/////////////////////////////////////////////////////////////////////////////////////
// udElementLinkItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udElementLinkItem, udLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udElementLinkItem::udElementLinkItem()
{
	m_sName = wxT("Diagram element link");
	
    m_sOriginalDiagram = wxT("");
    m_sOriginalElement = wxT("");

    XS_SERIALIZE(m_sOriginalDiagram, wxT("original_diagram"));
    XS_SERIALIZE(m_sOriginalElement, wxT("original_element"));
}

udElementLinkItem::udElementLinkItem(const udElementLinkItem &obj) : udLinkItem( obj )
{
    m_sOriginalDiagram = obj.m_sOriginalDiagram;
    m_sOriginalElement = obj.m_sOriginalElement;

    XS_SERIALIZE(m_sOriginalDiagram, wxT("original_diagram"));
    XS_SERIALIZE(m_sOriginalElement, wxT("original_element"));
}

udElementLinkItem::~udElementLinkItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

udProjectItem* udElementLinkItem::GetOriginal()
{
    return IPluginManager::Get()->GetProject()->GetDiagramElement(m_sOriginalDiagram, m_sOriginalElement);
}

void udElementLinkItem::OnSelection()
{
    // get pointer to main frame and the parent shape object
	udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    wxSFShapeBase* pParentShape = (wxSFShapeBase*)GetParent();

    if(pCanvas && pParentShape)
    {
        // select the parent shape if its canvas is the active one
        if(pCanvas == pParentShape->GetParentCanvas())
        {
            pParentShape->GetParentCanvas()->DeselectAll();
            pParentShape->Select(true);
            pParentShape->GetParentCanvas()->Refresh(false);
        }
    }
}

void udElementLinkItem::OnShapeTextChange(const wxString &txt, udLABEL::TYPE type, int id)
{
	if( type == udLABEL::ltTITLE) udLABEL::SetContent( m_sName, (wxSFShapeBase*)GetParent(), udLABEL::ltTITLE );
}

void udElementLinkItem::UpdateLabels(const wxString &diagram, const wxString& element)
{
    m_sOriginalDiagram = diagram;
    m_sOriginalElement = element;

    m_sName = IPluginManager::Get()->GetProject()->MakeUniqueName( m_sOriginalDiagram + wxT(":") + m_sOriginalElement );

    wxSFShapeBase *pShape = (wxSFShapeBase*)GetParent();

    udLABEL::SetContent(GetName(), pShape, udLABEL::ltTITLE);

    pShape->Update();
    pShape->Refresh();

	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

/////////////////////////////////////////////////////////////////////////////////////
// udDiagramLinkItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDiagramLinkItem, udLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udDiagramLinkItem::udDiagramLinkItem()
{
	m_sOriginalDiagram = wxT("");
	
	XS_SERIALIZE(m_sOriginalDiagram, wxT("original_diagram"));
}

udDiagramLinkItem::udDiagramLinkItem(const udDiagramLinkItem& obj) : udLinkItem(obj)
{
	m_sOriginalDiagram = obj.m_sOriginalDiagram;
	
	XS_SERIALIZE(m_sOriginalDiagram, wxT("original_diagram"));
}

udDiagramLinkItem::~udDiagramLinkItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

udProjectItem* udDiagramLinkItem::GetOriginal()
{
	return IPluginManager::Get()->GetProject()->GetDiagram( m_sOriginalDiagram );
}

/////////////////////////////////////////////////////////////////////////////////////
// udCodeLinkItem class /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCodeLinkItem, udLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udCodeLinkItem::udCodeLinkItem()
{
	m_sName = wxT("Code item link");
    m_sOriginalCodeItem = wxT("");
	m_fMustBeUnique = false;
	m_sScope = wxT("<global>");

    XS_SERIALIZE(m_sOriginalCodeItem, wxT("original_code"));
	XS_SERIALIZE(m_sScope, wxT("scope"));
}

udCodeLinkItem::udCodeLinkItem(const udCodeItem *orig)
{
	m_sName = orig->GetName();
	m_sOriginalCodeItem = orig->GetName();
	m_fMustBeUnique = false;
	m_sScope = orig->GetScope();
	
	XS_SERIALIZE(m_sOriginalCodeItem, wxT("original_code"));
	XS_SERIALIZE(m_sScope, wxT("scope"));
}

udCodeLinkItem::udCodeLinkItem(const udCodeLinkItem &obj) : udLinkItem( obj )
{
    m_sOriginalCodeItem = obj.m_sOriginalCodeItem;
	m_sScope = obj.m_sScope;

    XS_SERIALIZE(m_sOriginalCodeItem, wxT("original_code"));
	XS_SERIALIZE(m_sScope, wxT("scope"));
}

udCodeLinkItem::~udCodeLinkItem()
{
	// update parent elements if exist
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, (udProjectItem*) wxDynamicCast( GetParent(), uddLineElement ) );
}

// virtual functions ////////////////////////////////////////////////////////////////

udProjectItem* udCodeLinkItem::GetOriginal()
{
	udProjectItem *pCodeItem;
	SerializableList lstCodeItems;
	// get all code items...
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udCodeItem), lstCodeItems );
	// ... and find matching original
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udProjectItem*)node->GetData();
		if( pCodeItem->GetName() == m_sOriginalCodeItem ) return pCodeItem;
		
		node = node->GetNext();
	}
	
    return NULL;
}

void udCodeLinkItem::OnActivation()
{
	this->OnEditItem( IPluginManager::Get()->GetMainFrame() );
}

void udCodeLinkItem::OnEditItem(wxWindow* parent)
{
	udCodeLinkDialog dlg( parent, wxDynamicCast( GetOriginal(), udCodeItem ), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("code_link_dialog") );
	
	dlg.SetCodeName( m_sName );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udCodeLinkItem::OnTreeTextChange(const wxString& txt)
{
	// this function is not called directly from tree event...
	
	udProjectItem::OnTreeTextChange( txt );
	
	// try to update parent element (if any)
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, wxDynamicCast( GetParent(), udProjectItem ), NULL, udfDELAYED );	
}

bool udCodeLinkItem::OnTreeItemBeginDrag(const wxPoint &pos)
{
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;
	
    udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    if( pCanvas )
	{
		ShapeList lstDnD;
		// create new temporary shape carying dragged data
		wxSFShapeBase *pShape = new uddDnDElement();

		// assign this link item to temporary shape
		pShape->SetUserData( (xsSerializable*)this->Clone() );

		lstDnD.Append( pShape );

		pCanvas->DoDragDrop( lstDnD, Conv2Point(pShape->GetAbsolutePosition()) );

		// delete temporary dragged shape
		delete pShape;		
	}

	return true;
}

void udCodeLinkItem::OnTreeItemEndDrag(const wxPoint &pos)
{
	udProjectItem *pTargetParent = wxDynamicCast( GetParent(), udProjectItem );

	udProjectItem *pSourceItem = IPluginManager::Get()->GetSelectedProjectItem();
	
	if( pTargetParent && pSourceItem && IsSibblingAccepted( pSourceItem->GetClassInfo()->GetClassName() ) )
	{		
		udProjectItem *pSourceParent = wxDynamicCast( pSourceItem->GetParent(), udProjectItem );
		if( pSourceParent )
		{
			int nIndex = pTargetParent->GetChildrenList().IndexOf( this );
			if( nIndex != wxNOT_FOUND )
			{
				// reparent item
				pSourceItem->Reparent( pTargetParent );
				// move the item to correct position in the new parent
				pTargetParent->GetChildrenList().DeleteObject( pSourceItem );
				pTargetParent->GetChildrenList().Insert( nIndex, pSourceItem );
			
				// update tree items and other related stuff
				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pTargetParent );
				
				if( pTargetParent != pSourceParent )
				{
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );					
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udCodeItem class /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCodeItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udCodeItem::udCodeItem()
{
	m_sCode = wxT("");
	m_fInline = false;
	m_fInverted = false;
	m_sScope = wxT("<global>");
	
	AcceptSibbling(wxT("udGenericFunctionItem"));
	AcceptSibbling(wxT("udGenericVariableItem"));
	AcceptSibbling(wxT("udActionItem"));
	AcceptSibbling(wxT("udConditionItem"));
	AcceptSibbling(wxT("udEventItem"));
	AcceptSibbling(wxT("udMemberDataItem"));
	AcceptSibbling(wxT("udMemberFunctionItem"));
	AcceptSibbling(wxT("udConstructorFunctionItem"));
	AcceptSibbling(wxT("udDestructorFunctionItem"));
	
	XS_SERIALIZE( m_sCode, wxT("code") );
	XS_SERIALIZE( m_sScope, wxT("scope") );
}

udCodeItem::udCodeItem(const udCodeItem &obj)
: udProjectItem(obj)
{	
	m_sCode = obj.m_sCode;
	m_fInline = obj.m_fInline;
	m_fInverted = obj.m_fInverted;
	m_sScope = obj.m_sScope;
	
	XS_SERIALIZE( m_sCode, wxT("code") );
	XS_SERIALIZE( m_sScope, wxT("scope") );
}

udCodeItem::~udCodeItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udCodeItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	return wxT("");
}

wxMenu* udCodeItem::CreateMenu()
{
	wxMenu *pPopupMenu = new wxMenu();
	
    pPopupMenu->Append(IDM_DELAYED_EDIT, wxT("Edit properties..."), wxT("Edit action properties."));
    pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVE, wxT("Remove code item"), wxT("Remove code item."));
	
	return pPopupMenu;
}

void udCodeItem::OnActivation()
{
	this->OnEditItem(IPluginManager::Get()->GetMainFrame() );
}

bool udCodeItem::OnTreeItemBeginDrag(const wxPoint &pos)
{
	if( this->IsKindOf( CLASSINFO(udGenericVariableItem) ) ) return DragCodeItem( new udVariableLinkItem(this) );
	else if( this->IsKindOf( CLASSINFO(udGenericFunctionItem) ) )return DragCodeItem( new udFunctionLinkItem(this) );

	return true;
}

void udCodeItem::OnTreeItemEndDrag(const wxPoint& pos)
{	
	udProjectItem *pSourceItem = IPluginManager::Get()->GetSelectedProjectItem();
	if (!pSourceItem ) return;
	
	udProjectItem *pSourceParent = wxDynamicCast( pSourceItem->GetParent(), udProjectItem );
	if ( !pSourceParent ) return;
	
	if( pSourceItem->IsKindOf(CLASSINFO(udCodeItem)) && IsSibblingAccepted(pSourceItem->GetClassInfo()->GetClassName()) )
	{
		udProjectItem *pTargetParent = wxDynamicCast( GetParent(), udProjectItem );
		if( pTargetParent )
		{
			int nIndex = pTargetParent->GetChildrenList().IndexOf( this );
			if( nIndex != wxNOT_FOUND )
			{
				// reparent item
				pSourceItem->Reparent( pTargetParent );
				// move the item to correct position in the new parent
				pTargetParent->GetChildrenList().DeleteObject( pSourceItem );
				pTargetParent->GetChildrenList().Insert( nIndex, pSourceItem );
				
				// update tree items and other related stuff
				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pTargetParent );
					
				if( pTargetParent != pSourceParent )
				{
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );
				}
			}
		}
	}
	if( pSourceItem->IsKindOf(CLASSINFO(udCodeItem)) && IsChildAccepted(pSourceItem->GetClassInfo()->GetClassName()) )
	{
		// get list of source item's successors and check whether the target item isn't in the list
		SerializableList lstChildren;
		pSourceItem->GetChildrenRecursively( CLASSINFO(udProjectItem), lstChildren );
			
		if(lstChildren.IndexOf( this ) != wxNOT_FOUND )
		{
			wxMessageBox( wxT("Couldn't move item to its successor."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
		}
		else
		{
			// reparent item
			pSourceItem->Reparent( this );

			// update tree items and other related stuffs );
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
					
			if( pSourceParent != this )
			{
				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );
			}
		}
	}
}

void udCodeItem::OnTreeTextChange(const wxString& txt)
{
	if( m_sName != txt )
	{
		udCodeLinkItem *pLink;
		wxString sPrevName = m_sName;
		
		// update linked items
		SerializableList lstLinks;
		IPluginManager::Get()->GetProject()->GetCodeLinks( udfVALID, GetClassInfo(), sPrevName, m_sScope, lstLinks );
		
		SerializableList::compatibility_iterator node = lstLinks.GetFirst();
		while( node )
		{
			pLink = (udCodeLinkItem*)node->GetData();
			
			if( pLink->GetName() == sPrevName ) pLink->OnTreeTextChange( txt );
			pLink->SetOrigCodeItem( txt );
			
			node = node->GetNext();
		}
		
		udProjectItem::OnTreeTextChange( txt );
		
		// updated specific code items
		/*// update input actions
		lstLinks.Clear();
		udSStateChartDiagramItem *pDiag;
		IPluginManager::Get()->GetProject()->GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstLinks );
		
		node = lstLinks.GetFirst();
		while( node )
		{
			pDiag = wxDynamicCast( node->GetData(), udSStateChartDiagramItem );
			if( pDiag && pDiag->GetInputAction() == sPrevName ) pDiag->SetInputAction( txt );
			node = node->GetNext();
		}*/
	}
}

// protected functions //////////////////////////////////////////////////////////////

bool udCodeItem::DragCodeItem(udCodeLinkItem *link)
{
	if( !link ) return true;
	
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;
	
    udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    if( pCanvas )
	{
		ShapeList lstDnD;
		// create new temporary shape carying dragged data
		wxSFShapeBase *pShape = new uddDnDElement();

		// assign link item to temporary shape
		pShape->SetUserData( link );

		lstDnD.Append( pShape );

		pCanvas->DoDragDrop( lstDnD, Conv2Point(pShape->GetAbsolutePosition()) );

		// delete temporary dragged shape
		delete pShape;		
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
// udVariableItem class /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udVariableItem, udCodeItem);

// constructor and destructor ///////////////////////////////////////////////////////

udVariableItem::udVariableItem()
{
	m_sName = wxT("Variable");
	m_sDescription = wxT("Variable's descritpion...");
	
	/*AcceptSibbling(wxT("udFunctionItem"));
	AcceptSibbling(wxT("udVariableItem"));
	AcceptSibbling(wxT("udActionItem"));
	AcceptSibbling(wxT("udConditionItem"));
	AcceptSibbling(wxT("udEventItem"));*/
	
	m_nValueType = udLanguage::VT_VALUE;
	m_sValue = wxT("");
	
	m_nDataType = udLanguage::DT_INT;
	m_nDataModifier = udLanguage::DM_EXTERN;
	
	m_nUserDeclPlace = dlBUILTIN;
	m_sUserDataType = wxT("");
	m_sUserDeclaration = wxT("");
	m_sUserDeclFile = wxT("");
	
	MarkSerializableDataMembers();
}

udVariableItem::udVariableItem(const udVariableItem &obj)
: udCodeItem(obj)
{
	m_nValueType = obj.m_nValueType;
	m_sValue = obj.m_sValue;
	
	m_nDataType = obj.m_nDataType;
	m_nDataModifier = obj.m_nDataModifier;

	m_nUserDeclPlace = obj.m_nUserDeclPlace;
	m_sUserDataType = obj.m_sUserDataType;
	m_sUserDeclaration = obj.m_sUserDeclaration;
	m_sUserDeclFile = obj.m_sUserDeclFile;
	
	MarkSerializableDataMembers();
}

udVariableItem::~udVariableItem()
{
}

void udVariableItem::MarkSerializableDataMembers()
{
	RemoveProperty( GetProperty(wxT("code")) );
	XS_SERIALIZE_EX(m_sValue, wxT("default_value"), wxT(""));
	XS_SERIALIZE_INT(m_nValueType, wxT("value_type"));
	XS_SERIALIZE_INT(m_nDataType, wxT("data_type"));
	XS_SERIALIZE_INT(m_nDataModifier, wxT("data_modifier"));
	XS_SERIALIZE_INT(m_nUserDeclPlace, wxT("user_decl_place"));
	XS_SERIALIZE_EX(m_sUserDataType, wxT("user_data_type"), wxT(""));
	XS_SERIALIZE_EX(m_sUserDeclaration, wxT("user_decl"), wxT(""));
	XS_SERIALIZE_EX(m_sUserDeclFile, wxT("user_decl_file"), wxT(""));
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udVariableItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	switch( format )
	{
		case udCodeItem::cfFORMAL:
			/*if( lang && !GetDataTypeString( lang ).IsEmpty() )
			{
				return m_sName + wxT(" : ") + GetDataTypeString( lang ) + lang->GetValueType(m_nValueType).Sign();
			}
			else*/
			return m_sName;
				
		case udCodeItem::cfDECLARATION:
			if( lang )
			{
				lang->PushCode();
				
				switch( m_nDataModifier )
				{
					case udLanguage::DM_STATIC:
						// do nothing
						break;
						
					case udLanguage::DM_EXTERN:
						lang->VariableDeclCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName ) );
						break;
					
					default:
						if( !m_sValue.IsEmpty() )
						{
							lang->VariableDeclAssignCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName ), m_sValue );
						}
						else
							lang->VariableDeclCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName ) );
						break;
				}
				wxString sOut = lang->GetCodeBuffer();
				
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
				return m_sName;
			
		case udCodeItem::cfDEFINITION:
			if( lang )
			{
				lang->PushCode();
				
				switch( m_nDataModifier )
				{
					case udLanguage::DM_STATIC:						
					case udLanguage::DM_EXTERN:
						if( !m_sValue.IsEmpty() )
						{
							lang->VariableDeclAssignCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName), m_sValue );
						}
						else
							lang->VariableDeclCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName) );
						break;
						
					default:
						if( !lang->HasSeparatedDecl() && !m_sValue.IsEmpty() ) lang->VariableDeclAssignCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName), m_sValue );
						break;		
				}

				wxString sOut = lang->GetCodeBuffer();
					
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
			{
				if( !m_sValue.IsEmpty() ) return m_sName + wxT(" = ") + m_sValue;
				else
					return m_sName;
			}
		
		case udCodeItem::cfCALL:
			if( lang )
			{
				return lang->MakeValidIdentifier( m_sName );
			}
			else
				return m_sName;
		
		default:
			return m_sName;
	}
}

void udVariableItem::OnEditItem(wxWindow* parent)
{
	udVariableDialog dlg( parent, IPluginManager::Get()->GetSelectedLanguage(), true );
	udWindowManager dlgman( dlg, wxT("variable_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetDataType( m_nDataType );
	dlg.SetDataModifier( m_nDataModifier );
	dlg.SetValueType( m_nValueType );
	dlg.SetDefaultValue( m_sValue );
	dlg.SetUserDeclaration( m_sUserDeclaration );
	dlg.SetUserDataType( m_sUserDataType );
	dlg.SetUserDeclFile( m_sUserDeclFile );
	dlg.SetUserDeclPlace( m_nUserDeclPlace );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nDataType = dlg.GetDataType();
		m_nDataModifier = dlg.GetDataModifier();
		m_nValueType = dlg.GetValueType();
		m_sValue = dlg.GetDefaultValue();
		m_sUserDeclaration = dlg.GetUserDeclaration();
		m_sUserDataType = dlg.GetUserDataType();
		m_sUserDeclFile = dlg.GetUserDeclFile();
		m_nUserDeclPlace = dlg.GetUserDeclPlace();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

// protected functions /////////////////////////////////////////////////////////////////

wxString udVariableItem::GetDataTypeString(CODEFORMAT format, udLanguage *lang)
{
	if( lang )
	{
		if( m_nDataType != udLanguage::DT_USERDEFINED ) 
		{
			wxString sDataType;
			
			switch( format )
			{
				case udCodeItem::cfFORMAL:
				case udCodeItem::cfDECLARATION:
					sDataType = GetModifierString( lang ) + wxT(" ") + lang->GetDataTypeString( m_nDataType ) + lang->GetValueType( m_nValueType ).Sign();
					break;
					
				case udCodeItem::cfDEFINITION:
					sDataType = lang->GetDataTypeString( m_nDataType ) + lang->GetValueType( m_nValueType ).Sign();
					break;
					
				default:
					break;
			}
			
			return sDataType.Trim(false);
		}
		else if( lang->HasUserDataType() ) return m_sUserDataType;
	}
	
	return wxEmptyString;
}

wxString udVariableItem::GetModifierString(udLanguage *lang)
{
	if( lang && (m_nDataModifier != udLanguage::DM_NONE) ) return lang->GetModifierString( m_nDataModifier );
	
	return wxEmptyString;
}

/////////////////////////////////////////////////////////////////////////////////////
// udGenericVariableItem class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udGenericVariableItem, udVariableItem);

/////////////////////////////////////////////////////////////////////////////////////
// udVariableLinkItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udVariableLinkItem, udCodeLinkItem);

/////////////////////////////////////////////////////////////////////////////////////
// udParamItem class ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udParamItem, udVariableItem);

// constructor and destructor ///////////////////////////////////////////////////////

udParamItem::udParamItem() : udVariableItem()
{
	m_fMustBeUnique = false;
	m_nDataModifier = udLanguage::DM_NONE;
	
	AcceptSibbling(wxT("udParamItem"));
}

// public virtual functions /////////////////////////////////////////////////////////

void udParamItem::OnTreeTextChange(const wxString& txt)
{
	udProjectItem::OnTreeTextChange( txt );
	
	// update parent function
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, (udProjectItem*)GetParent(), NULL, udfDELAYED );
}

wxString udParamItem::ToString(CODEFORMAT format, udLanguage* lang)
{
	switch( format )
	{
		case udCodeItem::cfFORMAL:
			return udVariableItem::ToString( format, lang );
				
		case udCodeItem::cfDECLARATION:
			if( lang )
			{
				lang->PushCode();
				
				if( m_sValue.IsEmpty() )
				{
					lang->VariableDeclCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName ) );
				}
				else
					lang->VariableDeclAssignCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName ), m_sValue );
					
				wxString sOut = lang->GetCodeBuffer();
				
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
				return m_sName;
			
		case udCodeItem::cfDEFINITION:
			if( lang )
			{
				lang->PushCode();
				
				lang->VariableDeclCmd( GetDataTypeString( format, lang ), lang->MakeValidIdentifier( m_sName) );
				wxString sOut = lang->GetCodeBuffer();
					
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
			{
				if( !m_sValue.IsEmpty() ) return m_sName + wxT(" = ") + m_sValue;
				else
					return m_sName;
			}
		
		case udCodeItem::cfCALL:
			/*if( m_sValue.IsEmpty() ) return udVariableItem::ToString( format, lang );
			else
				return m_sValue;*/
			return m_sName;
		
		default:
			return m_sName;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udFunctionItem class /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udFunctionItem, udCodeItem);

// constructor and destructor ///////////////////////////////////////////////////////

udFunctionItem::udFunctionItem()
{
	m_sName = wxT("Function");
	m_sDescription = wxT("Function's descritpion...");
	
	AcceptChild(wxT("udParamItem"));
	/*AcceptSibbling(wxT("udFunctionItem"));
	AcceptSibbling(wxT("udVariableItem"));
	AcceptSibbling(wxT("udActionItem"));
	AcceptSibbling(wxT("udConditionItem"));
	AcceptSibbling(wxT("udEventItem"));*/
	
	m_nRetValDataType = udLanguage::DT_VOID;
	m_nRetValModifier = udLanguage::DM_NONE;
	m_nRetValType = udLanguage::VT_VALUE;
	m_nUserRetValDeclPlace = udVariableItem::dlBUILTIN;
	m_sUserRetValDataType = wxT("");
	m_sUserRetValDecl = wxT("");
	m_sUserRetValDeclFile = wxT("");
	m_nFcnModifier = udLanguage::FM_NONE;
	m_sImplementation = uddvFUNCTION_USERIMPLEMENTATION;
	
	MarkSerializableDataMembers();
}

udFunctionItem::udFunctionItem(const udFunctionItem &obj)
: udCodeItem(obj)
{	
	m_nRetValDataType = obj.m_nRetValDataType;
	m_nRetValModifier = obj.m_nRetValModifier;
	m_nRetValType = obj.m_nRetValType;
	m_nUserRetValDeclPlace = obj.m_nUserRetValDeclPlace;
	m_sUserRetValDataType = obj.m_sUserRetValDataType;
	m_sUserRetValDecl = obj.m_sUserRetValDecl;
	m_sUserRetValDeclFile = obj.m_sUserRetValDeclFile;
	m_nFcnModifier = obj.m_nFcnModifier;
	m_sImplementation = obj.m_sImplementation;
	
	MarkSerializableDataMembers();
}

udFunctionItem::~udFunctionItem()
{
}

void udFunctionItem::MarkSerializableDataMembers()
{
	XS_SERIALIZE_INT(m_nRetValDataType, wxT("retval_data_type"));
	XS_SERIALIZE_INT(m_nRetValType, wxT("retval_value_type"));
	XS_SERIALIZE_INT(m_nRetValModifier, wxT("retval_data_modifier"));
	XS_SERIALIZE_INT(m_nUserRetValDeclPlace, wxT("user_retval_decl_place"));
	XS_SERIALIZE_EX(m_sUserRetValDataType, wxT("user_retval_data_type"), wxT(""));
	XS_SERIALIZE_EX(m_sUserRetValDecl, wxT("user_retval_decl"), wxT(""));
	XS_SERIALIZE_EX(m_sUserRetValDeclFile, wxT("user_retval_decl_file"), wxT(""));
	XS_SERIALIZE_INT(m_nFcnModifier, wxT("function_modifier"));
	XS_SERIALIZE_EX(m_sImplementation, wxT("function_implementation"), uddvFUNCTION_USERIMPLEMENTATION);
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udFunctionItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	wxString sParameters = GetParametersString( format, lang);
	
	// create output string
	switch( format )
	{
		case udCodeItem::cfFORMAL:
			{
				/*if( lang && !GetDataTypeString( lang ).IsEmpty() )
				{
					return  m_sName + wxT("(") + sParameters + wxT(") : ") + GetDataTypeString( lang ) + lang->GetValueType(m_nRetValType).Sign();
				}
				else*/
				return m_sName + wxT("(") + sParameters + wxT(")");
			}

		case udCodeItem::cfCALL:
			if( lang )
			{
				return lang->MakeValidIdentifier( m_sName ) + wxT("(") + sParameters + wxT(")");// + lang->Delimiter();
			}
			else
				return m_sName + wxT("(") + sParameters + wxT(")");
				
		case udCodeItem::cfDECLARATION:
			if( lang )
			{
				lang->PushCode();
				
				lang->FunctionDeclCmd( GetDataTypeString( lang ), lang->MakeValidIdentifier( m_sName ), sParameters );
				wxString sOut = lang->GetCodeBuffer();
				
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
				return m_sName + wxT("(") + sParameters + wxT(")");
				
			
		case udCodeItem::cfDEFINITION:
			if( lang )
			{
				lang->PushCode();
				
				lang->FunctionDefCmd( GetDataTypeString( lang ), lang->MakeValidIdentifier( m_sName ), sParameters );
				wxString sOut = lang->GetCodeBuffer();
				
				lang->PopCode();
				return sOut.Trim().Trim(false);
			}
			else
				return m_sName + wxT("(") + sParameters + wxT(")");
		
		default:
			return m_sName;
	}
}

void udFunctionItem::OnEditItem(wxWindow* parent)
{
	udFunctionDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("function_dialog") );
	
	udDiagramItem *pDiag = IPluginManager::Get()->GetProject()->GetDiagram( m_sImplementation );
	
	dlg.SetCodeName( m_sName );
	dlg.SetCode( m_sCode );
	dlg.SetDescription( m_sDescription );
	dlg.SetDataType( m_nRetValDataType );
	dlg.SetDataModifier( m_nRetValModifier );
	dlg.SetFcnModifier( m_nFcnModifier );
	dlg.SetValueType( m_nRetValType );
	dlg.SetUserDataType( m_sUserRetValDataType );
	dlg.SetUserDeclaration( m_sUserRetValDecl );
	dlg.SetUserDeclFile( m_sUserRetValDeclFile );
	dlg.SetUserDeclPlace( m_nUserRetValDeclPlace );
	dlg.SetImplementation( m_sImplementation );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sCode = dlg.GetCode();
		m_sDescription = dlg.GetDescription();
		m_nRetValDataType = dlg.GetDataType();
		m_nRetValType = dlg.GetValueType();
		m_nRetValModifier = dlg.GetDataModifier();
		m_nFcnModifier = dlg.GetFcnModifier();
		m_sUserRetValDataType = dlg.GetUserDataType();
		m_sUserRetValDecl = dlg.GetUserDeclaration();
		m_sUserRetValDeclFile = dlg.GetUserDeclFile();
		m_nUserRetValDeclPlace = dlg.GetUserDeclPlace();
		m_sImplementation = dlg.GetImplementation();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	if( pDiag ) IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pDiag );
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
		
}

// public functions /////////////////////////////////////////////////////////////////

wxString udFunctionItem::GetDataTypeString(udLanguage *lang)
{
	if( lang )
	{
		wxString sModifier;
		//if( m_nFcnModifier != udLanguage::FM_NONE) sModifier = lang->GetModifierString( m_nFcnModifier );
		if( m_nRetValModifier != udLanguage::DM_NONE ) sModifier << wxT(" ") << lang->GetModifierString( m_nRetValModifier );
		
		wxString sDataType;
		if( m_nRetValDataType != udLanguage::DT_USERDEFINED ) sDataType = lang->GetDataTypeString( m_nRetValDataType );
		else if( lang->HasUserDataType() ) sDataType = m_sUserRetValDataType;
		if( m_nRetValType != udLanguage::VT_VALUE ) sDataType += lang->GetValueType( m_nRetValType ).Sign();
			
		wxString sOut = sModifier + wxT(" ") + sDataType;
		return sOut.Trim().Trim(false);
	}
	else
		return wxEmptyString;
}

wxString udFunctionItem::GetModifierString(udLanguage *lang)
{
	if( lang )
	{
		wxString sModifier;
		if( m_nFcnModifier != udLanguage::FM_NONE) sModifier = lang->GetModifierString( m_nFcnModifier );
		
		return sModifier;
	}
	else
		return wxEmptyString;
}

wxString udFunctionItem::GetParametersString(CODEFORMAT format, udLanguage *lang)
{
	wxString sParameters;
	
	// get formal parameters
	udParamItem *pPar = (udParamItem*)GetFirstChild(CLASSINFO(udParamItem));
	while( pPar )
	{
		if( !sParameters.IsEmpty() ) sParameters << wxT(", ");
		sParameters << pPar->ToString(format, lang);
		
		pPar = (udParamItem*)pPar->GetSibbling(CLASSINFO(udParamItem));
	}
	if( lang && !lang->Delimiter().IsEmpty() ) sParameters.Replace( lang->Delimiter(), wxT("") );
	
	return sParameters;
}

/////////////////////////////////////////////////////////////////////////////////////
// udGenericFunctionItem class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udGenericFunctionItem, udFunctionItem);

// virtual functions ////////////////////////////////////////////////////////////////

wxString udGenericFunctionItem::ToString(udCodeItem::CODEFORMAT format, udLanguage* lang)
{
	wxString sParameters = GetParametersString( format, lang);
	
	// create output string
	switch( format )
	{
		case udCodeItem::cfFORMAL:
			return udFunctionItem::ToString( format, lang );

		case udCodeItem::cfCALL:
			if( lang )
			{
				return lang->MakeValidIdentifier( m_sName ) + wxT("(") + sParameters + wxT(")") + lang->Delimiter();
			}
			else
				return m_sName + wxT("(") + sParameters + wxT(")");
				
		case udCodeItem::cfDECLARATION:
			return udFunctionItem::ToString( format, lang );
				
			
		case udCodeItem::cfDEFINITION:
			return udFunctionItem::ToString( format, lang );
		
		default:
			return m_sName;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udFunctionLinkItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udFunctionLinkItem, udCodeLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udFunctionLinkItem::udFunctionLinkItem()
{
	XS_SERIALIZE(m_mapCallParams, wxT("call_parameters"));
}

udFunctionLinkItem::udFunctionLinkItem(const udCodeItem* orig) : udCodeLinkItem( orig )
{
	XS_SERIALIZE(m_mapCallParams, wxT("call_parameters"));
}

udFunctionLinkItem::udFunctionLinkItem(const udFunctionLinkItem& obj) : udCodeLinkItem(obj)
{
	m_mapCallParams = obj.m_mapCallParams;
	
	XS_SERIALIZE(m_mapCallParams, wxT("call_parameters"));
}

// public functions /////////////////////////////////////////////////////////////////

wxString udFunctionLinkItem::GetUpdatedFunctionCall(udCodeItem::CODEFORMAT format, udLanguage* lang)
{
	wxString sUpdParam;
	wxString sFcnCall = udCodeLinkItem::ToString( format, lang );
	
	if( this->GetOriginal() )
	{
		udParamItem *pParam = (udParamItem*)this->GetOriginal()->GetFirstChild( CLASSINFO(udParamItem) );
		while( pParam )
		{
			sUpdParam = m_mapCallParams[pParam->GetName()];
			
			if( !sUpdParam.IsEmpty() ) sFcnCall.Replace( pParam->ToString( udCodeItem::cfCALL, lang), sUpdParam );
			else
			{
				if( pParam->GetValue().IsEmpty() ) sFcnCall.Replace( pParam->GetName(), wxT("- UNDEFINED PARAMETER -") );
				else
					sFcnCall.Replace( pParam->GetName(), pParam->GetValue() );
			}
			
			pParam = (udParamItem*)pParam->GetSibbling( CLASSINFO(udParamItem) );
		}
	}
	
	return sFcnCall;
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udFunctionLinkItem::ToString(udCodeItem::CODEFORMAT format, udLanguage *lang)
{
	switch( format )
	{
		case udCodeItem::cfFORMAL:
		
		case udCodeItem::cfCALL:
			return GetUpdatedFunctionCall( format, lang );
			
		default:
			return udCodeLinkItem::ToString( format, lang );
	}
}

void udFunctionLinkItem::OnEditItem(wxWindow* parent)
{
	udFunctionLinkDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("function_link_dialog") );
	
	dlg.SetCodeName( m_sName );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udDiagramItem class //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDiagramItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udDiagramItem::udDiagramItem() : udProjectItem()
{
	m_sName = wxT("Diagram");
    m_sDiagramType = wxT("Undefined");
	m_sDescription = wxT("Diagram's description...");
	m_sOutputFile = wxT("<default>");
	m_sActiveAlgorithm = wxT("<default>");
	m_sActiveGenerator = wxT("<default>");
	
	m_fInline = false;
	m_fGenerate = true;
	
	m_pSubElement = NULL;
    m_pCurrentUMLCanvas = NULL;

    m_DiagramManager.AcceptShape(wxT("All"));
    m_DiagramManager.SetParentProjItem(this);

    XS_SERIALIZE(m_sDiagramType, wxT("diagram_type"));
	XS_SERIALIZE(m_fGenerate, wxT("generate_code"));
	XS_SERIALIZE(m_sOutputFile, wxT("output_file"));
	XS_SERIALIZE(m_fInline, wxT("inline"));
    XS_SERIALIZE(m_sActiveGenerator, wxT("active_generator"));
    XS_SERIALIZE(m_sActiveAlgorithm, wxT("active_algorithm"));
}

udDiagramItem::udDiagramItem(const udDiagramItem &obj) : udProjectItem(obj)
{
    m_sDiagramType = obj.m_sDiagramType;
	m_sOutputFile = obj.m_sOutputFile;
	m_fInline = obj.m_fInline;
	m_sActiveAlgorithm = obj.m_sActiveAlgorithm;
	m_sActiveGenerator = obj.m_sActiveGenerator;
	
	m_fInline = obj.m_fInline;
	m_fGenerate = obj.m_fGenerate;

	m_pSubElement = NULL;
	m_pCurrentUMLCanvas = NULL;
	m_DiagramManager.CopyItems(obj.m_DiagramManager);

    m_DiagramManager.SetParentProjItem(this);

    XS_SERIALIZE(m_sDiagramType, wxT("diagram_type"));
	XS_SERIALIZE(m_sDescription, wxT("description"));
	XS_SERIALIZE(m_fGenerate, wxT("generate_code"));
	XS_SERIALIZE(m_sOutputFile, wxT("output_file"));
	XS_SERIALIZE(m_fInline, wxT("inline"));
    XS_SERIALIZE(m_sActiveGenerator, wxT("active_generator"));
    XS_SERIALIZE(m_sActiveAlgorithm, wxT("active_algorithm"));
}


udDiagramItem::~udDiagramItem()
{
    CloseDiagramPage();
}

// public functions /////////////////////////////////////////////////////////////////

udDiagramCanvas* udDiagramItem::ShowDiagramPage()
{
    if( m_pCurrentUMLCanvas )
    {
        int pageIndex = IPluginManager::Get()->GetMainNotebook()->GetPageIndex( m_pCurrentUMLCanvas );
        IPluginManager::Get()->GetMainNotebook()->SetSelection(pageIndex);
    }
    else
    {
        m_pCurrentUMLCanvas = this->CreateCanvas();

        if( m_pCurrentUMLCanvas )
        {
            // assign new canvas to the diagram manager
            m_DiagramManager.SetShapeCanvas(m_pCurrentUMLCanvas);
			// update all diagram elements if changed while the canvas was hiden
			m_DiagramManager.UpdateAll();
			m_DiagramManager.UpdateAllInnerContent();
			
            m_pCurrentUMLCanvas->DeselectAll();
			
			// create new notebook page
            IPluginManager::Get()->GetMainNotebook()->AddPage( m_pCurrentUMLCanvas, m_sName, true);
			
			UpdateDiagramPageLabel();
			m_pCurrentUMLCanvas->UpdateVirtualSize();
			
			IPluginManager::Get()->ConnectDiagramEvents( m_pCurrentUMLCanvas, true );
        }
    }

    return m_pCurrentUMLCanvas;
}

void udDiagramItem::UpdateDiagramPageLabel()
{
	if( m_pCurrentUMLCanvas )
	{
		wxString sPostFix;
		int pageIndex = IPluginManager::Get()->GetMainNotebook()->GetPageIndex( m_pCurrentUMLCanvas );
	
		udFunctionItem *pFcn = IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( this );
		if( pFcn )
		{
			if( pFcn->GetScope() != wxT("<global>") )
			{
				sPostFix = wxT(" [") + pFcn->GetScope() + wxT("::") + pFcn->GetName() + wxT("]");
			}
			else
				sPostFix = wxT(" [") + pFcn->GetName() + wxT("]");
		}
		
		IPluginManager::Get()->GetMainNotebook()->SetPageText( pageIndex, m_sName + sPostFix );
	}
}

void udDiagramItem::CloseDiagramPage()
{
	// clear reference to digram canvas in diagram manager

    if( m_pCurrentUMLCanvas )
    {
		m_pCurrentUMLCanvas->DeleteAllTextCtrls();
		
		IPluginManager::Get()->GetThumbnail()->SetCanvas(NULL);
		
		IPluginManager::Get()->ConnectDiagramEvents( m_pCurrentUMLCanvas, false );

        // get index of notebook page owning the diagram
        int pageIndex = IPluginManager::Get()->GetMainNotebook()->GetPageIndex( m_pCurrentUMLCanvas );
		
		// clear reference to digram canvas in diagram manager
		m_DiagramManager.SetShapeCanvas(NULL);
		m_pCurrentUMLCanvas = NULL;
		
        // delete page without notification
       IPluginManager::Get()->GetMainNotebook()->DeletePage(pageIndex);
    }
}

void udDiagramItem::OnDestroyDiagramPage()
{
	if( m_pCurrentUMLCanvas ) m_pCurrentUMLCanvas->DeleteAllTextCtrls();
	
	IPluginManager::Get()->GetThumbnail()->SetCanvas(NULL);
	
	IPluginManager::Get()->ConnectDiagramEvents( m_pCurrentUMLCanvas, false );
		
	// clear reference to digram canvas in diagram manager
    m_DiagramManager.SetShapeCanvas(NULL);
    m_pCurrentUMLCanvas = NULL;
}

udDiagramCanvas* udDiagramItem::CreateCanvas()
{
	udDiagramCanvas *pCanvas = new udDiagramCanvas(&m_DiagramManager, IPluginManager::Get()->GetMainNotebook(), wxID_ANY);
	
	m_DiagramManager.ClearAcceptedShapes();
	
	PaletteArray *palette = m_mapElementPalettes[m_sDiagramType];
	if( palette )
	{
		for(size_t i = 0; i < palette->GetCount(); i++)
		{
			m_DiagramManager.AcceptShape(palette->Item(i).m_sClassName);
		}
	}
	
	palette = m_mapElementPalettes[udnCOMMON_ITEMS];
	for(size_t i = 0; i < palette->GetCount(); i++)
	{
		m_DiagramManager.AcceptShape(palette->Item(i).m_sClassName);
	}
	
	m_DiagramManager.AcceptShape( wxT("uddDnDElement") );
	
	return pCanvas;
}

// virtual functions ////////////////////////////////////////////////////////////////

void udDiagramItem::OnActivation()
{
    ShowDiagramPage();
}

void udDiagramItem::OnTreeTextChange(const wxString &txt)
{
	if( m_sName != txt )
	{
		wxString m_sOldName = m_sName;
		
		// update 'linked' functions
		udFunctionItem *pFcn;
		while( (pFcn = IPluginManager::Get()->GetProject()->GetFunctionImplementedBy( this )) )
		{
			pFcn->SetImplementation( txt );
		}

		// update diagram mane and page title
		udProjectItem::OnTreeTextChange(txt);
		UpdateDiagramPageLabel();

		// update linked items
		SerializableList lstLinks;
		udElementLinkItem *pLink;

		IPluginManager::Get()->GetProject()->GetElementLinks( m_sOldName, wxT(""), lstLinks );
		SerializableList::compatibility_iterator node = lstLinks.GetFirst();
		while( node )
		{
			pLink = (udElementLinkItem*)node->GetData();
			pLink->UpdateLabels( m_sName, pLink->GetOrigElement());

			node = node->GetNext();
		}
	}
}

bool udDiagramItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	// only top diagrams can be moved
	//if( this->IsKindOf( CLASSINFO(udSubDiagramItem) ) ) return true;
	if( m_pSubElement ) return true;
	
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;

    udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    if( !pCanvas )return true;

    ShapeList lstDnD;

    // drop new subdiagram as a linked diagram element
    udDiagramLinkItem *pLink = new udDiagramLinkItem();

    pLink->SetOrigDiagram( GetName() );
	pLink->SetName( GetName() );
 	
	// create new temporary shape carying dragged data
	wxSFShapeBase *pShape = new uddDnDElement();

	// assign link item to temporary shape
	pShape->SetUserData( pLink );

	lstDnD.Append( pShape );

	pCanvas->DoDragDrop( lstDnD, Conv2Point(pShape->GetAbsolutePosition()) );

	// delete temporary dragged shape
	delete pShape;	
	
	return true;

}

wxXmlNode* udDiagramItem::Serialize(wxXmlNode* node)
{
    if( node )
    {
        // serialize standard defined properties
        node = udProjectItem::Serialize(node);

        // serialize non-standard properties
		wxXmlNode* chart = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("diagram"));
		m_DiagramManager.SerializeObjects(m_DiagramManager.GetRootItem(), chart, false);
		node->AddChild(chart);
    }

	return node;
}

void udDiagramItem::Deserialize(wxXmlNode* node)
{
    wxASSERT(node);
    if(!node)return;

    // deserialize standard defined properties
    udProjectItem::Deserialize(node);

    // deserialize non-standard properties	
    wxXmlNode *propNode = node->GetChildren();
	while(propNode)
	{
		if(propNode->GetName() == wxT("diagram"))
		{
		    m_DiagramManager.DeserializeObjects(NULL, propNode);
		}
		propNode = propNode->GetNext();
	}
}

void udDiagramItem::OnEditItem(wxWindow* parent)
{
	udDiagramDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("diagram_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetInline( m_fInline );
	dlg.SetGenerateCode( m_fGenerate );
	dlg.SetOutputFile( m_sOutputFile );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_fInline = dlg.GetInline();
		m_fGenerate = dlg.GetGenerateCode();
		
		if( dlg.GetOutputFile().Contains( wxT(".") ) )
		{
			m_sOutputFile = dlg.GetOutputFile().BeforeLast( '.' );
		}
		else
			m_sOutputFile = dlg.GetOutputFile();
		
		udGenerator *pGen = udPROJECT::CreateGenerator( dlg.GetGenerator() );
		if(pGen)
		{
			SetActiveGenerator( pGen->GetClassInfo()->GetClassName() );
			
			udAlgorithm *pAlg = pGen->FindAlgorithm( dlg.GetAlgorithm() );
			if(pAlg)
			{
				SetActiveAlgorithm( pAlg->GetClassInfo()->GetClassName() );
			}
			
			delete pGen;
		}
		else
		{
			SetActiveGenerator(wxT(""));
			SetActiveAlgorithm(wxT(""));
		}
			
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udDiagramItem::GetSpecificCodeItems( wxClassInfo *type, SerializableList& codeitems )
{
	// override it if neccessary
}

// protected functions //////////////////////////////////////////////////////////////

wxMenu* udDiagramItem::CreateMenu()
{
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
	// create popup menu
	wxMenu *pPopupMenu = new wxMenu();
	
    pPopupMenu->Append(IDM_DIAG_SHOW, wxT("Show diagram"), wxT("Show diagram."));

	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, IDM_DIAG_SHOWPREVIEW, wxT("Code preview"));
	//pItem->SetBitmap(udArt::GetBitmap(wxT("udICON_PREVIEW")));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/spellcheck.png"), wxBITMAP_TYPE_ANY));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();
	
	pPopupMenu->Append(IDM_DIAG_STORETOBANK, wxT("Store to bank"));
	
	pPopupMenu->AppendSeparator();

    pPopupMenu->Append(IDM_DELAYED_EDIT, wxT("Edit properties..."), wxT("Edit diagram properties."));
	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVE, wxT("Remove diagram"), wxT("Remove diagram and all included items."));
	
	return pPopupMenu;
}

/////////////////////////////////////////////////////////////////////////////////////
// udDiagElementItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDiagElementItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udDiagElementItem::udDiagElementItem() : udProjectItem()
{
	SetId( 0 );
	
    m_sName = wxT("Diagram element");
	m_sDescription = wxT("Diagram element's description...");
}

udDiagElementItem::udDiagElementItem(const udDiagElementItem &obj) : udProjectItem(obj)
{
}

udDiagElementItem::~udDiagElementItem()
{
}

// public functions ////////////////////////////////////////////////////////////////

udDiagramItem* udDiagElementItem::GetParentDiagram()
{
    wxSFShapeBase *pParentShape = wxDynamicCast( GetParent(), wxSFShapeBase );
    if( pParentShape )
    {
        udDiagramManager *pManager = wxDynamicCast( pParentShape->GetParentManager(), udDiagramManager );
        if( pManager ) return (udDiagramItem*) pManager->GetParentProjItem();
    }

    return NULL;
}

/*long udDiagElementItem::GetFreeId()
{
	long nId = 0;
	bool fUsed;
	
	do
	{
		fUsed = false;
		nId++;
		
		for( SerializableList::iterator it = m_lstChildItems.begin(); it != m_lstChildItems.end(); ++it )
		{
			if( (*it)->GetId() == nId )
			{
				fUsed = true;
				break;
			}
		}
	}
	while( fUsed );
	
	return nId;
}*/

void udDiagElementItem::AssignCodeItem(udProjectItem* item)
{
	/*if( item )
	{
		udCodeItem *pOriginal = NULL;
		
		if( item->IsKindOf( CLASSINFO(udCodeLinkItem) ) ) pOriginal = (udCodeItem*)((udCodeLinkItem*)item)->GetOriginal();
		else
			pOriginal = wxDynamicCast( item, udCodeItem );
			
		if( pOriginal )
		{
			// assign give code link to the diagram element
			//item->SetId( GetFreeId() );
			AddChild( item );
		}
	}*/
		
	if( item )
	{
		// assign give code link to the diagram element
		AddChild( item );
	}
}

void udDiagElementItem::ClearCodeItems( wxClassInfo *origtype )
{
	udCodeItem *pOriginal;
	udProjectItem *pItem;
	
	IPluginManager::Get()->EnableInternalEvents(false);
	
	SerializableList::compatibility_iterator node = GetFirstChildNode();
	while( node ) 
	{
		pItem = (udProjectItem*) node->GetData();
		
		// find original project item encapsulated by the node
		if( pItem->IsKindOf( CLASSINFO(udCodeLinkItem) ) )
		{			
			pOriginal = (udCodeItem*)((udCodeLinkItem*) pItem)->GetOriginal();
		}
		else
			pOriginal = wxDynamicCast( pItem, udCodeItem );

		// if the original matches given item type then remove the object from this transition
		if( pOriginal && ( pOriginal->IsKindOf( origtype ) ) )
		{
			delete pItem;
			GetChildrenList().DeleteNode( node );
			
			node = GetFirstChildNode();
		}
		else
			node = node->GetNext();
	}
	
	IPluginManager::Get()->EnableInternalEvents(true);
}

void udDiagElementItem::GetCodeItems(wxClassInfo* type, SerializableList& list, bool original)
{
	udCodeLinkItem *pLink;
	xsSerializable *pCodeItem;
	
	SerializableList::compatibility_iterator pNode = GetFirstChildNode();
	while( pNode )
	{
		pCodeItem = pNode->GetData();
		// try to find original action item first ...
		if( pCodeItem->IsKindOf( type ) ) list.Append( pCodeItem );
		else
		{
			// ... or link to action item
			pLink = wxDynamicCast( pCodeItem, udCodeLinkItem );
			if( pLink )
			{
				pCodeItem = pLink->GetOriginal();
				if( pCodeItem && pCodeItem->IsKindOf( type ) )
				{
					if( original ) list.Append( pCodeItem );
					else
						list.Append( pLink );
				}
			}
		}
		
		pNode = pNode->GetNext();
	}
}

udProjectItem* udDiagElementItem::GetCodeItem(wxClassInfo* type, const wxString& name, bool original)
{
	udProjectItem *pItem;
	
	SerializableList lstCodeItems;
	GetCodeItems( type, lstCodeItems, original );
	
	for( SerializableList::iterator it = lstCodeItems.begin(); it != lstCodeItems.end(); ++it )
	{
		pItem = (udProjectItem*) *it;
		if( pItem->GetName() == name ) return pItem;
	}
	
	return NULL;
}

void udDiagElementItem::RestoreCallParams()
{
	wxString sFcnName, sParamName;
	udFunctionLinkItem *pFcnLink;
	
	for( StringMap::iterator it = m_mapStoredCallParams.begin(); it != m_mapStoredCallParams.end(); ++it )
	{
		sFcnName = it->first.BeforeFirst(':');
		sParamName = it->first.AfterFirst(':');
		
		pFcnLink = wxDynamicCast( GetCodeItem( CLASSINFO(udFunctionLinkItem), sFcnName ), udFunctionLinkItem );
		if( pFcnLink )
		{
			pFcnLink->GetCallParams()[sParamName] = it->second;
		}
	}
}

void udDiagElementItem::StoreCallParams()
{
	m_mapStoredCallParams.clear();
	
	udFunctionLinkItem *pFcnLink = (udFunctionLinkItem*) GetFirstChild( CLASSINFO(udFunctionLinkItem) );
	while( pFcnLink )
	{
		for( StringMap::iterator it = pFcnLink->GetCallParams().begin(); it != pFcnLink->GetCallParams().end(); ++it )
		{
			m_mapStoredCallParams[ wxString::Format( wxT("%s:%s"), pFcnLink->GetName().c_str(), it->first.c_str() )] = it->second;
		}
		
		pFcnLink = (udFunctionLinkItem*) pFcnLink->GetSibbling( CLASSINFO(udFunctionLinkItem) );
	}
}

wxString udDiagElementItem::RemoveCallParams(const wxString& txt)
{
	int nBraceCount = 0;
	
	wxString sOut;
	wxChar cZn;
	
	for( size_t i = 0; i < txt.Len(); i++ )
	{
		cZn = txt.GetChar(i);
		if( cZn == '(' ) nBraceCount++;
		else if( cZn == ')' ) nBraceCount--;
		else if( nBraceCount == 0 ) sOut += cZn;
	}
	
	return sOut;
}

// virtual functions ////////////////////////////////////////////////////////////////

void udDiagElementItem::OnActivation()
{
	udDiagramItem *pDiag = GetParentDiagram();
	
    if( pDiag )
	{
		if( !pDiag->GetDiagramPage() )
		{
			pDiag->ShowDiagramPage();
		}
		else
			this->OnEditItem( pDiag->GetDiagramPage() );
			
		if( IPluginManager::Get()->IsProjManLinked() ) pDiag->GetDiagramPage()->ScrollToShape((wxSFShapeBase*)GetParent());
	}
	
    OnSelection();
}

void udDiagElementItem::OnSelection()
{
    // get pointer to main frame and the parent shape object
	udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    wxSFShapeBase *pParentShape = (wxSFShapeBase*)GetParent();

    if(pCanvas && pParentShape)
    {
        // select the parent shape if its canvas is the active one
        if(pCanvas == pParentShape->GetParentCanvas())
        {
            pParentShape->GetParentCanvas()->DeselectAll();
            pParentShape->Select(true);
            pParentShape->GetParentCanvas()->Refresh(false);
        }
    }
}

void udDiagElementItem::OnEditItem(wxWindow* parent)
{
	udElementDialog dlg( parent, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("element_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

void udDiagElementItem::OnTreeTextChange(const wxString &txt)
{
	if( m_sName != txt )
	{
		wxString sPrevName = m_sName;
		
		udProjectItem::OnTreeTextChange(txt);
		
		wxSFShapeBase *pParentShape = (wxSFShapeBase*)GetParent();
		if( pParentShape )
		{
			udLABEL::SetContent(txt, pParentShape, udLABEL::ltTITLE);
			// refresh canvas
			pParentShape->Update();
			if( IPluginManager::Get()->GetActiveCanvas() ) IPluginManager::Get()->GetActiveCanvas()->Refresh(false);
		}

		// update linked items
		SerializableList lstLinks;
		udElementLinkItem *pLink;

		IPluginManager::Get()->GetProject()->GetElementLinks( wxT(""), m_sName, lstLinks );
		SerializableList::compatibility_iterator node = lstLinks.GetFirst();
		while( node )
		{
			pLink = (udElementLinkItem*)node->GetData();
			pLink->UpdateLabels( pLink->GetOrigDiagram(), sPrevName);

			node = node->GetNext();
		}
		
		// update code items
		udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
		wxString sCurrentID = wxT("ID_") + pLang->MakeValidIdentifier( sPrevName ).Upper();
		wxString sNewID = wxT("ID_") + pLang->MakeValidIdentifier( txt ).Upper();

		wxString sBuff;
		lstLinks.Clear();
		IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udCodeItem), lstLinks );
		node = lstLinks.GetFirst();
		while( node )
		{
			udCodeItem *pCI = wxDynamicCast(node->GetData(), udCodeItem);
			if( pCI )
			{

				sBuff = pCI->GetCode();
				sBuff.Replace( sCurrentID, sNewID ) ;
				pCI->SetCode( sBuff );
			}
			node = node->GetNext();
		}
	}
}

bool udDiagElementItem::OnTreeItemBeginDrag(const wxPoint &pos)
{
	// if a shift key is pressed down then cancel the operation
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return true;
	
    wxASSERT(GetParent());
    if( !GetParent() )return true;

    udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    if( !pCanvas )return true;

    ShapeList lstDnD;
    wxSFShapeBase *pOrigShape = (wxSFShapeBase*)GetParent();

    // drop new subdiagram as a linked diagram element
    udElementLinkItem *pLink = new udElementLinkItem();

    pLink->SetOrigElement( GetName() );
    pLink->SetOrigDiagram( ((udDiagramManager*)pOrigShape->GetParentManager())->GetParentProjItem()->GetName() );
	pLink->SetName( GetName() );
    //pLink->SetName( wxString::Format(wxT("%d"), udProject::OccurenceCount( pLink->GetOrigDiagram() + wxT(":") + pLink->GetOrigElement() ) + 1) );
	
	// create new temporary shape carying dragged data
	wxSFShapeBase *pShape;
	if( cState.ControlDown() )
	{
		 // create temporary dragged element
		pShape = (wxSFShapeBase*)pOrigShape->Clone();
		pShape->SetId( -1 );

		/*udLABEL::SetContent( pLink->GetName(), pShape, pOrigShape->GetParentManager(), udLABEL::ltTITLE );
		// remove original project data and replace it with new link data
		delete pShape->GetUserData();
		pShape->SetUserData( pLink );*/
	}
	else
	{
		pShape = new uddDnDElement();

		// assign link item to temporary shape
		pShape->SetUserData( pLink );
	}
	
	lstDnD.Append( pShape );

	pCanvas->DoDragDrop( lstDnD, Conv2Point(pShape->GetAbsolutePosition()) );

	// delete temporary dragged shape
	delete pShape;	
	
	return true;
}

void udDiagElementItem::OnTreeItemEndDrag(const wxPoint &pos)
{
	udCodeLinkItem *pSourceItem = wxDynamicCast(IPluginManager::Get()->GetSelectedProjectItem(), udCodeLinkItem );
	
	if( pSourceItem && IsChildAccepted(pSourceItem->GetClassInfo()->GetClassName()) )
	{
		udProjectItem *pSourceParent = wxDynamicCast( pSourceItem->GetParent(), udProjectItem );
		if( pSourceParent )
		{
			// reparent item
			pSourceItem->Reparent( this );

			// update tree items and other related stuff
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
				
			if( pSourceParent != this )
			{
				IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );
			}
		}
	}
}

void udDiagElementItem::OnShapeTextChange(const wxString &txt, udLABEL::TYPE type, int id)
{
	if( type == udLABEL::ltTITLE)
	{
		wxString utxt = IPluginManager::Get()->GetProject()->MakeUniqueName(txt);
		if( utxt != txt )
		{
			udLABEL::SetContent(utxt, (wxSFShapeBase*)GetParent(), udLABEL::ltTITLE);
		}

		udProjectItem::OnTreeTextChange(utxt);
	}
}

wxMenu* udDiagElementItem::CreateMenu()
{	
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
	// create popup menu	
	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, wxID_COPY, wxT("Copy\tCtrl+C"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_ANY));
	pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(pPopupMenu, IDM_DELAYED_CUTELEMENT, wxT("Cut\tCtrl+X"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_ANY));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_EDITELEMENT, wxT("Edit properties..."), wxT("Edit diagram element"));

	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVEELEMENT, wxT("Remove element"), wxT("Remove diagram element"));
	
	return pPopupMenu;
}

void udDiagElementItem::OnContextMenu(wxWindow* parent, const wxPoint& pos)
{
	// re-create this menu due to possible updates
	wxMenu *pPopupMenu = this->CreateMenu();
	
	// update element's context menu
	if( pPopupMenu && parent )
	{
		wxSFShapeBase *pShape = wxDynamicCast( GetParent(), wxSFShapeBase );
		if( pShape &&
			parent->IsKindOf( CLASSINFO(udDiagramCanvas) ) &&
			!pShape->GetAcceptedConnections().IsEmpty() )
		{
			wxMenu *pSubmenu;

			int nCreateID = pPopupMenu->FindItem( wxT("Create") );
			if( nCreateID == wxNOT_FOUND )
			{
				// create new "Create" submenu
				pSubmenu =  new wxMenu();
				
				pPopupMenu->Insert( 0, wxID_ANY, wxT("Create"), pSubmenu );
				pPopupMenu->InsertSeparator( 1 );
			}
			else
				pSubmenu = pPopupMenu->FindItem( nCreateID )->GetSubMenu();
				
			if( pSubmenu->GetMenuItemCount() ) pSubmenu->AppendSeparator();
			
			if( pShape->GetAcceptedChildren().Index( wxT("All") ) == wxNOT_FOUND )
			{
				if( UpdateSubmenu(pSubmenu, pShape->GetAcceptedChildren(), udfDONT_CLEAR_CONTENT) ) pSubmenu->AppendSeparator();
			}
			else
			{
				wxArrayString arrComponents;
				// diagram-specific items
				PaletteArray *palette = m_mapElementPalettes[IPluginManager::Get()->GetActiveDiagram()->GetDiagramType()];
				for( size_t i = 0; i < palette->GetCount(); i++)
				{
					udPaletteItem *pPaletteItem = &palette->Item(i);
					if( pPaletteItem->m_nType == udPaletteItem::pitELEMENT ) arrComponents.Add( pPaletteItem->m_sClassName );
				}
				// common items
				palette = m_mapElementPalettes[wxT("Common Items")];
				for( size_t i = 0; i < palette->GetCount(); i++)
				{
					udPaletteItem *pPaletteItem = &palette->Item(i);
					if( pPaletteItem->m_nType == udPaletteItem::pitELEMENT ) arrComponents.Add( pPaletteItem->m_sClassName );
				}
				if( UpdateSubmenu(pSubmenu, arrComponents, udfDONT_CLEAR_CONTENT) ) pSubmenu->AppendSeparator();
			}
			
			UpdateSubmenu(pSubmenu, pShape->GetAcceptedConnections(), udfDONT_CLEAR_CONTENT);
		}
		else
		{
			pPopupMenu->Insert(0, IDM_DIAG_NAVIGATETO, wxT("Navigate to element"), wxT("Scroll the diagram so the element will be in its center"));
			pPopupMenu->InsertSeparator(1);
		}
		
		parent->PopupMenu(pPopupMenu, pos);
	}
	
	delete pPopupMenu;
}

bool udDiagElementItem::UpdateSubmenu(wxMenu* submenu, const wxArrayString& items, bool clear)
{
	wxASSERT(submenu);
	if( !submenu )return 0;

	wxMenuItem *pItem;
	int nCount = 0;

	// delete previous menu content
	if( clear )
	{
        while( submenu->GetMenuItemCount() > 0 )
        {
            pItem = submenu->FindItemByPosition(0);
            submenu->Destroy(pItem);
        }
	}

	// create new menu items from the palette info
	udPaletteItem *pPaletteItem;

	for( size_t i = 0; i < items.GetCount(); i++)
	{
		pPaletteItem = GetPaletteTool(items[i]);
		if( pPaletteItem )
		{
			pItem = new wxMenuItem(submenu, pPaletteItem->m_nId + 1000, pPaletteItem->m_sDesc);
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(pPaletteItem->m_sClassName));
			submenu->Append(pItem);
			nCount++;
		}
	}
	return nCount;
}

wxXmlNode* udDiagElementItem::Serialize(wxXmlNode* node)
{
    if( node )
    {
        // serialize standard defined properties
        node = udProjectItem::Serialize(node);

        // serialize code items links (cannot be serialized in a standard way because they are children
		// of user-data item appended to a transition shape )
		IPluginManager::Get()->GetProject()->SerializeObjects( this, node, false );
    }

	return node;
}

void udDiagElementItem::Deserialize(wxXmlNode* node)
{
    wxASSERT(node);
    if(!node)return;

    // deserialize standard defined properties
    udProjectItem::Deserialize(node);

    // deserialize non-standard properties (code items links)
	IPluginManager::Get()->GetProject()->DeserializeObjects( this, node );
}


/////////////////////////////////////////////////////////////////////////////////////
// udSubDiagramElementItem class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udSubDiagramElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udSubDiagramElementItem::udSubDiagramElementItem() : udDiagElementItem()
{
	// inherited class must properly create relevat diagram item here...
}

udSubDiagramElementItem::udSubDiagramElementItem(const udSubDiagramElementItem &obj)
: udDiagElementItem(obj)
{
	m_pSubDiagram = (udDiagramItem*)obj.m_pSubDiagram->Clone();
	m_pSubDiagram->SetSubdiagramElement(this);

    XS_SERIALIZE_DYNAMIC_OBJECT_NO_CREATE(m_pSubDiagram, wxT("subdiagram"));
}

udSubDiagramElementItem::~udSubDiagramElementItem()
{
	if( m_pSubDiagram ) IPluginManager::Get()->GetProject()->RemoveItem( m_pSubDiagram );
}

void udSubDiagramElementItem::OnActivation()
{
    m_pSubDiagram->OnActivation();
}

void udSubDiagramElementItem::OnCreate()
{
	udDiagramItem *pParent = GetParentDiagram();
	if( pParent )
	{
		//m_pSubDiagram->SetDiagram( (udDiagramItem*) wxCreateDynamicObject( pParent->GetClassInfo()->GetClassName() ) );
		m_pSubDiagram->SetName( m_sName );
		m_pSubDiagram->SetDiagramType( pParent->GetDiagramType() );
	}
}

void udSubDiagramElementItem::OnTreeTextChange(const wxString &txt)
{
	udDiagElementItem::OnTreeTextChange(txt);

	// create also name of encapsulated diagram
	m_pSubDiagram->OnTreeTextChange(txt);
}

void udSubDiagramElementItem::OnShapeTextChange(const wxString &txt, udLABEL::TYPE type, int id)
{
	udDiagElementItem::OnShapeTextChange(txt, type, id);

	// create also name of encapsulated diagram
	m_pSubDiagram->OnTreeTextChange(m_sName);
}

bool udSubDiagramElementItem::OnTreeItemBeginDrag(const wxPoint &pos)
{
	// if a shift key is pressed down then cancel the operation
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return true;
	
    wxASSERT(GetParent());
    if( !GetParent() )return true;

    udDiagramCanvas *pCanvas = IPluginManager::Get()->GetActiveCanvas();
    if( !pCanvas )return true;

    ShapeList lstDnD;
    wxSFShapeBase *pOrigShape = (wxSFShapeBase*)GetParent();

    // drop new subdiagram as a linked diagram element
    udElementLinkItem *pLink = new udElementLinkItem();

    pLink->SetOrigElement( GetName() );
    pLink->SetOrigDiagram( ((udDiagramManager*)pOrigShape->GetParentManager())->GetParentProjItem()->GetName() );
    //pLink->SetName( wxString::Format(wxT("%d"), udProject::OccurenceCount( pLink->GetOrigDiagram() + wxT(":") + pLink->GetOrigElement() ) + 1) );
    pLink->SetName( pLink->GetOrigDiagram() + wxT(":") + pLink->GetOrigElement() );

    // create temporary dragged element
    wxSFShapeBase *pShape = (wxSFShapeBase*)pOrigShape->Clone();
    pShape->SetId( -1 );

    udLABEL::SetContent( pLink->GetName(), pShape, pOrigShape->GetParentManager(), udLABEL::ltTITLE );
    // remove original project data and replace it with new link data
    delete pShape->GetUserData();
    pShape->SetUserData( pLink );

    lstDnD.Append( pShape );

    pCanvas->DoDragDrop( lstDnD, Conv2Point(pShape->GetAbsolutePosition()) );

    // delete temporary dragged element
    delete pShape;
	
	return true;
}

// protected functions //////////////////////////////////////////////////////////////

wxMenu* udSubDiagramElementItem::CreateMenu()
{
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
    // create popup menu
	
	wxMenu *pPopupMenu = udDiagElementItem::CreateMenu();
	
    pPopupMenu->Insert(0, IDM_DIAG_SHOW, wxT("Show diagram"), wxT("Show diagram."));

	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, IDM_DIAG_SHOWPREVIEW, wxT("Code preview"));
	//pItem->SetBitmap(udArt::GetBitmap(wxT("udICON_PREVIEW")));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/spellcheck.png"), wxBITMAP_TYPE_ANY));
	pPopupMenu->Insert(1, pItem);

	pPopupMenu->InsertSeparator(2);
	
	pPopupMenu->Insert(3, IDM_DIAG_STORETOBANK, wxT("Store to bank"));
	
	pPopupMenu->InsertSeparator(4);
	
	return pPopupMenu;
}
