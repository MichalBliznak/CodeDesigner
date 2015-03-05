#ifndef _DIAGRAM_BASE_H_
#define _DIAGRAM_BASE_H_

#include "interfaces/Defs.h"
#include "interfaces/IDiagram.h"
#include <wx/wxsf/wxShapeFramework.h>

class udDiagramItem;

class WXDLLIMPEXP_CD udDiagramManager : public wxSFDiagramManager
{
public:
    XS_DECLARE_CLONABLE_CLASS(udDiagramManager);
	
	udDiagramManager();
	udDiagramManager(udDiagramItem *parent);
	udDiagramManager(const udDiagramManager& obj);
    virtual ~udDiagramManager() {}

	virtual void UpdateAllInnerContent();
	
	void SetParentProjItem(udDiagramItem *parent){m_pParentProjItem = parent;}
    udDiagramItem* GetParentProjItem(){return m_pParentProjItem;}
	
protected:
	udDiagramItem *m_pParentProjItem;
};

class WXDLLIMPEXP_CD udDiagramCanvas : public wxSFShapeCanvas
{
public:
    DECLARE_DYNAMIC_CLASS(udDiagramCanvas);

    udDiagramCanvas();
    udDiagramCanvas(wxSFDiagramManager *manager, wxWindow *parent, long id);
    virtual ~udDiagramCanvas();

	// public functions
	virtual void InitializeBackground();
    virtual void InitializeCanvas();
	
	udDiagramManager* GetManager() { return (udDiagramManager*) GetDiagramManager(); }
};

#endif //_DIAGRAM_BASE_H_