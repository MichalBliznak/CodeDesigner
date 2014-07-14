#ifndef __Log__
#define __Log__

#include "gui/GUI.h"

class udLog : public _LogPanel
{
public:
	udLog( wxWindow* parent, wxWindowID id );
	virtual ~udLog();

	// public functions

	void ClearMessages();
	void AddMessage(const wxString& msg);

protected:
	// protected data members

	wxMenu *m_pPopupMenu;

	// protected functions
	virtual void OnRightClick( wxMouseEvent& event );
	void OnClear( wxCommandEvent& event );

	DECLARE_EVENT_TABLE();

private:
	// private data members

	bool m_fIconsLoaded;
	wxImageList *m_lstImages;
};

#endif // __Log__
