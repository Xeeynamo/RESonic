#include "Window.h"

namespace Editor
{
	Window::Window(char* name, MainEditor* maineditor, Control* parent) : Control(maineditor, parent)
	{
		m_name = "Window";

		size = Size(320, 240);
	}
	Window::~Window()
	{

	}

	void _Draw()
	{
		
	}
}