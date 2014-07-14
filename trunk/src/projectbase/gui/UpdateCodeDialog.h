#ifndef UPDATECODEDIALOG_H
#define UPDATECODEDIALOG_H

#include "GUI_ProjectBase.h" // Base class: _UpdateCodeDialog
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udUpdateCodeDialog : public _UpdateCodeDialog
{
public:
	udUpdateCodeDialog(wxWindow *parent, SerializableList *references, udLanguage *lang);
	virtual ~udUpdateCodeDialog();
	
	void SetPattern(const wxString& Pattern) {this->m_Pattern = Pattern;}
	void SetNewPattern(const wxString& NewPattern) {this->m_NewPattern = NewPattern;}

protected:
	udLanguage *m_Lang;
	wxString m_Pattern;
	wxString m_NewPattern;
	SerializableList *m_References;
	
	void UpdateCodePreview(int selection);

	virtual void OnCancel(wxCommandEvent& event);
	virtual void OnChangeCodeitem(wxCommandEvent& event);
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnUpdate(wxCommandEvent& event);
	virtual void OnNext(wxCommandEvent& event);
	virtual void OnPrevious(wxCommandEvent& event);
	virtual void OnDeselectAll(wxCommandEvent& event);
	virtual void OnSelectAll(wxCommandEvent& event);

};

#endif // UPDATECODEDIALOG_H
