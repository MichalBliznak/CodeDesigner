#ifndef UDALGORITHM_H
#define UDALGORITHM_H

#include <wx/hashmap.h>

#include "interfaces/Defs.h"
#include "ElementProcessor.h"

class udGenerator;
class udDiagramItem;

class WXDLLIMPEXP_CD  udAlgorithm : public wxObject
{
public:
    udAlgorithm();
    udAlgorithm(udGenerator *parent);
    virtual ~udAlgorithm();
	

    // public member data accessors
    void SetParentGenerator(udGenerator *parent);
    void SetName(const wxString& name){m_sName = name;}
    void SetDescription(const wxString& desc){m_sDescription = desc;}

    udGenerator* GetParentGenerator(){return m_pParentGenerator;}
    udElementProcessor* GetElementProcessor(const wxString& itemName);
    wxSFShapeBase* GetNextElement(){return m_pNextElement;}
    wxSFShapeBase* GetPrevElement(){return m_pPrevElement;}
    wxString GetName(){return m_sName;}
    wxString GetDescription(){return m_sDescription;}
    wxArrayString& GetSupportedLanguages(){return m_arrSuppLanguages;}
	ShapeList& GetProcessedElements() {return m_lstProcessedElements;}
	udDiagramItem* GetProcessedDiagram() {return m_pProcessedDiagram;}

    // public functions
    void Process(udDiagramItem *src);

protected:
    // protected data members
    ProcessorMap m_mapElementProcessors;
    wxArrayString m_arrSuppLanguages;
	ShapeList m_lstProcessedElements;

	udDiagramItem* m_pProcessedDiagram;
    udGenerator *m_pParentGenerator;
    wxSFShapeBase *m_pNextElement;
    wxSFShapeBase *m_pPrevElement;

    wxString m_sName;
    wxString m_sDescription;

    // protected virtual functions
    virtual bool Initialize();
    virtual void ProcessAlgorithm(udDiagramItem *src);
    virtual void CleanUp();
};

WX_DECLARE_HASH_MAP( wxString, udAlgorithm*, wxStringHash, wxStringEqual, AlgorithmMap );

#endif // UDALGORITHM_H
