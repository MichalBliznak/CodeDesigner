#ifndef UDCLASSDIALOG_H
#define UDCLASSDIALOG_H

#include "GUI.h" // Base class: _ClassDialog
#include "projectbase/codegen/Language.h"

class udClassDialog : public _ClassDialog {

public:
	udClassDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udClassDialog();
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetIsTemplate(bool IsTemplate) {this->m_IsTemplate = IsTemplate;}
	void SetTemplateName(const wxString& TemplateName) {this->m_TemplateName = TemplateName;}
	
	bool GetIsTemplate() const {return m_IsTemplate;}
	const wxString& GetTemplateName() const {return m_TemplateName;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}

protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_TemplateName;
	bool m_IsTemplate;
	
	udLanguage *m_pLang;
	
	// event handlers
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnUpdateTemplate(wxUpdateUIEvent& event);
};

#endif // UDCLASSDIALOG_H
