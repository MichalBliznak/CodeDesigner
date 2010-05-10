/*********************************************************************
 * Name:      	DiagTest.h
 * Purpose:   	Declares testing diagram plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#ifndef _DIAG_TEST_H_
#define _DIAG_TEST_H_

// include import/export definitions
#include "interfaces/Defs.h"
// common interfaces
#include "interfaces/IPlugin.h"
#include "interfaces/IPluginManager.h"

#include "projectbase/ProjectBase.h"

#define udnTEST_DIAGRAM wxT("Test diagram")
#define uddvDEFAULT_VALUE true

////////////////////////////////////////////////////////////////////////////////
// plugin class ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * \class udTestDiagramPlugin
 * \brief Class encapsulating base plugin class.
 */
class udTestDiagramPlugin : public IPlugin
{
public:
	udTestDiagramPlugin(IPluginManager *manager);
	virtual ~udTestDiagramPlugin() {}
	
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
	
	// user-defined event handlers
	void OnTest(wxCommandEvent &event);
};

extern udTestDiagramPlugin *thePlugin;

////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// custom diagram elements for 'DIAGRAM' plugin ////////////////////////////////

/**
 * \class uddTestElement
 * \brief Class encapsulating user-defined diagram component derived from base rectangular
 * shape wiht editable label.
 */
class WXDLLIMPEXP_CD uddTestElement : public uddRectElement
{
public:
	XS_DECLARE_CLONABLE_CLASS(uddTestElement);
	
	uddTestElement();
	virtual ~uddTestElement() {}
};

/**
 * \class udTestElementItem
 * \brief Class encapsulating data class for user-defined diagram component.
 */
class WXDLLIMPEXP_CD udTestElementItem : public udDiagElementItem
{
public:
	XS_DECLARE_CLONABLE_CLASS(udTestElementItem);
	
	virtual ~udTestElementItem() {}
};

/**
 * \class udTestDiagramItem
 * \brief Class encapsulating custom diagram.
 */
class WXDLLIMPEXP_CD udTestDiagramItem : public udDiagramItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(udTestDiagramItem);

    udTestDiagramItem();
	udTestDiagramItem(const udTestDiagramItem &obj);
    virtual ~udTestDiagramItem();
};

////////////////////////////////////////////////////////////////////////////////
// custom code generator/algorithm for 'CODE GENERATION' plugin ////////////////

/**
 * \class udTestGenerator
 * \brief Class encapsulating user-defined code generator able to process custom
 * diagram declared above.
 */
class WXDLLIMPEXP_CD udTestGenerator : public udGenerator
{
public:
	DECLARE_DYNAMIC_CLASS(udTestGenerator);
	
	udTestGenerator();
	
	// implement these virtual functions (if needed)
	virtual bool Initialize();
	virtual bool ProcessDiagram(udDiagramItem* src);
	virtual void CleanUp();

};

/**
 * \class udTestAlgorithm
 * \brief Class encapsulating code generation algorithm used by user-defined code
 * generator. A code generator can own several algorithms which are filered by 
 * currently selected programming language.
 */
class WXDLLIMPEXP_CD udTestAlgorithm : public udAlgorithm
{
public:
	DECLARE_DYNAMIC_CLASS(udTestAlgorithm);
	
	udTestAlgorithm();
	udTestAlgorithm(udGenerator *parent);
	
	// implement these virtual functions (if needed)
	virtual bool Initialize();
	virtual void ProcessAlgorithm(udDiagramItem* src);
	virtual void CleanUp();

};

/**
 * \class udTestElementProcessor
 * \brief Class encapsulating code processor used by generation algorithm suitable
 * for a specific diagram conponent.
 */
class WXDLLIMPEXP_CD udTestElementProcessor : public udElementProcessor
{
public:
	udTestElementProcessor();
	udTestElementProcessor(udGenerator *parent);
	
	// implement this virtual function
	virtual void ProcessElement(wxSFShapeBase* element);
};

////////////////////////////////////////////////////////////////////////////////
// plugin settings /////////////////////////////////////////////////////////////

/**
 * \class udTestSettingsCategory
 * \brief Class encapsulating plugin per-project settings category.
 */
class WXDLLIMPEXP_CD udTestSettingsCategory : public udSettingsCategory
{
public:
	XS_DECLARE_CLONABLE_CLASS(udTestSettingsCategory);
	
	udTestSettingsCategory();
	udTestSettingsCategory(const udTestSettingsCategory& obj);
	virtual ~udTestSettingsCategory();
	
	// public data members
	bool m_fTestProperty;
};

/**
 * \class udTestSettingsCategory
 * \brief Class encapsulating plugin application settings category.
 */
class WXDLLIMPEXP_CD udTestAppSettingsCategory : public udSettingsCategory
{
public:
	XS_DECLARE_CLONABLE_CLASS(udTestAppSettingsCategory);
	
	udTestAppSettingsCategory();
	udTestAppSettingsCategory(const udTestAppSettingsCategory& obj);
	virtual ~udTestAppSettingsCategory();
	
	// public data members
	bool m_fTestProperty;
};

#endif //_DIAG_TEST_H_

