#include "Language.h"
#include "ProjectBase.h"

#include <wx/arrimpl.cpp>
#include <wx/tokenzr.h>

WX_DEFINE_OBJARRAY(ValueTypeArray);

udLanguage::udLanguage()
{
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

    m_nStcLangType = wxSCI_LEX_NULL;
    m_sStcLangKeywords = wxT("");

    m_nIndentation = 0;
	m_nCodeBufferIndex = -1;
	
	m_fHasUserDataType = true;
	m_fHasSeparatedDecl = true;
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
	wxStringTokenizer tokenz( code, wxT("\n\r") );
	while( tokenz.HasMoreTokens() )
	{
		Indent();
		m_sOutBuffer << tokenz.GetNextToken();
		NewLine();
	}
}

