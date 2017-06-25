#include "LUT.h"
#include "XeEngineLV1.h"

LUT::LUT()
{

}
LUT::~LUT()
{

}

bool LUT::Load(char *filename)
{
	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename), true)) return false;
	f.Read(&header, sizeof(LUTStruct));
	data.Alloc((header.count ? header.count : 256) * (header.format>>3) * (header.colorsperpal ? 256 : 16));
	lut = data.GetMemoryHandle();
	f.Read(lut, data.Size());
	blut = (byte*)lut;
	wlut = (ushort*)lut;
	dlut = (uint*)lut;
	return true;
}

uint LUT::UnpackColor(byte index, byte palette)
{
	int pos = index + (palette*ColorsPerPalette());
	switch((LUTFormat)header.format)
	{
	case LUTFormat_RGB332:
		break;
	case LUTFormat_BGR233:
		break;
	case LUTFormat_ARGB2222:
		break;
	case LUTFormat_BGRA2222:
		break;
	// 16 bit per color
	case LUTFormat_RGB565:
		return ( ((wlut[pos]&0x1F)<<3) |  ((wlut[pos]&0x7E0)<<5) |  ((wlut[pos]&0xF800)<<8) | 0xFF000000 );
	case LUTFormat_BGR565:
		break;
	case LUTFormat_XRGB1555:
		return ( ((wlut[pos]&0x1F)<<3) |  ((wlut[pos]&0x3E0)<<6) |  ((wlut[pos]&0x7C00)<<9) | 0xFF000000 );
	case LUTFormat_XBGR1555:
		return ( ((wlut[pos]&0x1F)<<19) |  ((wlut[pos]&0x3E0)<<6) |  ((wlut[pos]&0x7C00)>>7) | 0xFF000000 );
		break;
	case LUTFormat_ARGB1555:
		return ( ((wlut[pos]&0x1F)<<3) |  ((wlut[pos]&0x3E0)<<6) |  ((wlut[pos]&0x7C00)<<9) | 0xFF000000 );
	case LUTFormat_BGRA5551:
		break;
	case LUTFormat_ARGB4444:
		break;
	case LUTFormat_BGRA4444:
		break;
	// 24 bit per color
	case LUTFormat_RGB888:
		break;
	case LUTFormat_BGR888:
		break;
	case LUTFormat_ARGB1887:
		break;
	case LUTFormat_BGRA8871:
		break;
	// 32 bit per color
	case LUTFormat_XRGB8888:
	case LUTFormat_BGRX8888:
		return dlut[pos] | 0xFF000000;
		break;
	case LUTFormat_ARGB8888:
	case LUTFormat_BGRA8888:
		return dlut[pos];
		break;
	}
	return 0;
}
short LUT::PaletteCount()
{
	return header.count == 0 ? 256 : header.count;
}
byte LUT::DestinationIndex()
{
	return header.destination;
}
byte LUT::Format()
{
	return header.format;
}
short LUT::ColorsPerPalette()
{
	return (header.colorsperpal&1) == 1 ? 256 : 16;
}