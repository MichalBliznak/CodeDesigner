#ifndef UDPROJECTGENERATOR_H
#define UDPROJECTGENERATOR_H

#include "projectbase/codegen/Language.h"

#include <wx/hashmap.h>
#include <wx/filename.h>

#include "projectbase/codegen/Generator.h"

class udProject;
class udCodeItem;

class udProjectGenerator : public wxObject
{
public:
    DECLARE_DYNAMIC_CLASS(udProjectGenerator);

    udProjectGenerator();
    virtual ~udProjectGenerator();

    // public functions
    void Generate(udProject *src);
	
	static wxFileName GetFullCodePath(const wxString& name, const wxString& ext);
	static wxString GetCodeFromCodemark(const udCodeItem *item, const wxFileName& file);
	static void GetModifiedUserCode(const udLanguage* lang, SerializableList& items, wxArrayString& origcode, wxArrayString& modifcode, int *ambiguous);
	
	void ClearGeneratedFiles() { m_arrGeneratedFiles.Clear(); }
	void AddToGeneratedFiles(const wxString& path) { m_arrGeneratedFiles.Add( path ); }
	wxArrayString& GetGeneratedFiles() { return m_arrGeneratedFiles; }
	
	// public member data accessors
	void SetActiveLanguage(udLanguage *lang){m_pOutLang = lang;}

protected:
	// protected data members
	udLanguage *m_pOutLang;
	wxArrayString m_arrGeneratedFiles;
	
	// protected functions
	wxString BeginMark( const wxString& mark );
	wxString EndMark( const wxString& mark );
	
	void InsertCodemark(const wxString& mark, const wxFileName& file, int pos);
	void InsertCodemark(const wxString& mark, const wxFileName& file, const wxString& after);
	void ClearCodemark(const wxString& mark, const wxFileName& file);
	void InsertIntoCodemark(const wxString& txt, const wxString& mark, const wxFileName& file);
	
	bool CodemarkExists(const wxString& mark, const wxFileName& file);
	
	void WriteToFile(const wxString& txt, const wxFileName& file);
	
	void Log(const wxString& msg);
	
	bool CheckAlgorithms(udProject *src);
	
    // protected virtual functions
    virtual void Initialize();
    virtual void ProcessProject(udProject *src);
    virtual void CleanUp();
};

WX_DECLARE_HASH_MAP( wxString, udProjectGenerator*, wxStringHash, wxStringEqual, ProjectGeneratorMap );


#endif // UDPROJECTGENERATOR_H
