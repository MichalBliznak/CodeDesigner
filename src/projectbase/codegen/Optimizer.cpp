#include "codegen/Optimizer.h"
#include "codegen/Generator.h"
#include "../ProjectBase.h"

udOptimizer::udOptimizer()
{
	m_pGenerator = NULL;

}
udOptimizer::udOptimizer(udGenerator *gen)
{
	m_pGenerator = gen;
	m_nFlags = 0;
}

udOptimizer::~udOptimizer()
{
}

udDiagramItem* udOptimizer::Optimize(udDiagramItem *src)
{
    return src;
}
