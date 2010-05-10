#include "UniDirectAssocItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlUniDirectAssocItem, uddMultiLabelLineElement);

umlUniDirectAssocItem::umlUniDirectAssocItem()
{
    Initialize();
}

umlUniDirectAssocItem::umlUniDirectAssocItem(const umlUniDirectAssocItem &obj)
: uddMultiLabelLineElement(obj)
{
}

umlUniDirectAssocItem::~umlUniDirectAssocItem()
{
}

void umlUniDirectAssocItem::Initialize()
{
    // initialize shape	

	AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = *wxBLACK_PEN;
	
	// create labels
	SetMaxLabelCount( 2 );
	
	uddLabelElement *pLabel = CreateLabel( udLABEL::ltASSOC_MULT1 );
	if( pLabel )
	{
		pLabel->SetText( wxT("*") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_END);
		pLabel->SetRelativePosition(0, -15);
		pLabel->SetHAlign( halignLINE_END );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}

	pLabel = CreateLabel( udLABEL::ltASSOC_ROLE1 );
	if( pLabel )
	{
		pLabel->SetText( wxT("role") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_END);
		pLabel->SetRelativePosition(0, 5);
		pLabel->SetHAlign( halignLINE_END );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
	
	SetTrgArrow( CLASSINFO(wxSFOpenArrow) );
}
