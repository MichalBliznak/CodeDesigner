#include "HStateChartGenerator.h"
#include "HStateChartPreprocessor.h"
#include "LoopCaseAlgorithm.h"
#include "ElifAlgorithm.h"
#include "GoToAlgorithm.h"
#include "../GenUml.h"

IMPLEMENT_DYNAMIC_CLASS(udHStateChartGenerator, udStateChartGenerator);

udHStateChartGenerator::udHStateChartGenerator()
{
    m_sName = udnHIERARCHICAL_STATE_CHART_GEN;
    m_sDescription = wxT("");

    m_mapAlgorithms[wxT("udLoopCaseAlgorithm")] = new udLoopCaseAlgorithm(this);
	m_mapAlgorithms[wxT("udElifAlgorithm")] = new udElifAlgorithm(this);
	m_mapAlgorithms[wxT("udGOTOAlgorithm")] = new udGOTOAlgorithm(this);
}

udHStateChartGenerator::~udHStateChartGenerator()
{
}

bool udHStateChartGenerator::Initialize()
{
	// initialize preprocesor
	m_pPreprocessor = new udHStateChartPreprocessor(this);

    return udStateChartGenerator::Initialize();
}

void udHStateChartGenerator::CleanUp()
{
	delete m_pPreprocessor;

	udStateChartGenerator::CleanUp();
}


