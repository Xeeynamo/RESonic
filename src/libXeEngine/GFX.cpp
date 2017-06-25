#include "GFX.h"

bool XeEngine::ImageFramework::GFX(Image& image, void* data, size_t size)
{
	static const u8 FormatSize[] = {1, 4, 8, 16, 24, 32};
	static const PixelFormat FormatPixel[] =
	{ PixelFormat_A8, PixelFormat_A8, PixelFormat_A8, PixelFormat_A8,
	PixelFormat_RGB5A1, PixelFormat_RGB888, PixelFormat_RGBA8888 };
	static const u8 FormatGfx[] = { 6, 5, 0, 4, 0, 2, 0, 0};
	static GFXStruct gfxstruct;
	static size_t remainsbyte;

	switch(image.m_function)
	{
	case Image::Function_Open:
		if (image.m_file.Open((const char*)data, true) == false) return false;
		image.m_file.Read(&gfxstruct, sizeof(GFXStruct));
		image.m_width = gfxstruct.width == 0 ? 1024 : gfxstruct.width * 4;
		image.m_height = gfxstruct.height == 0 ? 1024 : gfxstruct.height * 4;
		image.m_format = FormatPixel[gfxstruct.format];
		image.m_resolution = gfxstruct.resolution;
		image.m_count = gfxstruct.texturecount;
		remainsbyte = image.m_width * image.m_height *
			image.m_resolution * image.m_count *
			FormatSize[gfxstruct.format] / 8;
		return true;
	case Image::Function_Save:
		if (image.m_file.Create((const char*)data) == false) return false;
		if ((image.m_width & 3) || (image.m_width > 1024) ||
			(image.m_height & 3) || (image.m_height > 1024) ||
			image.m_count == 0 || image.m_resolution == 0)
			return false;
		gfxstruct.headersize = sizeof(GFXStruct);
		gfxstruct.width = (image.m_width / 4);
		gfxstruct.height = (image.m_height / 4);
		gfxstruct.format = FormatGfx[image.m_fileformat];
		gfxstruct.texturecount = (byte)image.m_count;
		gfxstruct.dstindex = 0;
		gfxstruct.flags = 0;
		image.m_file.Write(&gfxstruct, sizeof(GFXStruct));
		return true;
	case Image::Function_Read:
		{
			if (size < 8) return false;
			size_t bytesToRead = size * FormatSize[gfxstruct.format] / 8;
			if (bytesToRead >= remainsbyte)
				bytesToRead = remainsbyte;

			switch(gfxstruct.format)
			{
			case 1: // Monochrome
				{
					u8 bufSize[1024];
					unsigned char* dstData = (unsigned char*)data;
					while(bytesToRead > 0)
					{
						size_t readn;
						if (bytesToRead > 1024 * 4)
							readn = 1024 * 4;
						else
							readn = bytesToRead;
						bytesToRead -= readn;

						image.m_file.Read(bufSize, readn);
						for(size_t i = 0; i < readn / 8; i++)
						{
							dstData[i*8+0] = (bufSize[i] & 128) != 0;
							dstData[i*8+1] = (bufSize[i] & 64) != 0;
							dstData[i*8+2] = (bufSize[i] & 32) != 0;
							dstData[i*8+3] = (bufSize[i] & 16) != 0;
							dstData[i*8+4] = (bufSize[i] & 8) != 0;
							dstData[i*8+5] = (bufSize[i] & 4) != 0;
							dstData[i*8+6] = (bufSize[i] & 2) != 0;
							dstData[i*8+7] = (bufSize[i] & 1) != 0;
						}
					}
				} 
				break;
			case 2: // 4bpp
				{
					u8 bufSize[1024];
					unsigned char* dstData = (unsigned char*)data;
					while(bytesToRead > 0)
					{
						size_t readn;
						if (bytesToRead > 1024 * 4)
							readn = 1024 * 4;
						else
							readn = bytesToRead;
						bytesToRead -= readn;

						readn >>= 1;
						image.m_file.Read(bufSize, readn);
						for(size_t i = 0; i < readn; i++)
						{
							dstData[i*2+0] = bufSize[i] & 0xF;
							dstData[i*2+1] = bufSize[i] >> 4;
						}
					}
				}
				break;
			case 3: // 8bpp
			case 4: // 16 bit
			case 5: // 24 bit
			case 6: // 32 bit
				image.m_file.Read(data, size);
				return true;
			default:
				return false;
			}
		}
		return true;
	case Image::Function_Write:
		image.m_file.Write(data, size);
		image.m_file.Close();
		return true;
	case Image::Function_Rewind:
		image.m_file.Seek(sizeof(GFXStruct), FILESEEK_SET);
		return true;
	}
	return false;
}