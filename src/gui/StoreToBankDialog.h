#ifndef STORETOBANKDIALOG_H
#define STORETOBANKDIALOG_H

#include "gui/GUI.h"
#include "gui/DialogFunctions.h"
#include "Project.h"

class udStoreToBankDialog : public _StoreToBankDialog, udDialogFunctions {

public:
	udStoreToBankDialog(wxWindow *parent, udDiagramItem *diag);
	virtual ~udStoreToBankDialog();

protected:
	// protected data members
	udDiagramItem* m_Diagram;

	// virtual event handlers
	virtual void OnCreateClick( wxCommandEvent& event );
	virtual void OnStoreClick( wxCommandEvent& event );
};

#endif // STORETOBANKDIALOG_H
