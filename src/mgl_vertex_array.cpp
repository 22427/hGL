#include <mgl_vertex_array.h>
#include <mgl_context_state.h>

namespace mgl
{

void VertexArray::loc_bind()
{
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		const auto& v = m_vaps[i];
		if(m_enabled_vaa[i])
		{

			m_context->loc_bindBuffer(GL_ARRAY_BUFFER,v.b);
			glVertexAttribPointer(v.index,
								  v.size,
								  v.type,
								  v.normalized,
								  v.stride,
								  v.pointer);
			glEnableVertexAttribArray(v.index);
		}
		else
			glDisableVertexAttribArray(v.index);
	}
	m_dirty = false;
	if(m_element_buffer.name)
		m_context->loc_bindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_element_buffer);
}

void VertexArray::bind()
{
	for(uint8_t i = 0 ; i < 8 ; i++)
	{
		const auto& v = m_vaps[i];
		if(m_enabled_vaa[i])
		{

			m_context->bindBuffer(GL_ARRAY_BUFFER,v.b);
			glVertexAttribPointer(v.index,
								  v.size,
								  v.type,
								  v.normalized,
								  v.stride,
								  v.pointer);
			glEnableVertexAttribArray(v.index);
		}
		else
			glDisableVertexAttribArray(v.index);
	}
	if(m_element_buffer.name)
		m_context->bindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_element_buffer);
	m_dirty = false;
}


}
