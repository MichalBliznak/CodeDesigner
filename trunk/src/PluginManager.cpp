#include "Art.h"
#include "XS2PG.h"
#include "PluginManager.h"
#include "UMLDesignerMain.h"
#include "UMLDesignerApp.h"

#include <wx/listimpl.cpp>
#include <wx/arrimpl.cpp>
#include <wx/dir.h>

WX_DEFINE_LIST(PluginList);
WX_DEFINE_LIST(LibraryList);
WX_DEFINE_LIST(ProjectSettingsList);
WX_DEFINE_OBJARRAY(PluginInfoArray);

int udPluginManager::m_ComponentIndex = IDT_PALETTE_MIN_TOOL_ID + 1;
int udPluginManager::m_DiagramIndex = IDM_PROJ_MIN_DIAG_ID;
long udPluginManager::m_MenuIndex = ID_CODEDESIGNER_HIGHEST + 1;

// plugin manager settings class ///////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS( udPluginCategory, udSettingsCategory);

udPluginCategory::udPluginCategory() : udSettingsCategory( wxT("Plugins category") )
{
	m_arrActivePlugins.Add( wxT("<uninitialized>") );
	
	XS_SERIALIZE( m_arrActivePlugins, wxT("Active plugins") );
}

udPluginManSettings::udPluginManSettings()
{
	SetSerializerRootName( wxT("plugins") );
	SetSerializerOwner( wxT("CodeDesigner") );
	SetSerializerVersion( wxT("1") );
	
}

void udPluginManSettings::CreateCategories()
{
	AddItem( GetRootItem(), new udPluginCategory() );
}


// constructor and destructor //////////////////////////////////////////////////

udPluginManager::udPluginManager()
{
	m_lstPlugins.DeleteContents( true );
	m_lstLibraries.DeleteContents( true );
	m_lstProjectSettings.DeleteContents( true );
	
	m_Frame = NULL;

	SetThis( this );
}

udPluginManager::~udPluginManager()
{
	SetThis( NULL );
}

// implementation //////////////////////////////////////////////////////////////

IProject* udPluginManager::GetActiveProject()
{
	return (IProject*) wxGetApp().GetActiveProject();
}

wxAuiNotebook* udPluginManager::GetMainNotebook()
{
	return m_Frame->GetMainNotebook();
}

wxMenuBar* udPluginManager::GetMenuBar()
{
	return m_Frame->GetMenuBar();
}

wxStatusBar* udPluginManager::GetStatusBar()
{
	return m_Frame->GetStatusBar();
}

void udPluginManager::RegisterDiagram(const udDiagramInfo& info)
{
	// register new diagram type
	m_Frame->GetDiagrams().Add( udDiagramType( GetNewDiagramId(), info.GetName(), info.GetDataClassName() ) );//, info.GetCanvasClassName() ) );
	udArt::AddArt( info.GetIcon(), info.GetDataClassName());
	
	// register diagram components
	PaletteArray *arrPalette = new PaletteArray();
	m_mapElementPalettes[info.GetName()] = arrPalette;
 
	const DiagramComponentArray& arrComponents = info.GetComponentArray();
	for( size_t i = 0; i < arrComponents.GetCount(); i ++ )
	{
		udDiagramComponentInfo& cinfo = arrComponents[i];
		arrPalette->Add( udPaletteItem( GetNewComponentId(), cinfo.GetIcon(), cinfo.GetDescription(), cinfo.GetClassName(), cinfo.GetDataClassName(), (udPaletteItem::PITYPE) cinfo.GetType()) );
		udArt::AddArt( cinfo.GetIcon(), cinfo.GetClassName() );
	}
}

void udPluginManager::RegisterEventListener(IPlugin* plugin)
{
	m_Frame->RegisterEventListener( plugin );
}

