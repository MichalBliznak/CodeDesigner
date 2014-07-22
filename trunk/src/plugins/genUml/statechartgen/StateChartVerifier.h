#ifndef UDSTATEVERIFIER_H
#define UDSTATEVERIFIER_H

#include "projectbase/ProjectBase.h"

class WXDLLIMPEXP_CD udStateChartVerifier : public udVerifier
{
public:
    DECLARE_DYNAMIC_CLASS(udStateChartVerifier);

    udStateChartVerifier();
	udStateChartVerifier(udGenerator *gen);
    virtual ~udStateChartVerifier();

    // public virtual functions
    virtual bool Verify(udDiagramItem *diagram);

protected:
	// protected data members
	ShapeList m_lstProcessedStates;

	// protected functions
	bool CheckInitialStates(udDiagramItem *diagram);
	bool CheckEndingStates(udDiagramItem *diagram);
	bool CheckUnconnectedStates(udDiagramItem *diagram);
	bool CheckConnections(udDiagramItem *diagram);
	bool CheckHistoryStates(udDiagramItem *diagram);
	bool CheckGOTOConstraints(udDiagramItem *diagram);
	bool CheckLanguageConstraints(udDiagramItem *diagram);

	bool _CheckOutcommingPaths(wxSFDiagramManager *manager, wxSFShapeBase *parent);
};



#endif // UDSTATEVERIFIER_H
