#include "ProjectBase.h"
#include "codegen/CommentProcessors.h"

// function comments ///////////////////////////////////////////////////////////

udFunctionComment::udFunctionComment()
{
	RegisterDialect( wxT("udCLanguage"), new udCDialect() );
	RegisterDialect( wxT("udCPPLanguage"), new udCDialect() );
	RegisterDialect( wxT("udPythonLanguage"), new udPythonDialect() );
}

wxString udFunctionComment::udCDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );

	if( obj && lang )
	{
		// generate doxygen comments for given function
		udFunctionItem *pFcn = wxDynamicCast( obj, udFunctionItem );
		if( pFcn )
		{
			wxString sComment;
			
			sComment << wxT("!") << ENDL;
			// generate 'brief' section
			sComment << wxT(" \\brief ") << pFcn->GetDescription() << ENDL;
			
			// generate 'param' sections
			SerializableList::compatibility_iterator it = pFcn->GetFirstChildNode();
			while( it )
			{
				udParamItem *pPar = (udParamItem*) it->GetData();
				
				sComment << wxT(" \\param ") << lang->MakeValidIdentifier( pPar->GetName() ) << wxT(" ") << pPar->GetDescription() << ENDL;
				
				it = it->GetNext();
			}
			
			// generate 'return' section
			if( pFcn->GetRetValDataType() == udLanguage::DT_USERDEFINED )
			{
				if( !pFcn->GetUserRetValDataType().IsEmpty() ) sComment << wxT(" \\return ") << lang->GetValueType( pFcn->GetRetValType() ).Name() << wxT(" of type ") << pFcn->GetUserRetValDataType();
			}
			else if( pFcn->GetRetValDataType() != udLanguage::DT_VOID )
			{
				sComment << wxT(" \\return ") << lang->GetValueType( pFcn->GetRetValType() ).Name() << wxT(" of type ") << lang->GetDataTypeString( pFcn->GetRetValDataType() );
			}
			
			return lang->GetCommented( sComment );
		}
	}
	
	return wxEmptyString;
}

wxString udFunctionComment::udPythonDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );
	
	wxString sOut;
	
	if( obj && lang )
	{
		// generate doxygen comments for given function
		udFunctionItem *pFcn = wxDynamicCast( obj, udFunctionItem );
		if( pFcn )
		{
			wxString sComment;
			
			// generate 'brief' section
			sComment << pFcn->GetDescription() << ENDL;
			
			// generate 'param' sections
			SerializableList::compatibility_iterator it = pFcn->GetFirstChildNode();
			while( it )
			{
				udParamItem *pPar = (udParamItem*) it->GetData();
				
				sComment << wxT("  Param: ") << lang->MakeValidIdentifier( pPar->GetName() ) << wxT(" - ") << pPar->GetDescription() << ENDL;
				
				it = it->GetNext();
			}
			
			return lang->GetCommented( sComment );
		}
	}
	
	return wxEmptyString;
}

// variable comments ///////////////////////////////////////////////////////////

udVariableComment::udVariableComment()
{
	RegisterDialect( wxT("udCLanguage"), new udCDialect() );
	RegisterDialect( wxT("udCPPLanguage"), new udCDialect() );
	RegisterDialect( wxT("udPythonLanguage"), new udPythonDialect() );
}

wxString udVariableComment::udCDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );
	
	if( obj && lang )
	{
		return lang->GetCommented( wxT("! \\brief ") + obj->GetDescription() + wxT(" ") );
	}
	else
		return wxEmptyString;
}

wxString udVariableComment::udPythonDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );

	if( obj && lang )
	{
		return lang->GetCommented( wxT(" ") + obj->GetDescription() + wxT(" ") );
	}
	else
		return wxEmptyString;
}

// class comments //////////////////////////////////////////////////////////////

udClassComment::udClassComment()
{
	RegisterDialect( wxT("udCLanguage"), new udCDialect() );
	RegisterDialect( wxT("udCPPLanguage"), new udCDialect() );
	RegisterDialect( wxT("udPythonLanguage"), new udPythonDialect() );
}

wxString udClassComment::udCDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );
	
	if( obj && lang )
	{
		return lang->GetCommented( wxT("! \\brief ") + obj->GetDescription() + wxT(" ") );
	}
	else
		return wxEmptyString;
}

wxString udClassComment::udPythonDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );

	if( obj && lang)
	{
		return lang->GetCommented( wxT(" ") + obj->GetDescription() + wxT(" ") );
	}
	else
		return wxEmptyString;
}
