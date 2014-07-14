#ifndef UDCLASSALGORITHM_H
#define UDCLASSALGORITHM_H

#include "projectbase/ProjectBase.h"
#include "../../diagUml/DiagUml.h"

class WXDLLIMPEXP_CD udClassAlgorithm : public udAlgorithm
{
public:
    DECLARE_DYNAMIC_CLASS(udClassAlgorithm);

    udClassAlgorithm();
    udClassAlgorithm(udGenerator *parent);
    virtual ~udClassAlgorithm();
	
	// public data accessors
	void SetGenMode(const udGenerator::GENMODE& GenMode) {this->m_GenMode = GenMode;}
	const udGenerator::GENMODE& GetGenMode() const {return m_GenMode;}
	
	// public functions
    virtual void ProcessAlgorithm(udDiagramItem *src);

protected:
    // protected data members
	udGenerator::GENMODE m_GenMode;
	
	// protected functions
    virtual bool Initialize();
};

#endif // UDCLASSALGORITHM_H
