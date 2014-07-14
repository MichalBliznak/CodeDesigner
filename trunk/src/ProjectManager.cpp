#include "wx_pch.h"

#include "ProjectManager.h"
#include "XS2PG.h"
#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "gui/TabArt.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

BEGIN_EVENT_TABLE( udProjectManager, _ProjManPanel )
	EVT_CD_ITEM_SELECTED( wxID_ANY, udProjectManager::OnProjectItemSelected )
	EVT_CD_ITEM_CHANGED( wxID_ANY, udProjectManager::OnProjectItemSelected )
END_EVENT_TABLE();

// construction /////////////////////////////////////////////////////////////////////

udProjectManager::udProjectManager(wxWindow *parent) : _ProjManPanel( parent )
{
	//SetExtraStyle( wxWS_EX_BLOCK_EVENTS );
	
	udSettings &Settings = wxGetApp().GetSettings();
	
	m_fLinked = Settings.GetProperty(wxT("Link manager with designer"))->AsBool();
	m_fShowProperties = Settings.GetProperty(wxT("Show item properties"))->AsBool();
	m_fOrganizeCI = Settings.GetProperty(wxT("Organize code items"))->AsBool();
	m_nPropsSashPosition = Settings.GetProperty(wxT("Project manager sash position"))->AsInt();
	
	m_auintbViews->SetArtProvider( new udTabArt() );
	
	// initialize properties grid
	UpdatePropertiesView( NULL );
	
	// Delayed sash position update
	Connect(wxEVT_IDLE, wxIdleEventHandler( udProjectManager::OnIdle ) );
	//m_pSplitter->Unsplit( m_pPanelProperties );
}

udProjectManager::~udProjectManager()
{
	udSettings &Settings = wxGetApp().GetSettings();
	
	Settings.GetProperty(wxT("Project manager sash position"))->AsInt() = m_nPropsSashPosition;
	Settings.GetProperty(wxT("Organize code items"))->AsBool() = m_fOrganizeCI;
	Settings.GetProperty(wxT("Show item properties"))->AsBool() = m_fShowProperties;
	Settings.GetProperty(wxT("Link manager with designer"))->AsBool() = m_fLinked;
}

// public functions /////////////////////////////////////////////////////////////////

udProjectTree* udProjectManager::GetActiveView()
{
	return (udProjectTree*)m_auintbViews->GetPage( m_auintbViews->GetSelection() );
}

wxString udProjectManager::GetActiveViewName()
{
	return m_auintbViews->GetPageText( m_auintbViews->GetSelection() );
}

udProjectTree* udProjectManager::GetView(const wxString& name)
{
	return m_mapViews[name];
}

void udProjectManager::InsertView(udProjectTree* ctrl, const wxString& name)
{
	if( m_mapViews.find( name ) == m_mapViews.end() )
	{
		m_mapViews[name] = ctrl;
		m_auintbViews->AddPage( ctrl, name, true);
	}
	else
	{
        m_auintbViews->SetSelection( m_auintbViews->GetPageIndex( ctrl ) );
	}
}

void udProjectManager::RemoveView(const wxString& name)
{
	m_auintbViews->DeletePage( m_auintbViews->GetPageIndex( m_mapViews[name] ) );

	m_mapViews.erase(name);
}

void udProjectManager::SetActiveView(const wxString& name)
{
	m_auintbViews->SetSelection( m_auintbViews->GetPageIndex( m_mapViews[name] ) );
}

void udProjectManager::BuildFromProject(udProject* project)
{
	ViewsMap::iterator it;
	for( it = m_mapViews.begin(); it != m_mapViews.end(); ++it )
	{
		it->second->BuildFromProject( project );
	}
}

// event handlers ///////////////////////////////////////////////////////////////////////

void udProjectManager::OnExpandAll(wxCommandEvent& event)
{
	m_fExpanded = !m_fExpanded;
	if( m_fExpanded )
	{
		GetActiveView()->ExpandAll();
	}
	else
		GetActiveView()->CollapseAll();
}

