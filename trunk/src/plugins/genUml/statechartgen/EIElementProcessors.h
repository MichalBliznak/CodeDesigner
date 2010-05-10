#ifndef UDEIELEMENTPROCESSOR_H
#define UDEIELEMENTPROCESSOR_H

#include "StateChartElementProcessor.h"
#include "LCEITransitionProcessor.h"

/////////////////////////////////////////////////////////////////////////////////////
// udEISimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udEISimpleStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udEISimpleStateProcessor);

    udEISimpleStateProcessor();
    udEISimpleStateProcessor(udGenerator *parent);
    virtual ~udEISimpleStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udEISubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udEISubStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udEISubStateProcessor);

    udEISubStateProcessor();
    udEISubStateProcessor(udGenerator *parent);
    virtual ~udEISubStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udEIHistoryProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udEIHistoryProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udEIHistoryProcessor);

    udEIHistoryProcessor();
    udEIHistoryProcessor(udGenerator *parent);
    virtual ~udEIHistoryProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udEIFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udEIFinalItemProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udEIFinalItemProcessor);

    udEIFinalItemProcessor();
    udEIFinalItemProcessor(udGenerator *parent);
    virtual ~udEIFinalItemProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
	
protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};


#endif // UDEIELEMENTPROCESSOR_H
