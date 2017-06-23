#pragma once

#include "dep/glad/glad.h"
#include <functional>

#include <cstring>
#include <unordered_set>

#include "dep/glm/vec2.hpp"
#include "dep/glm/vec3.hpp"
#include "dep/glm/vec4.hpp"
#include "dep/glm/mat2x2.hpp"
#include "dep/glm/mat3x3.hpp"
#include "dep/glm/mat4x4.hpp"
#include "dep/glm/gtc/type_ptr.hpp"

#include "hgles_window.h"
#include "hgles_log.h"
namespace hgles
{

class MGL_DLL_PUBLIC ContextState
{
protected:
	struct MGL_DLL_PUBLIC TextureUnitState
	{
		GLuint tex_2D;
		GLuint tex_cube;
		TextureUnitState() : tex_2D(0),tex_cube(0){}
	};

	struct MGL_DLL_PUBLIC VertexAttributeBinding
	{
		GLuint buffer;
		GLuint index;
		GLint  size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const GLvoid* pointer;

		VertexAttributeBinding(
				const GLuint buffer =0 ,
				const GLuint index =0,
				const GLint size = 0,
				const GLenum type = GL_FLOAT,
				const GLboolean normalized = GL_FALSE,
				const GLsizei stride = 0,
				const GLvoid * pointer = nullptr);

		bool operator ==(const VertexAttributeBinding& o) const;
		bool operator != (const VertexAttributeBinding& o) const
		{
			return !((*this)==o);
		}
	};

	struct MGL_DLL_PUBLIC VertexArrayState
	{
		GLuint element_array;
		bool enable_vertex_array_attribute[8];
		VertexAttributeBinding binding[8];

		VertexArrayState()
		{
			element_array = 0;
			for(GLuint i = 0 ; i< 8;i++)
				enable_vertex_array_attribute[i] = false;
		}
	};


	TextureUnitState m_texture_units[8];

	std::vector<VertexArrayState> m_vertex_arrays;
	std::unordered_set<GLuint> m_free_vaos;

	GLuint m_active_texture_unit;
	GLuint m_bound_vertex_array;
	GLuint m_bound_buffer;
	GLuint m_used_program;

	void VertexAttribPointer(const VertexAttributeBinding& vab);
	void free_vao(const GLuint vao)
	{
		m_vertex_arrays[vao] = VertexArrayState();
		m_free_vaos.insert(vao);
	}

	GLuint get_vao()
	{
		if(!m_free_vaos.empty())
		{
			auto res = *(m_free_vaos.begin());
			m_free_vaos.erase(m_free_vaos.begin());
			return  res;
		}
		m_vertex_arrays.push_back(VertexArrayState());
		return static_cast<GLuint>(m_vertex_arrays.size())-1;
	}
public:

	ContextState()
	{
		m_vertex_arrays.resize(1);
		m_bound_buffer = 0;
		m_used_program = 0;
		m_active_texture_unit = 0;
		m_bound_vertex_array = 0;
	}
	// Context Operations ######################################################
	void ClearColor(const float r,
					const float g,
					const float b,
					const float a) const;
	void Clear(GLbitfield mask) const;
	void Enable(GLenum cap) const;
	void Disable(GLenum cap) const;

	// Textures ################################################################

	void ActiveTexture(const GLenum textureUnit);
	void BindTexture(const GLenum trgt, GLuint texture);
	void GenTextures(const GLsizei count, GLuint* textures) const;
	void DeleteTextures(const GLsizei count, const GLuint * textures) const;

	void GenerateMipmap(const GLenum trgt) const;
	void TexParametr(const GLenum trgt, const GLenum prm, const float  v) const;
	void TexParametr(const GLenum trgt, const GLenum prm, const float* v) const;
	void TexParametr(const GLenum trgt, const GLenum prm, const int  v) const;
	void TexParametr(const GLenum trgt, const GLenum prm, const int* v) const;

	void TexImage2D(GLenum trgt,
					GLint level,
					GLint internalformat,
					GLsizei width,
					GLsizei height,
					GLint border,
					GLenum format,
					GLenum type,
					const GLvoid * data) const;

	void TexSubImage2D(GLenum trgt,
					   GLint level,
					   GLint xoffset,
					   GLint yoffset,
					   GLsizei width,
					   GLsizei height,
					   GLenum format,
					   GLenum type,
					   const GLvoid * data) const;

	// Buffers #################################################################
	void BindBuffer(const GLenum trgt, const GLuint buffer);
	void GenBuffers(const GLsizei count, GLuint* buffers) const;
	void DeleteBuffers(const GLsizei count, const GLuint* buffers) const;
	void BufferData(GLenum trgt,GLsizeiptr size,
					const GLvoid * data,GLenum usage) const;


	// Vertes Arrays ###########################################################
	void BindVertexArray(const GLuint vao);
	void GenVertexArrays(const GLsizei count, GLuint* vaos);
	void DeleteVertexArrays(const GLsizei count,const  GLuint* vaos);

	// Vertex Attributes #######################################################
	void VertexAttribPointer( 	GLuint index,
								GLint size,
								GLenum type,
								GLboolean normalized,
								GLsizei stride,
								const GLvoid * pointer);
	void EnableVertexAttribArray(const GLuint index);
	void DisableVertexAttribArray(const GLuint index);

	// Draw ####################################################################
	void DrawArrays(const GLenum mode,
					const GLint first,
					const GLsizei count) const;

	void DrawElements(GLenum mode,
					  GLsizei count,
					  GLenum type,
					  const GLvoid * indices) const;

	// Shader ##################################################################
	GLuint CreateShader(const GLenum type) const;
	void DeleteShader(const GLuint shader) const;
	void ShaderSource(GLuint shader, GLsizei count,
					  const GLchar* const *string,
					  const GLint *length) const;

	void CompileShader(const GLuint shader) const;
	void BindAttribLocation(GLuint prgrm, GLuint index, const GLchar* name) const;

	GLuint CreateProgam() const;
	void DeleteProgram(const GLuint prgrm) const;
	void LinkProgram(GLuint prog) const;
	void AttachShader(GLuint prgrm, GLuint shader) const;
	void UseProgram(GLuint prgrm);

	// Uniforms ################################################################
	GLint GetUniformLocation(const GLuint prgrm, const char* uname) const;

	void Uniform(GLint location, const float v) const;
	void Uniform(GLint location, const int v) const;

	void Uniform(GLint location, const glm::vec2& v, const GLsizei cnt=1) const;
	void Uniform(GLint location, const glm::vec3& v, const GLsizei cnt=1) const;
	void Uniform(GLint location, const glm::vec4& v, const GLsizei cnt=1) const;

	void Uniform(GLint location, const glm::mat2& mat,
				 const GLsizei cnt = 1,
				 const GLboolean transp = GL_FALSE) const;
	void Uniform(GLint location, const glm::mat3& mat,
				 const GLsizei cnt = 1,
				 const GLboolean transp = GL_FALSE) const;
	void Uniform(GLint location, const glm::mat4& mat,
				 const GLsizei cnt = 1,
				 const GLboolean transp = GL_FALSE) const;

	// Utilities ###############################################################
	GLuint util_CreateShader(GLenum shader_type, const std::string& code) const;
	GLuint util_CreateProgram(const std::string& vs_code,
							  const std::string& fs_code) const;
	GLuint util_LoadShader(GLenum shader_type, const std::string& path) const;
	GLuint util_LoadProgram(const std::string& vs_path,
							const std::string& fs_path) const;
	std::string util_error_string(const GLenum error) const;
	bool util_error_check(const std::string &tect) const;
};
}
