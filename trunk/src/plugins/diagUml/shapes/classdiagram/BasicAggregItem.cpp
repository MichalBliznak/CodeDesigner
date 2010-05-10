#include "BasicAggregItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlBasicAggregItem, umlUniDirectAssocItem);

umlBasicAggregItem::umlBasicAggregItem()
{
    Initialize();
}

umlBasicAggregItem::umlBasicAggregItem(const umlBasicAggregItem &obj)
: umlUniDirectAssocItem(obj)
{
}

umlBasicAggregItem::~umlBasicAggregItem()
{
}

void umlBasicAggregItem::Initialize()
{
    // initialize shape	
	wxSFDiamondArrow* pArrow = (wxSFDiamondArrow*)SetSrcArrow( CLASSINFO(wxSFDiamondArrow) );
	if( pArrow )
	{
		pArrow->SetArrowPen( *wxBLACK_PEN );
		pArrow->SetArrowFill( *wxWHITE_BRUSH );
	}
}
