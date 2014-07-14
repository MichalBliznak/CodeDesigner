#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "CLanguage.h"
#include <wx/tokenzr.h>

IMPLEMENT_DYNAMIC_CLASS(udCLanguage, udLanguage);

udCLanguage::udCLanguage()
{
    m_sName = wxT("Ansi C Language");
    m_sDescription = wxT("Ansi C Language command processor.");

    // initialize lexer
    m_nStcLangType = wxSTC_LEX_CPP;
    m_sStcLangKeywords = wxT( "asm auto bool break case catch char const const_cast \
	                          continue default do double dynamic_cast else enum explicit \
	                          export extern false float for goto if int long \
	                          mutable register \
	                          reinterpret_cast return short signed sizeof static static_cast \
	                          struct switch true typedef typeid \
	                          typename union unsigned using void volatile wchar_t \
	                          while" );

    // initialize data types (keyword's order must corespond with DATATYPE enumeration)
    m_arrDataTypes.Add(wxT("<user-defined>")); // user-defined
    m_arrDataTypes.Add(wxT("unsigned char")); // bool
    m_arrDataTypes.Add(wxT("unsigned char")); // 8-bit unsigned integer
    m_arrDataTypes.Add(wxT("unsigned int")); // 16-bit unsigned integer
    m_arrDataTypes.Add(wxT("unsigned long")); // 32-bit unsigned integer
    m_arrDataTypes.Add(wxT("int")); // integer
    m_arrDataTypes.Add(wxT("long")); // long integer
    m_arrDataTypes.Add(wxT("float")); // real
    m_arrDataTypes.Add(wxT("double")); // long real
    m_arrDataTypes.Add(wxT("char")); // char
    m_arrDataTypes.Add(wxT("void")); // void
	
	// initialize value types
	m_arrValueTypes.Add(udValueType(wxT("Value"), wxT(""))); // value
	m_arrValueTypes.Add(udValueType(wxT("Pointer"), wxT("*"))); // value
	m_arrValueTypes.Add(udValueType(wxT("Reference"), wxT("&"))); // value
	
    // initialize data modifiers (keyword's order must corespond with DATAMODIFIER enumeration)
    m_arrDataModifiers.Add(wxT("<none>")); // empty modificator
    m_arrDataModifiers.Add(wxT("short")); // short modificator
    m_arrDataModifiers.Add(wxT("long")); // long modificator
    m_arrDataModifiers.Add(wxT("signed")); // signed modificator
    m_arrDataModifiers.Add(wxT("unsigned")); // unsigned modificator
    m_arrDataModifiers.Add(wxT("static")); // static modificator
    m_arrDataModifiers.Add(wxT("const")); // const modificator
    m_arrDataModifiers.Add(wxT("extern")); // extern modificator
    m_arrDataModifiers.Add(wxT("volatile")); // volatile modificator
	
    // initialize data modifiers (keyword's order must corespond with FCNMODIFIER enumeration)
    m_arrFcnModifiers.Add(wxT("<none>")); // empty modificator
	
	// initialize file extensions (keyword's order must corespond with FILEEXTENSION enumeration)
	m_arrFileExtensions.Add(wxT(".h"));
	m_arrFileExtensions.Add(wxT(".c"));
}

udCLanguage::~udCLanguage()
{
}

wxString udCLanguage::MakeValidIdentifier(const wxString& name) const
{
    wxChar zn;
    wxString out;
    bool fFirstAlpha = false;

    for(unsigned int i = 0; i < name.Len(); i++)
    {
        zn = name[i];
        if( ((zn >= '0') && (zn <= '9')) && !fFirstAlpha )
        {
            out << wxT("_");
        }
        else
        {
            fFirstAlpha = true;
            if( ((zn >= 'a') && (zn <= 'z')) ||
                ((zn >= 'A') && (zn <= 'Z')) ||
                ((zn >= '0') && (zn <= '9')) ||
                (zn == '[') ||
                (zn == ']') ||
                (zn == '_') )
            {
                out << zn;
            }
            else
                out << wxT("_");
        }
    }

    return out;
}

void udCLanguage::BeginCmd()
{
    Indent();
    m_sOutBuffer << wxT("{");
    IncIndentation();
    NewLine();
}
void udCLanguage::BreakCmd()
{
    Indent();
    m_sOutBuffer << wxT("break;");
    NewLine();
}

void udCLanguage::CaseCmd(const wxString& id)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("case %s:"), id.c_str());
    NewLine();
}

void udCLanguage::ContinueCmd()
{
    Indent();
    m_sOutBuffer << wxT("continue;");
    NewLine();
}

void udCLanguage::DoCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("while( %s )"), cond.c_str());
    NewLine();
}

void udCLanguage::ElseCmd()
{
    Indent();
    m_sOutBuffer << wxT("else");
    NewLine();
}

void udCLanguage::ElseIfCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("else if( %s )"), cond.c_str());
    NewLine();
}

