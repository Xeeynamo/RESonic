#pragma once
#include "MainEditor.h"

namespace Editor
{
	class TextureEditor : public Control
	{
	private:
	protected:
		virtual void _Draw();
	public:
		TextureEditor(MainEditor*);
	};
}