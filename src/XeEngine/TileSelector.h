#pragma once
#include "Control.h"

namespace Editor
{
	class TileSelector : Control
	{
	private:
	protected:
	public:
		TileSelector(MainEditor*, Control*);

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(short x, short y, short button);
		ushort GetTileSelected();
	};
}