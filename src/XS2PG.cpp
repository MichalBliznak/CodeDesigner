#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "XS2PG.h"

// static members ///////////////////////////////////////////////////////////////////////////////////////

IOFcnMap udXS2PG::m_mapReadFcn;
IOFcnMap udXS2PG::m_mapWriteFcn;
NameMaps udXS2PG::m_mapMaps;

// constructor and destructor ///////////////////////////////////////////////////////////////////////////


// public functions /////////////////////////////////////////////////////////////////////////////////////

void udXS2PG::CleanUp()
{
	wxArrayInt arrAlreadyDeleted;
	
	m_mapReadFcn.clear();
	m_mapWriteFcn.clear();
	
	NameMaps::iterator it;
	for( it = m_mapMaps.begin(); it != m_mapMaps.end(); ++it )
	{
		if( it->second && (arrAlreadyDeleted.Index((wxUIntPtr)it->second) == wxNOT_FOUND) )
		{
			it->second->clear();
			arrAlreadyDeleted.Add( (wxUIntPtr)it->second );
			delete it->second;
		}
	}
	m_mapMaps.clear();
}

void udXS2PG::Initialize()
{
	NameMap *pMap;
	
	// initialize conversion functions maps
	m_mapReadFcn[wxT("bool")] = ReadBoolFromPG;
	m_mapReadFcn[wxT("int")] = ReadIntFromPG;
	m_mapReadFcn[wxT("long")] = ReadLongFromPG;
	m_mapReadFcn[wxT("string")] = ReadStringFromPG;
	m_mapReadFcn[wxT("colour")] = ReadColourFromPG;
	m_mapReadFcn[wxT("filename")] = ReadFileNameFromPG;
	m_mapReadFcn[wxT("dirname")] = ReadDirNameFromPG;
	m_mapReadFcn[wxT("font")] = ReadFontFromPG;
	
	m_mapWriteFcn[wxT("bool")] = WriteBoolToPG;
	m_mapWriteFcn[wxT("int")] = WriteIntToPG;
	m_mapWriteFcn[wxT("long")] = WriteLongToPG;
	m_mapWriteFcn[wxT("string")] = WriteStringToPG;
	m_mapWriteFcn[wxT("colour")] = WriteColourToPG;
	m_mapWriteFcn[wxT("filename")] = WriteFileNameToPG;
	m_mapWriteFcn[wxT("dirname")] = WriteDirNameToPG;
	m_mapWriteFcn[wxT("font")] = WriteFontToPG;
	
	// friendly class names
	pMap = new NameMap();
	m_mapMaps[wxT("classname")] = pMap;
	m_mapMaps[wxT("active_generator")] = pMap;
	m_mapMaps[wxT("active_algorithm")] = pMap;
	
	// initialize friendly class names
	(*pMap)[wxT("udRootItem")] = wxT("Project root");
	(*pMap)[wxT("udPackageItem")] = wxT("Package");
	(*pMap)[wxT("udCodePackageItem")] = wxT("Code package");
	(*pMap)[wxT("udDiagramItem")] = wxT("Diagram");
	(*pMap)[wxT("udDiagElementItem")] = wxT("Diagram element");
	(*pMap)[wxT("udNoteElementItem")] = wxT("Note element");
	(*pMap)[wxT("udNoteConnElementItem")] = wxT("Note connection element");
	(*pMap)[wxT("udGroupElementItem")] = wxT("Group element");
		
	(*pMap)[wxT("udGenericVariableItem")] = wxT("Generic variable");
	(*pMap)[wxT("udGenericFunctionItem")] = wxT("Generic function");
	(*pMap)[wxT("udParamItem")] = wxT("Function parameter");
	(*pMap)[wxT("udSubDiagramItem")] = wxT("Sub diagram");
	
	// boolean flag
	pMap = new NameMap();
	m_mapMaps[wxT("inline")] = pMap;
	m_mapMaps[wxT("generate_code")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("False");
	(*pMap)[wxT("1")] = wxT("True");
	
	// declaration places
	pMap = new NameMap();
	m_mapMaps[wxT("user_decl_place")] = pMap;
	m_mapMaps[wxT("user_retval_decl_place")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("Built-in");
	(*pMap)[wxT("1")] = wxT("Defined in editor");
	(*pMap)[wxT("2")] = wxT("Defined in header file");
	
	// value type
	pMap = new NameMap();
	m_mapMaps[wxT("value_type")] = pMap;
	m_mapMaps[wxT("retval_value_type")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("VALUE");
	(*pMap)[wxT("1")] = wxT("POINTER");
	(*pMap)[wxT("2")] = wxT("REFERENCE");
	
	// data type
	pMap = new NameMap();
	m_mapMaps[wxT("data_type")] = pMap;
	m_mapMaps[wxT("retval_data_type")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("<user-defined>");
	(*pMap)[wxT("1")] = wxT("BOOL");
	(*pMap)[wxT("2")] = wxT("UINT8");
	(*pMap)[wxT("3")] = wxT("UINT16");
	(*pMap)[wxT("4")] = wxT("UINT32");
	(*pMap)[wxT("5")] = wxT("INT");
	(*pMap)[wxT("6")] = wxT("LONG");
	(*pMap)[wxT("7")] = wxT("REAL");
	(*pMap)[wxT("8")] = wxT("BIG REAL");
	(*pMap)[wxT("9")] = wxT("CHAR");
	(*pMap)[wxT("10")] = wxT("VOID");
	
	// data modifier type
	pMap = new NameMap();
	m_mapMaps[wxT("data_modifier")] = pMap;
	m_mapMaps[wxT("retval_data_modifier")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("<none>");
	(*pMap)[wxT("1")] = wxT("SHORT");
	(*pMap)[wxT("2")] = wxT("LONG");
	(*pMap)[wxT("3")] = wxT("SIGNED");
	(*pMap)[wxT("4")] = wxT("UNSIGNED");
	(*pMap)[wxT("5")] = wxT("STATIC");
	(*pMap)[wxT("6")] = wxT("CONST");
	(*pMap)[wxT("7")] = wxT("EXTERN");
	(*pMap)[wxT("8")] = wxT("VOLATILE");
	
	// function modifier type
	pMap = new NameMap();
	m_mapMaps[wxT("function_modifier")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("<none>");
	(*pMap)[wxT("1")] = wxT("STATIC");
	(*pMap)[wxT("2")] = wxT("VIRTUAL");
	(*pMap)[wxT("3")] = wxT("ABSTRACT");
	(*pMap)[wxT("4")] = wxT("CONST");
	
	// access type
	pMap = new NameMap();
	m_mapMaps[wxT("access_type")] = pMap;
	
	(*pMap)[wxT("0")] = wxT("PUBLIC");
	(*pMap)[wxT("1")] = wxT("PROTECTED");
	(*pMap)[wxT("2")] = wxT("PRIVATE");
}

const wxString& udXS2PG::GetFriendlyName(const wxString& field, const wxString& value)
{	
	NameMap *pMap = m_mapMaps[field];
	
	if( pMap && ((*pMap)[value]!=wxEmptyString) )
	{
		return (*pMap)[value];
	}
	else
		return value;
}

void udXS2PG::RegisterFriendlyName(const wxString& mapname, const wxString& origname, const wxString& friendlyname)
{
	NameMap *pMap = m_mapMaps[mapname];

	if( !pMap )
	{
		pMap = new NameMap();
		m_mapMaps[mapname] = pMap;
	}
	
	(*pMap)[origname] = friendlyname;
}

void udXS2PG::UnregisterFriendlyName(const wxString& mapname, const wxString& origname)
{
	NameMaps::iterator it = m_mapMaps.find(mapname);

	if( it != m_mapMaps.end() )
	{
		it->second->erase( mapname );
	}
}

// protected functions //////////////////////////////////////////////////////////////////////////////////

void udXS2PG::ReadBoolFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty* dest)
{
	*(bool*)dest->m_pSourceVariable = src->GetPropertyValueAsBool( propname );
}

void udXS2PG::ReadIntFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty* dest)
{
	*(int*)dest->m_pSourceVariable = src->GetPropertyValueAsInt( propname );
}

void udXS2PG::ReadLongFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty* dest)
{
	*(long*)dest->m_pSourceVariable = src->GetPropertyValueAsLong( propname );
}

void udXS2PG::ReadColourFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest)
{
	/*wxVariant value = src->GetPropertyValue( propname ); 
	*(wxColour*)dest->m_pSourceVariable = *(wxColour*) WX_PG_VARIANT_TO_WXOBJECT( value, wxColour );*/
	
	wxColour col;
	col << src->GetProperty( propname )->GetValue();
	
	*(wxColour*)dest->m_pSourceVariable = col;
}

void udXS2PG::ReadFileNameFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest)
{
	*(wxFileName*)dest->m_pSourceVariable = wxFileName( src->GetPropertyValueAsString( propname ) );
}

void udXS2PG::ReadDirNameFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest)
{
	*(wxFileName*)dest->m_pSourceVariable = wxFileName::DirName( src->GetPropertyValueAsString( propname ) );
}

