#pragma once

#ifdef XEENGINE_WINDOW_GTK
#include "Window.h"
#include <gtk\gtk.h>

namespace XeEngine
{
	namespace WindowFramework
	{
		class GTK : public Window
		{
		public:
			GTK();
			~GTK();
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
			GtkWindow* m_window;
			bool m_loop;
			Size m_minSize;
			Size m_maxSize;

			void Initialize();

			static void GTK_Paint(GtkWidget*, GTK*);
			static void GTK_StyleChange(GtkWidget*, GTK*);
			static void GTK_Show(GtkWidget*, GTK*);
			static void GTK_Create(GtkWidget*, GTK*);
			static void GTK_Destroy(GtkWidget*, GTK*);
			static void GTK_Close(GtkWidget*, GTK*);
			static void GTK_Move(GtkWidget*, GTK*);
			static void GTK_Resize(GtkWidget*, GTK*);
			static void GTK_Enter(GtkWidget*, GTK*);
			static void GTK_Leave(GtkWidget*, GTK*);
			static void GTK_Iconic(GtkWidget*, GTK*);
			static void GTK_Restore(GtkWidget*, GTK*);
		};
	}
}
#endif