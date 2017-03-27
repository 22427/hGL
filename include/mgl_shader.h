#pragma once
#include <string>
#include "mgl_object.h"
#include <vector>
namespace mgl
{

class MGL_DLL_PUBLIC Shader : public Object
{
protected:


public:
	Shader(ContextState* origin_context,GLuint name):Object(origin_context,name)
	{
	}
	friend class ContextState;
	~Shader();

	void shaderSource(GLsizei count, const GLchar** string, const GLint* length) const;

	void compile() const;

	void getInfoLog(GLsizei max_len, GLsizei* len, GLchar* info_log)const;

	void get(GLenum pname, GLint* params)const;


	void util_shaderfromSource(const std::string& code)const;

	std::string util_read_log()const;

	bool util_compile()const;
};


class MGL_DLL_PUBLIC Program : public Object
{
public:
	friend class ContextState;
	Program(ContextState* origin_context,GLuint name);
	~Program();

	void attachShader(const Shader* shader) const;

	void bindAttribLocation(GLuint index, const GLchar* attrib_name)const;

	void link()const;

	void getInfoLog(GLsizei max_len, GLsizei* len, GLchar* info_log)const;

	void getProgram(GLenum pname, GLint *params) const;


	std::string util_read_log()const;
	bool util_link()const;

};

}
