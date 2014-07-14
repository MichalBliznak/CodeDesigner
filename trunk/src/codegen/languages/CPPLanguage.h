#ifndef UDCPPLANGUAGE_H
#define UDCPPLANGUAGE_H

#include "codegen/languages/CLanguage.h"

class udCPPLanguage : public udCLanguage
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPLanguage);

    udCPPLanguage();
    virtual ~udCPPLanguage();

    // public virtual functions
    virtual wxString True() const {return wxT("true");}
    virtual wxString False() const {return wxT("false");}
	
	virtual wxString ImplExt(){return wxT(".cpp");}
	virtual wxString DeclExt(){return wxT(".h");}
	
	virtual void ClassDeclCmd(const wxString& name, const wxString& parents);
	virtual void ClassConstructorDeclCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams);
	virtual void ClassConstructorDefCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams);
	virtual void ClassDestructorDeclCmd(const wxString& modif, const wxString& name, const wxString& parent);
	virtual void ClassDestructorDefCmd(const wxString& modif, const wxString& name, const wxString& parent);
	virtual void ClassMemberFcnDeclCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params);
	virtual void ClassMemberFcnDefCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params);
	virtual void ClassInstanceCmd(const wxString& instname, const wxString& classname, const wxString& params, bool dynamic);
};

#endif // UDCPPLANGUAGE_H
