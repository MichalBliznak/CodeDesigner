#include "Language.h"
#include "ProjectBase.h"

#include <wx/arrimpl.cpp>
#include <wx/tokenzr.h>

WX_DEFINE_OBJARRAY(ValueTypeArray);

wxArrayString udLanguage::m_arrFormalDataTypes;

udLanguage::udLanguage()
{
	static bool fInitFormalTypeNames = true;
	
	udSettings &Settings = IPluginManager::Get()->GetAppSettings();
	
    m_sName = wxT("- Undefined language -");
    m_sDescription = wxT("Base language class implementation.");

    m_sOutBuffer = wxT("");

    m_sNewLineStr = wxT("\n");
	//for( int i = 0; i < Settings.GetProperty( wxT("Tabulator width") )->AsInt(); i++ ) m_sIndentStr << wxT(" ");
	if( Settings.GetProperty( wxT("Use tabulators") )->AsBool() )
	{
		m_sIndentStr = wxT("\t");
	}
	else
	{
		for( int i = 0; i < Settings.GetProperty( wxT("Indentation width") )->AsInt(); i++ ) m_sIndentStr << wxT(" ");
	}

    m_nStcLangType = wxSTC_LEX_NULL;
    m_sStcLangKeywords = wxT("");

    m_nIndentation = 0;
	m_nCodeBufferIndex = -1;
	
	m_fHasUserDataType = true;
	m_fHasSeparatedDecl = true;
	m_fHasClasses = false;
	
	if( fInitFormalTypeNames )
	{
		m_arrFormalDataTypes.Add(wxT("<user-defined>"));
		m_arrFormalDataTypes.Add(wxT("Bool"));
		m_arrFormalDataTypes.Add(wxT("UInt8"));
		m_arrFormalDataTypes.Add(wxT("UInt16"));
		m_arrFormalDataTypes.Add(wxT("UInt32"));
		m_arrFormalDataTypes.Add(wxT("Integer"));
		m_arrFormalDataTypes.Add(wxT("Long"));
		m_arrFormalDataTypes.Add(wxT("Real"));
		m_arrFormalDataTypes.Add(wxT("BigReal"));
		m_arrFormalDataTypes.Add(wxT("Char"));
		m_arrFormalDataTypes.Add(wxT("Void"));
		
		fInitFormalTypeNames = false;
	}
}

udLanguage::~udLanguage()
{
}

void udLanguage::PopCode()
{
	if( m_nCodeBufferIndex > -1 )
	{
		m_sOutBuffer = m_arrCodeBuffer[m_nCodeBufferIndex];
		m_nCodeBufferIndex--;
	}
}

void udLanguage::PushCode()
{
	m_nCodeBufferIndex++;
	
	m_arrCodeBuffer.SetCount(m_nCodeBufferIndex + 1);
	m_arrCodeBuffer[m_nCodeBufferIndex] = m_sOutBuffer;
	
	m_sOutBuffer.Clear();
}


void udLanguage::NewLine()
{
    m_sOutBuffer << m_sNewLineStr;
}

void udLanguage::Indent()
{
    for(int i = 0; i < m_nIndentation; i++)m_sOutBuffer << m_sIndentStr;
}

wxString udLanguage::GetDataTypeString(DATATYPE dt) const
{
    if( (size_t)dt >= m_arrDataTypes.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrDataTypes[(size_t)dt];
}

wxString udLanguage::GetFormalDataTypeString(DATATYPE dt)
{
    if( (size_t)dt >= m_arrFormalDataTypes.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrFormalDataTypes[(size_t)dt];
}

udValueType udLanguage::GetValueType(VALUETYPE vt) const
{
    if( (size_t)vt >= m_arrValueTypes.GetCount() )
    {
        return udValueType();
    }
    else
        return m_arrValueTypes[(size_t)vt];
}

wxString udLanguage::GetModifierString(DATAMODIFIER modif) const
{
    if( (size_t)modif >= m_arrDataModifiers.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrDataModifiers[(size_t)modif];
}

wxString udLanguage::GetModifierString(FCNMODIFIER modif) const
{
    if( (size_t)modif >= m_arrFcnModifiers.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrFcnModifiers[(size_t)modif];
}

wxString udLanguage::GetAccessTypeString(ACCESSTYPE at) const
{
    if( (size_t)at >= m_arrAccessTypes.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrAccessTypes[(size_t)at];
}

wxString udLanguage::GetExtension(FILEEXTENSION fe) const
{
    if( (size_t)fe >= m_arrFileExtensions.GetCount() )
    {
        return wxT("");
    }
    else
        return m_arrFileExtensions[(size_t)fe];
}

void udLanguage::WriteCodeBlocks(const wxString& code)
{
	wxStringTokenizer tokenz( code, wxT("\n"), wxTOKEN_RET_EMPTY );
	while( tokenz.HasMoreTokens() )
	{
		Indent();
		m_sOutBuffer << tokenz.GetNextToken();
		NewLine();
	}
}

wxString udLanguage::GetCommented(const wxString& txt)
{	
	int nCurrIndent = GetIndentation();
	SetIndentation( 0 );
	PushCode();
	
	this->MultiLineCommentCmd( txt );
	
	wxString sOut = GetCodeBuffer();
	
	PopCode();
	SetIndentation( nCurrIndent );
	
	return sOut;
}
