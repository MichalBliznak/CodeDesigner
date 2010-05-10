#ifndef UDLCEITRANSITIONPROCESSOR_H
#define UDLCEITRANSITIONPROCESSOR_H

#include "StateChartElementProcessor.h"

class WXDLLIMPEXP_CD udLCEITransitionProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCEITransitionProcessor);

    udLCEITransitionProcessor();
    udLCEITransitionProcessor(udGenerator *parent);
    virtual ~udLCEITransitionProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

#endif // UDLCEITRANSITIONPROCESSOR_H
