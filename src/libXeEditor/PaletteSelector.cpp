#include "PaletteSelector.h"
#include "..\libXeEngine\Texture.h"
#include "..\libXeEngine\Graphic.h"

Editor::PaletteSelector::PaletteSelector(MainEditor *e, Control *c, short x, short y, short size) : Control(e, c, Position(x, y), Size(size, size))
{
	m_name = "PaletteSelector";
	colorIndex = real_colorIndex = 0;
	lutIndex = 0;
	depthIndex = 0;
	u8 dataPaletteView[256];
	for(ptrdiff_t i = 0; i < 256; i++)
	{
		dataPaletteView[i] = i;
	}
	texPaletteView = new XeEngine::Texture;
	texPaletteView->Create(dataPaletteView, XeEngine::VideoPixelFormat_A8, 16, 16);

	setSize(this->size);
}
Editor::PaletteSelector::~PaletteSelector()
{
	SAFE_DELETE(texPaletteView);
}
void Editor::PaletteSelector::_Draw()
{
	XeEngine::Point pdst(position.x, position.y);
	XeEngine::Size sdst(256, 16);
	XeEngine::Point psrc(0, 0);
	XeEngine::Size ssrc(16, 1);
	for(int i  =0; i < 16; i++)
	{
		texPaletteView->Draw(pdst, sdst, psrc, ssrc, getLutIndex() | (getDepthIndex() << 8));
		pdst.y += 16;
		psrc.y ++;
	}
}
bool Editor::PaletteSelector::_InputKeyb(int key)
{
	switch(key)
	{
	case VK_LEFT:
		setLutIndex(getLutIndex() - 1);
		return true;
	case VK_RIGHT:
		setLutIndex(getLutIndex() + 1);
		return true;
	case VK_UP:
		setDepthIndex(getDepthIndex() - 1);
		return true;
	case VK_DOWN:
		setDepthIndex(getDepthIndex() + 1);
		return true;
	}
	return false;
}
bool Editor::PaletteSelector::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	colorIndex = (x / zoom) | ((y / zoom) << 4);
	if (button == XeEngine::MouseInput_LEFT)
	{
		real_colorIndex = colorIndex;
	}
	return true;
}
XeEngine::Color32 Editor::PaletteSelector::getColor()
{
	return XeEngine::Graphic::lut[depthIndex][lutIndex * XeEngine::paletteCount + colorIndex];
}
void Editor::PaletteSelector::setColor(XeEngine::Color32 color)
{
	XeEngine::Graphic::lut[depthIndex][lutIndex * XeEngine::paletteCount + colorIndex] = color;
}
byte Editor::PaletteSelector::getColorIndex() const
{
	return colorIndex;
}
void Editor::PaletteSelector::setColorIndex(byte index)
{
	colorIndex = index;
}
byte Editor::PaletteSelector::getLutIndex() const
{
	return lutIndex;
}
void Editor::PaletteSelector::setLutIndex(byte index)
{
	lutIndex = index;
}
byte Editor::PaletteSelector::getDepthIndex() const
{
	return depthIndex;
}
void Editor::PaletteSelector::setDepthIndex(byte index)
{
	if ((char)index < 0)
		index = XeEngine::clutCount - 1;
	else if (index >= XeEngine::clutCount)
		index = 0;
	depthIndex = index;
}

void Editor::PaletteSelector::setSize(Size size)
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