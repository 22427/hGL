#include <mgl_texture.h>
#include <mgl_context_state.h>

namespace mgl
{

Texture::Texture(ContextState *origin_context, GLuint name, GLenum target)
	:Object(origin_context,name),m_target(target)
{
	auto r = m_context->bindTexture(m_target,this);
	m_context->bindTexture(m_target,r);
}

void Texture::textureParameter(GLenum pname, GLfloat parameter) const
{
	auto r = m_context->bindTexture(m_target,this);
	glTexParameterf(m_target,pname,parameter);
	m_context->bindTexture(m_target,r);

}

void Texture::textureParameter(GLenum pname, GLint parameter) const
{
	auto r = m_context->bindTexture(m_target,this);
	glTexParameteri(m_target,pname,parameter);
	m_context->bindTexture(m_target,r);
}

void Texture::textureImage2D(GLint level,
							 GLint internal,
							 GLsizei w,
							 GLsizei h,
							 GLint border,
							 GLenum frmt,
							 GLenum type,
							 const void *pixels,
							 GLenum sub_target) const
{
	auto r = m_context->bindTexture(m_target,this);
	if(!sub_target)
		sub_target = m_target;
	glTexImage2D(sub_target,level,internal,w,h,border,frmt,type,pixels);
	m_context->bindTexture(m_target,r);
}

void Texture::textureSubImage2D(GLint level,
								GLint xoffset,
								GLint yoffset,
								GLsizei w,
								GLsizei h,
								GLenum frmt,
								GLenum type,
								const void *pixels,
								GLenum sub_target) const
{
	auto r = m_context->bindTexture(m_target,this);
	if(!sub_target)
		sub_target = m_target;
	glTexSubImage2D(sub_target,level,xoffset,yoffset,w,h,frmt,type,pixels);
	m_context->bindTexture(m_target,r);
}

void Texture::generateTextureMipmap() const
{
	auto r = m_context->bindTexture(m_target,this);
	glGenerateMipmap(m_target);
	m_context->bindTexture(m_target,r);
}

}
