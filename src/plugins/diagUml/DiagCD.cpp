#include "DiagCD.h"

#include <wx/textdlg.h>
#include <wx/regex.h>
#include <wx/artprov.h>

#include "projectbase/gui/AccessTypeDialog.h"
#include "projectbase/gui/UpdateCodeDialog.h"
#include "projectbase/gui/ScopedElementDialog.h"
#include "gui/ClassMemberLinkDialog.h"
#include "gui/ConstructorDialog.h"
#include "gui/DestructorDialog.h"
#include "gui/ClassTemplDialog.h"
#include "gui/EnumElementDialog.h"
#include "gui/EnumDialog.h"
#include "gui/ClassDialog.h"
#include "gui/AggregationDialog.h"
#include "Ids.h"
#include "DiagIds.h"
#include "shapes/ClassDiagram.h"
#include "shapes/classdiagram/ClassTemplItem.h"
#include "shapes/classdiagram/TemplateBindItem.h"
#include "shapes/classdiagram/EnumItem.h"

#include <wx/wxsf/wxShapeFramework.h>

// TODO: Implement class element's properties dialog

/////////////////////////////////////////////////////////////////////////////////////
// udClassDiagramItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udClassDiagramItem, udDiagramItem);

// constructor and destructor ///////////////////////////////////////////////////////

udClassDiagramItem::udClassDiagramItem()
{
    m_sDiagramType = udnCLASS_DIAGRAM;
    SetName(udnCLASS_DIAGRAM);

    m_sActiveGenerator = wxT("udClassDiagramGenerator");
    m_sActiveAlgorithm = wxT("udCPPClassAlgorithm");
}

udClassDiagramItem::udClassDiagramItem(const udClassDiagramItem &obj)
: udDiagramItem(obj)
{
    m_sDiagramType = udnCLASS_DIAGRAM;
}

udClassDiagramItem::~udClassDiagramItem()
{
}

udDiagramCanvas* udClassDiagramItem::CreateCanvas()
{
    //return new umlClassDiagram(&m_DiagramManager, IPluginManager::Get()->GetMainNotebook(), wxID_ANY);
	return udDiagramItem::CreateCanvas();
}

/////////////////////////////////////////////////////////////////////////////////////
// udClassElementItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udClassElementItem, udDiagElementItem);

udClassElementItem::udClassElementItem()
{
	m_Generate = true;
	
	AcceptChild(wxT("udMemberDataLinkItem"));
	AcceptChild(wxT("udMemberFunctionLinkItem"));
	
	XS_SERIALIZE(m_Generate, wxT("generate_code"));
}

udClassElementItem::udClassElementItem(const udClassElementItem& obj)
: udDiagElementItem(obj)
{
	m_Generate = obj.m_Generate;
	
	XS_SERIALIZE(m_Generate, wxT("generate_code"));
}

// public functions /////////////////////////////////////////////////////////////////

void udClassElementItem::SetFunctionString(const wxString& txt, int id)
{
	// get updated function
	SerializableList lstFunctions;
	GetCodeItems(CLASSINFO(udMemberFunctionLinkItem), lstFunctions);
	
	udMemberDataLinkItem *pFcnLink = NULL;
	SerializableList::compatibility_iterator node = lstFunctions.GetFirst();
	while( node )
	{
		pFcnLink = (udMemberDataLinkItem*)node->GetData();
		if( pFcnLink->GetOriginal() && (pFcnLink->GetOriginal()->GetId() == id) ) break;
		else
			pFcnLink = NULL;
		node = node->GetNext();
	}
	
	if( pFcnLink )
	{
		// remove the function from the class if new description is empty
		if( txt == wxEmptyString )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pFcnLink, this, wxEmptyString, udfDELAYED );
		}
		else
		{
			// set new/modify variable
			wxString sAccess, sFunction, sRegex = wxT("^[\\+\\-#]\\s[a-zA-Z0-9_\\s\\(\\):]*[:]?[a-zA-Z0-9_\\s]*$");
			wxRegEx reGuard( sRegex, wxRE_ADVANCED);
			
			if( reGuard.Matches( txt ) )
			{				
				sAccess = txt.BeforeFirst(' ');
				sFunction = txt.AfterFirst(' ');
				
				// set access type
				sAccess.Trim().Trim(false);
				
				udLanguage::ACCESSTYPE nAccessType = udLanguage::AT_PUBLIC;
				if( sAccess == wxT("#") ) nAccessType = udLanguage::AT_PROTECTED;
				else if( sAccess == wxT("-") ) nAccessType = udLanguage::AT_PRIVATE;
				
				// try to find function with this name
				sFunction = sFunction.BeforeFirst('(');
				sFunction.Trim().Trim(false);
				
				udMemberFunctionItem *pFunction = (udMemberFunctionItem*) IPluginManager::Get()->GetProject()->GetCodeItem( CLASSINFO(udMemberFunctionItem), sFunction, m_sName );
					
				// create a link to function and assign it to this transition
				if( pFunction )
				{
					AssignCodeItem( new udMemberFunctionLinkItem(pFunction, nAccessType) );
					
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pFcnLink, this, wxEmptyString, udfDELAYED );
				}
				else
				{
					if( wxMessageBox( wxString::Format( wxT("Class function member with name '%s' doesn't exist in this scope yet. Would you like to create one?"), sFunction.c_str() ), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION  ) == wxYES )
					{
						udProjectItem *pRoot =  (udProjectItem*) IPluginManager::Get()->GetProject()->GetRootItem();
						// create new function
						udMemberFunctionItem* pNewFcn = (udMemberFunctionItem*) IPluginManager::Get()->GetProject()->CreateProjectItem( wxT("udMemberFunctionItem"), pRoot->GetId() );
						// create relevant tree item
						if( pNewFcn )
						{
							pNewFcn->SetName( sFunction );
							pNewFcn->SetScope( m_sName );
							
							udAccessTypeDialog dlg( IPluginManager::Get()->GetMainFrame() );
							dlg.ShowModal();
							
							// assign the link to selected class item
							AssignCodeItem( new udMemberFunctionLinkItem(pNewFcn, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );

							IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pFcnLink, this, wxEmptyString, udfDELAYED );
							IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewFcn, pRoot, wxEmptyString, udfDELAYED );
						}
					}
				}
			}
			else
				wxMessageBox( wxString::Format( wxT("Function '%s' doesn't match the allowed form '%s'."), txt.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		}
	}
}

