#ifndef UDSTATECHARTOPTIMIZER_H
#define UDSTATECHARTOPTIMIZER_H

#include <wx/list.h>

#include "projectbase/ProjectBase.h"

WX_DECLARE_LIST(ShapeList, BranchList);

class WXDLLIMPEXP_CD udStateChartOptimizer : public udOptimizer
{
public:
    DECLARE_DYNAMIC_CLASS(udStateChartOptimizer);

	enum TASK
	{
		optMERGE_TRANSITIONS = 1,
		optMERGE_DIRECT_BRANCHES = 2,
		optINVERT_CONDITIONS = 4
	};

    udStateChartOptimizer();
	udStateChartOptimizer(udGenerator *gen);
    virtual ~udStateChartOptimizer();

    // public virtual functions
    virtual udDiagramItem* Optimize(udDiagramItem *src);

protected:
	// protected data member

	// protected functions
	bool MergeTransitions(udDiagramItem *src);
	bool MergeDirectBranches(udDiagramItem *src);
	bool InvertConditions(udDiagramItem *src);

private:
	// private data members
	udDiagramItem *m_pOptimizedDiagram;
	ShapeList m_lstProcessed;
	BranchList m_lstBranches;

	// private functions
	void FindTransWithIdenticalTarget(ShapeList& transitions, ShapeList& sublist);
	void FindTransWithIdenticalActions(ShapeList& transitions, ShapeList& sublist);
	void TrackBranch(wxSFShapeBase *state, wxSFLineShape *intrans, ShapeList *branch);
};

#endif // UDSTATECHARTOPTIMIZER_H
