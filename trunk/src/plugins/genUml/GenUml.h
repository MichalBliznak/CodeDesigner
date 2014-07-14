/*********************************************************************
 * Name:      	DiagTest.h
 * Purpose:   	Declares testing diagram plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#ifndef _GEN_UML_H_
#define _GEN_UML_H_

// include import/export definitions
#include "interfaces/Defs.h"
// common interfaces
#include "interfaces/IPlugin.h"
#include "interfaces/IPluginManager.h"

#include "projectbase/ProjectBase.h"

#include "statechartgen/StateChartVerifier.h"
#include "statechartgen/StateChartOptimizer.h"
#include "statechartgen/StateChartGenerator.h"
#include "statechartgen/StateChartElementProcessor.h"
#include "statechartgen/SStateChartGenerator.h"
#include "statechartgen/HStateChartGenerator.h"
#include "statechartgen/LoopCaseAlgorithm.h"
#include "statechartgen/GoToAlgorithm.h"
#include "statechartgen/ElifAlgorithm.h"
#include "statechartgen/LCElementProcessors.h"
#include "statechartgen/LCEITransitionProcessor.h"
#include "statechartgen/EIElementProcessors.h"
#include "statechartgen/GTElementProcessors.h"
#include "statechartgen/HStateChartPreprocessor.h"

#include "classdiaggen/PythonClassAlgorithm.h"
#include "classdiaggen/PythonElementProcessors.h"
#include "classdiaggen/CPPClassAlgorithm.h"
#include "classdiaggen/CPPElementProcessors.h"
#include "classdiaggen/ClassDiagramGenerator.h"
#include "classdiaggen/ClassAlgorithm.h"

#define udnSIMPLE_STATECHART_GEN wxT("State Chart generator")
#define udnHIERARCHICAL_STATE_CHART_GEN wxT("Hierarchical State Chart generator")
#define udnCLASS_DIAGRAM_GEN wxT("Class Diagram generator")

// plugin class ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class udUmlGeneratorPlugin : public IPlugin
{
public:
	udUmlGeneratorPlugin(IPluginManager *manager);
	virtual ~udUmlGeneratorPlugin() {}
	
	virtual int OnExit();
	virtual bool OnInit();
	virtual udPluginInfo GetInfo();

protected:
	udGeneratorInfo m_infoSSCH;
	udGeneratorInfo m_infoHSCH;
	udGeneratorInfo m_infoCD;
};

// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udStateChartCategory : public udSettingsCategory
{
public:
	XS_DECLARE_CLONABLE_CLASS(udStateChartCategory);
	
	udStateChartCategory();
	udStateChartCategory(const udStateChartCategory& obj);
	virtual ~udStateChartCategory();
	
	// public data members
	bool m_fInvertConditions;
	bool m_fMergeParallelTransitions;
	bool m_fMergeDirectBraches;
	bool m_fOmitLabels;
};

#endif //_GEN_UML_H_

