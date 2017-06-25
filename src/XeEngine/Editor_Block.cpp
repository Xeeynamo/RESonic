#include "Editor.h"
#include "EditorRES.h"

#define EDITOR_BLOCKEDITOR_ZOOM	2
#define EDITOR_BLOCKEDITOR_INFO_X (EDITOR_OBJECTINFO_X+widthControl*128+8)
#define EDITOR_BLOCKEDITOR_INFO_Y (EDITOR_OBJECTINFO_Y)
#define EDITOR_BLOCKEDITOR_EDIT_X (EDITOR_OBJECTINFO_X+widthControl*128+48)
#define EDITOR_BLOCKEDITOR_EDIT_Y (EDITOR_OBJECTINFO_Y+128*(int)EDITOR_BLOCKEDITOR_ZOOM+24)

#define EDITOR_BLOCKEDITOR_SELECTED_COLOR1	0xFF0000FF
#define EDITOR_BLOCKEDITOR_SELECTED_COLOR2	0xFFFF0000
#define EDITOR_BLOCKEDITOR_MENU_COLOR1		0xFFFF00FF
#define EDITOR_BLOCKEDITOR_MENU_COLOR2		0xFFFFFF00

void XeEditor::init_Block()
{
	_blockselected = 0;
	_blockpreview = 0;
	_subblockselected = 0;
	_subblockpreview = 0;
	_rightclickf = 0;
	_rightclickmod = 0;
	_collisionmode = 0;
	_collblockselected = 0;
	_blockscroll = 0;
}
void XeEditor::draw_Block()
{
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "File: %s", level->MakePath(level->currentAct, STAGEFILE_BLK));
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+8, "Blocks count: %X (%i)", levelBlock.Count(), levelBlock.Count());
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+16, "Destination: %X", levelBlock.Destination());
	g->PrintText(EDITOR_OBJECTINFO_X, EDITOR_OBJECTINFO_Y, "Block selected: %i", _blockselected);
	TileEntry *tentry = g->level.chunk[_blockselected];
	TileEntry *tileblock = &tentry[_subblockpreview];
	g->effect.SetClutDepth(1, CLUT_COUNT);

	int widthControl = (LOWORD(_scene->GetCameraSize()) - 256-16 - EDITOR_OBJECT_X)/128;
	int heightControl = (HIWORD(_scene->GetCameraSize()) - EDITOR_OBJECT_Y)/128;
	if (widthControl == 0) widthControl = 1;

	if (_rightclickf == 1)
	{
		XeEffect::SetFadeFactor(0.6f);
		XeEffect::SetSaturation(0.8f);
	}
	for(int l=0; l<heightControl; l++)
	{
		_scene->SetPosition(EDITOR_OBJECT_X, EDITOR_OBJECT_Y+l*128);
		for(int k=0; k<widthControl; k++)
		{
			_internal_DrawBlock(k + l*widthControl + _blockscroll);
			_scene->MovePosition(128, -128);
		}
	}
	XeEffect::SetFadeFactor(1.0);
	XeEffect::SetSaturation(0.0);

	g->PrintText(EDITOR_BLOCKEDITOR_INFO_X, EDITOR_BLOCKEDITOR_EDIT_Y+264,	"[%c] Collision mode", _collisionmode ? 'X' : ' ');
	if (_collisionmode == 0)
	{
		int res = g->level.texture.GetResolution();
		ushort tileid = (tileblock->texture<<8) | tileblock->tile;
		g->effect.SetClutDepth(0, CLUT_COUNT);
		g->effect.SetClutIndex(0);
		g->PrintText(EDITOR_BLOCKEDITOR_INFO_X, EDITOR_BLOCKEDITOR_INFO_Y,		"Block ID %04X ", _blockpreview);
		g->PrintText(EDITOR_BLOCKEDITOR_INFO_X, EDITOR_BLOCKEDITOR_EDIT_Y,	"SubBlock ID %02X", _subblockpreview);
		g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X, EDITOR_BLOCKEDITOR_EDIT_Y+16,		"Tile ID     %04X (%3i,%4i)", tileid, (tileid&15) * 16 * res, tileid/16 * 16 * res);
		g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X, EDITOR_BLOCKEDITOR_EDIT_Y+24,	"Palette ID    %02X", tileblock->palette);
		g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X, EDITOR_BLOCKEDITOR_EDIT_Y+32,	"Depth         %2i", tileblock->depth);
		g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X, EDITOR_BLOCKEDITOR_EDIT_Y+40,	"Flip          %2i", tileblock->flip);
		g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X, EDITOR_BLOCKEDITOR_EDIT_Y+48,	"Mirror        %2i", tileblock->mirror);

		for(int i=0; i<2; i++)
		{
			char colvalid = (i == 0) ? tileblock->path1 : tileblock->path2;
			if (colvalid)
			{
				if (colvalid & 1)
					g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X+i*64, EDITOR_BLOCKEDITOR_EDIT_Y+72, "^^");
				if (colvalid & 2)
				{
					g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X-8+i*64, EDITOR_BLOCKEDITOR_EDIT_Y+80, "<  >\n<  >");
					g->PrintText(EDITOR_BLOCKEDITOR_EDIT_X+i*64, EDITOR_BLOCKEDITOR_EDIT_Y+96, "VV");
				}
			}
			_scene->SetPosition(EDITOR_BLOCKEDITOR_EDIT_X+i*64, EDITOR_BLOCKEDITOR_EDIT_Y+80);
			char c = g->level.collisionIndex[i&1][tileblock->Tile];
			texCollision.Draw((c&0xF)<<4, c&0xF0, 16, 16, 0, NULL);
		}

		g->effect.SetClutDepth(1, CLUT_COUNT);
		g->effect.SetClutIndex(tileblock->palette);
		_scene->Push();
		_scene->SetPosition(EDITOR_OBJECTINFO_X+widthControl*128+16, EDITOR_OBJECT_Y + 128*EDITOR_BLOCKEDITOR_ZOOM+40);
		_scene->MovePosition(8, 8);
		_scene->SetScale(tileblock->mirror ? -1.0f : 1.0f, tileblock->flip ? -1.0f : 1.0f);
		_scene->MovePosition(-8, -8);
		g->level.texture.Draw((tileblock->tile&0xF)<<4, tileblock->tile&0xF0, 16, 16, tileblock->texture, NULL);
		_scene->Pop();
	}
	else
	{
		// Stampa il menu delle collisioni
		_scene->SetPosition(EDITOR_BLOCKEDITOR_INFO_X, EDITOR_BLOCKEDITOR_EDIT_Y, 1.0f);
		texCollision.Draw(0);
		g->effect.SetProperties(0);
		XeShape::SetColorArray(EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2, EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2);
		XeShape::DrawRect(EDITOR_BLOCKEDITOR_INFO_X+(_collblockselected&0xF)*16-1, EDITOR_BLOCKEDITOR_EDIT_Y+(_collblockselected&0xF0), 4.0f, 17, 16);

		g->effect.SetProperties(1);
		g->effect.SetClutDepth(1, CLUT_COUNT);
		g->effect.SetClutIndex(tileblock->palette);
	}

	// Stampa il block zoommato
	_scene->SetPosition(EDITOR_OBJECT_X+widthControl*128+8, EDITOR_OBJECT_Y);
	_scene->SetScale(EDITOR_BLOCKEDITOR_ZOOM, EDITOR_BLOCKEDITOR_ZOOM);
	g->effect.SetClutDepth(1, CLUT_COUNT);
	_internal_DrawBlock(_blockpreview);

	// Stampa i rettangoli di selezione
	g->effect.SetProperties(0);
	XeShape::SetColorArray(EDITOR_BLOCKEDITOR_SELECTED_COLOR1, EDITOR_BLOCKEDITOR_SELECTED_COLOR2, EDITOR_BLOCKEDITOR_SELECTED_COLOR1, EDITOR_BLOCKEDITOR_SELECTED_COLOR2);
	XeShape::DrawRect(EDITOR_OBJECT_X+((_blockpreview%widthControl)*128)-1,EDITOR_OBJECT_Y+((_blockpreview/widthControl)*128)-1, 1.0f, 130, 130);
	XeShape::DrawRect(EDITOR_OBJECT_X+widthControl*128+8+((_subblockpreview&7)*16*EDITOR_BLOCKEDITOR_ZOOM)-1,
		EDITOR_OBJECT_Y+((_subblockpreview>>3)*16*EDITOR_BLOCKEDITOR_ZOOM)-1, 1.0f, (16*EDITOR_BLOCKEDITOR_ZOOM)-1, (16*EDITOR_BLOCKEDITOR_ZOOM)-1);
	g->effect.SetProperties(1);

	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);

	BlockED_Draw_Tilemenu();
	BlockED_Draw_Collisionmenu();
}
void XeEditor::input_Block(WPARAM key, bool keyup)
{
	if (!BlockED_Input_Tilemenu())
	{
		int widthControl = (LOWORD(_scene->GetCameraSize()) - 256-16 - EDITOR_OBJECT_X)/128;
		_blockscroll += (_wheel*widthControl);
		if (_blockscroll < 0) _blockscroll = 0;
		switch(key)
		{
		case VK_F4:
			if (keyup) levelBlock.Save(name_levelblock);
			break;
		}
	}

}
void XeEditor::char_Block(WPARAM character)
{

}
void XeEditor::mouse_Block(short x, short y, WPARAM button)
{
	_blockpreview = _blockselected;
	_subblockpreview = _subblockselected;
	TileEntry *tentry = &g->level.chunk[_blockpreview][_subblockpreview];
	int widthControl = (editorWidth - 256-16 - EDITOR_OBJECT_X)/128;
	int heightControl = (editorHeight - EDITOR_OBJECT_Y)/128;
	
	if (!BlockED_Mouse_Tilemenu() && !BlockED_Mouse_Collisionmenu())
	{
		int mx = (mousex - EDITOR_OBJECT_X);
		int my = (mousey - EDITOR_OBJECT_Y);
		if (mx >= 0 && my >= 0)
		{
			// Menu dei Chunk localizzato a sinistra dell'editor
			mx /= 128;
			my /= 128;
			if (mx >= 0 && mx < widthControl && my >= 0 && my < heightControl)
			{
				_blockpreview = mx + my*widthControl + _blockscroll;
				if (button == MK_LBUTTON)
				{
					_blockselected = _blockpreview;
				}
				return;
			}
		}

		mx = mousex - (EDITOR_OBJECT_X+widthControl*128+8);
		my = mousey - (EDITOR_OBJECT_Y);
		if (mx >= 0 && my >= 0)
		{
			mx /= (16*EDITOR_BLOCKEDITOR_ZOOM);
			my /= (16*EDITOR_BLOCKEDITOR_ZOOM);
			if (mx >= 0 && my >= 0 && (mx|my) < 8)
			{
				// Editor dei Chunk localizzato a sinistra dell'editor
				_subblockpreview = mx + my*8;
				if (button == MK_RBUTTON)
				{
					_subblockselected = _subblockpreview;
					_tileblockselected = g->level.chunk[_blockpreview][_subblockpreview].tile;
					_rightclickf = 1;
					_rightclickmod = 0;
					//_rightclickx = mousex;
					//_rightclicky = mousey;
					_rightclickx = EDITOR_OBJECT_X;
					_rightclicky = EDITOR_OBJECT_Y;
				}
				if (button == MK_LBUTTON)
				{
					_subblockselected = _subblockpreview;
					if (_collisionmode == 1)
					{
						g->level.collisionIndex[0][g->level.chunk[_blockpreview][_subblockpreview].Tile] = _collblockselected;
					}
				}
				if (button == 9) // CTRL + MouseSX
				{
					g->level.chunk[_blockpreview][_subblockpreview] = g->level.chunk[_blockpreview][_subblockselected];
				}
				return;
			}
		}

		if (button == MK_RBUTTON)
		{
			if (_collisionmode == 1) return;
			if (mousex >= EDITOR_BLOCKEDITOR_EDIT_X-32 && mousex < EDITOR_BLOCKEDITOR_EDIT_X-16 &&
				mousey >= EDITOR_BLOCKEDITOR_EDIT_Y+32 && mousey < EDITOR_BLOCKEDITOR_EDIT_Y+48)
			{
				_tileblockselected = g->level.chunk[_blockpreview][_subblockpreview].tile;
				_rightclickf = 1;
				_rightclickmod = 0;
				_rightclickx = mousex;
				_rightclicky = mousey;
			}
			else if (mousex >= EDITOR_BLOCKEDITOR_EDIT_X-32 && mousex < EDITOR_BLOCKEDITOR_EDIT_X-16 &&
				mousey >= EDITOR_BLOCKEDITOR_EDIT_Y+64 && mousey < EDITOR_BLOCKEDITOR_EDIT_Y+80)
			{
				_collblockselected = g->level.collisionIndex[0][g->level.chunk[_blockpreview][_subblockpreview].Tile];
				_rightclickf = 2;
				_rightclickmod = 0;
				_rightclickx = mousex;
				_rightclicky = mousey;
			}
		}


		if (button == MK_LBUTTON || button == MK_RBUTTON)
		{
			if (mousey >= (EDITOR_BLOCKEDITOR_EDIT_Y+264) && mousey < (EDITOR_BLOCKEDITOR_EDIT_Y+264+8) && mousex >= EDITOR_BLOCKEDITOR_INFO_X)
			{
				_collisionmode ^= 1;
				return;
			}
			if (_collisionmode == 1)
			{
				if (mousex >= EDITOR_BLOCKEDITOR_INFO_X && mousex < EDITOR_BLOCKEDITOR_INFO_X+256 &&
					mousey >= EDITOR_BLOCKEDITOR_EDIT_Y && mousey < EDITOR_BLOCKEDITOR_EDIT_Y+256)
				{
					mousex = (mousex-EDITOR_BLOCKEDITOR_INFO_X)/16;
					mousey = (mousey-EDITOR_BLOCKEDITOR_EDIT_Y)/16;
					_collblockselected = mousex | (mousey<<4);
				}
				return;
			}
			switch((mousey-(EDITOR_BLOCKEDITOR_EDIT_Y+16))/8)
			{
			case 0: // Tile
				break;
			case 1: // Palette
				if (button == MK_LBUTTON)
					tentry->palette++;
				else if (button == MK_RBUTTON)
					tentry->palette--;
				break;
			case 2: // Depth
				tentry->depth ^= 1;
				break;
			case 3: // Collide flip
				tentry->flip ^= 1;
				break;
			case 4: // Collide mirror
				tentry->mirror ^= 1;
				break;
			default:
				mousey = mousey-(EDITOR_BLOCKEDITOR_EDIT_Y+16);
				mousey = mousex;
			}
			return;
		}
	}
}

