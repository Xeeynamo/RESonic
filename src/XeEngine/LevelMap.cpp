#include "LevelMap.h"
#include "MainEditor.h"
#include "MAP.h"

#define LEVELMAP_SPEEDMIN	0x10
#define LEVELMAP_SPEEDMAX	0x20

Editor::LevelMap::LevelMap(MainEditor *e, Control *c) : Control(e, c)
{
	m_name = "Level map";
	map = NULL;
	mousedrag = false;
	m_selectedLayer = 0;
	keyX = keyY = 0;
	chunkX = chunkY = 0;
	mapposition.x = mapposition.y = 0;
	position.x = position.y = 0;
	size.width = size.height = 0x7FFF;
	// Only for debugging
	setEditorChunk(0);
	setEditorEnabled(false);
}

bool Editor::LevelMap::getEditorEnabled()
{
	return editor;
}
void Editor::LevelMap::setEditorEnabled(bool editor)
{
	this->editor = editor;
}
short Editor::LevelMap::getEditorChunk()
{
	return chunkSelected;
}
void Editor::LevelMap::setEditorChunk(short chunk)
{
	this->chunkSelected = chunk;
}
short Editor::LevelMap::getMouseChunk()
{
	return mapblock[(chunkX&1) + (chunkY&1)*2 + (chunkX/2*4) + (chunkY/2*4*mapwidth)];
}
void Editor::LevelMap::setMouseChunk(short chunk)
{
	LevelMapUndo a;
	LevelMapUndo *b;
	a.address = &mapblock[(chunkX&1) + (chunkY&1)*2 + (chunkX/2*4) + (chunkY/2*4*mapwidth)];
	a.chunk = *a.address;
	if (chunk == a.chunk) return;
	a.layer = getLayer();
	*a.address = chunk;

	b = undo.Peek();
	if (b != NULL)
	{
		if (b->address == a.address && b->layer == a.layer)
			return;
	}
	undo.Push(a);

}
MAP *Editor::LevelMap::getMap()
{
	return this->map;
}
void Editor::LevelMap::setMap(MAP *map)
{
	this->map = map;
}
byte Editor::LevelMap::getLayer()
{
	return m_selectedLayer;
}
void Editor::LevelMap::setLayer(char layer)
{
	if (!map) return;
	if (layer < 0) layer = map->properties.layerCount - 1;
	else if (layer >= map->properties.layerCount) layer = 0;
	layerProp = map->Layer(layer);
	if (!layerProp) return;
	m_selectedLayer = layer;

	mapwidth = map->Layer(m_selectedLayer)->width;
	mapheight = map->Layer(m_selectedLayer)->height;
	mapblock = map->GetLayer(m_selectedLayer);
}
Editor::CtrlPosition Editor::LevelMap::getMapPosition()
{
	return mapposition;
}
void Editor::LevelMap::setMapPosition(Editor::CtrlPosition pos)
{
	this->mapposition = pos;
}

void Editor::LevelMap::_Draw()
{
	if (!map) return;
	if (!layerProp)
	{
		setLayer(m_selectedLayer);
		if (!layerProp) return;
	}
	if (map->properties.layerCount == 0 || layerProp->width == 0 || layerProp->height == 0) return;
	mapposition.x += keyX;
	mapposition.y += keyY;
	XeEffect::SetClutDepth(1, CLUT_COUNT);
	getSize();
	DrawLevel(mapposition.x, mapposition.y, size.width, size.height, getLayer());

	if (editor)
	{
		XeEffect::SetFadeFactor(0.5);
		DrawChunk(mapposition.x + chunkX * 128, mapposition.y + chunkY * 128, chunkSelected);
		XeEffect::SetFadeFactor(1.0);
	}
}
bool Editor::LevelMap::_InputKeyb(int key, bool up)
{
	switch(key)
	{
	case VK_LEFT:
		if (up) keyX = 0;
		else if (keyX < LEVELMAP_SPEEDMAX) keyX += LEVELMAP_SPEEDMIN;
		return true;
	case VK_RIGHT:
		if (up) keyX = 0;
		else if (keyX > -LEVELMAP_SPEEDMAX)  keyX -= LEVELMAP_SPEEDMIN;
		return true;
	case VK_UP:
		if (up) keyY = 0;
		else if (keyY < LEVELMAP_SPEEDMAX)  keyY += LEVELMAP_SPEEDMIN;
		return true;
	case VK_DOWN:
		if (up) keyY = 0;
		else if (keyY > -LEVELMAP_SPEEDMAX) keyY -= LEVELMAP_SPEEDMIN;
		return true;
	case VK_HOME:
		mapposition.x = mapposition.y = 0;
		return true;
	case VK_END:
		mapposition.x = -(map->Layer(getLayer())->width * 256 - size.width);
		mapposition.y = -(map->Layer(getLayer())->height * 256 - size.height);
		return true;
	}
	return false;
}
bool Editor::LevelMap::_InputKeyb(int key)
{
	switch(key)
	{
	case 'G':
		if (isCtrlPressed())
		{
			setEditorChunk(getMouseChunk());
			return true;
		}
		break;
	case 'Z':
		if (isCtrlPressed())
		{
			LevelMapUndo a;
			if (undo.Pop(a))
			{
				if (a.layer != getLayer())
					undo.Push(a);
				*a.address = a.chunk;
			}
			return true;
		}
		break;
	}
	return false;
}
bool Editor::LevelMap::_InputMouse(short x, short y, int button)
{
	chunkX = (x - mapposition.x)/128;
	chunkY = (y - mapposition.y)/128;
	switch(button)
	{
	case 0:
		mousedrag = false;
		break;
	case MK_LBUTTON:
	{
		if (!editor) break;
		if (chunkX >= 0 && chunkY >= 0 && chunkX < mapwidth*2 && chunkY < mapheight*2)
		{
			setMouseChunk(getEditorChunk());
			return true;
		}
	}
	case MK_MBUTTON:
	{
		if (!editor) break;
		if (chunkX >= 0 && chunkY >= 0 && chunkX < mapwidth*2 && chunkY < mapheight*2)
		{
			setEditorChunk(getMouseChunk());
			return true;
		}
	}
	case MK_RBUTTON:
		if (mousedrag)
		{
			mapposition.x += (x - mousedragpos.x);
			mapposition.y += (y - mousedragpos.y);
		}
		else mousedrag = true;
		mousedragpos.x = x;
		mousedragpos.y = y;
		return true;
	}
	return true;
}

Editor::CtrlSize Editor::LevelMap::getSize()
{
	size.width = e->getEditorWidth();
	size.height = e->getEditorHeight();
	return size;
}