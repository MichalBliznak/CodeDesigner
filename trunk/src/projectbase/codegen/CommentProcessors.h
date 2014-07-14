#ifndef _UDCOMMENTPROCESSORS_H_
#define _UDCOMMENTPROCESSORS_H_

#include "Generator.h"

// function comments ///////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udFunctionComment : public udCommentProcessor
{
public:
	udFunctionComment();
	virtual ~udFunctionComment() {;}
	
	class udCDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};

	class udPythonDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};
};

// variable comments ///////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udVariableComment : public udCommentProcessor
{
public:
	udVariableComment();
	virtual ~udVariableComment() {;}
	
	class udCDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};

	class udPythonDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};
};

// class comments //////////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udClassComment : public udCommentProcessor
{
public:
	udClassComment();
	virtual ~udClassComment() {;}
	
	class udCDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};

	class udPythonDialect : public udCommentDialect
	{
	public:
		virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
	};
};



#endif //_UDCOMMENTPROCESSORS_H_
