#include "BiDirectAssocItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlBiDirectAssocItem, uddMultiLabelLineElement);

umlBiDirectAssocItem::umlBiDirectAssocItem()
{
    Initialize();
}

umlBiDirectAssocItem::umlBiDirectAssocItem(const umlBiDirectAssocItem &obj)
: uddMultiLabelLineElement(obj)
{
}

umlBiDirectAssocItem::~umlBiDirectAssocItem()
{
}

void umlBiDirectAssocItem::Initialize()
{
    // initialize shape	

	AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = *wxBLACK_PEN;
	
	// create labels
	SetMaxLabelCount( 4 );
	
	uddLabelElement *pLabel = CreateLabel( udLABEL::ltASSOC_MULT1 );
	if( pLabel )
	{
		pLabel->SetText( wxT("*") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_START);
		pLabel->SetRelativePosition(0, -15);
		pLabel->SetHAlign( halignLINE_START );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}

	pLabel = CreateLabel( udLABEL::ltASSOC_ROLE1 );
	if( pLabel )
	{
		pLabel->SetText( wxT("role 1") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_START);
		pLabel->SetRelativePosition(0, 5);
		pLabel->SetHAlign( halignLINE_START );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
	
	pLabel = CreateLabel( udLABEL::ltASSOC_MULT2 );
	if( pLabel )
	{
		pLabel->SetText( wxT("*") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_END);
		pLabel->SetRelativePosition(0, -15);
		pLabel->SetHAlign( halignLINE_END );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
	
	pLabel = CreateLabel( udLABEL::ltASSOC_ROLE2 );
	if( pLabel )
	{
		pLabel->SetText( wxT("role 2") );
		pLabel->SetCustomDockPoint(sfdvLINESHAPE_DOCKPOINT_END);
		pLabel->SetRelativePosition(0, 5);
		pLabel->SetHAlign( halignLINE_END );
		pLabel->SetHBorder( 10 );
		pLabel->RemoveStyle( sfsPOSITION_CHANGE );
	}
}

