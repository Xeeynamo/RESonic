#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class Texture;
	class Font
	{
	private:
	protected:
		Texture* texFont;
		short x;
		short y;
		u16 m_palette;
		u8 charWidth, charHeight;
	public:
		Font();
		~Font();

		u8 GetWidth() const;
		u8 GetHeight() const;
		void SetTexture(Texture&);
		void SetPalette(u16, u8 = 0);
		void SetXY(short x, short y);
		void PrintChar(short x, short y, char);
		void PrintText(char*);
	};
}