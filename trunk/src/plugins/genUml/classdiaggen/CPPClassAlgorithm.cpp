#include "ClassDiagramGenerator.h"
#include "CPPClassAlgorithm.h"
#include "CPPElementProcessors.h"

IMPLEMENT_DYNAMIC_CLASS(udCPPClassAlgorithm, udClassAlgorithm);

udCPPClassAlgorithm::udCPPClassAlgorithm()
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor();
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor();
	m_mapElementProcessors[wxT("umlTemplateBindItem")] = new udCPPTemplBindElementProcessor();
	m_mapElementProcessors[wxT("umlEnumItem")] = new udCPPEnumElementProcessor();
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udCPPIncludeAssocProcessor();
	m_mapElementProcessors[wxT("umlBasicAggregItem")] = new udCPPIncludeAssocProcessor();
	m_mapElementProcessors[wxT("umlCompAggregItem")] = new udCPPIncludeAssocProcessor();

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::udCPPClassAlgorithm(udGenerator *parent) : udClassAlgorithm(parent)
{
    // initialize element processors
	m_mapElementProcessors[wxT("umlClassItem")] = new udCPPClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlClassTemplateItem")] = new udCPPClassElementProcessor(parent);
	m_mapElementProcessors[wxT("umlTemplateBindItem")] = new udCPPTemplBindElementProcessor(parent);
	m_mapElementProcessors[wxT("umlEnumItem")] = new udCPPEnumElementProcessor(parent);
	m_mapElementProcessors[wxT("umlIncludeAssocItem")] = new udCPPIncludeAssocProcessor(parent);
	m_mapElementProcessors[wxT("umlBasicAggregItem")] = new udCPPIncludeAssocProcessor(parent);
	m_mapElementProcessors[wxT("umlCompAggregItem")] = new udCPPIncludeAssocProcessor(parent);

    m_sName = wxT("CPP class algorithm");

    m_arrSuppLanguages.Add(wxT("udCPPLanguage"));
}

udCPPClassAlgorithm::~udCPPClassAlgorithm()
{
}
