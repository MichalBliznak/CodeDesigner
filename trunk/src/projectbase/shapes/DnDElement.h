#ifndef __dndelement__
#define __dndelement__

#include "interfaces/Defs.h"
#include "wx/wxsf/wxShapeFramework.h"

class WXDLLIMPEXP_CD uddDnDElement : public wxSFShapeBase
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddDnDElement);

    uddDnDElement();
    uddDnDElement(const uddDnDElement &obj);
    virtual ~uddDnDElement();

};
#endif // __dndelement__
