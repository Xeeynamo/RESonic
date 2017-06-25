#include "Editor.h"

#define OBJECTEDITOR_COLLIDESIZE 8

#define OBJECTLIST_SIZEWIDTH	168
#define OBJECTLIST_SIZEHEIGHT	48

#define OBJECTSTATUS_X		2	* 8
#define OBJECTSTATUS_X2		14	* 8
#define OBJECTSTATUS_Y		4	* 8
#define OBJECTSTATUS_W		32	* 8
#define OBJECTSTATUS_H		7	* 8
#define OBJECTSTATUS_LINEW	2

void XeEditor::init_Object()
{
	_objectViewIndex = 0;
	_selectedobj = 0xFFFF;
	_onmouseobjsCount = 0;

	_mapmovemousex = -1;
	_mapmovemousey = -1;
}
void XeEditor::draw_Object()
{
	levelMap = &level->map;

	// Disegna la mappa
	int width = levelMap->Layer(0)->width;
	int height = levelMap->Layer(0)->height;
	g->effect.SetProperties(1);
	g->effect.SetClutDepth(1, CLUT_COUNT);

	// Disegna il livello
	g->effect.SetProperties(1);
	g->effect.SetClutDepth(1, CLUT_COUNT);
	_internal_DrawLevel(_layoutselected, _mapposx, _mapposy);

	// Disegna la lista degli oggetti
	g->effect.SetClutDepth(0, CLUT_COUNT);
	int objectListHeight = editorHeight / OBJECTLIST_SIZEHEIGHT;
	int objectListPosX = editorWidth - OBJECTLIST_SIZEWIDTH + OBJECTLIST_SIZEHEIGHT;
	ObjectList *objlist = g->level.objlist;
	for(int i=0; i<objectListHeight; i++)
	{
		XeEffect::SetFadeFactor(1.0f);
		if (objlist[i].id != 0)
			g->PrintText(objectListPosX, i*OBJECTLIST_SIZEHEIGHT, "----\nID %04X\n%s\n----", objlist[i].id, objlist[i].name);
		else if (objlist[i].id == 0)
		{
			g->PrintText(objectListPosX, i*OBJECTLIST_SIZEHEIGHT, "----\nID %04X\n%s\n----", 0, "<unused slot>");
			continue;
		}

		char created = g->level.LoadObject(objlist[i].id);
		ObjectContainer *container = g->level.SelectObject(objlist[i].id);
		if (!container) continue;
		if (container->clut == 0xFF)
			g->effect.SetProperties(0);
		else
		{
			g->effect.SetProperties(1);
			g->effect.SetClutDepth(container->clut, CLUT_COUNT);
			g->effect.SetClutIndex(container->palette);
		}
		if (created != 0)
		{
			objanim[i].SetAnimation(&container->animation);
			objanim[i].SetAnimationIndex(0x0000);
		}
		objanim[i].Do();
		objanim[i].Draw(&container->texture, (objectListPosX - OBJECTLIST_SIZEHEIGHT/2), (i*OBJECTLIST_SIZEHEIGHT) + OBJECTLIST_SIZEHEIGHT/2);

		g->effect.SetProperties(1);
		g->effect.SetClutDepth(0, CLUT_COUNT);
		g->effect.SetClutIndex(0);
	}
	for(int i=0; i<level->objectPlacement.GetCount(); i++)
	{
		OBPEntry *e = &level->objectPlacement.entries[i];

		char created = g->level.LoadObject(e->id);
		ObjectContainer *container = g->level.SelectObject(e->id);
		if (!container) continue;
		if (container->clut == 0xFF)
			g->effect.SetProperties(0);
		else
		{
			g->effect.SetProperties(1);
			g->effect.SetClutDepth(container->clut, CLUT_COUNT);
			g->effect.SetClutIndex(container->palette);
		}
		if (created != 0)
		{
			objanim[objectListHeight+i].SetAnimation(&container->animation);
			objanim[objectListHeight+i].SetAnimationIndex(0x0000);
		}
		objanim[objectListHeight+i].Do();
		objanim[objectListHeight+i].Draw(&container->texture, e->x + _mapposx, e->y + _mapposy, false, false, 3.5);
	}

	XeEffect::SetFadeFactor(0.8f);
	for(int i=0; i<_onmouseobjsCount; i++)
	{
		if (_selectedobj != _onmouseobjs[i])
		DrawObjectStatus(&level->objectPlacement.entries[_onmouseobjs[i]], i+1);
	}
	XeEffect::SetFadeFactor(1.0f);
	if (_selectedobj != 0xFFFF)
	{
		DrawObjectStatus(&level->objectPlacement.entries[_selectedobj], 0);
	}

	g->effect.SetProperties(1);
	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);
}
void XeEditor::input_Object(WPARAM key, bool keyup)
{
	if (!levelMap) return;
	_objectViewIndex += _wheel;
	if (_objectViewIndex < 0) _objectViewIndex = 0;
}
void XeEditor::char_Object(WPARAM character)
{
	if (!levelMap) return;

}
void XeEditor::mouse_Object(short x, short y, WPARAM button)
{
	if (!levelMap) return;
	
	int count = level->objectPlacement.GetCount();
	OBPEntry *e = level->objectPlacement.entries;
	_onmouseobjsCount = 0;
	for(int i=0; i<count; i++)
	{
		if (x < e[i].x - OBJECTEDITOR_COLLIDESIZE + _mapposx || x > e[i].x + OBJECTEDITOR_COLLIDESIZE + _mapposx) continue;
		if (y < e[i].y - OBJECTEDITOR_COLLIDESIZE + _mapposy || y > e[i].y + OBJECTEDITOR_COLLIDESIZE + _mapposy) continue;
		_onmouseobjs[_onmouseobjsCount++] = i;
		if (_onmouseobjsCount >= 6) i = count;
	}

	switch(button)
	{
	case 0:
		_mapmovemousex = -1;
		_mapmovemousey = -1;
		break;
	case MK_LBUTTON:
		if (_mapmovemousex == -1)	// Non è in corso nessuna operazione di trascinamento
		{
			if (_onmouseobjsCount == 0)	// Se il mouse non è sopra nessun oggetto, la selezione precedente viene deselezionata
			{
				_selectedobj = 0xFFFF;
				return;
			}
			bool found = false;
			for(int i=0; i<_onmouseobjsCount; i++)
			{
				if (_selectedobj == _onmouseobjs[i])
				{
					if (++i >= _onmouseobjsCount)
						i = 0;
					_selectedobj = _onmouseobjs[i];
					found = true;
					i = _onmouseobjsCount;
					continue;
				}
			}
			if (!found)
				_selectedobj = _onmouseobjs[0];
		}
		if (_mapmovemousex == -1) // Attova la modalità dragging
		{
			_mapmovemousex = x;
			_mapmovemousey = y;
		}
		else // Se il click sinistro è ancora premuto, comincia l'operazione di dragging
		{
			e[_selectedobj].x += (x - _mapmovemousex);
			e[_selectedobj].y += (y - _mapmovemousey);
			_mapmovemousex = x;
			_mapmovemousey = y;
		}

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
	}
}

