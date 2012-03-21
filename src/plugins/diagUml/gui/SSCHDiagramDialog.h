#ifndef __sschdiagramdialog__
#define __sschdiagramdialog__

#include "projectbase/gui/DiagramDialog.h"

class udSChDiagramDialog : public udDiagramDialog
{
public:
	udSChDiagramDialog(wxWindow *parent, udDiagramItem *diag, udLanguage *lang);
	virtual ~udSChDiagramDialog();
	
	// public member data accessors
	void SetInputAction(const wxString& InputAction) {this->m_InputAction = InputAction;}
	const wxString& GetInputAction() const {return m_InputAction;}
	void SetNonBlocking(bool NonBlocking) {this->m_NonBlocking = NonBlocking;}
	bool IsNonBlocking() const {return m_NonBlocking;}
	
protected:
	// protected data members
	wxString m_InputAction;
	bool m_NonBlocking;
	
	wxStaticText* m_staticTextIA;
	wxChoice* m_chInputAction;
	wxCheckBox* m_cbNonBlocking;
	
	// protected virtual functions
	virtual void OnAlgorithmChange( wxCommandEvent& event );
	virtual void OnInit( wxInitDialogEvent& event );
	virtual void OnOk( wxCommandEvent& event );

};
#endif // __sschdiagramdialog__
