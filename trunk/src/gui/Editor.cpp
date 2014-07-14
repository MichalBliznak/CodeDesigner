#include "gui/Editor.h"
#include "UMLDesignerApp.h"

#include <wx/clipbrd.h>

BEGIN_EVENT_TABLE ( udCodeEditor,  _EditorFrame )
	EVT_STC_MARGINCLICK( wxID_ANY, udCodeEditor::OnMarginClick )
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
	
	this->SetFocus();
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

void udCodeEditor::OnMarginClick ( wxStyledTextEvent &event )
{
	if ( event.GetMargin() == 1 )
	{
		int lineClick = m_scintillaEditor->LineFromPosition ( event.GetPosition() );
		int levelClick = m_scintillaEditor->GetFoldLevel ( lineClick );

		if ( ( levelClick & wxSTC_FOLDLEVELHEADERFLAG ) > 0 )
		{
			m_scintillaEditor->ToggleFold ( lineClick );
		}
	}
}

void udCodeEditor::OnCopyClick(wxCommandEvent& event)
{
	if( wxTheClipboard->Open() )
	{
		wxTheClipboard->SetData( new wxTextDataObject( m_scintillaEditor->GetSelectedText() ) );
		wxTheClipboard->Close();
	}
}

void udCodeEditor::OnCutClick(wxCommandEvent& event)
{
	OnCopyClick( event );
	m_scintillaEditor->ReplaceSelection( wxT("") );
}

void udCodeEditor::OnPasteClick(wxCommandEvent& event)
{
	if( wxTheClipboard->Open() )
	{
		wxTextDataObject data;
		wxTheClipboard->GetData( data );
		
		m_scintillaEditor->InsertText( m_scintillaEditor->GetCurrentPos(), data.GetText() );
		
		wxTheClipboard->Close();
	}
}

void udCodeEditor::OnUpdateCopy(wxUpdateUIEvent& event)
{
	event.Enable( !m_scintillaEditor->GetSelectedText().IsEmpty() );
}

void udCodeEditor::OnUpdateCut(wxUpdateUIEvent& event)
{
	OnUpdateCopy( event );
}

void udCodeEditor::OnUpdatePaste(wxUpdateUIEvent& event)
{
	if( wxTheClipboard->Open() )
	{
		event.Enable( wxTheClipboard->IsSupported( wxDF_TEXT ) );
		wxTheClipboard->Close();
	}
}
