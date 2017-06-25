#pragma once
#include "XeEngineLV1.h"

namespace XeEngine
{
	enum XeTexturePixelFormat
	{
		//! \brief Automatic texture type
		XeTexturePixelFormat_Automatic	= 0,
		//! \brief 32-bit texture: RGBA8888
		XeTexturePixelFormat_RGBA8888	= 1,
		//! \brief 24-bit texture without Alpha channel
		XeTexturePixelFormat_RGB888		= 2,
		//! \brief 16-bit texture without Alpha channel
		XeTexturePixelFormat_RGB565		= 3,
		//! \brief 16-bit texture with Alpha channel
		XeTexturePixelFormat_RGBA5551	= 4,
		//! \brief 16-bit textures: RGBA4444
		XeTexturePixelFormat_RGBA4444	= 5,
		//! \brief 8-bit textures used as masks
		XeTexturePixelFormat_A8			= 6,
		//! \brief 8-bit intensity texture
		XeTexturePixelFormat_I8			= 7,
		//! \brief 16-bit textures used as masks and intensity
		XeTexturePixelFormat_AI88		= 8,
		//! \brief 32-bit texture of float
		XeTexturePixelFormat_FLOAT		= 9,
		//! \brief 4-bit PVRTC-compressed texture: PVRTC4
		XeTexturePixelFormat_PVRTC4		= 0x10,
		//! \brief 2-bit PVRTC-compressed texture: PVRTC2
		XeTexturePixelFormat_PVRTC2		= 0x11,

		//! \brief 32-bit texture: ARGB8888
		XeTexturePixelFormat_BGRA8888	= -1,
		//! \brief 24-bit texture without Alpha channel
		XeTexturePixelFormat_BGR888		= -2,

		//! \brief Default texture format: RGBA8888
		XeTexturePixelFormat_Default = XeTexturePixelFormat_RGBA8888
	};

	//! \brief A virtual class to manage images that can be handled in XeEngine::XeTexture
	class XeImage
	{
	protected:
		//! \brief The memory that will handle the data of the image
		XeEngine::Memory data;

		//! \brief Width of the image
		short width;

		//! \brief Height of the image
		short height;

		//! \brief Texture count of a single image
		short texcount;

		//! \brief The resolution of the image
		char resolution;

		//! \brief The format of the image
		XeTexturePixelFormat format;
	public:
		XeImage();
		~XeImage();

		//! \brief Load an image from a file
		//! \param File's name
		//! \return Returns true if the image was opened successfully
		virtual bool Load(String&) = 0;

		//! \brief Get the width of the image
		//! \return Image's width
		virtual short GetWidth() const;

		//! \brief Get the height of the image
		//! \return Image's height
		virtual short GetHeight() const;

		//! \brief Get the texture count of the image
		//! \return Image's count
		virtual short GetTextureCount() const;

		//! \brief Get the resolution of the image
		//! \return Image's resolution
		virtual char GetResolution() const;

		//! \brief Get the texture format of the image
		//! \return Image's format
		XeTexturePixelFormat GetFormat() const;

		//! \brief Get the data of the image
		//! \return Image's data
		virtual MemoryHandle GetData() const;
	};
}