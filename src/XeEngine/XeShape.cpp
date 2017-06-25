#include "XeShape.h"
#include "XeScene.h"
#include "XeEffect.h"

struct XeShape_Coord
{
	float x, y, z;
	float u, v;
	float r, g, b, a;
};

XeShape_Coord xeshape_coord[4];
int xeshape_textureid;
int xeshape_fade_frameindex;
int xeshape_fade_framelength;
int xeshape_fade_originalsize;
int xeshape_fade_verse;

void XeShape::Initialize()
{
	xeshape_fade_verse = 0;
	xeshape_coord[0].x = 0.0f;
	xeshape_coord[0].y = 0.0f;
	xeshape_coord[1].x = 0.0f;
	xeshape_coord[1].y = 0.0f;
	xeshape_coord[2].x = 0.0f;
	xeshape_coord[2].y = 0.0f;
	xeshape_coord[3].x = 0.0f;
	xeshape_coord[3].y = 0.0f;
	xeshape_coord[0].z = xeshape_coord[1].z = xeshape_coord[2].z = xeshape_coord[3].z = 0.0f;

	xeshape_coord[0].u = xeshape_coord[0].v = 0.0f;
	xeshape_coord[1].u = 1.0f;
	xeshape_coord[1].v = 0.0f;
	xeshape_coord[2].u = 1.0f;
	xeshape_coord[2].v = 1.0f;
	xeshape_coord[3].u = 0.0f;
	xeshape_coord[3].v = 1.0f;
}
void XeShape::Color2Float(unsigned int colori, XeShape_Coord *coord)
{
	coord->r = float((colori>>0) & 0xFF) / 255.0f;
	coord->g = float((colori>>8) & 0xFF) / 255.0f;
	coord->b = float((colori>>16) & 0xFF) / 255.0f;
	coord->a = float((colori>>24) & 0xFF) / 255.0f;
}
void XeShape::SetTextureID(unsigned int id)
{
	xeshape_textureid = id;
}
void XeShape::SetColor(unsigned int color)
{
	SetColorArray(color, color, color, color);
}
void XeShape::SetColorArray(unsigned int color1, unsigned int color2, unsigned int color3, unsigned int color4)
{
	Color2Float(color1, xeshape_coord+0);
	Color2Float(color2, xeshape_coord+1);
	Color2Float(color3, xeshape_coord+2);
	Color2Float(color4, xeshape_coord+3);
}
void XeShape::DrawRect(short x, short y, float depth, short width, short height)
{
	XeScene::SetPosition(x, y, depth);
	DrawRect(width, height);
}
void XeShape::DrawRect(short width, short height)
{
	xeshape_coord[1].x = xeshape_coord[2].x = width;
	xeshape_coord[2].y = xeshape_coord[3].y = height;

	XeScene::Bind3DTexture(xeshape_textureid);
	glVertexPointer(3, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].x);
	glColorPointer(4, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].r);
	glTexCoordPointer(2, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].u);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}
void XeShape::FillRect(short x, short y, float depth, short width, short height)
{
	XeScene::SetPosition(x, y, depth);
	FillRect(width, height);
}
void XeShape::FillRect(short width, short height)
{
	xeshape_coord[1].x = xeshape_coord[2].x = width;
	xeshape_coord[2].y = xeshape_coord[3].y = height;

	XeScene::Bind3DTexture(xeshape_textureid);
	glVertexPointer(3, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].x);
	glColorPointer(4, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].r);
	glTexCoordPointer(2, GL_FLOAT, sizeof(XeShape_Coord), &xeshape_coord[0].u);
	glDrawArrays(GL_QUADS, 0, 4);
}


void XeShape::FadeInit(int length, int verse, unsigned int color)
{
	xeshape_fade_frameindex = verse ? 0 : (length+1);
	xeshape_fade_framelength = length;
	xeshape_fade_verse = verse;
	XeScene::Push();
	XeScene::SetProjection(1, 1, 16.0f);
	XeShape::SetColorArray(color, color, color, color);
	XeScene::Pop();
}
void XeShape::FadeEffect()
{
	if (xeshape_fade_framelength == 0) return;
	if (xeshape_fade_framelength < 0) return;
	if (xeshape_fade_frameindex >= xeshape_fade_framelength)
		xeshape_fade_frameindex = xeshape_fade_framelength;
	xeshape_fade_frameindex += xeshape_fade_verse ? +1 : -1;

	XeEffect::SetFadeFactor(float(xeshape_fade_frameindex)/float(xeshape_fade_framelength));
	XeShape::FillRect(0, 0, 2.0f, 1024, 1024);
}
void XeShape::FadeOut()
{
	XeShape::FillRect(1024, 1024);
}