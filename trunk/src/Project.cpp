#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/textdlg.h>
#include <wx/regex.h>
#include <wx/artprov.h>

#include "Project.h"
#include "ProjectManager.h"
#include "Ids.h"
#include "Art.h"
#include "UMLDesignerMain.h"
#include "gui/GroupDialog.h"
#include "shapes/GroupItem.h"

// static staff
int udProject::m_nCounter = 0;

using namespace wxSFCommonFcn;

/////////////////////////////////////////////////////////////////////////////////////
// udRootItem class /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udRootItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udRootItem::udRootItem() : udProjectItem()
{
    m_sName = wxT("Project items");
	
	RemoveProperty( GetProperty( wxT("description") ) );
}

udRootItem::udRootItem(const udRootItem &obj) : udProjectItem(obj)
{
	RemoveProperty( GetProperty( wxT("description") ) );
}

udRootItem::~udRootItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxMenu* udRootItem::CreateMenu()
{
	const wxString &sResPath = wxGetApp().GetResourcesPath();
	
	// create popup menu
	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_PACKAGE, wxT("Create diagram package"), wxT("Create new package and add it to the project root"));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/project/cube_green.xpm"), wxBITMAP_TYPE_XPM));
	pPopupMenu->Append(pItem);

	pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_CODEPACKAGE, wxT("Create code package"), wxT("Create new code package and add it to the project root"));
	pItem->SetBitmap(wxBitmap(sResPath + wxT("app/project/cube_yellow.xpm"), wxBITMAP_TYPE_XPM));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();

	pItem = new wxMenuItem(pPopupMenu, IDM_DELAYED_REMOVEALL, wxT("Remove all"));
	//pItem->SetBitmap(wxBitmap(delete_xpm));
	pPopupMenu->Append(pItem);
	
	return pPopupMenu;
}

void udRootItem::OnTreeItemEndDrag(const wxPoint& pos)
{
	udProjectTree *pView = wxGetApp().GetMainFrame()->GetProjectManager()->GetActiveView();

	udProjectItem *pSourceItem = wxGetApp().GetMainFrame()->GetSelectedProjectItem();
	
	if( pSourceItem && (
		pSourceItem->IsKindOf( CLASSINFO(udPackageItem) ) ||
		pSourceItem->IsKindOf( CLASSINFO(udCodeItem) ) ||
		pSourceItem->IsKindOf( CLASSINFO(udCodePackageItem) ) ) )
	{
		// reparent item
		pSourceItem->Reparent( this );
		
		// update the code tree
		pView->UpdateItem( this );
	}
}

wxXmlNode* udRootItem::Serialize(wxXmlNode* node)
{
    if( node )
    {
        // serialize standard defined properties
        node = udProjectItem::Serialize(node);

        // serialize non-standard properties

        // diagram items
		wxXmlNode* settings = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("settings"));
		m_Settings.SerializeObjects(m_Settings.GetRootItem(), settings, false);
		node->AddChild(settings);
    }

	return node;
}

