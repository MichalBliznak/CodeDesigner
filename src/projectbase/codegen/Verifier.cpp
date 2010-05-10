#include "codegen/Verifier.h"
#include "codegen/Generator.h"
#include "../ProjectBase.h"

udVerifier::udVerifier()
{
	m_pGenerator = NULL;
}

udVerifier::udVerifier(udGenerator *gen)
{
	m_pGenerator = gen;
}

udVerifier::~udVerifier()
{
}

bool udVerifier::Verify(udDiagramItem *diagram)
{
    return true;
}