void udProjectManager::OnViewChanged(wxAuiNotebookEvent& event)
{	
	m_fExpanded = true;
	
	udProjectTree *pView = GetActiveView();
	if( pView )
	{
		wxTreeItemId itemId = pView->GetRootItem();
		if( itemId.IsOk() ) m_fExpanded = pView->IsExpanded( itemId );
	}
}

void udProjectManager::OnLinkedEditor(wxCommandEvent& event)
{
	m_fLinked = !m_fLinked;
}

void udProjectManager::OnUpdateLinkedEditor(wxUpdateUIEvent& event)
{
	event.Check( m_fLinked );
}

void udProjectManager::OnShowProperties(wxCommandEvent& event)
{
	m_fShowProperties = !m_fShowProperties;
	
	if( m_fShowProperties )
	{
		m_pSplitter->SplitHorizontally( m_pPanelTree, m_pPanelProperties, m_nPropsSashPosition );
		
		UpdatePropertiesView( wxGetApp().GetMainFrame()->GetSelectedProjectItem() );
	}
	else
		m_pSplitter->Unsplit( m_pPanelProperties );
}

void udProjectManager::OnUpdateShowProperties(wxUpdateUIEvent& event)
{
	event.Check( m_fShowProperties );
}

void udProjectManager::OnPropsSashChanged(wxSplitterEvent& event)
{
	m_nPropsSashPosition = event.GetSashPosition();
}

void udProjectManager::UpdatePropertiesView(udProjectItem* item)
{
	// initialize properties grid
	m_pPropertiesGrid->Clear();
	// create some common steps
	m_pPropertiesGrid->Append( new wxPropertyCategory( wxT("Common") ) );
	
	// show read-only properties of given item
	if( item )
	{
		m_pPropertiesGrid->DisableProperty( m_pPropertiesGrid->Append( new wxStringProperty( wxT("type"), wxPG_LABEL, udXS2PG::GetFriendlyName( wxT("classname"), item->GetClassInfo()->GetClassName() ) ) ) );
		
		m_pPropertiesGrid->Append( new wxPropertyCategory( wxT("Properties") ) );
		
		xsProperty *pProperty;
		wxString sValue;
		
		PropertyList::compatibility_iterator node = item->GetProperties().GetFirst();
		while( node )
		{
			pProperty = node->GetData();
			sValue = wxXmlSerializer::GetPropertyIOHandler( pProperty->m_sDataType )->GetValueStr( pProperty );
			
			wxPGProperty *pNewProp =  m_pPropertiesGrid->Append( new wxStringProperty( pProperty->m_sFieldName, wxPG_LABEL, udXS2PG::GetFriendlyName( pProperty->m_sFieldName, sValue ) ) );
			if( pNewProp ) m_pPropertiesGrid->DisableProperty( pNewProp );
			
			node = node->GetNext();
		}
	}
}

void udProjectManager::OnProjectItemSelected(udProjectEvent& event)
{
	if( m_fShowProperties ) UpdatePropertiesView( event.GetProjectItem() );
}

void udProjectManager::ClearAllViews()
{
	ViewsMap::iterator it;
	for( it = m_mapViews.begin(); it != m_mapViews.end(); ++it )
	{
		it->second->DeleteAllItems();
	}
}

void udProjectManager::OnPGActivated(wxMouseEvent& event)
{
	udProjectItem *pItem = wxGetApp().GetMainFrame()->GetSelectedProjectItem();
	if( pItem )
	{
		pItem->OnEditItem( wxGetApp().GetMainFrame() );
	}
}

void udProjectManager::OnIdle(wxIdleEvent& event)
{
	if( m_fShowProperties )
	{
		if( m_pSplitter->GetSashPosition() == m_nPropsSashPosition) Disconnect(wxEVT_IDLE, wxIdleEventHandler( udProjectManager::OnIdle ) );
		
		m_pSplitter->SetSashPosition( m_nPropsSashPosition );
	}
}

void udProjectManager::OnOrganizeCI(wxCommandEvent& event)
{
	m_fOrganizeCI = !m_fOrganizeCI;
}

void udProjectManager::OnUpdateOrganizeCI(wxUpdateUIEvent& event)
{
	event.Check( m_fOrganizeCI );
}

