#ifndef UDDIALOGFUNCTIONS_H
#define UDDIALOGFUNCTIONS_H

#include "Art.h"
#include "XS2PG.h"
#include "Project.h"

#include <wx/listctrl.h>

#define udfSORT true
#define udfDONT_SORT false

class udDialogFunctions
{
public:	
	// public functions
	
	// wxListCtrl related functions
	void GetSelectedItems(const wxListCtrl *ctrl, wxArrayInt& selection);
	void SelectAllItems(wxListCtrl *ctrl);
	void DeselectAllItems(wxListCtrl *ctrl);
	void InsertProjectItems(wxListCtrl *ctrl, SerializableList& items, bool sort = udfDONT_SORT);
	
	// wxListBox related functions
	void SelectAllItems(wxListBox *ctrl);
	void DeselectAllItems(wxListBox *ctrl);
};

#endif // UDDIALOGFUNCTIONS_H
