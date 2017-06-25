#pragma once
#include "XeControl.h"
#include "Control.h"

namespace Editor
{
	class Window : public Control
	{
	public:
		Window(char* name, MainEditor*, Control*);
		~Window();

		void _Draw();
	};
}