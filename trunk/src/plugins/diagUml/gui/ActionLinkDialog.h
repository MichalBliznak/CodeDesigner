#ifndef __udactionlinkdialog__
#define __udactionlinkdialog__

#include "GUI.h"
#include "projectbase/ProjectBase.h"
#include "projectbase/codegen/Language.h"

class udActionLinkDialog : public _ActionLinkDialog
{

public:
	udActionLinkDialog(wxWindow *parent, udFunctionLinkItem *link, udLanguage *lang);
	virtual ~udActionLinkDialog();
	
	// member data accessors
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetActionType(const int& ActionType) {this->m_ActionType = ActionType;}
	
	const wxString& GetCodeName() const {return m_Name;}
	const int& GetActionType() const {return m_ActionType;}
	
protected:
	// protected data members
	wxString m_Name;
	int m_ActionType;
	
	udCodeItem *m_pOriginal;
	udFunctionLinkItem *m_pLink;
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnEditOriginal( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
};

#endif // __udactionlinkdialog__
