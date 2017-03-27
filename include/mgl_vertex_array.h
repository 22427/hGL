#pragma once
#include <glad/glad.h>
#include "mgl_buffer.h"
#include <map>
namespace mgl
{

class VertexArray : public Object
{
protected:
	class VAP
	{
	public:
		VAP(Buffer* b =nullptr,
			GLuint attrib_index = 0,
			GLint size = 0, GLenum type=GL_FLOAT,
			GLboolean normalized=GL_FALSE,
			GLsizei stride=0, const void *pointer=nullptr):b(b)
		{
			this->index = attrib_index;
			this->size = size;
			this->type = type;
			this->normalized = normalized;
			this->stride = stride;
			this->pointer = pointer;
		}
		Buffer* b;
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const GLvoid* pointer;
	};

	VAP m_vaps[8];
	bool m_enabled_vaa[8];
	bool m_dirty;

	Buffer* m_element_buffer;


	void loc_bind();
	void bind();

public:
	VertexArray(ContextState* origin_context=nullptr, GLuint name=0)
		:Object(origin_context,name),m_element_buffer(nullptr)
	{
		for(uint8_t i = 0 ; i<8;i++)
		{
			m_enabled_vaa[i] = false;
		}

		m_dirty = true;
	}

	friend class ContextState;

	void elementBuffer(Buffer* b)
	{
		m_element_buffer = b;
		m_dirty = true;
	}

	void vertexAttribPointer(Buffer* b, GLuint attrib_index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
	{
		m_vaps[attrib_index].b = b;
		m_vaps[attrib_index].index = attrib_index;
		m_vaps[attrib_index].size = size;
		m_vaps[attrib_index].type = type;
		m_vaps[attrib_index].normalized = normalized;
		m_vaps[attrib_index].stride = stride;
		m_vaps[attrib_index].pointer = pointer;
		m_dirty = true;
	}

	void enableVertexAttribArray(GLuint attrib_index)
	{
		m_enabled_vaa[attrib_index] = true;
		m_dirty = true;
	}

	void disableVertexAttribArray(GLuint attrib_index)
	{
		m_enabled_vaa[attrib_index] = false;
		m_dirty = true;
	}


};


}
