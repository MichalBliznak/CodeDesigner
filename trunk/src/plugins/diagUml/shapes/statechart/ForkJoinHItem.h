#ifndef UMLFORKJOINHITEM_H
#define UMLFORKJOINHITEM_H

#include "projectbase/shapes/PolygonElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlForkJoinHItem : public uddPolygonElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlForkJoinHItem);

    umlForkJoinHItem();
	umlForkJoinHItem(const umlForkJoinHItem &obj);
    virtual ~umlForkJoinHItem();

protected:
    // protected functions
    virtual void CreateHandles();

private:
    // private functions
    void Initialize();
};



#endif // UMLFORKJOINHITEM_H
