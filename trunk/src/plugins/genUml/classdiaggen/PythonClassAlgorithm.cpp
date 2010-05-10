#include "ClassDiagramGenerator.h"
#include "PythonClassAlgorithm.h"
#include "PythonElementProcessors.h"

IMPLEMENT_DYNAMIC_CLASS(udPythonClassAlgorithm, udClassAlgorithm);

udPythonClassAlgorithm::udPythonClassAlgorithm()
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udPythonClassElementProcessor();

    m_sName = wxT("Python class algorithm");

    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udPythonClassAlgorithm::udPythonClassAlgorithm(udGenerator *parent) : udClassAlgorithm(parent)
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udPythonClassElementProcessor(parent);

    m_sName = wxT("Python class algorithm");

    m_arrSuppLanguages.Add(wxT("udPythonLanguage"));
}

udPythonClassAlgorithm::~udPythonClassAlgorithm()
{
}
