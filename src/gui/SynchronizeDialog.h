#ifndef SYNCHRONIZEDIALOG_H
#define SYNCHRONIZEDIALOG_H

#include "gui/GUI.h" // Base class: _SynchronizeDialog
#include "projectbase/ProjectBase.h"

class udSynchronizeDialog : public _SynchronizeDialog {

public:
	udSynchronizeDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udSynchronizeDialog();

public:
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnSelectCodeItem(wxCommandEvent& event);
	
protected:
	int m_nUpdated;
	int m_nAmbiguous;

	udLanguage *m_Lang;
	SerializableList m_lstFunctions;
	wxArrayString m_arrModified;
	wxArrayString m_arrOriginal;
};

#endif // SYNCHRONIZEDIALOG_H
