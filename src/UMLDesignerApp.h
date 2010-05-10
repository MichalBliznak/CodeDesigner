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
	enum LOG
	{
		logNONE = 0,
		logNORMAL = 1,
		logWARNINGS = 2,
		logERRORS = 4,
		logALL = 255
	};
	
    // public functions
    virtual bool OnInit();
    virtual int OnExit();

	const wxString& GetPath() const { return m_sAppPath; }
	wxString GetSettingsPath() const;
    UMLDesignerFrame* GetMainFrame(){return m_pMainFrame;}

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

protected:
    // protected data memners
    UMLDesignerFrame *m_pMainFrame;

    udProject *m_pProject;
    LanguageMap m_mapLanguages;
    ProjectGeneratorMap m_mapProjGenerators;
	static int m_nLogMask;
	wxString  m_sAppPath;
	
	udAppSettings m_Settings;
	udDiagramBank m_DiagBank;
	udPluginManager m_PluginManager;
	
	// protected functions
	wxString FindAppPath();
};

DECLARE_APP(UMLDesignerApp);

#endif // UMLDESIGNERAPP_H
