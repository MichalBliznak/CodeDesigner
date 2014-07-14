#ifndef UDGROUPDIALOG_H
#define UDGROUPDIALOG_H

#include "GUI.h" // Base class: _GroupDialog

class udGroupDialog : public _GroupDialog {

public:
	udGroupDialog(wxWindow *parent);
	virtual ~udGroupDialog();
	
	void SetColour(const wxColour& Colour) {this->m_Colour = Colour;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	const wxColour& GetColour() const {return m_Colour;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	
protected:
	wxColour m_Colour;
	wxString m_Name;
	wxString m_Description;
	
	virtual void OnOk(wxCommandEvent& event);
	virtual void OnInitDialog(wxInitDialogEvent& event);

};

#endif // UDGROUPDIALOG_H
