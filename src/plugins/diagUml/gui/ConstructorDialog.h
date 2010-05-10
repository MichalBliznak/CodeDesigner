#ifndef __udconstructordialog__
#define __udconstructordialog__

#include "GUI.h"
#include "projectbase/codegen/Language.h"
#include "projectbase/ProjectBase.h"
#include "../DiagUml.h"

class udConstructorDialog : public _ConstructorDialog
{

public:
	udConstructorDialog(wxWindow *parent, udConstructorFunctionItem *item, udLanguage *lang);
	virtual ~udConstructorDialog();
	
	// member data accessors
	void SetCode(const wxString& Code) {this->m_Code = Code;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetFcnModifier(const udLanguage::FCNMODIFIER& FcnModifier) {this->m_FcnModifier = FcnModifier;}
	void SetImplementation(const wxString& Implementation) {this->m_Implementation = Implementation;}
	
	const wxString& GetImplementation() const {return m_Implementation;}
	const wxString& GetCode() const {return m_Code;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	const udLanguage::FCNMODIFIER& GetFcnModifier() const {return m_FcnModifier;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_Code;
	wxString m_Implementation;
	udLanguage::FCNMODIFIER m_FcnModifier;
	
	udLanguage *m_pLang;
	udConstructorFunctionItem *m_pFcnItem;
	//udFunctionItem *m_pOrigFcnItem;
	
	udFunctionItem *m_pBackUp;
	StringMap m_mapUsedCons;
	StringMap m_mapConsParams;
	
	wxString m_sSelectedBaseClass;
	
	// protected functions
	void UpdateParameters();
	void UpdateConstructors(const wxString& baseclass);
	void UpdateConsParameters(const wxString& cons);
	bool EditParameter(udVariableItem *param);
	udVariableItem* GetSelectedParameter();
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
	virtual void OnCancel( wxCommandEvent& event );
	virtual void OnAddClick( wxCommandEvent& event );
	virtual void OnEditClick( wxCommandEvent& event );
	virtual void OnRemoveClick( wxCommandEvent& event );
	virtual void OnMoveUpClick( wxCommandEvent& event );
	virtual void OnMoveDownClick( wxCommandEvent& event );
	virtual void OnParamActivated( wxListEvent& event );
	virtual void OnUpdateParamButtons( wxUpdateUIEvent& event );
	virtual void OnBaseClassSelected( wxCommandEvent& event );
	virtual void OnBaseConstructorChange( wxCommandEvent& event );
	
	// protected event handlers
	void OnPropertyGridChange( wxPropertyGridEvent& event );
	
	DECLARE_EVENT_TABLE();
};

#endif // __udconstructordialog__
