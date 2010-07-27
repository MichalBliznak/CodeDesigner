#ifndef UDCLANGUAGE_H
#define UDCLANGUAGE_H

#include "projectbase/codegen/Language.h"

class udCLanguage : public udLanguage
{
public:
    DECLARE_DYNAMIC_CLASS(udCLanguage);

    udCLanguage();
    virtual ~udCLanguage();

    // public virtual functions
    virtual wxString MakeValidIdentifier(const wxString& name);

    virtual wxString NullValue(){return wxT("0");}
    virtual wxString NullPointer(){return wxT("NULL");}
    virtual wxString True(){return wxT("1");}
    virtual wxString False(){return wxT("0");}
	virtual wxString Delimiter(){return wxT(";");}
	virtual wxString Dummy(){return wxT("// dummy code");}
	virtual wxString ImplExt(){return wxT(".c");}
	virtual wxString DeclExt(){return wxT(".h");}

    virtual wxString And(){return wxT("&&");}
    virtual wxString Or(){return wxT("||");}
    virtual wxString Not(){return wxT("!");}
    virtual wxString Equal(){return wxT("==");}
    virtual wxString NotEqual(){return wxT("!=");}
    virtual wxString Less(){return wxT("<");}
    virtual wxString More(){return wxT(">");}

    virtual wxString GetCommented(const wxString& txt);
	
	virtual void IncludeCmd(const wxString& header);
	virtual void DefineCmd(const wxString& macro, const wxString& content);
	virtual void TypedefCmd(const wxString& type, const wxString& decl);
	
    virtual void BeginCmd();
    virtual void EndCmd();

    virtual void VariableDeclCmd(const wxString& type, const wxString &name);
    virtual void VariableDeclAssignCmd(const wxString& type, const wxString &name, const wxString& value);
    virtual void VariableAssignCmd(const wxString& name, const wxString &value);

    virtual void FunctionDeclCmd(const wxString& rettype, const wxString& name, const wxString& args);
    virtual void FunctionDefCmd(const wxString& rettype, const wxString& name, const wxString& args);
    virtual void FunctionCallCmd(const wxString& name, const wxString& args );

    virtual void IfCmd(const wxString& cond);
    virtual void ElseIfCmd(const wxString& cond);
    virtual void ElseCmd();
    virtual void SwitchCmd(const wxString& cond);
    virtual void CaseCmd(const wxString& id);

    virtual void ForCmd(const wxString& init, const wxString& cond, const wxString& action);
    virtual void DoCmd(const wxString& cond);
    virtual void WhileCmd(const wxString& cond);
    virtual void InfiniteLoopCmd();
    virtual void BreakCmd();
    virtual void ContinueCmd();
    virtual void ReturnCmd(const wxString& val);

    virtual void GotoCmd(const wxString& label);
    virtual void LabelCmd(const wxString& name);

    virtual void SingleLineCommentCmd(const wxString& msg);
    virtual void MultiLineCommentCmd(const wxString& msg);
	
	virtual void EnumCmd(const wxString& name, const wxArrayString& values, const wxString& instname);
};

#endif // UDCLANGUAGE_H
