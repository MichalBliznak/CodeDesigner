#ifndef UMLROUNDRECTELEMENT_H
#define UMLROUNDRECTELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"
#include "LabelElement.h"

class WXDLLIMPEXP_CD uddRoundRectElement : public wxSFRoundRectShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddRoundRectElement);

    uddRoundRectElement();
    uddRoundRectElement(const uddRoundRectElement &obj);
    virtual ~uddRoundRectElement();

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

#endif // UMLROUNDRECTELEMENT_H
