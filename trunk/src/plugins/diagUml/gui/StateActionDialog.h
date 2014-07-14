#ifndef __UDSTATEACTIONDIALOG__
#define __UDSTATEACTIONDIALOG__

#include "GUI.h"
#include "projectbase/codegen/Language.h"

class udStateActionDialog : public _StateActionDialog
{

public:
	udStateActionDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udStateActionDialog();
	
	// member data accessors
	void SetCode(const wxString& Code) {this->m_Code = Code;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetInline(const bool& Inline) {this->m_Inline = Inline;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetActionType(const int& ActionType) {this->m_ActionType = ActionType;}
	
	const wxString& GetCode() const {return m_Code;}
	const wxString& GetDescription() const {return m_Description;}
	const bool& GetInline() const {return m_Inline;}
	const wxString& GetCodeName() const {return m_Name;}
	const int& GetActionType() const {return m_ActionType;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_Code;
	int m_ActionType;
	bool m_Inline;
	
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __UDSTATEACTIONDIALOG__
