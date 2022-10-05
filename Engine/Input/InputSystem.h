#pragma once
#include <vector>
#include <cstdint>
#include "../Math/Vector2.h"
#include <array>

namespace squampernaut
{
	class InputSystem
	{
	public:
		enum KeyState
		{
			Idle,
			Pressed,
			Held,
			Released
		};
	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		KeyState GetKeyState(int key);

		bool GetKeyDown(int key) { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(int key) { return m_prevKeyboardState[key]; };


		const Vector2& GetMousePosition() const { return m_mousePosition; }

		KeyState GetButtonState(uint32_t button);

		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) {
			return m_prevMouseButtonState[button];
		}


	private:
		int m_numKeys;

		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

		Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_w;
	extern const uint32_t key_s;
	extern const uint32_t key_a;
	extern const uint32_t key_d;
	extern const uint32_t key_shiftL;
	extern const uint32_t key_escape;

	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_ctrlR;
	extern const uint32_t key_altR;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;

}