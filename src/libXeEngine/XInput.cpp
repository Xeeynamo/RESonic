#include <stdio.h>
#include "XInput.h"
#include "System.h"
#include "Window.h"

#ifdef MVCPP
#include <XInput.h>
#include <windows.h>
#pragma comment(lib, "xinput.lib")
#endif

namespace XeEngine
{
	static XeEngine::XInput* xinput_input = nullptr;

	u8 ProcessXInput(u8 key)
	{
		switch(key)
		{
		case VK_RETURN:
			key = SpecialKey_RETURN;
			break;
		case VK_ESCAPE:
			key = SpecialKey_ESCAPE;
			break;
		case VK_LEFT:
			key = SpecialKey_LEFT;
			break;
		case VK_UP:
			key = SpecialKey_UP;
			break;
		case VK_RIGHT:
			key = SpecialKey_RIGHT;
			break;
		case VK_DOWN:
			key = SpecialKey_DOWN;
			break;
		case VK_HOME:
			key = SpecialKey_HOME;
			break;
		case VK_END:
			key = SpecialKey_END;
			break;
		case VK_PRIOR:
			key = SpecialKey_PGUP;
			break;
		case VK_NEXT:
			key = SpecialKey_PGDOWN;
			break;
		case VK_SPACE:
			key = SpecialKey_SPACE;
			break;
		case VK_CONTROL:
			key = SpecialKey_CTRL;
			break;
		case VK_MENU:
			key = SpecialKey_ALT;
			break;
		case VK_SHIFT:
			key = SpecialKey_SHIFT;
			break;
		case VK_APPS:
			key = SpecialKey_MENU;
			break;
		case VK_DELETE:
			key = SpecialKey_DELETE;
			break;
		case VK_F1:
			key = (key - VK_F1) + 0x10;
			break;
		default:
			key = 0xFF;
		}
		return key;
	}

	WIN32CALLBACK(WinInput_Callback)
	{
#ifdef MVCPP
		if (xinput_input == nullptr) return WIN32CALLBACK_NULLRETURN;

		XeEngine::MouseInput mouseInput;
		XeEngine::TouchInput touchInput;

		switch(message)
		{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_MOUSEMOVE:
			if (xinput_input->InputMouse != nullptr)
			{
				if (wParam & MK_LBUTTON)
					mouseInput = XeEngine::MouseInput_LEFT;
				else if (wParam & MK_RBUTTON)
					mouseInput = XeEngine::MouseInput_RIGHT;
				else if (wParam & MK_MBUTTON)
					mouseInput = XeEngine::MouseInput_MIDDLE;
				else
					mouseInput = XeEngine::MouseInput_MOVE;
				xinput_input->InputMouse(LOWORD(lParam), HIWORD(lParam), mouseInput);
			}
			break;
		case WM_LBUTTONUP:
			if (xinput_input->InputMouse != nullptr)
			{
				xinput_input->InputMouse(LOWORD(lParam), HIWORD(lParam), XeEngine::MouseInput_LEFT_UP);
			}
			break;
		case WM_RBUTTONUP:
			if (xinput_input->InputMouse != nullptr)
			{
				xinput_input->InputMouse(LOWORD(lParam), HIWORD(lParam), XeEngine::MouseInput_RIGHT_UP);
			}
			break;
		case WM_MBUTTONUP:
			if (xinput_input->InputMouse != nullptr)
			{
				xinput_input->InputMouse(LOWORD(lParam), HIWORD(lParam), XeEngine::MouseInput_MIDDLE_UP);
			}
			break;
			break;
		case WM_MOUSEWHEEL:
			{
				signed short wheel = HIWORD(wParam);
				wheel = (wheel / (WHEEL_DELTA));
				xinput_input->InputKeyb(0xE001 | (wheel << 16), false);
			}
			break;
		case WM_MOUSEHWHEEL:
			{
				signed short wheel = HIWORD(wParam);
				wheel = (wheel / (WHEEL_DELTA)) & 0xFFFF0000;
				xinput_input->InputKeyb(0xE002 | (wheel << 16), false);
			}
			break;

		case WM_KEYDOWN:
			if (wParam < 0x100)
			{
				u8 processedInput = ProcessXInput((u8)wParam);
				if (processedInput != 0xFF)
					xinput_input->keybSpecial[processedInput] = 1;
				xinput_input->keybStatus[(u8)wParam] = 1;
			}
			if (xinput_input->InputKeyb == nullptr) break;
			xinput_input->InputKeyb((XeEngine::InputButton)wParam, false);
			break;
		case WM_KEYUP:
			if (wParam < 0x100)
			{
				u8 processedInput = ProcessXInput((u8)wParam);
				if (processedInput != 0xFF)
					xinput_input->keybSpecial[processedInput] = 2;
				xinput_input->keybStatus[(u8)wParam] = 2;
			}
			if (xinput_input->InputKeyb == nullptr) break;
			xinput_input->InputKeyb((XeEngine::InputButton)wParam, true);
			break;
		case WM_CHAR:
			if (xinput_input->InputChar == nullptr) break;
			xinput_input->InputChar((XeEngine::InputButton)wParam);
			break;

		case WM_TOUCH:
			/*WORD cInputs = LOWORD(wParam);
			PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
			if (pInputs)
			{
				if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT)))
				{
					for(int i = 0; i < cInputs; i++)
					{
						if (pInputs[i].dwFlags | TOUCHEVENTF_PALM) continue;

						// Send input
					}
					CloseTouchInputHandle((HTOUCHINPUT)lParam);
				}
				delete[] pInputs;
			}*/
			/*if (LOWORD(wParam))
			{
				if (xinput_input->InputTouch == nullptr) break;
				if (GetTouchInputInfo((HTOUCHINPUT)lParam, 1, &pInputs, sizeof(TOUCHINPUT)))
				{
					if ((pInputs.dwFlags & TOUCHEVENTF_PALM) != false) break;

					switch(pInputs.dwFlags)
					{
					case TOUCHEVENTF_MOVE:
						touchInput = XeEngine::TouchInput_MOVE;
						break;
					case TOUCHEVENTF_DOWN:
						touchInput = XeEngine::TouchInput_DOWN;
						break;
					case TOUCHEVENTF_UP:
						touchInput = XeEngine::TouchInput_UP;
						if (pInputs.dwTime < 1000)
							touchInput = XeEngine::TouchInput_CLICK;
						else
							touchInput = XeEngine::TouchInput_LONG;
						break;
					default:
						touchInput = XeEngine::TouchInput_NOTHING;
						break;
					}
					xinput_input->InputTouch((u16)pInputs.x, (u16)pInputs.y, touchInput);
				}
			}*/
			{
				WORD cInputs = LOWORD(wParam);
				printf("Numero tocchi: %i\n", cInputs);
				PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
				if (pInputs)
				{
					if (GetTouchInputInfo((HTOUCHINPUT)lParam, cInputs, pInputs, sizeof(TOUCHINPUT)))
					{
						for(int i = 0; i < cInputs; i++)
						{
							printf("Input %i / %i\n", i + 1, cInputs);
							printf("(%3i, %3i)(%3i, %3i) ID %p  Time %p\n", pInputs[i].x, pInputs[i].y, pInputs[i].cxContact, pInputs[i].cyContact, pInputs[i].dwID, pInputs[i].dwTime);
							for(int i = 0; i < 32; i++)
							{
								switch(pInputs[i].dwFlags & ((1 << i)- 1))
								{
								case TOUCHEVENTF_MOVE:
									printf("Move ");
									break;
								case TOUCHEVENTF_DOWN:
									printf("Down ");
									break;
								case TOUCHEVENTF_UP:
									printf("Up ");
									break;
								case TOUCHEVENTF_INRANGE:
									printf("InRange ");
									break;
								case TOUCHEVENTF_PRIMARY:
									printf("Primary ");
									break;
								case TOUCHEVENTF_NOCOALESCE:
									printf("Nocoalesce ");
									break;
								case TOUCHEVENTF_PALM:
									printf("Palm ");
									break;
								}
							}
							printf("\n======\n");
							// Send input
						}
						CloseTouchInputHandle((HTOUCHINPUT)lParam);
					}
					delete[] pInputs;
				}
			}
			
			break;

		default:
			return WIN32CALLBACK_NULLRETURN;
		}
		return 0;
#else
	return WIN32CALLBACK_NULLRETURN;
#endif
	}
}

