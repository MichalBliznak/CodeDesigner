#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "CPPLanguage.h"
#include <wx/tokenzr.h>

IMPLEMENT_DYNAMIC_CLASS(udCPPLanguage, udCLanguage);

udCPPLanguage::udCPPLanguage()
{
    m_sName = wxT("C++ Language");
    m_sDescription = wxT("C++ Language command processor.");
	
	m_fHasClasses = true;

    // initialize lexer
    m_nStcLangType = wxSTC_LEX_CPP;
    m_sStcLangKeywords = wxT( "asm auto bool break case catch char class const const_cast \
	                          continue default delete do double dynamic_cast else enum explicit \
	                          export extern false float for friend goto if inline int long \
	                          mutable namespace new operator private protected public register \
	                          reinterpret_cast return short signed sizeof static static_cast \
	                          struct switch template this throw true try typedef typeid \
	                          typename union unsigned using virtual void volatile wchar_t \
	                          while" );
	
    // initialize data types (keyword's order must corespond with DATATYPE enumeration)
	m_arrDataTypes[(int)DT_BOOL] = wxT("bool");
	
    // initialize data modifiers (keyword's order must corespond with FCNMODIFIER enumeration)
    m_arrFcnModifiers.Add(wxT("static")); // static function
    m_arrFcnModifiers.Add(wxT("virtual")); // virtual function
    m_arrFcnModifiers.Add(wxT("abstract")); // abstract function
    m_arrFcnModifiers.Add(wxT("const")); // const function
	
	// initialize access types (keyword's order must corespond with ACCESSTYPE enumeration)
	m_arrAccessTypes.Add(wxT("public"));
	m_arrAccessTypes.Add(wxT("protected"));
	m_arrAccessTypes.Add(wxT("private"));
	
	// initialize file extensions (keyword's order must corespond with FILEEXTENSION enumeration)
	m_arrFileExtensions.Clear();
	m_arrFileExtensions.Add(wxT(".h"));
	m_arrFileExtensions.Add(wxT(".cpp"));
}

udCPPLanguage::~udCPPLanguage()
{
}

void udCPPLanguage::ClassDeclCmd(const wxString& name, const wxString& parents)
{
	Indent();
	
	m_sOutBuffer << wxT("class ") << name;
	if( !parents.IsEmpty() )
	{
		m_sOutBuffer << wxT(" : ");
		
		wxStringTokenizer tokenz( parents, wxT(","), wxTOKEN_STRTOK );
		while( 1 )
		{
			m_sOutBuffer << wxT("public ") << tokenz.GetNextToken().Trim().Trim(false);
			
			if( tokenz.HasMoreTokens() ) m_sOutBuffer << wxT(", ");
			else
				break;
		}
	}
	
	NewLine();
}

void udCPPLanguage::ClassMemberFcnDeclCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params)
{
	if( modif == GetModifierString( FM_CONST ) )
	{
		Indent();
		
		wxString sDataType = type;
		sDataType.Trim().Trim(false);
		
		wxString sModif = modif;
		sModif.Trim().Trim(false);
		
		m_sOutBuffer << sDataType << wxT(" ") << name << wxT("( ") << params << wxT(" ) ") << sModif << wxT(";");
		
		NewLine();
	}
	else if( modif == GetModifierString( FM_ABSTRACT ) )
	{		
		Indent();
		
		wxString sDataType = type;
		sDataType.Trim().Trim(false);

		m_sOutBuffer << wxT("virtual ") << sDataType << wxT(" ") << name << wxT("( ") << params << wxT(" ) = 0;");
		
		NewLine();
	}
	else
		FunctionDeclCmd( modif + wxT(" ") + type, name, params );
}

void udCPPLanguage::ClassMemberFcnDefCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params)
{
	Indent();
	
	if( modif == GetModifierString( FM_CONST ) )
	{
		m_sOutBuffer << type << wxT(" ") << classname << wxT("::") << name << wxT("( ") << params << wxT(" )") << wxT(" ") << modif;
	}
	else
		m_sOutBuffer << type << wxT(" ") << classname << wxT("::") << name << wxT("( ") << params << wxT(" )");
	
	NewLine();
}

void udCPPLanguage::ClassConstructorDeclCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams)
{
	return FunctionDeclCmd( wxEmptyString, name, params );
}

void udCPPLanguage::ClassConstructorDefCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams)
{
	Indent();
	
	m_sOutBuffer << name << wxT("::") << name << wxT("( ") << params << wxT(" )");
	
	for(size_t i = 0; i < bases.GetCount(); i++)
	{
		if( i == 0)	m_sOutBuffer << wxT(" : ") << bases[i] << wxT("( ");
		else
			m_sOutBuffer << wxT(", ") << bases[i] << wxT("( ");
			
		m_sOutBuffer << basesparams[i] << wxT(" )");
	}
	
	NewLine();
}

void udCPPLanguage::ClassDestructorDeclCmd(const wxString& modif, const wxString& name, const wxString& parent)
{
	Indent();
	
	if( modif.IsEmpty() ) m_sOutBuffer << wxT("~") << name << wxT("();");
	else
		 m_sOutBuffer << modif << wxT(" ~") << name << wxT("();");
	
	NewLine();
}

void udCPPLanguage::ClassDestructorDefCmd(const wxString& modif, const wxString& name, const wxString& parent)
{
	Indent();
	
	m_sOutBuffer << name << wxT("::~") << name << wxT("()");
	
	NewLine();
}

void udCPPLanguage::ClassInstanceCmd(const wxString& instname, const wxString& classname, const wxString& params, bool dynamic)
{
	Indent();
	
	if( dynamic )
	{
		m_sOutBuffer << classname << wxT(" *") << instname << wxT(" = new ") << classname << wxT("( ") << params << wxT(" );");
	}
	else
	{
		if( params.IsEmpty() ) m_sOutBuffer << classname  << wxT(" ") << instname <<  wxT(";");
		else
			m_sOutBuffer << classname << wxT(" ") << instname << wxT("( ") << params << wxT(" );");
	}
	
	NewLine();
}
