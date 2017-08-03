#include <fstream>
#include <cstring>

#include "../include/hgles_context_state.h"
#include "../include/hgles_log.h"

namespace hgles {

ContextState::VertexAttributeBinding::VertexAttributeBinding(
		const GLuint buffer,
		const GLuint index,
		const GLint size,
		const GLenum type,
		const GLboolean normalized,
		const GLsizei stride,
		const GLvoid *pointer)
{
	this->buffer = buffer;
	this->index = index ;
	this->size = size;
	this->type = type;
	this->normalized = normalized;
	this->stride = stride;
	this->pointer = pointer;
}

bool ContextState::VertexAttributeBinding::operator ==(
		const ContextState::VertexAttributeBinding &o) const
{
	if(buffer != o.buffer)
		return false;
	if(index != o.index)
		return false;
	if(size != o.size)
		return false;
	if(type != o.type)
		return false;
	if(normalized != o.normalized)
		return false;
	if(stride != o.stride)
		return false;
	if(pointer != o.pointer)
		return false;
	return true;
}


void ContextState::ClearColor(const float r,
							  const float g,
							  const float b,
							  const float a) const
{
	glad_glClearColor(r,g,b,a);
}

void ContextState::Clear(GLbitfield mask) const
{
	glad_glClear(mask);
}

void ContextState::Enable(GLenum cap) const
{
	glad_glEnable(cap);
}

void ContextState::Disable(GLenum cap) const
{
	glad_glDisable(cap);
}

void ContextState::ActiveTexture(const GLenum textureUnit)
{
	if(m_active_texture_unit != textureUnit - GL_TEXTURE0)
	{
		m_active_texture_unit = textureUnit - GL_TEXTURE0;
		glad_glActiveTexture(textureUnit);
	}
}

void ContextState::BindTexture(const GLenum target, GLuint texture)
{
	if(target == GL_TEXTURE_2D)
	{
		if(m_texture_units[m_active_texture_unit].tex_2D != texture)
		{
			m_texture_units[m_active_texture_unit].tex_2D = texture;
			glad_glBindTexture(target,texture);
		}
	}
	else
	{
		if(m_texture_units[m_active_texture_unit].tex_cube != texture)
		{
			m_texture_units[m_active_texture_unit].tex_cube = texture;
			glad_glBindTexture(target,texture);
		}
	}
}

void ContextState::GenTextures(const GLsizei count, GLuint *textures) const
{
	glad_glGenTextures(count,textures);
}

void ContextState::DeleteTextures(const GLsizei count,
								  const GLuint *textures) const
{
	glad_glDeleteTextures(count,textures);
}

void ContextState::GenerateMipmap(const GLenum target) const
{
	glad_glGenerateMipmap(target);
}

void ContextState::TexParametr(const GLenum target,
							   const GLenum param,
							   const float val) const
{
	glad_glTexParameterf(target,param,val);
}

void ContextState::TexParametr(const GLenum target,
							   const GLenum param,
							   const float *val) const
{
	glad_glTexParameterfv(target,param,val);
}

void ContextState::TexParametr(const GLenum target,
							   const GLenum param,
							   const int val) const
{
	glad_glTexParameteri(target,param,val);
}

void ContextState::TexParametr(const GLenum target,
							   const GLenum param,
							   const int *val) const
{
	glad_glTexParameteriv(target,param,val);
}

void ContextState::TexImage2D(GLenum target,
							  GLint level,
							  GLint internalformat,
							  GLsizei width,
							  GLsizei height,
							  GLint border,
							  GLenum format,
							  GLenum type,
							  const GLvoid *data) const
{
	glad_glTexImage2D(target,level,internalformat,
					  width,height,border,format,type,data);
}

void ContextState::TexSubImage2D(GLenum target,
								 GLint level,
								 GLint xoffset,
								 GLint yoffset,
								 GLsizei width,
								 GLsizei height,
								 GLenum format,
								 GLenum type,
								 const GLvoid *data) const
{
	glad_glTexSubImage2D(target,level,xoffset,yoffset,
						 width,height,format,type,data);

}

void ContextState::GenBuffers(const GLsizei count, GLuint *textures) const
{
	glad_glGenBuffers(count, textures);
}

void ContextState::BindBuffer(const GLenum target, const GLuint buffer)
{
	if(target == GL_ARRAY_BUFFER)
	{
		if(m_bound_buffer != buffer)
			glad_glBindBuffer(GL_ARRAY_BUFFER,buffer);
	}
	if(target == GL_ELEMENT_ARRAY_BUFFER)
	{
		auto it = glad_glGenVertexArraysOES?0:m_bound_vertex_array;
		if(m_vertex_arrays[it].element_array != buffer)
		{
			m_vertex_arrays[it].element_array = buffer;
			glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
		}
	}
}

void ContextState::DeleteBuffers(const GLsizei count,
								 const GLuint *buffers) const
{
	glad_glDeleteBuffers(count, buffers);
}

void ContextState::BufferData(GLenum target,
							  GLsizeiptr size,
							  const GLvoid *data,
							  GLenum usage) const
{
	glad_glBufferData(target,size,data,usage);
}

void ContextState::GenVertexArrays(const GLsizei count, GLuint *textures)
{
	if(glad_glGenVertexArraysOES)
		glad_glGenVertexArraysOES(count, textures);
	else
	{
		for(GLsizei i = 0 ; i< count ;i++)
		{
			textures[i] = get_vao();
		}

	}
}

void ContextState::DeleteVertexArrays(const GLsizei count, const GLuint *vaos)
{
	if(glad_glDeleteVertexArraysOES)
		return glad_glDeleteVertexArraysOES(count, vaos);

	for(GLsizei i = 0 ; i< count ; i++)
	{
		const auto vao = vaos[i];
		free_vao(vao);
	}
}

void ContextState::VertexAttribPointer(GLuint index,
									   GLint size,
									   GLenum type,
									   GLboolean normalized,
									   GLsizei stride,
									   const GLvoid *pointer)
{
	auto it = glad_glGenVertexArraysOES?0:m_bound_vertex_array;
	auto vab = VertexAttributeBinding(m_bound_buffer,
									  index,
									  size,
									  type,
									  normalized,
									  stride,
									  pointer);
	if(!it)
	{
		glad_glVertexAttribPointer(index,size,type,normalized,stride,pointer);
	}
	else if(m_vertex_arrays[it].binding[index] != vab )
	{
		m_vertex_arrays[it].binding[index] = vab;
		glad_glVertexAttribPointer(index,size,type,normalized,stride,pointer);
	}
}

void ContextState::EnableVertexAttribArray(const GLuint index)
{
	auto it = glad_glGenVertexArraysOES?0:m_bound_vertex_array;
	if(!it)
		glad_glEnableVertexAttribArray(index);
	else if(!m_vertex_arrays[it].enable_vertex_array_attribute[index])
	{
		m_vertex_arrays[it].enable_vertex_array_attribute[index] = true;
		glad_glEnableVertexAttribArray(index);
	}
}

void ContextState::DisableVertexAttribArray(const GLuint index)
{
	auto it = glad_glGenVertexArraysOES?0:m_bound_vertex_array;
	if(m_vertex_arrays[it].enable_vertex_array_attribute[index])
	{
		m_vertex_arrays[it].enable_vertex_array_attribute[index] = false;
		glad_glDisableVertexAttribArray(index);
	}
}

void ContextState::DrawArrays(const GLenum mode,
							  const GLint first,
							  const GLsizei count) const
{
	glad_glDrawArrays(mode,first,count);
}

void ContextState::DrawElements(GLenum mode,
								GLsizei count,
								GLenum type,
								const GLvoid *indices) const
{
	glad_glDrawElements(mode,count,type,indices);
}

GLuint ContextState::CreateShader(const GLenum type) const
{
	return  glad_glCreateShader(type);
}

void ContextState::DeleteShader(const GLuint shader) const
{
	glad_glDeleteShader(shader);
}

void ContextState::ShaderSource(GLuint shader,
								GLsizei count,
								const GLchar * const *string,
								const GLint *length)  const
{
	glad_glShaderSource(shader,count,string,length);
}

void ContextState::CompileShader(const GLuint shader)  const
{
	glad_glCompileShader(shader);
}

void ContextState::BindAttribLocation(GLuint program,
									  GLuint index,
									  const GLchar *name)  const
{
	glad_glBindAttribLocation(program,index,name);
}

GLuint ContextState::CreateProgam() const
{
	return glad_glCreateProgram();
}

void ContextState::DeleteProgram(const GLuint program) const
{
	glad_glDeleteProgram(program);
}

void ContextState::LinkProgram(GLuint prog) const
{
	glad_glLinkProgram(prog);
}

void ContextState::AttachShader(GLuint program, GLuint shader) const
{
	glad_glAttachShader(program,shader);
}

void ContextState::UseProgram(GLuint prgrm)
{
	if(m_used_program == prgrm)
		return;
	glad_glUseProgram(prgrm);
	m_used_program = prgrm;
}

GLint ContextState::GetUniformLocation(const GLuint program,
									   const char *uname) const
{
	return glad_glGetUniformLocation(program,uname);
}

void ContextState::Uniform(GLint location, const float v) const
{
	glad_glUniform1f(location,v);
}

void ContextState::Uniform(GLint location, const int v) const
{
	glad_glUniform1i(location,v);
}

void ContextState::Uniform(GLint location,
						   const glm::vec2 &v,
						   const GLsizei cnt) const
{
	glad_glUniform2fv(location,cnt,glm::value_ptr(v));
}

void ContextState::Uniform(GLint location,
						   const glm::vec3 &v,
						   const GLsizei cnt) const
{
	glad_glUniform3fv(location,cnt,glm::value_ptr(v));
}

void ContextState::Uniform(GLint location,
						   const glm::vec4 &v,
						   const GLsizei cnt) const
{
	glad_glUniform4fv(location,cnt,glm::value_ptr(v));
}

void ContextState::Uniform(GLint location,
						   const glm::mat2 &mat,
						   const GLsizei cnt,
						   const GLboolean transp) const
{
	glad_glUniformMatrix2fv(location,cnt,transp,glm::value_ptr(mat));
}

void ContextState::Uniform(GLint location,
						   const glm::mat3 &mat,
						   const GLsizei cnt,
						   const GLboolean transp) const
{
	glad_glUniformMatrix3fv(location,cnt,transp,glm::value_ptr(mat));
}

void ContextState::Uniform(GLint location,
						   const glm::mat4 &mat,
						   const GLsizei cnt,
						   const GLboolean transp) const
{
	glad_glUniformMatrix4fv(location,cnt,transp,glm::value_ptr(mat));
}

GLuint ContextState::util_CreateShader(GLenum shader_type,
									   const std::string &code) const
{
	auto res = CreateShader(shader_type);
	const GLchar* c = code.c_str();
	ShaderSource(res,1,&c,nullptr);
	CompileShader(res);
	// todo check for errors
	return res;
}

GLuint ContextState::util_CreateProgram(const std::string &vs_code,
										const std::string &fs_code) const
{
	auto vs = util_CreateShader(GL_VERTEX_SHADER,vs_code);
	auto fs = util_CreateShader(GL_FRAGMENT_SHADER,fs_code);
	if(!vs || ! fs)
	{
		// todo error!!!
		if(!vs)
			DeleteShader(vs);
		if(!fs)
			DeleteShader(fs);
		return 0;
	}
	auto res = CreateProgam();
	AttachShader(res,vs);
	AttachShader(res,fs);
	LinkProgram(res);
	// todo check for errors
	DeleteShader(vs);
	DeleteShader(fs);
	return res;
}


void ContextState::BindVertexArray(const GLuint vao)
{
	if(m_bound_vertex_array == vao)
		return;
	if(glad_glBindVertexArrayOES)
		glad_glBindVertexArrayOES(vao);
	else
	{
		auto vaos = m_vertex_arrays[vao];
		BindBuffer(GL_ELEMENT_ARRAY_BUFFER,vaos.element_array);
		for(GLuint i = 0; i< 8;i++)
		{
			BindBuffer(GL_ARRAY_BUFFER,vaos.binding[i].buffer);
			if(vaos.binding[i].buffer || vaos.binding[i].pointer)
				VertexAttribPointer(vaos.binding[i]);
			if(vaos.enable_vertex_array_attribute[i])
				EnableVertexAttribArray(i);
			else
				DisableVertexAttribArray(i);
		}
	}
	m_bound_vertex_array = vao;
}

void ContextState::VertexAttribPointer(
		const ContextState::VertexAttributeBinding &vab)
{
	auto it = glad_glGenVertexArraysOES?0:m_bound_vertex_array;
	if(!it)
	{
		glad_glVertexAttribPointer(vab.index,
								   vab.size,
								   vab.type,
								   vab.normalized,
								   vab.stride,
								   vab.pointer);
	}
	else if(m_vertex_arrays[it].binding[vab.index] != vab )
	{
		m_vertex_arrays[it].binding[vab.index] = vab;
		glad_glVertexAttribPointer(vab.index,
								   vab.size,
								   vab.type,
								   vab.normalized,
								   vab.stride,
								   vab.pointer);
	}
}





GLuint ContextState::util_LoadShader(GLenum shader_type,
									 const std::string &path) const
{
	std::ifstream t(path);
	if(!t.is_open())
	{
		WARNING("Could not open shader file %s",path.c_str());
	}
	std::string code((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());

	return util_CreateShader(shader_type,code);
}

GLuint ContextState::util_LoadProgram(const std::string &vs_path,
									  const std::string &fs_path) const
{
	auto vs = util_LoadShader(GL_VERTEX_SHADER,vs_path);
	auto fs = util_LoadShader(GL_FRAGMENT_SHADER,fs_path);

	if(!vs || ! fs)
	{
		// todo error!!!
		if(!vs)
			DeleteShader(vs);
		if(!fs)
			DeleteShader(fs);
		return 0;
	}

	auto res = this->CreateProgam();
	if(!res)
	{
		DeleteShader(vs);
		DeleteShader(fs);
		ERROR("Failed to create programm!");
		return  0;
	}
	AttachShader(res,vs);
	AttachShader(res,fs);
	LinkProgram(res);
	// todo check error

	DeleteShader(vs);
	DeleteShader(fs);
	return  res;

}

std::string ContextState::util_error_string(const GLenum error) const
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

bool ContextState::util_error_check(const std::string &text) const
{
#ifndef NDEBUG
	GLenum err_cde;
	err_cde = glGetError();
	if (err_cde != GL_NO_ERROR)
	{
		ERROR("[glERR] %s:%s",text.c_str(),util_error_string(err_cde).c_str());
		return true;
	}
	return false;
#else
	retrun false
#endif
}



}
