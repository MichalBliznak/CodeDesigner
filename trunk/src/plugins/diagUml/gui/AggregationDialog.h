#ifndef UDAGGREGATIONDIALOG_H
#define UDAGGREGATIONDIALOG_H

#include "GUI.h" // Base class: _AggregationDialog
#include "projectbase/codegen/Language.h"

class WXDLLIMPEXP_CD udAggregationDialog : public _AggregationDialog {

public:
	udAggregationDialog(wxWindow *parent, udLanguage *lang);
	virtual ~udAggregationDialog();
	
	void SetAccessType(int AccessType) {this->m_AccessType = AccessType;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	int GetAccessType() const {return m_AccessType;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	void SetIncludeClass(bool IncludeClass) {this->m_IncludeClass = IncludeClass;}
	bool GetIncludeClass() const {return m_IncludeClass;}

protected:
	wxString m_Name;
	wxString m_Description;
	int m_AccessType;
	bool m_IncludeClass;

	udLanguage *m_Lang;
	
	virtual void OnInit(wxInitDialogEvent& event);
	virtual void OnMakeValid(wxCommandEvent& event);
	virtual void OnNameChange(wxCommandEvent& event);
	virtual void OnOk(wxCommandEvent& event);
};

#endif // UDAGGREGATIONDIALOG_H
