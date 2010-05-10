#ifndef UMLNOTECONNITEM_H
#define UMLNOTECONNITEM_H

#include "wx/wxsf/wxShapeFramework.h"

class uddNoteConnItem : public wxSFLineShape
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddNoteConnItem);

    uddNoteConnItem();
	uddNoteConnItem(const uddNoteConnItem &obj);
    virtual ~uddNoteConnItem();

private:
    // private functions
    void Initialize();
};


#endif // UMLNOTECONNITEM_H
