#include "TGA.h"
#include "XeFile.h"

TGA::TGA()
{
	XeEngine::MemoryFill(&tgastruct, sizeof(TGAStruct));
}
TGA::~TGA()
{

}

bool TGA::Load(XeEngine::String& filename)
{
	XeEngine::File f;
	if (!f.Open(filename, true)) return false;
	f.Read(&tgastruct, sizeof(TGAStruct));
	if (tgastruct.dataTypeCode != 2)
	{
		// Compressed format not supported
		f.Close();
		return false;
	}
	switch(tgastruct.bpp)
	{
	case 24:
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGR888;
		break;
	case 32:
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_BGRA8888;
		break;
	default:
		// Formats differents from 24bpp not supported
		f.Close();
		return false;
	}
	f.Seek(tgastruct.idLength, XeEngine::FILESEEK_CUR);
	f.Seek(tgastruct.colormapLength * (tgastruct.colormapDepth/8), XeEngine::FILESEEK_CUR);
	width = tgastruct.width;
	height = tgastruct.height;
	int pixelSize = width * height * (tgastruct.bpp/8);
	data.Alloc(pixelSize);
	f.Read(data.GetMemoryHandle(), pixelSize);
	f.Close();
	return true;
}