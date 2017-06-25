#include "MapEditor.h"
#include "MainEditor.h"
#include "LevelMap.h"
#include "ChunkSelector.h"
#include "MAP.h"

#define E_MAPED_FILEINFO_X 0
#define E_MAPED_FILEINFO_Y 16

void eventChunkSelected(Editor::ChunkSelector *control, Editor::Control *parent, int value)
{
	((Editor::MapEditor*)parent)->setChunkSelected(
		((Editor::MapEditor*)parent)->getChunkSelected());
}

Editor::MapEditor::MapEditor(MainEditor *e) : Control(e)
{
	m_name = "Map editor";

	map = &getLevel()->map;
	levelMap = new LevelMap(e, this);
	levelMap->setMap(map);
	levelMap->setLayer(0);
	chunkSelector = new ChunkSelector(e, this, 0, 0, 0, 0);
	chunkSelector->setFadeOnLoseFocus(true);
	chunkSelector->Visible(levelMap->getEditorEnabled());
	chunkSelector->eChunkSelected = eventChunkSelected;

	selectedLayout = 0;

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
	CtrlPosition pos;
	CtrlSize size;
	size.width = (int)(MAX(1, getEditorWidth()>>7)/2.5f) << 7 ;
	size.height = getEditorHeight() + 127;
	pos.x = MAX(256, getEditorWidth() - size.width);
	pos.y = 0;
	chunkSelector->setPosition(pos);
	chunkSelector->setSize(size);

	PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y, "File: %s", getLevel()->MakePath(getLevel()->currentAct, STAGEFILE_MAP));
	PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+8, "Map position (%i, %i, %i, %i)", -map->properties.posx, -map->properties.posy, map->properties.width, map->properties.height);
	PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+16, "Layer selected: %i/%i", map->properties.layerCount > 0 ? levelMap->getLayer() + 1 : 0, map->properties.layerCount);
	if (map->properties.layerCount)
	{
		LayerProperties *p = map->Layer(levelMap->getLayer());
		if (p)
		{
			PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+32, "Size: %ix%i", p->width, p->height);
			PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+40, "Speed: %.3f x %.3f", float(p->speedX)/256.0f, float(p->speedY)/256.0f);
			PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+48, "Priority: %i", p->priority);
		}
		PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+64, "Map position: %04X %04X", (unsigned short)levelMap->getMapPosition().x, (unsigned short)levelMap->getMapPosition().y);
		if (levelMap->getEditorEnabled())
		{
			PrintText(E_MAPED_FILEINFO_X, E_MAPED_FILEINFO_Y+72, "Chunk: %04X on %04X", levelMap->getEditorChunk(), levelMap->getMouseChunk());
		}
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
		levelMap->setLayer(levelMap->getLayer()-1);
		return true;
	case '+': 
		levelMap->setLayer(levelMap->getLayer()+1);
		return true;
	}
	return false;
}
bool Editor::MapEditor::_InputMouse(short x, short y, int button)
{
	levelMap->Enable(!chunkSelector->getFocus());
	return false;
}