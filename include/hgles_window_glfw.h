#pragma once
#include "hgles_window_interface.h"
#include "hgles_input_glfw.h"
#include <functional>
#include "hgles_dll.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <vector>
#include <unordered_set>
namespace hgles
{

class MGL_DLL_PUBLIC Window
		#ifndef NDEBUG
		: public WindowInterface
		#endif
{
protected:
	GLFWwindow* m_glfw_win;
	glm::ivec2 m_win_pos;
	glm::ivec2 m_win_sze;


	static unsigned int m_glfw_initiated;

	static void m_glfw_window_size_fun(GLFWwindow* win,int w,int h);
	static void m_glfw_window_pos_fun(GLFWwindow* win,int x,int y );


	std::unordered_set<WindowListener*> m_window_listeners;

	InputSystem * m_input_system;

public:
	friend class InputSystem;
	Window(const uint32_t w, const uint32_t h, const uint32_t x=0, const uint32_t y=0);
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

	void add_window_listener(WindowListener *wl);
	void remove_window_listener(WindowListener *wl);



	void set_size(const int w, const int h);
	void set_size(const glm::ivec2& sze);
	glm::ivec2 get_size() const;

	void set_position(const int x, const int y);
	void set_position(const glm::ivec2& pos);
	glm::ivec2 get_position() const;
};

}
