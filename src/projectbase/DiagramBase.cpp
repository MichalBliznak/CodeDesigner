#include "DiagramBase.h"
#include "ProjectBase.h"
#include "SettingsBase.h"

#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(DiagramComponentArray);

////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udDiagramCanvas, wxSFShapeCanvas);

udDiagramCanvas::udDiagramCanvas()
{
    GetDiagramManager()->ClearAcceptedShapes();
	GetDiagramManager()->AcceptShape( wxT("uddDnDElement") );

	GetHistoryManager().SetMode(wxSFCanvasHistory::histUSE_SERIALIZATION);
	GetHistoryManager().SetHistoryDepth(20);
	
	SaveCanvasState();
	
    InitializeCanvas();
}

udDiagramCanvas::udDiagramCanvas(wxSFDiagramManager* manager, wxWindow* parent, long id)
: wxSFShapeCanvas( manager, parent, id)
{
	GetDiagramManager()->ClearAcceptedShapes();
	GetDiagramManager()->AcceptShape( wxT("uddDnDElement") );

	GetHistoryManager().SetMode(wxSFCanvasHistory::histUSE_SERIALIZATION);
	GetHistoryManager().SetHistoryDepth(20);
	
	SaveCanvasState();
	
    InitializeCanvas();
}

udDiagramCanvas::~udDiagramCanvas()
{
}

void udDiagramCanvas::InitializeCanvas()
{
	AddStyle(sfsGRADIENT_BACKGROUND);
	
	AddStyle(sfsPROCESS_MOUSEWHEEL);
	SetMinScale(0.2);
	SetMaxScale(2);
	
	// apply default application settings
	udSettings& settings = IPluginManager::Get()->GetAppSettings();
	
	SetHoverColour( settings.GetProperty(wxT("Hover colour"))->AsColour() );
	
	InitializeBackground();
	
	if( settings.GetProperty(wxT("Show grid"))->AsBool() )
	{
		AddStyle( wxSFShapeCanvas::sfsGRID_USE );
		AddStyle( wxSFShapeCanvas::sfsGRID_SHOW );
		SetGridLineMult( 10 );
		#if defined (__WXMSW__) || defined (__WXMAC__)
		SetGridStyle( wxDOT );
		#else
		SetGridStyle( wxSHORT_DASH );
		#endif
	}
	else
	{
		RemoveStyle( wxSFShapeCanvas::sfsGRID_USE );
		RemoveStyle( wxSFShapeCanvas::sfsGRID_SHOW );
	}

	// set selected font to all text-based shapes
	uddLabelElement *pLabel;
	ShapeList lstTexts;
	
	const wxFont& defFont = settings.GetProperty(wxT("Default font"))->AsFont();
	
	GetDiagramManager()->GetShapes( CLASSINFO(uddLabelElement), lstTexts );
	ShapeList::compatibility_iterator node = lstTexts.GetFirst();
	while( node )
	{
		pLabel = (uddLabelElement*) node->GetData();
		// update some text properties
		pLabel->GetFont().SetPointSize( defFont.GetPointSize() );
		pLabel->GetFont().SetFamily ( defFont.GetFamily() );
		pLabel->GetFont().SetFaceName( defFont.GetFaceName() );
		
		node = node->GetNext();
	}
	
	// switch on/off accelerated graphics
	#if wxUSE_GRAPHICS_CONTEXT
	EnableGC( settings.GetProperty(wxT("Use enhanced graphics"))->AsBool() );
	#endif
}

void udDiagramCanvas::InitializeBackground()
{
	udSettings& settings = IPluginManager::Get()->GetAppSettings();
	udDiagramManager *manager = GetManager();
	
	if( manager->GetParentProjItem()->IsGenerated() )
	{
		SetGradientFrom( settings.GetProperty(wxT("Canvas gradient start"))->AsColour() );
		SetGradientTo( settings.GetProperty(wxT("Canvas gradient end"))->AsColour() );
	}
	else
	{
		SetGradientFrom( settings.GetProperty(wxT("Disabled canvas gradient start"))->AsColour() );
		SetGradientTo( settings.GetProperty(wxT("Disabled canvas gradient end"))->AsColour() );
	}
}

////////////////////////////////////////////////////////////////////////////////

XS_IMPLEMENT_CLONABLE_CLASS(udDiagramManager, wxSFDiagramManager);

udDiagramManager::udDiagramManager()
{
	m_pParentProjItem = NULL;
}

udDiagramManager::udDiagramManager(const udDiagramManager& obj) : wxSFDiagramManager(obj)
{
	m_pParentProjItem = obj.m_pParentProjItem;
}

udDiagramManager::udDiagramManager(udDiagramItem* parent)
{
	m_pParentProjItem = parent;
}

void udDiagramManager::UpdateAllInnerContent()
{
	udDiagElementItem *pElement;
	
	ShapeList lstShapes;
	GetShapes(CLASSINFO(wxSFShapeBase), lstShapes);
	
	// optimization: remove all shapes without user data
	wxSFShapeBase *pShape;
	ShapeList::compatibility_iterator node = lstShapes.GetFirst();
	while( node )
	{
		if( !node->GetData()->GetUserData() )
		{
			pShape = node->GetData();
			node = node->GetNext();
			
			lstShapes.DeleteObject( pShape );
		}
		else
			node = node->GetNext();
	}
	
	node = lstShapes.GetFirst();
	while( node )
	{
		// it is neccessary to assure whether given object exists in the serializer because UpdateInnerContent
		// function can delete some objects referenced in the examined list.
		if( Contains( node->GetData() ) )
		{
			pElement = wxDynamicCast( node->GetData()->GetUserData(), udDiagElementItem );
			if( pElement ) pElement->UpdateInnerContent();
		}
		
		node = node->GetNext();
	}
}
