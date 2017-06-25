#include "WinNull.h"

namespace XeEngine
{
	namespace WindowFramework
	{
		WinNull::WinNull()
		{

		}
		WinNull::~WinNull()
		{
			Close();
		}
		bool WinNull::Do()
		{
			return false;
		}

		// *** Aspect
		void WinNull::BackgroundColor(const unsigned int color)
		{

		}
		void WinNull::SetTitle(const char* text)
		{

		}
		void WinNull::SetStyle(const Style style)
		{

		}
		void WinNull::Show(const bool show)
		{
			if (show == true && m_initialized == false)
				Initialize();
		}
		void WinNull::ShowIcon(const bool show)
		{

		}
		void WinNull::ShowMaximize(const bool show)
		{

		}
		void WinNull::ShowMinimize(const bool show)
		{

		}
		void WinNull::AlwaysOnTop(const bool top)
		{

		}

		// *** Layout
		void WinNull::GetLocation(Point& point) const
		{

		}
		void WinNull::SetLocation(const Point& point)
		{

		}
		void WinNull::GetSize(Size& size) const
		{

		}
		void WinNull::SetSize(const Size& size)
		{

		}
		void WinNull::SetMinimumSize(const Size& size)
		{

		}
		void WinNull::SetMaximumSize(const Size& size)
		{

		}
		void WinNull::SetPositioning(const Positioning& positioning)
		{

		}

		// *** Commands
		Window::MessageBoxReturn WinNull::ShowMessage(const MessageBoxType, const MessageBoxButtons, const char* text)
		{
			return MessageBoxReturn_Ok;
		}
		bool WinNull::IsFocus()
		{
			return false;
		}
		void WinNull::SetFocus()
		{

		}
		bool WinNull::IsIconic()
		{
			return false;
		}
		void WinNull::SetIconic(bool iconic)
		{

		}
		bool WinNull::IsMaximize()
		{
			return false;
		}
		void WinNull::SetMaximize(bool maximize)
		{

		}
		void WinNull::CenterToScreen()
		{

		}
		void WinNull::Close()
		{

		}
		void WinNull::Scale(float scale)
		{

		}
		void* WinNull::GetHandle()
		{
			return nullptr;
		}

		bool WinNull::Initialize()
		{
			m_initialized = true;
			return m_initialized;
		}
	}
}