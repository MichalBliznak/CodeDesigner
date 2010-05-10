#include "codegen/ElementProcessor.h"
#include "codegen/Generator.h"

udElementProcessor::udElementProcessor()
{
    m_pParentGenerator = NULL;
}

udElementProcessor::udElementProcessor(udGenerator *parent)
{
    m_pParentGenerator = parent;
}

udElementProcessor::~udElementProcessor()
{
}

void udElementProcessor::ProcessElement(wxSFShapeBase *element)
{
}



