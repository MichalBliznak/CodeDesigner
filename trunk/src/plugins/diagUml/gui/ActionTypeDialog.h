#ifndef __udactiontypedialog__
#define __udactiontypedialog__

#include "projectbase/gui/ChoiceDialog.h"

class udActionTypeDialog : public udChoiceDialog
{
public:
	udActionTypeDialog(wxWindow *parent);
	virtual ~udActionTypeDialog();
};

#endif // __udactiontypedialog__
