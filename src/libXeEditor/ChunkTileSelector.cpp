#include "ChunkTileSelector.h"
#include "MainEditor.h"
#include "ContextMenu.h"

#define CHUNKSELECTED_COLOR1	0xFFFF8040
#define CHUNKSELECTED_COLOR2	0xFF4080FF

#define CHUNKTILE_MENU_CUT		1
#define CHUNKTILE_MENU_COPY		2
#define CHUNKTILE_MENU_PASTE	3
#define CHUNKTILE_MENU_DELETE	4

void Editor::ChunkTileSelector::eMenu(Editor::ContextMenu *menu, Editor::Control *parent, short index)
{
	switch(index)
	{
	case CHUNKTILE_MENU_CUT:
		((Editor::ChunkTileSelector*)parent)->Cut();
		break;
	case CHUNKTILE_MENU_COPY:
		((Editor::ChunkTileSelector*)parent)->Copy();
		break;
	case CHUNKTILE_MENU_PASTE:
		((Editor::ChunkTileSelector*)parent)->Paste();
		break;
	case CHUNKTILE_MENU_DELETE:
		((Editor::ChunkTileSelector*)parent)->Delete();
		break;
	}
}

Editor::ChunkTileSelector::ChunkTileSelector(MainEditor *e, Control *parent, short x, short y) : Control(e, parent, Position(x, y), Size(XeEngine::chunkSizeAbsolute, XeEngine::chunkSizeAbsolute))
{
	m_name = "ChunkTileSelector";
	undo = new XeEngine::Stack<UndoStructure>(64);
	chunkTileSelected = 0;
	eChunkTileSelected = nullptr;
	setSize(size);

	menu = new ContextMenu(e, this);
	menu->AddItem("Cut", CHUNKTILE_MENU_CUT);
	menu->AddItem("Copy", CHUNKTILE_MENU_COPY);
	menu->AddItem("Paste", CHUNKTILE_MENU_PASTE);
	menu->AddItem("Delete", CHUNKTILE_MENU_DELETE);
	menu->setPosition(Position(0, 0));
	menu->eMenuClick = eMenu;
	AddControl(menu);
}
Editor::ChunkTileSelector::~ChunkTileSelector()
{
	delete undo;
}

short Editor::ChunkTileSelector::getChunkIndex()
{
	return selection.chunkID;
}
void Editor::ChunkTileSelector::setChunkIndex(short value)
{
	if (value < 0) value = 0;
	selection.chunkID = value;
}
u8 Editor::ChunkTileSelector::getTileSelected()
{
	return chunkTileSelected;
}
void Editor::ChunkTileSelector::setTileSelected(u8 value)
{
	this->chunkTileSelected = value;
	if (eChunkTileSelected) eChunkTileSelected(this, parent, chunkTileSelected);
}
u8 Editor::ChunkTileSelector::getTileMouse()
{
	return mousePosition.x + (mousePosition.y * XeEngine::chunkSize);
}
void Editor::ChunkTileSelector::WriteTileEntry(XeEngine::TileEntry TileEntry)
{
	XeEngine::TileEntry* tentry = &getLevel()->chunk[getChunkIndex()][getTileSelected()];
	if (tentry->ToInt == TileEntry.ToInt)
		return;

	UndoStructure undoStructure;
	undoStructure.chunkID = getChunkIndex();
	undoStructure.count = 1;
	undoStructure.pos = new u8[undoStructure.count];
	undoStructure.tentry = new XeEngine::TileEntry[undoStructure.count];
	undoStructure.pos[0] = getTileSelected();
	undoStructure.tentry[0] = *tentry;
	undo->Push(undoStructure);
	
	*tentry = TileEntry;
}

void Editor::ChunkTileSelector::Cut()
{
	Copy();
	Delete();
}
void Editor::ChunkTileSelector::Copy()
{
	XeEngine::MemoryCopy(chunkCopy, getLevel()->chunk[getChunkIndex()], sizeof(XeEngine::Chunk));
	NormalizeSelection(selectionCopy, selection);
}
void Editor::ChunkTileSelector::Paste()
{
	XeEngine::TileEntry* tentry = getLevel()->chunk[getChunkIndex()];
	UndoStructure undoStructure;
	undoStructure.chunkID = getChunkIndex();
	undoStructure.count = XeEngine::chunkSize * XeEngine::chunkSize;
	undoStructure.pos = new u8[undoStructure.count];
	undoStructure.tentry = new XeEngine::TileEntry[undoStructure.count];
	for(int i=0; i<undoStructure.count; i++)
	{
		undoStructure.pos[i] = i;
		undoStructure.tentry[i] = tentry[i];
	}
	undo->Push(undoStructure);

	Selection selectionPaste, selectionSource;
	NormalizeSelection(selectionPaste, selection);
	selectionSource = selectionCopy;

	if (selectionPaste.left + (selectionSource.right - selectionSource.left) >= 8)
	{
		selectionSource.right -= (selectionPaste.left + (selectionSource.right - selectionSource.left) - 7);
	}
	if (selectionPaste.top + (selectionSource.bottom - selectionSource.top) >= 8)
	{
		selectionSource.bottom -= (selectionPaste.top + (selectionSource.bottom - selectionSource.top) - 7);
	}

	for(int i = selectionSource.bottom - selectionSource.top; i >= 0; i--)
	{
		for(int j = selectionSource.right - selectionSource.left; j >= 0; j--)
		{
			tentry[selectionPaste.left + j + (selectionPaste.top + i) * XeEngine::chunkSize] =
				chunkCopy[selectionSource.left + j + (selectionSource.top + i) * XeEngine::chunkSize];
		}
	}
}
void Editor::ChunkTileSelector::Delete()
{
	XeEngine::TileEntry* tentry = getLevel()->chunk[getChunkIndex()];
	UndoStructure undoStructure;
	undoStructure.chunkID = getChunkIndex();
	undoStructure.count = XeEngine::chunkSize * XeEngine::chunkSize;
	undoStructure.pos = new u8[undoStructure.count];
	undoStructure.tentry = new XeEngine::TileEntry[undoStructure.count];
	for(int i=0; i<undoStructure.count; i++)
	{
		undoStructure.pos[i] = i;
		undoStructure.tentry[i] = tentry[i];
	}
	undo->Push(undoStructure);

	Selection selectionDelete;
	NormalizeSelection(selectionDelete, selection);
	for(int i = selectionDelete.bottom - selectionDelete.top; i >= 0; i--)
	{
		for(int j = selectionDelete.right - selectionDelete.left; j >= 0; j--)
		{
			tentry[selectionDelete.left + j + (selectionDelete.top + i) * XeEngine::chunkSize].ToInt = 0;
		}
	}
}

