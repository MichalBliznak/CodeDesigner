#ifndef UDELIFEALGORITHM_H
#define UDELIFEALGORITHM_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udElifAlgorithm : public udAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udElifAlgorithm);

    udElifAlgorithm();
    udElifAlgorithm(udGenerator *parent);
    virtual ~udElifAlgorithm();

protected:
    // protected functions
    void ProcessState(wxSFShapeBase *state);

    // public virtual functions
    virtual bool Initialize();
    virtual void ProcessAlgorithm(udDiagramItem *src);
};

#endif // UDELIFEALGORITHM_H
