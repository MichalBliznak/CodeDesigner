#include "ProjectBase.h"
#include "codegen/CommentProcessors.h"

// function comments ///////////////////////////////////////////////////////////

udFunctionComment::udFunctionComment()
{
	RegisterDialect( wxT("udCLanguage"), new udFunctionCDialect() );
	RegisterDialect( wxT("udCPPLanguage"), new udFunctionCDialect() );
	RegisterDialect( wxT("udPythonLanguage"), new udFunctionPythonDialect() );
}

wxString udFunctionCDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
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
			
			int nIndent = lang->GetIndentation();
			lang->SetIndentation( 0 );
			lang->PushCode();
			
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
			
			sComment << ENDL;
			
			lang->MultiLineCommentCmd( sComment );
			sOut = lang->GetCodeBuffer();
			
			lang->PopCode();
			lang->SetIndentation( nIndent );
		}
	}
	
	return sOut;
}

wxString udFunctionPythonDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
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
			
			int nIndent = lang->GetIndentation();
			lang->SetIndentation( 0 );
			lang->PushCode();
			
			// generate 'brief' section
			sComment << pFcn->GetDescription() << ENDL;
			
			// generate 'param' sections
			SerializableList::compatibility_iterator it = pFcn->GetFirstChildNode();
			while( it )
			{
				udParamItem *pPar = (udParamItem*) it->GetData();
				
				sComment << wxT("  Parameter:") << lang->MakeValidIdentifier( pPar->GetName() ) << wxT(" ") << pPar->GetDescription() << ENDL;
				
				it = it->GetNext();
			}
			
			sComment << ENDL;
			
			lang->MultiLineCommentCmd( sComment );
			sOut = lang->GetCodeBuffer();
			
			lang->PopCode();
			lang->SetIndentation( nIndent );
		}
	}
	
	return sOut;
}

// variable comments ///////////////////////////////////////////////////////////

udVariableComment::udVariableComment()
{
	RegisterDialect( wxT("udCLanguage"), new udVariableCDialect() );
	RegisterDialect( wxT("udCPPLanguage"), new udVariableCDialect() );
	RegisterDialect( wxT("udPythonLanguage"), new udVariablePythonDialect() );
}

wxString udVariableCDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );

	wxString sOut;
	
	if( obj && lang )
	{
		int nIndent = lang->GetIndentation();
		lang->SetIndentation( 0 );
		lang->PushCode();
		
		lang->MultiLineCommentCmd( wxT("! \\brief ") + obj->GetDescription() );
		sOut = lang->GetCodeBuffer();
		
		lang->PopCode();
		lang->SetIndentation( nIndent );
	}
	
	return sOut;
}

wxString udVariablePythonDialect::MakeComment(const udProjectItem* obj, udLanguage* lang)
{
	wxASSERT( obj );
	wxASSERT( lang );

	wxString sOut;
	
	if( obj && lang )
	{
		int nIndent = lang->GetIndentation();
		lang->SetIndentation( 0 );
		lang->PushCode();
		
		lang->MultiLineCommentCmd( obj->GetDescription() );
		sOut = lang->GetCodeBuffer();
		
		lang->PopCode();
		lang->SetIndentation( nIndent );
	}
	
	return sOut;
}
