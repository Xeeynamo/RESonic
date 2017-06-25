#pragma once
#include "Geometry.h"

namespace XeEngine
{
	class Window
	{
	public:
		typedef Geometry2<int> Point;
		typedef Geometry2<int> Size;

		enum Style
		{
			Style_Sizable,
			Style_Fixed,
			Style_Unbordered,
		};
		enum Positioning
		{
			Positioning_Unmanaged,
			Positioning_Centered,
		};
		enum MessageBoxType
		{
			MessageBoxType_Standard	= 0,
			MessageBoxType_Info		= 1,
			MessageBoxType_Warning	= 2,
			MessageBoxType_Error	= 3,
		};
		enum MessageBoxButtons
		{
			MessageBoxButtons_Ok			= 0,
			MessageBoxButtons_OkCancel		= 1,
			MessageBoxButtons_YesNo			= 2,
			MessageBoxButtons_YesNoCancel	= 3,
		};
		enum MessageBoxReturn
		{
			MessageBoxReturn_Ok		= 0,
			MessageBoxReturn_Cancel	= 1,
			MessageBoxReturn_Yes	= 2,
			MessageBoxReturn_No		= 3,
		};
	public:
		Window()
		{
			m_initialized = false;
			m_positioning = Positioning_Unmanaged;
			OnPaint = nullptr;
			OnStyleChange = nullptr;
			OnShow = nullptr;
			OnCreate = nullptr;
			OnDestroy = nullptr;
			OnClose = nullptr;
			OnMove = nullptr;
			OnResize = nullptr;
			OnEnter = nullptr;
			OnLeave = nullptr;
			OnIconic = nullptr;
			OnRestore = nullptr;
		}
		virtual ~Window(){}

		virtual bool Initialize() = 0;
		virtual bool Do() = 0;
		virtual bool IsTouchCapable(){ return false; }
		virtual bool EnableTouch(bool){ return false; }

		// *** Aspect
		virtual void BackgroundColor(const unsigned int) = 0;
		virtual void SetTitle(const char*) = 0;
		virtual void SetStyle(const Style) = 0;
		virtual void Show(const bool) = 0;
		virtual void ShowIcon(const bool) = 0;
		virtual void ShowMaximize(const bool) = 0;
		virtual void ShowMinimize(const bool) = 0;
		virtual void AlwaysOnTop(const bool) = 0;

		// *** Layout
		virtual void GetLocation(Point&) const = 0;
		virtual void SetLocation(const Point&) = 0;
		virtual void GetSize(Size&) const = 0;
		virtual void SetSize(const Size&) = 0;
		virtual void SetMinimumSize(const Size&) = 0;
		virtual void SetMaximumSize(const Size&) = 0;
		virtual void SetPositioning(const Positioning&) = 0;

		// *** Commands
		virtual MessageBoxReturn ShowMessage(const MessageBoxType, const MessageBoxButtons, const char* text) = 0;
		virtual bool IsFocus() = 0;
		virtual void SetFocus() = 0;
		virtual bool IsIconic() = 0;
		virtual void SetIconic(bool) = 0;
		virtual bool IsMaximize() = 0;
		virtual void SetMaximize(bool) = 0;
		virtual void CenterToScreen() = 0;
		virtual void Close() = 0;
		virtual void Scale(float) = 0;
		virtual void* GetHandle() = 0;

		// *** Events
		void (*OnPaint)(Window&);
		void (*OnStyleChange)(Window&);	// ?
		void (*OnShow)(Window&);
		void (*OnCreate)(Window&);
		void (*OnDestroy)(Window&);
		bool (*OnClose)(Window&);
		void (*OnMove)(Window&);
		void (*OnResize)(Window&);
		void (*OnEnter)(Window&);
		void (*OnLeave)(Window&);
		void (*OnIconic)(Window&);		// ?
		void (*OnRestore)(Window&);		// ?
	protected:
		bool m_initialized;
		Point m_position;
		Size m_size;
		Positioning m_positioning;
		char* m_engine;
	};
}