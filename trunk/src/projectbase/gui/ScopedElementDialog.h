#ifndef UDSCOPEDELEMENTDIALOG_H
#define UDSCOPEDELEMENTDIALOG_H

#include "GUI_ProjectBase.h" // Base class: _ScopedElementDialog
#include "projectbase/codegen/Language.h"

class WXDLLIMPEXP_CD udScopedElementDialog : public _ScopedElementDialog {

public:
	udScopedElementDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udScopedElementDialog();
	
	void SetAccessType(int AccessType) {this->m_AccessType = AccessType;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	int GetAccessType() const {return m_AccessType;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}

protected:
	wxString m_Name;
	wxString m_Description;
	int m_AccessType;

	udLanguage *m_Lang;
	
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDSCOPEDELEMENTDIALOG_H
