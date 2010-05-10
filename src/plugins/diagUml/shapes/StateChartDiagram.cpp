#include "StateChartDiagram.h"

IMPLEMENT_DYNAMIC_CLASS(umlStateChartDiagram, udDiagramCanvas)

umlStateChartDiagram::umlStateChartDiagram() : udDiagramCanvas()
{
}

umlStateChartDiagram::umlStateChartDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id)
: udDiagramCanvas(manager, parent, id)
{
}

umlStateChartDiagram::~umlStateChartDiagram()
{

}