void udClassElementItem::SetVariableString(const wxString& txt, int id)
{
	// get updated variable
	SerializableList lstVariables;
	GetCodeItems(CLASSINFO(udMemberDataLinkItem), lstVariables);
	
	udMemberDataLinkItem *pVarLink = NULL;
	SerializableList::compatibility_iterator node = lstVariables.GetFirst();
	while( node )
	{
		pVarLink = (udMemberDataLinkItem*)node->GetData();
		if( pVarLink->GetOriginal() && (pVarLink->GetOriginal()->GetId() == id) ) break;
		else
			pVarLink = NULL;
		node = node->GetNext();
	}
	
	if( pVarLink )
	{
		// remove the variable from the class if txt is empty
		if( txt == wxEmptyString )
		{
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pVarLink, this, wxEmptyString, udfDELAYED );
		}
		else
		{
			// set new/modify variable
			wxString sAccess, sVariable, sRegex = wxT("^[\\+\\-#]\\s[a-zA-Z0-9_\\s]*[:]?[a-zA-Z0-9_\\s=]*$");
			wxRegEx reGuard( sRegex, wxRE_ADVANCED);
			
			if( reGuard.Matches( txt ) )
			{				
				sAccess = txt.BeforeFirst(' ');
				sVariable = txt.AfterFirst(' ');
				
				// set access type
				sAccess.Trim().Trim(false);
				
				udLanguage::ACCESSTYPE nAccessType = udLanguage::AT_PUBLIC;
				if( sAccess == wxT("#") ) nAccessType = udLanguage::AT_PROTECTED;
				else if( sAccess == wxT("-") ) nAccessType = udLanguage::AT_PRIVATE;
				
				// try to find variable with this name
				if( sVariable.Contains(wxT(":")) ) sVariable = sVariable.BeforeFirst(':');
				sVariable.Trim().Trim(false);
				
				udMemberDataItem *pVariable = (udMemberDataItem*) IPluginManager::Get()->GetProject()->GetCodeItem( CLASSINFO(udMemberDataItem), sVariable, m_sName );
					
				// create copy of matched variable and assign it to the class
				if( pVariable )
				{
					AssignCodeItem( new udMemberDataLinkItem(pVariable, nAccessType) );
					
					IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pVarLink, this, wxEmptyString, udfDELAYED );
				}
				else
				{
					if( wxMessageBox( wxString::Format( wxT("Class data member with name '%s' doesn't exist in this scope yet. Would you like to create one?"), sVariable.c_str() ), wxT("CodeDesigner"), wxYES_NO | wxICON_QUESTION  ) == wxYES )
					{
						udProjectItem *pRoot =  (udProjectItem*) IPluginManager::Get()->GetProject()->GetRootItem();
						// create new condition
						udMemberDataItem* pNewVar = (udMemberDataItem*) IPluginManager::Get()->GetProject()->CreateProjectItem( wxT("udMemberDataItem"), pRoot->GetId() );
						// create relevant tree item
						if( pNewVar )
						{
							pNewVar->SetName( sVariable );
							pNewVar->SetScope( m_sName );
							
							udAccessTypeDialog dlg(IPluginManager::Get()->GetMainFrame() );
							dlg.ShowModal();
							
							// assign the link to selected class item
							AssignCodeItem( new udMemberDataLinkItem(pNewVar, (udLanguage::ACCESSTYPE)dlg.GetChoice()) );

							IPluginManager::Get()->SendProjectEvent( wxEVT_CD_TASK_REMOVE, wxID_ANY, pVarLink, this, wxEmptyString, udfDELAYED );
							IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewVar, pRoot, wxEmptyString, udfDELAYED );
						}
					}
				}
			}
			else
				wxMessageBox( wxString::Format( wxT("Variable '%s' doesn't match the allowed form '%s'."), txt.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		}
	}
}

// public virtual functions /////////////////////////////////////////////////////////

