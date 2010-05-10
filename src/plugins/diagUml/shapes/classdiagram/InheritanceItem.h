#ifndef UMLINHERITITEM_H
#define UMLINHERITITEM_H

#include <wx/wxsf/wxShapeFramework.h>
#include "interfaces/Defs.h"


class WXDLLIMPEXP_CD umlInheritanceItem : public wxSFOrthoLineShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlInheritanceItem);

    umlInheritanceItem();
	umlInheritanceItem(const umlInheritanceItem &obj);
    virtual ~umlInheritanceItem();

private:
    // private functions
    void Initialize();
};

#endif // UMLINHERITITEM_H
