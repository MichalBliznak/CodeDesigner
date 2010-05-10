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
	
protected:
	// protected data members
	wxString m_InputAction;
	
	wxStaticText* m_staticTextIA;
	wxChoice* m_chInputAction;
	
	// protected virtual functions
	virtual void OnAlgorithmChange( wxCommandEvent& event );
	virtual void OnInit( wxInitDialogEvent& event );
	virtual void OnOk( wxCommandEvent& event );

};
#endif // __sschdiagramdialog__
