#pragma once
#include "Control.h"

namespace Editor
{
	class ChunkSelector;
	class MainEditor;
	class ChunkEditor : public Control
	{
	private:
		ChunkSelector *m_chunkSelector;
		int selectedChunk;

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(short x, short y, int button);
	protected:
	public:
		ChunkEditor(MainEditor*);
	};
}