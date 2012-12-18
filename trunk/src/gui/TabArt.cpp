#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "gui/TabArt.h"
#include "UMLDesignerApp.h"

#if wxVERSION_NUMBER >= 2900
	#define m_normal_font m_normalFont
	#define m_selected_font m_selectedFont
	#define m_measuring_font m_measuringFont
	#define m_fixed_tab_width m_fixedTabWidth
	#define m_tab_ctrl_height m_tabCtrlHeight
	#define m_base_colour m_baseColour
	#define m_base_colour_brush m_baseColourBrush
	#define m_base_colour_pen m_baseColourPen
	#define m_border_pen m_borderPen
	#define m_active_close_bmp m_activeCloseBmp
	#define m_disabled_close_bmp m_disabledCloseBmp
	#define m_active_left_bmp m_activeLeftBmp
	#define m_disabled_left_bmp m_disabledLeftBmp
	#define m_active_right_bmp m_activeRightBmp
	#define m_disabled_right_bmp m_disabledRightBmp
	#define m_active_windowlist_bmp m_activeWindowListBmp
	#define m_disabled_windowlist_bmp m_disabledWindowListBmp
	
	#define m_text_orientation m_textOrientation
	#define m_highlight_colour m_highlightColour
	#define m_separator_size m_separatorSize
	#define m_gripper_size m_gripperSize
	#define m_overflow_size m_overflowSize
	#define m_gripper_pen1 m_gripperPen1
	#define m_gripper_pen2 m_gripperPen2
	#define m_gripper_pen3 m_gripperPen3
	#define m_button_dropdown_bmp m_buttonDropDownBmp
	#define m_disabled_button_dropdown_bmp m_disabledButtonDropDownBmp
	#define m_overflow_bmp m_overflowBmp
	#define m_disabled_overflow_bmp m_disabledOverflowBmp
#endif

////////////////////////////////////////////////////////////////////////////////
// AUI notebook art

// these functions live in dockart.cpp -- they'll eventually
// be moved to a new utility cpp file

unsigned char wxAuiBlendColour(unsigned char fg, unsigned char bg, double alpha)
{
    double result = bg + (alpha * (fg - bg));
    if (result < 0.0)
        result = 0.0;
    if (result > 255)
        result = 255;
    return (unsigned char)result;
}

wxColor wxAuiStepColour(const wxColor& c, int ialpha)
{
	    if (ialpha == 100)
        return c;

    unsigned char r = c.Red(),
                  g = c.Green(),
                  b = c.Blue();
    unsigned char bg;

    // ialpha is 0..200 where 0 is completely black
    // and 200 is completely white and 100 is the same
    // convert that to normal alpha 0.0 - 1.0
    ialpha = wxMin(ialpha, 200);
    ialpha = wxMax(ialpha, 0);
    double alpha = ((double)(ialpha - 100.0))/100.0;

    if (ialpha > 100)
    {
        // blend with white
        bg = 255;
        alpha = 1.0 - alpha;  // 0 = transparent fg; 1 = opaque fg
    }
    else
    {
        // blend with black
        bg = 0;
        alpha += 1.0;         // 0 = transparent fg; 1 = opaque fg
    }

    r = wxAuiBlendColour(r, bg, alpha);
    g = wxAuiBlendColour(g, bg, alpha);
    b = wxAuiBlendColour(b, bg, alpha);

    return wxColour(r, g, b);
}

wxBitmap wxAuiBitmapFromBits(const unsigned char bits[], int w, int h, const wxColour& color)
{
	wxImage img = wxBitmap((const char*)bits, w, h).ConvertToImage();
    img.Replace(0,0,0,123,123,123);
    img.Replace(255,255,255,color.Red(),color.Green(),color.Blue());
    img.SetMaskColour(123,123,123);
    return wxBitmap(img);
}

#if defined( __WXMAC__ )
 static const unsigned char close_bits[]={
     0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFE, 0x03, 0xF8, 0x01, 0xF0, 0x19, 0xF3,
     0xB8, 0xE3, 0xF0, 0xE1, 0xE0, 0xE0, 0xF0, 0xE1, 0xB8, 0xE3, 0x19, 0xF3,
     0x01, 0xF0, 0x03, 0xF8, 0x0F, 0xFE, 0xFF, 0xFF };
