#include "hgles_input_interface.h"
/**
 * Dummy implementations for the input interfaces.
 */
namespace hgles
{
MouseListener::~MouseListener()
{

}

void MouseListener::button_down(const Button /*button*/)
{

}

void MouseListener::button_up(const Button /*button*/)
{

}

void MouseListener::cursor_move(const float /*dx*/, const float /*dy*/)
{

}

void MouseListener::cursor(const float /*x*/, const float /*y*/)
{

}

void MouseListener::scroll(const float /*x*/, const float /*y*/)
{

}

KeyboardListener::~KeyboardListener()
{

}

void KeyboardListener::key_down(const Key /*k*/)
{

}

void KeyboardListener::key_up(const Key /*k*/)
{

}

void KeyboardListener::key_repeat(const Key /*k*/)
{

}

CharacterListener::~CharacterListener()
{

}

void CharacterListener::char_input(const uint32_t /*c*/)
{

}
#ifndef NDEBUG
InputSystemInterface::~InputSystemInterface(){}
#endif

}
