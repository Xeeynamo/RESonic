#include "Sprite.h"
#include "Texture.h"
#include "Graphics.h"

XeEngine::Sprite::Sprite()
{
	created_texture = false;
	created_palette = false;
	m_opacity = 1.0f;

	m_texture = NULL;

	m_texWidth = m_texHeight = 0.0f;

	m_listFrame.Add(SpriteFrame());
	SetFrame(0);
	SetColor(XeEngine::Color(XeEngine::ColorARGB(0xFFFFFFFF)));
}
XeEngine::Sprite::~Sprite()
{
	Destroy();
}
void XeEngine::Sprite::Destroy()
{
	if (created_texture == true)
	{
		SAFE_DELETE(m_texture);
	}
}
void XeEngine::Sprite::SelfDraw()
{
	Node::SelfDraw();

	Video::SelectTexture(m_texture->GetID());

	Vertex pos[4];
	pos[0].x = coord.x + vPos[0].x;
	pos[0].y = coord.y + vPos[0].y;
	pos[1].x = coord.x + vPos[1].x;
	pos[1].y = coord.y + vPos[1].y;
	pos[2].x = coord.x + vPos[2].x;
	pos[2].y = coord.y + vPos[2].y;
	pos[3].x = coord.x + vPos[3].x;
	pos[3].y = coord.y + vPos[3].y;

	Graphic::SendVertex2D(pos, vTex);
	Graphic::Flush2D();
}

void XeEngine::Sprite::AttachTexture(Texture& tex)
{
	created_texture = false;
	m_texture = &tex;

	m_texWidth = (float)m_texture->GetWidth();
	m_texHeight = (float)m_texture->GetHeight();
}
void XeEngine::Sprite::CreateTexture(Texture* tex)
{
	created_texture = true;
	m_texture = tex;

	m_texWidth = (float)m_texture->GetWidth();
	m_texHeight = (float)m_texture->GetHeight();
}
void XeEngine::Sprite::LoadPalette(String& filename)
{
	created_palette = Graphic::SetEntityPalette(filename, GetID());
}

void XeEngine::Sprite::GetColor(Color& color) const
{
	//color = Color(ColorARGB(vertex->color.r, vertex->color.g, vertex->color.b, vertex->color.a));
}
void XeEngine::Sprite::SetColor(const Color& color)
{
	/*vertex[0].color.r = vertex[1].color.r = vertex[2].color.r = vertex[3].color.r = color.r;
	vertex[0].color.g = vertex[1].color.g = vertex[2].color.g = vertex[3].color.g = color.g;
	vertex[0].color.b = vertex[1].color.b = vertex[2].color.b = vertex[3].color.b = color.b;
	vertex[0].color.a = vertex[1].color.a = vertex[2].color.a = vertex[3].color.a = color.a * m_opacity;*/
}
float XeEngine::Sprite::GetOpacity() const
{
	//return vertex[0].color.a;
	return m_opacity;
}
void XeEngine::Sprite::SetOpacity(float opacity)
{
	m_opacity = opacity;
	//vertex[0].color.a = vertex[1].color.a = vertex[2].color.a = vertex[3].color.a = m_opacity;
}

void XeEngine::Sprite::CreateFrame(short srcx, short srcy, short width, short height, short centerx, short centery, short palette)
{
	m_listFrame.Add
	(
		SpriteFrame((float)srcx / m_texWidth,		(float)srcy / m_texHeight,
			(float)(srcx + width) / m_texWidth,		(float)(srcy + height) / m_texHeight,
			(float)-centerx, (float)-centery,
			((float)Graphic::GetEntityPalette(GetID(), palette) + 0.5f) / (float)(clutCount * paletteCount),
			(float)width, (float)height)
	);
}
void XeEngine::Sprite::SetFrame(u16 frame)
{
	SpriteFrame spriteFrame = m_listFrame[frame];

	vTex[0].u = spriteFrame.startx;
	vTex[0].v = spriteFrame.starty;
	vTex[1].u = spriteFrame.endx;
	vTex[1].v = spriteFrame.starty;
	vTex[2].u = spriteFrame.startx;
	vTex[2].v = spriteFrame.endy;
	vTex[3].u = spriteFrame.endx;
	vTex[3].v = spriteFrame.endy;
	vTex[0].w = vTex[1].w = vTex[2].w = vTex[3].w = spriteFrame.palette;

	vPos[0].x = spriteFrame.centerx;
	vPos[0].y = spriteFrame.centery;
	vPos[1].x = spriteFrame.centerx + spriteFrame.width;
	vPos[1].y = spriteFrame.centery;
	vPos[2].x = spriteFrame.centerx;
	vPos[2].y = spriteFrame.centery + spriteFrame.height;
	vPos[3].x = spriteFrame.centerx + spriteFrame.width;
	vPos[3].y = spriteFrame.centery + spriteFrame.height;

	m_frame = frame;
}
