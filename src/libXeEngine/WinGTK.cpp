#include "WinGTK.h"

#ifdef XEENGINE_WINDOW_GTK

#ifdef PLATFORM_WINDOWS
#include <gdk/gdkwin32.h>
#endif

#pragma comment(lib, "glib-2.0.lib")
#pragma comment(lib, "gdk-win32-2.0.lib")
#pragma comment(lib, "gtk-win32-2.0.lib")
#pragma comment(lib, "gio-2.0.lib")
#pragma comment(lib, "glib-2.0.lib")
#pragma comment(lib, "gmodule-2.0.lib")
#pragma comment(lib, "gobject-2.0.lib")
#pragma comment(lib, "gthread-2.0.lib")
#pragma comment(lib, "cairo.lib")
#pragma comment(lib, "gdk_pixbuf-2.0.lib")
#pragma comment(lib, "atk-1.0.lib")

namespace XeEngine
{
	namespace WindowFramework
	{
		GtkMessageType gtk_messagetype[] = {GTK_MESSAGE_INFO, GTK_MESSAGE_INFO, GTK_MESSAGE_WARNING, GTK_MESSAGE_ERROR};
		GtkButtonsType gtk_messagebutton[] = {GTK_BUTTONS_OK, GTK_BUTTONS_OK_CANCEL, GTK_BUTTONS_YES_NO, GTK_BUTTONS_YES_NO};

		GTK::GTK()
		{
			m_window = nullptr;
			m_minSize.Set(0, 0);
			m_maxSize.Set(65535, 65535);
		}
		GTK::~GTK()
		{
			Close();
			gtk_widget_destroy((GtkWidget*)m_window);
		}
		bool GTK::Do()
		{
			while(gdk_events_pending())
			{
				GdkEvent *ev = gdk_event_get();
				if (ev != nullptr)
				{
					gtk_main_do_event(ev);
				}
				gtk_main_iteration();
			}
			return m_loop;
		}

		// *** Aspect
		void GTK::BackgroundColor(const unsigned int color)
		{
			GdkColor gdkColor;
			gdkColor.pixel = 0;
			gdkColor.red = ((color >> 0) & 0xFF) << 8;
			gdkColor.green = ((color >> 8) & 0xFF) << 8;
			gdkColor.blue = ((color >> 16) & 0xFF) << 8;
			gtk_widget_modify_bg((GtkWidget*)m_window, GTK_STATE_NORMAL, &gdkColor);
		}
		void GTK::SetTitle(const char* text)
		{
			gtk_window_set_title(m_window, text);
		}
		void GTK::SetStyle(const Style style)
		{

		}
		void GTK::Show(const bool show)
		{
			if (show == true && m_initialized == false)
				Initialize();
			show ? gtk_widget_show((GtkWidget*)m_window) : gtk_widget_hide((GtkWidget*)m_window);
		}
		void GTK::ShowIcon(const bool show)
		{

		}
		void GTK::ShowMaximize(const bool show)
		{

		}
		void GTK::ShowMinimize(const bool show)
		{

		}
		void GTK::AlwaysOnTop(const bool top)
		{
			gtk_window_set_keep_above(m_window, top);
		}

		// *** Layout
		void GTK::GetLocation(Point& point) const
		{
			gint x, y;
			gtk_window_get_position(m_window, &x, &y);
			point.Set(x, y);
		}
		void GTK::SetLocation(const Point& point)
		{
			if (m_positioning == Positioning_Centered)
				CenterToScreen();
			else
				gtk_window_move(m_window, point.x, point.y);
		}
		void GTK::GetSize(Size& size) const
		{
			gint width, height;
			gtk_window_get_size(m_window, &width, &height);
			size.Set(width, height);
		}
		void GTK::SetSize(const Size& size)
		{
			Size sizeToSet;

			if (size.x > m_maxSize.x) sizeToSet.x = m_maxSize.x;
			else if (size.x < m_minSize.x) sizeToSet.x = m_minSize.x;
			else sizeToSet.x = size.x;

			if (size.y > m_maxSize.y) sizeToSet.y = m_maxSize.y;
			else if (size.y < m_minSize.y) sizeToSet.y = m_minSize.y;
			else sizeToSet.y = size.y;

			gtk_window_resize(m_window, sizeToSet.x, sizeToSet.y);
			if (m_positioning == Positioning_Centered)
				CenterToScreen();
		}
		void GTK::SetMinimumSize(const Size& size)
		{
			Size currentSize;
			m_minSize = size;
			GetSize(currentSize);
			SetSize(currentSize);
		}
		void GTK::SetMaximumSize(const Size& size)
		{
			Size currentSize;
			m_maxSize = size;
			GetSize(currentSize);
			SetSize(currentSize);
		}
		void GTK::SetPositioning(const Positioning& positioning)
		{
			m_positioning = positioning;
			switch(m_positioning)
			{
			case Positioning_Centered:
				CenterToScreen();
				break;
			}
		}

