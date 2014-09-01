#ifndef __udsubstatedialog__
#define __udsubstatedialog__

#include "GUI.h"
#include "projectbase/codegen/Language.h"

class udSubStateDialog : public _SubStateDialog
{

public:
	udSubStateDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udSubStateDialog();
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetStoreRetVal(bool StoreRetVal) {this->m_StoreRetVal = StoreRetVal;}
	
	bool GetStoreRetVal() const {return m_StoreRetVal;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	bool m_StoreRetVal;
	
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udsubstatedialog__