void Editor::ChunkTileSelector::setSize(Size size)
{
	size.width &= ~0x7F;
	size.height &= ~0x7F;
	Control::setSize(size);
}
void Editor::ChunkTileSelector::Undo()
{
	if (undo->isEmpty())
		return;

	UndoStructure* undoStructure;
	undo->Peek(undoStructure);
	if (getChunkIndex() != undoStructure->chunkID)
	{
		setChunkIndex(undoStructure->chunkID);
		return;
	}
	for(int i=0; i<undoStructure->count; i++)
	{
		getLevel()->chunk[getChunkIndex()][undoStructure->pos[i]] = undoStructure->tentry[i];
	}
	SAFE_ADELETE(undoStructure->pos);
	SAFE_ADELETE(undoStructure->tentry);
	undo->Pop();
}
void Editor::ChunkTileSelector::NormalizeSelection(Selection& out, Selection& in)
{
	out = in;
	if (out.left > out.right)
	{
		out.left = in.right;
		out.right = in.left;
	}
	if (out.top > out.bottom)
	{
		out.top = in.bottom;
		out.bottom = in.top;
	}
}

void Editor::ChunkTileSelector::_Draw()
{
	if (size.width < 0x80 || size.height < 0x80) return;
	DrawChunk(position.x, position.y, getChunkIndex());

	Selection selectionNormalized = selection;
	NormalizeSelection(selectionNormalized, selection);

	XeEngine::Shape::SetColorArray(e->GetLutEditor()[0x0F], e->GetLutEditor()[0x0E], e->GetLutEditor()[0x0D], e->GetLutEditor()[0x0C]);
	XeEngine::Shape::DrawRect(float(position.x + selectionNormalized.left * XeEngine::tileSize), float(position.y + selectionNormalized.top * XeEngine::tileSize), 1.0f,
		float((selectionNormalized.right - selectionNormalized.left + 1) * XeEngine::tileSize), float((selectionNormalized.bottom - selectionNormalized.top + 1) * XeEngine::tileSize));
}
bool Editor::ChunkTileSelector::_InputKeyb(int key)
{
	switch(key & 0xFFFF)
	{
	case 'Z':
		if (isCtrlPressed())
		{
			Undo();
			return true;
		}
		return false;
	case 'X':
		if (isCtrlPressed())
		{
			Cut();
			return true;
		}
	case 'C':
		if (isCtrlPressed())
		{
			Copy();
			return true;
		}
		return false;
	case 'V':
		if (isCtrlPressed())
		{
			Paste();
			return true;
		}
		return false;
	case VK_DELETE:
		Delete();
		break;
	}
	return false;
}
#include <stdio.h>
bool Editor::ChunkTileSelector::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	if (menu->InputMouse(x, y, button))
		return true;

	mousePosition.x = x / XeEngine::tileSize;
	mousePosition.y = y / XeEngine::tileSize;

	if (prevMouseInput == XeEngine::MouseInput_LEFT)
	{
		if (button == XeEngine::MouseInput_LEFT)
		{
			selection.right = (char)mousePosition.x;
			selection.bottom = (char)mousePosition.y;
		}
		else if (button == XeEngine::MouseInput_LEFT_UP)
		{
			prevMouseInput = XeEngine::MouseInput_NOTHING;
		}
		return true;
	}
	prevMouseInput = button;

	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
		selection.left = selection.right = (char)mousePosition.x;
		selection.top = selection.bottom = (char)mousePosition.y;
		setTileSelected(getTileMouse());
		break;
	case XeEngine::MouseInput_RIGHT_UP:
		setTileSelected(getTileMouse());
		selection.left = selection.right = (char)mousePosition.x;
		selection.top = selection.bottom = (char)mousePosition.y;
		menu->ShowMenu();
		break;
	}
	return true;
}