void XeEditor::BlockED_Draw_Tilemenu()
{
	if (_rightclickf != 1) return;

	if (_rightclickx+256 > editorWidth)
		_rightclickx-=256;
	if (_rightclicky+256 > editorHeight)
		_rightclicky-=256;

	g->effect.SetClutDepth(1, CLUT_COUNT);
	g->effect.SetClutIndex(g->level.chunk[_blockpreview][_subblockpreview].palette);
	_scene->SetPosition(_rightclickx, _rightclicky, 4.0f);
	g->level.texture.Draw(_texselected);

	g->effect.SetProperties(0);
	XeShape::SetColorArray(EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2, EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2);
	XeShape::DrawRect(_rightclickx-1, _rightclicky-1, 4.0f, 258, 258);
	g->effect.SetProperties(1);

	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);
}
bool XeEditor::BlockED_Input_Tilemenu()
{
	if (_rightclickf != 1) return false;

	_texselected += _wheel;
	if ((signed char)_texselected >= level->texture.GetDepth()) _texselected = level->texture.GetDepth() - 1;
	if ((signed char)_texselected < 0) _texselected = 0;
	g->level.chunk[_blockpreview][_subblockpreview].texture = _texselected;
	return true;
}
bool XeEditor::BlockED_Mouse_Tilemenu()
{
	if (_rightclickf != 1) return false;

	_tileblockpreview = _tileblockselected;
	if (mousex >= _rightclickx && mousex < _rightclickx+256 &&
		mousey >= _rightclicky && mousey < _rightclicky+256)
	{
		_tileblockpreview = (((mousex-_rightclickx)>>4)&0x0F) | ((mousey-_rightclicky)&0xF0);
	}
	if (mousebutton == MK_LBUTTON || mousebutton == MK_RBUTTON)
	{
		_rightclickf = 0;
	}
	g->level.chunk[_blockpreview][_subblockpreview].tile = _tileblockpreview;
	return true;
}
void XeEditor::BlockED_Draw_Collisionmenu()
{
	if (_rightclickf != 2) return;

	if (_rightclickx+256 > editorWidth)
		_rightclickx-=256;
	if (_rightclicky+256 > editorHeight)
		_rightclicky-=256;

	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);
	_scene->SetPosition(_rightclickx, _rightclicky, 4.0f);
	texCollision.Draw(0);

	g->effect.SetProperties(0);
	XeShape::SetColorArray(EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2, EDITOR_BLOCKEDITOR_MENU_COLOR1, EDITOR_BLOCKEDITOR_MENU_COLOR2);
	XeShape::DrawRect(_rightclickx-1, _rightclicky-1, 4.0f, 258, 258);
	g->effect.SetProperties(1);
}
bool XeEditor::BlockED_Mouse_Collisionmenu()
{
	if (_rightclickf != 2) return false;

	_collblockpreview = _collblockselected;
	if (mousex >= _rightclickx && mousex < _rightclickx+256 &&
		mousey >= _rightclicky && mousey < _rightclicky+256)
	{
		_collblockpreview = (((mousex-_rightclickx)>>4)&0x0F) | ((mousey-_rightclicky)&0xF0);
	}
	if (mousebutton == MK_LBUTTON || mousebutton == MK_RBUTTON)
	{
		_rightclickf = 0;
	}
	g->level.collisionIndex[0][g->level.chunk[_blockpreview][_subblockpreview].Tile] = _collblockpreview;

	return true;
}