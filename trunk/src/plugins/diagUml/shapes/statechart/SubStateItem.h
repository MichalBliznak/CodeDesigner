#ifndef UMLSUBSTATEITEM_H
#define UMLSUBSTATEITEM_H

#include "projectbase/shapes/RoundRectElement.h"
#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD umlSubStateItem : public uddRoundRectElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlSubStateItem);

    umlSubStateItem();
	umlSubStateItem(const umlSubStateItem &obj);
    virtual ~umlSubStateItem();

protected:
    // protected data members
    wxSFBitmapShape *m_pSign;

    // protected virtual functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);
    virtual void DrawHighlighted(wxDC& dc);

private:
    // private functions
    void Initialize();
	void DisableUselessProperties();
};

#endif // UMLSUBSTATEITEM_H
