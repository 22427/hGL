#pragma once
#include "dep/glm/vec2.hpp"

#include <string>
#include <functional>


namespace hgles {

class WindowListener
{
public:
	virtual void size_changed(const int w, const int h);
	virtual void position_changed(const int x, const int y);
};

inline void WindowListener::size_changed(const int /*w*/, const int /*h*/) {}
inline void WindowListener::position_changed(const int /*x*/, const int /*y*/) {}

#ifndef NDEBUG
class InputSystem;
class  WindowInterface
{

public:

	virtual ~WindowInterface(){}
	virtual void make_current() =0;
	virtual void unmake_current() =0;

	virtual void swap_buffers() =0;
	virtual void poll_events() =0;

	virtual void set_title(const std::string& title) =0;

	virtual void add_window_listener(WindowListener* wl) =0;
	virtual void remove_window_listener(WindowListener* wl) =0;

	virtual void toggle_fullscreen() =0;
	virtual void set_fullscreen(bool fs = true) =0;

	virtual void toggle_decoration() =0;
	virtual void set_decoration(bool dec = true) =0;

	virtual bool should_close() =0;
	virtual void set_should_close(bool s_c = true) =0;


	virtual void set_size(const int w, const int h) =0 ;
	virtual void set_size(const glm::ivec2& sze) =0 ;
	virtual glm::ivec2 get_size() const =0 ;

	virtual void set_position(const int x, const int y) =0 ;
	virtual void set_position(const glm::ivec2& pos) =0 ;
	virtual glm::ivec2 get_position() const  =0 ;



};
#endif


}
