#ifndef UMLINCLUDEASSOCITEM_H
#define UMLINCLUDEASSOCITEM_H

#include "projectbase/shapes/MultiLabelLineElement.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlIncludeAssocItem : public uddMultiLabelLineElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlIncludeAssocItem);

    umlIncludeAssocItem();
	umlIncludeAssocItem(const umlIncludeAssocItem &obj);
    virtual ~umlIncludeAssocItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLINCLUDEASSOCITEM_H
