#ifndef UMLCLASSTEMPLITEM_H
#define UMLCLASSTEMPLITEM_H

#include "ClassItem.h"

class WXDLLIMPEXP_CD umlClassTemplateItem : public umlClassItem
{
public:
    XS_DECLARE_CLONABLE_CLASS(umlClassTemplateItem);

    umlClassTemplateItem();
	umlClassTemplateItem(const umlClassTemplateItem &obj);
    virtual ~umlClassTemplateItem();
	
	// public functions	
	uddLabelElement* GetTemplateCtrl() {return m_pTemplate;}
	void UpdateTemplateCtrl( const wxString& txt );

protected:
	// protected data members
	uddLabelElement *m_pTemplate;
	
private:
	void Initialize();
};

#endif // UMLCLASSTEMPLITEM_H
