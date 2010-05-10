#ifndef UDSTATECHARTGENERATOR_H
#define UDSTATECHARTGENERATOR_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udStateChartGenerator : public udGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udStateChartGenerator);

    udStateChartGenerator();
    virtual ~udStateChartGenerator();

	// public functions
	void SortTransitions(ShapeList &transitions);

protected:
    // protected virtual functions
    virtual bool Initialize();
    virtual bool ProcessDiagram(udDiagramItem *src);
    virtual void CleanUp();
	
	// protected functions
	bool GenerateCommonDeclaration();
	bool GenerateCommonDefinition();
	bool GenerateDeclaration(udDiagramItem *src);
	bool GenerateDefinition(udDiagramItem *src);
	
	void GenerateIDs(udDiagramItem *src);
};



#endif // UDSTATECHARTGENERATOR_H
