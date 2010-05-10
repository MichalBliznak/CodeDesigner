#ifndef RENAMEVIRTUALDIALOG_H
#define RENAMEVIRTUALDIALOG_H

#include "GUI.h" // Base class: _RenameVirtualDialog
#include "../DiagCD.h"

#include "projectbase/ProjectBase.h"

class udRenameVirtualDialog : public _RenameVirtualDialog {

public:
	udRenameVirtualDialog(wxWindow *parent, udMemberFunctionItem *fcn, udLanguage *lang);
	virtual ~udRenameVirtualDialog();
	
	const wxString& GetName() {return this->m_Name;}
	const wxArrayString& GetCandidates() {return m_arrCandidates;}

protected:
	wxString m_Name;
	wxArrayString m_arrCandidates;
	
	udLanguage *m_Lang;
	
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnDeselectAll(wxCommandEvent& event);
	virtual void OnSelectAll(wxCommandEvent& event);
};

#endif // RENAMEVIRTUALDIALOG_H
