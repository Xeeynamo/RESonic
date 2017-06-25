#pragma once
#include "Window.h"

namespace XeEngine
{
	namespace WindowFramework
	{
		class WinNull : Window
		{
		public:
			WinNull();
			~WinNull();
			bool Do();

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
		private:
			bool Initialize();
		};
	}
}