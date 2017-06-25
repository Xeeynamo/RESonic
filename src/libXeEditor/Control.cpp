#include "MainEditor.h"
#include "..\libXeEngine\Font.h"
#include "..\libXeEngine\Level.h"
#include <stdio.h>

Editor::Control::Control(MainEditor *e, Control *parent, Position position, Size size)
{
	m_name = "Control";
	this->e = e;
	this->parent = parent;
	this->position = position;
	this->size = size;

	if (e) font = e->font;

	enabled = true;
	visible = true;
	m_highPriority = false;
	focus = false;
	collisionview = false;
	fadefactor = 1.0f;
	fadeOnLoseFocus = false;
}
Editor::Control::~Control()
{
	Control *c;
	controlList.MoveHead();
	while(controlList.Next(c))
		delete c;
}

Editor::Size Editor::Control::getSize()
{
	return size;
}
void Editor::Control::setSize(Editor::Size size)
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
Editor::Position Editor::Control::getMouseCoord()
{
	return e->getMouseCoord();
}
void Editor::Control::AddControl(Control *c)
{
	Position pos = c->getPosition();
	pos.x += this->position.x;
	pos.y += this->position.y;
	c->setPosition(pos);
	controlList.Add(c);
}

XeEngine::Game* Editor::Control::getGame()
{
	return e->getGame();
}
XeEngine::Level* Editor::Control::getLevel()
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
XeEngine::Effect* Editor::Control::GetControlEffect()
{
	return e->GetControlEffect();
}
XeEngine::Effect* Editor::Control::GetLevelEffect()
{
	return e->GetLevelEffect();
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
	font->PrintChar(x, y, c);
}
void Editor::Control::PrintText(short x, short y, const char* format, ...)
{
	char str[0x100];
	va_list args;
	va_start(args, format);
	vsprintf_s(str, format, args);
	font->SetXY(x, y);
	font->PrintText(str);
	va_end(args);
}
void Editor::Control::PrintTextAligned(short x, short y, const char* format, ...)
{
	char str[0x100];
	va_list args;
	va_start(args, format);
	vsprintf_s(str, format, args);
	font->SetXY(x * font->GetWidth(), y * font->GetHeight());
	font->PrintText(str);
	va_end(args);
}
void Editor::Control::TextColor(TEXTCOLOR color)
{
	e->TextColor(color);
}
void Editor::Control::SolidPalette(bool solid)
{
	getGame()->ClutSolid(solid, true);
}
void Editor::Control::DrawTile(short x, short y, short tile, byte palette, byte params)
{
	getGame()->DrawTile((float)x, (float)y, tile, palette, params);
}
void Editor::Control::DrawChunk(short x, short y, short chunk)
{
	getGame()->DrawChunk((float)x, (float)y, chunk);
	if (collisionview == 1)
	{
		//XeEffect::SetClutDepth(0, CLUT_COUNT);
		//XeEffect::SetClutIndex(0);
		//XeEffect::SetFadeFactor(0.5f);
		DrawChunkCollision(x, y, chunk);
		/*XeScene::Push();
		XeScene::MovePosition(0, -128);;
		_internal_DrawBlockCollision(chunk);
		XeScene::Pop();*/
		//XeEffect::SetFadeFactor(1.0f);
		//XeEffect::SetClutDepth(1, CLUT_COUNT);
	}
}
void Editor::Control::DrawChunkCollision(short x, short y, short chunk)
{
	/*TileEntry *tentry = getLevel()->chunk[chunk];
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
	}*/
}
void Editor::Control::DrawLevel256(short x, short y, short screenWidth, short screenHeight, short layer)
{
	/*short *block = getLevel()->map.GetLayer(layer);
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
	}*/
}
void Editor::Control::DrawLevel(short x, short y, short screenWidth, short screenHeight, XeEngine::MapLayer* mapLayer)
{

	/*short *block = getLevel()->map.GetLayer(layer);
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
	}*/
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
		//XeEffect::SetFadeFactor(fadefactor);
		//XeEffect::SetSaturation(-fadefactor + 1.0f);
	}
	this->_Draw();

	Control *c;
	controlList.MoveTail();
	while(controlList.Prev(c))
	{
		if (c)
		{
			if (c->Visible())
			{
				if (c->getFocus())
				{
					XeEngine::Shape::SetColor(0x80C08080);
					XeEngine::Shape::DrawRect(float(c->position.x - 1), float(c->position.y), 0.0f, float(c->size.width + 1), float(c->size.height));
				}
				c->Draw();
			}
		}
	}
	//XeEffect::SetFadeFactor(1.0f);
	//XeEffect::SetSaturation(0.0f);
}
void Editor::Control::InputWheel(short wheely)
{
	e->InputWheel(wheely);
}
bool Editor::Control::InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	if (this->_InputMouse(x, y, button))
		return true;

	Control *c;
	controlList.MoveHead();
	while(controlList.Next(c))
	{
		if (c)
		{
			if (c->Enable())
			{
				if (c->IsHighPriority() == false)
				{
					if (x < c->position.x || x >= c->position.x + c->size.width ||
						y < c->position.y || y >= c->position.y + c->size.height)
					{
						c->setFocus(false);
						continue;
					}
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
	controlList.MoveHead();
	while(controlList.Next(c))
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
	controlList.MoveHead();
	while(controlList.Next(c))
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
	controlList.MoveHead();
	while(controlList.Next(c))
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