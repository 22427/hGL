#include <hgles_vertex_array.h>
#include <hgles_context_state.h>

namespace hgles
{

void VertexArray::elementBuffer(Buffer *b)
{
	m_element_buffer = b;
	m_dirty = true;
}

void VertexArray::vertexAttribPointer(Buffer *b, GLuint attrib_index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
	if(glBindVertexArrayOES)
	{
		m_context->bindVertexArray(this);
		m_context->bindBuffer(GL_ARRAY_BUFFER,b);
		glVertexAttribPointer(attrib_index,
							  size,
							  type,
							  normalized,
							  stride,
							  pointer);
	}
	else
	{
		m_vaps[attrib_index].buffer = b;
		m_vaps[attrib_index].index = attrib_index;
		m_vaps[attrib_index].size = size;
		m_vaps[attrib_index].type = type;
		m_vaps[attrib_index].normalized = normalized;
		m_vaps[attrib_index].stride = stride;
		m_vaps[attrib_index].pointer = pointer;
	}

}

void VertexArray::enableVertexAttribArray(GLuint attrib_index)
{
	if(glBindVertexArrayOES)
	{
		m_context->bindVertexArray(this);
		glEnableVertexAttribArray(attrib_index);
	}
	else
	{
		m_enabled_vaa[attrib_index] = true;
	}
}

void VertexArray::disableVertexAttribArray(GLuint attrib_index)
{
	if(glBindVertexArrayOES)
	{
		m_context->bindVertexArray(this);
		glDisableVertexAttribArray(attrib_index);
	}
	else
	{
		m_enabled_vaa[attrib_index] = false;
	}
}



}
