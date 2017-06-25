#include "GFXLib.h"

#define GFX_MAXIMUM_VERSION_SUPPORTED	1
#define GFX_SHIFTING_SIZE	3

GFXLib::GFXLib()
{
	_version = GFX_MAXIMUM_VERSION_SUPPORTED;
	((int*)(&_header))[0] = 0;
	((int*)(&_header))[1] = 0;
}
GFXLib::~GFXLib()
{

}

char GFXLib::GetVersion()
{
	return _version;
}
void GFXLib::SetVersion(char version)
{
	if (version == 0 || version > GFX_MAXIMUM_VERSION_SUPPORTED)
		return;
	_version = version;
	switch(version)
	{
	case 1:
		_header.headersize = 8;
	default:
		_header.headersize = 0;
	}
}

int GFXLib::GetSize()
{
	return (int)((_header.width<<GFX_SHIFTING_SIZE) | (_header.height<<(GFX_SHIFTING_SIZE+16)));
}
void GFXLib::SetSize(short width, short height)
{
	_header.width = width>>GFX_SHIFTING_SIZE;
	_header.height = height>>GFX_SHIFTING_SIZE;
}
char GFXLib::GetResolution()
{
	return _version;
}
void GFXLib::SetResolution(char resolution)
{
	_header.resolution = resolution;
}
unsigned char GFXLib:: GetTextureCount()
{
	return _header.texturecount;
}
void GFXLib::SetTextureCount(unsigned char count)
{
	_header.texturecount = count;
}
unsigned char GFXLib::GetDestination()
{
	return _header.dstindex;
}
void GFXLib::SetDestination(unsigned char dstindex)
{
	_header.dstindex = dstindex;
}
GFXMode GFXLib::GetGFXMode()
{
	return (GFXMode)_header.mode;
}
void GFXLib::SetGFXMode(GFXMode mode)
{
	if (mode == -1)
		mode = GFXMode_Undefined;
	_header.mode = (unsigned char)mode;
}
bool GFXLib::GetFlagCompressed()
{
	return _header.compressed;
}
void GFXLib::SetFlagCompressed(bool enabled)
{
	_header.compressed = enabled;
}
bool GFXLib::GetFlagInternalPalette()
{
	return _header.internalpalette;
}
void GFXLib::SetFlagInternalPalette(bool enabled)
{
	_header.internalpalette = enabled;
}

bool GFXLib::OpenGFX()
{
	int version;
	Seek(SEEK_SET, 0);
	switch(version = CheckMagiccode("GFX", GFX_MAXIMUM_VERSION_SUPPORTED))
	{
	case 1:
		Read(sizeof(_header), &_header);
		break;
	case 0:
	default:
		return false;
	}
	_version = version;
	return true;
}
void GFXLib::SaveGFX()
{
	Seek(SEEK_SET, 0);
	WriteMagicCode("GFX", _version);
	Write(sizeof(_header), &_header);
}