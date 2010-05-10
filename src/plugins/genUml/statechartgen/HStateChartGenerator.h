#ifndef UDHSTATECHARTGENERATOR_H
#define UDHSTATECHARTGENERATOR_H

#include "StateChartGenerator.h"

class WXDLLIMPEXP_CD udHStateChartGenerator : public udStateChartGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udHStateChartGenerator);

    udHStateChartGenerator();
    virtual ~udHStateChartGenerator();

protected:

    // protected virtual functions
    virtual bool Initialize();
    virtual void CleanUp();
};

#endif // UDSSTATECHARTGENERATOR_H
