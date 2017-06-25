#include "HitboxShape.h"
#include "HitboxEditor.h"

Editor::HitboxShape::HitboxShape(MainEditor *e, Control *c, short x, short y, short size) : Control(e, c, Position(x, y), Size(size, size))
{
	m_name = "HitboxShape";
	setSize(this->size);

	m_index = 0;
	m_verse = 0;
}
void Editor::HitboxShape::_Draw()
{
	e->DrawCollision(m_index, m_verse ? 1 : 0, XeEngine::Point(position.x, position.y), XeEngine::Size(size.width, size.height));
}
bool Editor::HitboxShape::_InputKeyb(int key)
{
	return false;
}
bool Editor::HitboxShape::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	if (button == XeEngine::MouseInput_LEFT || button == XeEngine::MouseInput_RIGHT || button == XeEngine::MouseInput_MIDDLE)
	{
		u8 border = size.width / 16 / 4;
		XeEngine::Collision* col = (GetVerse() ? getLevel()->hitboxWall : getLevel()->hitboxFloor);
		s8* i = &col[GetIndex()][x / (size.width / 16)];
		switch(button)
		{
		case XeEngine::MouseInput_LEFT:
			*i = 0x10 - (y / (size.height / 16));
			if (y >= size.height - border)
				*i = 0;
			break;
		case XeEngine::MouseInput_RIGHT:
			*i = y / (size.height / -16) - 1;
			if (y <= border)
				*i = 0;
			break;
		case XeEngine::MouseInput_MIDDLE:
			*i = 0;
			break;
		}
	}
	return false;
}
u8 Editor::HitboxShape::GetIndex() const
{
	return m_index;
}
void Editor::HitboxShape::SetIndex(u8 index)
{
	m_index = index;
}
u8 Editor::HitboxShape::GetVerse() const
{
	return m_verse;
}
void Editor::HitboxShape::SetVerse(u8 verse)
{
	m_verse = verse;
}

void Editor::HitboxShape::setSize(Size size)
{
	size.width &= (~0xF);
	if (size.width < 0x10)
		size.width = 0x10;
	this->size.width = this->size.height = size.width;
}