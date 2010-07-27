/*********************************************************************
 * Name:      	DiagUml.h
 * Purpose:   	Declares UML plugin
 * Author:    	Michal Bližňák
 * Created:
 * Copyright:
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/

#ifndef _DIAG_UML_H_
#define _DIAG_UML_H_

// include import/export definitions
#include "interfaces/Defs.h"
// common interfaces
#include "interfaces/IPlugin.h"
#include "interfaces/IPluginManager.h"

#include "DiagSCH.h"
#include "DiagCD.h"

#include "shapes/statechart/DecisionItem.h"
#include "shapes/statechart/EntryItem.h"
#include "shapes/statechart/ExitItem.h"
#include "shapes/statechart/FinalItem.h"
#include "shapes/statechart/ForkJoinHItem.h"
#include "shapes/statechart/ForkJoinVItem.h"
#include "shapes/statechart/HistoryItem.h"
#include "shapes/statechart/InitialItem.h"
#include "shapes/statechart/SimpleStateItem.h"
#include "shapes/statechart/StateItem.h"
#include "shapes/statechart/SubStateItem.h"
#include "shapes/statechart/TransitionItem.h"

#include "shapes/classdiagram/BasicAggregItem.h"
#include "shapes/classdiagram/BiDirectAssocItem.h"
#include "shapes/classdiagram/ClassItem.h"
#include "shapes/classdiagram/ClassTemplItem.h"
#include "shapes/classdiagram/CompAggregItem.h"
#include "shapes/classdiagram/InheritanceItem.h"
#include "shapes/classdiagram/InterfaceItem.h"
#include "shapes/classdiagram/UniDirectAssocItem.h"
#include "shapes/classdiagram/TemplateBindItem.h"
#include "shapes/classdiagram/EnumItem.h"
#include "shapes/classdiagram/IncludeAssocItem.h"

#include "shapes/ClassDiagram.h"
#include "shapes/SimpleStateChartDiagram.h"
#include "shapes/StateChartDiagram.h"

// plugin class ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class udUmlDiagramPlugin : public IPlugin
{
public:
	udUmlDiagramPlugin(IPluginManager *manager);
	virtual ~udUmlDiagramPlugin() {}

	virtual int OnExit();
	virtual bool OnInit();
	virtual udPluginInfo GetInfo();

protected:
	// event handlers
	void OnAssignAction(wxCommandEvent& event);
	void OnAssignGuard(wxCommandEvent& event);
	void OnAssignVariable(wxCommandEvent& event);
	void OnAssignFunction(wxCommandEvent& event);

	void OnAssignNewCondition(wxCommandEvent& event);
	void OnAssignNewEvent(wxCommandEvent& event);
	void OnAssignNewAction(wxCommandEvent& event);
	void OnAssignNewStateAction(wxCommandEvent& event);
	void OnAssignNewVariable(wxCommandEvent& event);
	void OnAssignNewFunction(wxCommandEvent& event);

	void OnCreateConstructor(wxCommandEvent& event);
	void OnCreateDestructor(wxCommandEvent& event);
	
	void OnClearCodeItems(wxCommandEvent& event);
	
	void OnRefactorVirtualFcn(wxCommandEvent& event);
	
	void OnChangeAccessType(wxCommandEvent& event);
	
	void OnAddEnumElement(wxCommandEvent& event);
};

#endif //_DIAG_UML_H_
