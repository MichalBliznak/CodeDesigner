/*********************************************************************
 * Name:      	DiagTest.cpp
 * Purpose:   	Implements testing diagram plugin
 * Author:    	Michal Bližňák
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 *********************************************************************/
 
#include "DiagTest.h"
#include "projectbase/Common.h"

#include <wx/txtstrm.h>
 
////////////////////////////////////////////////////////////////////////////////
// plugin //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

udTestDiagramPlugin *thePlugin = NULL;

// create plugin-specific GUI identifiers
static long ID_BUTTON = IPluginManager::Get()->GetNewMenuId();
static long ID_MENU = IPluginManager::Get()->GetNewMenuId();

// define the plugin entry point
extern "C" WXDLLIMPEXP_CD IPlugin *CreatePlugin(IPluginManager *manager)
{
	if (thePlugin == NULL)
	{
		thePlugin = new udTestDiagramPlugin(manager);
	}
	
	return thePlugin;
}

extern "C" WXDLLIMPEXP_CD udPluginInfo GetPluginInfo()
{
	// set plugin info
	udPluginInfo info;
	
	info.SetAuthor( wxT("Michal Bližňák") );
	info.SetName( wxT("Test diagram") );
	info.SetDescription( wxT("Test plugin providing a simple diagram with code generator, custom menu, toolbar and AUI pane.") );
	info.SetType( udPluginInfo::ptMIXED );
	info.SetVersion( wxT("1.0") );
	info.SetAPIVersionMin( 1 );
	info.SetAPIVersionMax( 1 );
	
	return info;
}

udTestDiagramPlugin::udTestDiagramPlugin(IPluginManager *manager) : IPlugin(manager)
{
	// initialize plugin information
	
	// diagram info
	m_infoDiag.SetName( udnTEST_DIAGRAM );
	m_infoDiag.SetDataClassName( wxT("udTestDiagramItem") );
	m_infoDiag.SetIcon( wxT("plugins/project/UseCaseDiag.xpm") );
	
	// register diagram components
	m_infoDiag.AddComponentInfo( udDiagramComponentInfo(  wxT("plugins/elements/Actor.xpm"),
												wxT("Test element"),
												wxT("uddTestElement"),
												wxT("udTestElementItem"),
												udDiagramComponentInfo::pitELEMENT ) );
												
	// generator info
	m_infoGenerator.SetClassName( wxT("udTestGenerator") );
	m_infoGenerator.SetDiagramClassName( wxT("udTestDiagramItem") );
	m_infoGenerator.SetDescription( wxT("Test diagram generator") );
}

bool udTestDiagramPlugin::OnInit()
{
	// register diagram
	m_PluginManager->RegisterDiagram( m_infoDiag );
	
	// register code generator
	m_PluginManager->RegisterCodeGenerator( m_infoGenerator );
	
	// register friendly name
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTestElementItem"), wxT("Test element") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTestDiagramItem"), wxT("Test diagram") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTestGenerator"), wxT("Test generator") );
	m_PluginManager->RegisterFriendlyName( wxT("classname"), wxT("udTestAlgorithm"), wxT("Test algorithm") );
	
	// register plugin settings
	m_PluginManager->RegisterSettings( new udTestSettingsCategory(), IPluginManager::settingsPROJECT );
	m_PluginManager->RegisterSettings( new udTestAppSettingsCategory(), IPluginManager::settingsAPPLICATION );
	
	// connect events
	m_PluginManager->GetMainFrame()->Connect( ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(udTestDiagramPlugin::OnTest) );
	m_PluginManager->GetMainFrame()->Connect( ID_MENU, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(udTestDiagramPlugin::OnTest) );
	
	return true;
}

int udTestDiagramPlugin::OnExit()
{
	// note: diagram cannot be unregistered
	
	// unregister code generator
	m_PluginManager->UnregisterCodeGenerator( m_infoGenerator );
	
	// unregister friendly name
	m_PluginManager->UnregisterFriendlyName(  wxT("classname"), wxT("udTestElementItem") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udTestDiagramItem") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udTestGenerator") );
	m_PluginManager->UnregisterFriendlyName( wxT("classname"), wxT("udTestAlgorithm") );
	
	// note: plugin settings cannot be unregistered
	
	// disconnect events
	m_PluginManager->GetMainFrame()->Disconnect( ID_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(udTestDiagramPlugin::OnTest) );
	m_PluginManager->GetMainFrame()->Disconnect( ID_MENU, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(udTestDiagramPlugin::OnTest) );
	
	return 0;
}

udPluginInfo udTestDiagramPlugin::GetInfo()
{
	return GetPluginInfo();
}

////////////////////////////////////////////////////////////////////////////////
// registration of custom GUI controls /////////////////////////////////////////

