#ifndef __udfinalstatedialog__
#define __udfinalstatedialog__

#include "GUI.h"
#include "projectbase/codegen/Language.h"

class udFinalStateDialog : public _FinalStateDialog
{

public:
	udFinalStateDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udFinalStateDialog();
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetReturnValue(const wxString& ReturnValue) {this->m_ReturnValue = ReturnValue;}
	
	const wxString& GetReturnValue() const {return m_ReturnValue;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_ReturnValue;
	
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnDefault( wxCommandEvent& event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udfinalstatedialog__
