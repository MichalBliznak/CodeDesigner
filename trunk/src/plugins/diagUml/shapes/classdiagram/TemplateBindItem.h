#ifndef UMLTEMPLATEBINDITEM_H
#define UMLTEMPLATEBINDITEM_H

#include "projectbase/shapes/MultiLabelLineElement.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlTemplateBindItem : public uddMultiLabelLineElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlTemplateBindItem);

    umlTemplateBindItem();
	umlTemplateBindItem(const umlTemplateBindItem &obj);
    virtual ~umlTemplateBindItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLTEMPLATEBINDITEM_H
