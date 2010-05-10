#ifndef UDMANAGEPLUGINSDIALOG_H
#define UDMANAGEPLUGINSDIALOG_H

#include "GUI.h" // Base class: _ManagePluginsDialog

class udManagePluginsDialog : public _ManagePluginsDialog {

public:
	udManagePluginsDialog(wxWindow *parent);
	virtual ~udManagePluginsDialog();

public:
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnPluginSelected(wxCommandEvent& event);
	virtual void OnInitDialog(wxInitDialogEvent& event);
	
	void FillPluginInfo(int index);
};

#endif // UDMANAGEPLUGINSDIALOG_H