wxMenu* udClassElementItem::CreateMenu()
{	
	const wxString &sAppPath = IPluginManager::Get()->GetResourcesPath();
	
    // create popup menu

	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenu *pCreateSubMenu = new wxMenu();
	
	pCreateSubMenu->Append( IDM_CLASS_CREATECONSTRUCTOR, wxT("Create constructor") );
	pCreateSubMenu->Append( IDM_CLASS_CREATEDESTRUCTOR, wxT("Create destructor") );
	
	pCreateSubMenu->AppendSeparator();
	
	wxMenuItem *pItem = new wxMenuItem(pCreateSubMenu, IDM_CLASS_CREATEVARIABLE, wxT("Member variable"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udMemberDataItem")));
	pCreateSubMenu->Append(pItem);
	
	pItem = new wxMenuItem(pCreateSubMenu, IDM_CLASS_CREATEFUNCTION, wxT("Member function"));
	pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(wxT("udMemberFunctionItem")));
	pCreateSubMenu->Append(pItem);

    pPopupMenu->Append(wxID_ANY, wxT("Create"), pCreateSubMenu);
	
	// insert available variables
	udCodeItem *pProjItem;
	int nId = 0;
	
	wxMenu *pAssignSubMenu = new wxMenu();
	
	SerializableList lstItems;
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udMemberDataItem), lstItems);
	SerializableList::compatibility_iterator node = lstItems.GetFirst();
	while(node)
	{
		pProjItem = (udCodeItem*)node->GetData();
		
		if( !udPROJECT::GetProjectItem(this, CLASSINFO(udCodeLinkItem), pProjItem->GetName()) && 
			!pProjItem->IsKindOf(CLASSINFO(udParamItem)) &&
			(pProjItem->GetScope() == m_sName) )
		{
			pItem = new wxMenuItem(pAssignSubMenu, IDM_DIAG_ASSIGNVARIABLE + nId++, pProjItem->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(pProjItem->GetClassInfo()->GetClassName()));
			pAssignSubMenu->Append(pItem);
			
			if( nId > udvMAX_ITEMS ) break;
		}
		node = node->GetNext();
	}
	if( nId ) pPopupMenu->Append(wxID_ANY, wxT("Assign member variable"), pAssignSubMenu);
	
	// insert available functions
	nId = 0;
	pAssignSubMenu = new wxMenu();
	
	lstItems.Clear();
	IPluginManager::Get()->GetProject()->GetItems(CLASSINFO(udMemberFunctionItem), lstItems);
	node = lstItems.GetFirst();
	while(node)
	{
		pProjItem = (udCodeItem*)node->GetData();
		
		if( !udPROJECT::GetProjectItem(this, CLASSINFO(udCodeLinkItem), pProjItem->GetName()) &&
			(pProjItem->GetScope() == m_sName) )
		{
			pItem = new wxMenuItem(pAssignSubMenu, IDM_DIAG_ASSIGNFUNCTION + nId++, ((udProjectItem*)node->GetData())->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
			pAssignSubMenu->Append(pItem);
			
			if( nId > udvMAX_ITEMS ) break;
		}
		node = node->GetNext();
	}
	if( nId ) pPopupMenu->Append(wxID_ANY, wxT("Assign member function"), pAssignSubMenu);
	
	pPopupMenu->AppendSeparator();
	
	if( HasChildren() )
	{
		nId = 0;
		wxMenu *pEditSubMenu = new wxMenu();
		// insert assigned code items
		lstItems.Clear();
		GetCodeItems(CLASSINFO(udCodeItem), lstItems);
		SerializableList::compatibility_iterator node = lstItems.GetFirst();
		while(node)
		{
			wxMenuItem *pItem = new wxMenuItem(pEditSubMenu, IDM_DELAYED_EDITCODE + nId++, ((udProjectItem*)node->GetData())->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
			pEditSubMenu->Append(pItem);
		
			if( nId > udvMAX_ITEMS ) break;
		
			node = node->GetNext();
		}
		
		pPopupMenu->Append(wxID_ANY, wxT("Edit"), pEditSubMenu);
		pPopupMenu->AppendSeparator();
	}	
	
	pPopupMenu->Append(IDM_DIAG_CLEARVARIABLES, wxT("Clear member variables"));
	pPopupMenu->Append(IDM_DIAG_CLEARFUNCTIONS, wxT("Clear member functions"));
	
	pPopupMenu->AppendSeparator();
	
	// create popup menu	
	pItem = new wxMenuItem(pPopupMenu, wxID_COPY, wxT("Copy\tCtrl+C"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcopy.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(pPopupMenu, IDM_DELAYED_CUTELEMENT, wxT("Cut\tCtrl+X"));
	//pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU));
	pItem->SetBitmap(wxBitmap(sAppPath + wxT("app/gui/editcut.png"), wxBITMAP_TYPE_PNG));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_EDITELEMENT, wxT("Edit properties..."), wxT("Edit diagram element"));
	pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVEELEMENT, wxT("Remove element"), wxT("Remove diagram element"));
	
	return pPopupMenu;
}

void udClassElementItem::UpdateInnerContent()
{
	udProjectItem *pOriginal;
	
	udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
	
	// clear all text ctrls
	umlClassItem *pClassShape = wxDynamicCast( GetParent(), umlClassItem );
	if( pClassShape )
	{
		pClassShape->ClearVariableCtrls();
		pClassShape->ClearFunctionCtrls();
	
		// create text controls for member data
		udMemberDataLinkItem *pVar = (udMemberDataLinkItem*)GetFirstChild( CLASSINFO(udMemberDataLinkItem) );
		while( pVar )
		{
			pOriginal = pVar->GetOriginal();
			if( pOriginal )
			{
				pClassShape->CreateVariableCtrl( pVar->ToString(udCodeItem::cfFORMAL, pLang), pOriginal->GetId() );
			}
			pVar = (udMemberDataLinkItem*)pVar->GetSibbling( CLASSINFO(udMemberDataLinkItem) );
		}
		
		// create text controls for member functions
		udMemberFunctionLinkItem *pFcn = (udMemberFunctionLinkItem*)GetFirstChild( CLASSINFO(udMemberFunctionLinkItem) );
		while( pFcn )
		{
			pOriginal = pFcn->GetOriginal();
			if( pOriginal )
			{
				pClassShape->CreateFunctionCtrl( pFcn->ToString(udCodeItem::cfFORMAL, pLang), pOriginal->GetId() );
			}
			pFcn = (udMemberFunctionLinkItem*)pFcn->GetSibbling( CLASSINFO(udMemberFunctionLinkItem) );
		}
	}
}

void udClassElementItem::OnTreeItemEndDrag(const wxPoint &pos)
{
	udCodeLinkItem *pSourceItem = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udCodeLinkItem );
	if( !pSourceItem ) return;
	
	udProjectItem *pPresentItem = udPROJECT::GetProjectItem(this, CLASSINFO(udCodeLinkItem), pSourceItem->GetName());
	
	// only one instance of each code item is allowed in class element
	if( !pPresentItem || (pPresentItem == pSourceItem) )
	{
		// check also scope of dropped code link
		if( pSourceItem->GetScope() != GetName() )
		{
			wxMessageBox( wxT("The code link cannot be used in this scope."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		}
		else
			udDiagElementItem::OnTreeItemEndDrag(pos);
	}
}

void udClassElementItem::OnTreeTextChange(const wxString& txt)
{
	if( m_sName != txt )
	{
		wxString sPrevName = m_sName;
		
		udDiagElementItem::OnTreeTextChange( txt );
		
		UpdateMembers( sPrevName, m_sName );
	}
}

void udClassElementItem::OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id)
{
	switch( type )
	{
		case udLABEL::ltTITLE:
		{
			wxString sPrevName = m_sName;
			
			udDiagElementItem::OnShapeTextChange( txt, type, id );
			
			UpdateMembers( sPrevName, m_sName );
		}
		break;
			
		case udLABEL::ltCLASS_VARIABLES:
			SetVariableString( txt, id - udvID_OFFSET );
			break;
			
		case udLABEL::ltCLASS_FUNCTIONS:
			SetFunctionString( txt, id - udvID_OFFSET );
			break;
			
		default:
			break;
	}
}

void udClassElementItem::OnCreateCopy()
{
	// get all assigned code links
	SerializableList lstLinks;
	GetCodeItems( CLASSINFO(udMemberLinkItem), lstLinks );
	
	// remove current codelinks
	GetChildrenList().Clear();
	
	// rename the class item
//	udDiagElementItem::OnTreeTextChange( IPluginManager::Get()->GetProject()->MakeUniqueName( GetName(), 1 ) );
	udDiagElementItem::OnTreeTextChange( GetUniqueName( GetName() ) );
	
	// create copy of previously stored code links (if don't exist)
	for( SerializableList::iterator it = lstLinks.begin(); it != lstLinks.end(); ++it )
	{
		udMemberLinkItem *pLink = (udMemberLinkItem*)*it;
		// try to find original code item in updated scope
		udCodeItem *pOriginal = IPluginManager::Get()->GetProject()->GetCodeItem( CLASSINFO(udCodeItem), pLink->GetOrigCodeItem(), GetName() );
		
		if( !pOriginal )
		{
			AssignMemberCopy( pLink );
		}
		else
		{
			if( pLink->IsKindOf( CLASSINFO(udMemberDataLinkItem) ) )
			{
				AssignCodeItem( new udMemberDataLinkItem( pOriginal, pLink->GetAccessType() ) );
			}
			else if( pLink->IsKindOf( CLASSINFO(udMemberFunctionLinkItem) ) )
			{
				AssignCodeItem( new udMemberFunctionLinkItem( pOriginal, pLink->GetAccessType()) );
			}
		}
	}
	
	UpdateMembers( m_sName, m_sName );
	
	// remove old code links
	lstLinks.DeleteContents( true );
	lstLinks.Clear();
}

void udClassElementItem::OnEditItem(wxWindow* parent)
{
	udClassDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("class_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetGenerate( m_Generate );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_Generate = dlg.GetGenerate();
		m_sDescription = dlg.GetDescription();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

// protected function ///////////////////////////////////////////////////////////////

void udClassElementItem::UpdateMembers(const wxString& prevname, const wxString& newname)
{
	// update also class members
	SerializableList lstMembers;
	IProject *pProj = IPluginManager::Get()->GetProject();
	
	pProj->GetItems(CLASSINFO(udMemberDataItem), lstMembers);
	for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
	{
		if( ((udMemberDataItem*)*it)->GetScope() == prevname )
		{
			((udMemberDataItem*)*it)->SetScope( newname );
			((udMemberDataItem*)*it)->UpdateSignature();
		}
	}
	
	lstMembers.Clear();
	pProj->GetItems(CLASSINFO(udMemberFunctionItem), lstMembers);
	for( SerializableList::iterator it = lstMembers.begin(); it != lstMembers.end(); ++it )
	{
		udMemberFunctionItem *pFcn = (udMemberFunctionItem*)*it;
		if( pFcn->GetScope() == prevname )
		{
			pFcn->SetScope( newname );
			pFcn->UpdateSignature();
			
			for( SerializableList::iterator it2 = pFcn->GetChildrenList().begin(); it2 != pFcn->GetChildrenList().end(); ++ it2 )
			{
				udParamItem *pPar = wxDynamicCast( *it2, udParamItem );
				if( pPar )
				{
					pPar->SetScope( pFcn->GetScope() + wxT("::") + pFcn->GetName() );
					pPar->UpdateSignature();
				}
			}
		}
	}
	
	// update links
	wxString sSignature;
	SerializableList::compatibility_iterator node = GetFirstChildNode();
	while( node )
	{
		udCodeLinkItem *cl = (udCodeLinkItem*) node->GetData();
		cl->SetScope( newname );
		sSignature = cl->GetOrigCodeItem();
		sSignature.Replace( prevname + wxT("::"), newname + wxT("::") );
		cl->SetOrigCodeItem( sSignature );
		node = node->GetNext();
	}
	
	// update referenced code
	SerializableList m_References;
	udPROJECT::FindCodeReferences( prevname, m_References );
	
	if( !m_References.IsEmpty() )
	{
		udUpdateCodeDialog dlg( IPluginManager::Get()->GetActiveCanvas(), &m_References, IPluginManager::Get()->GetSelectedLanguage() );
		udWindowManager dlgman( dlg, wxT("update_code_dialog") );
	
		dlg.SetPattern( prevname );
		dlg.SetNewPattern( newname );
		dlg.ShowModal();
	}
}

void udClassElementItem::AssignMemberCopy(udLinkItem* link)
{
	udCodeItem *pNewItem = NULL;
	udCodeItem *pOriginal = (udCodeItem*)link->GetOriginal();
	
	if( !pOriginal ) return;
	
	udLanguage::ACCESSTYPE nAccess = udLanguage::AT_PUBLIC;
	
	// try to retrieve access type
	if( link->IsKindOf( CLASSINFO(udMemberLinkItem) ) )
	{
		nAccess = ((udMemberLinkItem*)link)->GetAccessType();
	}
	else
	{
		udAccessTypeDialog dlg( IPluginManager::Get()->GetActiveCanvas() );
		dlg.ShowModal();
		
		nAccess = (udLanguage::ACCESSTYPE) dlg.GetChoice();
	}
	
	// create new instance of class data member
	if( pOriginal->IsKindOf( CLASSINFO(udConstructorFunctionItem) ) )
	{
		pNewItem = new udConstructorFunctionItem( *(udConstructorFunctionItem*)pOriginal );
	}
	else if( pOriginal->IsKindOf( CLASSINFO(udDestructorFunctionItem) ) )
	{
		pNewItem = new udDestructorFunctionItem( *(udDestructorFunctionItem*)pOriginal );
	}
	else if( pOriginal->IsKindOf( CLASSINFO(udVariableItem) ) )
	{
		pNewItem = new udMemberDataItem( *(udVariableItem*)pOriginal );
	}
	else if( pOriginal->IsKindOf( CLASSINFO(udFunctionItem) ) )
	{
		pNewItem = new udMemberFunctionItem( *(udFunctionItem*)pOriginal );
	}
	
	pNewItem->SetScope( GetName() );
	// reset id (so new one will be created later)
	pNewItem->SetId( -1 );
	IPluginManager::Get()->GetProject()->AddItem( pOriginal->GetParent(), pNewItem );
	pNewItem->UpdateSignature();
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_ADDED, wxID_ANY, pNewItem, (udProjectItem*)pOriginal->GetParent(), wxEmptyString, udfDELAYED );
		
	if( link->IsKindOf( CLASSINFO(udMemberDataLinkItem) ) || link->IsKindOf( CLASSINFO(udVariableLinkItem) ) )
	{
		AssignCodeItem( new udMemberDataLinkItem( pNewItem, nAccess ) );
	}
	else if( link->IsKindOf( CLASSINFO(udMemberFunctionLinkItem) ) || link->IsKindOf( CLASSINFO(udFunctionLinkItem) ) )
	{
		AssignCodeItem( new udMemberFunctionLinkItem( pNewItem, nAccess) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udClassTemplateElementItem class /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udClassTemplateElementItem, udClassElementItem);

udClassTemplateElementItem::udClassTemplateElementItem()
{	
	m_TemplateName = wxT("Template");
	
	XS_SERIALIZE( m_TemplateName, wxT("template_typename") );
}

// public virtual functions /////////////////////////////////////////////////////////

void udClassTemplateElementItem::OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id)
{
	switch( type )
	{			
		case udLABEL::ltCLASS_TEMPLATE:
			{
				m_TemplateName = txt;
			}
			break;
			
		default:
			udClassElementItem::OnShapeTextChange(txt, type, id);
			break;
	}
}

void udClassTemplateElementItem::OnEditItem(wxWindow* parent)
{
	udClassTemplateDialog dlg( parent, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("class_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetTemplateName( m_TemplateName );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_TemplateName = dlg.GetTemplateName();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udClassTemplateElementItem::UpdateInnerContent()
{
	// clear all text ctrls
	umlClassTemplateItem *pClassShape = wxDynamicCast( GetParent(), umlClassTemplateItem );
	if( pClassShape )
	{
		udClassElementItem::UpdateInnerContent();
		
		// update template
		pClassShape->UpdateTemplateCtrl( m_TemplateName );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udBiAssocElementItem class ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udBiAssocElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udUniAssocElementItem class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udUniAssocElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udBaseAggregElementItem class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udBaseAggregElementItem, udIncludeAssocElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udBaseAggregElementItem::udBaseAggregElementItem()
{
	m_IncludeClass = false;
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
	XS_SERIALIZE( m_IncludeClass, wxT("include_target_class") );
}

udBaseAggregElementItem::udBaseAggregElementItem(const udBaseAggregElementItem& obj)
: udIncludeAssocElementItem( obj )
{
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
	XS_SERIALIZE( m_IncludeClass, wxT("include_target_class") );
}

udBaseAggregElementItem::~udBaseAggregElementItem()
{
}

// public virtual functions /////////////////////////////////////////////////////////

/*wxMenu* udBaseAggregElementItem::CreateMenu()
{
	wxMenu *pMenu = udDiagElementItem::CreateMenu();
	
	pMenu->Insert( 0, wxID_ANY, wxT("Access"), CreateAccessMenu() );
	
	return pMenu;
}*/

void udBaseAggregElementItem::OnEditItem(wxWindow* parent)
{
	udAggregationDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("aggregation_element_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetAccessType( (int)m_nAccessType );
	dlg.SetIncludeClass( m_IncludeClass );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nAccessType = (udLanguage::ACCESSTYPE)dlg.GetAccessType();
		m_IncludeClass = dlg.GetIncludeClass();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udCompAggregElementItem class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCompAggregElementItem, udIncludeAssocElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udCompAggregElementItem::udCompAggregElementItem()
{
	m_IncludeClass = false;
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
	XS_SERIALIZE( m_IncludeClass, wxT("include_target_class") );
}

udCompAggregElementItem::udCompAggregElementItem(const udCompAggregElementItem& obj)
: udIncludeAssocElementItem( obj )
{
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
	XS_SERIALIZE( m_IncludeClass, wxT("include_target_class") );
}

udCompAggregElementItem::~udCompAggregElementItem()
{
}

// public virtual functions /////////////////////////////////////////////////////////

/*wxMenu* udCompAggregElementItem::CreateMenu()
{
	wxMenu *pMenu = udDiagElementItem::CreateMenu();
	
	pMenu->Insert( 0, wxID_ANY, wxT("Access"), CreateAccessMenu() );
	
	return pMenu;
}*/

void udCompAggregElementItem::OnEditItem(wxWindow* parent)
{
	udAggregationDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("aggregation_element_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetAccessType( (int)m_nAccessType );
	dlg.SetIncludeClass( m_IncludeClass );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nAccessType = (udLanguage::ACCESSTYPE)dlg.GetAccessType();
		m_IncludeClass = dlg.GetIncludeClass();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udInherElementItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udInherElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udInterElementItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udInterElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udTemplateBindElementItem class //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udTemplateBindElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udTemplateBindElementItem::udTemplateBindElementItem()
{
	m_BindType = wxT("");
	
	XS_SERIALIZE( m_BindType, wxT("bind_type") );
}

// public functions /////////////////////////////////////////////////////////////////

void udTemplateBindElementItem::SetBindTypeString(const wxString& txt)
{
	wxString sRegex = wxT("^<[\\s]*[a-zA-Z0-9_]*[\\s]*>$");
	wxRegEx reGuard( sRegex, wxRE_ADVANCED);
			
	if( reGuard.Matches( txt ) )
	{	
		m_BindType = txt;
		
		m_BindType.Replace( wxT("<"), wxT("") );
		m_BindType.Replace( wxT(">"), wxT("") );
		m_BindType.Trim().Trim(false);
	}
	else
	{
		umlTemplateBindItem *pLine = (umlTemplateBindItem*) GetParent();
		pLine->GetLabel(udLABEL::ltGUARD_CONTENT)->SetText( wxT("<") + m_BindType + wxT(">") );
		
		wxMessageBox( wxString::Format( wxT("Bind type '%s' doesn't match the allowed form '%s'."), txt.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
	}
}

// public virtual functions /////////////////////////////////////////////////////////

void udTemplateBindElementItem::OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id)
{
	switch( type )
	{
		/*case udLABEL::ltTITLE:
		{
			umlTemplateBindItem *pLine = (umlTemplateBindItem*) GetParent();
			pLine->GetLabel(udLABEL::ltTITLE)->SetText( wxT("<< bind >>") );
		}
		break;*/
			
		case udLABEL::ltGUARD_CONTENT:
			SetBindTypeString(txt);
			break;
			
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udEnumElementItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udEnumElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udEnumElementItem::udEnumElementItem()
{
	AcceptChild( wxT("udEnumValueItem") );
	
	XS_SERIALIZE( m_InstanceName, wxT("instance_name") );
}

udEnumElementItem::udEnumElementItem(const udEnumElementItem& obj) : udDiagElementItem( obj )
{
	m_InstanceName = obj.m_InstanceName;
	
	XS_SERIALIZE( m_InstanceName, wxT("instance_name") );
}

udEnumElementItem::~udEnumElementItem()
{
}

// public functions /////////////////////////////////////////////////////////////////

void udEnumElementItem::AddElementString(const wxString& element)
{
	wxString key, val;
	
	if( CheckElementString( element, key, val ) )
	{
		udEnumValueItem *pEnumVal = new udEnumValueItem();
		pEnumVal->SetName( key );
		pEnumVal->SetValue( val );
		
		AssignCodeItem( pEnumVal );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

void udEnumElementItem::SetElementString(const wxString& element, int id)
{
	wxString key, val;
	
	if( CheckElementString( element, key, val ) )
	{
		// find element with given id
		udEnumValueItem *pElement = wxDynamicCast( GetChildrenList().Item( id )->GetData(), udEnumValueItem );
		if( pElement )
		{
			pElement->SetName( key );
			pElement->SetValue( val );
		}
	}
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this, NULL, wxEmptyString, udfDELAYED );
}

// public virtual functions /////////////////////////////////////////////////////////

wxMenu* udEnumElementItem::CreateMenu()
{
	int nIndex = 0;
	
	wxMenu *pMenu = udDiagElementItem::CreateMenu();
	
	pMenu->Insert(nIndex++, IDM_ENUM_ADDELEMENT, wxT("Add element"));

	if( HasChildren() )
	{
		int nId = 0;
		wxMenu *pEditSubMenu = new wxMenu();
		// insert assigned enumeration elements
		SerializableList::compatibility_iterator node = GetFirstChildNode();
		while(node)
		{
			wxMenuItem *pItem = new wxMenuItem(pEditSubMenu, IDM_DELAYED_EDITCODE + nId++, ((udProjectItem*)node->GetData())->GetName());
			pItem->SetBitmap(IPluginManager::Get()->GetArtBitmap(node->GetData()->GetClassInfo()->GetClassName()));
			pEditSubMenu->Append(pItem);
		
			if( nId > udvMAX_ITEMS ) break;
		
			node = node->GetNext();
		}
		
		pMenu->Insert(nIndex++, wxID_ANY, wxT("Edit"), pEditSubMenu);
	}
	
	pMenu->InsertSeparator(nIndex++);
	pMenu->Insert(nIndex++, IDM_ENUM_CLEARELEMENTS, wxT("Clear all elements"));
	pMenu->InsertSeparator(nIndex++);
	
	return pMenu;
}

void udEnumElementItem::OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id)
{
	switch( type )
	{
		case udLABEL::ltENUM_ELEMENT:
			SetElementString( txt, id - udvID_OFFSET );
			break;
			
		default:
			udDiagElementItem::OnShapeTextChange( txt, type, id );
	}
}

void udEnumElementItem::UpdateInnerContent()
{
	// clear all text ctrls
	umlEnumItem *pEnumShape = wxDynamicCast( GetParent(), umlEnumItem );
	if( pEnumShape )
	{
		udLanguage *pLang = IPluginManager::Get()->GetSelectedLanguage();
		
		pEnumShape->ClearElementCtrls();
	
		// create text controls for enumeration elements
		int nId = 0;
		udEnumValueItem *pEnum = (udEnumValueItem*)GetFirstChild( CLASSINFO(udEnumValueItem) );
		while( pEnum )
		{
			pEnumShape->CreateElementCtrl( pEnum->ToString(udCodeItem::cfFORMAL, pLang), nId++ );
			
			pEnum = (udEnumValueItem*)pEnum->GetSibbling( CLASSINFO(udEnumValueItem) );
		}
	}
}

void udEnumElementItem::OnEditItem(wxWindow* parent)
{
	udEnumDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("enum_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetInstanceName( m_InstanceName );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_InstanceName = dlg.GetInstanceName();
		m_sDescription = dlg.GetDescription();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

// protected functions //////////////////////////////////////////////////////////////

bool udEnumElementItem::CheckElementString(const wxString& element, wxString& key, wxString& val)
{
	wxString sRegex = wxT("^[a-zA-Z]+[a-zA-Z0-9_\\s]*=?[a-zA-Z0-9_\\s]*$");
	wxRegEx reGuard( sRegex, wxRE_ADVANCED);
			
	if( reGuard.Matches( element ) )
	{	
		if( element.Contains( wxT("=") ) )
		{
			key = element.BeforeFirst( '=' );
			key.Trim().Trim(false);
			
			val = element.AfterFirst( '=' );
			val.Trim().Trim(false);
		}
		else
		{
			key = element;
			key.Trim().Trim(false);
		}
		return true;
	}
	else
	{
		wxMessageBox( wxString::Format( wxT("Element '%s' doesn't match the allowed form '%s'."), element.c_str(), sRegex.c_str() ), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udIncludeAssocElementItem class //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udIncludeAssocElementItem, udDiagElementItem);

// constructor and destructor ///////////////////////////////////////////////////////

udIncludeAssocElementItem::udIncludeAssocElementItem()
{
	m_IncludeClass = true;
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
}

udIncludeAssocElementItem::udIncludeAssocElementItem(const udIncludeAssocElementItem& obj)
: udDiagElementItem( obj )
{
	m_IncludeClass = obj.m_IncludeClass;
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
}

udIncludeAssocElementItem::~udIncludeAssocElementItem()
{
}

// public virtual functions /////////////////////////////////////////////////////////

wxMenu* udIncludeAssocElementItem::CreateMenu()
{
	wxMenu *pMenu = udDiagElementItem::CreateMenu();
	
	pMenu->Insert( 0, wxID_ANY, wxT("Access"), CreateAccessMenu() );
	
	return pMenu;
}

void udIncludeAssocElementItem::OnEditItem(wxWindow* parent)
{
	udScopedElementDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("scoped_element_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetAccessType( (int)m_nAccessType );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sDescription = dlg.GetDescription();
		m_nAccessType = (udLanguage::ACCESSTYPE)dlg.GetAccessType();
		
		OnTreeTextChange( dlg.GetCodeName() );
		
		IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udMemberLinkItem /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udMemberLinkItem, udCodeLinkItem);

// constructor and destructor ///////////////////////////////////////////////////////

udMemberLinkItem::udMemberLinkItem()
{
	AcceptSibbling(wxT("udMemberDataLinkItem"));
	AcceptSibbling(wxT("udMemberFunctionLinkItem"));
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
}

udMemberLinkItem::udMemberLinkItem(const udCodeItem *orig, udLanguage::ACCESSTYPE at )
{
	SetName( orig->GetName() );
	SetOrigCodeItem( orig->GetSignature() );
	SetScope( orig->GetScope() );
	SetAccessType( at );
	
	AcceptSibbling(wxT("udMemberDataLinkItem"));
	AcceptSibbling(wxT("udMemberFunctionLinkItem"));
	
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
}

udMemberLinkItem::udMemberLinkItem(const udMemberLinkItem& obj) : udCodeLinkItem(obj)
{
	XS_SERIALIZE_INT( m_nAccessType, wxT("access_type") );
}

udMemberLinkItem::~udMemberLinkItem()
{
}

// public virtual functions /////////////////////////////////////////////////////////

wxMenu* udMemberLinkItem::CreateMenu()
{
	udCodeItem* pOrig = wxDynamicCast( GetOriginal(), udCodeItem );
	if( pOrig )
	{
		wxMenu *pMenu = GetOriginal()->CreateMenu();
		
		pMenu->Insert(0, wxID_ANY, wxT("Access"), CreateAccessMenu() );
		pMenu->InsertSeparator(1);
		
		return pMenu;
	}
	else
		return NULL;
}

udProjectItem* udMemberLinkItem::GetOriginal()
{
	udCodeItem *pCodeItem;
	SerializableList lstCodeItems;
	
	// try to fix parent class name if missing... (probably due to usage of old-dated project file).
	if( m_sScope.IsEmpty() )
	{
		udClassElementItem *pClassElement = wxDynamicCast( GetParent(), udClassElementItem );
		if( pClassElement ) m_sScope = pClassElement->GetName();
	}
	
	// get all code items...
	IPluginManager::Get()->GetProject()->GetItems( CLASSINFO(udCodeItem), lstCodeItems );
	// ... and find matching original
	SerializableList::compatibility_iterator node = lstCodeItems.GetFirst();
	while( node )
	{
		pCodeItem = (udCodeItem*)node->GetData();
		if( (pCodeItem->GetSignature() == m_sOriginalCodeItem) &&
			(pCodeItem->GetScope() == m_sScope)	)
		{
			return pCodeItem;
		}
		
		node = node->GetNext();
	}
	
    return NULL;
}

void udMemberLinkItem::OnTreeItemEndDrag(const wxPoint &pos)
{
	udCodeLinkItem *pSourceItem = wxDynamicCast( IPluginManager::Get()->GetSelectedProjectItem(), udCodeLinkItem );
	if( !pSourceItem ) return;
	
	udProjectItem *pPresentItem = udPROJECT::GetProjectItem((udProjectItem*)GetParent(), CLASSINFO(udCodeLinkItem), pSourceItem->GetName());
	
	// only one instance of each code item is allowed in class element
	if( !pPresentItem || (pPresentItem == pSourceItem) )
	{
		// check also scope of dropped code link
		udProjectItem *pClassElement = (udProjectItem*) GetParent();
		if( pSourceItem->GetScope() != pClassElement->GetName() )
		{
			wxMessageBox( wxT("The code link cannot be used in this scope."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
		}
		else
			udCodeLinkItem::OnTreeItemEndDrag(pos);
	}
}

wxString udMemberLinkItem::ToString(udCodeItem::CODEFORMAT format, udLanguage* lang)
{
	wxString sBase = udCodeLinkItem::ToString(format, lang);
	
	if( format == udCodeItem::cfFORMAL )
	{
		switch( m_nAccessType )
		{
			case udLanguage::AT_PUBLIC:
				sBase = wxT("+ ") + sBase;
				break;
			
			case udLanguage::AT_PROTECTED:
				sBase = wxT("# ") + sBase;
				break;
				
			case udLanguage::AT_PRIVATE:
				sBase = wxT("- ") + sBase;
				break;
		}
	}
	
	return sBase;
}

void udMemberLinkItem::OnEditItem(wxWindow* parent)
{
	udCodeItem *pOrig = wxDynamicCast(GetOriginal(), udCodeItem);
	if( pOrig )
	{
		udClassMemberLinkDialog dlg( parent, pOrig, IPluginManager::Get()->GetSelectedLanguage() );
		udWindowManager dlgman( dlg, wxT("member_link_dialog") );
		
		dlg.SetCodeName( m_sName );
		dlg.SetAccessType( (int)m_nAccessType );
		
		if( dlg.ShowModal() == wxID_OK )
		{
			m_nAccessType = (udLanguage::ACCESSTYPE) dlg.GetAccessType();
			
			this->OnTreeTextChange( dlg.GetCodeName() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udMemberDataItem /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udMemberDataItem, udVariableItem);

// constructor and destructor ///////////////////////////////////////////////////////

udMemberDataItem::udMemberDataItem()
{
	m_sName = wxT("Variable");
	m_fInline = false;
	m_nDataModifier = udLanguage::DM_NONE;

	m_sDescription = wxT("Class data member's description...");
}

udMemberDataItem::udMemberDataItem(const udMemberDataItem &obj)
: udVariableItem(obj)
{
}

udMemberDataItem::~udMemberDataItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udMemberDataItem::ToString(CODEFORMAT format, udLanguage *lang)
{
	switch(format)
	{
		case cfFORMAL:
			if( lang && !GetDataTypeString( format, lang ).IsEmpty() )
			{
				if( !m_sValue.IsEmpty() )
				{
					return m_sName + wxT(" : ") + GetDataTypeString( format, lang ) + wxT(" = ") + m_sValue;
				}
				else
					return m_sName + wxT(" : ") + GetDataTypeString( format, lang );
			}
			else
				return m_sName;
				
		case cfDECLARATION:
			if( lang )
			{
				lang->PushCode();
				
				if( lang->HasSeparatedDecl() || m_sValue.IsEmpty() )
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
				
			case cfDEFINITION:
				if( lang )
				{
					lang->PushCode();
					
					if( lang->HasSeparatedDecl() && !m_sValue.IsEmpty() )
					{
						lang->VariableAssignCmd( lang->MakeValidIdentifier( m_sName ), m_sValue );
					}

					wxString sOut = lang->GetCodeBuffer();
					
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sName;
	
		default:
			return udVariableItem::ToString( format, lang );
	}
}

bool udMemberDataItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	return DragCodeItem( new udMemberDataLinkItem(this, udLanguage::AT_PUBLIC) );
}

/////////////////////////////////////////////////////////////////////////////////////
// udMemberDataLinkItem class ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udMemberDataLinkItem, udMemberLinkItem);

/////////////////////////////////////////////////////////////////////////////////////
// udMemberFunctionItem /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udMemberFunctionItem, udFunctionItem);

// constructor and destructor ///////////////////////////////////////////////////////

udMemberFunctionItem::udMemberFunctionItem()
{
	m_sName = wxT("Function");
	m_fInline = false;
	m_fMustBeUnique = false;

	m_sDescription = wxT("Class member function's description...");
}

udMemberFunctionItem::udMemberFunctionItem(const udMemberFunctionItem &obj)
: udFunctionItem(obj)
{
}

udMemberFunctionItem::~udMemberFunctionItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udMemberFunctionItem::ToString(CODEFORMAT format, udLanguage *lang)
{	
	switch(format)
	{
		case cfFORMAL:
			{
				wxString sParameters = GetParametersString( format, lang );
				
				// create output string
				if( lang && !GetDataTypeString( lang ).IsEmpty() )
				{
					return  m_sName + wxT("(") + sParameters + wxT(") : ") + GetDataTypeString( lang ) + wxT(" ") + GetModifierString( lang );;
				}
				else
					return m_sName + wxT("(") + sParameters + wxT(")");
			}
			
		case cfDEFINITION:
			{
				wxString sParameters = GetParametersString( cfDECLARATION, lang );
				
				if( lang )
				{
					lang->PushCode();
					
					// test whether the parent class is a template class
					udClassTemplateElementItem *pClassTempl = wxDynamicCast( IPluginManager::Get()->GetProject()->GetDiagramElement(m_sScope), udClassTemplateElementItem );
					if( pClassTempl )
					{
						lang->ClassMemberFcnDefCmd( GetModifierString(lang), GetDataTypeString(lang), lang->MakeValidIdentifier(m_sScope) + wxT("<") + pClassTempl->GetTemplateName() + wxT(">"), lang->MakeValidIdentifier(m_sName), sParameters );
					}
					else
						lang->ClassMemberFcnDefCmd( GetModifierString(lang), GetDataTypeString(lang), lang->MakeValidIdentifier(m_sScope), lang->MakeValidIdentifier(m_sName), sParameters );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sScope + wxT("::") + m_sName + wxT("( ") + sParameters + wxT(" )");
			}
			
		case cfDECLARATION:
			{
				wxString sParameters = GetParametersString( format, lang );
				
				if( lang )
				{
					lang->PushCode();
					
					lang->ClassMemberFcnDeclCmd( GetModifierString(lang), GetDataTypeString(lang), lang->MakeValidIdentifier(m_sScope), lang->MakeValidIdentifier(m_sName), sParameters );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sName + wxT("( ") + sParameters + wxT(" )");
			}
			
		default:
			return udFunctionItem::ToString( format, lang );
	}
}

bool udMemberFunctionItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	return DragCodeItem( new udMemberFunctionLinkItem(this, udLanguage::AT_PUBLIC) );
}

wxMenu* udMemberFunctionItem::CreateMenu()
{	
	// create popup menu
	
	wxMenu *pPopupMenu = udFunctionItem::CreateMenu();
	
	if( !this->IsKindOf( CLASSINFO(udDestructorFunctionItem) ) &&
		( (m_nFcnModifier == udLanguage::FM_VIRTUAL) || (m_nFcnModifier == udLanguage::FM_ABSTRACT) ) )
	{
		pPopupMenu->Insert(0, IDM_CLASS_RENAMEVIRTUAL, wxT("Refactor virtual function"), wxT("Rename all correspoding ancestors/successors."));
		pPopupMenu->InsertSeparator(1);
	}
	
	return pPopupMenu;
}

/////////////////////////////////////////////////////////////////////////////////////
// udMemberFunctionLinkItem class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udMemberFunctionLinkItem, udMemberLinkItem);

/////////////////////////////////////////////////////////////////////////////////////
// udConstructorFunctionItem ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udConstructorFunctionItem, udMemberFunctionItem);

// constructor and destructor ///////////////////////////////////////////////////////

udConstructorFunctionItem::udConstructorFunctionItem()
{
	m_sName = wxT("Constructor");
	m_sDescription = wxT("Class constructor's description...");
	
	m_nRetValDataType = udLanguage::DT_USERDEFINED;
	m_sUserRetValDataType = wxT("");
	
	XS_SERIALIZE( m_mapUsedConstructors, wxT("used_constructors") );
	XS_SERIALIZE( m_mapCallParams, wxT("constructors_call_parameters") );
}

udConstructorFunctionItem::udConstructorFunctionItem(const udConstructorFunctionItem &obj)
: udMemberFunctionItem(obj)
{
	m_mapUsedConstructors = obj.m_mapUsedConstructors;
	m_mapCallParams = obj.m_mapCallParams;
	
	XS_SERIALIZE( m_mapUsedConstructors, wxT("used_constructors") );
	XS_SERIALIZE( m_mapCallParams, wxT("constructors_call_parameters") );
}

udConstructorFunctionItem::~udConstructorFunctionItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udConstructorFunctionItem::ToString(CODEFORMAT format, udLanguage *lang)
{	
	wxArrayString arrBases, arrBasesParams;
	
	// fill bases array
	for( StringMap::iterator it = m_mapUsedConstructors.begin(); it != m_mapUsedConstructors.end(); ++it )
	{
		arrBases.Add( it->first );
		
		arrBasesParams.Add( GetUpdatedCallParams( it->first, it->second ) );
	}
	
	switch(format)
	{
		case cfFORMAL:
			{
				// create output string
				return m_sScope + wxT("(") + GetParametersString( format, lang ) + wxT(") : constructor");
			}
			
		case cfDEFINITION:
			{
				wxString sParameters = GetParametersString( cfDECLARATION, lang );
				
				if( lang )
				{
					lang->PushCode();
					
					lang->ClassConstructorDefCmd( lang->MakeValidIdentifier(m_sScope), sParameters, arrBases, arrBasesParams );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sScope + wxT("::") + m_sName + wxT("( ") + sParameters + wxT(" )");
			}
			
		case cfDECLARATION:
			{
				wxString sParameters = GetParametersString( format, lang );
				
				if( lang )
				{
					lang->PushCode();
					
					lang->ClassConstructorDeclCmd( lang->MakeValidIdentifier(m_sScope), sParameters, arrBases, arrBasesParams );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sName + wxT("( ") + sParameters + wxT(" )");
			}
			
		default:
			return udFunctionItem::ToString( format, lang );
	}
}

void udConstructorFunctionItem::OnEditItem(wxWindow* parent)
{
	udConstructorDialog dlg( parent, this, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("constructor_dialog") );
	
	udDiagramItem *pDiag = IPluginManager::Get()->GetProject()->GetDiagram( m_sImplementation );
	
	dlg.SetCodeName( m_sName );
	dlg.SetCode( m_sCode );
	dlg.SetDescription( m_sDescription );
	dlg.SetFcnModifier( m_nFcnModifier );
	dlg.SetImplementation( m_sImplementation );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sCode = dlg.GetCode();
		m_sDescription = dlg.GetDescription();
		m_nFcnModifier = dlg.GetFcnModifier();
		m_sImplementation = dlg.GetImplementation();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	if( pDiag ) IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pDiag );
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

// protected functions //////////////////////////////////////////////////////////////

wxString udConstructorFunctionItem::GetUpdatedCallParams(const wxString& baseclass, const wxString& cons)
{
	wxString sOut;
	
	udConstructorFunctionItem *pBaseCons = (udConstructorFunctionItem*) IPluginManager::Get()->GetProject()->GetCodeItem( CLASSINFO(udConstructorFunctionItem), cons, baseclass );
	
	if( pBaseCons )
	{
		udParamItem *pPar = (udParamItem*) pBaseCons->GetFirstChild( CLASSINFO(udParamItem) );
		while(pPar)
		{
			StringMap::iterator it = m_mapCallParams.find( cons + wxT(":") + pPar->GetName() );
			if( it != m_mapCallParams.end() )
			{
				if( !sOut.IsEmpty() ) sOut << wxT(", ");
				sOut << it->second;
			}
			
			pPar = (udParamItem*) pPar->GetSibbling( CLASSINFO(udParamItem) );
		}
	}
	
	/*wxString sOut;
	wxString sConsName;
	
	for( StringMap::iterator it = m_mapCallParams.begin(); it != m_mapCallParams.end(); ++it )
	{
		sConsName = it->first.BeforeFirst(':');
		
		//if( it->first.Contains(cons + wxT(":")) && !it->second.IsEmpty() )
		if( (sConsName == cons) && !it->second.IsEmpty() )
		{
			if( !sOut.IsEmpty() ) sOut << wxT(", ");
			sOut << it->second;
		}
	}*/
	
	return sOut;
}

/////////////////////////////////////////////////////////////////////////////////////
// udDestructorFunctionItem /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDestructorFunctionItem, udMemberFunctionItem);

// constructor and destructor ///////////////////////////////////////////////////////

udDestructorFunctionItem::udDestructorFunctionItem()
{
	m_sName = wxT("Destructor");
	m_sDescription = wxT("Class destructor's description...");
	
	m_nRetValDataType = udLanguage::DT_USERDEFINED;
	m_sUserRetValDataType = wxT("");
}

udDestructorFunctionItem::udDestructorFunctionItem(const udDestructorFunctionItem &obj)
: udMemberFunctionItem(obj)
{
}

udDestructorFunctionItem::~udDestructorFunctionItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udDestructorFunctionItem::ToString(CODEFORMAT format, udLanguage *lang)
{	
	switch(format)
	{
		case cfFORMAL:
			{
				// create output string
				return m_sScope + wxT("(") + GetParametersString( format, lang ) + wxT(") : destructor " ) + GetModifierString( lang );
			}
			
		case cfDEFINITION:
			{
				if( lang )
				{
					lang->PushCode();
					
					lang->ClassDestructorDefCmd( wxT(""), lang->MakeValidIdentifier(m_sScope), wxT("") );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sScope + wxT("::~") + m_sName + wxT("()");
			}
			
		case cfDECLARATION:
			{
				if( lang )
				{
					lang->PushCode();
					
					lang->ClassDestructorDeclCmd( GetModifierString(lang), lang->MakeValidIdentifier(m_sScope), wxT("") );
					
					wxString sOut = lang->GetCodeBuffer();
				
					lang->PopCode();
					return sOut.Trim().Trim(false);
				}
				else
					return m_sName + wxT("()");
			}
			
		default:
			return udFunctionItem::ToString( format, lang );
	}
}

void udDestructorFunctionItem::OnEditItem(wxWindow* parent)
{
	udDestructorDialog dlg( parent, IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("destructor_dialog") );
	
	udDiagramItem *pDiag = IPluginManager::Get()->GetProject()->GetDiagram( m_sImplementation );
	
	dlg.SetCodeName( m_sName );
	dlg.SetCode( m_sCode );
	dlg.SetDescription( m_sDescription );
	dlg.SetFcnModifier( m_nFcnModifier );
	dlg.SetImplementation( m_sImplementation );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_sCode = dlg.GetCode();
		m_sDescription = dlg.GetDescription();
		m_nFcnModifier = dlg.GetFcnModifier();
		m_sImplementation = dlg.GetImplementation();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
	
	if( pDiag ) IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pDiag );
	
	IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
}

/////////////////////////////////////////////////////////////////////////////////////
// udEnumValueItem //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udEnumValueItem, udCodeItem);

// constructor and destructor ///////////////////////////////////////////////////////

udEnumValueItem::udEnumValueItem()
{
	AcceptSibbling( wxT("udEnumValueItem") );
	
	m_sDescription = wxT("Enumeration element's description...");
	
	RemoveProperty( GetProperty( wxT("code") ) );
	RemoveProperty( GetProperty( wxT("scope") ) );
	
	XS_SERIALIZE( m_Value, wxT("value") );
}

udEnumValueItem::udEnumValueItem(const udEnumValueItem &obj) : udCodeItem(obj)
{
	m_Value = obj.m_Value;
	
	RemoveProperty( GetProperty( wxT("code") ) );
	RemoveProperty( GetProperty( wxT("scope") ) );

	XS_SERIALIZE( m_Value, wxT("value") );
}

udEnumValueItem::~udEnumValueItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxString udEnumValueItem::ToString(CODEFORMAT format, udLanguage *lang)
{	
	switch(format)
	{
		case cfFORMAL:
		case cfDECLARATION:
			{
				if( m_Value.IsEmpty() ) return m_sName;
				else
					return m_sName + wxT(" = ") + m_Value;
			}
		
		default:
			return m_sName;
			break;
	}
}

void udEnumValueItem::OnTreeTextChange(const wxString& txt)
{
	udEnumElementItem *pEnum = wxDynamicCast( GetParent(), udEnumElementItem );
	if( pEnum )
	{
		wxString key, val;
		if( pEnum->CheckElementString( txt, key, val ) )
		{
			udProjectItem::OnTreeTextChange( key );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pEnum, NULL, wxEmptyString, udfDELAYED );
		}
	}
}

void udEnumValueItem::OnEditItem(wxWindow* parent)
{	
	udEnumElementDialog dlg( IPluginManager::Get()->GetMainFrame(), IPluginManager::Get()->GetSelectedLanguage() );
	udWindowManager dlgman( dlg, wxT("enum_value_dialog") );
	
	dlg.SetCodeName( m_sName );
	dlg.SetDescription( m_sDescription );
	dlg.SetValue( m_Value );
	
	if( dlg.ShowModal() == wxID_OK )
	{
		m_Value = dlg.GetValue();
		m_sDescription = dlg.GetDescription();
		
		OnTreeTextChange( dlg.GetCodeName() );
	}
}

bool udEnumValueItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;
	else
		return true;
}
