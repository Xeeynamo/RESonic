#pragma once
#include "Control.h"

namespace Editor
{
	class MainEditor;
	class ContextMenu;
	class ChunkSelector : public Control
	{
	private:
		short mouseX, mouseY;
		short chunkIndex;
		short chunkSelected;
		short chunkPrevMouse;
		char chunkWidth, chunkHeight;

		virtual bool _InputMouse(short x, short y, int button);
	protected:
		ContextMenu *menu;
		int value;

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
	public:
		ChunkSelector(MainEditor *e, Control *parent, short x, short y, short width, short height);

		short  getChunkIndex();
		void setChunkIndex(short);
		short  getChunkSelected();
		void setChunkSelected(short);
		short getChunkMouse();

		virtual void setSize(CtrlSize size);

		void Cut();
		void Copy();
		void Paste();
		void Delete();
		void Remove();

		// Eventi
		void (*eChunkSelected)(ChunkSelector*, Control *parent, int value);
	public:
	};
}