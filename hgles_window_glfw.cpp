#ifndef HGLES_USE_PI
#include <cstring>
#include <iostream>
#include "hgles_window_glfw.h"
#include "hgles_log.h"
#include "hgles_glad.h"
#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

namespace hgles
{
unsigned int Window::m_glfw_initiated = 0;

Window::Window(const int32_t w,
               const int32_t h,
               const uint32_t x,
               const uint32_t y)
    :m_glfw_win(nullptr), m_win_pos(x,y), m_win_sze(w,h)
{
    m_log = [](const std::string& str){std::cout<<"[ L ] "<<str<<"\n";};
    m_warning = [](const std::string& str){std::cout<<"[ W ] "<<str<<"\n";};
    m_error= [](const std::string& str){std::cerr<<"[ E ] "<<str<<"\n";};
    m_input_system = nullptr;
    if(!m_glfw_initiated)
    {
        if (!glfwInit())
        {
            m_error("Failed to init GLFW");
            exit(0);
        }
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    int the_width = w;
    int the_height = h;
    int monitor_count;
    GLFWmonitor** monitors = glfwGetMonitors (&monitor_count);
    const GLFWvidmode* vm = glfwGetVideoMode(monitors[0]);
    if(w<0 && h <0)
    {
        glfwWindowHint(GLFW_DECORATED,GLFW_FALSE);


    }


    if(w<0)
        the_width = vm->width;
    if(h<0)
        the_height = vm->height;
    m_glfw_win = glfwCreateWindow(the_width,
                                  the_height,
                                  "Window",
                                  nullptr,
                                  nullptr);
    if(!m_glfw_win)
    {
        m_error("Failed to create glfwWindow");
        exit(0);
    }




    glfwMakeContextCurrent(m_glfw_win);
    glfwSetWindowPos(m_glfw_win,static_cast<int>(x),static_cast<int>(y));

    if(!m_glfw_initiated)
    {
        if(!gladLoadGLES2Loader(
                    reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            m_error("Failed to load GL using GLAD!");
            exit(0);
        }

        m_glfw_initiated++;;
    }
    glfwSetWindowUserPointer(m_glfw_win,this);

    glfwSetWindowPosCallback(m_glfw_win,Window::m_glfw_window_pos_fun);
    glfwSetWindowSizeCallback(m_glfw_win,Window::m_glfw_window_size_fun);

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

void Window::add_window_listener(WindowListener *wl)
{
    m_window_listeners.insert(wl);
    wl->size_changed(m_win_sze.x,m_win_sze.y);
    wl->position_changed(m_win_pos.x,m_win_pos.y);
}

void Window::remove_window_listener(WindowListener *wl)
{
    m_window_listeners.erase(m_window_listeners.find(wl));
}

void Window::poll_events()
{
    glfwPollEvents();
}

void Window::set_title(const std::string &title)
{
    glfwSetWindowTitle(m_glfw_win,title.c_str());
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
        glfwSetWindowMonitor(m_glfw_win,
                             NULL,
                             m_win_pos.x,
                             m_win_pos.y,
                             m_win_sze.x,
                             m_win_sze.y,
                             60);
    }
}

void Window::toggle_decoration()
{

#if GLFW_VERSION_MAJOR >=3 && GLFW_VERSION_MINOR >=3
    auto is = glfwGetWindowAttrib(m_glfw_win,GLFW_DECORATED);
    glfwSetWindowAttrib(m_glfw_win,GLFW_DECORATED,is?GLFW_FALSE:GLFW_TRUE);
#else
    m_log("GLFW version 3.3 is required to toggle window decoration!");
#endif

}

void Window::set_decoration(bool dec)
{

#if GLFW_VERSION_MAJOR >=3 && GLFW_VERSION_MINOR >=3
    glfwSetWindowAttrib(m_glfw_win,GLFW_DECORATED,dec?GLFW_TRUE:GLFW_FALSE);
#else
    HGLES_UNUSED(dec);
    m_log("GLFW version 3.3 is required to set window decoration!");
#endif


}


void Window::m_glfw_window_size_fun(GLFWwindow *win, int w, int h)
{
    Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
    for(auto& l : ww->m_window_listeners)
    {
        l->size_changed(w,h);
    }
}

void Window::m_glfw_window_pos_fun(GLFWwindow *win, int x, int y)
{
    Window* ww = reinterpret_cast<Window*>(glfwGetWindowUserPointer((win)));
    for(auto& l : ww->m_window_listeners)
    {
        l->position_changed(x,y);
    }
}

void Window::set_size(const int w, const int h)
{
    glfwSetWindowSize(m_glfw_win,w>0?w:1,h>0?h:1);
}

void Window::set_size(const glm::ivec2 &sze)
{
    set_size(sze.x,sze.y);
}

glm::ivec2 Window::get_size() const
{
    glm::ivec2 r;
    glfwGetWindowSize(m_glfw_win,&(r.x),&(r.y));
    return r;
}

void Window::set_position(const int x, const int y)
{
    glfwSetWindowPos(m_glfw_win,x,y);
}

void Window::set_position(const glm::ivec2 &pos)
{
    set_position(pos.x,pos.y);
}

glm::ivec2 Window::get_position() const
{
    glm::ivec2 r;
    glfwGetWindowPos(m_glfw_win,&(r.x),&(r.y));
    return r;
}

}
#endif
