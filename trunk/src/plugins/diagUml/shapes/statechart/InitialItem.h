#ifndef UMLINITIALITEM_H
#define UMLINITIALITEM_H

#include "projectbase/shapes/CircleElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlInitialItem : public uddCircleElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlInitialItem);

    umlInitialItem();
	umlInitialItem(const umlInitialItem &obj);
    virtual ~umlInitialItem();

private:
    // private functions
    void Initialize();
};



#endif // UMLINITIALITEM_H