wxMenu* udTestDiagramPlugin::CreateMenu()
{
	// create plugin menu (if needed) here...
	
	wxMenu *pMenu = new wxMenu();
	pMenu->Append( ID_MENU, wxT("Test") );
	
	return pMenu;
}

udPaneInfo udTestDiagramPlugin::CreateAuiPane(wxWindow *parent)
{
	// create plugin Aui pane (if needed) here...
	
	udPaneInfo PaneInfo;
	
	PaneInfo.SetName( wxT("Test pane") );
	PaneInfo.SetBestSize( wxSize( 250, 400 ) );
	PaneInfo.SetPane( new wxTextCtrl( parent, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE ) );
	
	return PaneInfo;
}

udToolbarInfo udTestDiagramPlugin::CreateToolbar(wxWindow *parent)
{
	// create plugin toolbar (if needed) here...
	
	udToolbarInfo TbInfo;
	
	wxAuiToolBar *pToolbar = new wxAuiToolBar( parent, wxID_ANY );
	pToolbar->AddControl( new wxButton( pToolbar, ID_BUTTON, wxT("Test button") ) );
	pToolbar->Realize();
	
	TbInfo.SetToolbar( pToolbar );
	TbInfo.SetName( wxT("Test toolbar") );
	
	return TbInfo;
}

void udTestDiagramPlugin::OnTest(wxCommandEvent& event)
{
	wxMessageBox( wxT("Test action"), wxT("CodeDesigner") );
}

////////////////////////////////////////////////////////////////////////////////
// exported classes ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// diagram classes /////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(uddTestElement, uddRectElement);

uddTestElement::uddTestElement()
{
	// initialize diagram component. For more details see wxShapeFramework
	// documentation.
	
	//AcceptConnection(wxT("Some_Connection_Class"));
	ClearAcceptedSrcNeighbours();
	ClearAcceptedTrgNeighbours();
	AcceptSrcNeighbour(wxT("uddNoteItem"));
    AcceptTrgNeighbour(wxT("uddNoteItem"));
}

XS_IMPLEMENT_CLONABLE_CLASS(udTestElementItem, udDiagElementItem);

XS_IMPLEMENT_CLONABLE_CLASS(udTestDiagramItem, udDiagramItem);

udTestDiagramItem::udTestDiagramItem()
{
	// initialize custom diagram:
	
    m_sDiagramType = udnTEST_DIAGRAM;
	SetName( udnTEST_DIAGRAM );

    m_sActiveGenerator = wxT("udTestGenerator");
    m_sActiveAlgorithm = wxT("udTestAlgorithm");
}

udTestDiagramItem::udTestDiagramItem(const udTestDiagramItem &obj)
: udDiagramItem(obj)
{
    m_sDiagramType = udnTEST_DIAGRAM;
}

udTestDiagramItem::~udTestDiagramItem()
{
}

////////////////////////////////////////////////////////////////////////////////
// generator class /////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udTestGenerator, udGenerator);

udTestGenerator::udTestGenerator()
{
	// initialize code generator:
	
	m_sName = wxT("Test generator");
    m_sDescription = wxT("");

	// this generator uses following code generation algorithm:
    m_mapAlgorithms[wxT("udTestAlgorithm")] = new udTestAlgorithm(this);
}

bool udTestGenerator::Initialize()
{
	// do some initialization stuff here if needed

	// default initialization must be called
    return udGenerator::Initialize();
}

bool udTestGenerator::ProcessDiagram(udDiagramItem* src)
{
	// generator should (optionaly) process diagram in the following ways:
	switch( m_nMode )
	{
		case genCOMMON_DECLARATION:
			return true;
			
		case genCOMMON_DEFINITION:
			return true;
			
		case genDECLARATION:
			return true;
			
		case genDEFINITION:
		{
			// generate some code by using selected algorithm
			
			// initialize output stream
			wxTextOutputStream textOut(*m_pOut);
				
			// make sure we are usign correct algorithm
			udTestAlgorithm *pAlg = wxDynamicCast( m_pAlgorithm, udTestAlgorithm );
			if( pAlg )
			{
				// process given diagram by selected algorithm
				pAlg->Process(src);
				
				// write generated code to output text stream
				textOut << m_pOutLang->GetCodeBuffer();
				
				return true;
			}
			else
				return false;
		}
			
		default:
			IPluginManager::Get()->Log( wxT("ERROR: No valid generation target has been specified.") );
			return false;
	}
}

void udTestGenerator::CleanUp()
{
	// do some clean-up stuff here if needed
}

////////////////////////////////////////////////////////////////////////////////
// algorithm class /////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udTestAlgorithm, udAlgorithm);

