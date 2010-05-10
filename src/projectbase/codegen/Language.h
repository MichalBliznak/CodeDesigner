#ifndef UDLANGUAGE_H
#define UDLANGUAGE_H

#include <wx/hashmap.h>
#include <wx/dynarray.h>
#include <wx/wxScintilla/wxscintilla.h>

#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD udValueType : public wxObject
{
public:
	udValueType() {;}
	udValueType(const wxString& name, const wxString& sign) : m_sName(name), m_sSign(sign) {;}
	udValueType(const udValueType& obj) : m_sName(obj.m_sName), m_sSign(obj.m_sSign) {;}
	
	inline const wxString& Name() const {return m_sName;}
	inline const wxString& Sign() const {return m_sSign;}
	
protected:
	wxString m_sName;
	wxString m_sSign;
};

WX_DECLARE_OBJARRAY_WITH_DECL(udValueType, ValueTypeArray, class WXDLLIMPEXP_CD);

class WXDLLIMPEXP_CD udLanguage : public wxObject
{
public:
    udLanguage();
    virtual ~udLanguage();

    enum DATATYPE
    {
		DT_USERDEFINED = 0,
        DT_BOOL,
        DT_UINT8,
        DT_UINT16,
        DT_UINT32,
        DT_INT,
        DT_LONG,
        DT_REAL,
        DT_BIG_REAL,
        DT_CHAR,
        DT_VOID
    };
	
	enum VALUETYPE
	{
		VT_VALUE = 0,
		VT_POINTER,
		VT_REFERENCE
	};

    enum DATAMODIFIER
    {
		DM_NONE = 0,
        DM_SHORT,
        DM_LONG,
        DM_SIGNED,
        DM_UNSIGNED,
        DM_STATIC,
        DM_CONST,
        DM_EXTERN,
        DM_VOLATILE
    };
	
	enum FCNMODIFIER
	{
		FM_NONE = 0,
		FM_STATIC,
		FM_VIRTUAL,
		FM_ABSTRACT,
		FM_CONST
	};
	
	enum ACCESSTYPE
	{
		AT_PUBLIC = 0,
		AT_PROTECTED,
		AT_PRIVATE
	};
	
	enum FILEEXTENSION
	{
		FE_DECL = 0,
		FE_IMPL
	};

	// public functions
	udLanguage* Clone() { return (udLanguage*)wxCreateDynamicObject( this->GetClassInfo()->GetClassName() ); }
	
    // public member data accessors
    void SetIndentation(int depth){m_nIndentation = depth;}
    void SetIndentString(const wxString& str){m_sIndentStr = str;}
    void SetNewLineString(const wxString& nl){m_sNewLineStr = nl;}
    void SetName(const wxString& name){m_sName = name;}
    void SetDescription(const wxString& desc){m_sDescription = desc;}

    int GetIndentation() const {return m_nIndentation;}
    long GetStcLanguageType() const {return m_nStcLangType;}
    const wxString& GetStcLanguageKeywords() const {return m_sStcLangKeywords;}
    const wxString& GetIndentString() const {return m_sIndentStr;}
    const wxString& GetNewLineString() const {return m_sNewLineStr;}
    const wxString& GetName() const {return m_sName;}
    const wxString& GetDescription() const {return m_sDescription;}

    wxString GetDataTypeString(DATATYPE dt) const;
    wxString GetModifierString(DATAMODIFIER modif) const;
    wxString GetModifierString(FCNMODIFIER modif) const;
    wxString GetAccessTypeString(ACCESSTYPE at) const;
    udValueType GetValueType(VALUETYPE vt) const;
	wxString GetExtension(FILEEXTENSION fe) const;
	
	bool HasUserDataType() const {return m_fHasUserDataType;}
	bool HasSeparatedDecl() const {return m_fHasSeparatedDecl;}
	
    // public functions
    void ClearCodeBuffer() {m_sOutBuffer = wxT("");}
    wxString GetCodeBuffer() {return m_sOutBuffer;}
	
	void PushCode();
	void PopCode();

    void Indent();
    void IncIndentation(){m_nIndentation++;}
    void DecIndentation(){m_nIndentation--; if(m_nIndentation < 0)m_nIndentation = 0;}
    void NewLine();

