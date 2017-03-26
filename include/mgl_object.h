#pragma once
#include <glad/glad.h>

namespace mgl
{
class ContextState;
class Object
{
protected:

	ContextState* m_context;

public:
	Object(ContextState* origin_context = nullptr, GLuint name=0):m_context(origin_context),name(name)
	{

	}
	GLuint name;
};
}
