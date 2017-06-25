#pragma once
#include "MainEditor.h"

namespace Editor
{
	class EXPORT HitboxShape : public Control
	{
	private:
		u8 m_index;
		u8 m_verse;
	protected:
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	public:
		HitboxShape(MainEditor*, Control*, short x, short y, short size);
		// Funzioni proprie
		u8 GetIndex() const;
		void SetIndex(u8);
		u8 GetVerse() const;
		void SetVerse(u8);
		// Funzioni derivate
		virtual void setSize(Size size);
	};
}