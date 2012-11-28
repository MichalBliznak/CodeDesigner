#ifndef IPLUGINMANAGER_H
#define IPLUGINMANAGER_H

#include <wx/wx.h>
#include <wx/imaglist.h>
#include <wx/aui/auibook.h>
#include <wx/wxsf/wxShapeFramework.h>

#include "IDiagram.h"
#include "IGenerator.h"

class udLanguage;
class udGenerator;
class udProjectItem;
class udDiagramCanvas;
class udDiagramItem;
class IPlugin;
class IProject;
class udSettings;
class udSettingsCategory;
class GeneratorsArray;
class udCommentProcessor;

/**
 * \class IPluginManager
 * \author Michal
 * \date 14.2.2010
 * \file IPluginManager.h
 * \brief Plugin manager interface providing functionality needed for proper plugin initialization
 * and further usage. Every plugin will get a pointer to plugin interface at his startup.
 * \sa IPlugin
 */
class IPluginManager
{
public:	

	enum SETTINGSTYPE
	{
		settingsAPPLICATION,
		settingsPROJECT
	};
	
	virtual ~IPluginManager() {}
	
	// gui-related functions
	/**
	 * \brief Get pointer to CodeDesigner's main menu.
	 * \return Pointer to main menu
	 */
	virtual wxMenuBar* GetMenuBar() = 0;
	/**
	 * \brief Get pointer to CodeDesigner's status bar.
	 * \return Pointer to status bar
	 */
	virtual wxStatusBar* GetStatusBar() = 0;
	/**
	 * \brief Get pointer to main notebook where a diagrams are openend.
	 * \return Pointer to main notebook
	 */
	virtual wxAuiNotebook* GetMainNotebook() = 0;
	/**
	 * \brief Get pointer to diagram's thumbnail control.
	 * \return Pointer to thumbnail control
	 * \sa wxSFThumbnail
	 */
	virtual wxSFThumbnail* GetThumbnail() = 0;
	/**
	 * \brief Get active diagram canvas.
	 * \return Pointer to active diagram canvas
	 * \sa wxSFShapeCanvas
	 */
	virtual udDiagramCanvas* GetActiveCanvas() = 0;
	
	/**
	 * \brief Get active diagram.
	 * \return Pointer to currenlty selected diagram if any, otherwise NULL
	 * 'sa udDiagramItem, wxSFDiagramManager
	 */
	virtual udDiagramItem* GetActiveDiagram() = 0;
	/**
	 * \brief Get main application frame.
	 * \return Pointer to main application frame window
	 */
	virtual wxFrame* GetMainFrame() = 0;
	/**
	 * \brief Get application (executable) path.
	 * \return String containing application's path
	 */
	virtual const wxString& GetAppPath() = 0;
	/**
	 * \brief Get application's resources path.
	 * \return String containing application's resources path
	 */
	virtual wxString GetResourcesPath() = 0;
	/**
	 * \brief Get name of registered code items package.
	 * \return String containing code package name
	 */
	virtual wxString GetCodePackage(const wxString& classname) = 0;
	/**
	 * \brief Get image list stored art provider.
	 * \return Pointer to image list stored in art provider
	 */
	virtual wxImageList* GetArt() = 0;
	/**
	 * \brief Get bitmap stored in art provider.
	 * \param name Bitmap identifier used during registration of the bitmap in art provider.
	 * \return Bitmap (can be invalid if used identifier doesn't exist)
	 */
	virtual wxBitmap GetArtBitmap(const wxString& name) = 0;
	/**
	 * \brief Get index of bitmap stored in art provider.
	 * \param name Bitmap identifier used during registration of the bitmap in art provider.
	 * \return Index of bitmap stored in art provider (if exists)
	 */
	virtual int GetArtIndex(const wxString& name) = 0;
	/**
	 * \brief Get next free menu item ID ( applicable for any GUI control ).
	 * \param step Value by which the ID differs from previously returned ID
	 * \return New ID value
	 */
	virtual long GetNewMenuId(int step = 1) = 0;
	/**
	 * \brief Write given message to CodeDesigner's log window.
	 * \param msg Message to display. Note, that if the message contains 'ERROR' or 'WARNING' substrings
	 * then proper icon will be displayed in the log window as well.
	 */
	virtual void Log(const wxString& msg) = 0;
	/**
	 * \brief Clear log window.
	 */
	virtual void ClearLog() = 0;
	/**
	 * \brief Returns information whether selected of any diagram component or diagram canvas will
	 * select also relevant tree node in project structure tree.
	 * \return TRUE if the tree node will be selected as well.
	 */
	virtual bool IsProjManLinked() = 0;
	/**
	 * \brief Returns information whether newly created code items will be auto-organised into
	 * pre-registered code packages.
	 * \return TRUE if auto-organisation is enabled.
	 */
	virtual bool IsProjManOrganised() = 0;
	
