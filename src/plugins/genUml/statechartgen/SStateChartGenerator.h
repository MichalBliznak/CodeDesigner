#ifndef UDSSTATECHARTGENERATOR_H
#define UDSSTATECHARTGENERATOR_H

#include "StateChartGenerator.h"

class WXDLLIMPEXP_CD udSStateChartGenerator : public udStateChartGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udSStateChartGenerator);

    udSStateChartGenerator();
    virtual ~udSStateChartGenerator();
};

#endif // UDSSTATECHARTGENERATOR_H
