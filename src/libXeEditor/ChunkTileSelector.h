#pragma once
#include "Control.h"

namespace Editor
{
	class MainEditor;
	class ContextMenu;
	class EXPORT ChunkTileSelector : public Control
	{
	private:
		struct Selection
		{
			short chunkID;
			char left, right, top, bottom;
			Selection() : chunkID(0), left(0), right(0), top(0), bottom(0) {}
		};
		struct UndoStructure
		{
			u16 chunkID;
			u8 count;
			u8* pos;
			XeEngine::TileEntry* tentry;
			UndoStructure() : chunkID(0), count(0), pos(nullptr), tentry(nullptr){}
			UndoStructure& operator = (const UndoStructure& src)
			{
				chunkID = src.chunkID;
				count = src.count;
				pos = src.pos;
				tentry = src.tentry;
				return *this;
			}
		};
		//! \brief Handle the undo stack
		XeEngine::Stack<UndoStructure>* undo;
		//! \brief Handle the current coordinates of the mouse
		Position mousePosition;
		//! \brief Selected tile in chunkIndex
		u8 chunkTileSelected;
		//! \brief Holds the coordinates of selection 
		Selection selection;
		//! \brief Selection used for copy/paste
		Selection selectionCopy;
		//! \brief Holds a temporaney chunk where to see the data that will be copied
		XeEngine::Chunk chunkCopy;
		//! \brief Holds the previous input by the mouse
		//! \details That's used by the drag selection
		XeEngine::MouseInput prevMouseInput;

		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
		static void eMenu(Editor::ContextMenu *menu, Editor::Control *parent, short index);
		void Undo();
	protected:
		ContextMenu *menu;
		int value;

		void NormalizeSelection(Selection& out, Selection& in);
		virtual void _Draw();
	public:
		ChunkTileSelector(MainEditor *e, Control *parent, short x, short y);
		~ChunkTileSelector();

		short getChunkIndex();
		void setChunkIndex(short);
		u8 getTileSelected();
		void setTileSelected(u8);
		u8 getTileMouse();
		void WriteTileEntry(XeEngine::TileEntry);

		virtual void setSize(Size size);

		void Cut();
		void Copy();
		void Paste();
		void Delete();

		// Eventi
		void (*eChunkTileSelected)(ChunkTileSelector*, Control *parent, int value);
	public:
	};
}