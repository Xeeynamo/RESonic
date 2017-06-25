#include "Editor.h"
#include "EditorRES.h"

#define EDITOR_TEXTURE_TEXPOSX 8
#define EDITOR_TEXTURE_TEXPOSY 48
#define EDITOR_TEXTURE_TILEPOSX (EDITOR_TEXTURE_TEXPOSX+256+16)
#define EDITOR_TEXTURE_TILEPOSY (EDITOR_TEXTURE_TEXPOSY+16)
#define EDITOR_TEXTURE_TILEZOOM 8
#define EDITOR_TEXTURE_BLOCKZOOM 2

const char *str_editor_mode[] =
{
	"Game",
	"Level properties",
	"Map properties",
	"Map editor",
	"Object editor",
	"Texture editor",
	"Palette editor",
	"Block editor",
	"Collision editor"
};

XeEditor::XeEditor()
{
	framecount = 0;
	EditorMode = 0;
	_editor_submode = 0;

	keyCtrl = 0;
	_wheel = 0;
	_charpos = 0;
	_texselected = 0;
	_palselected = 0;
	_colselected = 0;
	levelMap = 0;

	_showguide = false;
	_showfps = true;
	_double = false;

	unsigned short whitepixel = 0xFFFF;
	texWhite.Create(1, 1, 1, XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB565, &whitepixel);
	XeShape::Initialize();
	XeShape::SetTextureID(texWhite.GetID());

	init_Preview();
	init_Map();
	init_Object();
	init_Lut();
	init_Block();
	init_Collision();
}
XeEditor::~XeEditor()
{

}

