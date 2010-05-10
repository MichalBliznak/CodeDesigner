#ifndef SIMPLESTATECHARTDIAGRAM_H
#define SIMPLESTATECHARTDIAGRAM_H

#include "projectbase/DiagramBase.h"

class WXDLLIMPEXP_CD umlSimpleStateChartDiagram : public udDiagramCanvas
{
public:
    DECLARE_DYNAMIC_CLASS(umlSimpleStateChartDiagram);

    umlSimpleStateChartDiagram();
    umlSimpleStateChartDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id);
    virtual ~umlSimpleStateChartDiagram();
};

#endif // SIMPLESTATECHARTDIAGRAM_H
