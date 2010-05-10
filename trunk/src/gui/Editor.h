#ifndef __Editor__
#define __Editor__

#include "projectbase/codegen/Language.h"
#include "gui/GUI.h"

class udCodeEditor : public _EditorFrame
{
public:
	udCodeEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size);

	// public functions
	wxScintilla* GetScintilla() {return m_scintillaEditor;}

protected:

	// Handlers for EditorFrame events.
	virtual void OnClose( wxCloseEvent& event );
	virtual void OnCloseClick( wxCommandEvent& event );

	void OnMarginClick( wxScintillaEvent &event );

	DECLARE_EVENT_TABLE();
};

#endif // __Editor__
