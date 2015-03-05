#ifndef _IPROJECT_H_
#define _IPROJECT_H_

#include "../projectbase/Common.h"

#include <wx/wxsf/wxShapeFramework.h>

class udDiagElementItem;
class udDiagramItem;
class udFunctionItem;
class udCodeItem;
class udDiagramCanvas;
class udLanguage;

/**
 * \class IProject
 * \author Michal
 * \date 12.2.2010
 * \file IProject.h
 * \brief Abstract base class for CodeDesigner project providing set of function usefull for handling 
 * of active project and its item. Note that there is a set of static functions declared in udPROJECT 
 * namespace that can be used for this purpose as well.
 * \sa udPROJECT, udLABEL, udFRAME
 */
class IProject : public wxXmlSerializer
{	
public:
	virtual ~IProject() {}
	
	// names function
	/**
	 * \brief Make unique project item name.
	 * \param name Name which should be unique
	 * \param threshold Number of allowed same names
	 * \return Unique version of given name
	 */
	virtual wxString MakeUniqueName(const wxString& name, int threshold = 0) = 0;
	/**
	 * \brief Test whether given project item name is an unique.
	 * \param name Examined name
	 * \return TRUE if the name is unique in the project
	 */
	virtual bool IsUniqueName(const wxString& name) = 0;
	
	// element manipulations
	/**
	 * \brief Create new project item and add it to the project.
	 * \param classname Class name of new project item
	 * \param parentId ID of parent project item
	 * \return Pointer to newly created project item on success, otherwise NULL
	 */
	virtual udProjectItem* CreateProjectItem(const wxString& classname, long parentId) = 0;
	/**
	 * \brief Get diagram element of given name (from any diagram in the project).
	 * \param element Diagram element name
	 * \return Pointer to diagram element if exists, otherwise NULL
	 */
	virtual udDiagElementItem* GetDiagramElement(const wxString& element) = 0;
	/**
	 * \brief Get diagram element of given name from specified diagram.
	 * \param diagram Diagram name
	 * \param element Diagram element name
	 * \return Pointer to diagram element if exists, otherwise NULL
	 */
	virtual udDiagElementItem* GetDiagramElement(const wxString& diagram, const wxString& element) = 0;
	/**
	 * \brief Get all diagram elements of given type (from all diagrams in the project)
	 * \param type Diagram element type
	 * \param elements List where pointers to diagram elements will be stored to
	 */
	virtual void GetDiagramElements(wxClassInfo *type, SerializableList& elements) = 0;
	/**
	 * \brief Get project item of given type and name
	 * \param type Project item type
	 * \param name Project item name
	 * \return Pointer to project item if exists, otherwise NULL
	 */
	virtual udProjectItem* GetProjectItem(wxClassInfo *type, const wxString& name) = 0;
	
	// code items manipulations
	/**
	 * \brief Get code item.
	 * \param type Code item type
	 * \param name Code item name
	 * \param scope Code item scope
	 * \return Pointer to code item if exists, otherwise NULL
	 */
	virtual udCodeItem* GetCodeItem(wxClassInfo* type, const wxString& name, const wxString& scope) = 0;
	/**
	 * \brief Get all code items referenced by given diagram.
	 * \param diagram Diagram where code items are used
	 * \param type Code items type
	 * \param codeitems List where found code items will be stored to
	 */
	virtual void GetDiagramCodeItems(udDiagramItem *diagram, wxClassInfo *type, SerializableList& codeitems) = 0;
	/**
	 * \brief Get a function (code item) which is implemented by given diagram.
	 * \param diag Diagram which implements function's functionality
	 * \return Pointer to function item if exists, otherwise NULL
	 */
	virtual udFunctionItem* GetFunctionImplementedBy(const udDiagramItem *diag) = 0;
	
	// links manipulations
	/**
	 * \brief Get links to given diagram element.
	 * \param diagram Name of diagram where the element is located in (can be empty string)
	 * \param element Name of original diagram element (can be empty string)
	 * \param elements List where all found links will be stored to
	 */
	virtual void GetElementLinks(const wxString& diagram, const wxString& element, SerializableList& elements) = 0;
	/**
	 * \brief Get code items links.
	 * \param valid TRUE for valid links, FALSE for invalid links
	 * \param type Code items type
	 * \param codeitem Name of original code item
	 * \param scope Scope of original code item
	 * \param elements List where all found links will be stored to
	 */
	virtual void GetCodeLinks(bool valid, wxClassInfo *type, const wxString& codeitem, const wxString& scope, SerializableList& elements) = 0;
	/**
	 * \brief Remove invalid element links.
	 */
	virtual void CheckElementLinks() = 0;
	/**
	 * \brief Remove invalid code links.
	 */
	virtual void CheckCodeLinks() = 0;
	
