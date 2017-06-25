#pragma once
#include "XeBase.h"
#include "Video.h"
#include "Geometry.h"
#include "Image.h"

namespace XeEngine
{
	class EXPORT Texture
	{
		friend static bool AddTexture(Texture& texture);
	private:

		void Init();
	protected:
		UID id;
		Hash hash;

		short width;
		short height;
		short m_resolution;
		PixelFormat m_format;

		float fWidth;
		float fHeight;

		//! \brief Tells if this class is a clone of another class
		bool clone;
	public:
		typedef Geometry2<float> Point;
		typedef Geometry2<float> Size;

		Texture();
		Texture(const String&);
		Texture(const Image&);
		~Texture();

		bool Create(const String&);
		bool Create(const Image&);
		bool Create(MemoryHandle, PixelFormat, short width, short height, short resolution = 1);
		void Upload(MemoryHandle, short width, short height);
		void Destroy();

		void Draw(const Point& pos, u16 palette = 0);
		void Draw(const Point& pos, const Size& size, u16 palette = 0);
		void Draw(const Point& pos, const Point &srcpos, const Size& srcsize, u16 palette = 0);
		void Draw(const Point& pos, const Size& size, const Point &srcpos, const Size& srcsize, u16 palette = 0);

		short GetWidth() const;
		short GetHeight() const;
		short GetResolution() const;
		void SetResolution(short);

		UID GetID() const;
		Hash GetHash() const;
		Texture& operator = (const Texture&);
	};


}
