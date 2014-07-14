#ifndef __udvariabledialog__
#define __udvariabledialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udVariableDialog : public _VariableDialog
{
public:
	//udVariableDialog(wxWindow *parent, udLanguage *lang, bool unique);
	udVariableDialog(wxWindow *parent, udVariableItem *var, udLanguage *lang);
	virtual ~udVariableDialog();
	
	// member data accessors
	void SetDescription(const wxString& Description) {this->m_Description = Description;}
	void SetCodeName(const wxString& Name) {this->m_Name = Name;}
	void SetDataType(const udLanguage::DATATYPE& DataType) {this->m_DataType = DataType;}
	void SetDataModifier(const udLanguage::DATAMODIFIER& Modifier) {this->m_DataModifier = Modifier;}
	void SetValueType(const udLanguage::VALUETYPE& ValueType) {this->m_ValueType = ValueType;}
	void SetDefaultValue(const wxString& DefaultValue) {this->m_DefaultValue = DefaultValue;}
	void SetUserDataType(const wxString& UserDataType) {this->m_UserDataType = UserDataType;}
	void SetUserDeclFile(const wxString& UserDeclFile) {this->m_UserDeclFile = UserDeclFile;}
	void SetUserDeclaration(const wxString& UserDeclaration) {this->m_UserDeclaration = UserDeclaration;}
	void SetUserDeclPlace(const udVariableItem::DECLLOCATION& DeclLocation) {this->m_UserDeclLocation = DeclLocation;}
	
	const wxString& GetDescription() const {return m_Description;}
	const wxString& GetCodeName() const {return m_Name;}
	const udLanguage::DATATYPE& GetDataType() const {return m_DataType;}
	const udLanguage::DATAMODIFIER& GetDataModifier() const {return m_DataModifier;}
	const udLanguage::VALUETYPE& GetValueType() const {return m_ValueType;}
	const wxString& GetDefaultValue() const {return m_DefaultValue;}
	const wxString& GetUserDataType() const {return m_UserDataType;}
	const wxString& GetUserDeclFile() const {return m_UserDeclFile;}
	const wxString& GetUserDeclaration() const {return m_UserDeclaration;}
	const udVariableItem::DECLLOCATION& GetUserDeclPlace() const {return m_UserDeclLocation;}
	
protected:
	// protected data members
	wxString m_Name;
	wxString m_Description;
	udLanguage::DATATYPE m_DataType;
	udLanguage::DATAMODIFIER m_DataModifier;
	udLanguage::VALUETYPE m_ValueType;
	udVariableItem::DECLLOCATION m_UserDeclLocation;
	wxString m_DefaultValue;
	wxString m_UserDataType;
	wxString m_UserDeclaration;
	wxString m_UserDeclFile;
	
	udLanguage *m_pLang;
	//bool m_fUnique;
	udVariableItem *m_pVarItem;
	
	// protected virtual functions
	virtual void OnInit(wxInitDialogEvent &event);
	virtual void OnNameChange(wxCommandEvent &event);
	virtual void OnMakeValid( wxCommandEvent &event );
	virtual void OnOk( wxCommandEvent& event );
	virtual void OnUpdateUserDataType( wxUpdateUIEvent& event );
	virtual void OnUpdateDefinitionFile( wxUpdateUIEvent& event );
	virtual void OnUpdateEditor( wxUpdateUIEvent& event );
};

#endif // __udvariabledialog__
