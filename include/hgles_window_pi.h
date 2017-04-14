#pragma once
#include "hgles_window_interface.h"

#include <functional>
#include "hgles_dll.h"

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <vector>
#include <unordered_set>
#include <EGL/egl.h>
#include <hgles_log.h>
#ifdef HGLES_USE_PI
extern "C"
{
#include <bcm_host.h>
}
#endif

namespace hgles
{

class MGL_DLL_PUBLIC Window
		#ifndef NDEBUG
		: public WindowInterface
		#endif
{
protected:

	glm::ivec2 m_win_pos;
	glm::ivec2 m_win_sze;

#ifdef HGLES_USE_PI
EGL_DISPMANX_WINDOW_T m_win_handle;
#endif




	/* The display handle */
	EGLDisplay m_display;

	/* The context */
	EGLContext m_context;

	/* The surface */
	EGLSurface m_surface;

	std::unordered_set<WindowListener*> m_window_listeners;

	bool m_should_close;


public:
	friend class InputSystem;
	Window(const uint32_t w, const uint32_t h, const uint32_t x=0, const uint32_t y=0);
	~Window(){}
	void make_current()
	{
		if(!eglMakeCurrent(m_display, m_surface, m_surface, m_context))
			ERROR("eglMakeCurrent failed!");
	}
	void unmake_current()
	{
		if(!eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
			ERROR("eglMakeCurrent failed!");
	}
	void swap_buffers()
	{
		eglSwapBuffers(m_display,m_surface);
	}
	void poll_events(){};
	void set_title(const std::string &/*title*/){};

	void toggle_fullscreen(){/*TODO*/}
	void set_fullscreen(bool /*fs*/){/*TODO*/}
	void toggle_decoration(){}
	void set_decoration(bool /*dec*/){}
	bool should_close(){return m_should_close;}
	void set_should_close(bool s_c = true){m_should_close =s_c;}

	void add_window_listener(WindowListener* /*wl*/){/*TODO*/}
	void remove_window_listener(WindowListener* /*wl*/){/*TODO*/}
};

}
