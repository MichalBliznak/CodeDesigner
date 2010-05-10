#include "SStateChartGenerator.h"
#include "LoopCaseAlgorithm.h"
#include "ElifAlgorithm.h"
#include "GoToAlgorithm.h"
#include "../GenUml.h"

IMPLEMENT_DYNAMIC_CLASS(udSStateChartGenerator, udStateChartGenerator);

udSStateChartGenerator::udSStateChartGenerator()
{
    m_sName = udnSIMPLE_STATECHART_GEN;
    m_sDescription = wxT("");

    m_mapAlgorithms[wxT("udLoopCaseAlgorithm")] = new udLoopCaseAlgorithm(this);
    m_mapAlgorithms[wxT("udElifAlgorithm")] = new udElifAlgorithm(this);
    m_mapAlgorithms[wxT("udGOTOAlgorithm")] = new udGOTOAlgorithm(this);
}

udSStateChartGenerator::~udSStateChartGenerator()
{
}


