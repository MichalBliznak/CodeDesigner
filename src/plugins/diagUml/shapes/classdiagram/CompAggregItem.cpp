#include "CompAggregItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlCompAggregItem, umlUniDirectAssocItem);

umlCompAggregItem::umlCompAggregItem()
{
    Initialize();
}

umlCompAggregItem::umlCompAggregItem(const umlCompAggregItem &obj)
: umlUniDirectAssocItem(obj)
{
}

umlCompAggregItem::~umlCompAggregItem()
{
}

void umlCompAggregItem::Initialize()
{
    // initialize shape	
	wxSFDiamondArrow* pArrow = (wxSFDiamondArrow*)SetSrcArrow( CLASSINFO(wxSFDiamondArrow) );
	if( pArrow )
	{
		pArrow->SetArrowPen( *wxBLACK_PEN );
		pArrow->SetArrowFill( *wxBLACK_BRUSH );
	}
}
