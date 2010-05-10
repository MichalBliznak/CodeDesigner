#include "SettingsBase.h"
#include <wx/wfstream.h>

/////////////////////////////////////////////////////////////////////////////////////
// xsFilePathPropIO class ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// define class encapsulating custom data format handler
XS_DEFINE_IO_HANDLER(wxFileName, xsFileNamePropIO);

// two following static member functions of the data handler class MUST be defined manualy:

wxString xsFileNamePropIO::ToString(const wxFileName& value)
{
	return value.GetPath();
}

// T xsPropIO::FromString(const wxString& value) -> converts data from given string representation to its relevant value
wxFileName xsFileNamePropIO::FromString(const wxString& value)
{
	return wxFileName( value );
}

/////////////////////////////////////////////////////////////////////////////////////
// xsDirPathPropIO class ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

// define class encapsulating custom data format handler
XS_DEFINE_IO_HANDLER(wxFileName, xsDirNamePropIO);

// two following static member functions of the data handler class MUST be defined manualy:

wxString xsDirNamePropIO::ToString(const wxFileName& value)
{
	return value.GetPath();
}

wxFileName xsDirNamePropIO::FromString(const wxString& value)
{
	if( value.Right(1) != wxFileName::GetPathSeparator() )
	{
		return wxFileName( value + wxFileName::GetPathSeparator() );
	}
	else
		return wxFileName( value );
}

/////////////////////////////////////////////////////////////////////////////////////
// udSettingsCathegory class ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udSettingsCategory, xsSerializable);

udSettingsCategory::udSettingsCategory()
{
	m_sName = wxT("Category");
}

udSettingsCategory::udSettingsCategory(const wxString& name)
{
	m_sName = name;
}

udSettingsCategory::~udSettingsCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udHiddenCathegory class //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC_CLASS(udHiddenCategory, udSettingsCategory);

udHiddenCategory::udHiddenCategory()
{
	m_sName = wxT("Hidden category");
}

udHiddenCategory::udHiddenCategory(const wxString& name)
{
	m_sName = name;
}

udHiddenCategory::~udHiddenCategory()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// udSettings class /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

udSettings::udSettings()
{
}

udSettings::~udSettings()
{
}

// public functions //////////////////////////////////////////////////////////////////

xsProperty* udSettings::GetProperty(const wxString& name)
{
	udSettingsCategory *pCategory;
	xsProperty *pProperty;
	
	SerializableList lstCategories;
	GetItems( CLASSINFO(udSettingsCategory), lstCategories );
	
	SerializableList::compatibility_iterator node = lstCategories.GetFirst();
	while( node )
	{
		pCategory = (udSettingsCategory*)node->GetData();
		
		pProperty = pCategory->GetProperty( name );
		if( pProperty ) return pProperty;
		
		node = node->GetNext();
	}
	
	return NULL;
}

udSettingsCategory* udSettings::GetCategory(const wxString& name)
{
	SerializableList lstCategories;
	GetItems( CLASSINFO(udSettingsCategory), lstCategories );
	
	SerializableList::compatibility_iterator node = lstCategories.GetFirst();
	while( node )
	{
		if( ((udSettingsCategory*)node->GetData())->GetName() == name ) return (udSettingsCategory*)node->GetData();
		
		node = node->GetNext();
	}
	
	return NULL;
}

wxString udSettings::GetPropertyAsString(const wxString& name, const wxString& defval)
{
	xsProperty *pProperty = GetProperty( name );
	wxASSERT( pProperty );
	
	if( pProperty )	return pProperty->ToString();
	else
		return defval;
}

bool udSettings::DeserializeFromXml(const wxString& file)
{
	if( wxFileExists(file) )
	{
		wxFileInputStream instream(file);
		return udSettings::DeserializeFromXml( instream );
	}
	else
	{
		this->CreateCategories();
		return false;
	}
}

bool udSettings::DeserializeFromXml(wxInputStream& instream)
{
	if( instream.IsOk() )
	{
		if( !wxXmlSerializer::DeserializeFromXml( instream ) )
		{
			RemoveAll();
			this->CreateCategories();
		}
		else
			return true;
	}
	else
		this->CreateCategories();
		
	return false;
}
