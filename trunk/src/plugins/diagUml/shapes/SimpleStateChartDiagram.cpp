#include "SimpleStateChartDiagram.h"

IMPLEMENT_DYNAMIC_CLASS(umlSimpleStateChartDiagram, udDiagramCanvas)

umlSimpleStateChartDiagram::umlSimpleStateChartDiagram() : udDiagramCanvas()
{
}

umlSimpleStateChartDiagram::umlSimpleStateChartDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id)
: udDiagramCanvas(manager, parent, id)
{
}

umlSimpleStateChartDiagram::~umlSimpleStateChartDiagram()
{

}
