#ifndef UMLFINALITEM_H
#define UMLFINALITEM_H

#include "projectbase/shapes/CircleElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlFinalItem : public uddCircleElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlFinalItem);

    umlFinalItem();
	umlFinalItem(const umlFinalItem &obj);
    virtual ~umlFinalItem();

protected:
    // protected virtual functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);

private:
    // private functions
    void Initialize();
};



#endif // UMLFINALITEM_H
