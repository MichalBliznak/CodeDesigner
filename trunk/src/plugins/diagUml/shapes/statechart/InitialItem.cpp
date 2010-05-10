#include "InitialItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(umlInitialItem, uddCircleElement);

umlInitialItem::umlInitialItem()
{
    Initialize();
}

umlInitialItem::umlInitialItem(const umlInitialItem &obj)
: uddCircleElement(obj)
{
}

umlInitialItem::~umlInitialItem()
{
}

void umlInitialItem::Initialize()
{
    // set basic properties
    m_Fill = *wxBLACK_BRUSH;

    AcceptConnection(wxT("umlTransitionItem"));

    m_pTitle->SetText(wxT("Initial"));
    m_pTitle->SetRelativePosition( 0, 25 );
}

