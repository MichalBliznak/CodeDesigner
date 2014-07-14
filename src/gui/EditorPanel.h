#ifndef __EditorPanel__
#define __EditorPanel__

#include "projectbase/ProjectBase.h"

#include "gui/GUI.h"

class udCodeEditorPanel : public _EditorPanel
{
public:
	udCodeEditorPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize );

	// public functions
	wxStyledTextCtrl* GetScintilla() {return m_scintillaEditor;}

protected:
	// protected functions
	udCodeItem *GetAsCodeItem( udProjectItem *item );
	bool CanSave();

	// Handlers for EditorFrame events.
	virtual void OnSave( wxCommandEvent &event );
	virtual void OnUpdateSave( wxUpdateUIEvent& event );
	virtual void OnKeyDown( wxKeyEvent& event );
	
	void OnProjectItemSelected( udProjectEvent& event );
	void OnMarginClick( wxStyledTextEvent &event );

	DECLARE_EVENT_TABLE();
	
private:
	udLanguage *m_pPrevLang;
};

#endif // __EditorPanel__
