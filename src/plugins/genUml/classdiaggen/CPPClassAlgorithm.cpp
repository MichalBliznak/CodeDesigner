#include "ClassDiagramGenerator.h"
#include "CPPClassAlgorithm.h"
#include "CPPElementProcessors.h"

IMPLEMENT_DYNAMIC_CLASS(udCPPClassAlgorithm, udClassAlgorithm);

udCPPClassAlgorithm::udCPPClassAlgorithm()
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor();
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor();
	m_mapElementProcessors[wxT("umlTemplateBindItem")] = new udTemplBindElementProcessor();
	m_mapElementProcessors[wxT("umlEnumItem")] = new udEnumElementProcessor();
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udIncludeAssocProcessor();

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::udCPPClassAlgorithm(udGenerator *parent) : udClassAlgorithm(parent)
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlTemplateBindItem")] = new udTemplBindElementProcessor(parent);
	m_mapElementProcessors[wxT("umlEnumItem")] = new udEnumElementProcessor(parent);
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udIncludeAssocProcessor(parent);

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::~udCPPClassAlgorithm()
{
}