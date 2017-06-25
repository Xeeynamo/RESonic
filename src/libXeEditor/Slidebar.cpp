#include "Slidebar.h"

Editor::Slidebar::Slidebar(MainEditor *e, Control *parent, short x, short y, short width) : Control(e, parent, Position(x, y), Size(width, 0))
{
	m_name = "Slidebar";

	setSize(size);
	eChangeValue = 0;

	setMin(0);
	setMax(10);
	setValue(0);
}

int Editor::Slidebar::getMin()
{
	return min;
}
void Editor::Slidebar::setMin(int min)
{
	this->min = min;
}
int Editor::Slidebar::getMax()
{
	return max;
}
void Editor::Slidebar::setMax(int max)
{
	this->max = max;
	mod = (float)(size.width - font->GetWidth()) / (float)max;
}
int Editor::Slidebar::getValue()
{
	return value;
}
void Editor::Slidebar::setValue(int value)
{
	this->value = MIN(max, MAX(min, value));
	if (eChangeValue) eChangeValue(this, parent, value);
}
void Editor::Slidebar::setSize(Size size)
{
	if (size.width < font->GetWidth() * 2)
		size.width = font->GetWidth() * 2;
	size.height = font->GetHeight() + font->GetHeight() / 2;
	this->size = size;
	mod = (float)(size.width - font->GetWidth()) / (float)getMax();
}

void Editor::Slidebar::_Draw()
{
	u8 fontWidth = font->GetWidth();
	u8 fontWidthHalf = fontWidth / 2;
	u8 fontHeightHalf = font->GetHeight() / 2;
	for(int i = fontWidthHalf; i < size.width - fontWidthHalf; i += fontWidth)
		PrintChar(position.x + i, position.y + fontHeightHalf, 0xE4);
	PrintChar(position.x + (short)(mod * getValue()), position.y, 0xE2);
}
bool Editor::Slidebar::_InputKeyb(int key)
{
	setValue(getValue() - getWheelY() * 2);
	switch(key)
	{
	case VK_LEFT:
		setValue(getValue() - 1);
		return true;
	case VK_RIGHT:
		setValue(getValue() + 1);
		return true;
	case VK_UP:
		setValue(getValue() - 4);
		return true;
	case VK_DOWN:
		setValue(getValue() + 4);
		return true;
	case VK_PRIOR:
		setValue(getValue() - 8);
		return true;
	case VK_NEXT:
		setValue(getValue() + 8);
		return true;
	case VK_HOME:
		setValue(getMin());
		return true;
	case VK_END:
		setValue(getMax());
		return true;
	}
	return false;
}
bool Editor::Slidebar::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
		if (x < 4)
		{
			setValue(min);
			return true;
		}
		if (x >= size.width - 4)
		{
			setValue(max);
			return true;
		}
		setValue((int)(float((x-4))/mod));
		if (eChangeValue) eChangeValue(this, parent, value);
		break;
	}
	return true;
}