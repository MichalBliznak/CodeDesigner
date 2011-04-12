#ifndef __udfunctiondialog__
#define __udfunctiondialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udFunctionDialog : public _FunctionDialog
{

public:
	udFunctionDialog(wxWindow *parent, udFunctionItem *item, udLanguage *lang);
	virtual ~udFunctionDialog();
	
	// member data accessors
	void SetCode(const wxString& Code) {this->m_Code = Code;}
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetDataType(const udLanguage::DATATYPE& DataType) {this->m_DataType = DataType;}
	void SetDataModifier(const udLanguage::DATAMODIFIER& Modifier) {this->m_DataModifier = Modifier;}
	void SetValueType(const udLanguage::VALUETYPE& ValueType) {this->m_ValueType = ValueType;}
	void SetUserDataType(const wxString& UserDataType) {this->m_UserDataType = UserDataType;}
	void SetUserDeclFile(const wxString& UserDeclFile) {this->m_UserDeclFile = UserDeclFile;}
	void SetUserDeclaration(const wxString& UserDeclaration) {this->m_UserDeclaration = UserDeclaration;}
	void SetUserDeclPlace(const udVariableItem::DECLLOCATION& DeclLocation) {this->m_UserDeclLocation = DeclLocation;}
	void SetFcnModifier(const udLanguage::FCNMODIFIER& FcnModifier) {this->m_FcnModifier = FcnModifier;}
	void SetInline(const bool& Inline) {this->m_Inline = Inline;}
	void SetImplementation(const wxString& Implementation) {this->m_Implementation = Implementation;}
	
	const wxString& GetImplementation() const {return m_Implementation;}
	const wxString& GetCode() const {return m_Code;}
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	const udLanguage::DATATYPE& GetDataType() const {return m_DataType;}
	const udLanguage::DATAMODIFIER& GetDataModifier() const {return m_DataModifier;}
	const udLanguage::VALUETYPE& GetValueType() const {return m_ValueType;}
	const wxString& GetUserDataType() const {return m_UserDataType;}
	const wxString& GetUserDeclFile() const {return m_UserDeclFile;}
	const wxString& GetUserDeclaration() const {return m_UserDeclaration;}
	const udVariableItem::DECLLOCATION& GetUserDeclPlace() const {return m_UserDeclLocation;}
	const udLanguage::FCNMODIFIER& GetFcnModifier() const {return m_FcnModifier;}
	const bool& GetInline() const {return m_Inline;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	wxString m_Code;
	wxString m_UserDataType;
	wxString m_UserDeclaration;
	wxString m_UserDeclFile;
	wxString m_Implementation;
	udLanguage::DATATYPE m_DataType;
	udLanguage::DATAMODIFIER m_DataModifier;
	udLanguage::FCNMODIFIER m_FcnModifier;
	udLanguage::VALUETYPE m_ValueType;
	udVariableItem::DECLLOCATION m_UserDeclLocation;
	bool m_Inline;
	
	udLanguage *m_pLang;
	udFunctionItem *m_pFcnItem;
	udFunctionItem *m_pOrigFcnItem;
	
	udFunctionItem *m_pBackUp;
	
	// protected functions
	void UpdateParameters();
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
	virtual void OnUpdateUserDataType( wxUpdateUIEvent& event );
	virtual void OnUpdateDefinitionFile( wxUpdateUIEvent& event );
	virtual void OnUpdateEditor( wxUpdateUIEvent& event );
	virtual void OnEditorChoice( wxCommandEvent& event );
	virtual void OnEditorKillFocus( wxFocusEvent& event );

};

#endif // __udfunctiondialog__
