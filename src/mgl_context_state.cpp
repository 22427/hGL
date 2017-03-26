#include <mgl_context_state.h>
#include <fstream>
#include <cstring>
#include <stb_image.h>
#include <mgl_log.h>
namespace mgl {


Shader ContextState::util_create_shader(GLenum shader_type, const std::string &code)
{
	auto res = createShader(shader_type);
	res.util_shaderSource(code);
	if(!res.util_compile())
	{
		WARNING("Compiling shader failed: %s",res.util_read_log().c_str());
		return res;
	}
	return res;
}

Shader ContextState::util_load_shader(GLenum shader_type,
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

Texture ContextState::util_load_texture2D(GLenum internal_format,
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
	res.textureImage2D(0,0,0,w,h,internal_format,GL_UNSIGNED_BYTE,data);
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

Program ContextState::util_create_program(const std::string &vs_c,
									  const std::string &fs_c)
{
	auto vs = util_create_shader(GL_VERTEX_SHADER,vs_c);
	auto fs = util_create_shader(GL_FRAGMENT_SHADER,fs_c);

	auto res = createProgram();
	res.attachShader(vs);
	res.attachShader(fs);
	if(!res.util_link())
	{
		WARNING("Linking program failed: %s",res.util_read_log().c_str());
	}
	return res;
}

Program ContextState::util_load_program(const std::string &vs_path,
									const std::string &fs_path)
{
	auto vs = util_load_shader(GL_VERTEX_SHADER,vs_path);
	auto fs = util_load_shader(GL_FRAGMENT_SHADER,fs_path);

	auto res = createProgram();
	res.attachShader(vs);
	res.attachShader(fs);
	if(!res.util_link())
	{
		WARNING("Linking program failed: %s",res.util_read_log().c_str());
	}
	return  res;
}

}
