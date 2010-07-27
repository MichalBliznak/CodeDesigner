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

class WXDLLIMPEXP_CD udTemplBindElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udTemplBindElementProcessor);

    udTemplBindElementProcessor();
    udTemplBindElementProcessor(udGenerator *parent);
    virtual ~udTemplBindElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

class WXDLLIMPEXP_CD udEnumElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udEnumElementProcessor);

    udEnumElementProcessor();
    udEnumElementProcessor(udGenerator *parent);
    virtual ~udEnumElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

#endif // UDCPPCLASSELEMENTPROCESSORS_H
