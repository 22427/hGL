
#include <mgl_context_state.h>
#include <mgl_buffer.h>

namespace mgl
{

void Buffer::bufferData(GLsizei size, const void *data, GLenum usage)
{
	m_context->loc_bindBuffer(GL_ARRAY_BUFFER,*this);
	glBufferData(GL_ARRAY_BUFFER,size,data,usage);
}

void Buffer::bufferSubData(GLsizei size, GLintptr offset, const void *data)
{
	m_context->loc_bindBuffer(GL_ARRAY_BUFFER,*this);
	glBufferSubData(GL_ARRAY_BUFFER,size,offset,data);
}

void *Buffer::mapBuffer(GLenum access)
{
	m_context->loc_bindBuffer(GL_ARRAY_BUFFER,*this);
	return glMapBufferOES(GL_ARRAY_BUFFER, access);
}

GLboolean Buffer::unmapBuffer()
{
	m_context->loc_bindBuffer(GL_ARRAY_BUFFER,*this);
	return glUnmapBufferOES(GL_ARRAY_BUFFER);
}

}
