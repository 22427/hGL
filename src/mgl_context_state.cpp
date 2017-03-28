#include <mgl_context_state.h>
#include <fstream>
#include <cstring>
#include <mgl_log.h>
#include <stb/stb_image.h>

namespace mgl {


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

	m_buf_bindings[0] = m_buf_bindings[1] = nullptr;
	m_next_vertex_array = 0;



}

GLenum ContextState::activeTexture(const GLenum textureUnit)
{
	auto to_ret = GL_TEXTURE0+m_active_tu;
	m_active_tu = textureUnit-GL_TEXTURE0;
	if(m_active_tu != to_ret)
		glActiveTexture(textureUnit);
	return to_ret;

}


const Framebuffer* ContextState::bindFramebuffer(const GLenum /*target*/, const Framebuffer */*f*/)
{

	return  nullptr;
}


const Renderbuffer* ContextState::bindRenderbuffer(const GLenum /*target*/, const Renderbuffer */*f*/)
{
	return nullptr;
}


const VertexArray* ContextState::bindVertexArray(VertexArray *vao)
{
	auto to_ret = m_vao;
	m_vao= vao;
	if(m_vao&&m_vao != to_ret)
		vao->bind();
	return to_ret;

}


const Buffer *ContextState::bindBuffer(const GLenum target, const Buffer *b)
{
	auto to_ret = m_buf_bindings[target-GL_ARRAY_BUFFER] ;
	m_buf_bindings[target-GL_ARRAY_BUFFER] = b;

	if(b && to_ret != b)
		glBindBuffer(target,b->name);
	return to_ret;
}



const Texture* ContextState::bindTexture(const GLenum target, const Texture *b)
{

	const Texture* to_ret = nullptr;
	// bind texture
	if(target == GL_TEXTURE_2D)
	{
		to_ret = m_tu[m_active_tu].tex2d;
		m_tu[m_active_tu].tex2d = b;

	}
	else if(target == GL_TEXTURE_CUBE_MAP)
	{
		to_ret = m_tu[m_active_tu].tex2d;
		m_tu[m_active_tu].cube = b;

	}

	if(b && to_ret != b)
		glBindTexture(target,b->name);
	return to_ret;

}

const Program* ContextState::useProgram(const Program *prog)
{
	const Program* to_ret = m_program;
	m_program = prog;

	if(prog && to_ret != prog)
		glUseProgram(prog->name);
	return  to_ret;
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
	m_next_vertex_array++;
	return new  VertexArray(this,m_next_vertex_array);
}

Shader* ContextState::util_create_shader(GLenum shader_type, const std::string &code)
{
	auto res = createShader(shader_type);
	res->util_shaderfromSource(code);
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

Texture* ContextState::util_load_texture2D(GLenum internal_format,
										   const std::string &path)
{
	int dchan = 0;

	switch (internal_format)
	{
	case GL_RGBA : dchan = 4; break;
	case GL_RGB : dchan = 3;  break;
	default: dchan = 4; break;
	}

	int w,h,c;
	auto data = stbi_load(path.c_str(),&w,&h,&c,dchan);
	if(! data)
	{
		WARNING("Failed to load image %s",path.c_str());
	}

	auto res = createTexture(GL_TEXTURE_2D);
	res->textureImage2D(0,0,0,w,h,internal_format,GL_UNSIGNED_BYTE,data);
	free(data);

	return res;
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
