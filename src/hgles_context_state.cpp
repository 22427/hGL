#include <hgles_context_state.h>
#include <fstream>
#include <cstring>
#include <hgles_log.h>

namespace hgles {


ContextState::ContextState()
{

	m_vao = nullptr;

	m_clear_color= glm::vec4(0,0,0,1);

	m_clear_depth= 1.0f;
	m_clear_setncil = 0;

	m_program = nullptr;
	m_framebuffer= nullptr;
	m_renderbuffer=nullptr;
	m_active_tu = 0;

	m_array_buf = m_index_buf = nullptr;
	m_next_vertex_array = 0;


}

void ContextState::activeTexture(const GLenum textureUnit)
{
	auto new_tu = textureUnit-GL_TEXTURE0;
	if(m_active_tu != new_tu)
		glActiveTexture(textureUnit);
	m_active_tu = new_tu;
}


void ContextState::bindFramebuffer(const GLenum /*target*/, const Framebuffer */*f*/)
{

}


void ContextState::bindRenderbuffer(const GLenum /*target*/, const Renderbuffer */*f*/)
{

}


void ContextState::bindVertexArray(VertexArray *vao)
{
	if(!vao)
	{
		if(glBindVertexArrayOES)
			glBindVertexArrayOES(0);
		else
		{
			for(uint8_t i = 0 ; i < 8 ; i++)
			{
				glDisableVertexAttribArray(i);
			}
			bindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
			bindBuffer(GL_ARRAY_BUFFER,0);
		}
	}
	else
	{
		if(glBindVertexArrayOES)
			glBindVertexArrayOES(vao->name);
		else
		{
			for(uint8_t i = 0 ; i < 8 ; i++)
			{
				const auto& v = vao->m_vaps[i];
				if(!v.buffer)
					continue;
				if(vao->m_enabled_vaa[i] )
				{
					if(!m_vao->m_enabled_vaa[i]) // attribute was not enabled
						glEnableVertexAttribArray(v.index);

					bindBuffer(GL_ARRAY_BUFFER,v.buffer);
					glVertexAttribPointer(v.index,
										  v.size,
										  v.type,
										  v.normalized,
										  v.stride,
										  v.pointer);
				}
				else if(m_vao->m_enabled_vaa[i]) // attribute was enabled
					glDisableVertexAttribArray(i);
			}
			if(vao->m_element_buffer)
				bindBuffer(GL_ELEMENT_ARRAY_BUFFER,vao->m_element_buffer);
			else
				bindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		}
	}
	m_vao = vao;
}


void ContextState::bindBuffer(const GLenum target, const Buffer *b)
{

	auto& m_b = (target == GL_ARRAY_BUFFER)?(m_array_buf):(m_index_buf) ;
	if(b && m_b != b)
		glBindBuffer(target,b->name);
	else if(!b)
		glBindBuffer(target,0);
	m_b = b;
}



void ContextState::bindTexture(const GLenum target, const Texture *t)
{

	auto& curr = m_tu[m_active_tu].tex2d;
	if(target == GL_TEXTURE_CUBE_MAP)
		curr = m_tu[m_active_tu].cube;

	if(t && curr != t)
		glBindTexture(target,t->name);
	else if(!t)
		glBindTexture(target,0);
	curr = t;

}

void ContextState::useProgram(const Program *prog)
{

	if(prog && m_program != prog)
		glUseProgram(prog->name);
	else if(!prog)
		glUseProgram(0);
	m_program = prog;
}

Buffer* ContextState::createBuffer()
{
	GLuint n;
	glGenBuffers(1,&n);
	return new   Buffer(this,n);
}

Shader* ContextState::createShader(GLenum shader_type)
{
	auto n = glCreateShader(shader_type);
	return new  Shader(this,n);
}

Texture* ContextState::createTexture(GLenum target)
{
	GLuint n;
	glGenTextures(1,&n);
	return new  Texture(this,n,target);
}

Program* ContextState::createProgram()
{
	auto n = glCreateProgram();
	return new  Program(this,n);
}

VertexArray* ContextState::createVertexArray()
{
	GLuint vao = 0;
	if(!glBindVertexArrayOES)
	{
		m_next_vertex_array++;
		vao = m_next_vertex_array;
	}
	else
	{
		glGenVertexArraysOES(1,&vao);
	}
	return new  VertexArray(this,m_next_vertex_array);
}

Shader* ContextState::util_create_shader(GLenum shader_type, const std::string &code)
{
	auto res = createShader(shader_type);
	res->shaderSource(code);
	if(!res->util_compile())
	{
		WARNING("Compiling shader failed: %s",res->util_read_log().c_str());
		return res;
	}
	return res;
}

Shader* ContextState::util_load_shader(GLenum shader_type,
									   const std::string &path)
{
	std::ifstream t(path);
	if(!t.is_open())
	{
		WARNING("Could not open shader file %s",path.c_str());
	}
	std::string code((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());

	return util_create_shader(shader_type,code);
}


std::string ContextState::util_error_string(const GLenum error)
{

#define TO_STR(s)  case s: return #s
	switch (error)
	{
	TO_STR(GL_NO_ERROR);
	TO_STR(GL_INVALID_ENUM);
	TO_STR(GL_INVALID_VALUE);
	TO_STR(GL_INVALID_OPERATION);
	TO_STR(GL_OUT_OF_MEMORY);
	default: return  "UNKNOWN_ERROR";
	}
#undef TO_STR
}

bool ContextState::util_error_check(const std::string &tect)
{
#ifndef NDEBUG
	GLenum error_code;
	error_code = glGetError();
	if (error_code != GL_NO_ERROR)
	{
		ERROR("[glERR] %s:%s",tect.c_str(),util_error_string(error_code).c_str());
		return true;
	}
	return false;
#else
	retrun false
		#endif
}

Program* ContextState::util_create_program(const std::string &vs_c,
										   const std::string &fs_c)
{
	auto vs = util_create_shader(GL_VERTEX_SHADER,vs_c);
	auto fs = util_create_shader(GL_FRAGMENT_SHADER,fs_c);

	auto res = createProgram();
	res->attachShader(vs);
	res->attachShader(fs);
	if(!res->util_link())
	{
		WARNING("Linking program failed: %s",res->util_read_log().c_str());
	}
	return res;
}

Program* ContextState::util_load_program(const std::string &vs_path,
										 const std::string &fs_path)
{
	auto vs = util_load_shader(GL_VERTEX_SHADER,vs_path);
	auto fs = util_load_shader(GL_FRAGMENT_SHADER,fs_path);

	auto res = createProgram();
	res->attachShader(vs);
	res->attachShader(fs);
	if(!res->util_link())
	{
		WARNING("Linking program failed: %s",res->util_read_log().c_str());
	}
	return  res;
}

}
