#ifndef UMLDECISIONITEM_H
#define UMLDECISIONITEM_H

#include "projectbase/shapes/PolygonElement.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlDecisionItem : public uddPolygonElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlDecisionItem);

    umlDecisionItem();
	umlDecisionItem(const umlDecisionItem &obj);
    virtual ~umlDecisionItem();

private:
    // private functions
    void Initialize();
};



#endif // UMLDECISIONITEM_H
