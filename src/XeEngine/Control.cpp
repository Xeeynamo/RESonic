#include "MainEditor.h"
#include "XeFont.h"
#include <stdio.h>

Editor::Control::Control(MainEditor *e, Control *parent, short x, short y, short width, short height)
{
	m_name = "Control";
	this->e = e;
	this->parent = parent;
	this->position.x = x;
	this->position.y = y;
	this->size.width = width;
	this->size.height = height;

	if (e) font = e->font;

	enabled = true;
	visible = true;
	focus = false;
	collisionview = false;
	textColor = 0;
	fadefactor = 1.0f;
	fadeOnLoseFocus = false;
}

Editor::CtrlSize Editor::Control::getSize()
{
	return size;
}
void Editor::Control::setSize(Editor::CtrlSize size)
{
	this->size = size;
}
bool Editor::Control::getFocus()
{
	return focus;
}
void Editor::Control::setFocus(bool focus)
{
	this->focus = focus;
}
void Editor::Control::setFadeOnLoseFocus(bool enabled)
{
	fadeOnLoseFocus = enabled;
	fadefactor = 1.0f;
}
Editor::CtrlPosition Editor::Control::getMouseCoord()
{
	return e->getMouseCoord();
}
void Editor::Control::AddControl(Control *c)
{
	CtrlPosition pos = c->getPosition();
	pos.x += this->position.x;
	pos.y += this->position.y;
	c->setPosition(pos);
	controlList.Add(c);
}

Game *Editor::Control::getGame()
{
	return e->getGame();
}
XeLevel *Editor::Control::getLevel()
{
	return e->getLevel();
}
short Editor::Control::getEditorWidth()
{
	return e->getEditorWidth();
}
short Editor::Control::getEditorHeight()
{
	return e->getEditorHeight();
}
char *Editor::Control::getName()
{
	return m_name;
}
bool Editor::Control::getCollisionView()
{
	return collisionview;
}
void Editor::Control::setCollisionView(bool collisionview)
{
	this->collisionview = collisionview;
}
bool Editor::Control::isCtrlPressed()
{
	return e->isCtrlPressed();
}
bool Editor::Control::isAltPressed()
{
	return e->isAltPressed();
}
bool Editor::Control::isShiftPressed()
{
	return e->isShiftPressed();
}
short Editor::Control::getWheelY()
{
	return e->getWheelY();
}

