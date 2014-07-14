/*********************************************************************
 * Name:      	RevEng.h
 * Purpose:   	Declares reverse code engineering plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#ifndef _REV_ENG_H_
#define _REV_ENG_H_

// include import/export definitions
#include "interfaces/Defs.h"
// common interfaces
#include "interfaces/IPlugin.h"
#include "interfaces/IPluginManager.h"

#include "projectbase/ProjectBase.h"

#define uddvDEFAULT_CTAGS wxT("<built-in>")
#define uddvDEFAULT_CTAGS_CPP_EXT wxT("c cpp cxx h hpp hxx inc")
#define uddvDEFAULT_CTAGS_PYTHON_EXT wxT("py pyw")

////////////////////////////////////////////////////////////////////////////////
// plugin class ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * \class udReverseEngineeringPlugin
 * \brief Class encapsulating base plugin class.
 */
class udReverseEngineeringPlugin : public IPlugin
{
public:
	udReverseEngineeringPlugin(IPluginManager *manager);
	virtual ~udReverseEngineeringPlugin() {}
	
	// pure abstract virtual functions (must be implemented)
	virtual bool OnInit();
	virtual int OnExit();
	virtual udPluginInfo GetInfo();

	// optional virtual functions for 'GUI' plugin
	virtual wxMenu* CreateMenu();
	virtual udPaneInfo CreateAuiPane(wxWindow *parent);
	virtual udToolbarInfo CreateToolbar(wxWindow *parent);
	
protected:
	// info about published component
	udDiagramInfo m_infoDiag;
	udGeneratorInfo m_infoGenerator;
};

extern udReverseEngineeringPlugin *thePlugin;

////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// plugin settings /////////////////////////////////////////////////////////////

/**
 * \class udRevEngAppSettingsCategory
 * \brief Class encapsulating plugin application settings category.
 */
class WXDLLIMPEXP_CD udRevEngAppSettingsCategory : public udSettingsCategory
{
public:
	XS_DECLARE_CLONABLE_CLASS(udRevEngAppSettingsCategory);
	
	udRevEngAppSettingsCategory();
	udRevEngAppSettingsCategory(const udRevEngAppSettingsCategory& obj);
	virtual ~udRevEngAppSettingsCategory();
	
	// public data members
	wxString m_CtagsPath;
	wxString m_CPPExtensions;
	wxString m_PythonExtensions;
};

#endif //_REV_ENG_H_

