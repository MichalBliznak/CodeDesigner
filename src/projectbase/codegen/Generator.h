#ifndef UDGENERATOR_H
#define UDGENERATOR_H

#include "interfaces/Defs.h"
#include "Algorithm.h"
#include "Language.h"
#include "Verifier.h"
#include "Optimizer.h"
#include "Preprocessor.h"

#if defined(__WXMSW__)
	#define ENDL wxT("\n")
#elif defined(__WXGTK__)
	#define ENDL wxT("\n")
#else
	#define ENDL wxT("\r")
#endif

class udProjectItem;
class udDiagramItem;
class udCodeItem;

class WXDLLIMPEXP_CD udCommentDialect : public wxObject
{
public:
	virtual wxString MakeComment(const udProjectItem *obj, udLanguage *lang) = 0;
};

WX_DECLARE_HASH_MAP( wxString, udCommentDialect*, wxStringHash, wxStringEqual, DialectMap );

class WXDLLIMPEXP_CD udCommentProcessor : public wxObject
{
public:
	virtual ~udCommentProcessor();
	
	virtual wxString MakeComment(const udProjectItem *obj, udLanguage *lang);
	
	void RegisterDialect(const wxString& langtype, udCommentDialect *dialect);
	void UnregisterDialect(const wxString& langtype);
	
protected:
	DialectMap m_mapDialect;
};

WX_DECLARE_HASH_MAP( wxString, udCommentProcessor*, wxStringHash, wxStringEqual, CommentMap );

class WXDLLIMPEXP_CD udGenerator : public wxObject
{
public:
	enum GENMODE
	{
		genNONE,
		genCOMMON_DECLARATION,
		genCOMMON_DEFINITION,
		genDECLARATION,
		genDEFINITION
	};

    udGenerator();
    virtual ~udGenerator();

    // public member data accessors
    void SetActiveLanguage(udLanguage *lang){m_pOutLang = lang;}
    void SetActiveAlgorithm(udAlgorithm *alg){m_pAlgorithm = alg;}
    void SetActiveVerifier(udVerifier *ver){m_pVerifier = ver;}
    void SetActiveOptimizer(udOptimizer *optim){m_pOptimizer = optim;}
    void SetOutputStream(wxOutputStream *out){m_pOut = out;}
    void SetName(const wxString& name){m_sName = name;}
    void SetDescription(const wxString& desc){m_sDescription = desc;}
	void SetMode(GENMODE mode){m_nMode = mode;}

    udLanguage* GetActiveLanguage(){return m_pOutLang;}
    udAlgorithm* GetActiveAlgorithm(){return m_pAlgorithm;}
    udVerifier* GetActiveVerifier(){return m_pVerifier;}
    udOptimizer* GetActiveOptimizer(){return m_pOptimizer;}
    wxOutputStream* GetOutputStream(){return m_pOut;}
    const wxString& GetName() const {return m_sName;}
    const wxString& GetDescription() const {return m_sDescription;}
    AlgorithmMap& GetAlgorithms(){return m_mapAlgorithms;}
	GENMODE GetMode() const {return m_nMode;}

    udAlgorithm* FindAlgorithm(const wxString& name);

    // public functions
    bool Generate(udDiagramItem *src, bool recursive);

	static wxString GetBeginCodeMark(const udCodeItem *item);
	static wxString GetEndCodeMark(const udCodeItem *item);
	
	static void ResetIDCounter(){m_nIDCounter = 0;}

    wxString MakeIDName(wxSFShapeBase *element);
    wxString MakeIDName(udProjectItem *element);
    wxString MakeValidIdentifier(const wxString& name);
	
	static void RegisterCommentProcessor(const wxString& type, udCommentProcessor *processor);
	static void UnregisterCommentProcessor(const wxString& type);
	static wxString GetComment(const udProjectItem *obj, udLanguage *lang);
	static void CleanCommentProcessors();
	static void InitAllStdCommentProcessors();

protected:
    // protected data members
    AlgorithmMap m_mapAlgorithms;
	static CommentMap m_mapComments;

    udLanguage *m_pOutLang;
    udAlgorithm *m_pAlgorithm;
    udVerifier *m_pVerifier;
    udOptimizer *m_pOptimizer;
    udPreprocessor *m_pPreprocessor;

    wxOutputStream *m_pOut;

    wxString m_sName;
    wxString m_sDescription;

    SerializableList m_lstProcessedDiagrams;
	
	GENMODE m_nMode;
	
	bool m_fRecursive;
	static bool m_fComments;
	static unsigned long m_nIDCounter;

    // protected functions
    bool _Generate(udDiagramItem *src);

    // protected virtual functions
    virtual bool Initialize();
    virtual bool ProcessDiagram(udDiagramItem *src);
    virtual void CleanUp();
};

#endif // UDGENERATOR_H