void XeEditor::AttachGame(Game *game)
{
	g = game;
	level = &g->level;
	_internal_CollisionTexture();
}
void XeEditor::AttachScene(XeScene *scene)
{
	_scene = scene;
}
void XeEditor::Draw()
{
	framecount++;
	// Palette debugging
	if (EditorMode == 0)
	{
		for(int i=0; i<256; i++)
		{
			g->level.palette[1][i][0] &= ~0xFF000000;
		}
	}
	else
	{
		for(int i=0; i<256; i++)
		{
			g->level.palette[1][i][0] |= 0xFF000000;
		}
	}
	// Refresh palette
	if (g->levelLUT.GetID() == -1)
		g->levelLUT.Create(256, 256, CLUT_COUNT, XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA8888, g->level.palette);
	else
		g->levelLUT.Upload(0, 0, 256, 256, 0, CLUT_COUNT, g->level.palette);
	XeEffect::SetClutTexture(g->levelLUT.GetID());
	XeEffect::SetTexture();

	// Dynamic tiles
	g->level.dynamicTiles.Tick(&g->level.texture);

	// Set resolution on 2x mode
	editorWidth = LOWORD(g->scene->GetCameraSize());
	editorHeight = HIWORD(g->scene->GetCameraSize());
	if (_double && EditorMode != 0)
	{
		editorWidth /= 2;
		editorHeight /= 2;
		XeScene::SetCameraSize(editorWidth, editorHeight);
		XeScene::SetScale(2.0f, 2.0f);
	}

	_scene->OnPaintBegin();
	//glColorMask(1.0, 1.0, 1.0, 1.0);
	if (EditorMode != 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g->effect.UseProgram(true);
	g->effect.SetProperties(PROPERTIES_CLUT);
	g->effect.SetEffect(0);
	g->effect.SetClutIndex(0);
	g->effect.SetClutDepth(0, CLUT_COUNT);
	XeEffect::SetFadeFactor(1.0f);

	g->PrintText(0, 0, "Mode: %s", str_editor_mode[EditorMode]);
	XeShape::SetColor(0xFFFFFF00);
	XeShape::DrawRect(64, 64, 4.0f, 64, 64);
	if (_showguide)
	{
		int x_guide = 24*8;
		g->PrintText(0, 16, "[*] 2x resolution");
		for(int i=0; i<sizeof(str_editor_mode)/sizeof(char*); i++)
		{
			g->PrintText(0, 24+i*8, "[%i] %s", i, str_editor_mode[i]);
		}
		switch(EditorMode)
		{
		case 1:
			g->PrintText(x_guide, 16, "[F2] Edit level name");
			g->PrintText(x_guide, 24, "[F4]     Save maps");
			break;
		case 3:
			g->PrintText(x_guide, 16, "[F4]     Save maps");
			g->PrintText(x_guide, 24, "[ARROWS] Move map of 16px");
			g->PrintText(x_guide, 32, "[PG U/D] Scroll blocks");
			g->PrintText(x_guide, 40, "[HOME]   Go to the first block");
			g->PrintText(x_guide, 48, "[END]    Go to the selected block");
			g->PrintText(x_guide, 56, "[E/R]    Width -/+ of layout");
			g->PrintText(x_guide, 64, "[D/F]    Height -/+ of layout");
			g->PrintText(x_guide, 72, "[V/B]    Layer selected -/+");
			g->PrintText(x_guide, 80, "[O/P]    Speed X -/+");
			g->PrintText(x_guide, 88, "[K/L]    Speed Y -/+");
			g->PrintText(x_guide, 96, "[K/L]    Speed Y -/+");
			g->PrintText(x_guide, 104, "[N/M]    Priority -/+");
			g->PrintText(x_guide, 112, "[+/-]    Change layer");
			break;
		case 5:
			g->PrintText(x_guide, 16, "[O/P] Inc/Decrement texture");
			g->PrintText(x_guide, 24, "[K/L] Inc/Decrement palette");
			break;
		case 6:
			g->PrintText(x_guide, 24, "[K/L] Inc/Decrement palette");
			break;
		case 7:
			g->PrintText(x_guide, 24, "[MouseSX] Select the tile on Chunk editor");
			g->PrintText(x_guide, 24, "[MouseDX] List of tiles on Chunk editor");
			g->PrintText(x_guide, 32, "[CTRL+MouseSX] Draw the selected tile in Chunk editor");
			break;
		case 8:
			g->PrintText(x_guide, 24, "[V] Change collision verse");
		}
		XeEffect::SetFadeFactor(0.2f);
		XeEffect::SetSaturation(0.8f);
	}
	if (EditorMode != 0)
		_internal_CollisionTexture();

	if (EditorMode != 0)
	{
		if (level->stage.act == NULL)
		{
			g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "No level loaded.");
			return;
		}
	}

	switch(EditorMode)
	{
	case 0:
		draw_Preview();
		break;
	case 1:
		if (_editor_submode == 1 && (framecount % 60) <= 30) g->PrintText((12+_charpos)*8, 16, "|");
		else g->PrintText(0, 16, "Level name");
		g->PrintText(0, 24, "Map selected: %02X", g->level.GetMapCount() != 0 ? g->level.GetMapSelected()+1 : 0);
		g->PrintText(0, 24, "Map count: %02X", g->level.GetMapCount());

		g->PrintText(11*8, 16, "[%s]", g->level.GetLevelName());
		break;
	case 3:
		draw_Map();
		break;
	case 4:
		draw_Object();
		break;
	case 5: // Texture editor
		g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "File: %s", name_levelGfx);
		g->PrintText(EDITOR_OBJECTINFO_X, EDITOR_OBJECTINFO_Y+0, "Texture selected: %i", _texselected);
		g->PrintText(EDITOR_OBJECTINFO_X, EDITOR_OBJECTINFO_Y+8, "Palette selected: %i", _palselected);

		_scene->SetPosition(EDITOR_TEXTURE_TEXPOSX, EDITOR_TEXTURE_TEXPOSY);
		g->effect.SetClutDepth(1, CLUT_COUNT);
		g->effect.SetClutIndex(_palselected);
		g->level.texture.Draw(_texselected);

		if (mousex >= EDITOR_TEXTURE_TEXPOSX && mousex < EDITOR_TEXTURE_TEXPOSX+256 &&
			mousey >= EDITOR_TEXTURE_TEXPOSY && mousey < EDITOR_TEXTURE_TEXPOSY+256)
		{
			int id = ((mousex-EDITOR_TEXTURE_TEXPOSX)>>4) | (((mousey-EDITOR_TEXTURE_TEXPOSY)>>4)<<4) | (_texselected<<8);
			g->PrintText(EDITOR_TEXTURE_TILEPOSX, EDITOR_TEXTURE_TILEPOSY-16, "Tile ID: %04X", id);
			_scene->SetPosition(EDITOR_TEXTURE_TILEPOSX, EDITOR_TEXTURE_TILEPOSY);
			g->level.texture.Draw((mousex-EDITOR_TEXTURE_TEXPOSX)&0xF0, (mousey-EDITOR_TEXTURE_TEXPOSY)&0xF0, 0x10, 0x10, _texselected, NULL);
		}
		break;
	case 6:
		draw_Lut();
		break;
	case 7:
		draw_Block();
		break;
	case 8:
		draw_Collision();
		break;
	}

	XeEffect::SetFadeFactor(1.0);
	XeEffect::SetSaturation(0.0);
	XeEffect::SetClutDepth(0, CLUT_COUNT);
	XeEffect::SetClutIndex(0);
	if (_showfps) g->PrintText(0, editorHeight-8, "FPS %f", g->GetFPS());

	if (_double)
		g->scene->SetCameraSize(editorWidth*2, editorHeight*2);
	_scene->OnPaintEnd();
}
void XeEditor::InputKey(WPARAM key, bool keyup)
{
	switch(key)
	{
	case VK_CONTROL:
		keyCtrl = !keyup;
		break;
	case VK_RETURN:
		if (EditorMode == 1 && _editor_submode == 1)
		{
			_editor_submode = 0;
		}
		break;
	case VK_ESCAPE:
		_editor_submode = 0;
		break;
	case VK_LEFT:
		if (EditorMode == 1 && _editor_submode == 1)
		{
			if (_charpos > 0) _charpos--;
		}
		break;
	case VK_UP:
		break;
	case VK_RIGHT:
		if (EditorMode == 1 && _editor_submode == 1)
		{
			if (_charpos == 32) return;
			if (_charpos < strlen(g->level.level.name)) _charpos++;
		}
		break;
	case VK_DOWN:
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
		_scene->SetCameraSize(LOWORD(_scene->GetRenderSize()), HIWORD(_scene->GetRenderSize()));
		EditorMode = key - '0';
		break;
	case VK_F1:
		_showguide = !keyup;
		break;
	case VK_F2:
		if (EditorMode == 1)
		{
			if (_editor_submode == 1) return;
			_charpos = 0;
			_editor_submode = 1;
		}
		break;
	}

	switch(EditorMode)
	{
	case 0:
		input_Preview(key, keyup);
		break;
	case 3:
		input_Map(key, keyup);
		break;
	case 4:
		input_Object(key, keyup);
		break;
	case 7:
		input_Block(key, keyup);
		break;
	case 8:
		input_Collision(key, keyup);
		break;
	}

	_wheel = 0;
}
void XeEditor::InputChar(WPARAM character)
{
	character = toupper(character);
	switch(character)
	{
	case '*':
		_double ^= 1;
		return;
	}
	switch(EditorMode)
	{
	case 0:
		char_Preview(character);
		break;
	case 1:
		if (_editor_submode == 1)
		{
			char *name = g->level.level.name;
			switch(character)
			{
			case '\t':
			case '\n':
			case '\r':
				break;
			case VK_BACK:
				if (_charpos > 0) name[--_charpos] = 0;
				else name[_charpos] = 0;
				break;
			default:
				if (_charpos == 32) return;
				name[_charpos++] = (char)character;
				break;
			}
		}
		break;
	case 3:
		char_Map(character);
		break;
	case 4:
		char_Object(character);
		break;
	case 5:
		switch(character)
		{
		case 'O':
			if (_texselected > 0) _texselected--;
			break;
		case 'P':
			if (_texselected < TEXTURE_COUNT-1) _texselected++;
			break;
		case 'K':
			if (_palselected > 0) _palselected--;
			break;
		case 'L':
			if (_palselected < PALETTE_COUNT-1) _palselected++;
			break;
		}
		break;
	case 6:
		char_Lut(character);
		break;
	case 7:
		char_Block(character);
		break;
	case 8:
		char_Collision(character);
		break;
	}
}
void XeEditor::InputMouse(short x, short y, WPARAM button)
{
	mousebutton = button;
	mousex = x;
	mousey = y;

	if (_double && EditorMode != 0)
	{
		x /= 2;
		y /= 2;
		mousex /= 2;
		mousey /= 2;
	}

	switch(EditorMode)
	{
	case 1:
		mouse_Preview(mousex, mousey, button);
		break;
	case 3:
		mouse_Map(mousex, mousey, button);
		break;
	case 4:
		mouse_Object(mousex, mousey, button);
		break;
	case 6:
		mouse_Lut(mousex, mousey, button);
		break;
	case 7:
		mouse_Block(mousex, mousey, button);
		break;
	case 8:
		mouse_Collision(x, y, button);
		break;
	}
}
void XeEditor::InputWheel(signed short wheel)
{
	_wheel = -wheel;
}
void XeEditor::ShowFPS(bool enabled)
{
	_showfps = enabled;
}

