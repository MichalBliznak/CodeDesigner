#ifndef UDLOOPCASEALGORITHM_H
#define UDLOOPCASEALGORITHM_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udLoopCaseAlgorithm : public udAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udLoopCaseAlgorithm);

    udLoopCaseAlgorithm();
    udLoopCaseAlgorithm(udGenerator *parent);
    virtual ~udLoopCaseAlgorithm();

    // public functions
    virtual void ProcessAlgorithm(udDiagramItem *src);

protected:
    // protected functions
    virtual bool Initialize();
    void ProcessState(wxSFShapeBase *state);	
};

#endif // UDLOOPCASEALGORITHM_H
