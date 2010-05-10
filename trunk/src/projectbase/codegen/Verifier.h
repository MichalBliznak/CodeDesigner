#ifndef UDVERIFIER_H
#define UDVERIFIER_H

#include <wx/wx.h>

#include "interfaces/Defs.h"

class udGenerator;
class udDiagramItem;

class WXDLLIMPEXP_CD udVerifier : public wxObject
{
public:
	udVerifier();
	udVerifier(udGenerator *gen);
    virtual ~udVerifier();

    // public virtual functions
    virtual bool Verify(udDiagramItem *diagram);

protected:
	// protected data members
	udGenerator *m_pGenerator;
};


#endif // UDVERIFIER_H
