
#include <hgles_context_state.h>
#include <hgles_buffer.h>

namespace hgles
{

void Buffer::bufferData(GLsizei size, const void *data, GLenum usage)
{
	m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	glBufferData(GL_ARRAY_BUFFER,size,data,usage);
}

void Buffer::bufferSubData(GLsizei size, GLintptr offset, const void *data)
{
	m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	glBufferSubData(GL_ARRAY_BUFFER,size,offset,data);
}

void *Buffer::mapBuffer(GLenum access)
{
	m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	return glMapBufferOES(GL_ARRAY_BUFFER, access);
}

GLboolean Buffer::unmapBuffer()
{
	m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	auto res =  glUnmapBufferOES(GL_ARRAY_BUFFER);
	return  res;
}

}
