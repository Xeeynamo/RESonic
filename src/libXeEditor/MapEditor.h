#pragma once
#include "Control.h"

class XeEngine::Map;
namespace Editor
{
	class LevelMap;
	class ChunkSelector;
	class EXPORT MapEditor : public Control
	{
	private:
		XeEngine::Map *map;
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputChar(int character);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
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