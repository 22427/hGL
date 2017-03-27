
#include <mgl_context_state.h>
#include <mgl_buffer.h>

namespace mgl
{

void Buffer::bufferData(GLsizei size, const void *data, GLenum usage)
{
	auto r = m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	glBufferData(GL_ARRAY_BUFFER,size,data,usage);
	m_context->bindBuffer(GL_ARRAY_BUFFER,r);
}

void Buffer::bufferSubData(GLsizei size, GLintptr offset, const void *data)
{
	auto r = m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	glBufferSubData(GL_ARRAY_BUFFER,size,offset,data);
	m_context->bindBuffer(GL_ARRAY_BUFFER,r);
}

void *Buffer::mapBuffer(GLenum access)
{
	m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	return glMapBufferOES(GL_ARRAY_BUFFER, access);
}

GLboolean Buffer::unmapBuffer()
{
	auto r = m_context->bindBuffer(GL_ARRAY_BUFFER,this);
	auto res =  glUnmapBufferOES(GL_ARRAY_BUFFER);
	m_context->bindBuffer(GL_ARRAY_BUFFER,r);
	return  res;
}

}
