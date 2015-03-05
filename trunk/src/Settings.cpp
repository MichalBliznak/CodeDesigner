#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "Settings.h"
#include "projectbase/Common.h"

/////////////////////////////////////////////////////////////////////////////////////
// udAppSettings class //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

udAppSettings::udAppSettings()
{
	SetSerializerRootName( wxT("configuration") );
	SetSerializerOwner( wxT("CodeDesigner") );
	// set current settings file version (will be tested during settings' deserialization)
	SetSerializerVersion( wxT("4") );
}

udAppSettings::~udAppSettings()
{
}

void udAppSettings::CreateCategories()
{
	// initialize categories
	AddItem( GetRootItem(), new udFrameCategory() );
	AddItem( GetRootItem(), new udDiagramsCategory() );
	AddItem( GetRootItem(), new udEditorCategory() );
	AddItem( GetRootItem(), new udGeneratorCategory() );
	
	AddItem( GetRootItem(), new udHiddenGUICategory() );
}

/////////////////////////////////////////////////////////////////////////////////////
// udDiagramsCategory class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udFrameCategory, udSettingsCategory);

udFrameCategory::udFrameCategory() : udSettingsCategory( wxT("Main frame") )
{
	// initialize application settings
	m_colBackground = udFRAME::GetBcgColour();
	m_fShowSplash = true;
	
	XS_SERIALIZE( m_colBackground, wxT("Background colour") );
	XS_SERIALIZE( m_fShowSplash, wxT("Show splash screen") );
}

udFrameCategory::~udFrameCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udDiagramsCategory class /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udDiagramsCategory, udSettingsCategory);

udDiagramsCategory::udDiagramsCategory() : udSettingsCategory( wxT("Diagrams") )
{
	// initialize application settings
	m_fShowGrid = true;
	m_fUseGraphicsContext = false;
	m_fExportBackground = false;
	
	m_colHighlightCol = wxColour( 128, 128, 255 );
	m_colBackgroundFrom = wxColour( 255, 255, 255 );
	m_colBackgroundTo = wxColour( 200, 200, 255 );
	m_colDisabledBackgroundFrom = wxColour( 255, 255, 255 );
	m_colDisabledBackgroundTo = wxColour( 255, 200, 200 );
	
	m_nDefaultFont = sfdvTEXTSHAPE_FONT;
	
	// initialize categories' properties
	XS_SERIALIZE( m_fShowGrid, wxT("Show grid") );
	XS_SERIALIZE( m_fUseGraphicsContext, wxT("Use enhanced graphics") );
	XS_SERIALIZE( m_nDefaultFont, wxT("Default font") );
	XS_SERIALIZE( m_colHighlightCol, wxT("Hover colour") );
	XS_SERIALIZE( m_colBackgroundFrom, wxT("Canvas gradient start") );
	XS_SERIALIZE( m_colBackgroundTo, wxT("Canvas gradient end") );
	XS_SERIALIZE( m_colDisabledBackgroundFrom, wxT("Disabled canvas gradient start") );
	XS_SERIALIZE( m_colDisabledBackgroundTo, wxT("Disabled canvas gradient end") );
	XS_SERIALIZE( m_fExportBackground, wxT("Export canvas background") );
}

udDiagramsCategory::~udDiagramsCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udGUICategory class //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udHiddenGUICategory, udHiddenCategory);

udHiddenGUICategory::udHiddenGUICategory() : udHiddenCategory( wxT("Hidden GUI category") )
{
	// initialize application settings
	m_sPerspective = wxT("");
	m_fShowThumbElements = true;
	m_fShowThumbConnections = false;
	m_fShowProperties = true;
	m_fOrganizeCI = true;
	m_fLinkDesigner = true;
	m_nProjManSashPos = 350;
	
	// initialize categories' properties
	XS_SERIALIZE( m_sPerspective, wxT("Perspective") );
	XS_SERIALIZE( m_fShowThumbElements, wxT("Show elements in thumbnail") );
	XS_SERIALIZE( m_fShowThumbConnections, wxT("Show connections in thumbnail") );
	XS_SERIALIZE( m_fShowProperties, wxT("Show item properties") );
	XS_SERIALIZE( m_fOrganizeCI, wxT("Organize code items") );
	XS_SERIALIZE( m_fLinkDesigner, wxT("Link manager with designer") );
	XS_SERIALIZE( m_nProjManSashPos, wxT("Project manager sash position") );
	XS_SERIALIZE( m_arrRecentFiles, wxT("Recent files") );
}

udHiddenGUICategory::~udHiddenGUICategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udGeneratorCategory class ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udGeneratorCategory, udSettingsCategory);

udGeneratorCategory::udGeneratorCategory() : udSettingsCategory( wxT("Code generator") )
{
	// initialize application settings
	m_sBaseFileName = wxT("CDCode");
	m_sCodeItemsFileName = wxT("CDCode_CI");
	m_sOutDir = wxGetHomeDir();
	m_fGenerateDescription = false;
	m_fSyncBeforeGenerate = true;
	
	// initialize categories' properties
	XS_SERIALIZE_DIR( m_sOutDir, wxT("Output directory") );
	XS_SERIALIZE( m_sBaseFileName, wxT("Base file name") );
	XS_SERIALIZE( m_sCodeItemsFileName, wxT("Code items file name") );
	XS_SERIALIZE( m_fGenerateDescription, wxT("Generate code descriptions") );
	XS_SERIALIZE( m_fSyncBeforeGenerate, wxT("Synchronize before generation") );
}

udGeneratorCategory::~udGeneratorCategory()
{
}


/////////////////////////////////////////////////////////////////////////////////////
// udProjectSettings class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

udProjectSettings::udProjectSettings()
{
}

udProjectSettings::~udProjectSettings()
{
}

void udProjectSettings::CreateCategories()
{
	// initialize categories
	AddItem( GetRootItem(), new udGeneratorCategory() );
	AddItem( GetRootItem(), new udHiddenProjectCategory() );
}


/////////////////////////////////////////////////////////////////////////////////////
// udHiddenProjectCategory class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udHiddenProjectCategory, udHiddenCategory);

udHiddenProjectCategory::udHiddenProjectCategory()
{
    m_sActiveLanguage = wxT("udCLanguage");
	m_nProjectVersion = 1;
	
    XS_SERIALIZE(m_sActiveLanguage, wxT("active_language"));
    XS_SERIALIZE(m_nProjectVersion, wxT("project_version"));
}

udHiddenProjectCategory::~udHiddenProjectCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udEditorCategory class ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udEditorCategory, udSettingsCategory);

udEditorCategory::udEditorCategory() : udSettingsCategory( wxT("Editor") )
{
	// initialize application settings
	m_fUseTabs = false;
	m_nTabWidth = 4;
	m_nIndentWidth = 4;
#ifdef __WXGTK__
	m_EditorFont = wxFont( 8, wxMODERN, wxNORMAL, wxNORMAL );
	m_EditorFont.SetFaceName( wxT( "Monospace" ) );
#else
	m_EditorFont = wxFont( 9, wxMODERN, wxNORMAL, wxNORMAL );
#endif
	
	// initialize categories' properties
	XS_SERIALIZE( m_fUseTabs, wxT("Use tabulators") );
	XS_SERIALIZE( m_nTabWidth, wxT("Tabulator width") );
	XS_SERIALIZE( m_nIndentWidth, wxT("Indentation width") );
	XS_SERIALIZE( m_EditorFont, wxT("Editor font") );
}

udEditorCategory::~udEditorCategory()
{
}
