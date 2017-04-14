#pragma once
#include "hgles_input_interface.h"
#include "hgles_dll.h"
#include <cstdint>
#include <unordered_set>
#include <poll.h>
#include <vector>
namespace hgles
{
	class MGL_DLL_PUBLIC InputSystem :
			#ifndef NDEBUG
			public InputSystemInterface
			#endif
	{
		uint8_t m_key_state[K_LAST+1];
		uint8_t m_button_state[BUTTON_LAST+1];
		std::vector<KeyboardListener*> m_keyboard_listener;
		std::vector<MouseListener*> m_mouse_listener;
		std::vector<CharacterListener*> m_char_listener;

		std::vector<pollfd> m_observed_keyboards;
		std::vector<pollfd> m_observed_mice;


		void turn_on_keyboards();
		void turn_off_keyboards();

		void turn_on_mice();
		void turn_off_mice();

		int m_cursor_position[2];
		int m_wheel_position[2];
	public:
		InputSystem();
		void init(Window *w);
		void add_keyboard_listener(KeyboardListener *kbl);
		void remove_keyboard_listener(KeyboardListener *kbl);

		void add_mouse_listener(MouseListener *ml);
		void remove_mouse_listener(MouseListener *ml);

		void add_character_listener(CharacterListener */*cl*/){}
		void remove_character_listener(CharacterListener */*cl*/){}

		bool is_key_down(const Key k){return m_key_state[k];}
		bool is_button_down(const Button b){return m_button_state[b];}

		void poll_events();
	};
}
