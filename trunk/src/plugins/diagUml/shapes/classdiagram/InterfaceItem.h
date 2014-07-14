#ifndef UMLINTERFACEITEM_H
#define UMLINTERFACEITEM_H

#include "wx/wxsf/wxShapeFramework.h"
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlInterfaceItem : public wxSFOrthoLineShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlInterfaceItem);

    umlInterfaceItem();
	umlInterfaceItem(const umlInterfaceItem &obj);
    virtual ~umlInterfaceItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLINTERFACEITEM_H
