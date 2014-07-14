#ifndef _PROJECT_BASE_COMMON_H_
#define _PROJECT_BASE_COMMON_H_

#include "interfaces/Defs.h"

#include <wx/wxsf/wxShapeFramework.h>
#include <wx/stc/stc.h>

class udLanguage;
class udDiagramItem;
class udDiagElementItem;
class udGenerator;
class udProjectItem;

#define udfOMIT_LINKS true

namespace udLABEL
{
	enum TYPE
	{
		ltUNDEFINED = 0,
		ltTITLE,
		ltNOTE_CONTENT,
		ltGUARD_CONTENT,
		ltSTATE_ENTRYACTIONS,
		ltSTATE_EXITACTIONS,
		ltCLASS_VARIABLES,
		ltCLASS_FUNCTIONS,
		ltASSOC_ROLE1,
		ltASSOC_ROLE2,
		ltASSOC_MULT1,
		ltASSOC_MULT2,
		ltCLASS_TEMPLATE,
		ltENUM_ELEMENT,
		ltSTEREOTYPE
	};
	
	/**
	 * \brief Set content of diagram component's label.
	 * \param name New content
	 * \param element Pointer to diagram component owning the label
	 * \param type Label type
	 * \sa udLABEL::TYPE
	 */
	WXDLLIMPEXP_CD void SetContent(const wxString& name, wxSFShapeBase *element, TYPE type);
	/**
	 * \brief Set content of diagram component's label.
	 * \param name New content
	 * \param element Pointer to diagram component owning the label
	 * \param manager Pointer to diagram nanager which should be user for the content update insted of 
	 * the default element's one
	 * \param type Label type
	 */
	WXDLLIMPEXP_CD void SetContent(const wxString& name, wxSFShapeBase *element, wxXmlSerializer *manager, TYPE type);
	/**
	 * \brief Get content of diagram component's label.
	 * \param element Pointer to diagram component owning the label
	 * \param type Label type
	 * \return Label's content
	 */
	WXDLLIMPEXP_CD wxString GetContent(wxSFShapeBase *element, TYPE type);
	
	/**
	 * \brief Get quantity parameters from associations.
	 * \param element Pointer to diagram component owning the label
	 * \param type Label type
	 * \param min Pointer to variable where minimal amount will be stored to
	 * \param max Pointer to variable where maximal amount will be stored to
	 */
	WXDLLIMPEXP_CD void GetQuantity(wxSFShapeBase *element, TYPE type, long *min, long *max);
};

namespace udPROJECT
{
	/**
	 * \brief Get parent diagram item of given project item if exists.
	 * \param element Project item assigned to some shape
	 * \return Pointer to parent diagram item if exists, otherwise NULL
	 */
	WXDLLIMPEXP_CD udDiagramItem* GetParentDiagram(udProjectItem *element);
	/**
	 * \brief Get diagram component which is a base parent of given shape object (typicaly used
	 * if the parent of editable label should be found). Note that returned shape don't has to be
	 * a direct parent.
	 * \param child Pointer to child shape of searched parent diagram component
	 * \return Pointer to parent diagram component
	 */
	WXDLLIMPEXP_CD wxSFShapeBase* GetParentElement(wxSFShapeBase *child);
	/**
	 * \brief Create selected code generator for given diagram.
	 * \param diag Pointer to a diagram item for which the generator should be created
	 * \return Pointer to code generator
	 */
	WXDLLIMPEXP_CD udGenerator* CreateGenerator(udDiagramItem *diag);
	/**
	 * \brief Create code generator of given (friendly) name.
	 * \param name Friendly (user-readable) code generator name
	 * \return Pointer to code generator if exists, otherwise NULL
	 */
	WXDLLIMPEXP_CD udGenerator* CreateGenerator(const wxString& name);
	/**
	 * \brief Get diagram element from given diagram.
	 * \param diagram Pointer to diagram where the diagram element is located
	 * \param name Diagram element name
	 * \return 
	 */
	WXDLLIMPEXP_CD udDiagElementItem* GetDiagramElement(udDiagramItem *diagram, const wxString& name);
	/**
	 * \brief Get diagram element owned by given diagram component. Note that if given component is a link
	 * component, then original diagram element will be returned.
	 * \param shape Diagram component owning the diagram element 
	 * \param omitlinks If TRUE then NULL value will be returned for link elements
	 * \return Pointer to diagram component
	 */
	WXDLLIMPEXP_CD udDiagElementItem* GetDiagramElement(wxSFShapeBase *shape, bool omitlinks = false);
	/**
	 * \brief Get all diagram elements of given type from specified diagram.
	 * \param diagram Pointer to diagram item
	 * \param type Element type
	 * \param elements List where all elements will be stored to
	 * \param recursive TRUE if also subdiagrams should be examined
	 */
	WXDLLIMPEXP_CD void GetDiagramElements(udDiagramItem *diagram, wxClassInfo *type, SerializableList& elements, bool recursive);
	/**
	 * \brief Get subdiagrams of given parent diagram.
	 * \param parent Pointer to parent diagram item
	 * \param type Subdiagram type
	 * \param subdiagrams List where all subdiagrams will be stored to
	 */
	WXDLLIMPEXP_CD void GetSubDiagrams(udDiagramItem* parent, wxClassInfo *type, SerializableList& subdiagrams);
	/**
	 * \brief Get superdiagram (base parent diagram) of given subdiagram.
	 * \param child Pointer to subdiagram.
	 * \return Pointer to base parent diagram.
	 */
	WXDLLIMPEXP_CD udDiagramItem* GetSuperDiagram(udDiagramItem *child);
	/**
	 * \brief Get child project item of given parent.
	 * \param parent Pointer to parent project item
	 * \param type Type of child project item
	 * \param name Name of child project item
	 * \return Pointer to child project item if exists, otherwise NULL
	 */
	WXDLLIMPEXP_CD udProjectItem* GetProjectItem(udProjectItem* parent, wxClassInfo* type, const wxString& name);
	/**
	 * \brief Get code items containing given pattern in their code.
	 * \param patern Searched pattern
	 * \param references List where matching code items will be stored to
	 */
	WXDLLIMPEXP_CD void FindCodeReferences(const wxString& pattern, SerializableList& references);
};

namespace udFRAME
{
	/**
	 * \brief Fill choice control with list of available code generators.
	 * \param choice Pointer to updated choice control
	 * \param lang Pointer to language which is supported by code generator
	 * \param diag Pointer to diagram which is supported by code generator
	 */
	WXDLLIMPEXP_CD void FillGeneratorsChoice(wxChoice *choice, udLanguage *lang, udDiagramItem *diag);
	/**
	 * \brief Fill choice control with list of code generation algorithms.
	 * \param choice Pointer to updated choice control
	 * \param lang Pointer to language which is supported by codegen algorithm
	 * \param diag Pointer to diagram which is supported by codegen algorithm
	 * \param gen Pointer to generator which supports codegen algorithm
	 */
	WXDLLIMPEXP_CD void FillAlgorithmsChoice(wxChoice *choice, udLanguage *lang, udDiagramItem *diag, udGenerator *gen);
	/**
	 * \brief Initialize scintilla text control.
	 * \param sci Pointer to inilialized scintilla text control
	 * \param lang Pointer to programming language used in the text control
	 */
	WXDLLIMPEXP_CD void InitStyledTextCtrl(wxStyledTextCtrl *sci, udLanguage *lang);
	
	/**
	 * \brief Get default background colour
	 * \return Background colour
	 */
	WXDLLIMPEXP_CD wxColour GetBcgColour();
};

#endif //_PROJECT_BASE_COMMON_H_
