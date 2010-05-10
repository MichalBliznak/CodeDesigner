#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <wx/wx.h>
#include <wx/aui/aui.h>

class IPluginManager;

/**
 * \class cdPluginInfo
 * \author Michal
 * \date 14.2.2010
 * \file IPlugin.h
 * \brief Data structure holding information about the plugin.
 */
class udPluginInfo
{
public:
	enum TYPE
	{
		ptDIAGRAM,
		ptCODEGEN,
		ptGUI,
		ptMIXED
	};
	
	void SetAuthor(const wxString& Author) {this->m_Author = Author;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetName(const wxString& Name) {this->m_Name = Name;}
	void SetType(const TYPE& Type) {this->m_Type = Type;}
	void SetVersion(const wxString& Version) {this->m_Version = Version;}
	void SetAPIVersionMax(int APIVersionMax) {this->m_APIVersionMax = APIVersionMax;}
	void SetAPIVersionMin(int APIVersionMin) {this->m_APIVersionMin = APIVersionMin;}
	
	int GetAPIVersionMax() const {return m_APIVersionMax;}
	int GetAPIVersionMin() const {return m_APIVersionMin;}
	const wxString& GetAuthor() const {return m_Author;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetName() const {return m_Name;}
	const TYPE& GetType() const {return m_Type;}
	const wxString& GetVersion() const {return m_Version;}
	
protected:
	wxString m_Name;
	wxString m_Description;
	wxString m_Version;
	wxString m_Author;
	TYPE m_Type;
	int m_APIVersionMin;
	int m_APIVersionMax;
};

/**
 * \class udPaneInfo
 * \author Michal
 * \date 7.4.2010
 * \file IPlugin.h
 * \brief Data structure holding information about Aui pane provided by the plugin.
 */
class udPaneInfo
{
public:
	udPaneInfo() : m_Pane(NULL) {;}

	void SetBestSize(const wxSize& BestSize) {this->m_BestSize = BestSize;}
	void SetName(const wxString& Name) {this->m_Name = Name;}
	void SetPane(wxWindow* Pane) {this->m_Pane = Pane;}
	
	const wxSize& GetBestSize() const {return m_BestSize;}
	const wxString& GetName() const {return m_Name;}
	wxWindow* GetPane() {return m_Pane;}
	
protected:
	wxWindow *m_Pane;
	wxString m_Name;
	wxSize m_BestSize;
};

/**
 * \class udToolbarInfo
 * \author Michal
 * \date 19.4.2010
 * \file IPlugin.h
 * \brief Data structure holding information about toolbar provided by the plugin.
 */
class udToolbarInfo
{
public:
	udToolbarInfo() : m_Toolbar(NULL) {;}
	
	void SetName(const wxString& Name) {this->m_Name = Name;}
	void SetToolbar(wxAuiToolBar* Toolbar) {this->m_Toolbar = Toolbar;}
	
	const wxString& GetName() const {return m_Name;}
	wxAuiToolBar* GetToolbar() {return m_Toolbar;}
	
protected:
	wxAuiToolBar *m_Toolbar;
	wxString m_Name;
};

/**
 * \class IPlugin
 * \author Michal
 * \date 14.2.2010
 * \file IPlugin.h
 * \brief Main plugin class providing set of (pure) virtual functions used for plugin
 * initialization. Every plugin must inherit this class.
 */
class IPlugin : public wxEvtHandler
{
public:
	/**
	 * \brief Contrustor
	 * \param manager Pointer to plugin manager.
	 */
	IPlugin(IPluginManager *manager) : m_PluginManager(manager) {}
	virtual ~IPlugin() {}
	
	/**
	 * \brief Plugin's 'entry point'. All plugin-specific initialization code
	 * should be placed here.
	 * \return TRUE on success.
	 */
	virtual bool OnInit() = 0;
	/**
	 * \brief Plugin's deinitialization code (if any).
	 * \return Return code (0 on success, otherwise non-zero value)
	 */
	virtual int OnExit() = 0;
	/**
	 * \brief Get basic information about the plugin.
	 * \return Plugin info
	 * \sa udPluginInfo
	 */
	virtual udPluginInfo GetInfo() = 0;
	
	/**
	 * \brief Create plugin's toolbar if needed.
	 * \param parent Pointer to parent of plugin toolbar
	 * \return Data structure containing pointer to newly created toolbar and other info.
	 * \sa udToolbarInfo
	 */
	virtual udToolbarInfo CreateToolbar(wxWindow *parent) { return udToolbarInfo(); }
	/**
	 * \brief Create plugin's AUI pane if needed.
	 * \param parent Pointer to pane's parent
	 * \return Data structure containing pointer to newly created GUI control assigned to
	 * AUI pane and other info.
	 * \sa udPaneInfo
	 */
	virtual udPaneInfo CreateAuiPane(wxWindow *parent) { return udPaneInfo(); }
	/**
	 * \brief Create plugin's menu located under "Plugins" main menu item if needed.
	 * \return Pointer to plugin's menu.
	 */
	virtual wxMenu* CreateMenu() { return NULL; }
	
protected:
	IPluginManager *m_PluginManager;
};

//Every dll must contain at least this function
typedef IPlugin*    	(*GET_PLUGIN_CREATE)(IPluginManager*);
typedef udPluginInfo  	(*GET_PLUGIN_INFO_FUNC)();

#endif // IPLUGIN_H
