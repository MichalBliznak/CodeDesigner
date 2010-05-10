#ifndef UMLEXITITEM_H
#define UMLEXITITEM_H

#include "projectbase/shapes/CircleElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlExitItem : public uddCircleElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlExitItem);

    umlExitItem();
	umlExitItem(const umlExitItem &obj);
    virtual ~umlExitItem();

protected:
    // protected functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);

private:
    // private functions
    void Initialize();
    void DrawCross(wxDC& dc);
};



#endif // UMLEXITITEM_H
