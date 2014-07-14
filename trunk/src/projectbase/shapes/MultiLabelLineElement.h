#ifndef UMLMULTILABELLINEELEMENT_H
#define UMLMULTILABELLINEELEMENT_H

#include "wx/wxsf/wxShapeFramework.h"
#include "LabelElement.h"

class WXDLLIMPEXP_CD uddMultiLabelLineElement : public wxSFOrthoLineShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddMultiLabelLineElement);

    uddMultiLabelLineElement();
    uddMultiLabelLineElement(const uddMultiLabelLineElement &obj);
    virtual ~uddMultiLabelLineElement();

    // public data members accessors
	uddLabelElement* CreateLabel(udLABEL::TYPE type);
    uddLabelElement* GetLabel(udLABEL::TYPE type);
	
	void SetMaxLabelCount(int count);
	int GetMaxLabelCount() const { return m_nMaxLabelCount; }

    // public virtual functions
    virtual bool OnKey(int key);

protected:
    // protected data members
	int m_nCounter;
	uddLabelElement **m_pLabels;

private:
	// private data members
	int m_nMaxLabelCount;
	
    // private functions
	void DisableUselessProperties();
};


#endif // UMLMULTILABELLINEELEMENT_H
