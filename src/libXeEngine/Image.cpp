#include "Image.h"

namespace XeEngine
{
	const u8 Image::VideoFormatSize[] =
	{
		32, 24, 16, 16, 16, 8, 16
	};
	size_t Image::countImageFormat = 0;
	ImageFormat Image::listImageFormat[16];

	void Image::AddImageFormat(const ImageFormat& imgformat)
	{
		listImageFormat[countImageFormat++] = imgformat;
	}

	Image::Image()
	{
		Reset();
	}
	Image::Image(const char* filename)
	{
		Open(filename);
	}
	Image::~Image()
	{

	}
	void Image::Reset()
	{
		m_hash = 0;
		m_width = 0;
		m_height = 0;
		m_resolution = 1;
		m_count = 1;
		m_format = PixelFormat_RGBA8888;
		m_function = Function_None;
		m_fileformat = -1;
	}

	bool Image::Open(const char* filename)
	{
		Reset();
		m_fileformat = GetFileFormat(filename);
		if ( m_fileformat == -1 ) return false;
		m_function = Function_Open;
		if (listImageFormat[m_fileformat].function(*this, (void*)filename, 0) == false)
		{
			Reset();
			return false;
		}
		m_hash = String(filename).GetHash();
		return true;
	}
	bool Image::Create(const char* filename, const u16 width, const u16 height, const PixelFormat pixelFormat, const u16 count, const u16 resolution)
	{
		Reset();
		m_fileformat = GetFileFormat(filename);
		if ( m_fileformat == -1 ) return false;
		m_function = Function_Save;
		m_width = width;
		m_height = height;
		m_format = pixelFormat;
		m_count = count;
		m_resolution = resolution;
		if (listImageFormat[m_fileformat].function(*this, (void*)filename, 0) == false)
		{
			Reset();
			return false;
		}
		m_hash = String(filename).GetHash();
		return true;
	}

	bool Image::Read(MemoryHandle mem, size_t size)
	{
		m_function = Function_Read;
		return listImageFormat[m_fileformat].function(*this, mem, size);
	}

	bool Image::Write(MemoryHandle mem, size_t size)
	{
		m_function = Function_Write;
		return listImageFormat[m_fileformat].function(*this, mem, size);
	}

	bool Image::Rewind()
	{
		m_function = Function_Rewind;
		return listImageFormat[m_fileformat].function(*this, 0, 0);
	}

	u16 Image::GetWidth() const
	{
		return m_width / m_resolution;
	}
	u16 Image::GetHeight() const
	{
		return m_height / m_resolution;
	}
	u16 Image::GetResolution() const
	{
		return m_resolution;
	}
	u16 Image::GetCount() const
	{
		return m_count;
	}
	PixelFormat Image::GetFormat() const
	{
		return m_format;
	}
	u32 Image::GetBitSize() const
	{
		return VideoFormatSize[GetFormat()];
	}
	u32 Image::GetDataSize() const
	{
		return GetWidth() * GetHeight() * GetResolution() * GetBitSize() / 8;
	}
	Hash Image::GetHash() const
	{
		return m_hash;
	}

	UID Image::GetFileFormat(const char* filename)
	{
		String str(filename);
		str.GetExtension(str);
		for(size_t i = 0; i < countImageFormat; i++)
		{
			if (listImageFormat[i].extension == str)
			{
				return i;
			}
		}
		return (UID)-1;
	}
}