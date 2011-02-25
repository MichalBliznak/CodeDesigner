/*********************************************************************
 * Name:      	CodeLite.cpp
 * Purpose:   	Implements CodeLite integration plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#include "CodeLite.h"
#include "projectbase/Common.h"

#include <wx/txtstrm.h>
 
////////////////////////////////////////////////////////////////////////////////
// plugin //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

udCodeLitePlugin *thePlugin = NULL;

// create plugin-specific GUI identifiers
static long IDM_RECONNECT = IPluginManager::Get()->GetNewMenuId();
static long ID_ALIVE_TIMER = IPluginManager::Get()->GetNewMenuId();

// define the plugin entry point
extern "C" WXDLLIMPEXP_CD IPlugin *CreatePlugin(IPluginManager *manager)
{
	if (thePlugin == NULL)
	{
		thePlugin = new udCodeLitePlugin(manager);
	}
	
	return thePlugin;
}

extern "C" WXDLLIMPEXP_CD udPluginInfo GetPluginInfo()
{
	// set plugin info
	udPluginInfo info;
	
	info.SetAuthor( wxT("Michal Bližňák") );
	info.SetName( wxT("CodeLite") );
	info.SetDescription( wxT("CodeLite integration plugin.") );
	info.SetType( udPluginInfo::ptGUI );
	info.SetVersion( wxT("1.0") );
	info.SetAPIVersionMin( 1 );
	info.SetAPIVersionMax( 1 );
	
	return info;
}

udCodeLitePlugin::udCodeLitePlugin(IPluginManager *manager) : IPlugin(manager)
{
	m_Client = NULL;
}

bool udCodeLitePlugin::OnInit()
{
	// register plugin settings
	m_PluginManager->RegisterSettings( new udCodeLiteSettingsCategory(), IPluginManager::settingsAPPLICATION );
	
	// connect events
	m_PluginManager->RegisterEventListener( this );
	
	Connect( wxID_ANY, wxEVT_CD_PROJECT_AFTER_GENERATION, udProjectEventHandler(udCodeLitePlugin::OnProjectGenerated) );
	m_PluginManager->GetMainFrame()->Connect( IDM_RECONNECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(udCodeLitePlugin::OnReconnect), NULL, this );
	
	// start client
	StartClient();
	
	// start 'alive' timer
	Connect( ID_ALIVE_TIMER, wxEVT_TIMER, wxTimerEventHandler(udCodeLitePlugin::OnTimer) );
	m_Timer.SetOwner( this, ID_ALIVE_TIMER );
	m_Timer.Start( 10000 );
	
	return true;
}

int udCodeLitePlugin::OnExit()
{
	// note: plugin settings cannot be unregistered
	
	// close IPC client
	m_Timer.Stop();
	
	delete m_Client;
	
	// disconnect events
	m_PluginManager->UnregisterEventListener( this );
	
	Disconnect( ID_ALIVE_TIMER, wxEVT_TIMER, wxTimerEventHandler(udCodeLitePlugin::OnTimer) );
	Disconnect( wxID_ANY, wxEVT_CD_PROJECT_AFTER_GENERATION, udProjectEventHandler(udCodeLitePlugin::OnProjectGenerated) );	
	m_PluginManager->GetMainFrame()->Disconnect( IDM_RECONNECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(udCodeLitePlugin::OnReconnect), NULL, this );
	
	return 0;
}

udPluginInfo udCodeLitePlugin::GetInfo()
{
	return GetPluginInfo();
}

void udCodeLitePlugin::StartClient()
{
	delete m_Client;
	
	m_Client = new CDClient();
}

void udCodeLitePlugin::LogClientStatus()
{
	wxString sPort = IPluginManager::Get()->GetAppSettings().GetPropertyAsString( wxT("Communication port"), uddvDEFAULT_PORT_VALUE );
	
	if( m_Client->IsConnected() )
	{
		IPluginManager::Get()->Log( wxString::Format( wxT("CodeLite plugin: IPC connection on port %s estabilished."), sPort.c_str() ) );
	}
	else
		IPluginManager::Get()->Log( wxString::Format( wxT("WARNING: CodeLite plugin: IPC connection on port %s failed."), sPort.c_str() ) );

}

////////////////////////////////////////////////////////////////////////////////
// registration of custom GUI controls /////////////////////////////////////////

wxMenu* udCodeLitePlugin::CreateMenu()
{
	// create plugin menu (if needed) here...
	
	wxMenu *pMenu = new wxMenu();
	pMenu->Append( IDM_RECONNECT, wxT("Reconnect") );
	
	return pMenu;
}

void udCodeLitePlugin::OnProjectGenerated(udProjectEvent& event)
{
	if( m_Client->IsConnected() )
	{
		if( IPluginManager::Get()->GetAppSettings().GetProperty( wxT("Re-tag CodeLite workspace") )->AsBool() )
		{
			m_Client->GetConnection()->Execute( wxT("RETAG WORKSPACE") );
		}
	}
}

void udCodeLitePlugin::OnReconnect(wxCommandEvent& event)
{	
	StartClient();
	LogClientStatus();
}

void udCodeLitePlugin::OnTimer(wxTimerEvent& event)
{
	if( IPluginManager::Get()->GetAppSettings().GetProperty( wxT("Keep connection alive") )->AsBool() )
	{
		if( !m_Client->IsConnected() )
		{
			StartClient();
			LogClientStatus();
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// plugin application settings class ///////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udCodeLiteSettingsCategory, udSettingsCategory);

udCodeLiteSettingsCategory::udCodeLiteSettingsCategory() : udSettingsCategory( wxT("CodeLite") )
{
	m_sPort = uddvDEFAULT_PORT_VALUE;
	m_fKeepAlive = uddvDEFAULT_KEEP_ALIVE;
	m_fRetagWorkspace = uddvDEFAULT_RETAG_WORKSPACE;
	
	// serialize class member (always, if needed)
	XS_SERIALIZE( m_sPort, wxT("Communication port") );
	XS_SERIALIZE( m_fKeepAlive, wxT("Keep connection alive") );
	XS_SERIALIZE( m_fRetagWorkspace, wxT("Re-tag CodeLite workspace") );
}

udCodeLiteSettingsCategory::udCodeLiteSettingsCategory(const udCodeLiteSettingsCategory& obj) : udSettingsCategory( obj )
{
	SetName( wxT("CodeLite") );
	
	m_sPort = obj.m_sPort;
	m_fKeepAlive = obj.m_fKeepAlive;
	m_fRetagWorkspace = obj.m_fRetagWorkspace;

	XS_SERIALIZE( m_sPort, wxT("Communication port") );
	XS_SERIALIZE( m_fKeepAlive, wxT("Keep connection alive") );
	XS_SERIALIZE( m_fRetagWorkspace, wxT("Re-tag CodeLite workspace") );
}

udCodeLiteSettingsCategory::~udCodeLiteSettingsCategory()
{
}

////////////////////////////////////////////////////////////////////////////////
// IPC classes /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


CDClient::CDClient()
{
	wxString sPort = IPluginManager::Get()->GetAppSettings().GetPropertyAsString( wxT("Communication port"), uddvDEFAULT_PORT_VALUE );
	
	m_Connection = (CDConnection*) MakeConnection( wxT("localhost"), sPort, wxT("RETAG") );
}

CDClient::~CDClient()
{
	Disconnect();
}

void CDClient::Disconnect()
{
	if( m_Connection )
	{
		m_Connection->Disconnect();
		delete m_Connection;
		m_Connection = NULL;
	}
}

wxConnectionBase* CDClient::OnMakeConnection()
{
	return new CDConnection( this );
}

////////////////////////////////////////////////////////////////////////////////

CDConnection::CDConnection(CDClient* client)
{
	m_Client = client;
}

CDConnection::~CDConnection()
{
}

bool CDConnection::Execute(const wxChar* data, int size, wxIPCFormat format)
{
    bool retval = wxConnection::Execute(data, size, format);
    if (!retval) IPluginManager::Get()->Log( wxT("WARNING: IPC Execute failed") );
	
    return retval;
}

bool CDConnection::OnDisconnect()
{
	m_Client->Disconnect();
	return true;
}
