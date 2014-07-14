#ifndef __udxs2pg__
#define __udxs2pg__

#include <wx/filename.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include "wx/wxxmlserializer/XmlSerializer.h"

// pointer to function for conversion between PG and XS
typedef void (*IOFcn_t)(wxPropertyGrid*, const wxString&, xsProperty*);

// map for conversion functions
WX_DECLARE_STRING_HASH_MAP( IOFcn_t, IOFcnMap );
WX_DECLARE_STRING_HASH_MAP( wxString, NameMap );

WX_DECLARE_STRING_HASH_MAP( NameMap*, NameMaps );

class udXS2PG
{
public:
	// public data members accessors
	static IOFcn_t GetReadFcn( const wxString& propname ) { return m_mapReadFcn[propname]; }
	static IOFcn_t GetWriteFcn( const wxString& propname ) { return m_mapWriteFcn[propname]; }
	
	// public functions
	static void Initialize();
	static void CleanUp();
	
	static const wxString& GetFriendlyName( const wxString& field, const wxString& value );
	
	static void RegisterFriendlyName(const wxString& mapname, const wxString& origname, const wxString& friendlyname);
	static void UnregisterFriendlyName(const wxString& mapname, const wxString& origname);
	
protected:	
	// protected data members
	static IOFcnMap m_mapReadFcn;
	static IOFcnMap m_mapWriteFcn;
	static NameMaps m_mapMaps;
	
	// protected functions
	static void ReadBoolFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadIntFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadLongFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadStringFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadColourFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadFileNameFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadDirNameFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	static void ReadFontFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest);
	
	static void WriteBoolToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteIntToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteLongToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteStringToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteColourToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteFileNameToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteDirNameToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
	static void WriteFontToPG(wxPropertyGrid *dest, const wxString& propname, xsProperty *src);
};

#endif // __udxs2pg__
