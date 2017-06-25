#pragma once
#include "Video.h"
#include "String.h"
#include "File.h"

namespace XeEngine
{
	class Image;
	struct ImageFormat
	{
		String extension;
		bool (*function)(Image&, void*, size_t);
	};
	class Image
	{
		static const u8 VideoFormatSize[];
		static size_t countImageFormat;
		static ImageFormat listImageFormat[];
	public:
		enum ImageFunction
		{
			Function_None,
			Function_Open,
			Function_Save,
			Function_Read,
			Function_Write,
			Function_Rewind,
		};
		static void AddImageFormat(const ImageFormat&);

		Image();
		Image(const char* filename);
		~Image();

		// Apre un'immagine specifica e ne legge solo l'header
		bool Open(const char* filename);

		// Crea un'immagine
		bool Create(const char* filename, const u16 width, const u16 height, const PixelFormat pixelFormat = PixelFormat_RGBA8888, const u16 count = 1, const u16 resolution = 1);

		// Legge n byte dell'immagine
		bool Read(MemoryHandle, size_t);

		// Scrive n byte sull'immagine
		bool Write(MemoryHandle, size_t);

		// Riavvolge la lettura dell'immagine
		bool Rewind();

		u16 GetWidth() const;
		u16 GetHeight() const;
		u16 GetResolution() const;
		u16 GetCount() const;
		PixelFormat GetFormat() const;
		u32 GetBitSize() const;
		u32 GetDataSize() const;
		Hash GetHash() const;
	public:
		File m_file;
		Hash m_hash;
		u16 m_width, m_height;
		u16 m_resolution, m_count;
		PixelFormat m_format;
		ImageFunction m_function;
		UID m_fileformat;
	private:
		void Reset();

		static UID GetFileFormat(const char* filename);
	};
}