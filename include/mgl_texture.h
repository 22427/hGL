#pragma once
#include <cmath>
#include <algorithm>
#include "mgl_buffer.h"

namespace mgl
{


class MGL_DLL_PUBLIC Texture : public Object
{
protected:

	GLenum m_target;

public:
		Texture(ContextState* origin_context,GLuint name,GLenum target);
	friend class ContextState;

	void textureParameter(GLenum pname, GLfloat parameter) const;
	void textureParameter(GLenum pname, GLint parameter) const;

	void textureImage2D(GLint level,
						GLint internal,
						GLsizei w,
						GLsizei h,
						GLint border,
						GLenum frmt,
						GLenum type,
						const void* pixels,
						GLenum sub_target=0) const;
	void textureSubImage2D(GLint level,
						   GLint xoffset,
						   GLint yoffset,
						   GLsizei w,
						   GLsizei h,
						   GLenum frmt,
						   GLenum type,
						   const void* pixels,
						   GLenum sub_target=0) const;

	void generateTextureMipmap() const;
};


}
