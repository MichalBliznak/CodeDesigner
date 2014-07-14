/*********************************************************************
 * Name:      	GenUml.cpp
 * Purpose:   	Implements testing diagram plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#include "GenUml.h"
 
// plugin //////////////////////////////////////////////////////////////////////

static udUmlGeneratorPlugin *thePlugin = NULL;

//Define the plugin entry point
extern "C" WXDLLIMPEXP_CD IPlugin *CreatePlugin(IPluginManager *manager)
{
	if (thePlugin == NULL)
	{
		thePlugin = new udUmlGeneratorPlugin(manager);
	}
	
	return thePlugin;
}

extern "C" WXDLLIMPEXP_CD udPluginInfo GetPluginInfo()
{
	// set plugin info
	udPluginInfo info;
	
	info.SetAuthor( wxT("Michal Bližňák") );
	info.SetName( wxT("UML code generators") );
	info.SetDescription( wxT("Code generators for State charts and Class Diagram supporting C/C++ and Python.") );
	info.SetType( udPluginInfo::ptCODEGEN );
	info.SetVersion( wxT("1.0") );
	info.SetAPIVersionMin( 1 );
	info.SetAPIVersionMax( 1 );
	
	return info;
}

udUmlGeneratorPlugin::udUmlGeneratorPlugin(IPluginManager *manager) : IPlugin(manager)
{
	m_infoSSCH.SetClassName( wxT("udSStateChartGenerator") );
	m_infoSSCH.SetDiagramClassName( wxT("udSStateChartDiagramItem") );
	m_infoSSCH.SetDescription( udnSIMPLE_STATECHART_GEN );
	
	m_infoHSCH.SetClassName( wxT("udHStateChartGenerator") );
	m_infoHSCH.SetDiagramClassName( wxT("udHStateChartDiagramItem") );
	m_infoHSCH.SetDescription( udnHIERARCHICAL_STATE_CHART_GEN );
	
	m_infoCD.SetClassName( wxT("udClassDiagramGenerator") );
	m_infoCD.SetDiagramClassName( wxT("udClassDiagramItem") );
	m_infoCD.SetDescription( udnCLASS_DIAGRAM_GEN );
}

int udUmlGeneratorPlugin::OnExit()
{
	// unregister code generator
	m_PluginManager->UnregisterCodeGenerator( m_infoSSCH );
	m_PluginManager->UnregisterCodeGenerator( m_infoHSCH );
	m_PluginManager->UnregisterCodeGenerator( m_infoCD );
	
	// register friendly names
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udSStateChartGenerator") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udHStateChartGenerator") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udClassDiagramGenerator") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udLoopCaseAlgorithm") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udGOTOAlgorithm") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udElifAlgorithm") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udCPPClassAlgorithm") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udPythonClassAlgorithm") );
	
	// unregister comment processors
	m_PluginManager->UnregisterCommentProcessor( wxT("udActionItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udConditionItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udMemberFunctionItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udMemberDataItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udConstructorFunctionItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udClassElementItem") );
	m_PluginManager->UnregisterCommentProcessor( wxT("udClassTemplateElementItem") );

	return 0;
}

bool udUmlGeneratorPlugin::OnInit()
{
	// register code generator
	m_PluginManager->RegisterCodeGenerator( m_infoSSCH );
	m_PluginManager->RegisterCodeGenerator( m_infoHSCH );
	m_PluginManager->RegisterCodeGenerator( m_infoCD );
	
	// register friendly names
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udSStateChartGenerator"), wxT("Simple State Chart generator") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udHStateChartGenerator"), wxT("Hierarchical State Chart generator") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udClassDiagramGenerator"), wxT("Class diagrams generator") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udLoopCaseAlgorithm"), wxT("Loop-Case algorithm") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udGOTOAlgorithm"), wxT("GOTO algorithm") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udElifAlgorithm"), wxT("Else-If algorithm") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udCPPClassAlgorithm"), wxT("Class algorithm for C++") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udPythonClassAlgorithm"), wxT("Class algorithm for Python") );
	
	// register comment processors
	m_PluginManager->RegisterCommentProcessor( wxT("udActionItem"), new udFunctionComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udConditionItem"), new udFunctionComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udMemberFunctionItem"), new udFunctionComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udMemberDataItem"), new udVariableComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udConstructorFunctionItem"), new udFunctionComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udClassElementItem"), new udClassComment() );
	m_PluginManager->RegisterCommentProcessor( wxT("udClassTemplateElementItem"), new udClassComment() );
	
	
	// register plugin settings
	m_PluginManager->RegisterSettings( new udStateChartCategory(), IPluginManager::settingsPROJECT );
	
	return true;
}

udPluginInfo udUmlGeneratorPlugin::GetInfo()
{
	return GetPluginInfo();
}

/////////////////////////////////////////////////////////////////////////////////////
// udStateChartCategory class ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udStateChartCategory, udSettingsCategory);

udStateChartCategory::udStateChartCategory() : udSettingsCategory( wxT("State chart") )
{
	m_fInvertConditions = true;
	m_fMergeParallelTransitions = true;
	m_fMergeDirectBraches = true;
	m_fOmitLabels = true;
	
	XS_SERIALIZE( m_fInvertConditions, wxT("Invert conditions") );
	XS_SERIALIZE( m_fMergeParallelTransitions, wxT("Merge parallel transitions") );
	XS_SERIALIZE( m_fMergeDirectBraches, wxT("Merge direct branches") );
	XS_SERIALIZE( m_fOmitLabels, wxT("Omit unused labels") );
}

udStateChartCategory::udStateChartCategory(const udStateChartCategory& obj) : udSettingsCategory( obj )
{
	SetName( wxT("State chart") );
	
	m_fInvertConditions = obj.m_fInvertConditions;
	m_fMergeParallelTransitions = obj.m_fMergeDirectBraches;
	m_fMergeDirectBraches = obj.m_fMergeDirectBraches;
	m_fOmitLabels = obj.m_fOmitLabels;
	
	XS_SERIALIZE( m_fInvertConditions, wxT("Invert conditions") );
	XS_SERIALIZE( m_fMergeParallelTransitions, wxT("Merge parallel transitions") );
	XS_SERIALIZE( m_fMergeDirectBraches, wxT("Merge direct branches") );
	XS_SERIALIZE( m_fOmitLabels, wxT("Omit unused labels") );
}

udStateChartCategory::~udStateChartCategory()
{
}
