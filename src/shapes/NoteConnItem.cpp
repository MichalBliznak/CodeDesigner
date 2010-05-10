#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "shapes/NoteConnItem.h"

XS_IMPLEMENT_CLONABLE_CLASS(uddNoteConnItem, wxSFLineShape);

uddNoteConnItem::uddNoteConnItem()
{
    Initialize();
}

uddNoteConnItem::uddNoteConnItem(const uddNoteConnItem &obj)
: wxSFLineShape(obj)
{
}

uddNoteConnItem::~uddNoteConnItem()
{
}

void uddNoteConnItem::Initialize()
{
    // initialize shape
	/*m_pGuard->Show(false);
	m_pGuard->Activate(false);
    m_pGuard->SetText(wxT("<< >>"));*/

	AcceptConnection(wxT("uddNoteConnItem"));
    AcceptSrcNeighbour(wxT("All"));
    AcceptTrgNeighbour(wxT("All"));

	m_Pen = wxPen(wxColour(100, 100, 100), 1, wxDOT);
}


