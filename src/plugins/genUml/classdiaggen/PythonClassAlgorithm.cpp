#include "ClassDiagramGenerator.h"
#include "PythonClassAlgorithm.h"
#include "PythonElementProcessors.h"

IMPLEMENT_DYNAMIC_CLASS(udPythonClassAlgorithm, udClassAlgorithm);

udPythonClassAlgorithm::udPythonClassAlgorithm()
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udPyClassElementProcessor();
	m_mapElementProcessors[wxT("umlEnumItem")] = new udPyEnumElementProcessor();
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udPyIncludeAssocProcessor();
	m_mapElementProcessors[wxT("umlBasicAggregItem")] = new udPyIncludeAssocProcessor();
	m_mapElementProcessors[wxT("umlCompAggregItem")] = new udPyIncludeAssocProcessor();

    m_sName = wxT("Python class algorithm");

    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udPythonClassAlgorithm::udPythonClassAlgorithm(udGenerator *parent) : udClassAlgorithm(parent)
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udPyClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlEnumItem")] = new udPyEnumElementProcessor(parent);
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udPyIncludeAssocProcessor(parent);
	m_mapElementProcessors[wxT("umlBasicAggregItem")] = new udPyIncludeAssocProcessor(parent);
	m_mapElementProcessors[wxT("umlCompAggregItem")] = new udPyIncludeAssocProcessor(parent);

    m_sName = wxT("Python class algorithm");

    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udPythonClassAlgorithm::~udPythonClassAlgorithm()
{
}
