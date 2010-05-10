/***************************************************************
 * Name:      Events.cpp
 * Purpose:   Implements internal event classes
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2009-01-29
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "Events.h"

//----------------------------------------------------------------------------------//
// udProjectEvent class
//----------------------------------------------------------------------------------//

udProjectEvent::udProjectEvent(const udProjectEvent& obj) : wxEvent( obj )
{
	m_pProjectItem = obj.m_pProjectItem;
	m_pParentItem = obj.m_pParentItem;
}

udProjectEvent::udProjectEvent(wxEventType cmdType, int id, udProjectItem *item, udProjectItem *parent) : wxEvent( id, cmdType )
{
	m_pProjectItem = item;
	m_pParentItem = parent;
}

udProjectEvent::~udProjectEvent()
{
}

//----------------------------------------------------------------------------------//
// udElementEvent class
//----------------------------------------------------------------------------------//


/*udElementEvent::udElementEvent(const udElementEvent& obj) : wxEvent( obj )
{
	m_pProjectItem = obj.m_pProjectItem;
	m_pParentItem = obj.m_pParentItem;
	m_pShape = obj.m_pShape;
}

udElementEvent::udElementEvent(wxEventType cmdType, int id) : wxEvent( id, cmdType )
{
	m_pProjectItem = NULL;
	m_pParentItem = NULL;
	m_pShape = NULL;
}

udElementEvent::~udElementEvent()
{
}*/

