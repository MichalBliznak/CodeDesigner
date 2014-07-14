#ifndef UDELEMENTPROCESSOR_H
#define UDELEMENTPROCESSOR_H

#include <wx/hashmap.h>

#include "interfaces/Defs.h"
#include "Language.h"
#include <wx/wxsf/wxShapeFramework.h>

class WXDLLIMPEXP_CD udGenerator;

class WXDLLIMPEXP_CD udElementProcessor : public wxObject
{
public:
    udElementProcessor();
    udElementProcessor(udGenerator *parent);
    virtual ~udElementProcessor();

    // public member data accessors
    void SetParentGenerator(udGenerator *parent){m_pParentGenerator = parent;}

    // public function
    virtual void ProcessElement(wxSFShapeBase *element);

protected:
    // protected data members
    udGenerator *m_pParentGenerator;

};

WX_DECLARE_HASH_MAP( wxString, udElementProcessor*, wxStringHash, wxStringEqual, ProcessorMap );

#endif // UDELEMENTPROCESSOR_H
