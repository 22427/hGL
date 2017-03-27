#include <mgl_context_state.h>
#include <mgl_buffer.h>

namespace mgl
{




Shader::~Shader()
{

}

void Shader::shaderSource(GLsizei count, const GLchar **string, const GLint *length) const
{
	glShaderSource(name,count,string,length);
}

void Shader::compile() const
{
	glCompileShader(name);
}

void Shader::getInfoLog(GLsizei max_len, GLsizei *len, GLchar *info_log) const
{
	glGetShaderInfoLog(name,max_len,len,info_log);
}

void Shader::get(GLenum pname, GLint *params) const
{
	glGetShaderiv(name,pname,params);
}

void Shader::util_shaderfromSource(const std::string &code) const
{
	const char * c = code.c_str();
	glShaderSource(name,1,&c,nullptr);
}

std::string Shader::util_read_log() const
{
	GLint length = 0;
	glGetShaderiv(name, GL_INFO_LOG_LENGTH, &length);
	std::vector<GLchar> error_log(length);
	getInfoLog(length, &length, &error_log[0]);
	return error_log.data();
}

bool Shader::util_compile() const
{
	compile();
	GLint is_compiled = 0;
	glGetShaderiv(name, GL_COMPILE_STATUS, &is_compiled);
	return  is_compiled == GL_TRUE;

}

Program::Program(ContextState *origin_context,GLuint name):Object(origin_context,name)
{

}

Program::~Program()
{
}

void Program::attachShader(const mgl::Shader *shader) const
{
	glAttachShader(name,shader->name);
}

void Program::bindAttribLocation(GLuint index, const GLchar *attrib_name) const
{
	glBindAttribLocation(name,index,attrib_name);
}

void Program::link() const
{
	glLinkProgram(name);
}

void Program::getInfoLog(GLsizei max_len, GLsizei *len, GLchar *info_log) const
{
	glGetProgramInfoLog(name,max_len,len,info_log);
}

void Program::getProgram(GLenum pname, GLint *params) const
{
	glGetProgramiv(name,pname,params);
}


std::string Program::util_read_log() const
{
	GLint length = 0;
	glGetProgramiv(name, GL_INFO_LOG_LENGTH, &length);
	std::vector<GLchar> error_log(length);
	getInfoLog(length, &length, &error_log[0]);
	return error_log.data();
}

bool Program::util_link() const
{
	link();
	GLint is_linked = 0;
	glGetProgramiv(name, GL_LINK_STATUS, &is_linked);
	return  is_linked == GL_TRUE;
}


}
