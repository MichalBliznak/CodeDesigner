#include "wx_pch.h"

#ifdef _DEBUG_MSVC
#define new DEBUG_NEW
#endif

#include "PythonLanguage.h"
#include <wx/tokenzr.h>

IMPLEMENT_DYNAMIC_CLASS(udPythonLanguage, udLanguage);

udPythonLanguage::udPythonLanguage()
{
    m_sName = wxT("Python Language");
    m_sDescription = wxT("Python Language command processor.");

    m_nStcLangType = wxSTC_LEX_PYTHON;
    m_sStcLangKeywords = wxT( "and assert break class continue def del elif else \
                                except exec finally for from global if import in \
                                is lambda not or pass print raise return try while" );
								
	m_fHasUserDataType = false;
	m_fHasSeparatedDecl = false;
	m_fHasClasses = true;
	
	// initialize access types (keyword's order must corespond with ACCESSTYPE enumeration)
	m_arrAccessTypes.Add(wxT("public"));
	m_arrAccessTypes.Add(wxT("protected"));
	m_arrAccessTypes.Add(wxT("private"));
	
	// initialize file extensions (keyword's order must corespond with FILEEXTENSION enumeration)
	m_arrFileExtensions.Add(wxT(""));
	m_arrFileExtensions.Add(wxT(".py"));
}

udPythonLanguage::~udPythonLanguage()
{
}

wxString udPythonLanguage::MakeValidIdentifier(const wxString& name) const
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

void udPythonLanguage::BeginCmd()
{
    IncIndentation();
}

void udPythonLanguage::BreakCmd()
{
    Indent();
    m_sOutBuffer << wxT("break");
    NewLine();
}

void udPythonLanguage::CaseCmd(const wxString& id)
{
    Indent();
    m_sOutBuffer << wxT(" - NOT SUPPORTED - ");
    NewLine();
}

void udPythonLanguage::ContinueCmd()
{
    Indent();
    m_sOutBuffer << wxT("continue");
    NewLine();
}

void udPythonLanguage::DoCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("while( %s ):"), cond.c_str());
    NewLine();
}

void udPythonLanguage::ElseCmd()
{
    Indent();
    m_sOutBuffer << wxT("else:");
    NewLine();
}

void udPythonLanguage::ElseIfCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("elif( %s ):"), cond.c_str());
    NewLine();
}

void udPythonLanguage::EndCmd()
{
    DecIndentation();
	
	wxString appex = m_sOutBuffer.Right( 2 * m_sNewLineStr.Len() );
	if( appex != (m_sNewLineStr + m_sNewLineStr) ) NewLine();
}

void udPythonLanguage::ForCmd(const wxString& init, const wxString& cond, const wxString& action)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("for %s in %s:"), init.c_str(), cond.c_str());
    NewLine();
}

void udPythonLanguage::FunctionDeclCmd(const wxString& rettype, const wxString& name, const wxString& args )
{
	// do nothing
}

void udPythonLanguage::FunctionDefCmd(const wxString& rettype, const wxString& name, const wxString& args )
{
    Indent();
    m_sOutBuffer << wxT("def ") << name << wxT("( ") << args << wxT(" ):");
    NewLine();
}

void udPythonLanguage::FunctionCallCmd(const wxString& name, const wxString& args)
{
    Indent();
    m_sOutBuffer << name << wxT("( ") << args << wxT(" )");
    NewLine();
}

void udPythonLanguage::GotoCmd(const wxString& label)
{
    Indent();
    m_sOutBuffer << wxT(" - NOT SUPPORTED - ");
    NewLine();
}

void udPythonLanguage::LabelCmd(const wxString& name)
{
    Indent();
    m_sOutBuffer << wxT(" - NOT SUPPORTED - ");
    NewLine();
}

void udPythonLanguage::IfCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("if( %s ):"), cond.c_str());
    NewLine();
}

void udPythonLanguage::InfiniteLoopCmd()
{
    Indent();
    m_sOutBuffer << wxT("while( True ):");
    NewLine();
}

void udPythonLanguage::MultiLineCommentCmd(const wxString& msg)
{
    wxStringTokenizer tkz(msg, wxT("\n"), wxTOKEN_RET_EMPTY);

    Indent();
    m_sOutBuffer << wxT("\"\"\" ");

    while ( tkz.HasMoreTokens() )
    {
        Indent();
        m_sOutBuffer << tkz.GetNextToken();

        if(tkz.HasMoreTokens()) NewLine();
    }

    m_sOutBuffer << wxT(" \"\"\"");
    NewLine();
}

void udPythonLanguage::ReturnCmd(const wxString& val)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("return %s"), val.c_str());
    NewLine();
}

void udPythonLanguage::SingleLineCommentCmd(const wxString& msg)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("# %s"), msg.c_str());
    NewLine();
}

void udPythonLanguage::SwitchCmd(const wxString& cond)
{
    Indent();
    m_sOutBuffer << wxT(" - NOT SUPPORTED - ");
    NewLine();
}

void udPythonLanguage::VariableAssignCmd(const wxString& name, const wxString& value)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("%s = %s"), name.c_str(), value.c_str());
    NewLine();
}

