#include "ManagePluginsDialog.h"
#include "../UMLDesignerMain.h"
#include "../UMLDesignerApp.h"

// constructor and destructor ///////////////////////////////////////////////////////////

udManagePluginsDialog::udManagePluginsDialog(wxWindow *parent) : _ManagePluginsDialog(parent)
{
}

udManagePluginsDialog::~udManagePluginsDialog()
{
}

// virtual event handlers ///////////////////////////////////////////////////////////////

void udManagePluginsDialog::OnInitDialog(wxInitDialogEvent& event)
{
	udSettings& Settings = wxGetApp().GetPluginManager().GetSettings();
	PluginInfoArray& arrPluginsInfo = wxGetApp().GetPluginManager().GetPluginsInfo();
	
	wxArrayString& arrActivePlugins = Settings.GetProperty( wxT("Active plugins") )->AsStringArray();
	
	// fill check list box
	for( size_t i = 0; i < arrPluginsInfo.GetCount(); i++ )
	{
		udPluginInfo& info = arrPluginsInfo[i];
		m_checkListPlugins->Append( info.GetName() );
		
		if( arrActivePlugins.Index( info.GetName() ) != wxNOT_FOUND ) m_checkListPlugins->Check( i );
	}
	
	if( arrPluginsInfo.GetCount() > 0 )
	{
		FillPluginInfo(0);
	}
	
	event.Skip();
}

void udManagePluginsDialog::OnPluginSelected(wxCommandEvent& event)
{
	int nIndex = m_checkListPlugins->GetSelection();
	if( nIndex != wxNOT_FOUND )
	{
		FillPluginInfo(nIndex);
	}
}

void udManagePluginsDialog::OnOk(wxCommandEvent& event)
{
	udSettings& Settings = wxGetApp().GetPluginManager().GetSettings();
	wxArrayString& arrPlugins = Settings.GetProperty( wxT("Active plugins") )->AsStringArray();
	
	// clear previous active plugins
	arrPlugins.Clear();
	
	// get checked plugins
	for( size_t nIndex = 0; nIndex < m_checkListPlugins->GetCount(); nIndex++ )
	{
		if( m_checkListPlugins->IsChecked( nIndex ) ) arrPlugins.Add( m_checkListPlugins->GetString( nIndex ) );
	}
	
	wxMessageBox( wxT("All changes will take an effect after application's restart."), wxT("CodeDesigner") );
	
	EndModal(wxID_OK);
}

void udManagePluginsDialog::FillPluginInfo(int index)
{
	PluginInfoArray& arrPluginsInfo = wxGetApp().GetPluginManager().GetPluginsInfo();
	
	if( arrPluginsInfo.GetCount() > index)
	{
		udPluginInfo& info = arrPluginsInfo[index];
		
		// clear plugin info
		m_listCtrlPluginInfo->ClearAll();
		
		// fill plugin info
		m_listCtrlPluginInfo->InsertColumn(0, wxT("Plugin info"));
		m_listCtrlPluginInfo->InsertColumn(1, wxT(""));
		
		// name
		m_listCtrlPluginInfo->InsertItem(0, wxT("Name"));
		m_listCtrlPluginInfo->SetItem(0, 1, info.GetName());
		
		// description
		m_listCtrlPluginInfo->InsertItem(1, wxT("Description"));
		m_listCtrlPluginInfo->SetItem(1, 1, info.GetDescription());
		//m_listCtrlPluginInfo->SetItemBackgroundColour(1, wxColour(200, 200, 200));
		
		// author
		m_listCtrlPluginInfo->InsertItem(2, wxT("Author"));
		m_listCtrlPluginInfo->SetItem(2, 1, info.GetAuthor());
		
		// version
		m_listCtrlPluginInfo->InsertItem(3, wxT("Version"));
		m_listCtrlPluginInfo->SetItem(3, 1, info.GetVersion());
		//m_listCtrlPluginInfo->SetItemBackgroundColour(3, wxColour(200, 200, 200));
		
		m_listCtrlPluginInfo->SetColumnWidth(0, wxLIST_AUTOSIZE);
		m_listCtrlPluginInfo->SetColumnWidth(1, wxLIST_AUTOSIZE);
	}
}
