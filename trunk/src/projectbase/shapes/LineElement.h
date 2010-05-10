#ifndef UMLLINEELEMENT_H
#define UMLLINEELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"
#include "LabelElement.h"

class WXDLLIMPEXP_CD uddLineElement : public wxSFCurveShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddLineElement);

    uddLineElement();
    uddLineElement(const uddLineElement &obj);
    virtual ~uddLineElement();

    // public data members accessors
    uddLabelElement* GetLabel(){return m_pLabel;}

    // public virtual functions
    virtual bool OnKey(int key);

protected:
    // protected data members
	uddLabelElement *m_pLabel;

private:
    // private functions
    void Initiliaze();
	void DisableUselessProperties();
};


#endif // UMLLINEELEMENT_H
