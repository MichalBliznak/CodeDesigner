#ifndef UMLCIRCLEELEMENT_H
#define UMLCIRCLEELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"

#include "LabelElement.h"

class WXDLLIMPEXP_CD uddCircleElement : public wxSFCircleShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddCircleElement);

    uddCircleElement();
	uddCircleElement(const uddCircleElement &obj);
    virtual ~uddCircleElement();

    // public data members accessors
    wxSFEditTextShape* GetTitle(){return m_pTitle;}

    // public virtual functions
    virtual bool OnKey(int key);

protected:
    // protected data members
    uddLabelElement *m_pTitle;

	// protected functions
    virtual void CreateHandles();

private:
    // private functions
    void Initiliaze();
	void DisableUselessProperties();
};

#endif // UMLCIRCLEELEMENT_H
