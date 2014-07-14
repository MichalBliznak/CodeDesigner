#ifndef UDENUMDIALOG_H
#define UDENUMDIALOG_H

#include "GUI.h" // Base class: _EnumDialog
#include "projectbase/codegen/Language.h"

class udEnumDialog : public _EnumDialog {

public:
	udEnumDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udEnumDialog();
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetInstanceName(const wxString& InstanceName) {this->m_InstanceName = InstanceName;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetInstanceName() const {return m_InstanceName;}
	const wxString& GetCodeName() const {return m_Name;}

protected:
	wxString m_Name;
	wxString m_Description;
	wxString m_InstanceName;
	
	udLanguage *m_pLang;

	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDENUMDIALOG_H
