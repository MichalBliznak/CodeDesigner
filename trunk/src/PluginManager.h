#ifndef _CDPLUGINMANAGER_H
#define _CDPLUGINMANAGER_H

#include <wx/list.h>
#include <wx/dynlib.h>
#include <wx/dynarray.h>

#include "interfaces/IPlugin.h" // Base class: IPluginManager

#include "projectbase/ProjectBase.h"

WX_DECLARE_LIST(IPlugin, PluginList);
WX_DECLARE_LIST(wxDynamicLibrary, LibraryList);
WX_DECLARE_LIST(udSettingsCategory, ProjectSettingsList);

WX_DECLARE_OBJARRAY(udPluginInfo, PluginInfoArray);

class UMLDesignerFrame;

class udPluginCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udPluginCategory);
	
	udPluginCategory();
	
	wxArrayString m_arrActivePlugins;
};

class udPluginManSettings : public udSettings
{
public:
	udPluginManSettings();
	
	virtual void CreateCategories();
};

class udPluginManager : public IPluginManager {

public:
	udPluginManager();
	virtual ~udPluginManager();
	
	void LoadPlugins();
	void UnloadPlugins();
	bool InitializePlugins();
	bool UninitializePlugins();
	void SetManagedFrame(UMLDesignerFrame *frame) {m_Frame = frame;};
	
	PluginInfoArray& GetPluginsInfo() {return m_arrPluginInfo;}
	PluginList& GetPluginsList() {return m_lstPlugins;}
	udSettings& GetSettings() {return m_Settings;}
	
	void AppendPluginsSettings( udSettings& projsettings );

	// interface implementation
	virtual IProject* GetActiveProject();
	virtual wxAuiNotebook* GetMainNotebook();
	virtual wxMenuBar* GetMenuBar();
	virtual wxStatusBar* GetStatusBar();
	virtual udDiagramCanvas* GetActiveCanvas();
	virtual udDiagramItem* GetActiveDiagram();
	virtual const wxString& GetAppPath();
	virtual wxString GetResourcesPath();
	virtual wxString GetCodePackage(const wxString& classname);
	virtual wxImageList* GetArt();
	virtual wxBitmap GetArtBitmap(const wxString& name);
	virtual int GetArtIndex(const wxString& name);
	virtual wxFrame* GetMainFrame();
	virtual IProject* GetProject();
	virtual udLanguage* GetSelectedLanguage();
	virtual udProjectItem* GetSelectedProjectItem();
	virtual wxSFThumbnail* GetThumbnail();
	
	virtual udSettings& GetAppSettings();
	virtual udSettings& GetProjectSettings();
	
	virtual GeneratorsArray& GetGenerators();
	virtual udGeneratorInfo* FindGeneratorInfoByClassName(const wxString& classname);
	virtual udGeneratorInfo* FindGeneratorInfoByName(const wxString& name);
	
	virtual void SendProjectEvent(wxEventType cmdType, int id, udProjectItem* item, udProjectItem* parent, const wxString& data, bool delayed);
	
	virtual void RegisterDiagram(const udDiagramInfo& info);
	virtual void RegisterSettings(udSettingsCategory* settings, SETTINGSTYPE type);
	virtual void RegisterEventListener(IPlugin *plugin);
	virtual void UnregisterEventListener(IPlugin *plugin);
	virtual void RegisterFriendlyName(const wxString& mapname, const wxString& origname, const wxString& friendlyname);
	virtual void UnregisterFriendlyName(const wxString& mapname, const wxString& origname);
	virtual void RegisterArtBitmap(const wxString& path, const wxString& name);
	virtual void UnregisterArtBitmap(const wxString& name);
	virtual void RegisterCodePackage(const wxString& classname, const wxString& packagename);
	virtual void UnregisterCodePackage(const wxString& classname);
	virtual void RegisterCodeGenerator(const udGeneratorInfo& info);
	virtual void UnregisterCodeGenerator(const udGeneratorInfo& info);
	virtual void RegisterCommentProcessor(const wxString& type, udCommentProcessor *processor);
	virtual void UnregisterCommentProcessor(const wxString& type);

	virtual void ConnectDiagramEvents(udDiagramCanvas *diagram, bool enable);
	virtual void EnableInternalEvents(bool enable);
	
	virtual void SaveDiagramState(udDiagramItem *diag);
	
	virtual bool IsProjManLinked();
	virtual bool IsProjManOrganised();
	virtual void Log(const wxString& msg);
	virtual void ClearLog();
	
	static int GetNewComponentId() {return m_ComponentIndex++;}
	static int GetNewDiagramId() {return m_DiagramIndex++;}
	virtual long GetNewMenuId(int step = 1) {return m_MenuIndex+=step;}
	
protected:
	UMLDesignerFrame *m_Frame;
	static int m_ComponentIndex;
	static int m_DiagramIndex;
	static long m_MenuIndex;
	
	PluginList m_lstPlugins;
	PluginInfoArray m_arrPluginInfo;
	LibraryList m_lstLibraries;
	ProjectSettingsList m_lstProjectSettings;
	
	udPluginManSettings m_Settings;
};

#endif // _CDPLUGINMANAGER_H
