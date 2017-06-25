#include "WinAPI.h"

namespace XeEngine
{
	namespace WindowFramework
	{
		const char* winapi_classname = "xeengine::winapi";
		WinAPI* winapi_currentwindow = nullptr;
		UINT winapi_icon[] = {0, MB_ICONINFORMATION, MB_ICONWARNING, MB_ICONERROR};
		UINT winapi_button[] = {MB_OK, MB_OKCANCEL, MB_YESNO, MB_YESNOCANCEL};

		LRESULT __stdcall WinAPI_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			if (winapi_currentwindow && winapi_currentwindow->GetHandle() == hWnd)
			{
				return winapi_currentwindow->WindowProc(uMsg, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}

		WinAPI::WinAPI()
		{
			m_hwnd = nullptr;
			m_minSize.Set(0, 0);
			m_maxSize.Set(65535, 65535);
		}
		WinAPI::~WinAPI()
		{
			UnregisterClass(winapi_classname, GetModuleHandle(NULL));
		}

		bool WinAPI::Initialize()
		{
			WNDCLASS  wc;        // Windows Class Structure
			// Redraw On Size, And Own DC For Window.
			wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc    = (WNDPROC)WinAPI_WindowProc;		// WndProc Handles Messages
			wc.cbClsExtra     = 0;								// No Extra Window Data
			wc.cbWndExtra     = 0;
			wc.hInstance      = GetModuleHandle(NULL);          // Set The Instance
			wc.hIcon          = LoadIcon(NULL, IDI_WINLOGO);    // Load The Default Icon
			wc.hCursor        = LoadCursor(NULL, IDC_ARROW);    // Load The Arrow Pointer
			wc.hbrBackground  = NULL;                           // No Background Required For GL
			wc.lpszMenuName   = NULL;							// Set the menu
			wc.lpszClassName  = winapi_classname;				// Set the class name
			RegisterClass(&wc);

			m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, winapi_classname, "Window",
				GetStyle(false), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL,	GetModuleHandle(NULL), NULL);

			UpdateWindow(m_hwnd);
			m_backgroundcolor = (HBRUSH)(COLOR_WINDOW+1);
			m_initialized = true;
			return m_initialized;
		}
		bool WinAPI::Do()
		{
			winapi_currentwindow = this;
			MSG msg;
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				if(msg.message == WM_QUIT)
				{
					return false;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			return true;
		}
		bool WinAPI::IsTouchCapable()
		{
			return (GetSystemMetrics(SM_DIGITIZER) & (0x80 + 0x40)) != 0;
		}
		bool WinAPI::EnableTouch(bool enable)
		{
			return (enable ? RegisterTouchWindow(m_hwnd, 0) : UnregisterTouchWindow(m_hwnd)) == 0;
		}

		// *** Aspect
		void WinAPI::BackgroundColor(const unsigned int color)
		{
			m_backgroundcolor = CreateSolidBrush(color & 0xFFFFFF);
		}
		void WinAPI::SetTitle(const char* text)
		{
			SetWindowText((HWND)GetHandle(), text);
		}
		void WinAPI::SetStyle(const Style style)
		{

		}
		void WinAPI::Show(const bool show)
		{
			ShowWindow((HWND)GetHandle(), show == true ? SW_SHOW : SW_HIDE);
		}
		void WinAPI::ShowIcon(const bool show)
		{

		}
		void WinAPI::ShowMaximize(const bool show)
		{

		}
		void WinAPI::ShowMinimize(const bool show)
		{

		}
		void WinAPI::AlwaysOnTop(const bool top)
		{
			SetWindowPos((HWND)GetHandle(), top ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		// *** Layout
		void WinAPI::GetLocation(Point& point) const
		{
			RECT rcWindow;
			GetWindowRect((HWND)m_hwnd, &rcWindow);
			point.x = rcWindow.left;
			point.y = rcWindow.top;
		}
		void WinAPI::SetLocation(const Point& point)
		{
			if (m_positioning == Window::Positioning_Centered)
				CenterToScreen();
		}
		void WinAPI::GetSize(Size& size) const
		{
			RECT rcWindow;
			GetWindowRect((HWND)m_hwnd, &rcWindow);
			size.x = rcWindow.right - rcWindow.left;
			size.y = rcWindow.bottom - rcWindow.top;
		}
		void WinAPI::SetSize(const Size& size)
		{
			Size sizeToSet;

			if (size.x > m_maxSize.x) sizeToSet.x = m_maxSize.x;
			else if (size.x < m_minSize.x) sizeToSet.x = m_minSize.x;
			else sizeToSet.x = size.x;

			if (size.y > m_maxSize.y) sizeToSet.y = m_maxSize.y;
			else if (size.y < m_minSize.y) sizeToSet.y = m_minSize.y;
			else sizeToSet.y = size.y;

			RECT rcWindow;
			GetWindowRect((HWND)GetHandle(), &rcWindow);

			RECT rcClient;
			GetClientRect((HWND)GetHandle(), &rcClient);

			POINT ptDiff;
			ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
			ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
			rcClient.right = rcClient.left + sizeToSet.x;
			rcClient.bottom = rcClient.top + sizeToSet.y;

			AdjustWindowRectEx(&rcClient, (DWORD)GetWindowLongPtr((HWND)GetHandle(), GWL_STYLE), FALSE, GetWindowLong((HWND)GetHandle(), GWL_EXSTYLE));

			SetWindowPos((HWND)GetHandle(), 0, 0, 0, sizeToSet.x + ptDiff.x, sizeToSet.y + ptDiff.y,
				SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

			if (m_positioning == Window::Positioning_Centered)
				CenterToScreen();
		}
		void WinAPI::SetMinimumSize(const Size& size)
		{
			Size currentSize;
			m_minSize = size;
			GetSize(currentSize);
			SetSize(currentSize);
		}
		void WinAPI::SetMaximumSize(const Size& size)
		{
			Size currentSize;
			m_maxSize = size;
			GetSize(currentSize);
			SetSize(currentSize);
		}
		void WinAPI::SetPositioning(const Positioning& positioning)
		{
			m_positioning = positioning;
			switch(m_positioning)
			{
			case Window::Positioning_Centered:
				CenterToScreen();
				break;
			}
		}

		// *** Commands
		Window::MessageBoxReturn WinAPI::ShowMessage(const MessageBoxType type, const MessageBoxButtons buttons, const char* text)
		{
			switch(MessageBox((HWND)GetHandle(), text, NULL, winapi_icon[type] | winapi_button[buttons]))
			{
			case IDOK:
				return MessageBoxReturn_Ok;
			case IDCANCEL:
				return MessageBoxReturn_Cancel;
			case IDABORT:
				return MessageBoxReturn_Ok;
			case IDRETRY:
				return MessageBoxReturn_Ok;
			case IDIGNORE:
				return MessageBoxReturn_Ok;
			case IDYES:
				return MessageBoxReturn_Yes;
			case IDNO:
				return MessageBoxReturn_No;
			}
			return MessageBoxReturn_Ok;
		}
		bool WinAPI::IsFocus()
		{
			return GetActiveWindow() == (HWND)GetHandle();
		}
		void WinAPI::SetFocus()
		{
			BringWindowToTop((HWND)GetHandle());
		}
		bool WinAPI::IsIconic()
		{
			return ::IsIconic((HWND)GetHandle()) != 0;
		}
		void WinAPI::SetIconic(bool iconic)
		{
			::ShowWindow((HWND)GetHandle(), iconic ? SW_SHOWMINIMIZED : SW_SHOW);
		}
		bool WinAPI::IsMaximize()
		{
			return false;
		}
		void WinAPI::SetMaximize(bool maximize)
		{
			::ShowWindow((HWND)GetHandle(), maximize ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
		}
		void WinAPI::CenterToScreen()
		{
			RECT rcDesktop, rcWindow;
			GetWindowRect(GetDesktopWindow(), &rcDesktop);

			// Substract the task bar
			HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), NULL);
			if (hTaskBar != NULL)
			{
				APPBARDATA abd;

				abd.cbSize = sizeof(APPBARDATA);
				abd.hWnd = hTaskBar;

				SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
				SubtractRect(&rcDesktop, &rcDesktop, &abd.rc);
			}
			GetWindowRect((HWND)GetHandle(), &rcWindow);

			int offsetX = (rcDesktop.right - rcDesktop.left - (rcWindow.right - rcWindow.left)) / 2;
			offsetX = (offsetX > 0) ? offsetX : rcDesktop.left;
			int offsetY = (rcDesktop.bottom - rcDesktop.top - (rcWindow.bottom - rcWindow.top)) / 2;
			offsetY = (offsetY > 0) ? offsetY : rcDesktop.top;

			SetWindowPos((HWND)GetHandle(), 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		}
		void WinAPI::Close()
		{
			DestroyWindow((HWND)GetHandle());
		}
		void WinAPI::Scale(float scale)
		{

		}
		void* WinAPI::GetHandle()
		{
			return m_hwnd;
		}

		DWORD WinAPI::GetStyle(bool fullscreen)
		{
			DWORD style = 0;

			if (fullscreen)
			{
				style |= WS_POPUP;
			}
			else
			{
				style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
				style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
			}
			return style;
		}
		LRESULT __stdcall WinAPI::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_CREATE:
				if (OnCreate) OnCreate(*this);
				break;
			case WM_DESTROY:
				if (OnDestroy) OnDestroy(*this);
				PostQuitMessage(0);
				break;
			case WM_MOVE:
				if (OnMove) OnMove(*this);
				break;
			case WM_SIZE:
				if (OnResize) OnResize(*this);
				break;
			case WM_SETFOCUS:
				if (OnEnter) OnEnter(*this);
				break;
			case WM_KILLFOCUS:
				if (OnLeave) OnLeave(*this);
				break;
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					BeginPaint((HWND)GetHandle(), &ps);
					FillRect(ps.hdc, &ps.rcPaint, m_backgroundcolor);
					if (OnPaint) OnDestroy(*this);
					EndPaint((HWND)GetHandle(), &ps);
				}
				return 0;
			case WM_CLOSE:
				{
					bool closeAccepted = true;
					if (OnClose) closeAccepted = OnClose(*this);
					if (closeAccepted == true)
					{
						Close();
					}
				}
				return 0;
			case WM_MOUSEMOVE:
				//con.Log(DEBUG_LEVEL_INFO, "Mouse move %4i %4i", LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_LBUTTONDOWN:
				//con.Log(DEBUG_LEVEL_INFO, "WM_LBUTTONDOWN");
				break;
			case WM_LBUTTONUP:
				//con.Log(DEBUG_LEVEL_INFO, "WM_LBUTTONUP");
				break;
			case WM_RBUTTONDOWN:
				//con.Log(DEBUG_LEVEL_INFO, "WM_RBUTTONDOWN");
				break;
			case WM_RBUTTONUP:
				//con.Log(DEBUG_LEVEL_INFO, "WM_RBUTTONUP");
				break;
			case WM_MOUSEWHEEL:
				//con.Log(DEBUG_LEVEL_INFO, "WM_MOUSEWHEEL %i", GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
				break;
			case WM_TOUCH:
				{
					UINT cInputs = LOWORD(wParam);
					PTOUCHINPUT pInputs = new TOUCHINPUT[cInputs];
					if (NULL != pInputs)
					{
						if (GetTouchInputInfo((HTOUCHINPUT)lParam,
							cInputs, pInputs, sizeof(TOUCHINPUT)))
						{
							/*for(UINT i = 0; i < cInputs; i++)
							{
								con.Log(DEBUG_LEVEL_INFO, "[%i] %4i %4i ID %p TIME %p %p %p", i,
									pInputs[i].x, pInputs[i].y, pInputs[i].dwID,
									pInputs[i].dwTime, pInputs[i].cxContact, pInputs[i].cyContact);
								if (pInputs[i].dwFlags & TOUCHEVENTF_MOVE)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_MOVE");
								if (pInputs[i].dwFlags & TOUCHEVENTF_DOWN)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_DOWN");
								if (pInputs[i].dwFlags & TOUCHEVENTF_UP)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_UP");
								if (pInputs[i].dwFlags & TOUCHEVENTF_INRANGE)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_INRANGE");
								if (pInputs[i].dwFlags & TOUCHEVENTF_PRIMARY)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_PRIMARY");
								if (pInputs[i].dwFlags & TOUCHEVENTF_NOCOALESCE)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_NOCOALESCE");
								if (pInputs[i].dwFlags & TOUCHEVENTF_PALM)
									con.Log(DEBUG_LEVEL_INFO, "TOUCHEVENTF_PALM");
							}
							con.Log(DEBUG_LEVEL_INFO, "-----------------------------------------");
							*/
							if (!CloseTouchInputHandle((HTOUCHINPUT)lParam))
							{
								con.Log(DEBUG_LEVEL_ERROR, "CloseTouchInputHandle");
							}
						}
						else
						{
							con.Log(DEBUG_LEVEL_ERROR, "GetLastError() = %p", GetLastError());
						}
						delete [] pInputs;
					}
					else
					{
						// error handling, presumably out of memory
						con.Log(DEBUG_LEVEL_ERROR, "out of memory");
					}
				}
				break;
			}
			return DefWindowProc((HWND)GetHandle(), message, wParam, lParam);
		}
	}
}