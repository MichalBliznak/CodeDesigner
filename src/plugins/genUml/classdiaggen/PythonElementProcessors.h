#ifndef UDPYTHONCLASSELEMENTPROCESSORS_H
#define UDPYTHONCLASSELEMENTPROCESSORS_H

#include "projectbase/ProjectBase.h"

/////////////////////////////////////////////////////////////////////////////////////
// udPythonClassElementProcessor class //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udPythonClassElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udPythonClassElementProcessor);

    udPythonClassElementProcessor();
    udPythonClassElementProcessor(udGenerator *parent);
    virtual ~udPythonClassElementProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
	
protected:
	// protected functions
	void ProcessClassDefinition(wxSFShapeBase *element);
};

#endif // UDPYTHONCLASSELEMENTPROCESSORS_H
