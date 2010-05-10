#ifndef __udcodelinkdialog__
#define __udcodelinkdialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD udCodeLinkDialog : public _CodeLinkDialog
{

public:
	udCodeLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang);
	virtual ~udCodeLinkDialog();
	
	// member data accessors
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	
	udCodeItem *m_pOriginal;
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnEditOriginal( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udcodelinkdialog__