void XeEditor::DrawObjectStatus(OBPEntry *e, ushort position)
{
	if (position > 6) return;
	char *objname = "UNKNOW NAME";
	int x = OBJECTSTATUS_X;
	int y = OBJECTSTATUS_Y + ((OBJECTSTATUS_H + 1) * position);
	if (position > 0)
		y += 8;
	if (e->x + _mapposx < (editorWidth - OBJECTLIST_SIZEWIDTH + OBJECTLIST_SIZEHEIGHT) / 4)
	{
		x = editorWidth - OBJECTLIST_SIZEWIDTH + OBJECTLIST_SIZEHEIGHT - OBJECTSTATUS_X - OBJECTSTATUS_W;
	}
	static const Color c[] =
	{
		MAKERGB(0xC0, 0xC0, 0xC0), MAKERGB(0x90, 0x90, 0x90), MAKERGB(0x60, 0x60, 0x60), MAKERGB(0x90, 0x90, 0x90),  
		MAKERGB(0xFF, 0x00, 0x00), MAKERGB(0xC0, 0x00, 0x00), MAKERGB(0x80, 0x00, 0x00), MAKERGB(0xC0, 0x00, 0x00),
		MAKERGB(0x00, 0xFF, 0x00), MAKERGB(0x00, 0xC0, 0x00), MAKERGB(0x00, 0x80, 0x00), MAKERGB(0x00, 0xC0, 0x00),
		MAKERGB(0x00, 0x00, 0xFF), MAKERGB(0x00, 0x00, 0xC0), MAKERGB(0x00, 0x00, 0x80), MAKERGB(0x00, 0x00, 0xC0), 
		MAKERGB(0xFF, 0xFF, 0x00), MAKERGB(0xC0, 0xC0, 0x00), MAKERGB(0x80, 0x80, 0x00), MAKERGB(0xC0, 0xC0, 0x00), 
		MAKERGB(0xFF, 0x00, 0xFF), MAKERGB(0xC0, 0x00, 0xC0), MAKERGB(0x80, 0x00, 0x80), MAKERGB(0xC0, 0x00, 0xC0), 
		MAKERGB(0x00, 0xFF, 0xFF), MAKERGB(0x00, 0xC0, 0xC0), MAKERGB(0x00, 0x80, 0x80), MAKERGB(0x00, 0xC0, 0xC0), 
	};
	g->effect.SetProperties(0);
	XeShape::SetColorArray(c[position*4 + 0], c[position*4 + 1], c[position*4 + 2], c[position*4 + 3]);
	XeShape::FillRect(x, y, 6, OBJECTSTATUS_W, OBJECTSTATUS_H);
	XeShape::FillRect(x + OBJECTSTATUS_W, y + OBJECTSTATUS_H/2, 3.0, e->x + _mapposx - (x + OBJECTSTATUS_W) + OBJECTSTATUS_LINEW, OBJECTSTATUS_LINEW);
	XeShape::FillRect(e->x + _mapposx, y + OBJECTSTATUS_H/2, 3.0, OBJECTSTATUS_LINEW, e->y + _mapposy - (y + OBJECTSTATUS_H/2));

	for(int i=0; i<OBJECT_LISTSIZE; i++)
	{
		if (level->objlist[i].id == e->id)
		{
			objname = level->objlist[i].name;
			i = OBJECT_LISTSIZE;
		}
	}

	g->effect.SetProperties(1);
	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);
	g->PrintText(x, y + 0 * 8, "ID %04X (%s)", e->id, objname);
	g->PrintText(x, y + 1 * 8, "POS %04X %04X", e->x, e->y);
	g->PrintText(x, y + 2 * 8, "SIZE %02X %02X", e->width, e->height);
	g->PrintText(x, y + 3 * 8, "SUB ID %04X", e->subid);
	g->PrintText(x, y + 4 * 8, "%cFlip X", e->flipX ? 0xE1 : 0xE0);
	g->PrintText(x, y + 5 * 8, "%cFlip Y", e->flipY ? 0xE1 : 0xE0);
	g->PrintText(x, y + 6 * 8, "%cAbsolutecoord", e->absolute ? 0xE1 : 0xE0);

	g->PrintText(x+OBJECTSTATUS_X2, y + 1 * 8, "%cPriority", e->priority ? 0xE1 : 0xE0);
	g->PrintText(x+OBJECTSTATUS_X2, y + 2 * 8, "%cVisible", e->visible ? 0xE1 : 0xE0);
	g->PrintText(x+OBJECTSTATUS_X2, y + 3 * 8, "%cResparn", e->respawn ? 0xE1 : 0xE0);
	g->PrintText(x+OBJECTSTATUS_X2, y + 4 * 8, "%cIgnore X", e->ignorex ? 0xE1 : 0xE0);
	g->PrintText(x+OBJECTSTATUS_X2, y + 5 * 8, "%cIgnore Y", e->ignorey ? 0xE1 : 0xE0);
}