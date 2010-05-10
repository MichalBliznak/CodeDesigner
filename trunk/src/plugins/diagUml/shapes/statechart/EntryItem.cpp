#include "EntryItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlEntryItem, uddCircleElement);

umlEntryItem::umlEntryItem()
{
    Initialize();
}

umlEntryItem::umlEntryItem(const umlEntryItem &obj)
: uddCircleElement(obj)
{
}

umlEntryItem::~umlEntryItem()
{
}

void umlEntryItem::Initialize()
{
    m_pTitle->SetText(wxT("Entry"));
    m_pTitle->SetRelativePosition( 0, 25 );

    AcceptConnection(wxT("umlTransitionItem"));
}



