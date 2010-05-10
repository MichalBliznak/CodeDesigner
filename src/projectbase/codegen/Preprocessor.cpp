#include "codegen/Preprocessor.h"
#include "codegen/Generator.h"
#include "../ProjectBase.h"

udPreprocessor::udPreprocessor()
{
	m_pGenerator = NULL;
	m_pPreprocessedDiagram = NULL;

}
udPreprocessor::udPreprocessor(udGenerator *gen)
{
	m_pGenerator = gen;
	m_pPreprocessedDiagram = NULL;
}

udPreprocessor::~udPreprocessor()
{
}

udDiagramItem* udPreprocessor::Process(udDiagramItem *src)
{
    return src;
}


