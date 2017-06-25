#pragma once
#include "Window.h"
#include <windows.h>

namespace XeEngine
{
	namespace WindowFramework
	{
		class WinAPI : public Window
		{
		friend LRESULT __stdcall WinAPI_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		public:
			WinAPI();
			~WinAPI();

			bool Initialize();
			bool Do();
			bool IsTouchCapable();
			bool EnableTouch(bool asd);

			// *** Aspect
			void BackgroundColor(const unsigned int);
			void SetTitle(const char*);
			void SetStyle(const Style);
			void Show(const bool);
			void ShowIcon(const bool);
			void ShowMaximize(const bool);
			void ShowMinimize(const bool);
			void AlwaysOnTop(const bool);

			// *** Layout
			void GetLocation(Point&) const;
			void SetLocation(const Point&);
			void GetSize(Size&) const;
			void SetSize(const Size&);
			void SetMinimumSize(const Size&);
			void SetMaximumSize(const Size&);
			void SetPositioning(const Positioning&);

			// *** Commands
			MessageBoxReturn ShowMessage(const MessageBoxType, const MessageBoxButtons, const char* text);
			bool IsFocus();
			void SetFocus();
			bool IsIconic();
			void SetIconic(bool);
			bool IsMaximize();
			void SetMaximize(bool);
			void CenterToScreen();
			void Close();
			void Scale(float);
			void* GetHandle();
		public:
			HWND m_hwnd;
			HBRUSH m_backgroundcolor;
			Size m_minSize;
			Size m_maxSize;

			DWORD GetStyle(bool fullscreen);
			LRESULT __stdcall WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
		};
	}
}