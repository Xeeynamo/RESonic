#include "MapEditor.h"
#include "MainEditor.h"
#include "LevelMap.h"
#include "ChunkSelector.h"
#include "../libXeEngine/MAP.h"

#define E_MAPED_FILEINFO_X 0
#define E_MAPED_FILEINFO_Y 2

void eventChunkSelected(Editor::ChunkSelector *control, Editor::Control *parent, int value)
{
	((Editor::MapEditor*)parent)->setChunkSelected(
		((Editor::MapEditor*)parent)->getChunkSelected());
}

Editor::MapEditor::MapEditor(MainEditor *e) : Control(e)
{
	m_name = "Map editor";

	map = nullptr;
	map = getLevel()->map;
	levelMap = new LevelMap(e, this);
	chunkSelector = new ChunkSelector(e, this, 0, 0, 0, 0);
	chunkSelector->setFadeOnLoseFocus(true);
	chunkSelector->Visible(levelMap->getEditorEnabled());
	chunkSelector->eChunkSelected = eventChunkSelected;

	AddControl(chunkSelector);
	AddControl(levelMap);
}

void Editor::MapEditor::setFocus(bool focus)
{
	Editor::Control::setFocus(focus);
	SolidPalette(focus);
	e->RefreshPalette();
}
short Editor::MapEditor::getChunkSelected()
{
	return this->chunkSelector->getChunkSelected();
}
void Editor::MapEditor::setChunkSelected(short chunk)
{
	this->levelMap->setEditorChunk(chunk);
}

void Editor::MapEditor::_Draw()
{
	static const char* layer_name[4] =
	{
		"Foreground (primary)",
		"Background (primary)",
		"Foreground (secondary)",
		"Background (secondary)",
	};

	Position pos;
	Size size;
	size.width = (int)(MAX(1, getEditorWidth()>>7)/2.5f) << 7 ;
	size.height = getEditorHeight() + 127;
	pos.x = MAX(256, getEditorWidth() - size.width);
	pos.y = 0;
	chunkSelector->setPosition(pos);
	chunkSelector->setSize(size);

	XeEngine::Level* level = getLevel();

	XeEngine::String mapPath;
	XeEngine::MapRoom* mapRoom;
	level->BuildPath(mapPath, getLevel()->GetCurrentAct(), XeEngine::STAGEFILE_MAP);
	mapRoom = levelMap->GetMapRoom();

	PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 0, "File: %s", mapPath.ToChar());
	if (mapRoom != nullptr)
	{
		PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 1, "Map position (%u, %u, %u, %u)", mapRoom->x, mapRoom->y, mapRoom->width, mapRoom->height);
		PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 2, "Current layer type: %s", layer_name[levelMap->GetCurrentLayer()]);

		XeEngine::MapLayer* mapLayer = levelMap->GetMapLayer();
		if (mapLayer != nullptr)
		{
			PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 3, "Layer size: %ix%i", mapLayer->width, mapLayer->height);
			PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 5, "Camera: %04X %04X", (unsigned short)-levelMap->getMapPosition().x, (unsigned short)-levelMap->getMapPosition().y);
			if (levelMap->getEditorEnabled())
			{
				PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 6, "Chunk: %04X on %04X", levelMap->getEditorChunk(), levelMap->getMouseChunk());
			}
		}
		else
		{
			PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 3, "Invalid layer");
		}
	}
	else
	{
		PrintTextAligned(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y + 1, "No room loaded");
	}

}
bool Editor::MapEditor::_InputKeyb(int key)
{
	if (!isCtrlPressed()) return false;
	switch(key)
	{
	case 'E':
		levelMap->setEditorEnabled(levelMap->getEditorEnabled()^1);
		chunkSelector->Visible(levelMap->getEditorEnabled());
		return true;
	}
	return false;
}
bool Editor::MapEditor::_InputChar(int character)
{
	switch(character)
	{
	case '-':
		levelMap->SetCurrentLayer((levelMap->GetCurrentLayer() - 1) & 3);
		return true;
	case '+': 
		levelMap->SetCurrentLayer((levelMap->GetCurrentLayer() + 1) & 3);
		return true;
	}
	return false;
}
bool Editor::MapEditor::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	levelMap->Enable(!chunkSelector->getFocus());
	return false;
}