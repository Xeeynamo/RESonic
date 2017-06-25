#include "GFX.h"

GFX::GFX()
{
	XeEngine::MemoryFill(&gfxstruct, sizeof(GFXStruct));
}
GFX::~GFX()
{
	
}

bool GFX::Load(XeEngine::String& filename)
{
	XeEngine::Memory tmp;
	XeEngine::File f;
	if (!f.Open(filename, true)) return false;
	f.Read(&gfxstruct, sizeof(GFXStruct));
	width = (gfxstruct.width == 0 ? 256 : gfxstruct.width*4)*gfxstruct.resolution;
	height = (gfxstruct.height == 0 ? 256 : gfxstruct.height*4)*gfxstruct.resolution;
	resolution = gfxstruct.resolution;
	texcount = gfxstruct.texturecount;
	
	int size = width*height*resolution*gfxstruct.texturecount;

	switch(gfxstruct.mode)
	{
	case 1: // Monochrome
		{
			format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8;
			data.Alloc(size);
			tmp.Alloc(size/8);
			f.Read(tmp.GetMemoryHandle(), size/8);

			u8* srcData = (u8*)tmp.GetMemoryHandle();
			u8* dstData = (u8*)data.GetMemoryHandle();
			for(int i=0; i<size/8; i++)
			{
				dstData[i*8+0] = (srcData[i] & 128) != 0;
				dstData[i*8+1] = (srcData[i] & 64) != 0;
				dstData[i*8+2] = (srcData[i] & 32) != 0;
				dstData[i*8+3] = (srcData[i] & 16) != 0;
				dstData[i*8+4] = (srcData[i] & 8) != 0;
				dstData[i*8+5] = (srcData[i] & 4) != 0;
				dstData[i*8+6] = (srcData[i] & 2) != 0;
				dstData[i*8+7] = (srcData[i] & 1) != 0;
			}
			tmp.Free();
		} 
		break;
	case 2: // 4bpp
		{
			format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8;
			data.Alloc(size);
			tmp.Alloc(size/2);
			f.Read(tmp.GetMemoryHandle(), size/2);

			u8* srcData = (u8*)tmp.GetMemoryHandle();
			u8* dstData = (u8*)data.GetMemoryHandle();
			for(int i=0; i<size/2; i++)
			{
				dstData[i*2+0] = srcData[i] & 0xF;
				dstData[i*2+1] = srcData[i] >> 4;
			}
			tmp.Free();
		}
		break;
	case 3: // 8bpp
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8;
		data.Alloc(size);
		f.Read(data.GetMemoryHandle(), size);
		break;
	case 4: // 16 bit
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB565;
		data.Alloc(width*height*2);
		f.Read(data.GetMemoryHandle(), size*2);
		break;
	case 5: // 24 bit
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGB888;
		data.Alloc(size*3);
		f.Read(data.GetMemoryHandle(), size*3);
		break;
	case 6: // 32 bit
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA8888;
		data.Alloc(size*4);
		f.Read(data.GetMemoryHandle(), size*4);
		break;
	default:
		format = XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_Default;
	}
	f.Close();
	return true;
}
int GFX::Count()
{
	return gfxstruct.texturecount;
}
int GFX::DestinationIndex()
{
	return gfxstruct.dstindex;
}