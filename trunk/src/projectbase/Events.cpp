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

#include "ProjectBase.h"

DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_ADDED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_REMOVED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_CHANGED )
DEFINE_EVENT_TYPE( wxEVT_CD_ITEM_SELECTED )
DEFINE_EVENT_TYPE( wxEVT_CD_TASK_REMOVE )
DEFINE_EVENT_TYPE( wxEVT_CD_PROJECT_BEFORE_GENERATION)
DEFINE_EVENT_TYPE( wxEVT_CD_PROJECT_AFTER_GENERATION)
DEFINE_EVENT_TYPE( wxEVT_CD_PROJECT_FILE_ADDED)
/*DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_ADDED )
DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_REMOVED )
DEFINE_EVENT_TYPE( wxEVT_CD_ELEMENT_CHANGED )*/

//----------------------------------------------------------------------------------//
// udProjectEvent class
//----------------------------------------------------------------------------------//

udProjectEvent::udProjectEvent(const udProjectEvent& obj) : wxEvent( obj )
{
	m_pProjectItem = obj.m_pProjectItem;
	m_pParentItem = obj.m_pParentItem;
	m_StringData = obj.m_StringData;
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