void udPluginManager::SendProjectEvent(wxEventType cmdType, int id, udProjectItem* item, udProjectItem* parent, const wxString& data, bool delayed)
{
	m_Frame->SendProjectEvent( cmdType, id, item, parent, data, delayed);
}

void udPluginManager::UnregisterEventListener(IPlugin* plugin)
{
	m_Frame->UnregisterEventListener( plugin );
}

void udPluginManager::LoadPlugins()
{
	const int nAPIVERSION = 1;
	
	// load/create plugin manager settings
	wxString sSettingsPath = wxGetApp().GetSettingsPath() + wxT("plugins.xml");
	m_Settings.DeserializeFromXml( sSettingsPath );
		
	wxArrayString& arrActivePlugins = m_Settings.GetProperty( wxT("Active plugins") )->AsStringArray();
	
	//const wxString &sAppPath = wxGetApp().GetPath();
	wxString ext;
	
#if defined (__WXGTK__) 
	ext = wxT("so");
#elif defined (__WXMAC__)
	ext = wxT("dylib");
#else
	ext = wxT("dll");
#endif

#ifndef NDEBUG
	wxString sFileSpec( wxT( "*_d." ) + ext );
#else
	wxString sFileSpec( wxT( "*." ) + ext );
#endif

	wxDynamicLibrary *pDl = NULL;
	
	wxArrayString arrPluginNames;
	//wxDir::GetAllFiles( sAppPath + wxT("plugins"), &arrPluginNames, sFileSpec, wxDIR_FILES );
	wxDir::GetAllFiles( wxGetApp().GetPluginsPath(), &arrPluginNames, sFileSpec, wxDIR_FILES );
	
	// force loading of all available plugins after reset of application settings
	bool fForceLoad = false;
	if( arrActivePlugins.Index( wxT("<uninitialized>") ) != wxNOT_FOUND )
	{
		fForceLoad = true;
		arrActivePlugins.Clear();
	}
		
	for( size_t i = 0; i < arrPluginNames.GetCount(); i++ )
	{
		wxString sFileName( arrPluginNames[i] );
		
		#ifdef NDEBUG
		if( sFileName.Contains( wxT("_d.") + ext ) ) continue;
		#endif

		// try to load the library
		pDl = new wxDynamicLibrary();
		if( !pDl->Load( sFileName ) )
		{
			UMLDesignerApp::Log( wxT("ERROR: Unable to load plugin: ") + sFileName );
			delete pDl;
			continue;
		}
		
		// try to get plugin info function
		GET_PLUGIN_INFO_FUNC PluginInfo = (GET_PLUGIN_INFO_FUNC) pDl->GetSymbol( wxT("GetPluginInfo") );
		if( !PluginInfo )
		{
			delete pDl;
			continue;
		}
		
		// test whether the plugin's API matches current version
		udPluginInfo pluginInfo = PluginInfo();
		if( (pluginInfo.GetAPIVersionMin() >= nAPIVERSION) &&
			(pluginInfo.GetAPIVersionMax() <= nAPIVERSION) )
		{
			m_arrPluginInfo.Add(pluginInfo);
			
			if( fForceLoad || (arrActivePlugins.Index( pluginInfo.GetName() ) != wxNOT_FOUND) )
			{
				if( fForceLoad ) arrActivePlugins.Add( pluginInfo.GetName() );
				
				// try to get plugin construction function
				GET_PLUGIN_CREATE PluginCreate = (GET_PLUGIN_CREATE) pDl->GetSymbol( wxT("CreatePlugin") );
				if( !PluginCreate )
				{
					arrActivePlugins.Remove( pluginInfo.GetName() );
					delete pDl;
					continue;
				}
				
				// create plugin instance
				IPlugin* pPlugin = PluginCreate( this );
				if( pPlugin ) //&& pPlugin->OnInit() )
				{
					m_lstPlugins.Append( pPlugin );
					m_lstLibraries.Append( pDl );
					
					//UMLDesignerApp::Log( wxT("Plugin '") + pPlugin->GetInfo().GetName() + wxT("' has been successfully loaded.") );
				}
				else
				{
					arrActivePlugins.Remove( pluginInfo.GetName() );
					delete pPlugin;
					delete pDl;
				}
			}
			else
				delete pDl;
		}
	}
}

