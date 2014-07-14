#ifndef UMLENTRYITEM_H
#define UMLENTRYITEM_H

#include "projectbase/shapes/CircleElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlEntryItem : public uddCircleElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlEntryItem);

    umlEntryItem();
	umlEntryItem(const umlEntryItem &obj);
    virtual ~umlEntryItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLENTRYITEM_H
