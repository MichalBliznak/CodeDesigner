#ifndef __udfunctionlinkdialog__
#define __udfunctionlinkdialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udFunctionLinkDialog : public _FunctionLinkDialog
{

public:
	udFunctionLinkDialog(wxWindow *parent, udFunctionLinkItem *link, udLanguage *lang);
	virtual ~udFunctionLinkDialog();
	
	// member data accessors
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	// protected data members
	wxString m_Name;
	
	udFunctionLinkItem *m_pLink;
	udLanguage *m_pLang;
	udCodeItem *m_pOriginal;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnEditOriginal( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
	
	// protected event handlers
	/*void OnPropertyGridChange( wxPropertyGridEvent& event );
	
	DECLARE_EVENT_TABLE();*/
};

#endif // __udfunctionlinkdialog__