void udPluginManager::UnloadPlugins()
{
	// store plugin manager settings
	wxString sSettingsPath = wxGetApp().GetSettingsPath() + wxT("plugins.xml");
	m_Settings.SerializeToXml( sSettingsPath );
	
	// perform clean-up
	m_lstPlugins.Clear();
	m_lstLibraries.Clear();
}

bool udPluginManager::InitializePlugins()
{
	bool fSuccess = true;
	
	for( PluginList::iterator it = m_lstPlugins.begin(); it != m_lstPlugins.end(); ++it )
	{
		if( !(*it)->OnInit() )
		{
			UMLDesignerApp::Log( wxT("WARNING: Couldn't initialize'") + (*it)->GetInfo().GetName() + wxT("' plugin.") );
			fSuccess = false;
		}
	}
	
	return fSuccess;
}

bool udPluginManager::UninitializePlugins()
{
	bool fSuccess = true;
	
	for( PluginList::iterator it = m_lstPlugins.begin(); it != m_lstPlugins.end(); ++it )
	{
		if( (*it)->OnExit() != 0 )
		{
			UMLDesignerApp::Log( wxT("WARNING: Couldn't uninitialize'") + (*it)->GetInfo().GetName() + wxT("' plugin correctly.") );
			fSuccess = false;
		}
	}
	
	m_lstProjectSettings.Clear();
	return fSuccess;
}

void udPluginManager::RegisterFriendlyName(const wxString& mapname, const wxString& origname, const wxString& friendlyname)
{
	udXS2PG::RegisterFriendlyName( mapname, origname, friendlyname );
}

void udPluginManager::UnregisterFriendlyName(const wxString& mapname, const wxString& origname)
{
	udXS2PG::UnregisterFriendlyName( mapname, origname );
}

void udPluginManager::ConnectDiagramEvents(udDiagramCanvas *diagram, bool enable)
{
	m_Frame->ConnectDiagramEvents( diagram, enable );
}

void udPluginManager::EnableInternalEvents(bool enable)
{
	UMLDesignerFrame::EnableInternalEvents( enable );
}

udDiagramCanvas* udPluginManager::GetActiveCanvas()
{
	return m_Frame->GetActiveCanvas();
}

const wxString& udPluginManager::GetAppPath()
{
	return wxGetApp().GetPath();
}

wxString udPluginManager::GetResourcesPath()
{
	return wxGetApp().GetResourcesPath();
}

wxImageList* udPluginManager::GetArt()
{
	return udArt::GetImageList();
}

int udPluginManager::GetArtIndex(const wxString& name)
{
	return udArt::GetImageIndex(name);
}

wxBitmap udPluginManager::GetArtBitmap(const wxString& name)
{
	return udArt::GetBitmap( name );
}

wxFrame* udPluginManager::GetMainFrame()
{
	return m_Frame;
}

IProject* udPluginManager::GetProject()
{
	return udProject::Get();
}

udLanguage* udPluginManager::GetSelectedLanguage()
{
	return m_Frame->GetSelectedLanguage();
}

udProjectItem* udPluginManager::GetSelectedProjectItem()
{
	return m_Frame->GetSelectedProjectItem();
}

wxSFThumbnail* udPluginManager::GetThumbnail()
{
	return m_Frame->GetThumbnail();
}

bool udPluginManager::IsProjManLinked()
{
	return m_Frame->GetProjectManager()->IsLinked();
}

void udPluginManager::Log(const wxString& msg)
{
	UMLDesignerApp::Log( msg );
}