void udXS2PG::ReadStringFromPG(wxPropertyGrid *src, const wxString& propname, xsProperty *dest)
{
	*(wxString*)dest->m_pSourceVariable = src->GetPropertyValueAsString( propname );
}

void udXS2PG::WriteBoolToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{

	dest->Append( new wxBoolProperty( propname, wxPG_LABEL, *(bool*)src->m_pSourceVariable ) );
}

void udXS2PG::WriteColourToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxColourProperty( propname, wxPG_LABEL, *(wxColour*)src->m_pSourceVariable ) );
}

void udXS2PG::WriteFileNameToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxFileProperty( propname, wxPG_LABEL, ((wxFileName*)src->m_pSourceVariable)->GetPath() ) );
}

void udXS2PG::WriteDirNameToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxDirProperty( propname, wxPG_LABEL, ((wxFileName*)src->m_pSourceVariable)->GetPath() ) );
}

void udXS2PG::WriteStringToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxStringProperty( propname, wxPG_LABEL, *(wxString*)src->m_pSourceVariable ) );
}

void udXS2PG::WriteIntToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxIntProperty( propname, wxPG_LABEL, *(int*)src->m_pSourceVariable ) );
}

void udXS2PG::WriteLongToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	if( propname != wxT("id") ) dest->Append( new wxIntProperty( propname, wxPG_LABEL, *(long*)src->m_pSourceVariable ) );
}

void udXS2PG::ReadFontFromPG(wxPropertyGrid* src, const wxString& propname, xsProperty* dest)
{	
	wxFont font;
	font << src->GetProperty( propname )->GetValue();
	
	*(wxFont*)dest->m_pSourceVariable = font;

	/*wxFontPropertyValue* pFontVal = wxDynamicCast( src->GetPropertyValueAsWxObjectPtr( src->GetPropertyByName( propname ) ), wxFontPropertyValue );
	if( pFontVal )
	{		
		*(wxFont*)dest->m_pSourceVariable = wxFont( pFontVal->m_pointSize,
													pFontVal->m_family,
													pFontVal->m_style,
													pFontVal->m_weight,
													pFontVal->m_underlined,
													pFontVal->m_faceName);
	}*/
}

void udXS2PG::WriteFontToPG(wxPropertyGrid* dest, const wxString& propname, xsProperty* src)
{
	dest->Append( new wxFontProperty( propname, wxPG_LABEL, *(wxFont*)src->m_pSourceVariable ) );
}
