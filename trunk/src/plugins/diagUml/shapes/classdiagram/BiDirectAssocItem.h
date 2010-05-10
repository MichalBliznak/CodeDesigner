#ifndef UMLBIDIRECTASSOCITEM_H
#define UMLBIDIRECTASSOCITEM_H

#include "projectbase/shapes/MultiLabelLineElement.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlBiDirectAssocItem : public uddMultiLabelLineElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlBiDirectAssocItem);

    umlBiDirectAssocItem();
	umlBiDirectAssocItem(const umlBiDirectAssocItem &obj);
    virtual ~umlBiDirectAssocItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLBIDIRECTASSOCITEM_H
