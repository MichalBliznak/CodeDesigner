/*********************************************************************
 * Name:      	CodeLite.h
 * Purpose:   	Declares CodeLite integration plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#ifndef _CODELITE_H_
#define _CODELITE_H_

// include import/export definitions
#include "interfaces/Defs.h"
// common interfaces
#include "interfaces/IPlugin.h"
#include "interfaces/IPluginManager.h"

#include "projectbase/ProjectBase.h"

#include <wx/ipc.h>

#define uddvDEFAULT_PORT_VALUE wxT("50000")
#define uddvDEFAULT_KEEP_ALIVE true
#define uddvDEFAULT_UPDATE_WORKSPACE true

////////////////////////////////////////////////////////////////////////////////
// plugin class ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class CDClient;

/**
 * \class udCodeLitePlugin
 * \brief Class encapsulating CodeLite integration class.
 */
class udCodeLitePlugin : public IPlugin
{
public:
	udCodeLitePlugin(IPluginManager *manager);
	virtual ~udCodeLitePlugin() {}
	
	// pure abstract virtual functions (must be implemented)
	virtual bool OnInit();
	virtual int OnExit();
	virtual udPluginInfo GetInfo();
	
	// optional virtual functions for 'GUI' plugin
	virtual wxMenu* CreateMenu();
	
protected:
	CDClient *m_Client;
	wxString m_Files;

	void StartClient();
	void LogClientStatus();

	// user-defined event handlers
	void OnProjectGenerating(udProjectEvent &event);
	void OnProjectGenerated(udProjectEvent &event);
	void OnFileAdded(udProjectEvent &event);
	void OnReconnect(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);
};

class CDConnection : public wxConnection
{
public:
	CDConnection(CDClient *client);
	virtual ~CDConnection();
	
	virtual bool OnDisconnect();
#if wxVERSION_NUMBER < 2900
	virtual bool Poke(const wxString& item, wxChar *data, int size = -1, wxIPCFormat format = wxIPC_TEXT);
#else
	virtual bool Poke(const wxString& item, const wchar_t *data);
#endif
	
protected:
	CDClient *m_Client;
};

class CDClient : public wxClient
{
public:
	CDClient();
	virtual ~CDClient();
	
	void Disconnect();
	bool IsConnected() { return m_Connection != NULL; };
    CDConnection *GetConnection() { return m_Connection; };
	
	virtual wxConnectionBase *OnMakeConnection();
	
protected:
	CDConnection *m_Connection;
};

////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// plugin settings /////////////////////////////////////////////////////////////

/**
 * \class udCodeLiteSettingsCategory
 * \brief Class encapsulating plugin application settings category.
 */
class WXDLLIMPEXP_CD udCodeLiteSettingsCategory : public udSettingsCategory
{
public:
	XS_DECLARE_CLONABLE_CLASS(udCodeLiteSettingsCategory);
	
	udCodeLiteSettingsCategory();
	udCodeLiteSettingsCategory(const udCodeLiteSettingsCategory& obj);
	virtual ~udCodeLiteSettingsCategory();
	
	// public data members
	wxString m_sPort;
	bool m_fKeepAlive;
	bool m_fUpdateWorkspace;
};

extern udCodeLitePlugin *thePlugin;

#endif //_CODELITE_H_

