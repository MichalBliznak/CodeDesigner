///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  8 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/checklst.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/treectrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class _RevEngPanel
///////////////////////////////////////////////////////////////////////////////
class _RevEngPanel : public wxPanel 
{
	private:
	
	protected:
		enum
		{
			IDB_ADDFILES = 6000,
			IDB_REMOVEFILES,
			IDM_FILES_SELECTALL,
			IDM_FILES_DESELECTALL,
			IDM_FILES_CHECKALL,
			IDM_FILES_UNCHECKALL,
			IDB_PARSE
		};
		
		wxStaticText* m_staticText1;
		wxButton* m_buttonAddFiles;
		wxButton* m_buttonRemoveFiles;
		wxCheckListBox* m_checkListFiles;
		wxMenu* m_menuFiles;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textIdentifiers;
		wxButton* m_buttonParse;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText2;
		wxTreeCtrl* m_treeSymbols;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAddFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRemoveFiles( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSelectAllFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeselectAllFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckAllFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUncheckAllFilesClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnParseClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateParse( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnBeginDrag( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnRightClick( wxTreeEvent& event ) { event.Skip(); }
		
	
	public:
		
		_RevEngPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL ); 
		~_RevEngPanel();
		
		void m_checkListFilesOnContextMenu( wxMouseEvent &event )
		{
			m_checkListFiles->PopupMenu( m_menuFiles, event.GetPosition() );
		}
	
};

#endif //__GUI_H__
