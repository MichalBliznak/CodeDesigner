#ifndef UMLHISTORYITEM_H
#define UMLHISTORYITEM_H

#include "projectbase/shapes/CircleElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlHistoryItem : public uddCircleElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlHistoryItem);

    umlHistoryItem();
	umlHistoryItem(const umlHistoryItem &obj);
    virtual ~umlHistoryItem();

protected:
    // protected data members
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);

private:
    // private functions
    void Initiliaze();
    void DrawSign(wxDC& dc);
};

#endif // UMLHISTORYITEM_H
