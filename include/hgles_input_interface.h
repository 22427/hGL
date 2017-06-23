#pragma once
#include <cstdint>
#include "hgles_input_keys.h"

namespace hgles {

class KeyboardListener
{
public:
	virtual void key_down(const Key k);
	virtual void key_up(const Key k);
	virtual void key_repeat(const Key k);
};

class CharacterListener
{
public:
	virtual void char_input(const uint32_t c);
};


class MouseListener
{
public:
	virtual void button_down(const Button button);
	virtual void button_up(const Button button);
	virtual void cursor_move(const float dx, const float dy);
	virtual void cursor(const float x, const float y);
	virtual void scroll(const float x, const float y);
};

#ifndef NDEBUG
class Window;
class InputSystemInterface
{
public:
	virtual void init(Window* w) = 0;
	virtual void poll_events() = 0;

	virtual void add_keyboard_listener(KeyboardListener* kbl) = 0;
	virtual void add_mouse_listener(MouseListener* ml) = 0;
	virtual void add_character_listener(CharacterListener* cl) = 0;

	virtual void remove_keyboard_listener(KeyboardListener* kbl) = 0;
	virtual void remove_mouse_listener(MouseListener* ml) = 0;
	virtual void remove_character_listener(CharacterListener* cl) = 0;

	virtual bool is_key_down(const Key k)=0;
	virtual bool is_button_down(const Button b)=0;
};

// Dummies!!
inline void KeyboardListener::key_down(const Key){}
inline void KeyboardListener::key_up(const Key ){}
inline void KeyboardListener::key_repeat(const Key ){}
inline void CharacterListener::char_input(const uint32_t ){}
inline void MouseListener::button_down(const Button ){}
inline void MouseListener::button_up(const Button){}
inline void MouseListener::cursor(const float, const float){}
inline void MouseListener::cursor_move(const float, const float){}
inline void MouseListener::scroll(const float, const float){}


#endif
}
