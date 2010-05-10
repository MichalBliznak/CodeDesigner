#ifndef UMLSIMPLESTATEITEM_H
#define UMLSIMPLESTATEITEM_H

#include "projectbase/shapes/RoundRectElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlSimpleStateItem : public uddRoundRectElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlSimpleStateItem);

    umlSimpleStateItem();
	umlSimpleStateItem(const umlSimpleStateItem &obj);
    virtual ~umlSimpleStateItem();

protected:
    // protected virtual functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);
    virtual void DrawHighlighted(wxDC& dc);

private:
    // private functions
    void Initialize();
};



#endif // UMLSIMPLESTATEITEM_H
