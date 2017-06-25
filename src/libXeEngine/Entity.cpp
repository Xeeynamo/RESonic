#include "Entity.h"

namespace XeEngine
{
	Entity::Entity()
	{
		m_curframe.x = 0;
		m_curframe.y = 0;
		m_curframe.w = 0;
		m_curframe.h = 0;
		m_curframe.cx = 0;
		m_curframe.cy = 0;
		m_curframe.pal = 0;
		m_gfxid = 0;
		m_color = 0xFFFFFFFF;
	}
	Entity::~Entity()
	{
	}
	
	void Entity::SelfDraw()
	{
		Graphics::DrawSpriteRotation(m_gfxid, x - m_curframe.cx, y - m_curframe.cy, m_curframe.w, m_curframe.h, m_curframe.x, m_curframe.y,
			m_curframe.cx, m_curframe.cy, m_rotx, m_roty, m_rotz);
	}

	void Entity::AttachTexture(const Graphics::GraphicID id)
	{
		m_gfxid = id;
		if (m_curframe.w == 0 && m_curframe.h == 0)
		{
			Graphics::ImageInfo info;
			Graphics::GetImageInfo(m_gfxid, info);
			m_curframe.x = 0;
			m_curframe.y = 0;
			m_curframe.w = info.width;
			m_curframe.h = info.height;
			m_curframe.cx = info.width / 2;
			m_curframe.cy = info.height / 2;
		}
	}
	Graphics::GraphicID Entity::RemoveTexture()
	{
		Graphics::GraphicID id = m_gfxid;
		m_gfxid = 0;
		return id;
	}

	void Entity::CreateFrame(short srcx, short srcy, short width, short height, short centerx, short centery, short palette)
	{
		Frame frame;
		frame.x = srcx;
		frame.y = srcy;
		frame.w = width;
		frame.h = height;
		frame.cx = centerx;
		frame.cy = centery;
		frame.pal = palette;
		m_frames.Add(frame);
	}
	void Entity::SetFrame(u16 index)
	{
		m_curframe = m_frames[index];
	}
	void Entity::DeleteAllFrames()
	{
		m_frames.RemoveAll();
	}

	Color Entity::GetColor() const
	{
		return m_color & 0x00FFFFFF;
	}
	void Entity::SetColor(Color c)
	{
		m_color = (m_color & 0xFF000000) | (c & 0x00FFFFFF);
	}
	float Entity::GetOpacity() const
	{
		return (float)(m_color >> 24) / 255.0f;
	}
	void Entity::SetOpacity(float opacity)
	{
		m_color = GetColor() | ((u32)(opacity * 255.0f) << 24);
	}
}