#ifndef UDDGROUPITEM_H
#define UDDGROUPITEM_H

#include "projectbase/shapes/RectElement.h" // Base class: uddRectElement

class uddGroupItem : public uddRectElement
{
public:
	XS_DECLARE_CLONABLE_CLASS(uddGroupItem)
	
	uddGroupItem();
	uddGroupItem(const uddGroupItem& obj);
	virtual ~uddGroupItem();
	
protected:
	void Initialize();

};

#endif // UDDGROUPITEM_H