void Editor::Control::PrintChar(short x, short y, unsigned char c)
{
	short cx = (short)c;
	XeEffect::SetClutIndex(textColor);
	font->SetXY(x, y);
	font->PrintText((char*)&cx);
}
void Editor::Control::PrintText(short x, short y, const char* format, ...)
{
	char str[0x100];
	va_list args;
	va_start(args, format);
	vsprintf_s(str, format, args);
	XeEffect::SetClutIndex(textColor);
	font->SetXY(x, y);
	font->PrintText(str);
	va_end(args);
}
void Editor::Control::TextColor(TEXTCOLOR color)
{
	textColor = color;
}
void Editor::Control::SolidPalette(bool solid)
{
	Palette *p = getLevel()->palette[1];
	if (solid == true)
	{
		for(int i=0; i<256; i++)
		{
			for(int j=0; j<256; j+=16)
				p[i][j] |= 0xFF000000;
		}
	}
	else
	{
		for(int i=0; i<256; i++)
		{
			for(int j=0; j<256; j+=16)
				p[i][j] &= 0x00FFFFFF;
		}
	}
}
void Editor::Control::DrawTile(short x, short y, short tile, byte palette, byte flipXY)
{
	XeScene::SetPosition(x, y);
	XeEffect::SetClutDepth(1, CLUT_COUNT);
	XeEffect::SetClutIndex(palette);
	getLevel()->texture.Draw(((tile&0x000F)<<4), tile&0x00F0, 16, 16, tile>>8);
}
void Editor::Control::DrawChunk(short x, short y, short chunk)
{
	TileEntry *tentry = getLevel()->chunk[chunk];
	TileEntry *tileblock;
	int prevpal = -1;
	XeScene::SetPosition(x, y);
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
					XeEffect::SetClutIndex(tileblock->palette);
					XeEffect::SetTexture();
				}
				XeScene::Push();
				XeScene::MovePosition(8, 8);
				XeScene::SetScale(tileblock->mirror ? -1.0f : 1.0f, tileblock->flip ? -1.0f : 1.0f);
				XeScene::MovePosition(-8, -8);
				getLevel()->texture.Draw((tileblock->tile<<4)&0xFF, tileblock->tile&~0xF, 16, 16, tileblock->texture, NULL);
				XeScene::Pop();
			}
			XeScene::MovePosition(16, 0);
		}
		XeScene::MovePosition(-16*8, 16);
	}
	if (collisionview == 1)
	{
		XeEffect::SetClutDepth(0, CLUT_COUNT);
		XeEffect::SetClutIndex(0);
		XeEffect::SetFadeFactor(0.5f);
		DrawChunkCollision(x, y, chunk);
		/*XeScene::Push();
		XeScene::MovePosition(0, -128);;
		_internal_DrawBlockCollision(chunk);
		XeScene::Pop();*/
		XeEffect::SetFadeFactor(1.0f);
		XeEffect::SetClutDepth(1, CLUT_COUNT);
	}
}
void Editor::Control::DrawChunkCollision(short x, short y, short chunk)
{
	TileEntry *tentry = getLevel()->chunk[chunk];
	TileEntry *tileblock;
	int prevpal = -1;
	XeScene::SetPosition(x, y);
	for(int j=0; j<8; j++)
	{
		for(int i=0; i<8; i++)
		{
			tileblock = &tentry[i | (j<<3)];
			short colindex = getLevel()->collisionIndex[0][tileblock->Tile];
			if (colindex == 0)
			{
				XeScene::MovePosition(16, 0);
				continue;
			}
			if (tileblock->tile)
			{
				XeScene::Push();
				XeScene::MovePosition(8, 8);
				XeScene::SetScale(tileblock->mirror ? -1.0f : 1.0f, tileblock->flip ? -1.0f : 1.0f);
				XeScene::MovePosition(-8, -8);
				e->getTextureCollision()->Draw((colindex<<4)&0xFF, colindex&~0xF, 16, 16, 0, NULL);
				XeScene::Pop();
			}
			XeScene::MovePosition(16, 0);
		}
		XeScene::MovePosition(-16*8, 16);
	}
}
void Editor::Control::DrawLevel256(short x, short y, short screenWidth, short screenHeight, short layer)
{
	short *block = getLevel()->map.GetLayer(layer);
	short width = getLevel()->map.Layer(layer)->width;
	short height = getLevel()->map.Layer(layer)->height;
	short endW = MIN(MAX(screenWidth - x + 255, 0) / 256, width);
	short endH = MIN(MAX(screenHeight - y + 255, 0) / 256, height);

	short dstX, dstY;
	for(int j=MAX(-y/256, 0); j<endH; j++)
	{
		for(int i=MAX(-x/256, 0); i<endW; i++)
		{
			dstX = x + i*256;
			dstY = y + j*256;
			DrawChunk(dstX, dstY, block[(i+j*width)*4+0]);
			DrawChunk(dstX + 128, dstY, block[(i+j*width)*4+1]);
			DrawChunk(dstX, dstY + 128, block[(i+j*width)*4+2]);
			DrawChunk(dstX + 128, dstY + 128, block[(i+j*width)*4+3]);
		}
	}
}
void Editor::Control::DrawLevel(short x, short y, short screenWidth, short screenHeight, short layer)
{
	short *block = getLevel()->map.GetLayer(layer);
	short width = getLevel()->map.Layer(layer)->width;
	short height = getLevel()->map.Layer(layer)->height;
	short endW = MIN(MAX(screenWidth - x + 127, 0) / 128, width*2);
	short endH = MIN(MAX(screenHeight - y + 127, 0) / 128, height*2);

	short dstX, dstY;
	for(int j=MAX(-y/128, 0); j<endH; j++)
	{
		for(int i=MAX(-x/128, 0); i<endW; i++)
		{
			dstX = x + i*128;
			dstY = y + j*128;
			switch(i&1 | ((j<<1)&2))
			{
			case 0:
				DrawChunk(dstX, dstY, block[((i/2)+(j/2)*width)*4+0]);
				break;
			case 1:
				DrawChunk(dstX, dstY, block[((i/2)+(j/2)*width)*4+1]);
				break;
			case 2:
				DrawChunk(dstX, dstY, block[((i/2)+(j/2)*width)*4+2]);
				break;
			case 3:
				DrawChunk(dstX, dstY, block[((i/2)+(j/2)*width)*4+3]);
				break;
			}
		}
	}
}

