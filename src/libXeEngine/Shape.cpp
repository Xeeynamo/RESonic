#include "Shape.h"
#include "Texture.h"
#include "Graphics.h"

namespace XeEngine
{
	Vertex v[5];
	Texture* texture = nullptr;
}

void XeEngine::Shape::Initialize()
{
	if (texture != nullptr) return;

	Color32 color[1] = {1};
	texture = new Texture();
	texture->Create((MemoryHandle)color, PixelFormat_A8, 1, 1);
	v[0].color = v[1].color = v[2].color = v[3].color = v[4].color =
		0xFFFFFFFF;
	v[0].u = v[0].v = 0.0f;
	v[1].u = v[1].v = 0.0f;
	v[2].u = v[2].v = 0.0f;
	v[3].u = v[3].v = 0.0f;
	v[4].u = v[4].v = 0.0f;
	v[1].u = v[2].v = v[2].u = v[3].v = v[4].v = 1.0f;
	v[0].palette = v[1].palette = v[2].palette = v[3].palette = v[4].palette = 0.0f;
}
void XeEngine::Shape::SetColor(unsigned int color)
{
	SetColorArray(color, color, color, color);
}
void XeEngine::Shape::SetColorArray(unsigned int color1, unsigned int color2, unsigned int color3, unsigned int color4)
{
	v[0].color = color1;
	v[1].color = color2;
	v[2].color = color3;
	v[3].color = color4;
	v[4].color = color1;
}
void XeEngine::Shape::DrawRect(float x, float y, float z, float width, float height)
{
	v[0].x = v[3].x = x;
	v[0].y = v[1].y = y;
	v[1].x = v[2].x = x + width;
	v[2].y = v[3].y  = y + height;
	v[4].x = v[0].x;
	v[4].y = v[0].y;

	Video::SelectTexture(texture->GetID());
	Video::SendVertices(v, 4, Primitives_LineStrip);
}
void XeEngine::Shape::FillRect(float x, float y, float z, float width, float height)
{
	v[0].x = v[3].x = x;
	v[0].y = v[1].y = y;
	v[1].x = v[2].x = x + width;
	v[2].y = v[3].y  = y + height;

	Video::SelectTexture(texture->GetID());
	Video::SendVertices(v, 4, Primitives_TriangleStrip);
}