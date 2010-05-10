#ifndef UMLUNIDIRECTASSOCITEM_H
#define UMLUNIDIRECTASSOCITEM_H

#include "projectbase/shapes/MultiLabelLineElement.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlUniDirectAssocItem : public uddMultiLabelLineElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlUniDirectAssocItem);

    umlUniDirectAssocItem();
	umlUniDirectAssocItem(const umlUniDirectAssocItem &obj);
    virtual ~umlUniDirectAssocItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLUNIDIRECTASSOCITEM_H
