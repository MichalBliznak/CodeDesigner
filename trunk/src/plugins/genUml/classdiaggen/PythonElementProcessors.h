#ifndef UDPYTHONCLASSELEMENTPROCESSORS_H
#define UDPYTHONCLASSELEMENTPROCESSORS_H

#include "projectbase/ProjectBase.h"

/////////////////////////////////////////////////////////////////////////////////////
// udPyClassElementProcessor class //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udPyClassElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udPyClassElementProcessor);

    udPyClassElementProcessor();
    udPyClassElementProcessor(udGenerator *parent);
    virtual ~udPyClassElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
	
protected:
	// protected functions
	void ProcessClassDefinition(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udPyEnumElementProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udPyEnumElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udPyEnumElementProcessor);

    udPyEnumElementProcessor();
    udPyEnumElementProcessor(udGenerator *parent);
    virtual ~udPyEnumElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udPyIncludeAssocProcessor class //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udPyIncludeAssocProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udPyIncludeAssocProcessor);

    udPyIncludeAssocProcessor();
    udPyIncludeAssocProcessor(udGenerator *parent);
    virtual ~udPyIncludeAssocProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

#endif // UDPYTHONCLASSELEMENTPROCESSORS_H