	// project-related functions
	/**
	 * \brief Get current active project.
	 * \return Pointer to current active project
	 * \sa IProject
	 */
	virtual IProject* GetProject() = 0;
	/**
	 * \brief Get currently selected output language.
	 * \return Pointer to selected language
	 * \sa udLanguage
	 */
	virtual udLanguage* GetSelectedLanguage() = 0;
	/**
	 * \brief Get selected project item.
	 * \return Pointer to selected project item if any, otherwise NULL
	 */
	virtual udProjectItem* GetSelectedProjectItem() = 0;
	/**
	 * \brief Get array containing info about all registered code generators
	 * \return Reference to array.
	 * \sa udGeneratorInfo
	 */
	virtual GeneratorsArray& GetGenerators() = 0;
	/**
	 * \brief Find registered code generator by its friendly name.
	 * \param name Generator's (user-readable) name (e.g. 'Python Class Generator')
	 * \return Pointer to code generator if exists, otherwise NULL
	 */
	virtual udGeneratorInfo* FindGeneratorInfoByName(const wxString& name) = 0;
	/**
	 * \brief Find registered code generator by its class name.
	 * \param classname Generator's class name (e.g. udPythonClassGenerator)
	 * \return Pointer to code generator if exists, otherwise NULL
	 */
	virtual udGeneratorInfo* FindGeneratorInfoByClassName(const wxString& classname) = 0;
	
	// settings-related functions
	/**
	 * \brief Get main application settings.
	 * \return Refernce to main application settings object
	 * \sa udSettings, wxXmlSerializer
	 */
	virtual udSettings& GetAppSettings() = 0;
	/**
	 * \brief Get current project settings.
	 * \return Reference to per-project settings object
	 * \sa udSettings, wxXmlSerializer
	 */
	virtual udSettings& GetProjectSettings() = 0;
	
	// plugin-related functions
	/**
	 * \brief Send internal event to the CodeDesigner and all registered listeners.
	 * \param cmdType Event type (e.g. wxEVT_CD_ITEM_SELECTED, wxEVT_CD_ITEM_ADDED, wxEVT_CD_ITEM_CHANGED,
	 * wxEVT_CD_ITEM_REMOVED, wxEVT_CD_TASK_REMOVE)
	 * \param id Event ID
	 * \param item Pointer to involved project item
	 * \param parent Pointer to parent of involved project item (if any)
	 * \param data String data associated with the event
	 * \param delayed TRUE if the event's processing should be delayed, FALSE if it should be processed
	 * immediatelly
	 */
	virtual void SendProjectEvent(wxEventType cmdType = wxEVT_NULL, int id = 0, udProjectItem *item = NULL, udProjectItem *parent = NULL, const wxString& data = wxEmptyString, bool delayed = false) = 0;
	/**
	 * \brief Register event handler which should receive CodeDesigner's internal events.
	 * \param plugin Pointer to new internal event's listener
	 */
	virtual void RegisterEventListener(IPlugin *plugin) = 0;
	/**
	 * \brief Unregister CodeDesigner's internal event listener.
	 * \param plugin Pointer to already registered event listener
	 */
	virtual void UnregisterEventListener(IPlugin *plugin) = 0;
	/**
	 * \brief Enable/Disable processing of CodeDesigner's internal events.
	 * \param enable TRUE for enabling, FALSE for disabling
	 */
	virtual void EnableInternalEvents(bool enable) = 0;
	
