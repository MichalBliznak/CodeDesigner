#ifndef UMLPOLYGONELEMENT_H
#define UMLPOLYGONELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"
#include "LabelElement.h"

class WXDLLIMPEXP_CD uddPolygonElement : public wxSFPolygonShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddPolygonElement);

    uddPolygonElement();
    uddPolygonElement(const uddPolygonElement &obj);
    virtual ~uddPolygonElement();

    // public data members accessors
    wxSFEditTextShape* GetTitle(){return m_pTitle;}

    // public virtual functions
    virtual bool OnKey(int key);

protected:
    // protected data members
    uddLabelElement *m_pTitle;

private:
    // private functions
    void Initialize();
	void DisableUselessProperties();
};

#endif // UMLPOLYGONELEMENT_H
