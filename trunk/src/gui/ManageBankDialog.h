#ifndef MANAGEBANKDIALOG_H
#define MANAGEBANKDIALOG_H

#include "gui/GUI.h"
#include "gui/DialogFunctions.h"
#include "DiagramBank.h"

class udManageBankDialog : public _ManageBankDialog, udDialogFunctions
{
public:
	udManageBankDialog(wxWindow *parent);
	virtual ~udManageBankDialog();

protected:
	// protected functions
	void FillCategories();
	void FillDiagrams(const wxString& category);
	void FillDependencies(udDiagramItem *diagram);
	udDiagramRecord* GetSelectedRecord();
	udDiagramRecord* CopyRecord();
	
	// protected virtual event handlers
	virtual void OnCreateCat( wxCommandEvent& event );
	virtual void OnMoveDiag( wxCommandEvent& event );
	virtual void OnRemoveCat( wxCommandEvent& event );
	virtual void OnRemoveDiag( wxCommandEvent& event );
	virtual void OnRemoveAllDiag( wxCommandEvent& event );
	virtual void OnRenameCat( wxCommandEvent& event );
	virtual void OnCategoryChange( wxCommandEvent& event );
	virtual void OnCopyDiag( wxCommandEvent& event );
	virtual void OnDiagramChange( wxListEvent& event );
	virtual void OnUpdateRenameCat( wxUpdateUIEvent& event );
	virtual void OnUpdateRemoveCat( wxUpdateUIEvent& event );
	virtual void OnUpdateRemoveDiag( wxUpdateUIEvent& event );
	virtual void OnUpdateRemoveAllDiag( wxUpdateUIEvent& event );
	virtual void OnUpdateMoveTo( wxUpdateUIEvent& event );
	virtual void OnUpdateCopyTo( wxUpdateUIEvent& event );
};

#endif // MANAGEBANKDIALOG_H
