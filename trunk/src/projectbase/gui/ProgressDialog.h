#ifndef __progressdialog__
#define __progressdialog__

#include "GUI_ProjectBase.h"
#include "../ProjectBase.h"

class WXDLLIMPEXP_CD udProgressDialog : public _ProgressDialog
{
public:
	udProgressDialog(wxWindow *parent);
	virtual ~udProgressDialog();
	
	// public functions
	void SetLabel(const wxString& txt);
	void SetStepCount(int steps);
	
	void Clear();
	void Step();
	void Pulse();

};

#endif // __progressdialog__
