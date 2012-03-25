#ifndef __diagramdialog__
#define __diagramdialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udDiagramDialog : public _DiagramDialog
{
public:
	udDiagramDialog(wxWindow *parent, udDiagramItem *diag, udLanguage *lang);
	virtual ~udDiagramDialog();
	
	// public member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetOutputFile(const wxString& OutputFile) {this->m_OutputFile = OutputFile;}
	void SetGenerateCode(const bool& GenerateCode) {this->m_GenerateCode = GenerateCode;}
	
	const bool& GetGenerateCode() const {return m_GenerateCode;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	const wxString& GetOutputFile() const {return m_OutputFile;}
	const wxString& GetAlgorithm() const {return m_Algorithm;}
	const wxString& GetGenerator() const {return m_Generator;}
	
protected:
	// protected data members
	bool m_GenerateCode;
	wxString m_Name;
	wxString m_Description;
	wxString m_OutputFile;
	wxString m_Generator;
	wxString m_Algorithm;
	
	udDiagramItem *m_pDiagram;
	udLanguage *m_pLanguage;
	
	// protected virtual functions
	virtual void OnInit( wxInitDialogEvent& event );
	virtual void OnNameChange( wxCommandEvent& event );
	virtual void OnMakeValid( wxCommandEvent& event );
	virtual void OnGeneratorChange( wxCommandEvent& event );
	virtual void OnOk( wxCommandEvent& event );
	virtual void OnReset(wxCommandEvent& event);
	
	void OnDelayedNameUpdate(wxCommandEvent& event);

};
#endif // __diagramdialog__
