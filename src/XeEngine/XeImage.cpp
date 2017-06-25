#include "XeImage.h"
#include <windows.h>

XeEngine::XeImage::XeImage()
{
	resolution = 1;
	texcount = 1;
}
XeEngine::XeImage::~XeImage()
{

}

short XeEngine::XeImage::GetWidth() const
{
	return width;
}
short XeEngine::XeImage::GetHeight() const
{
	return height;
}
short XeEngine::XeImage::GetTextureCount() const
{
	return texcount;
}
char XeEngine::XeImage::GetResolution() const
{
	return resolution;
}
XeEngine::XeTexturePixelFormat XeEngine::XeImage::GetFormat() const
{
	return format;
}
XeEngine::MemoryHandle XeEngine::XeImage::GetData() const
{
	return data.GetMemoryHandle();
}