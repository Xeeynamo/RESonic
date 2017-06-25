#include "App.h"
#include "RESonic1.h"
#include "..\libXeEngine\VideoGL21.h"
#include "..\libXeEngine\XInput.h"
#include "..\libXeEngine\Window.h"
#include "..\libXeEngine\Shape.h"
#include "..\libXeEngine\Graphic.h"
#include <stdio.h>

RESonic1App::RESonic1App() : Application(VideoEngine_OpenGL21)
{
	s1 = nullptr;
	editor = nullptr;

	s1 = new RESonic1;
	editor = new Editor::MainEditor(s1);
}
RESonic1App::~RESonic1App()
{
	SAFE_DELETE(editor);
	SAFE_DELETE(s1);
}

void RESonic1App::OnExecute()
{
	input->Update();
	XeEngine::Video::PaintBegin();
	XeEngine::Video::Clear();

	if (editor->Run() == false)
	{
		s1->Run();
	}

	XeEngine::Video::PaintEnd();
}
void RESonic1App::OnInitialize()
{
	// Initialize the Window
	GetWindow().SetTitle("RE: Sonic the Hedgehog");
	GetWindow().SetFrameSize(800, 480);
	GetWindow().ShowWindowCursor(true);
	GetWindow().Show(true);
	// Initialize the Video
	XeEngine::Video::SetClearColor(1.0f / 24.0f, 1.0f / 32.0f, 1.0f / 32.0f, 1.0f); // 0x202018
	// Initialize the game
	s1->Initialize();
	// Initialize the editor
	editor->Initialize();
	// Initialize the shapes
	XeEngine::Shape::Initialize();
}
void RESonic1App::OnDestroy()
{
	return;
}
void RESonic1App::OnBackground()
{

}
void RESonic1App::OnForeground()
{

}
void RESonic1App::OnResize(short width, short height, float zoom)
{
	this->appWidth = width;
	this->appHeight = height;
	XeEngine::Video::Resize(width, height);
	editor->SetRenderSize(width, height);
}
bool RESonic1App::OnClose()
{
	return true;
}