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

#define IS 0
#define SB 1




struct MGL_DLL_PUBLIC TextureUnitState
{
	const Texture* tex2d;
	const Texture* cube;
	TextureUnitState()
	{
		tex2d = nullptr;
		cube = nullptr;
	}
};


class Framebuffer;
class Renderbuffer;
class MGL_DLL_PUBLIC ContextState
{
	friend class Texture;
	friend class Buffer;
	friend class VertexArray;

protected:


	GLuint m_active_tu;
	TextureUnitState m_tu[8];


	const VertexArray* m_vao;

	const Buffer* m_buf_bindings[2];



	glm::vec4 m_clear_color;
	GLfloat m_clear_depth;
	GLint m_clear_setncil;

	const Program* m_program;

	const Framebuffer* m_framebuffer;
	const Renderbuffer* m_renderbuffer;


	GLuint m_next_vertex_array;

public:

	ContextState();

	GLenum activeTexture(const GLenum textureUnit);
	const Framebuffer* bindFramebuffer(const GLenum target, const Framebuffer* f);
	const Renderbuffer *bindRenderbuffer(const GLenum target, const Renderbuffer* f);
	const VertexArray *bindVertexArray(VertexArray* vao);
	const Buffer* bindBuffer(const GLenum target, const Buffer* b);

	const Texture *bindTexture(const GLenum target, const Texture* b);
	const Program *useProgram(const Program* prog);

	Buffer* createBuffer();
	Shader* createShader(GLenum shader_type);

	Texture* createTexture(GLenum target);
	Program* createProgram();

	VertexArray* createVertexArray();

	void deleteBuffer(const Buffer* b)
	{
		glDeleteBuffers(1,&(b->name));
		delete b;
	}

	void deleteShader(const Shader* s)
	{
		glDeleteShader(s->name);
		delete s;
	}

	void deleteProgram(const Program* p)
	{

		glDeleteProgram(p->name);
		delete p;
	}

	void deleteTextrue(const Texture* t)
	{
		glDeleteTextures(1,&(t->name));
		delete t;
	}

	void deleteVertexArray(const VertexArray* vao)
	{
		delete vao;
	}

	void drawArrays(const GLenum mode,
					const GLint first,
					const GLsizei count)
	{


		glDrawArrays(mode,first,count);
	}


	Shader* util_create_shader(GLenum shader_type, const std::string& code);
	Program* util_create_program(const std::string& vs_code, const std::string& fs_code);

	Program* util_load_program(const std::string& vs_path, const std::string& fs_path);
	Shader* util_load_shader(GLenum shader_type, const std::string& path);
	Texture*  util_load_texture2D(GLenum internal_format, const std::string& path);

	std::string util_error_string(const GLenum error) ;
	bool util_error_check(const std::string& tect);
};


}
