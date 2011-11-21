#ifndef CLASSDIAGRAM_H
#define CLASSDIAGRAM_H

#include "projectbase/DiagramBase.h"
#include "projectbase/codegen/Language.h"

#include "../DiagUml.h"
#include "classdiagram/ClassItem.h"

class WXDLLIMPEXP_CD umlClassDiagram : public udDiagramCanvas
{
public:
    DECLARE_DYNAMIC_CLASS(umlClassDiagram);

    umlClassDiagram();
    umlClassDiagram(wxSFDiagramManager *manager, wxWindow *parent, long id);
    virtual ~umlClassDiagram();

	// public static functions
	static void GetBaseClasses(umlClassItem *shape, ShapeList& bases);
	static void GetOuterClasses(umlClassItem *shape, ShapeList& bases);
	static void GetClassMembers(umlClassItem *shape, wxClassInfo *type, udLanguage::ACCESSTYPE at, SerializableList& members);
	static void GetClassAssociations(umlClassItem *shape, wxClassInfo *type, wxSFLineShape::CONNECTMODE direction, udLanguage::ACCESSTYPE at, ShapeList& assocs);
};

#endif // CLASSDIAGRAM_H
