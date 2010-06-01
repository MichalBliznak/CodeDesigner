#include "ClassDiagramGenerator.h"
#include "CPPClassAlgorithm.h"
#include "CPPElementProcessors.h"

IMPLEMENT_DYNAMIC_CLASS(udCPPClassAlgorithm, udClassAlgorithm);

udCPPClassAlgorithm::udCPPClassAlgorithm()
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor();
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor();

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::udCPPClassAlgorithm(udGenerator *parent) : udClassAlgorithm(parent)
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor(parent);

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::~udCPPClassAlgorithm()
{
}
