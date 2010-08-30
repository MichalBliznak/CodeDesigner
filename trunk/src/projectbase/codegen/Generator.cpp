#include "codegen/Generator.h"
#include "ProjectBase.h"

unsigned long udGenerator::m_nIDCounter = 0;

udGenerator::udGenerator()
{
    m_pVerifier = NULL;
    m_pOptimizer = NULL;
    m_pAlgorithm = NULL;
    m_pPreprocessor = NULL;
    m_pOutLang = NULL;
    m_pOut = NULL;
	m_nMode = genNONE;
	m_fRecursive = false;
}

udGenerator::~udGenerator()
{
    // free assigned algorithms
    AlgorithmMap::iterator ita = m_mapAlgorithms.begin();
    while(ita != m_mapAlgorithms.end())
    {
        delete ita->second;
        ita++;
    }
    m_mapAlgorithms.clear();
}

bool udGenerator::Initialize()
{
    m_lstProcessedDiagrams.Clear();
	
	// initialize output language
    if(m_pOutLang)
    {
        m_pOutLang->ClearCodeBuffer();
        m_pOutLang->SetIndentation(0);
    }
    else
        return false;
		
	// initialize code generation algoritm
    if(m_pAlgorithm)
    {
        if(!m_pAlgorithm->GetParentGenerator()) m_pAlgorithm->SetParentGenerator(this);
    }

    return true;
}

bool udGenerator::ProcessDiagram(udDiagramItem *src)
{
	return true;
}

void udGenerator::CleanUp()
{
}

wxString udGenerator::MakeValidIdentifier(const wxString& name)
{
    if(m_pOutLang)
    {
        return m_pOutLang->MakeValidIdentifier(name);
    }
    else
        return name;
}
wxString udGenerator::MakeIDName(wxSFShapeBase *element)
{
    //wxString sId = MakeValidIdentifier(umlDiagramBase::GetLabelContent(element, umlLabelElement::ltTITLE));
    udProjectItem *pElement = wxDynamicCast( element->GetUserData(), udProjectItem );
    wxString sId = MakeValidIdentifier( pElement->GetName() );
    return wxString::Format(wxT("ID_%s"), sId.MakeUpper().c_str(), element->GetId());
}

wxString udGenerator::MakeIDName(udProjectItem *element)
{
    wxString sId = MakeValidIdentifier(element->GetName());
    return wxString::Format(wxT("ID_%s"), sId.MakeUpper().c_str(), element->GetId());
}

bool udGenerator::Generate(udDiagramItem *src, bool recursive)
{
	m_fRecursive = recursive;
	
    /*if(!src)
    {
        UMLDesignerApp::Log(wxT("ERROR: No source diagram is specified."));
        return false;
    }*/

    // initialize generator
    IPluginManager::Get()->Log(wxT("Initializing generator..."));
    if(this->Initialize())
    {
        IPluginManager::Get()->Log(wxT("Initialization is done."));
    }
    else
    {
        IPluginManager::Get()->Log(wxT("ERROR: Initialization has failed."));
        return false;
    }

    // generate code
	IPluginManager::Get()->Log(wxT("Starting code generation..."));
    bool fSuccess = _Generate(src);
	IPluginManager::Get()->Log(wxT("Code generation is done."));

    // clean up
    IPluginManager::Get()->Log(wxT("Cleaning up the generator..."));
    this->CleanUp();
    IPluginManager::Get()->Log(wxT("Clean up process is done."));

	if( fSuccess )
	{
		IPluginManager::Get()->Log(wxT("Generation process is done."));
	}
	else
		IPluginManager::Get()->Log(wxT("Generation process is done with 'ERROR' status."));

    return fSuccess;
}

bool udGenerator::_Generate(udDiagramItem *src)
{
	bool fSuccess = true;
	
	if( src )
	{
		udDiagramItem *m_pOptimizedSource = NULL;
		udDiagramItem *m_pPreprocessedSource = NULL;
	
		if( m_lstProcessedDiagrams.IndexOf( src ) != wxNOT_FOUND ) return true;

		IPluginManager::Get()->Log(wxString::Format(wxT("Processing diagram '%s' ..."), src->GetName().c_str()));

		// preprocess source diagram's structure
		if(m_pPreprocessor)
		{
			IPluginManager::Get()->Log(wxT("Preprocessing..."));
			m_pPreprocessedSource = m_pPreprocessor->Process(src);
			IPluginManager::Get()->Log(wxT("Done."));
		}
		else
			m_pPreprocessedSource = src;
			
		// verify source structure if requested
		if(m_pVerifier)
		{
			IPluginManager::Get()->Log(wxT("Verifying..."));
			if(!m_pVerifier->Verify(m_pPreprocessedSource))
			{
				IPluginManager::Get()->Log(wxT("Verification is done with 'ERROR' status."));
				fSuccess = false;
			}
			IPluginManager::Get()->Log(wxT("Verification is done with 'OK' status."));
		}

		if( fSuccess )
		{
			// optimize source diagram's structure
			if(m_pOptimizer)
			{
				IPluginManager::Get()->Log(wxT("Optimizing..."));
				m_pOptimizedSource = m_pOptimizer->Optimize(m_pPreprocessedSource);
				IPluginManager::Get()->Log(wxT("Done."));
			}
			else
				m_pOptimizedSource = m_pPreprocessedSource;
				
			// processing the source diagram
			if(m_pOptimizedSource)
			{
				fSuccess = this->ProcessDiagram(m_pOptimizedSource);
				IPluginManager::Get()->Log(wxString::Format(wxT("Diagram '%s' was processed."), src->GetName().c_str()));
			}
		}
		
		m_lstProcessedDiagrams.Append( src );
		
		// delete optimized diagram
		if( m_pOptimizedSource && (m_pOptimizedSource != src) ) delete m_pOptimizedSource;
		if( m_pPreprocessedSource && (m_pPreprocessedSource != src) && (m_pPreprocessedSource != m_pOptimizedSource) ) delete m_pPreprocessedSource;
	}
	else
		fSuccess = this->ProcessDiagram( NULL );

    return fSuccess;
}

udAlgorithm* udGenerator::FindAlgorithm(const wxString& name)
{
    AlgorithmMap::iterator ita = m_mapAlgorithms.begin();
    while(ita != m_mapAlgorithms.end())
    {
        if(ita->second->GetName() == name)return ita->second;
        ita++;
    }

    return NULL;
}

wxString udGenerator::GetBeginCodeMark(const udCodeItem *item)
{
	return wxString::Format( wxT("['%s::%s' begin]"), item->GetScope().c_str(), item->GetName().c_str() );
}

wxString udGenerator::GetEndCodeMark(const udCodeItem *item)
{
	return wxString::Format( wxT("['%s::%s' end]"), item->GetScope().c_str(), item->GetName().c_str() );
}

// code comments ///////////////////////////////////////////////////////////////

void udGenerator::CleanCommentProcessor()
{
}

wxString udGenerator::GetComment(const udProjectItem* obj)
{
	return wxEmptyString;
}

void udGenerator::RegisterCommentProcessor(const wxString& type, udCommentProcessor* processor)
{
}

void udGenerator::UnregisterCommentProcessor(const wxString& type)
{
}

wxString udCommentDialect::MakeComment(const udProjectItem* obj, const udLanguage* lang)
{
	return wxEmptyString;
}
