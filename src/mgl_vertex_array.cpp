#include <mgl_vertex_array.h>
#include <mgl_context_state.h>

namespace mgl
{


void VertexArray::bind()
{
	if(m_dirty)
	{
		for(uint8_t i = 0 ; i < 8 ; i++)
		{
			const auto& v = m_vaps[i];
			if(!v.b)
				continue;

			if(m_enabled_vaa[i])
			{
				glEnableVertexAttribArray(v.index);
				auto r = m_context->bindBuffer(GL_ARRAY_BUFFER,v.b);
				glVertexAttribPointer(v.index,
									  v.size,
									  v.type,
									  v.normalized,
									  v.stride,
									  v.pointer);
				m_context->bindBuffer(GL_ARRAY_BUFFER,r);

			}
			else
				glDisableVertexAttribArray(i);
		}
		if(m_element_buffer)
			m_context->bindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_element_buffer);
		m_dirty = false;
	}
}


}
