#ifndef STATECHARTELEMENTPROCESSOR_H
#define STATECHARTELEMENTPROCESSOR_H

/////////////////////////////////////////////////////////////////////////////////////
// udStateChartElementProcessor class ///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udStateChartElementProcessor : public udElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udStateChartElementProcessor);

    udStateChartElementProcessor();
    udStateChartElementProcessor(udGenerator *parent);
    virtual ~udStateChartElementProcessor();

protected:
	// protected functions
	static wxSFLineShape* GetConditionlessPath(wxSFShapeBase *element);
};

#endif // STATECHARTELEMENTPROCESSOR_H
