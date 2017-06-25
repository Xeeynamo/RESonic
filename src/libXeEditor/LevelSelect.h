#pragma once
#include "Control.h"

class XeEngine::Map;
namespace Editor
{
	class EXPORT LevelSelect : public Control
	{
	private:
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputChar(int character);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	protected:
		int m_level;
		int m_act;
	public:
		LevelSelect(MainEditor*);
	};
}