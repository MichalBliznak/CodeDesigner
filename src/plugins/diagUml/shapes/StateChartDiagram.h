#ifndef STATECHARTDIAGRAM_H
#define STATECHARTDIAGRAM_H

#include "projectbase/DiagramBase.h"

class WXDLLIMPEXP_CD umlStateChartDiagram : public udDiagramCanvas
{
public:
    DECLARE_DYNAMIC_CLASS(umlStateChartDiagram);

    umlStateChartDiagram();
    umlStateChartDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id);
    virtual ~umlStateChartDiagram();
};

#endif // STATECHARTDIAGRAM_H
