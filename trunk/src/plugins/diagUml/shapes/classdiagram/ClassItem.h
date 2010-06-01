#ifndef UMLCLASSITEM_H
#define UMLCLASSITEM_H

#include "projectbase/shapes/RectElement.h"
#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD umlClassItem : public uddRectElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlClassItem);

    umlClassItem();
	umlClassItem(const umlClassItem &obj);
    virtual ~umlClassItem();
	
	// public functions
	void ClearVariableCtrls();
	void ClearFunctionCtrls();
	uddLabelElement* CreateVariableCtrl( const wxString& content, long parentid );
	uddLabelElement* CreateFunctionCtrl( const wxString& content, long parentid );
	
	// public virtual functions
	virtual void OnChildDropped(const wxRealPoint& pos, wxSFShapeBase *child);

protected:
	// protected data members
	wxSFFlexGridShape *m_pGrid;
	wxSFGridShape *m_pVariablesGrid;
	wxSFGridShape *m_pFunctionsGrid;

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

#endif // UMLCLASSITEM_H
