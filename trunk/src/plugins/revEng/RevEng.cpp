/*********************************************************************
 * Name:      	RevEng.cpp
 * Purpose:   	Implements reverse code engineering plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#include "RevEng.h"
#include "gui/RevEngPanel.h"
#include "projectbase/Common.h"

#define udREVENG_VERSION wxT("1.0 Beta")

// TODO: LONG TERM: create state charts from function bodies (for both standalone functions and class member functions).
// TODO: support for namespace (if implemented in app core)
 
////////////////////////////////////////////////////////////////////////////////
// plugin //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

udReverseEngineeringPlugin *thePlugin = NULL;

// define the plugin entry point
extern "C" WXDLLIMPEXP_CD IPlugin *CreatePlugin(IPluginManager *manager)
{
	if (thePlugin == NULL)
	{
		thePlugin = new udReverseEngineeringPlugin(manager);
	}
	
	return thePlugin;
}

extern "C" WXDLLIMPEXP_CD udPluginInfo GetPluginInfo()
{
	// set plugin info
	udPluginInfo info;
	
	info.SetAuthor( wxT("Michal Bližňák") );
	info.SetName( wxT("Reverse Engineering") );
	info.SetDescription( wxT("Reverse code engineering plugin which uses CTAGS tool to parse source files.") );
	info.SetType( udPluginInfo::ptGUI );
	info.SetVersion( udREVENG_VERSION );
	info.SetAPIVersionMin( 1 );
	info.SetAPIVersionMax( 1 );
	
	return info;
}

udReverseEngineeringPlugin::udReverseEngineeringPlugin(IPluginManager *manager) : IPlugin(manager)
{
	// initialize plugin information
}

bool udReverseEngineeringPlugin::OnInit()
{	
	// register plugin settings
	m_PluginManager->RegisterSettings( new udRevEngAppSettingsCategory(), IPluginManager::settingsAPPLICATION );
	
	return true;
}

int udReverseEngineeringPlugin::OnExit()
{	
	return 0;
}

udPluginInfo udReverseEngineeringPlugin::GetInfo()
{
	return GetPluginInfo();
}

////////////////////////////////////////////////////////////////////////////////
// registration of custom GUI controls /////////////////////////////////////////

wxMenu* udReverseEngineeringPlugin::CreateMenu()
{
	// create plugin menu (if needed) here...
	
	return NULL;
}

udPaneInfo udReverseEngineeringPlugin::CreateAuiPane(wxWindow *parent)
{
	// create plugin Aui pane (if needed) here...
	
	udPaneInfo PaneInfo;
	
	PaneInfo.SetName( wxT("Reverse Engineering") );
	PaneInfo.SetBestSize( wxSize( 250, 400 ) );
	PaneInfo.SetPane( new udRevEngPanel(parent) );
	
	return PaneInfo;
}

udToolbarInfo udReverseEngineeringPlugin::CreateToolbar(wxWindow *parent)
{
	// create plugin toolbar (if needed) here...
	
	udToolbarInfo TbInfo;
	
	return TbInfo;
}

////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// plugin application settings class ///////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udRevEngAppSettingsCategory, udSettingsCategory);

udRevEngAppSettingsCategory::udRevEngAppSettingsCategory() : udSettingsCategory( wxT("Reverse Engineering") )
{
	m_CtagsPath = uddvDEFAULT_CTAGS;
	m_CPPExtensions = uddvDEFAULT_CTAGS_CPP_EXT;
	m_PythonExtensions = uddvDEFAULT_CTAGS_PYTHON_EXT;
	
	// serialize class member (always, if needed)
	XS_SERIALIZE( m_CtagsPath, wxT("CTAGS path") );
	XS_SERIALIZE( m_CPPExtensions, wxT("C/C++ file extensions") );
	XS_SERIALIZE( m_PythonExtensions, wxT("Python file extensions") );
}

udRevEngAppSettingsCategory::udRevEngAppSettingsCategory(const udRevEngAppSettingsCategory& obj) : udSettingsCategory( obj )
{
	SetName( wxT("Reverse Engineering") );
	
	m_CtagsPath = obj.m_CtagsPath;
	m_CPPExtensions = obj.m_CPPExtensions;
	m_PythonExtensions = obj.m_PythonExtensions;

	XS_SERIALIZE( m_CtagsPath, wxT("CTAGS path") );
	XS_SERIALIZE( m_CPPExtensions, wxT("C/C++ file extensions") );
	XS_SERIALIZE( m_PythonExtensions, wxT("Python file extensions") );
}

udRevEngAppSettingsCategory::~udRevEngAppSettingsCategory()
{
}



