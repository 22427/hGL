#ifndef USE_PI
#include <cstring>

#include "../include/hgles_input_glfw.h"
#include "../include/hgles_window_glfw.h"
#include "../include/dep/glad/glad.h"
#define GLFW_INCLUDE_ES2
#include "../include/dep/GLFW/glfw3.h"

namespace hgles
{

void InputSystem::m_glfw_char_cb(GLFWwindow *win, unsigned int character)
{
	Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
	auto& is = ww->m_input_system;
	for(auto& l : is->m_char_listener)
	{
		l->char_input(character);
	}
}

void InputSystem::m_glfw_key_cb(GLFWwindow *win, int key,
								int /*scancode*/,
								int action, int /*mods*/)
{
	Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
	auto& is = ww->m_input_system;
	if(action == GLFW_PRESS)
	{
		is->m_key_state[key] = 1;
		for(auto& l : is->m_keyboard_listener)
		{
			l->key_down(static_cast<Key>(key));
		}
	}
	else if (action == GLFW_REPEAT)
	{
		for(auto& l : is->m_keyboard_listener)
		{
			l->key_repeat(static_cast<Key>(key));
		}
	}
	else
	{
		is->m_key_state[key] = 0;
		for(auto& l : is->m_keyboard_listener)
		{
			l->key_up(static_cast<Key>(key));
		}

	}

}

void InputSystem::m_glfw_mouse_button_cb(GLFWwindow *win, int button,
										 int action, int /*mods*/)
{
	Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
	auto& is = ww->m_input_system;
	if(action == GLFW_PRESS)
	{
		is->m_button_state[button] = 1;
		for(auto& l : is->m_mouse_listener)
		{
			l->button_down(static_cast<Button>(button));
		}
	}
	else
	{
		is->m_button_state[button] = 0;
		for(auto& l : is->m_mouse_listener)
		{
			l->button_up(static_cast<Button>(button));
		}

	}
}

void InputSystem::m_glfw_scroll_cb(GLFWwindow *win, double x, double y)
{
	Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
	auto& is = ww->m_input_system;
	for(auto& l : is->m_mouse_listener)
	{
		l->scroll(static_cast<float>(x),
				  static_cast<float>(y));
	}
}

void InputSystem::m_glfw_cursor_cb(GLFWwindow *win, double x, double y)
{
	Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
	auto& is = ww->m_input_system;
	float dx = static_cast<float>(x)-ww->m_input_system->m_cursor_x;
	float dy = static_cast<float>(y)-ww->m_input_system->m_cursor_y;
	for(auto& l : is->m_mouse_listener)
	{
		l->cursor(static_cast<float>(x),
				  static_cast<float>(y));
		l->cursor_move(dx,dy);
	}
	ww->m_input_system->m_cursor_x = static_cast<float>(x);
	ww->m_input_system->m_cursor_y = static_cast<float>(y);
}

InputSystem::InputSystem()
{
	memset(m_key_state,0,K_LAST+1);
	memset(m_button_state,0,BUTTON_LAST+1);
	m_cursor_x = m_cursor_y = 0;
}



void InputSystem::init(Window *w)
{
	w->m_input_system = this;
	glfwSetCharCallback(w->m_glfw_win,m_glfw_char_cb);
	glfwSetKeyCallback(w->m_glfw_win,m_glfw_key_cb);
	glfwSetMouseButtonCallback(w->m_glfw_win,m_glfw_mouse_button_cb);
	glfwSetScrollCallback(w->m_glfw_win,m_glfw_scroll_cb);
	glfwSetCursorPosCallback(w->m_glfw_win,m_glfw_cursor_cb);
	double x,y;
	glfwGetCursorPos(w->m_glfw_win,&x,&y);
	m_cursor_x = static_cast<float>(x);
	m_cursor_y = static_cast<float>(y);
}


void InputSystem::add_keyboard_listener(KeyboardListener *kbl)
{
	m_keyboard_listener.insert(kbl);
}

void InputSystem::add_mouse_listener(MouseListener *ml)
{
	m_mouse_listener.insert(ml);
}

void InputSystem::add_character_listener(CharacterListener *cl)
{
	m_char_listener.insert(cl);
}

void InputSystem::remove_keyboard_listener(KeyboardListener *kbl)
{
	m_keyboard_listener.erase(m_keyboard_listener.find(kbl));
}

void InputSystem::remove_mouse_listener(MouseListener *ml)
{
	m_mouse_listener.erase(m_mouse_listener.find(ml));
}

void InputSystem::remove_character_listener(CharacterListener *cl)
{
	m_char_listener.erase(m_char_listener.find(cl));
}

bool InputSystem::is_key_down(const Key k)
{
	return m_key_state[k];
}

bool InputSystem::is_button_down(const Button b)
{
	return m_button_state[b];
}

}
#endif
