#ifndef UMLFORKJOINVITEM_H
#define UMLFORKJOINVITEM_H

#include "projectbase/shapes/PolygonElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlForkJoinVItem : public uddPolygonElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlForkJoinVItem);

    umlForkJoinVItem();
	umlForkJoinVItem(const umlForkJoinVItem &obj);
    virtual ~umlForkJoinVItem();

protected:
    // protected functions
    virtual void CreateHandles();

private:
    // private functions
    void Initialize();
};



#endif // UMLFORKJOINVITEM_H
