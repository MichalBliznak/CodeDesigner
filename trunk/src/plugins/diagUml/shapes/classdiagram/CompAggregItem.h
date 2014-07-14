#ifndef UMLCOMPAGGREGITEM_H
#define UMLCOMPAGGREGITEM_H

#include "UniDirectAssocItem.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlCompAggregItem : public umlUniDirectAssocItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlCompAggregItem);

    umlCompAggregItem();
	umlCompAggregItem(const umlCompAggregItem &obj);
    virtual ~umlCompAggregItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLBASICAGGREGITEM_H