udTestAlgorithm::udTestAlgorithm()
{
	// initialize element processors:
	m_mapElementProcessors[wxT("uddTestElement")] = new udTestElementProcessor();

    m_sName = wxT("Test diagram algorithm");
	
	// set supported languages
    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udTestAlgorithm::udTestAlgorithm(udGenerator *parent) : udAlgorithm(parent)
{
	// initialize element processors:
	m_mapElementProcessors[wxT("uddTestElement")] = new udTestElementProcessor(parent);

    m_sName = wxT("Test diagram algorithm");
	
	// set supported languages
    m_arrSuppLanguages.Add(wxT("udCLanguage"));
    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

bool udTestAlgorithm::Initialize()
{
	// do some initialization stuff here if needed
	
	return udAlgorithm::Initialize();
}

void udTestAlgorithm::ProcessAlgorithm(udDiagramItem* src)
{
	// get active language
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	
	udDiagElementItem *pElement = NULL;
	
	// process given diagram:
	
	ShapeList lstElements;
	// get all diagram elements of given type from processed diagram.
	src->GetDiagramManager().GetShapes( CLASSINFO(uddTestElement), lstElements );
	
	for( ShapeList::iterator it = lstElements.begin(); it != lstElements.end(); ++it )
	{
		// process given element by suitable processor
		udElementProcessor *pProcessor = GetElementProcessor( (*it)->GetClassInfo()->GetClassName() );
		if(pProcessor)
		{
			pProcessor->ProcessElement( *it );
		}
		else
		{
			// handle a situation if suitable element processor doesn't exist
			pElement = udPROJECT::GetDiagramElement( *it );
			
			pLang->SingleLineCommentCmd( wxString::Format(wxT( "!!! WARNING: UNSUPPORTED ELEMENT ('%s') !!!"), pElement->GetName().c_str()) );
			// plugin manager can be accessed by using static function Get() as follows:
			IPluginManager::Get()->Log( wxString::Format(wxT("WARNING: '%s' element is not supported by this algorithm."), pElement->GetName().c_str()) );
		}
	}
}

void udTestAlgorithm::CleanUp()
{
	// do some clean-up stuff here if needed
}

////////////////////////////////////////////////////////////////////////////////
// element processor class /////////////////////////////////////////////////////

udTestElementProcessor::udTestElementProcessor()
{
	m_pParentGenerator = NULL;
}

udTestElementProcessor::udTestElementProcessor(udGenerator* parent) : udElementProcessor(parent)
{
	// do some initialization stuff here if needed
}

void udTestElementProcessor::ProcessElement(wxSFShapeBase* element)
{
	// process given diagram component:
	
	// get active language
	udLanguage *pLang = m_pParentGenerator->GetActiveLanguage();
	
	// get data of processed diagram element
	udDiagElementItem *pElement = udPROJECT::GetDiagramElement( element );
	
	pLang->WriteCodeBlocks( wxString::Format( wxT("<<< Processing '%s' diagram element at position %lf, %lf >>>"),
											  pElement->GetName().c_str(),
											  element->GetAbsolutePosition().x,
											  element->GetAbsolutePosition().y ) );
}

////////////////////////////////////////////////////////////////////////////////
// plugin project settings class ///////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udTestSettingsCategory, udSettingsCategory);

udTestSettingsCategory::udTestSettingsCategory() : udSettingsCategory( wxT("Test category") )
{
	m_fTestProperty = uddvDEFAULT_VALUE;
	
	// serialize class member (only if its current value differs from default one)
	XS_SERIALIZE_EX( m_fTestProperty, wxT("Test property"), uddvDEFAULT_VALUE );
}

udTestSettingsCategory::udTestSettingsCategory(const udTestSettingsCategory& obj) : udSettingsCategory( obj )
{
	SetName( wxT("Test category") );
	
	m_fTestProperty = obj.m_fTestProperty;

	XS_SERIALIZE_EX( m_fTestProperty, wxT("Test property"), uddvDEFAULT_VALUE );
}

udTestSettingsCategory::~udTestSettingsCategory()
{
}

////////////////////////////////////////////////////////////////////////////////
// plugin application settings class ///////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udTestAppSettingsCategory, udSettingsCategory);

udTestAppSettingsCategory::udTestAppSettingsCategory() : udSettingsCategory( wxT("Test main category") )
{
	m_fTestProperty = uddvDEFAULT_VALUE;
	
	// serialize class member (always, if needed)
	XS_SERIALIZE( m_fTestProperty, wxT("Test property") );
}

udTestAppSettingsCategory::udTestAppSettingsCategory(const udTestAppSettingsCategory& obj) : udSettingsCategory( obj )
{
	SetName( wxT("Test main category") );
	
	m_fTestProperty = obj.m_fTestProperty;

	XS_SERIALIZE( m_fTestProperty, wxT("Test property") );
}

udTestAppSettingsCategory::~udTestAppSettingsCategory()
{
}



