#include "codegen/Generator.h"
#include "codegen/CommentProcessors.h"
#include "ProjectBase.h"

unsigned long udGenerator::m_nIDCounter = 0;
bool udGenerator::m_fComments = false;

CommentMap udGenerator::m_mapComments;

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
	
	// check whether code comments are enabled
	udSettings &Settings = IPluginManager::Get()->GetProjectSettings();
	m_fComments = Settings.GetProperty( wxT("Generate code descriptions") )->AsBool();

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
    udProjectItem *pElement = wxDynamicCast( element->GetUserData(), udProjectItem );
	return pElement->GetUniqueId( m_pOutLang );
}

wxString udGenerator::MakeIDName(udProjectItem *element)
{
	return element->GetUniqueId( m_pOutLang );
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
			else
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

void udGenerator::InitAllStdCommentProcessors()
{
	// TODO: implement 'InitAllStdCommentProcessors'
	
	RegisterCommentProcessor( wxT("udGenericFunctionItem"), new udFunctionComment() );
	RegisterCommentProcessor( wxT("udGenericVariableItem"), new udVariableComment() );
}

// code comments ///////////////////////////////////////////////////////////////

void udGenerator::CleanCommentProcessors()
{
	for( CommentMap::iterator it = m_mapComments.begin(); it != m_mapComments.end(); ++it )
	{
		delete it->second;
	}
	m_mapComments.clear();
}

wxString udGenerator::GetComment(const udProjectItem* obj, udLanguage *lang)
{
	wxASSERT( obj );
	
	if( obj )
	{
		if( m_fComments )
		{
			// find appropriate comment processor and make a comment
			udCommentProcessor *pProcessor = m_mapComments[ obj->GetClassInfo()->GetClassName() ];
			if( pProcessor )
			{
				return pProcessor->MakeComment( obj, lang );
			}
		}
	}
	
	return wxEmptyString;
}

void udGenerator::RegisterCommentProcessor(const wxString& type, udCommentProcessor* processor)
{
	wxASSERT( processor );
	
	if( processor )
	{
		UnregisterCommentProcessor( type );
		m_mapComments[type] = processor;
	}
}

void udGenerator::UnregisterCommentProcessor(const wxString& type)
{
	if( m_mapComments.find( type ) != m_mapComments.end() )
	{
		delete m_mapComments[ type ];
		m_mapComments.erase( type );
	}
}

udCommentProcessor::~udCommentProcessor()
{
	for( DialectMap::iterator it = m_mapDialect.begin(); it != m_mapDialect.end(); ++it )
	{
		delete it->second;
	}
	m_mapDialect.clear();
}

wxString udCommentProcessor::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );
	
	if( obj && lang )
	{
		udCommentDialect *pDialect = m_mapDialect[ lang->GetClassInfo()->GetClassName() ];
		if( pDialect )
		{
			return pDialect->MakeComment( obj, lang );
		}
	}
	
	return wxEmptyString;
}

void udCommentProcessor::RegisterDialect(const wxString& langtype, udCommentDialect* dialect)
{
	wxASSERT( dialect );
	
	if( dialect )
	{
		UnregisterDialect( langtype );
		m_mapDialect[ langtype ] = dialect;
	}
}

void udCommentProcessor::UnregisterDialect(const wxString& langtype)
{
	if( m_mapDialect.find( langtype ) != m_mapDialect.end() )
	{
		delete m_mapDialect[ langtype ];
		m_mapDialect.erase( langtype );
	}
}
