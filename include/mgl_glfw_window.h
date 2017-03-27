#pragma once
#include "mgl_window.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
namespace mgl
{

class Window_GLFW : public Window
{

	GLFWwindow* m_glfw_win;
	glm::ivec2 m_win_pos;
	glm::ivec2 m_win_sze;


	static unsigned int m_glfw_initiated;
	static void m_glfw_window_size_fun(GLFWwindow* win,int w,int h);
	static void m_glfw_window_pos_fun(GLFWwindow* win,int x,int y );
	static void m_glfw_mouse_button_fun(GLFWwindow* win,
										int button,
										int action,
										int mods);
	static void m_glfw_cursor_pos_fun(GLFWwindow* win,double x,double y );
	static void m_glfw_scroll_fun(GLFWwindow* win,double x,double y );
	static void m_glfw_key_fun(GLFWwindow* win,
							   int key,
							   int scancode ,
							   int action,
							   int mods );
	static void m_glfw_char_mods_fun(GLFWwindow* win,unsigned int ch,int mod);
	static void m_glfw_error_callback(int err_no,const char*txt);


	std::function<void (int,int)> m_size_fun;
	std::function<void (int,int)> m_pos_fun;

	std::function<void (int button,int action,int mode)> m_mouse_button_fun;
	std::function<void (double x,double y)> m_cursor_pos_fun;
	std::function<void (double x,double y)> m_scroll_fun;

	std::function<void (int key ,int scancode ,int modifiers)> m_key_down_fun;
	std::function<void (int key ,int scancode ,int modifiers)> m_key_up_fun;
	std::function<void (unsigned int c ,int mods)> m_char_fun;

	uint8_t m_key_state[512];

public:
	Window_GLFW(const uint32_t w, const uint32_t h);
	~Window_GLFW();
	void make_current();
	void unmake_current();
	void swap_buffers();
	void poll_events();
	void set_title(const std::string &title);
	void set_size_callback(std::function<void (int, int)> fun);
	void set_position_callback(std::function<void (int, int)> fun);
	void set_button_callback(std::function<void (int, int, int)> fun);
	void set_cursor_callback(std::function<void (double, double)> fun);
	void set_scroll_callback(std::function<void (double, double)> fun);
	void set_key_down_callback(std::function<void (int, int, int)> fun);
	void set_key_up_callback(std::function<void (int, int, int)> fun);
	void set_char_callback(std::function<void (unsigned int, int)> fun);
	void toggle_fullscreen();
	void set_fullscreen(bool fs);
	void toggle_decoration();
	void set_decoration(bool dec);
	bool should_close();
	void set_should_close(bool s_c = true);
	bool is_key_down(int key) const {return  m_key_state[key];}
};

}
