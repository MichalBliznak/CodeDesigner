#ifndef UDCPPCLASSELEMENTPROCESSORS_H
#define UDCPPCLASSELEMENTPROCESSORS_H

#include "projectbase/ProjectBase.h"

/////////////////////////////////////////////////////////////////////////////////////
// udCPPClassElementProcessor class /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udCPPClassElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPClassElementProcessor);

    udCPPClassElementProcessor();
    udCPPClassElementProcessor(udGenerator *parent);
    virtual ~udCPPClassElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
	
protected:
	// protected functions
	void ProcessClassDeclaration(wxSFShapeBase *element);
	void ProcessClassDefinition(wxSFShapeBase *element);
	void ProcessClassMembers(wxSFShapeBase *element);
};

class WXDLLIMPEXP_CD udCPPTemplBindElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPTemplBindElementProcessor);

    udCPPTemplBindElementProcessor();
    udCPPTemplBindElementProcessor(udGenerator *parent);
    virtual ~udCPPTemplBindElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

class WXDLLIMPEXP_CD udCPPEnumElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPEnumElementProcessor);

    udCPPEnumElementProcessor();
    udCPPEnumElementProcessor(udGenerator *parent);
    virtual ~udCPPEnumElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

class WXDLLIMPEXP_CD udCPPIncludeAssocProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPIncludeAssocProcessor);

    udCPPIncludeAssocProcessor();
    udCPPIncludeAssocProcessor(udGenerator *parent);
    virtual ~udCPPIncludeAssocProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

#endif // UDCPPCLASSELEMENTPROCESSORS_H
