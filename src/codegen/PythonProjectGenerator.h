#ifndef UDPYTHONPROJECTGENERATOR_H
#define UDPYTHONPROJECTGENERATOR_H

#include "codegen/base/ProjectGenerator.h"


class udPythonProjectGenerator : public udProjectGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udPythonProjectGenerator);

    udPythonProjectGenerator();
    virtual ~udPythonProjectGenerator();

protected:
    // protected virtual functions
    virtual void Initialize();
    virtual void ProcessProject(udProject *src);
    virtual void CleanUp();
};

#endif // UDPYTHONPROJECTGENERATOR_H