void udPythonLanguage::VariableDeclAssignCmd(const wxString& type, const wxString& name, const wxString& value)
{
    Indent();
    m_sOutBuffer << wxString::Format(wxT("%s = %s"), name.c_str(), value.c_str());
    NewLine();
}

void udPythonLanguage::VariableDeclCmd(const wxString& type, const wxString& name)
{
    Indent();
    m_sOutBuffer << name;
    NewLine();
}

void udPythonLanguage::WhileCmd(const wxString& cond)
{
    DoCmd(cond);
}

void udPythonLanguage::DefineCmd(const wxString& macro, const wxString& content)
{
    Indent();
    m_sOutBuffer << wxString::Format( wxT("%s = %s"), macro.c_str(), content.c_str() );
    NewLine();
}

void udPythonLanguage::IncludeCmd(const wxString& header)
{
    Indent();
    m_sOutBuffer << wxString::Format( wxT("import %s"), header.c_str() );
    NewLine();
}

void udPythonLanguage::TypedefCmd(const wxString& type, const wxString& decl)
{
    Indent();
    m_sOutBuffer << wxT(" - NOT SUPPORTED - ");
    NewLine();
}

void udPythonLanguage::ClassDeclCmd(const wxString& name, const wxString& parents)
{
	Indent();
	
	if( parents.IsEmpty() )
	{
		m_sOutBuffer << wxT("class ") << name << wxT(":");
	}
	else
		m_sOutBuffer << wxT("class ") << name << wxT("( ") << parents << wxT(" ):");
		
	NewLine();
}

void udPythonLanguage::ClassMemberFcnDefCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params)
{
    Indent();
	
	m_sOutBuffer << wxT("def ") << name << wxT("( ") << params << wxT(" ):");
		
    NewLine();
}


void udPythonLanguage::ClassMemberFcnDeclCmd(const wxString& modif, const wxString& type, const wxString& classname, const wxString& name, const wxString& params)
{
    Indent();
	
	if( !params.IsEmpty() )
	{
		m_sOutBuffer << wxT("def ") << name << wxT("( self, ") << params << wxT(" ):");
	}
	else
		m_sOutBuffer << wxT("def ") << name << wxT("( self ):");
		
    NewLine();
}

void udPythonLanguage::ClassConstructorDeclCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams)
{
	Indent();
	
	if( !params.IsEmpty() )
	{
		m_sOutBuffer << wxT("def __init__( self, ") << params << wxT(" ):");
	}
	else
		m_sOutBuffer << wxT("def __init__( self ):");
		
	NewLine();
		
	if( !bases.IsEmpty() )
	{
		Indent();
			
		for(size_t i = 0; i < bases.GetCount(); i++)
		{
			if( !basesparams[i].IsEmpty() )
			{
				m_sOutBuffer << bases[i] << wxT(".__init__( self, ") << basesparams[i] << wxT(" )");
			}
			else
				m_sOutBuffer << bases[i] << wxT(".__init__( self )");
		}

		NewLine();
	}
		
    NewLine();	
	
}

void udPythonLanguage::ClassConstructorDefCmd(const wxString& name, const wxString& params, const wxArrayString& bases, const wxArrayString& basesparams)
{
}

void udPythonLanguage::ClassDestructorDeclCmd(const wxString& modif, const wxString& name, const wxString& parent)
{
	Indent();
	
	m_sOutBuffer << wxT("def __del__( self ):");
		
	NewLine();
		
	if( !parent.IsEmpty() )
	{
		IncIndentation();
		Indent();
		
		m_sOutBuffer << parent << wxT(".__del__( self )");
		
		DecIndentation();
		NewLine();
	}
		
    NewLine();	
}

void udPythonLanguage::ClassDestructorDefCmd(const wxString& modif, const wxString& name, const wxString& parent)
{
}

void udPythonLanguage::ClassInstanceCmd(const wxString& instname, const wxString& classname, const wxString& params, bool dynamic)
{
	Indent();
	
	if( dynamic ) m_sOutBuffer << wxT("self.");
	m_sOutBuffer << instname << wxT(" = ") << classname << wxT("( ") << params << wxT(" )");
	
	NewLine();
}

void udPythonLanguage::EnumCmd(const wxString& name, const wxArrayString& values, const wxString& instname)
{
	ClassDeclCmd( name, wxT("") );
	
	BeginCmd();
	
	int nVal = 0;
	wxString sPar, sVal;
	
	for( size_t i = 0; i < values.GetCount(); ++i )
	{
		if( values[i].Contains( wxT("=") ) )
		{
			sPar = values[i].BeforeFirst('=').Trim().Trim(false);
			sVal = values[i].AfterLast('=').Trim().Trim(false);
			
			long nNewVal;
			if( sVal.ToLong( &nNewVal ) ) nVal = nNewVal + 1;
		}
		else
		{
			sPar = values[i];
			sVal.Printf( wxT("%d"), nVal++ );
		}
		
		if( i < values.GetCount()-1 ) WriteCodeBlocks( sPar + wxT(" = " ) + sVal + wxT(",") );
		else
			WriteCodeBlocks( sPar + wxT(" = " ) + sVal );
	}
	
	EndCmd();
	
	//if( !instname.IsEmpty() ) ClassInstanceCmd( instname, name, wxT(""), false );
	//NewLine();	
}