#elif defined( __WXGTK__)
 static const unsigned char close_bits[]={
     0xff, 0xff, 0xff, 0xff, 0x07, 0xf0, 0xfb, 0xef, 0xdb, 0xed, 0x8b, 0xe8,
     0x1b, 0xec, 0x3b, 0xee, 0x1b, 0xec, 0x8b, 0xe8, 0xdb, 0xed, 0xfb, 0xef,
     0x07, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#else
 static const unsigned char close_bits[]={
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xf3, 0xcf, 0xf9,
     0x9f, 0xfc, 0x3f, 0xfe, 0x3f, 0xfe, 0x9f, 0xfc, 0xcf, 0xf9, 0xe7, 0xf3,
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
#endif

static const unsigned char left_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xfe, 0x3f, 0xfe,
   0x1f, 0xfe, 0x0f, 0xfe, 0x1f, 0xfe, 0x3f, 0xfe, 0x7f, 0xfe, 0xff, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const unsigned char right_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0x9f, 0xff, 0x1f, 0xff,
   0x1f, 0xfe, 0x1f, 0xfc, 0x1f, 0xfe, 0x1f, 0xff, 0x9f, 0xff, 0xdf, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static const unsigned char list_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x0f, 0xf8, 0xff, 0xff, 0x0f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfe, 0x7f, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

udTabArt::udTabArt()
{
    m_normal_font = *wxNORMAL_FONT;
    m_selected_font = *wxNORMAL_FONT;
    m_selected_font.SetWeight(wxBOLD);
    m_measuring_font = m_selected_font;

    m_fixed_tab_width = 100;
    m_tab_ctrl_height = 0;

#if defined( __WXMAC__ ) && wxOSX_USE_COCOA_OR_CARBON
    wxColor base_colour = wxColour( wxMacCreateCGColorFromHITheme(kThemeBrushToolbarBackground));
#else
	udSettings &Settings = wxGetApp().GetSettings();
    wxColor base_colour = Settings.GetProperty(wxT("Background colour"))->AsColour();
#endif

    // the base_colour is too pale to use as our base colour,
    // so darken it a bit --
    if ((255-base_colour.Red()) +
        (255-base_colour.Green()) +
        (255-base_colour.Blue()) < 60)
    {
        base_colour = wxAuiStepColour(base_colour, 92);
    }

    m_base_colour = base_colour;
    wxColor border_colour = wxAuiStepColour(base_colour, 75);

    m_border_pen = wxPen(border_colour);
    m_base_colour_pen = wxPen(m_base_colour);
    m_base_colour_brush = wxBrush(m_base_colour);

    m_active_close_bmp = wxAuiBitmapFromBits(close_bits, 16, 16, *wxBLACK);
    m_disabled_close_bmp = wxAuiBitmapFromBits(close_bits, 16, 16, wxColour(128,128,128));

    m_active_left_bmp = wxAuiBitmapFromBits(left_bits, 16, 16, *wxBLACK);
    m_disabled_left_bmp = wxAuiBitmapFromBits(left_bits, 16, 16, wxColour(128,128,128));

    m_active_right_bmp = wxAuiBitmapFromBits(right_bits, 16, 16, *wxBLACK);
    m_disabled_right_bmp = wxAuiBitmapFromBits(right_bits, 16, 16, wxColour(128,128,128));

    m_active_windowlist_bmp = wxAuiBitmapFromBits(list_bits, 16, 16, *wxBLACK);
    m_disabled_windowlist_bmp = wxAuiBitmapFromBits(list_bits, 16, 16, wxColour(128,128,128));

    m_flags = 0;
}

udTabArt::~udTabArt()
{
}

wxAuiTabArt* udTabArt::Clone()
{
    udTabArt* art = new udTabArt;
    art->SetNormalFont(m_normal_font);
    art->SetSelectedFont(m_selected_font);
    art->SetMeasuringFont(m_measuring_font);

    return art;
}

wxSize udTabArt::GetTabSize(wxDC& dc,
                                      wxWindow* wnd,
                                      const wxString& caption,
                                      const wxBitmap& bitmap,
                                      bool active,
                                      int close_button_state,
                                      int* x_extent)
{
#if wxVERSION_NUMBER >= 2905
	return wxAuiGenericTabArt::GetTabSize( dc, wnd, caption, bitmap, active, close_button_state, x_extent ) + wxSize(0, 6);
#else
	return wxAuiDefaultTabArt::GetTabSize( dc, wnd, caption, bitmap, active, close_button_state, x_extent ) + wxSize(0, 6);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// AUI toolbar art

udToolArt::udToolArt()
{
	udSettings &Settings = wxGetApp().GetSettings();
    m_base_colour = Settings.GetProperty(wxT("Background colour"))->AsColour();

    m_flags = 0;
    m_text_orientation = wxAUI_TBTOOL_TEXT_BOTTOM;
    m_highlight_colour = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);

    m_separator_size = 7;
    m_gripper_size = 7;
    m_overflow_size = 16;

    wxColor darker1_colour = wxAuiStepColour(m_base_colour, 85);
    wxColor darker2_colour = wxAuiStepColour(m_base_colour, 75);
    wxColor darker3_colour = wxAuiStepColour(m_base_colour, 60);
    wxColor darker4_colour = wxAuiStepColour(m_base_colour, 50);
    wxColor darker5_colour = wxAuiStepColour(m_base_colour, 40);

    m_gripper_pen1 = wxPen(darker5_colour);
    m_gripper_pen2 = wxPen(darker3_colour);
    m_gripper_pen3 = *wxWHITE_PEN;

    static const unsigned char button_dropdown_bits[] = { 0xe0, 0xf1, 0xfb };
    static const unsigned char overflow_bits[] = { 0x80, 0xff, 0x80, 0xc1, 0xe3, 0xf7 };

    m_button_dropdown_bmp = wxAuiBitmapFromBits(button_dropdown_bits, 5, 3,
                                                *wxBLACK);
    m_disabled_button_dropdown_bmp = wxAuiBitmapFromBits(
                                                button_dropdown_bits, 5, 3,
                                                wxColor(128,128,128));
    m_overflow_bmp = wxAuiBitmapFromBits(overflow_bits, 7, 6, *wxBLACK);
    m_disabled_overflow_bmp = wxAuiBitmapFromBits(overflow_bits, 7, 6, wxColor(128,128,128));

    m_font = *wxNORMAL_FONT;
}

udToolArt::~udToolArt()
{
}

wxAuiToolBarArt* udToolArt::Clone()
{
	 return static_cast<wxAuiToolBarArt*>(new udToolArt);
}
