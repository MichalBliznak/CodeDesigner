#ifndef UDHSTATECHARTPREPROCESSOR_H
#define UDHSTATECHARTPREPROCESSOR_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udHStateChartPreprocessor : public udPreprocessor
{
public:
    DECLARE_DYNAMIC_CLASS(udHStateChartPreprocessor);

    udHStateChartPreprocessor();
	udHStateChartPreprocessor(udGenerator *gen);
    virtual ~udHStateChartPreprocessor();

    // public virtual functions
    virtual udDiagramItem* Process(udDiagramItem *src);
	
protected:

	void ReconnectInputs(udDiagramItem *diag);
	void ReconnectOutputs(udDiagramItem *diag);
	void AssignStateActions(udDiagramItem *diag);
	void SortStateActions(udDiagramItem *diag);
	
};

#endif // UDHSTATECHARTPREPROCESSOR_H
