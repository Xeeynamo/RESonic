#include "ChunkSelector.h"
#include "MainEditor.h"
#include "ContextMenu.h"

#define CHUNKSELECTED_COLOR1	0xFFFF8040
#define CHUNKSELECTED_COLOR2	0xFF4080FF

#define CHUNK_MENU_CUT		1
#define CHUNK_MENU_COPY		2
#define CHUNK_MENU_PASTE	3
#define CHUNK_MENU_DELETE	4
#define CHUNK_MENU_REMOVE	5

void eMenu(Editor::ContextMenu *menu, Editor::Control *parent, short index)
{
	switch(index)
	{
	case CHUNK_MENU_CUT:
		((Editor::ChunkSelector*)parent)->Cut();
		break;
	case CHUNK_MENU_COPY:
		((Editor::ChunkSelector*)parent)->Copy();
		break;
	case CHUNK_MENU_PASTE:
		((Editor::ChunkSelector*)parent)->Paste();
		break;
	case CHUNK_MENU_DELETE:
		((Editor::ChunkSelector*)parent)->Delete();
		break;
	case CHUNK_MENU_REMOVE:
		((Editor::ChunkSelector*)parent)->Remove();
		break;
	}
}

Editor::ChunkSelector::ChunkSelector(MainEditor *e, Control *parent, short x, short y, short width, short height) : Control(e, parent, x, y, width, height)
{
	m_name = "ChunkSelector";
	mouseX = mouseY = 0;
	chunkIndex = 0;
	chunkSelected = 0;
	chunkPrevMouse = -1;
	setSize(size);

	CtrlPosition pos;

	pos.x = 0;
	pos.y = 0;
	menu = new ContextMenu(e, this);
	menu->AddItem("CUT", CHUNK_MENU_CUT);
	menu->AddItem("COPY", CHUNK_MENU_COPY);
	menu->AddItem("PASTE", CHUNK_MENU_PASTE);
	menu->AddItem("DELETE", CHUNK_MENU_DELETE);
	menu->AddItem("REMOVE", CHUNK_MENU_REMOVE);
	menu->setPosition(pos);
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


void Editor::ChunkSelector::Cut()
{
	chunkPrevMouse = getChunkMouse();
}
void Editor::ChunkSelector::Copy()
{
	chunkPrevMouse = getChunkMouse();
}
void Editor::ChunkSelector::Paste()
{
	if (chunkPrevMouse == -1) return;
	memcpy(getLevel()->chunk[getChunkMouse()], getLevel()->chunk[chunkPrevMouse], sizeof(Block));
}
void Editor::ChunkSelector::Delete()
{
	memset(getLevel()->chunk[getChunkMouse()], 0, sizeof(Block));
}
void Editor::ChunkSelector::Remove()
{

}

void Editor::ChunkSelector::setSize(CtrlSize size)
{
	size.width &= ~0x7F;
	size.height &= ~0x7F;
	chunkWidth = size.width>>7;
	chunkHeight = size.height>>7;
	Control::setSize(size);
}

void Editor::ChunkSelector::_Draw()
{
	if (size.width < 0x80 || size.height < 0x80) return;
	XeEffect::SetProperties(1);
	XeEffect::SetClutDepth(1, CLUT_COUNT);

	for(int j=0; j<chunkHeight; j++)
	{
		for(int i=0; i<chunkWidth; i++)
		{
			DrawChunk(position.x + i*0x80, position.y + j*0x80, i + (j*chunkWidth) + chunkIndex);
		}
	}

	XeEffect::SetProperties(0);
	XeShape::SetColorArray(CHUNKSELECTED_COLOR1, CHUNKSELECTED_COLOR2, CHUNKSELECTED_COLOR2, CHUNKSELECTED_COLOR1);
	XeShape::DrawRect(position.x + ((chunkSelected-chunkIndex)%(size.width/128))*128, position.y + ((chunkSelected-chunkIndex)/(size.width/128))*128, 1.0f, 128, 128);
	XeEffect::SetProperties(1);

}
bool Editor::ChunkSelector::_InputKeyb(int key)
{
	setChunkIndex(getChunkIndex() - chunkWidth*getWheelY());

	switch(key)
	{
	case VK_PRIOR:
		setChunkIndex(getChunkIndex() - chunkWidth);
		return true;
	case VK_NEXT:
		setChunkIndex(getChunkIndex() + chunkWidth);
		return true;
	case VK_HOME:
		setChunkIndex(0);
		return true;
	case VK_END:
		setChunkIndex(chunkSelected);
		return true;
	}
	return false;
}
bool Editor::ChunkSelector::_InputMouse(short x, short y, int button)
{
	if (menu->InputMouse(x, y, button)) return true;

	mouseX = x;
	mouseY = y;
	switch(button)
	{
	case MK_LBUTTON:
		setChunkSelected(getChunkMouse());
		break;
	case MK_RBUTTON:
		menu->ShowMenu();
		break;
	}
	return true;
}