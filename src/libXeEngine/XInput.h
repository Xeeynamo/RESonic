#pragma once
#include "Input.h"

namespace XeEngine
{
	enum MouseInput
	{
		//! \brief It happens when nothing was pressed
		MouseInput_NOTHING = 0,

		//! \brief Handle the movement of a Mouse
		MouseInput_MOVE,

		//! \brief Handle the LEFT button of a Mouse
		MouseInput_LEFT,

		//! \brief Handle the LEFT UP button of a Mouse
		MouseInput_LEFT_UP,

		//! \brief Handle the RIGHT button of a Mouse
		MouseInput_RIGHT,

		//! \brief Handle the RIGHT UP button of a Mouse
		MouseInput_RIGHT_UP,

		//! \brief Handle the MIDDLE button of a Mouse
		MouseInput_MIDDLE,

		//! \brief Handle the MIDDLE UP button of a Mouse
		MouseInput_MIDDLE_UP,

		//! \brief Handle the wheel of a Mouse
		//! \details X will handle the Vertical scroll, Y the Horizontal scroll
		MouseInput_WHEEL,
	};

	enum TouchInput
	{
		//! \brief It happens when the touch can't be handled
		//! \details Can emulate XeEngine::MouseInput::MouseInput_NOTHING
		TouchInput_NOTHING,

		//! \brief It happens when the touch is in movement
		//! \details Can emulate XeEngine::MouseInput::MouseInput_WHEEL
		TouchInput_MOVE,

		//! \brief It happens when the screen will handle a touch
		//! \details Can emulate XeEngine::MouseInput::MouseInput_MOVE
		TouchInput_DOWN,

		//! \brief It happens when a touch was left from the screen
		//! \details Can emulate XeEngine::MouseInput::MouseInput_MOVE
		TouchInput_UP,

		//! \brief It happens when a touch was done quickly (less than 1 second)
		//! \details Can emulate XeEngine::MouseInput::MouseInput_LEFT
		TouchInput_CLICK,

		//! \brief It happens when a touch was pressed for a long period (more than 1 second)
		//! \details Can emulate XeEngine::MouseInput::MouseInput_RIGHT
		TouchInput_LONG,
	};

	typedef unsigned int InputButton;

	class Window;
	class XInput : public Input
	{
	private:
		Window* m_window;
	protected:
	public:
		//! \param A XeEngine::Window is useful for get the various input messages
		XInput(Window&);
		~XInput();

		virtual void Update();
		virtual void Vibration(Rumble left, Rumble right, int player = 0);

		//! \brief Handle the keyboard input
		//! \details Callback for the virtual keyboard input
		//! \param The pressed key
		//! \param TRUE if the key was release, FALSE if the key was pressed
		void (*InputKeyb)(InputButton key, bool up);

		//! \brief Handle the keyboard input as characters
		//! \details Callback. for character input (usually text)
		//! \param The pressed character
		void (*InputChar)(InputButton key);

		//! \brief Handle the mouse input
		//! \details Callback for mouse input
		//! \param Coordinate X of the mouse
		//! \param Coordinate Y of the mouse
		//! \param XeEngine::MouseInput
		void (*InputMouse)(unsigned short x, unsigned short y, MouseInput button);

		//! \brief Handle the touch input
		//! \details Callback for touch input
		//! \param Coordinate X of the touched area
		//! \param Coordinate Y of the touched area
		//! \param XeEngine::TouchInput
		void (*InputTouch)(unsigned short x, unsigned short y, TouchInput button);
	};
}
