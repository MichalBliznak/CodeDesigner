#ifndef UDTABART_H
#define UDTABART_H

#include <wx/aui/auibook.h>
#include <wx/aui/auibar.h>

class udTabArt : public wxAuiDefaultTabArt {

public:
	udTabArt();
    virtual ~udTabArt();

    wxAuiTabArt* Clone(); 

    wxSize GetTabSize(
                 wxDC& dc,
                 wxWindow* wnd,
                 const wxString& caption,
                 const wxBitmap& bitmap,
                 bool active,
                 int close_button_state,
                 int* x_extent);
};

class udToolArt : public wxAuiDefaultToolBarArt {
	
public:
	udToolArt();
	virtual ~udToolArt();
	
	wxAuiToolBarArt* Clone(); 
};

#endif // UDTABART_H