void udRootItem::Deserialize(wxXmlNode* node)
{
    wxASSERT(node);
    if(!node)return;

    // deserialize standard defined properties
    udProjectItem::Deserialize(node);

    // deserialize non-standard properties	
    wxXmlNode *propNode = node->GetChildren();
	while(propNode)
	{
		if(propNode->GetName() == wxT("settings"))
		{
			m_Settings.RemoveAll();
		    m_Settings.DeserializeObjects(NULL, propNode);
		}
		propNode = propNode->GetNext();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udPackageItem class //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udPackageItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udPackageItem::udPackageItem() : udProjectItem()
{
    m_sName = wxT("Package");
	m_fMustBeUnique = false;
	
	AcceptChild(wxT("udPackageItem"));
	AcceptChild(wxT("udSStateChartDiagramItem"));
	AcceptChild(wxT("udHStateChartDiagramItem"));
	AcceptChild(wxT("udClassDiagramItem"));

	RemoveProperty( GetProperty( wxT("description") ) );
}

udPackageItem::udPackageItem(const udPackageItem &obj) : udProjectItem(obj)
{	
	RemoveProperty( GetProperty( wxT("description") ) );
}

udPackageItem::~udPackageItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxMenu* udPackageItem::CreateMenu()
{
	// create popup menu
	wxMenu *pPopupMenu = new wxMenu(); 
	
	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_PACKAGE, wxT("Create diagram package"), wxT("Create new package and add it to the project root"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udPackageItem")));
	pPopupMenu->Append(pItem);

	pPopupMenu->AppendSeparator();

	DiagramsArray arrDiagrams = wxGetApp().GetMainFrame()->GetDiagrams();
	for( size_t i = 0; i < arrDiagrams.GetCount(); i++ )
	{
        pItem = new wxMenuItem(pPopupMenu, arrDiagrams[i].m_nId, wxT("Create ") + arrDiagrams[i].m_sName, wxT("Create new ") + arrDiagrams[i].m_sName + wxT(" and add it to the current package."));
        pItem->SetBitmap(udArt::GetBitmap(arrDiagrams[i].m_sClassName));
        pPopupMenu->Append(pItem);
	}
	
	pPopupMenu->AppendSeparator();
	
	pPopupMenu->Append(IDM_DIAG_INSERTFROMBANK, wxT("Insert diagram from bank"));

    //pPopupMenu->AppendSeparator();
    //pPopupMenu->Append(IDM_DELAYED_EDIT, wxT("Edit properties..."), wxT("Edit package properties."));
    pPopupMenu->AppendSeparator();
    pPopupMenu->Append(IDM_DELAYED_REMOVE, wxT("Remove package"), wxT("Remove package and all included items."));

	return pPopupMenu;
}

bool udPackageItem::OnTreeItemBeginDrag(const wxPoint& pos)
{
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;	
	else
		return true;
}

void udPackageItem::OnTreeItemEndDrag(const wxPoint& pos)
{
	udProjectItem *pSourceItem = wxGetApp().GetMainFrame()->GetSelectedProjectItem();
	
	if( pSourceItem && IsChildAccepted(pSourceItem->GetClassInfo()->GetClassName()) )
	{
		udProjectItem *pSourceParent = wxDynamicCast( pSourceItem->GetParent(), udProjectItem );
		if( pSourceParent )
		{
			// get list of source item's successors and check whether the target item isn't in the list
			SerializableList lstChildren;
			pSourceItem->GetChildrenRecursively( CLASSINFO(udPackageItem), lstChildren );
			
			if(lstChildren.IndexOf( this ) != wxNOT_FOUND )
			{
				wxMessageBox( wxT("Couldn't move item to its successor."), wxT("CodeDesigner"), wxICON_WARNING | wxOK );
			}
			else
			{
				// reparent item
				pSourceItem->Reparent( this );

				// update tree items and other related stuff
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
				
				if( pSourceParent != this )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udCodePackageItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCodePackageItem, udProjectItem);

// constructor and destructor ///////////////////////////////////////////////////////

udCodePackageItem::udCodePackageItem() : udProjectItem()
{
    m_sName = wxT("Package");
	m_fMustBeUnique = false;
	
	AcceptChild(wxT("udCodePackageItem"));
	AcceptChild(wxT("udActionItem"));
	AcceptChild(wxT("udConditionItem"));
	AcceptChild(wxT("udEventItem"));
	AcceptChild(wxT("udVariableItem"));
	AcceptChild(wxT("udFunctionItem"));
	AcceptChild(wxT("udMemberDataItem"));
	AcceptChild(wxT("udMemberFunctionItem"));
	AcceptChild(wxT("udConstructorFunctionItem"));
	AcceptChild(wxT("udDestructorFunctionItem"));

	RemoveProperty( GetProperty( wxT("description") ) );
}

udCodePackageItem::udCodePackageItem(const udCodePackageItem &obj) : udProjectItem(obj)
{
	RemoveProperty( GetProperty( wxT("description") ) );
}

udCodePackageItem::~udCodePackageItem()
{
}

// virtual functions ////////////////////////////////////////////////////////////////

wxMenu* udCodePackageItem::CreateMenu()
{
	// create popup menu
	wxMenu *pPopupMenu = new wxMenu();
	
	wxMenuItem *pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_CODEPACKAGE, wxT("Create code package"), wxT("Create new code package"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udCodePackageItem")));
	pPopupMenu->Append(pItem);
	
	pPopupMenu->AppendSeparator();
	
	pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_VARIABLE, wxT("Create generic variable"), wxT("Create new user-defined variable"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udGenericVariableItem")));
	pPopupMenu->Append(pItem);
	
	pItem = new wxMenuItem(pPopupMenu, IDM_PROJ_FUNCTION, wxT("Create generic function"), wxT("Create new user-defined function"));
	pItem->SetBitmap(udArt::GetBitmap(wxT("udGenericFunctionItem")));
	pPopupMenu->Append(pItem);

    pPopupMenu->AppendSeparator();
	
    pPopupMenu->Append(IDM_DELAYED_REMOVE, wxT("Remove package"), wxT("Remove all user-defined code items."));
	
	return pPopupMenu;
}

bool udCodePackageItem::OnTreeItemBeginDrag(const wxPoint &pos)
{
	// if a shift key is pressed down then re-arrange it by a DnD operation built-in in a tree control
	wxMouseState cState = wxGetMouseState();
	if( cState.ShiftDown() ) return false;	
	else
		return true;
}

void udCodePackageItem::OnTreeItemEndDrag(const wxPoint &pos)
{
	udProjectItem *pSourceItem = wxGetApp().GetMainFrame()->GetSelectedProjectItem();
	
	if( pSourceItem && IsChildAccepted(pSourceItem->GetClassInfo()->GetClassName()) )
	{
		udProjectItem *pSourceParent = wxDynamicCast( pSourceItem->GetParent(), udProjectItem );
		if( pSourceParent )
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
				UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
					
				if( pSourceParent != this )
				{
					UMLDesignerFrame::SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, pSourceParent );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udNoteElementItem class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udNoteElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udNoteConnElementItem class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udNoteConnElementItem, udDiagElementItem);

/////////////////////////////////////////////////////////////////////////////////////
// udGroupElementItem class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udGroupElementItem, udDiagElementItem);

udGroupElementItem::udGroupElementItem()
{
	m_fMustBeUnique = false;
}

// virtual functions ////////////////////////////////////////////////////////////////

void udGroupElementItem::OnEditItem(wxWindow* parent)
{
	uddGroupItem *pGroup = wxDynamicCast( GetParent(), uddGroupItem );
	if( pGroup )
	{
		udGroupDialog dlg(parent);
		udWindowManager mgr(dlg, wxT("group_dialog"));
		
		wxBrush fill = pGroup->GetFill();
		
		dlg.SetCodeName( m_sName );
		dlg.SetDescription( m_sDescription );
		dlg.SetColour( fill.GetColour() );
		
		if( dlg.ShowModal() == wxID_OK )
		{	
			fill.SetColour( dlg.GetColour() );
			pGroup->SetFill( fill );
			
			SetDescription( dlg.GetDescription() );
			
			OnTreeTextChange( dlg.GetCodeName() );
			
			IPluginManager::Get()->SendProjectEvent( wxEVT_CD_ITEM_CHANGED, wxID_ANY, this );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// udProject class //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udProject, IProject);

// constructor and destructor ///////////////////////////////////////////////////////

udProject::udProject()
{
	SetSerializerOwner( wxT("CodeDesigner") );
	SetSerializerRootName( wxT("project") );
	SetSerializerVersion( wxT("1.0") );
	
    CreateRootItem();
}

udProject::udProject(const udProject &obj) : IProject(obj)
{
}

udProject::~udProject()
{
}

// public functions /////////////////////////////////////////////////////////////////

udProject* udProject::Get()
{
	return wxGetApp().GetActiveProject();
}

void udProject::CreateRootItem()
{
    // create root item
    udRootItem* root = new udRootItem();
	
    root->SetId(GetNewId());
	
	// initialize project settings
	root->GetSettings().CreateCategories();
	
	udSettings& Settings = wxGetApp().GetSettings();
	wxString sPath = Settings.GetProperty(wxT("Output directory"))->ToString();
	
	m_sProjectPath = sPath; //wxGetCwd();
	m_sProjectDir = sPath;
	
	root->GetSettings().GetProperty(wxT("Output directory"))->FromString( sPath );

    SetRootItem(root);
}

udProjectItem* udProject::CreateProjectItem(const wxString& classname, long parentId )
{
    udProjectItem* pItem = (udProjectItem*)wxCreateDynamicObject(classname);

    if(pItem)
    {
		pItem->SetName( pItem->GetName() );
        AddItem(parentId, pItem);
    }

    return pItem;
}

udDiagramItem* udProject::GetDiagram(udDiagramCanvas *canvas)
{
	if( canvas )
	{
		udDiagramItem *diagram;
		SerializableList lstDiagrams;
	
	    GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
		SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
		while(node)
		{
		    diagram = (udDiagramItem*)node->GetData();
		    if(diagram->GetDiagramPage() == canvas) return diagram;

		    node = node->GetNext();
		}
	}

    return NULL;
}

udDiagramItem* udProject::GetDiagram(const wxString& name)
{
    udDiagramItem *diagram;
    SerializableList lstDiagrams;

    GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );
    SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
    while(node)
    {
        diagram = (udDiagramItem*)node->GetData();
        if(diagram->GetName() == name) return diagram;

        node = node->GetNext();
    }

    return NULL;
}

udDiagElementItem* udProject::GetDiagramElement(const wxString& diagram, const wxString& element)
{
    return (udDiagElementItem*) udPROJECT::GetDiagramElement( GetDiagram( diagram ), element );
}

udDiagElementItem* udProject::GetDiagramElement(const wxString& element)
{
	udDiagElementItem *pDiagElement;
	
	SerializableList lstDiagrams;
	GetDiagramsRecursively(NULL, lstDiagrams);
	
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it )
	{
		pDiagElement = (udDiagElementItem*) udPROJECT::GetDiagramElement( (udDiagramItem*)*it, element );
		if( pDiagElement ) return pDiagElement;
	}
	
	return NULL;
}

void udProject::GetDiagramElements(wxClassInfo *type, SerializableList& elements)
{
    SerializableList lstDiagrams;
    GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );

    SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
    while( node )
    {
        udPROJECT::GetDiagramElements( (udDiagramItem*)node->GetData(), type, elements, sfNORECURSIVE );
        node = node->GetNext();
    }
}

void udProject::GetElementLinks(const wxString& diagram, const wxString& element, SerializableList& elements)
{
    SerializableList lstLinks;
    udElementLinkItem *pLink;

    GetDiagramElements( CLASSINFO(udElementLinkItem), lstLinks );
    SerializableList::compatibility_iterator node = lstLinks.GetFirst();
    while( node )
    {
        pLink = (udElementLinkItem*)node->GetData();
        if( ((pLink->GetOrigDiagram() == diagram) || (diagram==wxT(""))) && ((pLink->GetOrigElement()==element) ||(element==wxT(""))) ) elements.Append( pLink );

        node = node->GetNext();
    }
}

void udProject::GetCodeLinks(bool valid, wxClassInfo *type, const wxString& codeitem, const wxString& scope, SerializableList& elements)
{
    SerializableList lstParents;
    udCodeLinkItem *pLink;
	udProjectItem *pOriginal;
	
    GetDiagramElements( CLASSINFO(udDiagElementItem), lstParents );
    SerializableList::compatibility_iterator node = lstParents.GetFirst();
    while( node )
    {
		SerializableList::compatibility_iterator lnode = node->GetData()->GetFirstChildNode();
		while( lnode )
		{
			pLink = wxDynamicCast( lnode->GetData(), udCodeLinkItem );
			if( pLink )
			{
				pOriginal = pLink->GetOriginal() ;
				if( valid )
				{
					wxASSERT( pOriginal );
					if( pOriginal )
					{
						if( (!type || pOriginal->IsKindOf(type)) &&
							( (codeitem == wxT("")) || ((pLink->GetOrigCodeItem() == codeitem) && (pLink->GetScope() == scope)) ) ) elements.Append( pLink );
					}
				}
				else
					if( !pOriginal ) elements.Append( pLink );
			}

			lnode = lnode->GetNext();
		}
        node = node->GetNext();
    }
}

void udProject::GetDiagramsRecursively(wxClassInfo *type, SerializableList& diagrams)
{
	udDiagramItem *pDiagram;
    SerializableList lstDiagrams;

    GetItems(CLASSINFO(udDiagramItem), lstDiagrams);

    SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
    while(node)
    {
        pDiagram = (udDiagramItem*) node->GetData();
		if( !type || pDiagram->IsKindOf( type ) ) diagrams.Append( pDiagram );

        udPROJECT::GetSubDiagrams( pDiagram, type, diagrams );

        node = node->GetNext();
    }
}

void udProject::CloseAllDiagrams()
{
    SerializableList lstDiagrams;
    GetDiagramsRecursively( CLASSINFO(udDiagramItem), lstDiagrams );

    SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
    while(node)
    {
        ((udDiagramItem*)node->GetData())->CloseDiagramPage();
        node = node->GetNext();
    }
}

void udProject::CloseAllSubdiagrams(udDiagramItem *parent)
{
	udDiagramItem *pDiag;
    SerializableList lstDiagrams;
    udPROJECT::GetDiagramElements( parent, CLASSINFO(udSubDiagramElementItem), lstDiagrams, sfRECURSIVE );

    SerializableList::compatibility_iterator node = lstDiagrams.GetFirst();
    while(node)
    {
		pDiag = ((udSubDiagramElementItem*)node->GetData())->GetSubDiagram();
		if( pDiag ) pDiag->CloseDiagramPage();
        node = node->GetNext();
    }
}

void udProject::CheckElementLinks()
{
    udElementLinkItem *pLink;
    udDiagramManager *pManager;

    SerializableList lstLinks;
    GetDiagramElements( CLASSINFO(udElementLinkItem), lstLinks );

    // remove all links without original element
    SerializableList::compatibility_iterator node = lstLinks.GetFirst();
    while( node )
    {
        pLink = (udElementLinkItem*)node->GetData();
        if( !pLink->GetOriginal() )
        {
            pManager = (udDiagramManager*)pLink->GetParent()->GetParentManager();
            pManager->RemoveShape((wxSFShapeBase*)pLink->GetParent());
        }
        node = node->GetNext();
    }
}

void udProject::CheckCodeLinks()
{
    udCodeLinkItem *pLink;

    SerializableList lstLinks;
    GetCodeLinks( udfINVALID, NULL, wxT(""), wxT(""), lstLinks );

    // remove all links without original code item
    SerializableList::compatibility_iterator node = lstLinks.GetFirst();
    while( node )
    {
        pLink = (udCodeLinkItem*)node->GetData();

		pLink->GetParent()->GetChildrenList().DeleteObject( pLink );
		delete pLink;
		
        node = node->GetNext();
    }
}

udProjectItem* udProject::GetProjectItem(wxClassInfo* type, const wxString& name)
{
	SerializableList lstItems;
	GetItems( type, lstItems );
				
	SerializableList::compatibility_iterator node = lstItems.GetFirst();
	while( node )
	{
		if( ((udProjectItem*)node->GetData())->GetName() == name ) return (udProjectItem*)node->GetData();
		node = node->GetNext();
	}
	return NULL;
}

udCodeItem* udProject::GetCodeItem(wxClassInfo* type, const wxString& name, const wxString& scope)
{
	SerializableList lstItems;
	GetItems( type, lstItems );
				
	SerializableList::compatibility_iterator node = lstItems.GetFirst();
	while( node )
	{
		udCodeItem *pItem = wxDynamicCast( node->GetData(), udCodeItem );
		if( pItem &&
			( pItem->GetName() == name ) &&
			( pItem->GetScope() == scope ) ) return pItem;
	
		node = node->GetNext();
	}
	
	return NULL;
}

// static public functions //////////////////////////////////////////////////////////

wxString udProject::MakeUniqueName(const wxString& name, int threshold)
{
    int nCount = 2;
    wxString uname = name;

	while(OccurenceCount(uname) > threshold)
    {
        uname = wxString::Format(wxT("%s %d"), name.c_str(), nCount);
		threshold = 0;

        nCount++;
    }

    return uname;
}

bool udProject::IsUniqueName(const wxString& name)
{
    if( OccurenceCount(name) == 0 ) return true;
	else
		return false;
}

int udProject::OccurenceCount(const wxString &name)
{
	m_nCounter = 0;

    udProjectItem *pItem;
    SerializableList lstItems;

    // test project items
    GetItems(CLASSINFO(udProjectItem), lstItems);

    SerializableList::compatibility_iterator node = lstItems.GetFirst();
    while(node)
    {
        pItem = (udProjectItem*)node->GetData();
        if(pItem->GetName() == name)
        {
            m_nCounter++;
        }

        // test diagram items
        if(pItem->IsKindOf(CLASSINFO(udDiagramItem)))
        {
            DiagramOccurenceCount((udDiagramItem*)pItem, name);
        }

        node = node->GetNext();
    }

    return m_nCounter;
}

void udProject::GetDiagramCodeItems(udDiagramItem* diagram, wxClassInfo* type, SerializableList& codeitems)
{
	udProjectItem *pItem;
	udCodeItem *pFcn;
	udDiagElementItem *pElement;
	SerializableList lstElements;
	SerializableList lstLinks;
	SerializableList lstDiagrams;
	
	lstDiagrams.Append( diagram );
	udPROJECT::GetSubDiagrams( diagram, CLASSINFO(udDiagramItem), lstDiagrams );
	
	for( SerializableList::iterator it = lstDiagrams.begin(); it != lstDiagrams.end(); ++it )
	{
		udDiagramItem *pDiag = (udDiagramItem*)*it;
		
		// get specific dependencies
		pDiag->GetSpecificCodeItems( type, codeitems );
		
		// add diagram's dependencies to the record
		pFcn = GetFunctionImplementedBy( pDiag );
		if( pFcn && (codeitems.IndexOf( pFcn ) == wxNOT_FOUND) )
		{
			codeitems.Append( pFcn );
		}
		
		// get code items assigned to the diagram elements
		lstElements.Clear();
		
		udPROJECT::GetDiagramElements( pDiag, CLASSINFO(udDiagElementItem), lstElements, sfRECURSIVE );
		
		for( SerializableList::iterator it = lstElements.begin(); it != lstElements.end(); ++it )
		{
			pElement = (udDiagElementItem*) *it;
			
			lstLinks.Clear();
			pElement->GetCodeItems( CLASSINFO(udCodeLinkItem), lstLinks );
			
			for( SerializableList::iterator it2 = lstLinks.begin(); it2 != lstLinks.end(); ++it2 )
			{
				pItem = ((udCodeLinkItem*) *it2)->GetOriginal();
				if( pItem && ( codeitems.IndexOf( pItem ) == wxNOT_FOUND ) )
				{
					codeitems.Append( pItem );
				}
			}
		}
	}
}

void udProject::AppendSubDiagramsShapes(ShapeList& elements)
{
    udProjectItem *pDiagItem;

    ShapeList lstSource = elements;
    SerializableList lstElements;

    ShapeList::compatibility_iterator node = lstSource.GetFirst();
    while( node )
    {
        pDiagItem = (udProjectItem*)node->GetData()->GetUserData();
        if( pDiagItem && pDiagItem->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
        {
            lstElements.Clear();
            udPROJECT::GetDiagramElements(((udSubDiagramElementItem*)pDiagItem)->GetSubDiagram(), CLASSINFO(udSubDiagramElementItem), lstElements, sfRECURSIVE);

            SerializableList::compatibility_iterator enode = lstElements.GetFirst();
            while( enode )
            {
                elements.Append( (wxSFShapeBase*)((udSubDiagramElementItem*)enode->GetData())->GetParent() );
                enode = enode->GetNext();
            }
        }

        node = node->GetNext();
    }
}

udFunctionItem* udProject::GetFunctionImplementedBy(const udDiagramItem* diag)
{
	wxASSERT( diag );
	
	SerializableList lstFunctions;
	GetItems( CLASSINFO(udFunctionItem), lstFunctions );
	
	for( SerializableList::iterator it = lstFunctions.begin(); it != lstFunctions.end(); ++it )
	{
		if( ((udFunctionItem*)*it)->GetImplementation() == diag->GetName() ) return (udFunctionItem*)*it;
	}
	
	return NULL;
}

// protected functions  ///////////////////////////////////////////////////////

void udProject::DiagramOccurenceCount(udDiagramItem *diagram, const wxString& name)
{
    udProjectItem *pDiagItem;
    ShapeList lstDiagItems;

    diagram->GetDiagramManager().GetShapes(CLASSINFO(wxSFShapeBase), lstDiagItems);
    ShapeList::compatibility_iterator snode = lstDiagItems.GetFirst();
    while(snode)
    {
        pDiagItem = (udProjectItem*)snode->GetData()->GetUserData();
        if( pDiagItem )
        {
            if( pDiagItem->GetName() == name ) m_nCounter++;

            if( pDiagItem->IsKindOf(CLASSINFO(udSubDiagramElementItem)) )
            {
                DiagramOccurenceCount(((udSubDiagramElementItem*)pDiagItem)->GetSubDiagram(), name);
            }
        }

        snode = snode->GetNext();
    }
}
