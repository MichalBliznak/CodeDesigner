#ifndef __udelementdialog__
#define __udelementdialog__

#include "GUI_ProjectBase.h"
#include "../codegen/Language.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD udElementDialog : public _ElementDialog
{

public:
	udElementDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udElementDialog();
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udelementdialog__
