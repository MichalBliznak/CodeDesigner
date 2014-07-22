#ifndef UDEVENTLINKDIALOG_H
#define UDEVENTLINKDIALOG_H

#include "GUI.h" // Base class: _EventLinkDialog
#include "projectbase/ProjectBase.h"
#include "projectbase/codegen/Language.h"

class udEventLinkDialog : public _EventLinkDialog
{
public:
	udEventLinkDialog(wxWindow *parent, udCodeItem *orig, udLanguage *lang);
	virtual ~udEventLinkDialog();
	
	// public member data accessors
	void SetClearFlag(bool ClearFlag) {this->m_fClearFlag = ClearFlag;}
	void SetCodeName(const wxString& Name) {this->m_sName = Name;}
	bool IsClearFlag() const {return m_fClearFlag;}
	const wxString& GetCodeName() const {return m_sName;}
	
protected:
	// protected data members
	wxString m_sName;
	bool m_fClearFlag;
	
	udCodeItem *m_pOriginal;
	udLanguage *m_pLang;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnEditOriginal( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );

};

#endif // UDEVENTLINKDIALOG_H
