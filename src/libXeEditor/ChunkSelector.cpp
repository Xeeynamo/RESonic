#include "ChunkSelector.h"
#include "MainEditor.h"
#include "ContextMenu.h"

#define CHUNKSELECTED_COLOR1	0xFFFF8040
#define CHUNKSELECTED_COLOR2	0xFF4080FF

#define CHUNK_MENU_COPY		1
#define CHUNK_MENU_PASTE	2
#define CHUNK_MENU_DELETE	3

void eMenu(Editor::ContextMenu *menu, Editor::Control *parent, short index)
{
	switch(index)
	{
	case CHUNK_MENU_COPY:
		((Editor::ChunkSelector*)parent)->Copy();
		break;
	case CHUNK_MENU_PASTE:
		((Editor::ChunkSelector*)parent)->Paste();
		break;
	case CHUNK_MENU_DELETE:
		((Editor::ChunkSelector*)parent)->Delete();
		break;
	}
}

Editor::ChunkSelector::ChunkSelector(MainEditor *e, Control *parent, short x, short y, short width, short height) : Control(e, parent, Position(x, y), Size(width, height))
{
	m_name = "ChunkSelector";
	mouseX = mouseY = 0;
	chunkIndex = 0;
	chunkSelected = 0;
	chunkPrevMouse = -1;
	setSize(size);

	menu = new ContextMenu(e, this);
	menu->AddItem("Copy", CHUNK_MENU_COPY);
	menu->AddItem("Paste", CHUNK_MENU_PASTE);
	menu->AddItem("Delete", CHUNK_MENU_DELETE);
	menu->setPosition(Position(0, 0));
	menu->eMenuClick = eMenu;
	AddControl(menu);

	eChunkSelected = 0;
}

short Editor::ChunkSelector::getChunkIndex()
{
	return chunkIndex;
}
void Editor::ChunkSelector::setChunkIndex(short value)
{
	if (value < 0) value = 0;
	this->chunkIndex = value;
}
short Editor::ChunkSelector::getChunkSelected()
{
	return chunkSelected;
}
void Editor::ChunkSelector::setChunkSelected(short value)
{
	this->chunkSelected = value;
	if (eChunkSelected) eChunkSelected(this, parent, chunkSelected);
}
short Editor::ChunkSelector::getChunkMouse()
{
	return (mouseX>>7) + (mouseY>>7)*chunkWidth + chunkIndex;
}

void Editor::ChunkSelector::Copy()
{
	chunkPrevMouse = getChunkMouse();
}
void Editor::ChunkSelector::Paste()
{
	if (chunkPrevMouse == -1) return;
	memcpy(getLevel()->chunk[getChunkMouse()], getLevel()->chunk[chunkPrevMouse], sizeof(XeEngine::Chunk));
}
void Editor::ChunkSelector::Delete()
{
	memset(getLevel()->chunk[getChunkMouse()], 0, sizeof(XeEngine::Chunk));
}

void Editor::ChunkSelector::setSize(Size size)
{
	size.width &= ~0x7F;
	size.height &= ~0x7F;
	chunkWidth = size.width >> 7;
	chunkHeight = size.height >> 7;
	Control::setSize(size);
}

void Editor::ChunkSelector::_Draw()
{
	if (size.width < 0x80 || size.height < 0x80) return;

	for(int j=0; j<chunkHeight; j++)
	{
		for(int i=0; i<chunkWidth; i++)
		{
			DrawChunk(position.x + i*0x80, position.y + j*0x80, i + (j*chunkWidth) + chunkIndex);
		}
	}

	XeEngine::Shape::SetColorArray(e->GetLutEditor()[0x0F], e->GetLutEditor()[0x0E], e->GetLutEditor()[0x0D], e->GetLutEditor()[0x0C]);
	XeEngine::Shape::DrawRect(float(position.x + ((chunkSelected-chunkIndex)%(size.width/128))*128), float(position.y + ((chunkSelected-chunkIndex)/(size.width/128))*128), 1.0f, 128.0f, 128.0f);
}
bool Editor::ChunkSelector::_InputKeyb(int key)
{
	switch(key & 0xFFFF)
	{
	case VK_PRIOR:
		setChunkIndex(getChunkIndex() - chunkWidth);
		return true;
	case VK_NEXT:
		setChunkIndex(getChunkIndex() + chunkWidth);
		return true;
	case VK_END:
		setChunkIndex(chunkSelected);
		return true;
	case VK_HOME:
		setChunkIndex(0);
		return true;
	case 'C':
		Copy();
		break;
	case 'V':
		Paste();
		break;
	case VK_DELETE:
		Delete();
		break;
	case 0xE001:
		setChunkIndex(getChunkIndex() - chunkWidth * (key >> 16));
		break;
	case 0xE002:
		setChunkIndex(getChunkIndex() - (key >> 16));
		break;
	}
	return false;
}
bool Editor::ChunkSelector::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	if (menu->InputMouse(x, y, button))
		return true;

	mouseX = x;
	mouseY = y;
	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
		setChunkSelected(getChunkMouse());
		break;
	case XeEngine::MouseInput_RIGHT_UP:
		menu->ShowMenu();
		break;
	}
	return true;
}