	void WriteCodeBlocks(const wxString& code);

    // public virtual functions
    virtual wxString MakeValidIdentifier(const wxString& name){return name;}

    virtual wxString NullValue(){return wxT("");}
    virtual wxString NullPointer(){return wxT("");}
    virtual wxString True(){return wxT("");}
    virtual wxString False(){return wxT("");}
    virtual wxString Delimiter(){return wxT("");}
    virtual wxString This(){return wxT("");}
	virtual wxString Dummy(){return wxT("");}

    virtual wxString And(){return wxT("");}
    virtual wxString Or(){return wxT("");}
    virtual wxString Not(){return wxT("");}
    virtual wxString Equal(){return wxT("");}
    virtual wxString NotEqual(){return wxT("");}
    virtual wxString Less(){return wxT("");}
    virtual wxString More(){return wxT("");}

    virtual wxString GetCommented(const wxString& txt){return wxT("");}

	virtual void IncludeCmd(const wxString& header){;}
	virtual void DefineCmd(const wxString& macro, const wxString& content){;}
	virtual void TypedefCmd(const wxString& type, const wxString& decl){;}
	
    virtual void BeginCmd(){;}
    virtual void EndCmd(){;}

    virtual void VariableDeclCmd(const wxString& type, const wxString &name){;}
    virtual void VariableDeclAssignCmd(const wxString& type, const wxString &name, const wxString& value){;}
    virtual void VariableAssignCmd(const wxString& name, const wxString &value){;}

    virtual void FunctionDeclCmd(const wxString& rettype, const wxString& name, const wxString& args){;}
	virtual void FunctionDefCmd(const wxString& rettype, const wxString& name, const wxString& args){;}
    virtual void FunctionCallCmd(const wxString& name, const wxString& args ){;}

    virtual void IfCmd(const wxString& cond){;}
    virtual void ElseIfCmd(const wxString& cond){;}
    virtual void ElseCmd(){;}
    virtual void SwitchCmd(const wxString& cond){;}
    virtual void CaseCmd(const wxString& id){;}

    virtual void ForCmd(const wxString& init, const wxString& cond, const wxString& action){;}
    virtual void DoCmd(const wxString& cond){;}
    virtual void WhileCmd(const wxString& cond){;}
    virtual void InfiniteLoopCmd(){;}
    virtual void BreakCmd(){;}
    virtual void ContinueCmd(){;}
    virtual void ReturnCmd(const wxString& val){;}

    virtual void GotoCmd(const wxString& label){;}
    virtual void LabelCmd(const wxString& name){;}

    virtual void SingleLineCommentCmd(const wxString& msg){;}
    virtual void MultiLineCommentCmd(const wxString& msg){;}
	
	virtual void ClassDeclCmd(const wxString& name, const wxString& parents){;}
	virtual void ClassDefCmd(const wxString& name, const wxString& parents){;}
	virtual void ClassConstructorDeclCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams){;}
	virtual void ClassConstructorDefCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams){;}
	virtual void ClassDestructorDeclCmd(const wxString& modif, const wxString& name, const wxString& parent){;}
	virtual void ClassDestructorDefCmd(const wxString& modif, const wxString& name, const wxString& parent){;}
	virtual void ClassMemberFcnDeclCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params){;}
	virtual void ClassMemberFcnDefCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params){;}
	

protected:
    // protected data members
    int m_nIndentation;

    long m_nStcLangType;
    wxString m_sStcLangKeywords;

    wxString m_sOutBuffer;
    wxString m_sIndentStr;
    wxString m_sNewLineStr;

    wxArrayString m_arrDataTypes;
    wxArrayString m_arrDataModifiers;
    wxArrayString m_arrFcnModifiers;
    wxArrayString m_arrAccessTypes;
    wxArrayString m_arrFileExtensions;
	ValueTypeArray m_arrValueTypes;

    wxString m_sName;
    wxString m_sDescription;
	
	wxArrayString m_arrCodeBuffer;
	int m_nCodeBufferIndex;
	
	bool m_fHasUserDataType;
	bool m_fHasSeparatedDecl;
};

WX_DECLARE_HASH_MAP( wxString, udLanguage*, wxStringHash, wxStringEqual, LanguageMap );

#endif // UDLANGUAGE_H
