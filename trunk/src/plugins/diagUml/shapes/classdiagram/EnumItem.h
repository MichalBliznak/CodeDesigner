#ifndef _UMLENUMITEM_H_
#define _UMLENUMITEM_H_

#include "projectbase/shapes/RectElement.h"
#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD umlEnumItem : public uddRectElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlEnumItem);

    umlEnumItem();
	umlEnumItem(const umlEnumItem &obj);
    virtual ~umlEnumItem();
	
	// public functions
	void ClearElementCtrls();
	uddLabelElement* CreateElementCtrl( const wxString& content, long parentid );
	
	// public virtual functions
	virtual void OnChildDropped(const wxRealPoint& pos, wxSFShapeBase *child);

protected:
	// protected data members
	uddLabelElement *m_pStereotype;
	wxSFGridShape *m_pElementsGrid;

    // protected virtual functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);
    virtual void DrawHighlighted(wxDC& dc);

private:
    // private functions
    void Initialize();
	void DisableUselessProperties();
	
	void DrawSeparators(wxDC& dc);
};

#endif // _UMLENUMITEM_H_
