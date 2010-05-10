#ifndef UMLNOTEITEM_H
#define UMLNOTEITEM_H

#include "projectbase/shapes/PolygonElement.h"

class uddNoteItem : public uddPolygonElement
{
public:
    XS_DECLARE_CLONABLE_CLASS(uddNoteItem);

    uddNoteItem();
    uddNoteItem(const uddNoteItem &obj);
    virtual ~uddNoteItem();

    // public virtual functions
    virtual bool OnKey(int key);

protected:
    // protected data members
    uddLabelElement *m_pContent;

    // protected functions
    void Initialize();

    // protected virtual functions
    virtual void DrawNormal(wxDC& dc);
    virtual void DrawHover(wxDC& dc);

private:
    // private functions
    wxRect UpdateRightCorner();
    void DrawRightCorner(const wxRect& bb, wxDC& dc);
};



#endif // UMLNOTEITEM_H
