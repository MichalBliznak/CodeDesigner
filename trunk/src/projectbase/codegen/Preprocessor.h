#ifndef UDPREPROCESSOR_H
#define UDPREPROCESSOR_H

#include <wx/wx.h>

#include "interfaces/Defs.h"

class udGenerator;
class udDiagramItem;

class WXDLLIMPEXP_CD udPreprocessor : public wxObject
{
public:
	udPreprocessor();
	udPreprocessor(udGenerator *gen);
    virtual ~udPreprocessor();

    // public virtual functions
    virtual udDiagramItem* Process(udDiagramItem *src);

protected:
	// protected data member
	udGenerator *m_pGenerator;
	udDiagramItem *m_pPreprocessedDiagram;
};

#endif // UDPREPROCESSOR_H
