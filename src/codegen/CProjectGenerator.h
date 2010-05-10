#ifndef UDCPROJECTGENERATOR_H
#define UDCPROJECTGENERATOR_H

#include "codegen/base/ProjectGenerator.h"


class udCProjectGenerator : public udProjectGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udCProjectGenerator);

    udCProjectGenerator();
    virtual ~udCProjectGenerator();

protected:
    // protected virtual functions
    virtual void Initialize();
    virtual void ProcessProject(udProject *src);
    virtual void CleanUp();
};



#endif // UDCPROJECTGENERATOR_H
