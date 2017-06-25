#pragma once
#include "MainEditor.h"

namespace Editor
{
	class EXPORT TextureEditor : public Control
	{
	private:
	protected:
		virtual void _Draw();
	public:
		TextureEditor(MainEditor*);
	};
}