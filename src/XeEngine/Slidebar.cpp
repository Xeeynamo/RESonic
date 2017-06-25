#include "Slidebar.h"

Editor::Slidebar::Slidebar(MainEditor *e, Control *parent, short x, short y, short width) : Control(e, parent, x, y, width)
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
	mod = (float)(size.width-8) / (float)max;
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
void Editor::Slidebar::setSize(CtrlSize size)
{
	if (size.width < 16)
		size.width = 16;
	size.height = 12;
	this->size = size;
	mod = (float)(size.width-8) / (float)getMax();
}

void Editor::Slidebar::_Draw()
{
	XeEffect::SetProperties(1);
	XeEffect::SetClutDepth(0, CLUT_COUNT);
	for(int i=4; i<size.width-4; i+=8)
		PrintChar(position.x + i, position.y + 4, 0xE4);
	PrintChar(position.x + (short)(mod * getValue()), position.y, 0xE2);
}
bool Editor::Slidebar::_InputKeyb(int key)
{
	setValue(getValue() - getWheelY()*2);
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
bool Editor::Slidebar::_InputMouse(short x, short y, int button)
{
	switch(button)
	{
	case MK_LBUTTON:
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