#ifndef CLASSINSTANCEDIALOG_H
#define CLASSINSTANCEDIALOG_H

#include "GUI.h" // Base class: _ClassInstanceDialog

class ClassInstanceDialog : public _ClassInstanceDialog
{
public:
	ClassInstanceDialog(wxWindow *parent);
	virtual ~ClassInstanceDialog();

	const wxString& GetInstanceName() const {return m_InstanceName;}
	bool GetIsDynamic() const {return m_IsDynamic;}
	const wxString& GetParameters() const {return m_Parameters;}

protected:
	wxString m_InstanceName;
	wxString m_Parameters;
	bool m_IsDynamic;
	
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnInit(wxInitDialogEvent& event);
};

#endif // CLASSINSTANCEDIALOG_H
