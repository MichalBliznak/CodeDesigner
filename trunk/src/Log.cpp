#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include <wx/artprov.h>
#include <wx/imaglist.h>

#include "Ids.h"
#include "Log.h"
#include "UMLDesignerApp.h"

BEGIN_EVENT_TABLE(udLog, _LogPanel)
	EVT_MENU(IDM_LOGWND_CLEAR, udLog::OnClear)
END_EVENT_TABLE()

udLog::udLog( wxWindow* parent, wxWindowID id ) : _LogPanel( parent, id )
{
	// initialize list control
    m_pLogList->InsertColumn(0, wxT("Message"));
    m_pLogList->InsertColumn(1, wxT("Time"));

    // prepare the imagelist
    static const int ICON_SIZE = 16;
    m_lstImages = new wxImageList(ICON_SIZE, ICON_SIZE);

    // order should be the same as in the switch below!
#if wxVERSION_NUMBER < 2900
    static const wxChar* icons[] =
#else
	static const char* icons[] =
#endif
    {
		wxART_INFORMATION,
        wxART_WARNING,
        wxART_ERROR
    };

    m_fIconsLoaded = true;

    for ( size_t icon = 0; icon < WXSIZEOF(icons); icon++ )
    {
        wxBitmap bmp = wxArtProvider::GetBitmap(icons[icon], wxART_MESSAGE_BOX,
                                                wxSize(ICON_SIZE, ICON_SIZE));

        // This may very well fail if there are insufficient colours available.
        // Degrade gracefully.
        if ( !bmp.Ok() )
        {
            m_fIconsLoaded = false;
            break;
        }

        m_lstImages->Add(bmp);
    }

    m_pLogList->SetImageList(m_lstImages, wxIMAGE_LIST_SMALL);

	// create popup menu
	m_pPopupMenu = new wxMenu();
	m_pPopupMenu->Append(IDM_LOGWND_CLEAR, wxT("Clear"));
}

udLog::~udLog()
{
	delete m_lstImages;
	delete m_pPopupMenu;
}

void udLog::ClearMessages()
{
	m_pLogList->DeleteAllItems();
}

void udLog::AddMessage(const wxString &msg)
{
	if( ( msg.Contains( wxT("ERROR") ) && (UMLDesignerApp::GetLogMask() & UMLDesignerApp::logERRORS) ) ||
		( msg.Contains( wxT("WARNING") ) && (UMLDesignerApp::GetLogMask() & UMLDesignerApp::logWARNINGS) ) ||
		(UMLDesignerApp::GetLogMask() & UMLDesignerApp::logNORMAL) )
		{
			int nImage = -1;
			int nIndex = m_pLogList->GetItemCount();

			wxDateTime tNow = wxDateTime::Now();

			if ( m_fIconsLoaded )
			{
				if( msg.Contains(wxT("ERROR")) ) nImage = 2;
				else if( msg.Contains(wxT("WARNING")) ) nImage = 1;
				else nImage = 0;
			}

			m_pLogList->InsertItem(nIndex, wxT(" ") + msg, nImage);
			m_pLogList->SetItem(nIndex, 1, wxString::Format(wxT("%s"), tNow.Format(wxT("%H:%M:%S"), wxDateTime::CET).c_str()));

			// let the columns size themselves
			m_pLogList->SetColumnWidth(0, wxLIST_AUTOSIZE);
			m_pLogList->SetColumnWidth(1, wxLIST_AUTOSIZE);
		}
}

void udLog::OnRightClick(wxMouseEvent& event)
{
	if( m_pPopupMenu )
	{
		PopupMenu(m_pPopupMenu, event.GetPosition());
	}
}

void udLog::OnClear(wxCommandEvent& event)
{
	ClearMessages();
}
