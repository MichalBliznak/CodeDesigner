/***************************************************************
 * Name:      UMLDesignerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2007-07-10
 * Copyright: Michal Bližňák ()
 * License:
 **************************************************************/
#include "wx_pch.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif


#include <wx/log.h>
#include <wx/stdpaths.h>
#include <wx/splash.h>

#include "UMLDesignerApp.h"
#include "UMLDesignerMain.h"
#include "codegen/languages/CLanguage.h"
#include "codegen/languages/CPPLanguage.h"
#include "codegen/languages/PythonLanguage.h"
#include "codegen/CProjectGenerator.h"
#include "codegen/PythonProjectGenerator.h"
#include "XS2PG.h"
#include "Art.h"

#define udvSETTINGS_DIR wxStandardPaths::Get().GetUserDataDir() + wxFileName::GetPathSeparator()
#define udvSETTINGS_PATH udvSETTINGS_DIR + wxT("config.xml")
#define udvDIAGBANK_PATH udvSETTINGS_DIR + wxT("diagrambank.xml")

int UMLDesignerApp::m_nLogMask = logALL;

IMPLEMENT_APP(UMLDesignerApp);

bool UMLDesignerApp::OnInit()
{
	// process command line parameters
	m_nRunMode = runSTANDARD;
	
	// should some project to be opened or generated now?
	if( argc == 2 && wxFileExists( wxString( argv[1] ) ) )
	{
		m_nRunMode = runWITHPROJECT;
	}
	else if( argc == 3 && wxString( argv[1]) == wxT("-g") && wxFileExists( wxString( argv[2] ) ) )
	{
		m_nRunMode = runSILENT;
	}
	else if( argc > 2 )
	{
		wxPrintf(wxT("CodeDesigner's usage:\n    CodeDesigner [-g][project]\n    g - generate opened project immediately\n    project - path to a project file to be opened by CodeDesigner\n\n"));
		fflush(stdout);
	}
	
	SetAppName( wxT("codedesigner") );
	
	wxInitAllImageHandlers();
	
	m_pMainFrame = NULL;
	m_sAppPath = FindAppPath() + wxFileName::GetPathSeparator();
	
	// set CWD to the app dir
	wxSetWorkingDirectory( m_sAppPath );
	
	// initialize XS 2 PG bridge
	udXS2PG::Initialize();
	
	// register new IO handlers
	XS_REGISTER_IO_HANDLER(wxT("filename"), xsFileNamePropIO);
	XS_REGISTER_IO_HANDLER(wxT("dirname"), xsDirNamePropIO);
	
	// create application settings
	if( !wxDirExists( udvSETTINGS_DIR ) ) wxMkdir( udvSETTINGS_DIR );
	
	// load plugins
	m_PluginManager.LoadPlugins();

	// try to load application settings
	if( !m_Settings.DeserializeFromXml( udvSETTINGS_PATH ) )
	{
		if( wxFileExists( udvSETTINGS_PATH ) ) wxMessageBox( wxT("Application settings couldn't be read so default values will be used."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
	}
	
	// show splash screen
	if( m_nRunMode != runSILENT && m_Settings.GetProperty( wxT("Show splash screen") )->AsBool() )
	{
		new wxSplashScreen( wxBitmap( GetResourcesPath() + wxT("app/gui/splash.png"), wxBITMAP_TYPE_PNG ),  wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, 4000, NULL, wxID_ANY );
		wxYield();
	}
	
    // initialize languages
    InitLanguages();
	
	// initialize common comment generators
	udGenerator::InitAllStdCommentProcessors();
		
	// initialize projects
	m_pProject = new udProject();
	
	UMLDesignerFrame::EnableInternalEvents( false );
	
	// try to load diagram bank
	if( wxFileExists( udvDIAGBANK_PATH ) )
	{
		if( !m_DiagBank.DeserializeFromXml( udvDIAGBANK_PATH ) )
		{
			wxCopyFile( udvDIAGBANK_PATH, udvDIAGBANK_PATH + wxT(".backup") );
			wxMessageBox( wxT("Diagram bank file couldn't be read correctly (probably some previously used plugins aren't loaded at this time) so the current file was archived and new one is in use."), wxT("CodeDesigner"), wxOK | wxICON_WARNING );
			
			m_DiagBank.RemoveAll();
			m_DiagBank.CreateCategories();
		}
	}
	else
		m_DiagBank.CreateCategories();
		

	UMLDesignerFrame::EnableInternalEvents( true );
	
	switch( m_nRunMode )
	{
		case runSTANDARD:
			m_pMainFrame = new UMLDesignerFrame(0L);
			SetTopWindow(m_pMainFrame);
			break;
			
		case runWITHPROJECT:
			m_pMainFrame = new UMLDesignerFrame(0L);
			SetTopWindow(m_pMainFrame);
			
			m_pMainFrame->OpenProjectFile( wxString( argv[1] ) );
			break;
			
		case runSILENT:
		{
			wxString sPath =  wxString( argv[2] );
			m_pProject->DeserializeFromXml( sPath );
			m_pProject->SetProjectDirectory( sPath.BeforeLast( wxFileName::GetPathSeparator() ) );
			m_pProject->SetProjectPath( sPath );
		
			// generate project here and then quit silently
			wxString sLang = m_pProject->GetSettings().GetPropertyAsString( wxT("active_language"), wxT("udCPPLanguage") );
			
			udLanguage *pLang = m_mapLanguages[sLang];
			udProjectGenerator *pProjGen = m_mapProjGenerators[sLang];
			
			if( pLang && pProjGen )
			{
				UMLDesignerFrame::EnableInternalEvents( false );
				
				pProjGen->SetActiveLanguage( pLang );
				pProjGen->Generate( udProject::Get() );
				
				UMLDesignerFrame::EnableInternalEvents( true );
			}
		}
		break;
	}
	
	if( m_nRunMode != runSILENT )
	{
		m_pMainFrame->Show();
		return true;
	}
	else
	{
		/*// quit application immediately
		wxCommandEvent e( wxEVT_COMMAND_MENU_SELECTED, wxID_EXIT );
		wxPostEvent( m_pMainFrame, e );*/
		OnExit();
		return false;
	}
	
	/*return true;*/
}

int UMLDesignerApp::OnExit()
{
	UMLDesignerFrame::EnableInternalEvents( false );
	
    // clear languages
    ClearLanguages();

    // clear project generators
    ProjectGeneratorMap::iterator pit = m_mapProjGenerators.begin();
    while(pit != m_mapProjGenerators.end())
    {
        delete pit->second;
        pit++;
    }
    m_mapProjGenerators.clear();
	
	// clean-up code generator
	udGenerator::CleanCommentProcessors();
	
	// store settings
	m_Settings.SerializeToXml( udvSETTINGS_PATH );
	m_Settings.RemoveAll();
	
	// store diagram bank
	m_DiagBank.SerializeToXml( udvDIAGBANK_PATH );
	m_DiagBank.RemoveAll();
	
	// deinitialize projects
	delete m_pProject;
	
	// unload plugins
	m_PluginManager.UnloadPlugins();
	
	// clean-up XS 2 PG bridge
	udXS2PG::CleanUp();

    return 0;
}

wxString UMLDesignerApp::GetSettingsPath() const
{
	return udvSETTINGS_DIR;
}

wxString UMLDesignerApp::GetDiagramBankPath() const
{
	return udvDIAGBANK_PATH;
}

wxString UMLDesignerApp::GetPluginsPath() const
{
	#ifdef __WXMSW__
	return m_sAppPath + wxT("plugins") + wxFileName::GetPathSeparator();
	#else
	return wxStandardPaths::Get().GetPluginsDir() + wxFileName::GetPathSeparator() + wxT("plugins") + wxFileName::GetPathSeparator();
	#endif
}

wxString UMLDesignerApp::GetResourcesPath() const
{
	#ifdef __WXMSW__
	return m_sAppPath + wxT("res") + wxFileName::GetPathSeparator();
	#else
	return wxStandardPaths::Get().GetResourcesDir() + wxFileName::GetPathSeparator();
	#endif
}

udProject* UMLDesignerApp::GetActiveProject()
{
    return m_pProject;
}

udLanguage* UMLDesignerApp::GetLanguage(int index)
{
    if(index >= 0)
    {
        LanguageMap::iterator it = m_mapLanguages.begin();
        for(int i = 0; i < index; i++)it++;

        if(it != m_mapLanguages.end())return it->second;
    }

    return NULL;
}

udLanguage* UMLDesignerApp::GetLanguage(const wxString& name)
{
    LanguageMap::iterator it = m_mapLanguages.begin();

    while( it != m_mapLanguages.end())
    {
        if(it->second->GetName() == name)return it->second;
        it++;
    }

    return NULL;
}

void UMLDesignerApp::Log(const wxString& msg)
{
	if( wxGetApp().GetRunMode() != runSILENT )
	{
		if( wxGetApp().GetMainFrame() )
		{
			wxGetApp().GetMainFrame()->GetLogWindow()->AddMessage(msg);
		}
		else
		{
			if( (m_nLogMask & logERRORS) && msg.Contains(wxT("ERROR")) )
			{
				wxLogError(msg);
			}
			else if( (m_nLogMask & logWARNINGS ) && msg.Contains(wxT("WARNING")) )
			{
				wxLogWarning(msg);
			}
			else if( m_nLogMask & logNORMAL )
			{
				wxLogMessage(msg);
			}
		}
	}
}

void UMLDesignerApp::ClearLog()
{
	if( wxGetApp().GetMainFrame() )
	{
		wxGetApp().GetMainFrame()->GetLogWindow()->ClearMessages();
	}
}

wxString UMLDesignerApp::FindAppPath()
{
    wxString str;

    // Try appVariableName
    if (!GetAppName().IsEmpty())
    {
        str = wxGetenv(GetAppName());
        if (!str.IsEmpty())
            return str;
    }

#if defined(__WXMAC__) && !defined(__DARWIN__)
    // On Mac, the current directory is the relevant one when
    // the application starts.
    return wxGetCwd();
#endif

    if (wxIsAbsolutePath(argv[0]))
        return wxPathOnly(argv[0]);
    else
    {
        // Is it a relative path?
        wxString currentDir(wxGetCwd());
        if (currentDir.Last() != wxFILE_SEP_PATH)
            currentDir += wxFILE_SEP_PATH;

        str = currentDir + argv[0];
        if (wxFileExists(str))
            return wxPathOnly(str);
    }

    // OK, it's neither an absolute path nor a relative path.
    // Search PATH.

    wxPathList pathList;
    pathList.AddEnvList(wxT("PATH"));
    str = pathList.FindAbsoluteValidPath(argv[0]);
    if (!str.IsEmpty())
        return wxPathOnly(str);

    // Failed
    return wxEmptyString;
}

void UMLDesignerApp::ClearLanguages()
{
	LanguageMap::iterator lit = m_mapLanguages.begin();
    while(lit != m_mapLanguages.end())
    {
        delete lit->second;
        lit++;
    }
    m_mapLanguages.clear();
}

void UMLDesignerApp::InitLanguages()
{
	m_mapLanguages[wxT("udCLanguage")] = new udCLanguage();
    m_mapLanguages[wxT("udCPPLanguage")] = new udCPPLanguage();
    m_mapLanguages[wxT("udPythonLanguage")] = new udPythonLanguage();
    //m_mapLanguages[wxT("udLanguage")] = new udLanguage(); // only for testing purposes!

    m_mapProjGenerators[wxT("udCLanguage")] = new udCProjectGenerator();
    m_mapProjGenerators[wxT("udCPPLanguage")] = new udCProjectGenerator();
    m_mapProjGenerators[wxT("udPythonLanguage")] = new udPythonProjectGenerator();
}

