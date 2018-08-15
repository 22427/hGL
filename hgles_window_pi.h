#pragma once
#include "hgles_window_interface.h"
#include "hgles_dll.h"
#include "hgles_glad.h"
#include <glm/vec2.hpp>
#include "hgles_log.h"

#include <functional>
#include <vector>
#include <unordered_set>
#include <EGL/egl.h>

#ifdef HGLES_USE_PI
extern "C"
{
#include <bcm_host.h>
}
#endif

namespace hgles
{

class HGLES_DLL_PUBLIC Window
		#ifndef NDEBUG
		: public WindowInterface
		#endif
{
protected:

	glm::ivec2 m_win_pos;
	glm::ivec2 m_win_sze;


	glm::ivec2 m_pos;
	glm::ivec2 m_sze;
	glm::ivec2 m_display_sze;

#ifdef HGLES_USE_PI
	EGL_DISPMANX_WINDOW_T m_win_handle;
#endif


	std::function<void (const std::string&)> m_log;
	std::function<void (const std::string&)> m_error;
	std::function<void (const std::string&)> m_warning;



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
	Window(const uint32_t w, const uint32_t h,
		   const uint32_t x=0, const uint32_t y=0);
	~Window();
	void make_current();
	void unmake_current();
	void swap_buffers();
	void poll_events();
	void set_title(const std::string &title);

	void toggle_fullscreen();
	void set_fullscreen(bool fs);
	void toggle_decoration();
	void set_decoration(bool dec);
	bool should_close();
	void set_should_close(bool s_c = true);

	void add_window_listener(WindowListener* wl);
	void remove_window_listener(WindowListener* wl);


	void set_size(const int w, const int h);
	void set_size(const glm::ivec2& sze);
	glm::ivec2 get_size() const;

	void set_position(const int x, const int y);
	void set_position(const glm::ivec2& pos);
	glm::ivec2 get_position() const;

	void set_log_cb(std::function<void (const std::string&)>& cb)
	{m_log = cb;}
	void set_warning_cb(std::function<void (const std::string&)>& cb)
	{m_warning = cb;}
	void set_error_cb(std::function<void (const std::string&)>& cb)
	{m_error = cb;}
};

}