void Editor::Control::Draw()
{
	if (fadeOnLoseFocus)
	{
		if (getFocus())
		{
			if (fadefactor < 1.0f)
				fadefactor += 0.2f;
		}
		else
		{
			if (fadefactor > 0.4f)
				fadefactor -= 0.08f;
		}
		XeEffect::SetFadeFactor(fadefactor);
		XeEffect::SetSaturation(-fadefactor + 1.0f);
	}
	this->_Draw();

	Control *c;
	controlList.Last();
	while(controlList.Prev(&c))
	{
		if (c)
		{
			if (c->Visible())
			{
				if (c->getFocus())
				{
					XeEffect::SetProperties(0);
					XeShape::SetColor(MAKEARGB(0x80, 0x80, 0x80, 0xC0));
					XeShape::DrawRect(c->position.x - 1, c->position.y, 0.0f, c->size.width + 1, c->size.height);
					XeEffect::SetProperties(1);
				}
				c->Draw();
			}
		}
	}
	XeEffect::SetFadeFactor(1.0f);
	XeEffect::SetSaturation(0.0f);
}
void Editor::Control::InputWheel(short wheely)
{
	e->InputWheel(wheely);
}
bool Editor::Control::InputMouse(short x, short y, int button)
{
	if (this->_InputMouse(x, y, button)) return true;

	Control *c;
	controlList.First();
	while(controlList.Next(&c))
	{
		if (c)
		{
			if (c->Enable())
			{
				if (x < c->position.x || x >= c->position.x + c->size.width ||
					y < c->position.y || y >= c->position.y + c->size.height)
				{
					c->setFocus(false);
					continue;
				}
				c->setFocus(true);
				if (c->InputMouse(x - c->position.x, y - c->position.y, button))
					return true;
				continue;
			}
		}
	}
	return false;
}
bool Editor::Control::InputKeyb(int key, bool up)
{
	if (this->_InputKeyb(key, up)) return true;

	Control *c;
	controlList.First();
	while(controlList.Next(&c))
	{
		if (c)
		{
			if (c->Enable() && c->getFocus())
			{
				if (c->InputKeyb(key, up)) return true;
				else continue;
			}
		}
	}
	return false;
}
bool Editor::Control::InputKeyb(int key)
{
	if (this->_InputKeyb(key)) return true;

	Control *c;
	controlList.First();
	while(controlList.Next(&c))
	{
		if (c)
		{
			if (c->Enable() && c->getFocus())
			{
				if (c->InputKeyb(key)) return true;
				else continue;
			}
		}
	}
	return false;
}
bool Editor::Control::InputChar(int character)
{
	if (this->_InputChar(character)) return true;

	Control *c;
	controlList.First();
	while(controlList.Next(&c))
	{
		if (c)
		{
			if (c->Enable() && c->getFocus())
			{
				if (c->InputChar(character)) return true;
				else continue;
			}
		}
	}
	return false;
}