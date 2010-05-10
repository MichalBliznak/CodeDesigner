#include "ClassDiagramGenerator.h"
#include "CPPClassAlgorithm.h"
#include "PythonClassAlgorithm.h"
#include "../GenUml.h"

#include <wx/txtstrm.h>

IMPLEMENT_DYNAMIC_CLASS(udClassDiagramGenerator, udGenerator);

// constructor and destructor///////////////////////////////////////////////////////////////////////////////

udClassDiagramGenerator::udClassDiagramGenerator()
{
    m_sName = udnCLASS_DIAGRAM_GEN;
    m_sDescription = wxT("");

    m_mapAlgorithms[wxT("udPythonClassAlgorithm")] = new udPythonClassAlgorithm(this);
    m_mapAlgorithms[wxT("udCPPClassAlgorithm")] = new udCPPClassAlgorithm(this);
}

udClassDiagramGenerator::~udClassDiagramGenerator()
{
    udGenerator::CleanUp();
}

// protected virtual functions /////////////////////////////////////////////////////////////////////////////

bool udClassDiagramGenerator::Initialize()
{
    return udGenerator::Initialize();
}

bool udClassDiagramGenerator::ProcessDiagram(udDiagramItem *src)
{
	switch( m_nMode )
	{
		case genCOMMON_DECLARATION:
			return GenerateCommonDeclaration();
			
		case genCOMMON_DEFINITION:
			return GenerateCommonDefinition();
			
		case genDECLARATION:
			return GenerateDeclaration( src );
			
		case genDEFINITION:
			return GenerateDefinition( src );
			
		default:
			IPluginManager::Get()->Log( wxT("ERROR: No valid generation target has been specified.") );
			return false;
	}
}

void udClassDiagramGenerator::CleanUp()
{
}

// protected functions /////////////////////////////////////////////////////////////////////////////////////

bool udClassDiagramGenerator::GenerateCommonDeclaration()
{	
	
	return true;
}

bool udClassDiagramGenerator::GenerateCommonDefinition()
{
	
	return true;
}

bool udClassDiagramGenerator::GenerateDeclaration(udDiagramItem* src)
{		
	// initialize output stream
	wxTextOutputStream textOut(*m_pOut);
		
	if( m_pOutLang->HasSeparatedDecl() )
	{
		udClassAlgorithm *pAlg = wxDynamicCast( m_pAlgorithm, udClassAlgorithm );
		if( pAlg )
		{
			pAlg->SetGenMode( m_nMode );
			pAlg->Process(src);
			
			textOut << m_pOutLang->GetCodeBuffer();
		}
	}
	
	return true;
}

bool udClassDiagramGenerator::GenerateDefinition(udDiagramItem* src)
{
	// initialize output stream
	wxTextOutputStream textOut(*m_pOut);
		
	udClassAlgorithm *pAlg = wxDynamicCast( m_pAlgorithm, udClassAlgorithm );
	if( pAlg )
	{
		pAlg->SetGenMode( m_nMode );
		pAlg->Process(src);
		
		textOut << m_pOutLang->GetCodeBuffer();
	}

	return true;
}

