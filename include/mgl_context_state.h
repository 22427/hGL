#pragma once
#include <glad/glad.h>
#include <functional>

#include <cstring>

#include <glm/vec4.hpp>
#include "mgl_window.h"
#include "mgl_object.h"
#include "mgl_buffer.h"
#include "mgl_shader.h"
#include "mgl_texture.h"
#include "mgl_vertex_array.h"
#include "mgl_log.h"
namespace mgl
{

class Framebuffer;
class Renderbuffer;
class ContextState
{
	friend class Texture;
	friend class Buffer;
	friend class VertexArray;

protected:
#define IS 0
#define SB 1
	GLenum m_tu_active[2];
	GLuint m_tu_tex2d[2];
	GLuint m_tu_cube[2];

	GLuint m_vao[2];

	GLuint m_buf_bindings[2][2];



	glm::vec4 m_clear_color[2];
	GLfloat m_clear_depth[2];
	GLint m_clear_setncil[2];

	GLuint m_program[2];

	GLuint m_framebuffer[2];
	GLuint m_renderbuffer[2];


	GLuint m_next_vertex_array;

public:

	ContextState()
	{
		m_tu_active[0] = m_tu_active[1]= GL_TEXTURE0;
		m_tu_tex2d[0] = m_tu_tex2d[1]= 0;
		m_tu_cube[0] = m_tu_cube[1]= 0;

		m_vao[0] = m_vao[1] = 0;
		memset(m_buf_bindings,0,4*sizeof(GLuint));
		m_clear_color[0] = m_clear_color[1] = glm::vec4(0,0,0,1);

		m_clear_depth[0] = m_clear_depth[1] = 1.0f;
		m_clear_setncil[0] = m_clear_setncil[1] = 0;

		m_program[0] = m_program[1] = 0;
		m_framebuffer[0] = m_framebuffer[1] = 0;
		m_renderbuffer[0] = m_renderbuffer[1] = 0;

		m_next_vertex_array = 0;



	}

	~ContextState();

	void activeTexture(const GLenum textureUnit)
	{
		if(m_tu_active[IS] != textureUnit)
		{
			glActiveTexture(textureUnit);
		}
		m_tu_active[IS] = textureUnit;
		m_tu_active[SB] = m_tu_active[IS];
	}

	void loc_activeTexture(const GLenum textureUnit)
	{
		if(m_tu_active[IS] != textureUnit)
		{
			glActiveTexture(textureUnit);
		}
		m_tu_active[IS] = textureUnit;
	}

	void bindFramebuffer(const GLenum target, const Framebuffer& f)
	{

//		m_framebuffer[SB] = m_tu_active[IS];
	}

	void loc_bindFramebuffer(const GLenum target, const Framebuffer& f)
	{

	}


	void bindRenderbuffer(const GLenum target, const Renderbuffer& f)
	{

	}

	void loc_bindRenderbuffer(const GLenum target, const Renderbuffer& f)
	{

	}

	void bindVertexArray(VertexArray& vao)
	{
		vao.bind();
	}

	void loc_bindVertexArray(VertexArray& vao)
	{
		vao.loc_bind();
	}

	void bindBuffer(const GLenum target, const Buffer& b)
	{
		if(m_buf_bindings[target-GL_ARRAY_BUFFER][IS] != b.name)
		{
			glad_glBindBuffer(target,b.name);
		}
		m_buf_bindings[target-GL_ARRAY_BUFFER][IS] = b.name;
		m_buf_bindings[target-GL_ARRAY_BUFFER][SB] = m_buf_bindings[target-GL_ARRAY_BUFFER][IS];

	}

	void loc_bindBuffer(const GLenum target, const Buffer& b)
	{
		if(m_buf_bindings[target-GL_ARRAY_BUFFER][IS] != b.name)
		{
			glad_glBindBuffer(target,b.name);
		}
		m_buf_bindings[target-GL_ARRAY_BUFFER][IS] = b.name;
	}


	void bindTexture(const GLenum target, const Texture& b)
	{
		auto s = m_tu_tex2d;
		if(target == GL_TEXTURE_CUBE_MAP)
			s = m_tu_cube;

		if(s[IS] != b.name)
		{
			glBindTexture(target,b.name);
		}
		s[IS] = b.name;
	}

	void loc_bindTexture(const GLenum target, const Texture& b)
	{
		auto s = m_tu_tex2d;
		if(target == GL_TEXTURE_CUBE_MAP)
			s = m_tu_cube;

		if(s[IS] != b.name)
		{
			glBindTexture(target,b.name);
		}
		s[IS] = b.name;
		s[SB] = s[IS];
	}


	void useProgram(const Program& prog)
	{
		if(m_program[IS] != prog.name)
		{
			glUseProgram(prog.name);
		}
		m_program[IS] = prog.name;
		m_program[SB] = m_program[IS];
	}

	void loc_useProgram(const Program& prog)
	{
		if(m_program[IS] != prog.name)
		{
			glUseProgram(prog.name);
		}
		m_program[IS] = prog.name;
		m_program[SB] = m_program[IS];
	}

	Buffer createBuffer()
	{
		GLuint n;
		glGenBuffers(1,&n);
		return  Buffer(this,n);
	}
	Shader createShader(GLenum shader_type)
	{
		auto n = glCreateShader(shader_type);
		return Shader(this,n);
	}

	Texture createTexture(GLenum target)
	{
		GLuint n;
		glGenTextures(1,&n);
		return Texture(this,n,target);
	}
	Program createProgram()
	{
		auto n = glCreateProgram();
		return Program(this,n);
	}

	VertexArray createVertexArray()
	{
		m_next_vertex_array++;
		return VertexArray(this,m_next_vertex_array);
	}

	Shader util_create_shader(GLenum shader_type, const std::string& code);
	Program util_create_program(const std::string& vs_code, const std::string& fs_code);

	Program util_load_program(const std::string& vs_path, const std::string& fs_path);
	Shader util_load_shader(GLenum shader_type, const std::string& path);
	Texture  util_load_texture2D(GLenum internal_format, const std::string& path);

	std::string util_error_string(const GLenum error) ;

	bool util_error_check(const std::string& tect)
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
};


}
