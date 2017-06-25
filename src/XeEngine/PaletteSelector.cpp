#include "PaletteSelector.h"

Editor::PaletteSelector::PaletteSelector(MainEditor *e, Control *c, short x, short y, short size) : Control(e, c, x, y, size)
{
	CtrlSize s;

	colorIndex = real_colorIndex = 0;
	lutIndex = 0;
	depthIndex = 1;

	m_name = "PaletteSelector";
	s.width = s.height = size;
	setSize(s);
}
void Editor::PaletteSelector::_Draw()
{
	getGame()->effect.SetProperties(0);
	XeScene::SetPosition(position.x, position.y);
	XeScene::SetScale(zoomf, zoomf);
	for(int i=0; i<16; i++)
	{
		getGame()->levelLUT.Draw(i*16, lutIndex, 16, 1, depthIndex, NULL);
		XeScene::MovePosition(0, 1);
	}
	getGame()->effect.SetProperties(1);
}
bool Editor::PaletteSelector::_InputKeyb(int key)
{
	switch(key)
	{
	case VK_LEFT:
		setLutIndex(getLutIndex()-1);
		return true;
	case VK_RIGHT:
		setLutIndex(getLutIndex()+1);
		return true;
	case VK_UP:
		setDepthIndex(getDepthIndex()-1);
		return true;
	case VK_DOWN:
		setDepthIndex(getDepthIndex()+1);
		return true;
	}
	return false;
}
bool Editor::PaletteSelector::_InputMouse(short x, short y, int button)
{
	colorIndex = (x/zoom) | ((y/zoom)<<4);
	if (button == 1)
	{
		real_colorIndex = colorIndex;
	}
	return true;
}

Color Editor::PaletteSelector::getColor()
{
	return getLevel()->palette[depthIndex][lutIndex][colorIndex];
}
void Editor::PaletteSelector::setColor(Color color)
{
	getLevel()->palette[depthIndex][lutIndex][colorIndex] = color;
}
byte Editor::PaletteSelector::getColorIndex()
{
	return colorIndex;
}
void Editor::PaletteSelector::setColorIndex(byte index)
{
	colorIndex = index;
}
byte Editor::PaletteSelector::getLutIndex()
{
	return lutIndex;
}
void Editor::PaletteSelector::setLutIndex(byte index)
{
	lutIndex = index;
}
byte Editor::PaletteSelector::getDepthIndex()
{
	return depthIndex;
}
void Editor::PaletteSelector::setDepthIndex(byte index)
{
	if ((char)index < 0)
		index = CLUT_COUNT - 1;
	else if (index >= CLUT_COUNT)
		index = 0;
	depthIndex = index;
}

void Editor::PaletteSelector::setSize(CtrlSize size)
{
	if (size.width < 0x10) size.width = 0x10;
	this->size.width = (size.width&~0xF);
	this->size.height = this->size.width;
	zoom = this->size.width >> 4;
	zoomf = (float)zoom;
}
void Editor::PaletteSelector::setFocus(bool focus)
{
	Control::setFocus(focus);
	colorIndex = real_colorIndex;
}