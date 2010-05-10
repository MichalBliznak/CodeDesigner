#ifndef __udaccesstypedialog__
#define __udaccesstypedialog__

#include "interfaces/Defs.h"
#include "ChoiceDialog.h"

class WXDLLIMPEXP_CD udAccessTypeDialog : public udChoiceDialog
{
public:
	udAccessTypeDialog(wxWindow *parent);
	virtual ~udAccessTypeDialog();
};

#endif // __udaccesstypedialog__
