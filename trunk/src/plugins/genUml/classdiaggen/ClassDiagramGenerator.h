#ifndef UDCLASSDIAGRAMGENERATOR_H
#define UDCLASSDIAGRAMGENERATOR_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udClassDiagramGenerator : public udGenerator
{
public:
    DECLARE_DYNAMIC_CLASS(udClassDiagramGenerator);

    udClassDiagramGenerator();
    virtual ~udClassDiagramGenerator();

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
};



#endif // UDCLASSDIAGRAMGENERATOR_H
