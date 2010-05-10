#ifndef UDLCELEMENTPROCESSORS_H
#define UDLCELEMENTPROCESSORS_H

#include "StateChartElementProcessor.h"
#include "LCEITransitionProcessor.h"

/////////////////////////////////////////////////////////////////////////////////////
// udLCSimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udLCSimpleStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCSimpleStateProcessor);

    udLCSimpleStateProcessor();
    udLCSimpleStateProcessor(udGenerator *parent);
    virtual ~udLCSimpleStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udLCSubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udLCSubStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCSubStateProcessor);

    udLCSubStateProcessor();
    udLCSubStateProcessor(udGenerator *parent);
    virtual ~udLCSubStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udLCFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udLCFinalItemProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCFinalItemProcessor);

    udLCFinalItemProcessor();
    udLCFinalItemProcessor(udGenerator *parent);
    virtual ~udLCFinalItemProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

/////////////////////////////////////////////////////////////////////////////////////
// udLCStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*class udLCStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCStateProcessor);

    udLCStateProcessor();
    udLCStateProcessor(udGenerator *parent);
    virtual ~udLCStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};*/

/////////////////////////////////////////////////////////////////////////////////////
// udLCDecisionProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/*class udLCDecisionProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCDecisionProcessor);

    udLCDecisionProcessor();
    udLCDecisionProcessor(udGenerator *parent);
    virtual ~udLCDecisionProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};*/

/////////////////////////////////////////////////////////////////////////////////////
// udLCHistoryProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udLCHistoryProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udLCHistoryProcessor);

    udLCHistoryProcessor();
    udLCHistoryProcessor(udGenerator *parent);
    virtual ~udLCHistoryProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udLCEITransitionProcessor m_transProcessor;
};

#endif // UDLCELEMENTPROCESSORS_H