void udCLanguage::EndCmd()
{
    DecIndentation();
    Indent();
    m_sOutBuffer << wxT("}");
    NewLine();
}

void udCLanguage::ForCmd(const wxString& init, const wxString& cond, const wxString& action)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("for( %s;%s;%s )"), init.c_str(), cond.c_str(), action.c_str());
    NewLine();
}

void udCLanguage::FunctionDeclCmd(const wxString& rettype, const wxString& name, const wxString& args )
{
    Indent();
	
	wxString sDataType = rettype;
	sDataType.Trim().Trim(false);
	
    m_sOutBuffer << sDataType << wxT(" ") << name << wxT("( ") << args << wxT(" );");
	
    NewLine();
}

void udCLanguage::FunctionDefCmd(const wxString& rettype, const wxString& name, const wxString& args )
{
    Indent();
	
	wxString sDataType = rettype;
	sDataType.Trim().Trim(false);
	
    m_sOutBuffer << sDataType << wxT(" ") << name << wxT("( ") << args << wxT(" )");
	
    NewLine();
}

void udCLanguage::FunctionCallCmd(const wxString& name, const wxString& args)
{
    Indent();
    m_sOutBuffer << name << wxT("( ") << args << wxT(" );");
    NewLine();
}

void udCLanguage::GotoCmd(const wxString& label)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("goto %s;"), label.c_str());
    NewLine();
}

void udCLanguage::LabelCmd(const wxString& name)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("%s:"), name.c_str());
    NewLine();
}

void udCLanguage::IfCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("if( %s )"), cond.c_str());
    NewLine();
}

void udCLanguage::InfiniteLoopCmd()
{
    Indent();
    m_sOutBuffer << wxT("for( ;; )");
    NewLine();
}

void udCLanguage::MultiLineCommentCmd(const wxString& msg)
{
	bool fFirstLine = true;
	
    wxStringTokenizer tkz(msg, wxT("\n"), wxTOKEN_RET_EMPTY);

    Indent();
    m_sOutBuffer << wxT("/*");

    while ( tkz.HasMoreTokens() )
    {
        Indent();
		if( !fFirstLine ) m_sOutBuffer << wxT(" *");
		else
			fFirstLine = false;
        m_sOutBuffer << tkz.GetNextToken();
        NewLine();
    }

    Indent();
    m_sOutBuffer << wxT(" */");
    NewLine();
}

void udCLanguage::ReturnCmd(const wxString& val)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("return %s;"), val.c_str());
    NewLine();
}

void udCLanguage::SingleLineCommentCmd(const wxString& msg)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("/* %s */"), msg.c_str());
    NewLine();
}

void udCLanguage::SwitchCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("switch( %s )"), cond.c_str());
    NewLine();
}

void udCLanguage::VariableAssignCmd(const wxString& name, const wxString& value)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("%s = %s;"), name.c_str(), value.c_str());
    NewLine();
}

void udCLanguage::VariableDeclAssignCmd(const wxString& type, const wxString& name, const wxString& value)
{
    Indent();
	
	wxString sDataType = type;
	sDataType.Trim().Trim(false);
	
    m_sOutBuffer << wxString::Format(wxT("%s %s = %s;"), sDataType.c_str(), name.c_str(), value.c_str());
	
    NewLine();
}

void udCLanguage::VariableDeclCmd(const wxString& type, const wxString& name)
{
    Indent();
	
	wxString sDataType = type;
	sDataType.Trim().Trim(false);
	
    m_sOutBuffer << sDataType << wxT(" ") << name << wxT(";");	
	
    NewLine();
}

void udCLanguage::WhileCmd(const wxString& cond)
{
    DoCmd(cond);
}

void udCLanguage::DefineCmd(const wxString& macro, const wxString& content)
{
	Indent();
	m_sOutBuffer << wxString::Format( wxT("#define %s %s"), macro.c_str(), content.c_str() );
	NewLine();
}

void udCLanguage::IncludeCmd(const wxString& header)
{
	Indent();
	m_sOutBuffer << wxString::Format( wxT("#include %s"), header.c_str() );
	NewLine();
}

void udCLanguage::TypedefCmd(const wxString& type, const wxString& decl)
{
	Indent();
	m_sOutBuffer << wxString::Format( wxT("typedef %s %s;"), decl.c_str(), type.c_str() );
	NewLine();
}


void udCLanguage::EnumCmd(const wxString& name, const wxArrayString& values, const wxString& instname)
{
	Indent();
	
	m_sOutBuffer << wxT("enum ") << name << wxT(" {");
	
    IncIndentation();
    NewLine();
	
	for( size_t i = 0; i < values.GetCount(); ++i )
	{
		if( i < values.GetCount()-1 ) WriteCodeBlocks( values[i] + wxT(",") );
		else
			WriteCodeBlocks( values[i] );
	}
	
	EndCmd();
	m_sOutBuffer.Trim();
	
	if( !instname.IsEmpty() ) m_sOutBuffer << wxT(" ") << instname;
	m_sOutBuffer << wxT(";");
	
	NewLine();	
}
