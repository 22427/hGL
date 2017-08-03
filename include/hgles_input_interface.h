#pragma once
#include <cstdint>
#include "hgles_input_keys.h"

namespace hgles {

class KeyboardListener
{
public:
	virtual ~KeyboardListener();
	virtual void key_down(const Key k);
	virtual void key_up(const Key k);
	virtual void key_repeat(const Key k);
};

class CharacterListener
{
public:
	virtual ~CharacterListener();
	virtual void char_input(const uint32_t c);
};


class MouseListener
{
public:
	virtual ~MouseListener();
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
	virtual ~InputSystemInterface();
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
#endif
}