	// diagram manipulations
	/**
	 * \brief Get diagram item.
	 * \param name Diagram name
	 * \return Pointer to diagram if exists, otherwise NULL
	 */
	virtual udDiagramItem* GetDiagram(const wxString& name) = 0;
	/**
	 * \brief Get diagram item.
	 * \param canvas Pointer to shape canvas where diagram components are displayed on
	 * \return Pointer to diagram if exists, otherwise NULL
	 */
	virtual udDiagramItem* GetDiagram(udDiagramCanvas *canvas) = 0;
	/**
	 * \brief Get all diagrams and their subdiagrams.
	 * \param type Diagram type
	 * \param diagrams List where pointers to the diagrams will be stored to
	 */
	virtual void GetDiagramsRecursively(wxClassInfo *type, SerializableList& diagrams) = 0;
	/**
	 * \brief Close all opened diagrams.
	 */
	virtual void CloseAllDiagrams() = 0;
};

/**
 * \class IProjectItem
 * \author Michal
 * \date 9.2.2010
 * \file IProject.h
 * \brief Abstract base class for all project items/diagram elements. The class contains set of (pure) virtual functions
 * that must be implemented and which allow user to handle various events.
 */
class IProjectItem : public xsSerializable
{	
public:	
    virtual ~IProjectItem() {}

	// virtual public functions
	/**
	 * \brief Set item's name. The name can be modified to be unique if required.
	 * \param name Name
	 */
	virtual void SetName(const wxString& name) = 0;
	/**
	 * \brief Set item's description. 
	 * \param desc Destription
	 */
	virtual void SetDescription(const wxString& desc) = 0;

	/**
	 * \brief Get item's name.
	 * \return Item's name
	 */
    virtual const wxString& GetName() const = 0;
	/**
	 * \brief Get item's description.
	 * \return Item's description
	 */
	virtual const wxString& GetDescription() const = 0;
	/**
	 * \brief Get unique ID based on the item's name, parent's name and given language.
	 * \param lang Pointer to output programming language
	 * \return Unique ID
	 */
	virtual wxString GetUniqueId(const udLanguage *lang) = 0;
	
	/**
	 * \brief Set type of project item which can be assigned to this item
	 * as its child (via dnd in project structure tree).
	 * \param classname Child item's type
	 */
	virtual void AcceptChild(const wxString& classname) = 0;
	/**
	 * \brief Set type of project item which can be assigned to this item
	 * as its sibbling (via dnd in project structure tree).
	 * \param classname Sibbling item's type
	 */
	virtual void AcceptSibbling(const wxString& classname) = 0;
	/**
	 * \brief Determine whether item of given type is accepted as a child.
	 * \param classname Item's type
	 * \return 
	 */
	virtual bool IsChildAccepted(const wxString& classname) const = 0;
	/**
	 * \brief Determine whether item of given type is accepted as a child.
	 * \param classname Item's type
	 * \return 
	 */
	virtual bool IsSibblingAccepted(const wxString& classname) const = 0;
	/**
	 * \brief Set whether item's name must be unique.
	 * \param unique TRUE if the name must be unique
	 */
	virtual void SetMustBeUnique(bool unique) = 0;
	/**
	 * \brief Determine whether item's name must be unique.
	 * \return TRUE if the name must be unique
	 */
	virtual bool MustBeUnique() const = 0;

	/**
	 * \brief Create project item's context menu (if needed).
	 * \return Pointer to item's context menu (the application will delete it after an usage)
	 */
	virtual wxMenu* CreateMenu() = 0;
	
	/**
	 * \brief Function called after the item's creation.
	 */
	virtual void OnCreate() = 0;
	/**
	 * \brief Function called when a new item's copy (via dnd or paste) is created.
	 */
	virtual void OnCreateCopy() = 0;
	/**
	 * \brief Function called if item's name was modified via project structure tree.
	 * \param txt New name
	 */
	virtual void OnTreeTextChange(const wxString& txt) = 0;
	/**
	 * \brief Function called if item's name was modified via related diagram component.
	 * \param txt New name
	 * \param type Type of diagram component label which was modified
	 * \param id ID of modified diagram component
	 */
	virtual void OnShapeTextChange(const wxString& txt, udLABEL::TYPE type, int id) = 0;
	/**
	 * \brief Function called if item has started to be dragged in project structure tree.
	 * \param pos Initila dragging position
	 * \return TRUE if standard dnd implementation in tree control should be suppressed
	 */
	virtual bool OnTreeItemBeginDrag(const wxPoint& pos) = 0;
	/**
	 * \brief Function called if item's dragging has ended in project structure tree.
	 * \param pos Position where the item was dropped to
	 */
	virtual void OnTreeItemEndDrag(const wxPoint& pos) = 0;
	/**
	 * \brief Function called if item's modification is requested.
	 * \param parent Pointer to window which should be used as a parent for potentialy displayed
	 * properties dialog.
	 */
    virtual void OnEditItem(wxWindow* parent) = 0;
	/**
	 * \brief Function called if the item has been selected.
	 */
    virtual void OnSelection() = 0;
	/**
	 * \brief Function called  if the item has been activated (double-clicked by LMB).
	 */
    virtual void OnActivation() = 0;
	/**
	 * \brief Function called if item's context menu should be displayed.
	 * \param parent
	 * \param pos
	 */
    virtual void OnContextMenu(wxWindow* parent, const wxPoint& pos) = 0;
	
protected:
	// virtual protected functions
	/**
	 * \brief Get unique name based on current item's name.
	 * \return Unique item's name
	 */
	virtual wxString GetUniqueName(const wxString& name) = 0;
};

#endif //_IPROJECT_H_
