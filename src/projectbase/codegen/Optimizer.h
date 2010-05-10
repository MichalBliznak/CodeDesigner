#ifndef UDOPTIMIZER_H
#define UDOPTIMIZER_H

#include <wx/wx.h>

#include "interfaces/Defs.h"

class udGenerator;
class udDiagramItem;

class WXDLLIMPEXP_CD udOptimizer : public wxObject
{
public:
	udOptimizer();
	udOptimizer(udGenerator *gen);
    virtual ~udOptimizer();

    // public virtual functions
    virtual udDiagramItem* Optimize(udDiagramItem *src);

	// public functions
	void SetOptimizationFlags(int flags){m_nFlags = flags;}

	int GetOptimizationFlags(){return m_nFlags;}

protected:
	// protected data member
	int m_nFlags;
	udGenerator *m_pGenerator;
};

#endif // UDOPTIMIZER_H
