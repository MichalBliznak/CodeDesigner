#ifndef UMLRECTELEMENT_H
#define UMLRECTELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"
#include "LabelElement.h"

class WXDLLIMPEXP_CD uddRectElement : public wxSFRectShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddRectElement);

    uddRectElement();
    uddRectElement(const uddRectElement &obj);
    virtual ~uddRectElement();

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

#endif // UMLRECTELEMENT_H
