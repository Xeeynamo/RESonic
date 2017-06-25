#pragma once
#include "Control.h"

class XeEngine::Map;
namespace Editor
{
	class HitboxShape;
	class EXPORT HitboxEditor : public Control
	{
	private:
		HitboxShape* hitboxShape;

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputChar(int character);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	protected:
		XeEngine::Point posCollisionTexture;
	public:
		HitboxEditor(MainEditor*);
	};
}