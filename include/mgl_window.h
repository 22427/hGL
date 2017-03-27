#pragma once
#include <functional>
#include <glad/glad.h>
namespace mgl {

class  Window
{

public:

	virtual ~Window(){}
	virtual void make_current() =0;
	virtual void unmake_current() =0;
	virtual void swap_buffers() =0;

	virtual void poll_events() =0;

	virtual void set_title(const std::string& title) =0;
	virtual void set_size_callback(std::function<void (int w,int h)> fun) =0;
	virtual void set_position_callback(std::function<void (int x ,int y)> fun) =0;
	virtual void set_button_callback(std::function<void (int button,
													 int action,
													 int mods)> fun) =0;
	virtual void set_cursor_callback(std::function<void (double x,double y)> fun) =0;
	virtual void set_scroll_callback(std::function<void (double x,double y)> fun) =0;
	virtual void set_key_down_callback(std::function<void (int key, int scancode, int mods)> fun) =0;
	virtual void set_key_up_callback(std::function<void (int key, int scancode, int mods)> fun) =0;
	virtual void set_char_callback(std::function<void (unsigned int c, int mods)> fun) =0;

	virtual void toggle_fullscreen() =0;
	virtual void set_fullscreen(bool fs = true) =0;

	virtual void toggle_decoration() =0;
	virtual void set_decoration(bool dec = true) =0;

	virtual bool should_close() =0;
	virtual void set_should_close(bool s_c = true) =0;

	virtual bool is_key_down(int key) const = 0;

};



}
