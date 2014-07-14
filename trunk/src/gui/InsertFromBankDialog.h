#ifndef INSERTFROMBANKDIALOG_H
#define INSERTFROMBANKDIALOG_H

#include "gui/GUI.h"
#include "gui/DialogFunctions.h"
#include "Project.h"

class udInsertFromBankDialog : public _InsertFromBankDialog, udDialogFunctions
{	
public:
	udInsertFromBankDialog(wxWindow *parent, udPackageItem *package);
	virtual ~udInsertFromBankDialog();

protected:
	// protected data members
	udPackageItem *m_Package;

	// protected functions
	void FillDiagrams(const wxString& category);
	
	// protected virtual event handlers
	virtual void OnSelectAll( wxCommandEvent& event );
	virtual void OnDeselectAll( wxCommandEvent& event );
	virtual void OnInsertClick( wxCommandEvent& event );
	virtual void OnCategoryChange( wxCommandEvent& event );
	virtual void OnShowDeps( wxCommandEvent& event );
	virtual void OnUpdateShowDeps( wxUpdateUIEvent& event );
};

#endif // INSERTFROMBANKDIALOG_H