XeEngine::XInput::XInput(Window& window)
{
	m_window = &window;
	InputKeyb = NULL;
	InputChar = NULL;
	InputMouse = NULL;
	InputTouch = NULL;
	m_window->AddProcedure(WinInput_Callback);
	xinput_input = (XeEngine::XInput*)Get();
	con.Log(DEBUG_LEVEL_INFO, "XInput initialized");
}
XeEngine::XInput::~XInput()
{
	m_window->RemoveProcedure(WinInput_Callback);
}

void XeEngine::XInput::Update()
{
	Input::Update();

#ifdef MVCPP
	DWORD dwResult = 0;    
	for (DWORD i = 0; i < 4; i++)
	{
		XINPUT_STATE state;
		MemoryFill(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		//dwResult = XInputGetState(i, &state);

		if(dwResult == ERROR_SUCCESS)
		{
			gInput[i] = state.Gamepad.wButtons;
			lx[i] = state.Gamepad.sThumbLX;
			ly[i] = state.Gamepad.sThumbLY;
			rx[i] = state.Gamepad.sThumbRX;
			ry[i] = state.Gamepad.sThumbRY;
		}
		else
		{
			gInput[i] = 0;
			lx[i] = 0;
			ly[i] = 0;
			rx[i] = 0;
			ry[i] = 0;
		}
	}
#endif
	_ProcessAnalog();
	_Keyb2Joy();
	_MakeInputRepeat();

	//printf("\r%04X %04X %04X %+6i %+6i %04X - %04X", Peek(), PeekRepeat(), PeekNoRepeat(), GetLX(), GetLY(), (unsigned short)GetKeyState('1'), 0);
}

void XeEngine::XInput::Vibration(Rumble left, Rumble right, int player)
{
#ifdef MVCPP
	XINPUT_VIBRATION vib;
	vib.wLeftMotorSpeed = left;
	vib.wRightMotorSpeed = right;
	XInputSetState(player % 4, &vib);
#endif
}
