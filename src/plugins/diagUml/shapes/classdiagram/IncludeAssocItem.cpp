#include "IncludeAssocItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlIncludeAssocItem, uddMultiLabelLineElement);

umlIncludeAssocItem::umlIncludeAssocItem()
{
    Initialize();
}

umlIncludeAssocItem::umlIncludeAssocItem(const umlIncludeAssocItem &obj)
: uddMultiLabelLineElement(obj)
{
}

umlIncludeAssocItem::~umlIncludeAssocItem()
{
}

void umlIncludeAssocItem::Initialize()
{
    // initialize shape	

	AcceptConnection(wxT("uddNoteConnItem"));

	m_Pen = wxPen( *wxBLACK, 1, wxSHORT_DASH );
	
	// create labels
	SetMaxLabelCount( 1 );
	
	uddLabelElement *pLabel = CreateLabel( udLABEL::ltSTEREOTYPE);
	if( pLabel )
	{
		pLabel->SetText( wxT("<< includes >>") );
		pLabel->SetEditType( wxSFEditTextShape::editDISABLED );
		pLabel->SetRelativePosition(0, -15);
		pLabel->SetHAlign( halignCENTER );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
	
	SetTrgArrow( CLASSINFO(wxSFOpenArrow) );
}
