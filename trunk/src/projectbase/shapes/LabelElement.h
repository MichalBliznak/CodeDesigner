#ifndef UMLLABELELEMENT_H
#define UMLLABELELEMENT_H

#include "interfaces/Defs.h"
#include "../Common.h"
#include "wx/wxsf/wxShapeFramework.h"

#define uddvLABELELEMENT_LABELTYPE udLABEL::ltTITLE

class WXDLLIMPEXP_CD uddLabelElement : public wxSFEditTextShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddLabelElement);

    uddLabelElement();
	uddLabelElement(const uddLabelElement &obj);
    virtual ~uddLabelElement();

    // public functions
    void SetLabelType( udLABEL::TYPE type ){ m_nLabelType = type; }
    udLABEL::TYPE GetLabelType(){ return m_nLabelType; }

	// public virtual functions
	virtual void OnDragging(const wxPoint& pos);
	virtual void OnChildDropped(const wxRealPoint& pos, wxSFShapeBase *child);

protected:
    // protected data members
    udLABEL::TYPE m_nLabelType;

	// protected functions
    virtual void CreateHandles();

private:
	// private data members
	wxPoint m_nStartDragPos;

    // private functions
    void Initiliaze();
	void DisableUselessProperties();
};

#endif // UMLLABELELEMENT_H
