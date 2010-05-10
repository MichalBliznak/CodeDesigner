#ifndef UDPYTHONCLASSALGORITHM_H
#define UDPYTHONCLASSALGORITHM_H

#include "ClassAlgorithm.h"

class WXDLLIMPEXP_CD udPythonClassAlgorithm : public udClassAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udPythonClassAlgorithm);

    udPythonClassAlgorithm();
    udPythonClassAlgorithm(udGenerator *parent);
    virtual ~udPythonClassAlgorithm();
};

#endif // UDPYTHONCLASSALGORITHM_H
