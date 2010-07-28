#include "TemplateBindItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlTemplateBindItem, uddMultiLabelLineElement);

umlTemplateBindItem::umlTemplateBindItem()
{
    Initialize();
}

umlTemplateBindItem::umlTemplateBindItem(const umlTemplateBindItem &obj)
: uddMultiLabelLineElement(obj)
{
}

umlTemplateBindItem::~umlTemplateBindItem()
{
}

void umlTemplateBindItem::Initialize()
{
    // initialize shape	

	AcceptConnection(wxT("uddNoteConnItem"));
	AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = wxPen( *wxBLACK, 1, wxDOT );
	
	// create labels
	SetMaxLabelCount( 2 );
	
	uddLabelElement *pLabel = CreateLabel( udLABEL::ltTITLE );
	if( pLabel )
	{
		pLabel->SetText( wxT("<< bind >>") );
		pLabel->SetEditType( wxSFEditTextShape::editDISABLED );
		pLabel->SetRelativePosition(0, -15);
		pLabel->SetHAlign( halignCENTER );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}

	pLabel = CreateLabel( udLABEL::ltGUARD_CONTENT);
	if( pLabel )
	{
		pLabel->SetText( wxT("<>") );
		pLabel->SetRelativePosition(0, 5);
		pLabel->SetHAlign( halignCENTER );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
	
	SetTrgArrow( CLASSINFO(wxSFOpenArrow) );
}
