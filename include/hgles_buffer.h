#pragma once

#include "hgles_object.h"
namespace hgles
{

class MGL_DLL_PUBLIC Buffer : public Object
{
protected:

public:

	friend class ContextState;
	friend class VertexArray;


	Buffer(ContextState* origin_context=nullptr, GLuint name=0)
		:Object(origin_context,name)
	{}

	void bufferData(GLsizei size, const void* data, GLenum usage);

	void bufferSubData(GLsizei size,GLintptr offset , const void* data) ;

	void* mapBuffer (GLenum access = GL_WRITE_ONLY_OES);

	GLboolean unmapBuffer ();
};
}
