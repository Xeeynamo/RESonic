#include "LevelMap.h"
#include "MainEditor.h"
#include "../libXeEngine/MAP.h"
#include "../libXeEngine/Graphic.h"

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
	XeEngine::MapLayer* mapLayer = GetMapLayer();
	if (mapLayer == nullptr) return 0;
	return getLevel()->layout[m_selectedLayer][chunkX + chunkY * mapLayer->width * 2];
}
void Editor::LevelMap::setMouseChunk(short chunk)
{
	XeEngine::MapLayer* layer = GetMapLayer();
	XeEngine::ChunkAlloc* chunkLayout = getLevel()->layout[m_selectedLayer];
	chunkLayout = &chunkLayout[chunkX + chunkY * layer->width * 2];

	if (*chunkLayout != chunk)
	{
		LevelMapUndo levelMapUndo;
		levelMapUndo.x = chunkX;
		levelMapUndo.y = chunkY;
		levelMapUndo.chunk = *chunkLayout;
		levelMapUndo.layer = m_selectedLayer;
		levelMapUndo.room = getLevel()->m_room;

		*chunkLayout = chunk;
		undo.Push(levelMapUndo);
	}
}
Editor::Position Editor::LevelMap::getMapPosition()
{
	return mapposition;
}

void Editor::LevelMap::_Draw()
{
	XeEngine::MapLayer* mapLayer = GetMapLayer();
	if (mapLayer == nullptr) return;
	mapposition.x += keyX;
	mapposition.y += keyY;
	getSize();

	XeEngine::Shape::SetColorArray(e->GetLutEditor()[0x0F], e->GetLutEditor()[0x0E], e->GetLutEditor()[0x0D], e->GetLutEditor()[0x0C]);
	XeEngine::Shape::DrawRect(mapposition.x, mapposition.y, 0.0f, (float)(mapLayer->width * 256), (float)(mapLayer->height * 256));

	short eWidth = getEditorWidth();
	short eHeight = getEditorHeight();
	short layerx = MAX(0, -mapposition.x);
	short layery = MAX(0, -mapposition.y);
	short layerw = MIN(eWidth / 16 + 1, mapLayer->width * 16);
	short layerh = MIN(eHeight / 16 + 1, mapLayer->height * 16);
	if (layerx + layerw * 16 > mapLayer->width * 256)
	{
		layerw = layerw + (mapLayer->width * 256 - (layerx + layerw * 16)) / 16;
	}
	if (layery + layerh * 16 > mapLayer->height * 256)
	{
		layerh = layerh + (mapLayer->height * 256 - (-mapposition.y + layerh * 16)) / 16;
	}

	if (layerw >= 0 && layerh >= 0)
	{
		getLevel()->DrawLayer(MIN(0, -mapposition.x), MIN(0, -mapposition.y), layerx, layery, layerw, layerh, m_selectedLayer);
	}

	if (editor)
	{
		//video->SetClutDepth(0, XeEngine::clutCount);
		//video->SetFadeFactor(0.5f);
		DrawChunk(mapposition.x + chunkX * 128, mapposition.y + chunkY * 128, chunkSelected);
		//video->SetFadeFactor(1.0f);
	}
	//video->SetClutDepth(3, XeEngine::clutCount);
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
		{
			XeEngine::MapLayer* mapLayer = GetMapLayer();
			if (mapLayer != nullptr)
			{
				mapposition.x = -(mapLayer->width * 256 - size.width);
				mapposition.y = -(mapLayer->height * 256 - size.height);
			}
		}
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
			LevelMapUndo *levelMapUndo = nullptr;
			undo.Peek(levelMapUndo);
			if (levelMapUndo != nullptr)
			{
				if (levelMapUndo->layer != m_selectedLayer)
				{
					SetCurrentLayer(levelMapUndo->layer);
				}
				else
				{
					XeEngine::MapLayer* layer = GetMapLayer();
					if ((-mapposition.x > levelMapUndo->x * 128) || (-mapposition.x + getEditorWidth() < levelMapUndo->x * 128) ||
						(-mapposition.y > levelMapUndo->y * 128) || (-mapposition.y + getEditorHeight() < levelMapUndo->y * 128))
					{
						mapposition.x = - (levelMapUndo->x * 128 - getEditorWidth() / 2);
						mapposition.y = - (levelMapUndo->y * 128 - getEditorHeight() / 2);
					}
					else
					{
						undo.Pop();
						getLevel()->layout[m_selectedLayer][levelMapUndo->x + levelMapUndo->y * layer->width * 2] = levelMapUndo->chunk;
					}
				}
			}
			return true;
		}
		break;
	}
	return false;
}
bool Editor::LevelMap::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	chunkX = (x - mapposition.x)/128;
	chunkY = (y - mapposition.y)/128;
	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
	{
		if (!editor) break;
		XeEngine::MapLayer* mapLayer = GetMapLayer();
		if (chunkX >= 0 && chunkY >= 0 && chunkX < mapLayer->width * 2 && chunkY < mapLayer->height * 2)
		{
			setMouseChunk(getEditorChunk());
			return true;
		}
		break;
	}
	case XeEngine::MouseInput_MIDDLE:
	{
		if (!editor) break;
		if (chunkX >= 0 && chunkY >= 0 && chunkX < mapwidth*2 && chunkY < mapheight*2)
		{
			setEditorChunk(getMouseChunk());
			return true;
		}
		break;
	}
	case XeEngine::MouseInput_RIGHT:
		if (mousedrag)
		{
			mapposition.x += (x - mousedragpos.x);
			mapposition.y += (y - mousedragpos.y);
		}
		else mousedrag = true;
		mousedragpos.x = x;
		mousedragpos.y = y;
		return true;
	default:
		mousedrag = false;
		break;
	}
	return true;
}

Editor::Size Editor::LevelMap::getSize()
{
	size.width = e->getEditorWidth();
	size.height = e->getEditorHeight();
	return size;
}

u8 Editor::LevelMap::GetCurrentLayer()
{
	return m_selectedLayer;
}
void Editor::LevelMap::SetCurrentLayer(u8 selectedLayer)
{
	m_selectedLayer = selectedLayer;
}
XeEngine::MapRoom* Editor::LevelMap::GetMapRoom()
{
	XeEngine::MapRoom* mapRoom = nullptr;
	getLevel()->map->GetRoom(mapRoom, getLevel()->m_room);
	return mapRoom;
}
void Editor::LevelMap::SetMapRoom(u8 index)
{
	getLevel()->map->SetRoom(index);
}
XeEngine::MapLayer* Editor::LevelMap::GetMapLayer()
{
	if (m_selectedLayer >= 4)
		return nullptr;
	XeEngine::MapRoom* mapRoom = GetMapRoom();
	if (mapRoom == nullptr)
		return nullptr;
	u8 layerID = mapRoom->layerID[m_selectedLayer];
	if (layerID == 0xFF)
		return nullptr;
	XeEngine::MapLayer* mapLayer;
	getLevel()->map->GetMapLayer(mapLayer, getLevel()->m_room, m_selectedLayer);
	return  mapLayer;
}
void Editor::LevelMap::SetMapLayer(u8 index)
{
	m_selectedLayer = index;
}