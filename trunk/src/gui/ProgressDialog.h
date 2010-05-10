#ifndef __progressdialog__
#define __progressdialog__

#include "GUI.h"

class udProgressDialog : public _ProgressDialog
{
public:
	udProgressDialog(wxWindow *parent);
	virtual ~udProgressDialog();
	
	// public functions
	void SetLabel(const wxString& txt);
	void SetStepCount(int steps);
	
	void Clear();
	void Step();

};

#endif // __progressdialog__
