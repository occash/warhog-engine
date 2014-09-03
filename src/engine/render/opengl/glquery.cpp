#include "glquery.h"
#include "glextensions.h"

GLQuery::GLQuery(unsigned int target) :
	_target(target)
{
	glGenQueries(1, &_query);
}

GLQuery::~GLQuery()
{
	glDeleteQueries(1, &_query);
}

void GLQuery::begin()
{
	glBeginQuery(_target, _query);
}

void GLQuery::end()
{
	glEndQuery(_target);
}

bool GLQuery::ready() const
{
	GLint result = GL_FALSE;
	glGetQueryObjectiv(_query, GL_QUERY_RESULT_AVAILABLE, &result);
	return result == GL_TRUE;
}

int GLQuery::result() const
{
	GLint result = 0;
	glGetQueryObjectiv(_query, GL_QUERY_RESULT, &result);
	return result;
}
