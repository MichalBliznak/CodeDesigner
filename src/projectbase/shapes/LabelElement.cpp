#include "LabelElement.h"
#include "MultiLabelLineElement.h"
#include "../ProjectBase.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddLabelElement, wxSFEditTextShape);

uddLabelElement::uddLabelElement()
{
    Initiliaze();
	DisableUselessProperties();

	XS_SERIALIZE_INT(m_nLabelType, wxT("label_type"));
}

uddLabelElement::uddLabelElement(const uddLabelElement &obj)
: wxSFEditTextShape(obj)
{
    m_nLabelType = obj.m_nLabelType;

	DisableUselessProperties();

	XS_SERIALIZE_INT(m_nLabelType, wxT("label_type"));
}

uddLabelElement::~uddLabelElement()
{
}

void uddLabelElement::Initiliaze()
{
    // set basic properties
    SetText(wxT("Element"));
	
	AcceptChild(wxT("uddDnDElement"));
	//AcceptConnection(wxT("uddNoteConnItem"));
	//AcceptSrcNeighbour(wxT("All"));
    //AcceptTrgNeighbour(wxT("All"));

    m_nLabelType = uddvLABELELEMENT_LABELTYPE;

    //GetFont().SetPointSize(8);
	udSettings& settings = IPluginManager::Get()->GetAppSettings();
	SetFont( settings.GetProperty(wxT("Default font"))->AsFont() );
	SetHoverColour( settings.GetProperty(wxT("Hover colour"))->AsColour() );
	
    SetStyle( sfsPOSITION_CHANGE | sfsHOVERING | sfsPROCESS_DEL | sfsSHOW_HANDLES);
}

void uddLabelElement::DisableUselessProperties()
{
    // reduce project file size
    EnablePropertySerialization(wxT("border"), false);
    EnablePropertySerialization(wxT("fill"), false);
    EnablePropertySerialization(wxT("hborder"), false);
    EnablePropertySerialization(wxT("vborder"), false);
    EnablePropertySerialization(wxT("style"), false);
    EnablePropertySerialization(wxT("halign"), false);
    EnablePropertySerialization(wxT("valign"), false);
    EnablePropertySerialization(wxT("hover_color"), false);
    EnablePropertySerialization(wxT("font"), false);
	EnablePropertySerialization(wxT("custom_dock_point"), false);
	
	EnablePropertySerialization(wxT("accepted_connections"), false);
	EnablePropertySerialization(wxT("accepted_children"), false);
	EnablePropertySerialization(wxT("accepted_src_neighbours"), false);
	EnablePropertySerialization(wxT("accepted_trg_neighbours"), false);
	
	EnablePropertySerialization(wxT("edittype"), false);
	EnablePropertySerialization(wxT("multiline"), false);
	EnablePropertySerialization(wxT("label_type"), false);
}

void uddLabelElement::CreateHandles()
{
	AddHandle(wxSFShapeHandle::hndLEFTTOP);
}

void uddLabelElement::OnDragging(const wxPoint &pos)
{
	// if the label is dragged by the user then disable the automatic alignment
	if( !GetParentShape()->IsKindOf( CLASSINFO(uddMultiLabelLineElement)) )
	{
		SetVAlign(valignNONE);
		SetHAlign(halignNONE);
	}
}

void uddLabelElement::OnChildDropped(const wxRealPoint& pos, wxSFShapeBase* child)
{
	wxSFShapeBase *pUmlParent = wxDynamicCast( udPROJECT::GetParentElement( this ), wxSFShapeBase );
	if( pUmlParent )
	{
		pUmlParent->OnChildDropped( GetAbsolutePosition() + pos, child );
	}
}
