#include "StateChartElementProcessor.h"
#include "../../diagUml/DiagUml.h"

IMPLEMENT_DYNAMIC_CLASS(udStateChartElementProcessor, udElementProcessor);

udStateChartElementProcessor::udStateChartElementProcessor()
{
    m_pParentGenerator = NULL;
}

udStateChartElementProcessor::udStateChartElementProcessor(udGenerator *parent)
: udElementProcessor(parent)
{
}

udStateChartElementProcessor::~udStateChartElementProcessor()
{
}

wxSFLineShape* udStateChartElementProcessor::GetConditionlessPath(wxSFShapeBase *element)
{
    wxSFDiagramManager *pDiagManager = element->GetShapeManager();

    // process all element paths
    udTransElementItem *pTransElement;

    ShapeList lstTransitions;
    pDiagManager->GetAssignedConnections(element, CLASSINFO(umlTransitionItem), wxSFShapeBase::lineSTARTING, lstTransitions);

    ShapeList::compatibility_iterator node = lstTransitions.GetFirst();
    while(node)
    {
        pTransElement = (udTransElementItem*)node->GetData()->GetUserData();
		if( !pTransElement->HasCondition() )return (wxSFLineShape*)node->GetData();

		node = node->GetNext();
	}
	
	return NULL;
}

