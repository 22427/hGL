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
	virtual void button_down(const uint32_t button);
	virtual void button_up(const uint32_t button);
	virtual void cursor(const float x, const float y);
	virtual void scroll(const float x, const float y);
};

class InputSystem
{
public:
	virtual void add_keyboard_listener(KeyboardListener* kbl) = 0;
	virtual void add_mouse_listener(MouseListener* kbl) = 0;
	virtual void add_character_listener(CharacterListener* kbl) = 0;

	virtual bool is_key_down(const Key k)=0;
	virtual bool is_button_down(const uint32_t b)=0;
};

}
