#ifndef UDDEPENDENCIESDIALOG_H
#define UDDEPENDENCIESDIALOG_H

#include "gui/GUI.h"
#include "gui/DialogFunctions.h"
#include "DiagramBank.h"

class udDependenciesDialog : public _DependenciesDialog, udDialogFunctions
{
public:
	udDependenciesDialog(wxWindow *parent, SerializableList& records);
	virtual ~udDependenciesDialog();

};

#endif // UDDEPENDENCIESDIALOG_H
