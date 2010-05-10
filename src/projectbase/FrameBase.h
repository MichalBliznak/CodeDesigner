#ifndef _FRAME_BASE_H_
#define _FRAME_BASE_H_

#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/hashmap.h>
#include <wx/wxsf/wxShapeFramework.h>

#include "interfaces/Defs.h"

class WXDLLIMPEXP_CD udPaletteItem
{
public:

	enum PITYPE
	{
		pitTOOL,
		pitELEMENT,
		pitCONNECTION
	};

	udPaletteItem(long id, const wxString &icon, const wxString &desc, const wxString &className, const wxString &dataClassName, PITYPE type) :
m_nId(id), m_sIcon(icon), m_sDesc(desc), m_sClassName(className), m_sDataClassName(dataClassName), m_nType(type) {;}

    long m_nId;
	wxString m_sIcon;
    wxString m_sDesc;
    wxString m_sClassName;
    wxString m_sDataClassName;
    PITYPE m_nType;
};

WX_DECLARE_OBJARRAY_WITH_DECL( udPaletteItem, PaletteArray, class WXDLLIMPEXP_CD  );
WX_DECLARE_STRING_HASH_MAP_WITH_DECL( PaletteArray*, PalettesMap, class WXDLLIMPEXP_CD  );

// global stuff
extern WXDLLIMPEXP_CD PalettesMap m_mapElementPalettes;

WXDLLIMPEXP_CD udPaletteItem* GetPaletteTool(const wxString& className);
WXDLLIMPEXP_CD udPaletteItem* GetPaletteTool(int id);

// exported classes ////////////////////////////////////////////////////////////

class udWindowRecord : public xsSerializable
{
public:
	DECLARE_DYNAMIC_CLASS(udWindowRecord);
	
	udWindowRecord();
	udWindowRecord(const wxString& name);
	
	// data members accessors
	void SetPosition(const wxPoint& Position) {this->m_Position = Position;}
	void SetSize(const wxSize& Size) {this->m_Size = Size;}
	void SetName(const wxString& Name) {this->m_Name = Name;}
	const wxPoint& GetPosition() const {return m_Position;}
	const wxSize& GetSize() const {return m_Size;}
	const wxString& GetName() const {return m_Name;}
	
protected:
	// window attributes
	wxString m_Name;
	wxPoint m_Position;
	wxSize m_Size;
};

class WXDLLIMPEXP_CD udWindowManager : public wxObject
{
public:
	udWindowManager(wxWindow& wnd, const wxString& wndname);
	~udWindowManager();
	
	static void Clear();
	
protected:
	wxWindow *m_ManagedWindow;
	wxString m_Name;
	
	udWindowRecord* GetRecord(const wxString& wndname);
};

#endif //_FRAME_BASE_H_
