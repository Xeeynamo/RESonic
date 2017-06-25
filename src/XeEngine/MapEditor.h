#pragma once
#include "Control.h"

class MAP;
namespace Editor
{
	class LevelMap;
	class ChunkSelector;
	class MapEditor : public Control
	{
	private:
		MAP *map;
		int selectedLayout;
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputChar(int character);
		virtual bool _InputMouse(short x, short y, int button);
	protected:
		LevelMap *levelMap;
		ChunkSelector *chunkSelector;
	public:
		MapEditor(MainEditor*);

		virtual void setFocus(bool);
		short getChunkSelected();
		void setChunkSelected(short chunk);
	};
}