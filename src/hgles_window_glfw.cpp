#ifdef HGLES_USE_GLFW
#include <hgles_window_glfw.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <hgles_log.h>
namespace hgles
{



unsigned int Window::m_glfw_initiated = 0;

Window::Window(const uint32_t w, const uint32_t h)
	:m_glfw_win(nullptr)
{
	memset(m_key_state,0,512);
	if(!m_glfw_initiated)
	{
		if (!glfwInit())
		{
			CRIT_ERROR("Failed to init GLFW");
		}
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_glfw_win = glfwCreateWindow(static_cast<int>(w),
								  static_cast<int>(h),
								  "Window",
								  nullptr,
								  nullptr);
	if(!m_glfw_win)
		CRIT_ERROR("Failed to create glfwWindow");

	glfwMakeContextCurrent(m_glfw_win);

	if(!m_glfw_initiated)
	{
		if(!gladLoadGLES2Loader(
					reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			CRIT_ERROR("Failed to load GL using GLAD!");
		}

		m_glfw_initiated++;;
	}
	glfwSetWindowUserPointer(m_glfw_win,this);
	glfwSetErrorCallback(&m_glfw_error_callback);
}

Window::~Window()
{
	m_glfw_initiated--;
	if(m_glfw_win)
		glfwDestroyWindow(m_glfw_win);
	if(m_glfw_initiated==0)
		glfwTerminate();
}

void Window::make_current()
{
	glfwMakeContextCurrent(m_glfw_win);
}

void Window::unmake_current()
{
	glfwMakeContextCurrent(nullptr);
}

void Window::swap_buffers()
{
	glfwSwapBuffers(m_glfw_win);
}

bool Window::should_close()
{
	return glfwWindowShouldClose(m_glfw_win);
}

void Window::set_should_close(bool s_c)
{
	glfwSetWindowShouldClose(m_glfw_win,s_c);
}

void Window::poll_events()
{
	glfwPollEvents();
}

void Window::set_title(const std::string &title)
{
	glfwSetWindowTitle(m_glfw_win,title.c_str());
}

void Window::set_size_callback(std::function<void (int, int)> fun)
{
	if(!m_size_fun)
	{

		glfwSetWindowSizeCallback(m_glfw_win,&m_glfw_window_size_fun);
	}
	m_size_fun = fun;
	if(!m_size_fun)
	{
		glfwSetWindowSizeCallback(m_glfw_win,nullptr);
	}
	else
	{
		int w =0 ,h = 0;
		glfwGetWindowSize(m_glfw_win,&w,&h);
		m_size_fun(w,h);
	}
}

void Window::set_position_callback(std::function<void (int, int)> fun)
{
	GLFW_KEY_ESCAPE

	if(!m_pos_fun)
	{
		glfwSetWindowPosCallback(m_glfw_win,&m_glfw_window_pos_fun);
	}
	m_size_fun = fun;
	if(!m_pos_fun)
	{
		glfwSetWindowPosCallback(m_glfw_win,nullptr);
	}
	else
	{
		int x =0 ,y = 0;
		glfwGetWindowPos(m_glfw_win,&x,&y);
		m_pos_fun(x,y);
	}
}

void Window::set_button_callback(std::function<void (int, int, int)> fun)
{
	if(!m_mouse_button_fun)
	{
		glfwSetWindowPosCallback(m_glfw_win,&m_glfw_window_pos_fun);
	}
	m_mouse_button_fun = fun;
	if(!fun)
	{
		glfwSetMouseButtonCallback(m_glfw_win,nullptr);
	}
}

void Window::set_cursor_callback(std::function<void (double, double)> fun)
{
	if(!m_cursor_pos_fun)
	{
		glfwSetCursorPosCallback(m_glfw_win,&m_glfw_cursor_pos_fun);
	}
	m_cursor_pos_fun = fun;
	if(!fun)
	{
		glfwSetCursorPosCallback(m_glfw_win,nullptr);
	}
}

void Window::set_scroll_callback(std::function<void (double, double)> fun)
{
	if(!m_scroll_fun)
	{
		glfwSetScrollCallback(m_glfw_win,&m_glfw_scroll_fun);
	}
	m_scroll_fun = fun;
	if(!fun)
	{
		glfwSetScrollCallback(m_glfw_win,nullptr);
		return;
	}
}

void Window::set_key_down_callback(std::function<void (int, int, int)> fun)
{
	if(!m_key_down_fun)
	{
		glfwSetKeyCallback(m_glfw_win,&m_glfw_key_fun);
	}
	m_key_down_fun = fun;
	if(!fun)
	{
		glfwSetKeyCallback(m_glfw_win,nullptr);
		return;
	}
}

void Window::set_key_up_callback(std::function<void (int, int, int)> fun)
{
	if(!m_key_up_fun)
	{
		glfwSetKeyCallback(m_glfw_win,&m_glfw_key_fun);
	}
	m_key_up_fun = fun;
	if(!fun)
	{
		glfwSetKeyCallback(m_glfw_win,nullptr);
		return;
	}
}


void Window::set_char_callback(std::function<void (unsigned int, int)> fun)
{
	if(!m_char_fun)
	{
		glfwSetCharModsCallback(m_glfw_win,&m_glfw_char_mods_fun);
	}
	m_char_fun = fun;
	if(!fun)
	{
		glfwSetCharModsCallback(m_glfw_win,nullptr);
		return;
	}
}

void Window::set_fullscreen(bool fs)
{
	auto mon = glfwGetWindowMonitor(m_glfw_win);
	if(! mon && fs) // there is no monitor and we want there to be one
	{
		glfwGetWindowSize(m_glfw_win,&m_win_sze.x,&m_win_sze.y);
		glfwGetWindowPos(m_glfw_win,&m_win_pos.x,&m_win_pos.y);

		mon = glfwGetPrimaryMonitor();
		auto vm = glfwGetVideoMode(mon);
		glfwSetWindowMonitor(m_glfw_win,
							 glfwGetPrimaryMonitor(),
							 0,0,vm->width,vm->height,vm->refreshRate);
	}
	else if(mon && !fs) // there is one and we want it to go away
	{
		glfwSetWindowMonitor(m_glfw_win,NULL,m_win_pos.x,m_win_pos.y,m_win_sze.x,m_win_sze.y,60);
	}
}

void Window::toggle_fullscreen()
{
	auto mon = glfwGetWindowMonitor(m_glfw_win);
	if(! mon) // there is no monitor and we want there to be one
	{
		glfwGetWindowSize(m_glfw_win,&m_win_sze.x,&m_win_sze.y);
		glfwGetWindowPos(m_glfw_win,&m_win_pos.x,&m_win_pos.y);

		mon = glfwGetPrimaryMonitor();
		auto vm = glfwGetVideoMode(mon);
		glfwSetWindowMonitor(m_glfw_win,
							 glfwGetPrimaryMonitor(),
							 0,0,
							 vm->width,vm->height,vm->refreshRate);
	}
	else // there is one and we want it to go away
	{
		glfwSetWindowMonitor(m_glfw_win,NULL,m_win_pos.x,m_win_pos.y,m_win_sze.x,m_win_sze.y,60);
	}
}

void Window::toggle_decoration()
{
	auto is = glfwGetWindowAttrib(m_glfw_win,GLFW_DECORATED);
	glfwSetWindowAttrib(m_glfw_win,GLFW_DECORATED,is?GLFW_FALSE:GLFW_TRUE);

}

void Window::set_decoration(bool dec)
{
	glfwSetWindowAttrib(m_glfw_win,GLFW_DECORATED,dec?GLFW_TRUE:GLFW_FALSE);
}


void Window::m_glfw_window_size_fun(GLFWwindow *win, int w, int h)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_size_fun)
		c->m_size_fun(w,h);
}

void Window::m_glfw_window_pos_fun(GLFWwindow *win, int x, int y)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_pos_fun)
		c->m_pos_fun(x,y);
}

void Window::m_glfw_mouse_button_fun(GLFWwindow *win, int button, int action, int mods)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_mouse_button_fun)
		c->m_mouse_button_fun(button,action,mods);
}

void Window::m_glfw_cursor_pos_fun(GLFWwindow *win, double x, double y)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_cursor_pos_fun)
		c->m_cursor_pos_fun(x,y);
}

void Window::m_glfw_scroll_fun(GLFWwindow *win, double x, double y)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_scroll_fun)
		c->m_scroll_fun(x,y);
}

void Window::m_glfw_key_fun(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_key_down_fun && action == GLFW_PRESS)
	{
		c->m_key_state[key] = 1;
		c->m_key_down_fun(key,scancode,mods);
	}
	if(c->m_key_up_fun && action == GLFW_RELEASE)
	{
		c->m_key_state[key] = 0;
		c->m_key_up_fun(key,scancode,mods);
	}
}

void Window::m_glfw_char_mods_fun(GLFWwindow *win, unsigned int ch, int mod)
{
	Window* c = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(c->m_char_fun)
		c->m_char_fun(ch,mod);
}

void Window::m_glfw_error_callback(int err_no, const char *txt)
{
	ERROR("%d : %s",err_no,txt);
}

}
#endif
