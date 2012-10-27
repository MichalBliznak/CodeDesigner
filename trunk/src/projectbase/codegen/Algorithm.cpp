#include "codegen/Algorithm.h"

udAlgorithm::udAlgorithm()
{
    m_pParentGenerator = NULL;
	m_pProcessedDiagram = NULL;
    m_pNextElement = NULL;
    m_pPrevElement = NULL;
}

udAlgorithm::udAlgorithm(udGenerator *parent)
{
    m_pParentGenerator = parent;
	m_pProcessedDiagram = NULL;
    m_pNextElement = NULL;
    m_pPrevElement = NULL;
}

udAlgorithm::~udAlgorithm()
{
    // free assigned element processors
    ProcessorMap::iterator it = m_mapElementProcessors.begin();
    while(it != m_mapElementProcessors.end())
    {
        delete it->second;
        it++;
    }
    m_mapElementProcessors.clear();
}

void udAlgorithm::SetParentGenerator(udGenerator *parent)
{
    m_pParentGenerator = parent;

    ProcessorMap::iterator it = m_mapElementProcessors.begin();
    while(it != m_mapElementProcessors.end())
    {
        it->second->SetParentGenerator(parent);
        it++;
    }
}

udElementProcessor* udAlgorithm::GetElementProcessor(const wxString& itemName)
{
    ProcessorMap::iterator it = m_mapElementProcessors.find(itemName);

    if( it != m_mapElementProcessors.end())
    {
        return m_mapElementProcessors[itemName];
    }
    else
        return NULL;
}

void udAlgorithm::Process(udDiagramItem *src)
{
    // initialize algorithm
    if(this->Initialize())
    {
		m_pProcessedDiagram = src;
        this->ProcessAlgorithm(src);
    }

    this->CleanUp();
}

bool udAlgorithm::Initialize()
{
    return true;
}

void udAlgorithm::ProcessAlgorithm(udDiagramItem *src)
{
}

void udAlgorithm::CleanUp()
{
}

