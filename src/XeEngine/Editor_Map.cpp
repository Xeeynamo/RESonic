#include "Editor.h"
#include "EditorRES.h"

// N/M - Layout selezionato
// V/B - Aumenta/diminuisce il numero di layout per mappa
// E/R - Aumenta/diminuisce la larghezza della mappa
// D/F - Aumenta/diminuisce l'altezza della mappa

#define EDITOR_MAPEDITOR_COLOR1	0xFFFF00FF
#define EDITOR_MAPEDITOR_COLOR2	0xFF00FF00
#define EDITOR_BLOCKSELECTED_COLOR1	0xFF0000FF
#define EDITOR_BLOCKSELECTED_COLOR2	0xFF00FFFF

#define EDITOR_LAYOUTLEFTBAR_FADEOUT		0.2f
#define EDITOR_LAYOUTLEFTBAR_FADEOUTSPEED	0.08f
#define EDITOR_LAYOUTLEFTBAR_FADEINSPEED	0.2f

void XeEditor::init_Map()
{
	_mapLeftBarFade = 1.0f;
	_layoutselected = 0;
	_mapposx = 128;
	_mapposy = 128;
	_mapblockscroll = 0;
	_mapblockselected = 0;
	_mapMouseOnMap = false;
	_mapOnLeftBar = false;

	_mapmovemousex = -1;
	_mapmovemousey = -1;
}
int XeEditor::GetMapBlockEditorSize(short width, short height)
{
	short blockwidth = editorWidth/128/3;
	if (blockwidth == 0 && editorWidth >= 384) blockwidth = 1;
	short blockheight = (editorHeight+127)/128;
	return blockwidth | (blockheight<<16);
}
void XeEditor::draw_Map()
{
	levelMap = &level->map;
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "File: %s", level->MakePath(level->currentAct, STAGEFILE_MAP));
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+8, "Map position (%i, %i, %i, %i)", levelMap->properties.posx, levelMap->properties.posy, levelMap->properties.width, levelMap->properties.height);
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+16, "Layout selected: %i/%i", levelMap->properties.layerCount > 0 ? _layoutselected + 1 : 0, levelMap->properties.layerCount);
	if (levelMap->properties.layerCount)
	{
		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+32, "Size: %ix%i", levelMap->Layer(_layoutselected)->width, levelMap->Layer(_layoutselected)->height);
		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+40, "Speed: %.3f x %.3f", float(levelMap->Layer(_layoutselected)->speedX)/256.0f, float(levelMap->Layer(_layoutselected)->speedY)/256.0f);
		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+48, "Priority: %i", levelMap->Layer(_layoutselected)->priority);

		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+64, "Selected chunk: %04X", _mapblockselected);
		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+72, "Map position: %04X %04X", _mapposx, _mapposy);
	}

	if ((levelMap->properties.layerCount != 0 && levelMap->Layer(_layoutselected)->width != 0 && levelMap->Layer(_layoutselected)->height) != 0)
	{
		g->effect.SetProperties(1);
		g->effect.SetClutDepth(1, CLUT_COUNT);
		_internal_DrawLevel(_layoutselected, _mapposx, _mapposy);

		if (_mapMouseOnMap)
		{
			g->effect.SetFadeFactor(0.5f);
			XeScene::SetPosition(_mapposx + _mapCursorX*128, _mapposy + _mapCursorY*128, 1.0f);
			_internal_DrawBlock(_mapblockselected);
			g->effect.SetFadeFactor(1.0f);
		}
		int blocksize = GetMapBlockEditorSize(editorWidth, editorHeight);
		int blockwidth = LOWORD(blocksize);
		int blockheight = HIWORD(blocksize);

		if (_mapOnLeftBar == false)
		{
			if (_mapLeftBarFade > EDITOR_LAYOUTLEFTBAR_FADEOUT)
			{
				_mapLeftBarFade -= EDITOR_LAYOUTLEFTBAR_FADEOUTSPEED;
			}
		}
		else
		{
			if (_mapLeftBarFade < 1.0)
			{
				_mapLeftBarFade += EDITOR_LAYOUTLEFTBAR_FADEINSPEED;
			}
		}
		XeEffect::SetFadeFactor(_mapLeftBarFade);
		XeScene::SetPosition(editorWidth-blockwidth*128, 0, 1.0f);
		for(int j=0; j<blockheight; j++)
		{
			for(int i=0; i<blockwidth; i++)
			{
				_internal_DrawBlock(i+j*blockwidth + _mapblockscroll);
				XeScene::MovePosition(128, -128);
			}
			XeScene::MovePosition(blockwidth*-128, 128);
		}

		g->effect.SetProperties(0);
		XeShape::SetColorArray(EDITOR_BLOCKSELECTED_COLOR1, EDITOR_BLOCKSELECTED_COLOR2, EDITOR_BLOCKSELECTED_COLOR1, EDITOR_BLOCKSELECTED_COLOR2);
		if (blockwidth != 0)
			XeShape::DrawRect(editorWidth-blockwidth*128 + (_mapblockselected%blockwidth)*128, ((_mapblockselected-_mapblockscroll)/blockwidth)*128, 4.0f, 128, 128);

		short width = levelMap->Layer(_layoutselected)->width;
		short height = levelMap->Layer(_layoutselected)->height;
		XeEffect::SetFadeFactor(1.0f);
		XeShape::SetColorArray(EDITOR_MAPEDITOR_COLOR1, EDITOR_MAPEDITOR_COLOR2, EDITOR_MAPEDITOR_COLOR1, EDITOR_MAPEDITOR_COLOR2);
		XeShape::DrawRect(_mapposx-1, _mapposy, 0.0f, width*256+2, height*256+1);
		XeShape::DrawRect(_mapposx-2, _mapposy-1, 0.0f, width*256+4, height*256+3);
		g->effect.SetProperties(1);
		g->effect.SetClutDepth(0, CLUT_COUNT);
	}
}
void XeEditor::input_Map(WPARAM key, bool keyup)
{
	if (!levelMap) return;
	int blocksize = GetMapBlockEditorSize(editorWidth, editorHeight);
	int blockwidth = LOWORD(blocksize);
	int blockheight = HIWORD(blocksize);

	_mapblockscroll += (_wheel*blockwidth);
	if ((signed short)_mapblockscroll < 0) _mapblockscroll = 0;

	switch(key)
	{
	case VK_F4:
		//levelMap->Save(name_levelmap);
		break;
	case VK_LEFT:
		_mapposx -= 16;
		break;
	case VK_RIGHT:
		_mapposx += 16;
		break;
	case VK_UP:
		_mapposy -= 16;
		break;
	case VK_DOWN:
		_mapposy += 16;
		break;

	case VK_PRIOR:
		_mapblockscroll -= blockwidth;
		if (_mapblockscroll < 0)
			_mapblockscroll = 0;
		break;
	case VK_NEXT:
		_mapblockscroll += blockwidth;
		break;
	case VK_HOME:
		_mapblockscroll = 0;
		break;
	case VK_END:
		int asd = LOWORD(GetMapBlockEditorSize(editorWidth, editorHeight));
		_mapblockscroll = (_mapblockselected / asd) * asd;
		break;
	}
}
void XeEditor::char_Map(WPARAM character)
{
	if (!levelMap) return;
	switch(character)
	{
		// Selezione del layout
	case '-':
		if (_layoutselected > 0) _layoutselected--;
		break;
	case '+':
		if (_layoutselected < levelMap->properties.layerCount-1) _layoutselected++;
		break;
	case 'V':
		if (levelMap->properties.layerCount > 0) levelMap->properties.layerCount--;
		break;
	case 'B':
		if (levelMap->properties.layerCount < 8) levelMap->properties.layerCount++;
		break;
		// Ridimensionamento del layout
	case 'E':
		if (levelMap->properties.layerCount == 0) break;
		if (levelMap->Layer(_layoutselected)->width > 0)
		{
			levelMap->ResizeLayer(_layoutselected, levelMap->Layer(_layoutselected)->width-1, levelMap->Layer(_layoutselected)->height);
		}
		break;
	case 'R':
		if (levelMap->properties.layerCount == 0) break;
		levelMap->ResizeLayer(_layoutselected, levelMap->Layer(_layoutselected)->width+1, levelMap->Layer(_layoutselected)->height);
		break;
	case 'D':
		if (levelMap->properties.layerCount == 0) break;
		if (levelMap->Layer(_layoutselected)->height > 0)
		{
			levelMap->ResizeLayer(_layoutselected, levelMap->Layer(_layoutselected)->width, levelMap->Layer(_layoutselected)->height-1);
		}
		break;
	case 'F':
		if (levelMap->properties.layerCount == 0) break;
		levelMap->ResizeLayer(_layoutselected, levelMap->Layer(_layoutselected)->width, levelMap->Layer(_layoutselected)->height+1);
		break;
		// Cambio delle proprietà del layout
	case 'O':
		levelMap->Layer(_layoutselected)->speedX--;
		break;
	case 'P':
		levelMap->Layer(_layoutselected)->speedX++;
		break;
	case 'K':
		levelMap->Layer(_layoutselected)->speedY--;
		break;
	case 'L':
		levelMap->Layer(_layoutselected)->speedY++;
		break;
	case 'N':
		levelMap->Layer(_layoutselected)->priority--;
		break;
	case 'M':
		levelMap->Layer(_layoutselected)->priority++;
		break;
	}
}
void XeEditor::mouse_Map(short x, short y, WPARAM button)
{
	if (!levelMap) return;
	int mapeditorblocksize = GetMapBlockEditorSize(editorWidth, editorHeight);
	short levelWidth = levelMap->Layer(_layoutselected)->width;
	short levelHeight = levelMap->Layer(_layoutselected)->height;
	_mapMouseOnMap = false;
	if (mousex > _mapposx && mousex < (_mapposx + levelWidth*256) &&
		mousey > _mapposy && mousey < (_mapposy + levelHeight*256))
	{
		_mapMouseOnMap = true;
		_mapCursorX = (mousex-_mapposx)/128;
		_mapCursorY = (mousey-_mapposy)/128;
	}
	if (x > editorWidth-LOWORD(mapeditorblocksize)*128)
		_mapOnLeftBar = true;
	else _mapOnLeftBar = false;

	switch(button)
	{
	case 0:
		_mapmovemousex = _mapmovemousey = -1;
		break;
	case MK_RBUTTON:
		if (_mapmovemousex == -1)
		{
			_mapmovemousex = x;
			_mapmovemousey = y;
		}
		else
		{
			_mapposx += (x - _mapmovemousex);
			_mapposy += (y - _mapmovemousey);
			_mapmovemousex = x;
			_mapmovemousey = y;
		}
		break;
	case MK_MBUTTON:
		if (_mapMouseOnMap)
		{
			short *block = levelMap->GetLayer(_layoutselected);
			_mapblockselected = block[(_mapCursorX&1) + (_mapCursorY&1)*2 + (_mapCursorX/2*4) + (_mapCursorY/2*4*levelWidth)];
		}
		break;
	case MK_LBUTTON:
		if (x > editorWidth-LOWORD(mapeditorblocksize)*128)
		{
			x -= (editorWidth-LOWORD(mapeditorblocksize)*128);
			x = x/128;
			y = y/128;
			_mapblockselected = x + y*LOWORD(mapeditorblocksize) + _mapblockscroll;
		}
		else if (_mapMouseOnMap)
		{
			short *block = levelMap->GetLayer(_layoutselected);
			block[(_mapCursorX&1) + (_mapCursorY&1)*2 + (_mapCursorX/2*4) + (_mapCursorY/2*4*levelWidth)] = _mapblockselected;
		}
		break;
	}
}