	/**
	 * \brief Register new diagram type.
	 * \param info Diagram info
	 * \sa udDiagramInfo
	 */
	virtual void RegisterDiagram(const udDiagramInfo& info) = 0;
	
	/**
	 * \brief Register new settings object.
	 * \param settings Pointer to registered settings category
	 * \param type settingsAPPLICATION for main application settings object, settingsPROJECT for per-project
	 * settings object.
	 * \sa udSettings, udSettingsCategory
	 */
	virtual void RegisterSettings(udSettingsCategory *settings, SETTINGSTYPE type) = 0;
	
	/**
	 * \brief Register so called 'friendly name', i.e. user-readable name for various class a property names.
	 * \param mapname Property name (e.g. class, active_algorithm, modifier, ...)
	 * \param origname Original name (e.g. udClassItem, udClassGenerator, ...)
	 * \param friendlyname User-readable name (e.g. Class Item, Class Code Generator, ...)
	 */
	virtual void RegisterFriendlyName(const wxString& mapname, const wxString& origname, const wxString& friendlyname) = 0;
	/**
	 * \brief Unregister previously registered so called 'friendly name'.
	 * \param mapname Property name (e.g. class, active_algorithm, modifier, ...)
	 * \param origname Original name (e.g. udClassItem, udClassGenerator, ...)
	 */
	virtual void UnregisterFriendlyName(const wxString& mapname, const wxString& origname) = 0;
	
	/**
	 * \brief Register new image in CodeDesigner's art provider.
	 * \param path Path (absolute or relative) to registered image
	 * \param name Unique image identifier
	 */
	virtual void RegisterArtBitmap(const wxString& path, const wxString& name) = 0;
	/**
	 * \brief Unregister previously registered image. 
	 * \param name Unique image identifier
	 */
	virtual void UnregisterArtBitmap(const wxString& name) = 0;
	
	/**
	 * \brief Register folder name for given code item type.
	 * \param classname Code item's class name
	 * \param packagename Foder name
	 */
	virtual void RegisterCodePackage(const wxString& classname, const wxString& packagename) = 0;
	/**
	 * \brief Unregister previously registered code items' folder name.
	 * \param classname Code item's class name
	 */
	virtual void UnregisterCodePackage(const wxString& classname) = 0;
	
	/**
	 * \brief Register code generator.
	 * \param info Code generator info
	 * \sa udGeneratorInfo
	 */
	virtual void RegisterCodeGenerator(const udGeneratorInfo& info) = 0;
	/**
	 * \brief Unregister previously registered code generator
	 * \param info Code generator info
	 * \sa udGeneratorInfo
	 */
	virtual void UnregisterCodeGenerator(const udGeneratorInfo& info) = 0;
	
	/**
	 * \brief Register comment processor for given project item type.
	 * \param type Project item typw (class name)
	 * \param processor Pointer to registered comment processor
	 */
	virtual void RegisterCommentProcessor(const wxString& type, udCommentProcessor *processor) = 0;
	/**
	 * \brief Unregister comment processor for given project item type.
	 * \param type Project item typw (class name)
	 */
	virtual void UnregisterCommentProcessor(const wxString& type) = 0;
	
	/**
	 * \brief Connect/Disconnect diagram events.
	 * \param diagram Pointer to source diagram
	 * \param enable TRUE for enabling, FALSE for disabling of diagram's events
	 */
	virtual void ConnectDiagramEvents(udDiagramCanvas *diagram, bool enable) = 0;
	
	/**
	 * \brief Save current diagram state (for undo/redo)
	 * \param diag Pointer to 
	 */
	virtual void SaveDiagramState(udDiagramItem *diag) = 0;
	
	// initialization function
	/**
	 * \brief Get pointer to plugin manager. Global function.
	 * \return Pointer to plugin manager
	 */
	static IPluginManager* Get() { return m_PluginManager; }
	/**
	 * \brief Set pointer to plugin manager.
	 * \param manager Valid pointer to plugin manager
	 */
	void SetThis(IPluginManager *manager) { m_PluginManager = manager; }

protected:
    // protected data members
	/**
	 * \brief Pointer to plugin manager
	 */
	WXDLLIMPEXP_CD static IPluginManager *m_PluginManager;
};

#endif // IPLUGINMANAGER_H
