#ifndef UDENUMELEMENTDIALOG_H
#define UDENUMELEMENTDIALOG_H

#include "GUI.h" // Base class: _EnumElementDialog
#include "projectbase/codegen/Language.h"

class udEnumElementDialog : public _EnumElementDialog {

public:
	udEnumElementDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udEnumElementDialog();
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetValue(const wxString& Value) {this->m_Value = Value;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetValue() const {return m_Value;}
	const wxString& GetCodeName() const {return m_Name;}

protected:
	wxString m_Name;
	wxString m_Description;
	wxString m_Value;
	udLanguage *m_pLang;
	
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDENUMELEMENTDIALOG_H
