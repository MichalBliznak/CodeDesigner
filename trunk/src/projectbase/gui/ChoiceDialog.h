#ifndef __udchoicedialog__
#define __udchoicedialog__

#include "interfaces/Defs.h"
#include "GUI_ProjectBase.h"

class WXDLLIMPEXP_CD udChoiceDialog : public _ChoiceDialog
{
public:
	udChoiceDialog(wxWindow *parent);
	virtual ~udChoiceDialog();
	
	// public functions
	void SetComment(const wxString& txt);
	void SetChoices(int n, const wxString choices[]);
	void SetChoices(const wxArrayString& choices);
	
	int GetChoice();
	wxString GetChoiceString();
};

#endif // __udchoicedialog__