		// *** Commands
		Window::MessageBoxReturn GTK::ShowMessage(const MessageBoxType type, const MessageBoxButtons button, const char* text)
		{
			GtkWidget* msgbox = gtk_message_dialog_new(m_window, GTK_DIALOG_MODAL, gtk_messagetype[type], gtk_messagebutton[button], text);
			gint result = gtk_dialog_run((GtkDialog*)msgbox);
			gtk_widget_destroy((GtkWidget*)msgbox);
			switch(result)
			{
			case GTK_RESPONSE_OK:
				return MessageBoxReturn_Ok;
			case GTK_RESPONSE_CANCEL:
				return MessageBoxReturn_Cancel;
			case GTK_RESPONSE_YES:
				return MessageBoxReturn_Yes;
			case GTK_RESPONSE_NO:
				return MessageBoxReturn_No;
			}
			return MessageBoxReturn_Ok;
		}
		bool GTK::IsFocus()
		{
			return gtk_widget_is_toplevel((GtkWidget*)m_window) != 0;
		}
		void GTK::SetFocus()
		{
			gtk_window_activate_focus(m_window);
		}
		bool GTK::IsIconic()
		{
			return false;
		}
		void GTK::SetIconic(bool iconic)
		{
			iconic ? gtk_window_iconify(m_window) : gtk_window_deiconify(m_window);
		}
		bool GTK::IsMaximize()
		{
			return false;
		}
		void GTK::SetMaximize(bool maximize)
		{
			maximize ? gtk_window_maximize(m_window) : gtk_window_unmaximize(m_window);
		}
		void GTK::CenterToScreen()
		{
			gtk_window_set_position(m_window, GTK_WIN_POS_CENTER);
			gtk_window_set_position(m_window, GTK_WIN_POS_CENTER_ALWAYS);
		}
		void GTK::Close()
		{
			gtk_main_quit();
			m_loop = false;
			GTK_Destroy(nullptr, this);
		}
		void GTK::Scale(float scale)
		{

		}
		void* GTK::GetHandle()
		{
#ifdef PLATFORM_WINDOWS
			return gdk_win32_window_get_impl_hwnd(gtk_widget_get_window(GTK_WIDGET(m_window)));
#else
			return nullptr;
#endif
		}

		void GTK::Initialize()
		{
			gtk_init (0, 0);
			m_window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
			g_signal_connect(m_window, "set-focus", G_CALLBACK(GTK_Enter), this);
			g_signal_connect(m_window, "destroy", G_CALLBACK(GTK_Close), this);

			m_initialized = true;
			m_loop = true;
		}


		void GTK::GTK_Paint(GtkWidget*, GTK* window)
		{
			if (window->OnPaint != nullptr)
				window->OnPaint(*window);
		}
		void GTK::GTK_StyleChange(GtkWidget*, GTK* window)
		{
			if (window->OnStyleChange != nullptr)
				window->OnStyleChange(*window);
		}
		void GTK::GTK_Show(GtkWidget*, GTK* window)
		{
			if (window->OnShow != nullptr)
				window->OnShow(*window);
		}
		void GTK::GTK_Create(GtkWidget*, GTK* window)
		{
			if (window->OnCreate != nullptr)
				window->OnCreate(*window);
		}
		void GTK::GTK_Destroy(GtkWidget*, GTK* window)
		{
			if (window->OnDestroy != nullptr)
				window->OnDestroy(*window);
		}
		void GTK::GTK_Close(GtkWidget*, GTK* window)
		{
			bool closeAccepted = true;
			if (window->OnClose != nullptr)
				closeAccepted = window->OnClose(*window);
			if (closeAccepted == true)
			{
				window->Close();
			}
		}
		void GTK::GTK_Move(GtkWidget*, GTK* window)
		{
			if (window->OnMove != nullptr)
				window->OnMove(*window);
		}
		void GTK::GTK_Resize(GtkWidget*, GTK* window)
		{
			if (window->OnResize != nullptr)
				window->OnResize(*window);
		}
		void GTK::GTK_Enter(GtkWidget*, GTK* window)
		{
			if (window->OnEnter != nullptr)
				window->OnEnter(*window);
		}
		void GTK::GTK_Leave(GtkWidget*, GTK* window)
		{
			if (window->OnLeave != nullptr)
				window->OnLeave(*window);
		}
		void GTK::GTK_Iconic(GtkWidget*, GTK* window)
		{
			if (window->OnIconic != nullptr)
				window->OnIconic(*window);
		}
		void GTK::GTK_Restore(GtkWidget*, GTK* window)
		{
			if (window->OnRestore != nullptr)
				window->OnRestore(*window);
		}
	}
}

#endif