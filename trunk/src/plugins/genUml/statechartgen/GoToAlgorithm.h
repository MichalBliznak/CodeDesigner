#ifndef UDGOTOALGORITHM_H
#define UDGOTOALGORITHM_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udGOTOAlgorithm : public udAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udGOTOAlgorithm);

    udGOTOAlgorithm();
    udGOTOAlgorithm(udGenerator *parent);
    virtual ~udGOTOAlgorithm();

    // public functions
    virtual void ProcessAlgorithm(udDiagramItem *src);

protected:
    // protected functions
    virtual bool Initialize();
    void ProcessState(wxSFShapeBase *state);
};

#endif // UDGOTOALGORITHM_H
