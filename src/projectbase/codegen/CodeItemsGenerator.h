#ifndef UDSTATECHARTGENERATOR_H
#define UDSTATECHARTGENERATOR_H

#include "interfaces/Defs.h"
#include "Generator.h"

class WXDLLIMPEXP_CD udCodeItemsGenerator : public udGenerator
{
public:
    udCodeItemsGenerator();
    virtual ~udCodeItemsGenerator();

protected:
    // protected virtual functions
    virtual bool Initialize();
    virtual bool ProcessDiagram(udDiagramItem *src);
    virtual void CleanUp();
	
	// protected functions
	bool GenerateCommonDeclaration();
	bool GenerateCommonDefinition();
};



#endif // UDSTATECHARTGENERATOR_H
