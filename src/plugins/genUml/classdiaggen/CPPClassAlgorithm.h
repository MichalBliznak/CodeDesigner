#ifndef UDCPPCLASSALGORITHM_H
#define UDCPPCLASSALGORITHM_H

#include "ClassAlgorithm.h"

class WXDLLIMPEXP_CD udCPPClassAlgorithm : public udClassAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udCPPClassAlgorithm);

    udCPPClassAlgorithm();
    udCPPClassAlgorithm(udGenerator *parent);
    virtual ~udCPPClassAlgorithm();
};

#endif // UDCPPCLASSALGORITHM_H
