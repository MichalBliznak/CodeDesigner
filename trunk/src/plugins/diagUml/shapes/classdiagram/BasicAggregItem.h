#ifndef UMLBASICAGGREGITEM_H
#define UMLBASICAGGREGITEM_H

#include "UniDirectAssocItem.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlBasicAggregItem : public umlUniDirectAssocItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlBasicAggregItem);

    umlBasicAggregItem();
	umlBasicAggregItem(const umlBasicAggregItem &obj);
    virtual ~umlBasicAggregItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLBASICAGGREGITEM_H
