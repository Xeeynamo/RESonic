#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class Video;
	class Input;
	class Window;
	class EXPORT Application
	{
	private:
		//! \brief Attach a window to handle all the messages
		//! \details The referement to a Window
		//! \warning On destroying, the window will be deleted from Application automatically
		void AttachWindow(Window*);

		XeEngine::Window *m_window;
	protected:
		XeEngine::Video* video;
		XeEngine::Input* input;
	public:
		enum VideoEngine
		{
			VideoEngine_Null,
			VideoEngine_Direct3D9,
			VideoEngine_OpenGL21,
		};

		static Application*& Get();

		Application(const VideoEngine);
		virtual ~Application();

		//! \brief Call it to run the Application
		void Run();

		//! \brief Called when the Application is initialized
		virtual void OnInitialize();

		//! \brief Called when the Application is destroyed
		virtual void OnDestroy();

		//! \brief Called when the Application enters in foreground
		//! \details This happens for example when the Window is reduced as icon or the application was put in foreground
		virtual void OnForeground();

		//! \brief Called when the Application enters in background
		//! \details This happens for example when the Window is reduced as icon or the application was put in background
		virtual void OnBackground();

		//! \brief Called when the Application requires to change the view size 
		//! \details This happens only in a GUI system that works with windows
		//! \param Width
		//! \param Height
		//! \param Zoom of the Window
		virtual void OnResize(short, short, float = 1.0f) = 0;

		//! \brief Call it to run the Application
		virtual void OnExecute() = 0;

		//! \brief Called when the Application's window requires its close
		//! \details This happens for example when ALT+F4 or the red X is pressed; this can be used for confirmation messages or flushing
		//! \return Returns TRUE if the window will be closed, FALSE if the closing process is interrupted
		virtual bool OnClose() = 0;

		//! \brief Get the application's window
		Window& GetWindow() const;

		//! \brief Set the application in Foreground or Background
		void SetIconic(bool);

		//! \brief Change the view's size of the application 
		//! \param Width
		//! \param Height
		//! \param Zoom of the Window
		void SetSize(short, short, float = 1.0f);
	};
}