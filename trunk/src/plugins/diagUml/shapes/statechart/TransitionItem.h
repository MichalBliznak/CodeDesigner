#ifndef UMLTRANSITIONITEM_H
#define UMLTRANSITIONITEM_H

#include "projectbase/shapes/LineElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlTransitionItem : public uddLineElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlTransitionItem);

    umlTransitionItem();
	umlTransitionItem(const umlTransitionItem &obj);
    virtual ~umlTransitionItem();
	
	// public virtual functions
	virtual void OnChildDropped(const wxRealPoint& pos, wxSFShapeBase *child);

private:
    // private functions
    void Initialize();
};


#endif // UMLTRANSITIONITEM_H
