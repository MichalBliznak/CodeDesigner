#ifndef UDTABART_H
#define UDTABART_H

#include <wx/aui/auibook.h>
#include <wx/aui/auibar.h>

#if wxVERSION_NUMBER >= 2905
class udTabArt : public wxAuiGenericTabArt {
#else
class udTabArt : public wxAuiDefaultTabArt {
#endif
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
				 
	/*int GetAdditionalBorderSpace(wxWindow* wnd) { return 0; }
	int GetBorderWidth(wxWindow* wnd) { return 0; };*/
	int GetIndentSize() { return 2; }
};

class udToolArt : public wxAuiDefaultToolBarArt {
	
public:
	udToolArt();
	virtual ~udToolArt();
	
	wxAuiToolBarArt* Clone(); 
};

#endif // UDTABART_H