udSettings& udPluginManager::GetAppSettings()
{
	return wxGetApp().GetSettings();
}

udSettings& udPluginManager::GetProjectSettings()
{
	return udProject::Get()->GetSettings();
}

void udPluginManager::RegisterArtBitmap(const wxString& path, const wxString& name)
{
	udArt::AddArt(path, name);
}

void udPluginManager::UnregisterArtBitmap(const wxString& name)
{
	udArt::RemoveArt(name);
}

udDiagramItem* udPluginManager::GetActiveDiagram()
{
	return m_Frame->GetActiveDiagram();
}

void udPluginManager::SaveDiagramState(udDiagramItem* diag)
{
	m_Frame->SaveDiagramState( diag );
}

void udPluginManager::RegisterCodePackage(const wxString& classname, const wxString& packagename)
{
	m_Frame->GetCodePackages()[classname] = packagename;
}

void udPluginManager::UnregisterCodePackage(const wxString& classname)
{
	m_Frame->GetCodePackages().erase(classname);
}

void udPluginManager::RegisterCodeGenerator(const udGeneratorInfo& info)
{
	m_Frame->GetGenerators().Add(info);
}

void udPluginManager::UnregisterCodeGenerator(const udGeneratorInfo& info)
{
	GeneratorsArray& arrGens = m_Frame->GetGenerators();
	
	for( size_t i = 0; i < arrGens.GetCount(); i++ )
	{
		if( arrGens[i].GetClassName() == info.GetClassName() )
		{
			arrGens.RemoveAt(i);
			break;
		}
	}
}

udGeneratorInfo* udPluginManager::FindGeneratorInfoByClassName(const wxString& classname)
{
	return m_Frame->FindGeneratorInfoByClassName( classname );
}

udGeneratorInfo* udPluginManager::FindGeneratorInfoByName(const wxString& name)
{
	return m_Frame->FindGeneratorInfoByName( name );
}

GeneratorsArray& udPluginManager::GetGenerators()
{
	return m_Frame->GetGenerators();
}

void udPluginManager::RegisterSettings(udSettingsCategory* settings, SETTINGSTYPE type)
{
	if( settings )
	{
		switch( type )
		{
			case IPluginManager::settingsAPPLICATION:
			{
				udSettings& AppSettings = wxGetApp().GetSettings();
				if( !AppSettings.GetCategory( settings->GetName() ) )
				{
					AppSettings.AddItem( (xsSerializable*)NULL, settings );
				}
				else
					delete settings;
			}
			break;
			
			case IPluginManager::settingsPROJECT:
			{
				// insert project settings to list which will be appended to newly loaded project's settings
				m_lstProjectSettings.Append( settings );
				
				// update current project settings
				AppendPluginsSettings( udProject::Get()->GetSettings() );
			}
			break;
		}
	}
}

void udPluginManager::AppendPluginsSettings(udSettings& projsettings)
{
	for( ProjectSettingsList::iterator it = m_lstProjectSettings.begin(); it != m_lstProjectSettings.end(); ++it )
	{
		if( !projsettings.GetCategory( (*it)->GetName() ) )
		{
			projsettings.AddItem( (xsSerializable*)NULL, (xsSerializable*)(*it)->Clone() );
		}
	}
}

void udPluginManager::RegisterCommentProcessor(const wxString& type, udCommentProcessor* processor)
{
	udGenerator::RegisterCommentProcessor( type, processor );
}

void udPluginManager::UnregisterCommentProcessor(const wxString& type)
{
	udGenerator::UnregisterCommentProcessor( type );
}

void udPluginManager::ClearLog()
{
	UMLDesignerApp::ClearLog();
}

wxString udPluginManager::GetCodePackage(const wxString& classname)
{
	return m_Frame->GetCodePackages()[classname];
}

bool udPluginManager::IsProjManOrganised()
{
	return m_Frame->GetProjectManager()->IsOrganized();
}

