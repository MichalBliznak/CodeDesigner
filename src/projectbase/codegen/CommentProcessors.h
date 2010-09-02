#ifndef _UDCOMMENTPROCESSORS_H_
#define _UDCOMMENTPROCESSORS_H_

#include "Generator.h"

// function comments ///////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udFunctionComment : public udCommentProcessor
{
public:
	udFunctionComment();
	virtual ~udFunctionComment() {;}
};

class WXDLLIMPEXP_CD udFunctionCDialect : public udCommentDialect
{
public:
	virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
};

class WXDLLIMPEXP_CD udFunctionPythonDialect : public udCommentDialect
{
public:
	virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
};

// variable comments ///////////////////////////////////////////////////////////

class WXDLLIMPEXP_CD udVariableComment : public udCommentProcessor
{
public:
	udVariableComment();
	virtual ~udVariableComment() {;}
};

class WXDLLIMPEXP_CD udVariableCDialect : public udCommentDialect
{
public:
	virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
};

class WXDLLIMPEXP_CD udVariablePythonDialect : public udCommentDialect
{
public:
	virtual wxString MakeComment(const udProjectItem* obj, udLanguage* lang);
};

// class comments //////////////////////////////////////////////////////////////

#endif //_UDCOMMENTPROCESSORS_H_
