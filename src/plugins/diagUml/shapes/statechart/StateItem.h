#ifndef UMLSTATEITEM_H
#define UMLSTATEITEM_H

#include "SimpleStateItem.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlCompStateItem : public umlSimpleStateItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlCompStateItem);

    umlCompStateItem();
	umlCompStateItem(const umlCompStateItem &obj);
    virtual ~umlCompStateItem();
	
	// public virtual functions
	virtual void OnChildDropped(const wxRealPoint& pos, wxSFShapeBase *child);

private:
	// protected data members
    uddLabelElement *m_pEntryActions;
    uddLabelElement *m_pExitActions;
	wxSFGridShape *m_pGrid;
	
    // private functions
    void Initialize();
	void DisableUselessProperties();
};



#endif // UMLSTATEITEM_H
