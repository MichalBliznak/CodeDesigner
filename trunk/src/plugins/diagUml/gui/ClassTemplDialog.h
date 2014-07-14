#ifndef UDCLASSTEMPLDIALOG_H
#define UDCLASSTEMPLDIALOG_H

#include "GUI.h" // Base class: _ClassDialog
#include "projectbase/codegen/Language.h"

class udClassTemplateDialog : public _ClassTemplateDialog {

public:
	udClassTemplateDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udClassTemplateDialog();
	
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetTemplateName(const wxString& TemplateName) {this->m_TemplateName = TemplateName;}
	
	const wxString& GetTemplateName() const {return m_TemplateName;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}

protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_TemplateName;
	
	udLanguage *m_pLang;
	
	// event handlers
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDCLASSTEMPLDIALOG_H
