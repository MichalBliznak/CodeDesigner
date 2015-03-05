#ifndef __udsettings__
#define __udsettings__

#include "projectbase/SettingsBase.h"

// specialized classes //////////////////////////////////////////////////////////////////

class udAppSettings : public udSettings
{
public:
	udAppSettings();
	virtual ~udAppSettings();
	
	virtual void CreateCategories();
};

class udProjectSettings : public udSettings
{
public:	
	udProjectSettings();
	virtual ~udProjectSettings();
	
	virtual void CreateCategories();
};

class udDiagramsCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udDiagramsCategory);
	
	udDiagramsCategory();
	virtual ~udDiagramsCategory();
	
	// public data members
	bool m_fShowGrid;
	bool m_fUseGraphicsContext;
	bool m_fExportBackground;
	
	wxColour m_colHighlightCol;
	wxColour m_colBackgroundFrom;
	wxColour m_colBackgroundTo;
	wxColour m_colDisabledBackgroundFrom;
	wxColour m_colDisabledBackgroundTo;
	
	wxFont m_nDefaultFont;
};

class udFrameCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udFrameCategory);
	
	udFrameCategory();
	virtual ~udFrameCategory();
	
	// public data members
	wxColour m_colBackground;
	bool m_fShowSplash;
};

class udHiddenGUICategory : public udHiddenCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udHiddenGUICategory);
	
	udHiddenGUICategory();
	virtual ~udHiddenGUICategory();
	
	// public data members
	wxString m_sPerspective;
	bool m_fShowThumbElements;
	bool m_fShowThumbConnections;
	bool m_fShowProperties;
	bool m_fOrganizeCI;
	bool m_fLinkDesigner;
	int m_nProjManSashPos;
	wxArrayString m_arrRecentFiles;
};

class udGeneratorCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udGeneratorCategory);
	
	udGeneratorCategory();
	virtual ~udGeneratorCategory();
	
	// public data members
	wxString m_sBaseFileName;
	wxString m_sCodeItemsFileName;
	wxFileName m_sOutDir;
	bool m_fGenerateDescription;
	bool m_fSyncBeforeGenerate;
};

class udHiddenProjectCategory : public udHiddenCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udHiddenProjectCategory);
	
	udHiddenProjectCategory();
	virtual ~udHiddenProjectCategory();
	
	// public data members
	wxString m_sActiveLanguage;
	long m_nProjectVersion;
};

class udEditorCategory : public udSettingsCategory
{
public:
	DECLARE_DYNAMIC_CLASS(udEditorCategory);
	
	udEditorCategory();
	virtual ~udEditorCategory();
	
	// public data members
	bool m_fUseTabs;
	int m_nTabWidth;
	int m_nIndentWidth;
	wxFont m_EditorFont;
};

#endif // __udsettings__
