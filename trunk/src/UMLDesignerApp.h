/***************************************************************
 * Name:      UMLDesignerApp.h
 * Purpose:   Defines Application Class
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-10
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/

#ifndef UMLDESIGNERAPP_H
#define UMLDESIGNERAPP_H

#include <wx/app.h>
//#include <wx/wxFlatNotebook/wxFlatNotebook.h>

#include "Project.h"
#include "Settings.h"
#include "DiagramBank.h"
#include "PluginManager.h"
#include "projectbase/codegen/Language.h"
#include "projectbase/codegen/Generator.h"
#include "codegen/base/ProjectGenerator.h"

class UMLDesignerFrame;

class UMLDesignerApp : public wxApp
{
public:
//#ifdef __WXGTK__
//	// fix broken menu bar behaviour under Ubuntu
//	UMLDesignerApp() { wxSetEnv(wxT("UBUNTU_MENUPROXY"), wxT("0")); }
//#endif
	enum LOG
	{
		logNONE = 0,
		logNORMAL = 1,
		logWARNINGS = 2,
		logERRORS = 4,
		logALL = 255
	};
	
	enum RUNMODE
	{
		runSTANDARD,
		runWITHPROJECT,
		runSILENT
	};
	
    // public functions
    virtual bool OnInit();
    virtual int OnExit();

	const wxString& GetPath() const { return m_sAppPath; }
	wxString GetSettingsPath() const;
	wxString GetDiagramBankPath() const;
	wxString GetPluginsPath() const;
	wxString GetResourcesPath() const;
    UMLDesignerFrame* GetMainFrame(){return m_pMainFrame;}
	RUNMODE GetRunMode() { return m_nRunMode; }

    udProject* GetActiveProject();
    udLanguage* GetLanguage(int index);
    udLanguage* GetLanguage(const wxString& name);
    LanguageMap& GetLanguages(){return m_mapLanguages;}
    ProjectGeneratorMap& GetProjectGenerators(){return m_mapProjGenerators;}
	
	udSettings& GetSettings(){return m_Settings;}
	udDiagramBank& GetDiagramBank(){return m_DiagBank;}
	udPluginManager& GetPluginManager(){return m_PluginManager;}

	static void SetLogMask(int mask){m_nLogMask = mask;}
	static int GetLogMask(){return m_nLogMask;}
	static void ClearLog();
    static void Log(const wxString& msg);
	
	void ClearLanguages();
	void InitLanguages();

protected:
    // protected data memners
    UMLDesignerFrame *m_pMainFrame;

    udProject *m_pProject;
    LanguageMap m_mapLanguages;
    ProjectGeneratorMap m_mapProjGenerators;
	static int m_nLogMask;
	wxString  m_sAppPath;
	RUNMODE m_nRunMode;
	
	udAppSettings m_Settings;
	udDiagramBank m_DiagBank;
	udPluginManager m_PluginManager;
	
	// protected functions
	wxString FindAppPath();
};

DECLARE_APP(UMLDesignerApp);

#endif // UMLDESIGNERAPP_H
