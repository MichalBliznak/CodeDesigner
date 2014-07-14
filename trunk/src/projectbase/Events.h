/***************************************************************
 * Name:      Events.h
 * Purpose:   Defines internal event classes
 * Author:    Michal Bližňák (michal.bliznak@tiscali.cz)
 * Created:   2009-01-29
 * Copyright: Michal Bližňák
 * License:   wxWidgets license (www.wxwidgets.org)
 * Notes:
 **************************************************************/

#ifndef _EVENTS_H
#define _EVENTS_H

#include <wx/event.h>
#include <wx/dnd.h>

#include "interfaces/Defs.h"

class udProjectEvent;
class udProjectItem;

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_ITEM_ADDED, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_ITEM_REMOVED, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_ITEM_CHANGED, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_ITEM_SELECTED, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_TASK_REMOVE, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_PROJECT_BEFORE_GENERATION, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_PROJECT_AFTER_GENERATION, wxID_ANY )
	DECLARE_EXPORTED_EVENT_TYPE( WXDLLIMPEXP_CD, wxEVT_CD_PROJECT_FILE_ADDED, wxID_ANY )
	/*DECLARE_EVENT_TYPE( wxEVT_CD_ELEMENT_ADDED, 8773 )
	DECLARE_EVENT_TYPE( wxEVT_CD_ELEMENT_REMOVED, 8774 )
	DECLARE_EVENT_TYPE( wxEVT_CD_ELEMENT_CHANGED, 8775 )*/
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*udProjectEventFunction)(udProjectEvent&);

#define udProjectEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(udProjectEventFunction, &func)

#define EVT_CD_ITEM_ADDED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_ITEM_ADDED, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),

#define EVT_CD_ITEM_REMOVED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_ITEM_REMOVED, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),

#define EVT_CD_ITEM_CHANGED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_ITEM_CHANGED, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),
							 
#define EVT_CD_ITEM_SELECTED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_ITEM_SELECTED, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),
							 
#define EVT_CD_TASK_REMOVE(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_TASK_REMOVE, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),
							 
#define EVT_CD_PROJECT_BEFORE_GENERATION(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_PROJECT_BEFORE_GENERATION, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),
							 
#define EVT_CD_PROJECT_AFTER_GENERATION(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_PROJECT_AFTER_GENERATION, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),
							 
#define EVT_CD_PROJECT_FILE_ADDED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	                           wxEVT_CD_PROJECT_FILE_ADDED, id, wxID_ANY, \
	                           (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( udProjectEventFunction, &fn ), \
	                           (wxObject *) NULL \
	                         ),

class WXDLLIMPEXP_CD udProjectEvent : public wxEvent
{
public:
	udProjectEvent(wxEventType cmdType = wxEVT_NULL, int id = 0, udProjectItem *item = NULL, udProjectItem *parent = NULL);
	udProjectEvent(const udProjectEvent& obj);
	virtual ~udProjectEvent();

	// public member data accessors
	
	void SetProjectItem(udProjectItem* ProjectItem) { this->m_pProjectItem = ProjectItem; }
	void SetParentItem(udProjectItem* ParentItem) { this->m_pParentItem = ParentItem; }
	void SetString(const wxString& StringData) {this->m_StringData = StringData;}
	
	udProjectItem* GetProjectItem() { return m_pProjectItem; }
	udProjectItem* GetParentItem() { return m_pParentItem; }
	const wxString& GetString() const {return m_StringData;}
	
	wxEvent* Clone() const { return new udProjectEvent(*this); }


private:
	// private data members
	udProjectItem *m_pProjectItem;
	udProjectItem *m_pParentItem;
	wxString m_StringData;
};


#endif // _EVENTS_H
