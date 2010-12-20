#include "gui/Editor.h"
#include "UMLDesignerApp.h"

BEGIN_EVENT_TABLE ( udCodeEditor,  _EditorFrame )
	EVT_SCI_MARGINCLICK( wxID_ANY, udCodeEditor::OnMarginClick )
END_EVENT_TABLE ()

// constructor and destructor ///////////////////////////////////////////////////////////////

udCodeEditor::udCodeEditor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size )
: _EditorFrame( parent, id, title, pos, size )
{
	wxString sResPath = wxGetApp().GetResourcesPath();
	#ifdef __WXMSW__
	SetIcon(wxIcon(sResPath + wxT("app/gui/editor-icon.ico"), wxBITMAP_TYPE_ICO));
	#else
	SetIcon(wxIcon(sResPath + wxT("app/gui/editor-icon.png"), wxBITMAP_TYPE_PNG));
	#endif
}

// event handlers ///////////////////////////////////////////////////////////////////////////

void udCodeEditor::OnClose( wxCloseEvent& event )
{
	Destroy();
}

void udCodeEditor::OnCloseClick( wxCommandEvent& event )
{
	Destroy();
}

void udCodeEditor::OnMarginClick ( wxScintillaEvent &event )
{
	if ( event.GetMargin() == 1 )
	{
		int lineClick = m_scintillaEditor->LineFromPosition ( event.GetPosition() );
		int levelClick = m_scintillaEditor->GetFoldLevel ( lineClick );

		if ( ( levelClick & wxSCI_FOLDLEVELHEADERFLAG ) > 0 )
		{
			m_scintillaEditor->ToggleFold ( lineClick );
		}
	}
}