void XeEditor::_internal_DrawLevel(short layer, short posx, short posy)
{
	short *block = levelMap->GetLayer(layer);
	short width = levelMap->Layer(layer)->width;
	short height = levelMap->Layer(layer)->height;
	short endW = MIN(MAX(editorWidth - _mapposx + 255, 0) / 256, width);
	short endH = MIN(MAX(editorHeight - _mapposy + 255, 0) / 256, height);
	for(int j=MAX(-_mapposy/256, 0); j<endH; j++)
	{
		for(int i=MAX(-_mapposx/256, 0); i<endW; i++)
		{
			XeScene::SetPosition(_mapposx + i*256, _mapposy + j*256, 0.0f);
			_internal_DrawBlock(block[(i+j*width)*4+0]);
			XeScene::MovePosition(128, -128);
			_internal_DrawBlock(block[(i+j*width)*4+1]);
			XeScene::MovePosition(-128, 0);
			_internal_DrawBlock(block[(i+j*width)*4+2]);
			XeScene::MovePosition(128, -128);
			_internal_DrawBlock(block[(i+j*width)*4+3]);
		}
	}
}
void XeEditor::_internal_CollisionTexture()
{
	XeEngine::Memory colsheet;
	colsheet.Alloc(256*256);
	_internal_CollisionSheetToRaw((u8*)colsheet.GetMemoryHandle(), g->level.collision, 0xF);
	if (texCollision.GetID() == INVALID_TEXTURE)
		texCollision.Create(256, 256, 1, XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8, colsheet.GetMemoryHandle());
	else
		texCollision.Upload(0, 0, 256, 256, 0, 1, colsheet.GetMemoryHandle());
}
void XeEditor::_internal_CollisionBlockToRaw(unsigned char *raw, char *c, unsigned char emptyvalue)
{
	memset(raw, emptyvalue, 16*16);
	for(int i=0; i<16; i++)
	{
		raw[i] = 0;
		if ((unsigned char)c[i] > 0x80)
		{
			for(int j=0; j<(unsigned char)(~c[i]+1); j++)
			{
				raw[j*16+i] = 0x01;
			}
		}
		else
		{
			for(int j=0; j<c[i]; j++)
			{
				raw[(0xF-j)*16 +i] = 0x01;
			}
		}
	}
}
void XeEditor::_internal_CollisionSheetToRaw(unsigned char *raw, Collision *c, unsigned char emptyvalue)
{
	unsigned char colblock[16*16];
	if (_colverse == 1)
		c += 0x100;
	for(int i=0; i<0x100; i++)
	{
		_internal_CollisionBlockToRaw(colblock, c[i], emptyvalue);
		for(int j=0; j<16; j++)
		{
			memcpy(&raw[j*256 + ((i>>4)*256*16) + ((i&0xF)*16)], &colblock[j*16], 16);
		}
	}
}
void XeEditor::_internal_DrawBlock(int blockindex)
{
	TileEntry *tentry = g->level.chunk[blockindex];
	TileEntry *tileblock;
	int prevpal = -1;
	for(int j=0; j<8; j++)
	{
		for(int i=0; i<8; i++)
		{
			tileblock = &tentry[i | (j<<3)];
			//if (tileblock->tile)
			{
				if (prevpal != tileblock->palette)
				{
					prevpal = tileblock->palette;
					g->effect.SetClutIndex(tileblock->palette);
					g->effect.SetTexture();
				}
				_scene->Push();
				_scene->MovePosition(8, 8);
				_scene->SetScale(tileblock->mirror ? -1.0f : 1.0f, tileblock->flip ? -1.0f : 1.0f);
				_scene->MovePosition(-8, -8);
				g->level.texture.Draw((tileblock->tile<<4)&0xFF, tileblock->tile&~0xF, 16, 16, tileblock->texture, NULL);
				_scene->Pop();
			}
			_scene->MovePosition(16, 0);
		}
		_scene->MovePosition(-16*8, 16);
	}
	if (_collisionmode == 1)
	{
		g->effect.SetClutDepth(0, CLUT_COUNT);
		g->effect.SetClutIndex(0);
		g->effect.SetFadeFactor(0.5f);
		_scene->Push();
		_scene->MovePosition(0, -128);;
		_internal_DrawBlockCollision(blockindex);
		_scene->Pop();
		g->effect.SetFadeFactor(1.0f);
		g->effect.SetClutDepth(1, CLUT_COUNT);
	}
}
void XeEditor::_internal_DrawBlockCollision(int blockindex)
{
	TileEntry *tentry = g->level.chunk[blockindex];
	TileEntry *tileblock;
	int prevpal = -1;
	for(int j=0; j<8; j++)
	{
		for(int i=0; i<8; i++)
		{
			tileblock = &tentry[i | (j<<3)];
			short colindex = g->level.collisionIndex[0][tileblock->Tile];
			/*if (colindex == 0)
			{
				_scene->MovePosition(16, 0);
				continue;
			}*/
			//if (tileblock->tile)
			{
				_scene->Push();
				_scene->MovePosition(8, 8);
				_scene->SetScale(tileblock->mirror ? -1.0f : 1.0f, tileblock->flip ? -1.0f : 1.0f);
				_scene->MovePosition(-8, -8);
				texCollision.Draw((colindex<<4)&0xFF, colindex&~0xF, 16, 16, 0, NULL);
				_scene->Pop();
			}
			_scene->MovePosition(16, 0);
		}
		_scene->MovePosition(-16*8, 16);
	}
}