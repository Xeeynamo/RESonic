#pragma once
#include "OGL.h"

struct XeShape_Coord;
class XeShape
{
private:
protected:
public:
	static void Initialize();
	static void Color2Float(unsigned int colori, XeShape_Coord *coord);

	static void SetTextureID(unsigned int id);
	static void SetColor(unsigned int color);
	static void SetColorArray(unsigned int color1, unsigned int color2, unsigned int color3, unsigned int color4);
	static void DrawRect(short x, short y, float depth, short width, short height);
	static void DrawRect(short width, short height);
	static void FillRect(short x, short y, float depth, short width, short height);
	static void FillRect(short width, short height);

	static void FadeInit(int length, int verse, unsigned int color);
	static void FadeEffect();
	static void FadeOut();
};