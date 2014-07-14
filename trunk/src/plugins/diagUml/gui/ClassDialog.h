#ifndef UDCLASSDIALOG_H
#define UDCLASSDIALOG_H

#include "GUI.h" // Base class: _ClassDialog
#include "projectbase/codegen/Language.h"

class udClassDialog : public _ClassDialog
{
public:
	udClassDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udClassDialog();
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	void SetGenerate(bool Generate) {this->m_Generate = Generate;}
	bool GetGenerate() const {return m_Generate;}

public:
	wxString m_Name;
	wxString m_Description;
	bool m_Generate;
	
	udLanguage *m_pLang;

	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDCLASSDIALOG_H
