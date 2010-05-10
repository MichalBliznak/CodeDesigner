#ifndef UDGTELEMENTPROCESSORS_H
#define UDGTELEMENTPROCESSORS_H

#include "StateChartElementProcessor.h"

/////////////////////////////////////////////////////////////////////////////////////
// udGTTransitionProcessor class ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGTTransitionProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udGTTransitionProcessor);

    udGTTransitionProcessor();
    udGTTransitionProcessor(udGenerator *parent);
    virtual ~udGTTransitionProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udGTSimpleStateProcessor class ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


class WXDLLIMPEXP_CD udGTSimpleStateProcessor : public udStateChartElementProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udGTSimpleStateProcessor);

    udGTSimpleStateProcessor();
    udGTSimpleStateProcessor(udGenerator *parent);
    virtual ~udGTSimpleStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udGTTransitionProcessor m_transProcessor;

	// protected functions
	bool ShouldOmitLabel(wxSFShapeBase *element);
	bool HasOutput(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udGTSubStateProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGTSubStateProcessor : public udGTSimpleStateProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udGTSubStateProcessor);

    udGTSubStateProcessor();
    udGTSubStateProcessor(udGenerator *parent);
    virtual ~udGTSubStateProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udGTHistoryProcessor class //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGTHistoryProcessor : public udGTSimpleStateProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udGTHistoryProcessor);

    udGTHistoryProcessor();
    udGTHistoryProcessor(udGenerator *parent);
    virtual ~udGTHistoryProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};

/////////////////////////////////////////////////////////////////////////////////////
// udGTFinalItemProcessor class /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udGTFinalItemProcessor : public udGTSimpleStateProcessor
{
public:
    DECLARE_DYNAMIC_CLASS(udGTFinalItemProcessor);

    udGTFinalItemProcessor();
    udGTFinalItemProcessor(udGenerator *parent);
    virtual ~udGTFinalItemProcessor();

    // public virtual functions
    virtual void ProcessElement(wxSFShapeBase *element);
};


#endif // UDGTELEMENTPROCESSORS_H
