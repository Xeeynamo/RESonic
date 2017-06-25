#include "Application.h"
#include "XInput.h"
#include "Window.h"
#include "Graphics.h"

// Video engines
#include "VideoNull.h"
#include "VideoD3D9.h"
#include "VideoGL21.h"

DebugConsole con;
namespace XeEngine
{
	void cbOnInitialize()
	{
		Application::Get()->OnInitialize();
	}
	void cbOnDestroy()
	{
		Application::Get()->OnDestroy();
	}
	void cbOnForeground()
	{
		Application::Get()->OnForeground();
	}
	void cbOnBackground()
	{
		Application::Get()->OnBackground();
	}
	void cbOnResize(short width, short height, float zoom)
	{
		Application::Get()->OnResize(width, height, zoom);
	}
	bool cbOnClose()
	{
		return Application::Get()->OnClose();
	}
}

XeEngine::Application*& XeEngine::Application::Get()
{
	static Application* application;
	return application;
}
XeEngine::Application::Application(const VideoEngine videoEngine)
{
	Get() = this;
	con.Log(DEBUG_LEVEL_INFO, "Application launched");

	AttachWindow(new Window());
	switch(videoEngine)
	{
	case VideoEngine_Null:		Video::CreateVideo(new VideoNull(*m_window));	break;
	case VideoEngine_Direct3D9:	Video::CreateVideo(new VideoD3D9(*m_window));	break;
	case VideoEngine_OpenGL21:	Video::CreateVideo(new VideoGL21(*m_window));	break;
	}

	Input::Set(new XInput(*m_window));
	input = XeEngine::Input::Get();

	Graphic::Initialize();
}
XeEngine::Application::~Application()
{
	SAFE_DELETE(m_window);
	//SAFE_DELETE(input);
	Video::DeleteVideo();
}

void XeEngine::Application::Run()
{
	GetWindow().SetFrameSize(640, 480);
	OnInitialize();
	do 
	{
		OnExecute();
	} while(GetWindow().Do());
	OnDestroy();
}

void XeEngine::Application::AttachWindow(Window* win)
{
	m_window = win;
	m_window->OnForeground = XeEngine::cbOnForeground;
	m_window->OnBackground = XeEngine::cbOnBackground;
	m_window->OnResize = XeEngine::cbOnResize;
	m_window->OnClose = XeEngine::cbOnClose;
	m_window->Create();
}

XeEngine::Window& XeEngine::Application::GetWindow() const
{
	return *m_window;
}
void XeEngine::Application::SetIconic(bool iconic)
{
	iconic == true ? OnBackground() : OnForeground();
}
void XeEngine::Application::SetSize(short w, short h, float zoom)
{
	OnResize(w, h, zoom);
}

void XeEngine::Application::OnInitialize()
{

}
void XeEngine::Application::OnDestroy()
{

}
void XeEngine::Application::OnForeground()
{

}
void XeEngine::Application::OnBackground()
{

}
void XeEngine::Application::OnResize(short, short, float)
{

}
bool XeEngine::Application::OnClose()
{
	return true;
}