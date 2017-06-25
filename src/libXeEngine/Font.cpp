#include "Font.h"
#include "Texture.h"
#include "Graphics.h"

XeEngine::Font::Font()
{
	texFont = nullptr;
	x = y = 0;
	charWidth = 0;
	charHeight = 0;
	m_palette = 0;
}
XeEngine::Font::~Font()
{

}

u8 XeEngine::Font::GetWidth() const
{
	return charWidth;
}
u8 XeEngine::Font::GetHeight() const
{
	return charHeight;
}
void XeEngine::Font::SetTexture(Texture& texture)
{
	texFont = &texture;
	charWidth = texture.GetWidth() / 16;
	charHeight = texture.GetHeight() / 16;
}
void XeEngine::Font::SetPalette(u16 palette, u8 section)
{
	m_palette = palette | (section << 8);
}
void XeEngine::Font::SetXY(short x, short y)
{
	this->x = x;
	this->y = y;
}
void XeEngine::Font::PrintChar(short x, short y, char character)
{
	texFont->Draw
		(
		Point(x, y, 4.0f),
		Point((float)(character & 0xF) * charWidth, (float)(character >> 4) * charHeight),
		Size(charWidth, charHeight), m_palette
		);
}
void XeEngine::Font::PrintText(char *str)
{
	if (texFont == nullptr)
		return;

	for(ptrdiff_t i = 0; str[i]; i++)
	{
		switch (str[i])
		{
		case '\t':
			x += (4 * charWidth);
			break;
		case '\n':
			y += charHeight;
		case '\r':
			x = 0;
			break;
		case ' ':
			x += charWidth;
			break;
		default:
			PrintChar(x, y, str[i]);
			x += charWidth;
		}
	}
}