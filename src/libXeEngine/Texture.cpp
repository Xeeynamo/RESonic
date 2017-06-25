#include "Texture.h"
#include "List.h"
#include "Graphics.h"

namespace XeEngine
{
	struct TexCollector
	{
		Texture *texture;
		Hash hash;
		int count;

		bool operator == (const TexCollector& t)
		{
			return hash == t.hash;
		}
	};
	List<TexCollector>* GetTexCollector()
	{
		static List<TexCollector> list;
		return &list;
	}
	bool ExistHash(Hash hash)
	{
		List<TexCollector>* list = GetTexCollector();
		TexCollector tex;

		list->MoveHead();
		while(list->Next(tex))
		{
			if (tex.hash == hash)
				return true;
		}
		return false;
	}
	bool AddTexture(Texture& texture)
	{
		List<TexCollector>* list = GetTexCollector();
		Hash h = texture.GetHash();
		if (h == 0) return false;
		TexCollector tex;

		list->MoveHead();
		while(list->Next(tex))
		{
			if (tex.hash == h)
			{
				list->Remove(tex);
				tex.count++;
				list->Add(tex);

				texture = *tex.texture;
				return false;
			}
		}

		tex.hash = h;
		tex.texture = new Texture(texture);
		tex.texture->clone = false;
		tex.count = 1;
		list->Add(tex);
		return true;
	}
	void RemoveTexture(const Texture& texture)
	{
		List<TexCollector>* list = GetTexCollector();
		Hash h = texture.GetHash();
		if (h == 0) return;
		TexCollector tex;

		list->MoveHead();
		while(list->Next(tex))
		{
			if (tex.hash == h)
			{
				list->Remove(tex);
				tex.count--;
				if (tex.count <= 0)
				{
					delete tex.texture;
					return;
				}
				list->Add(tex);
				return;
			}
		}
	}
}

XeEngine::Texture::Texture()
{
	m_resolution = 1;
	Init();
}
XeEngine::Texture::Texture(const String& filename)
{
	m_resolution = 1;
	Init();
	Create(filename);
}
XeEngine::Texture::Texture(const Image& image)
{
	m_resolution = 1;
	Init();
	Create(image);
}
XeEngine::Texture::~Texture()
{
	Destroy();
}
void XeEngine::Texture::Init()
{
	id = 0;
	hash = 0;
}

bool XeEngine::Texture::Create(const String& filename)
{
	/*if (ExistHash(filename.GetHash()))
		return true;*/
	return Create(Image(filename.ToChar()));
}
bool XeEngine::Texture::Create(const Image& image)
{
	hash = image.GetHash();
	if (hash == 0) return false;

	clone = true;
	if (ExistHash(hash) == false)
	{
		Memory m;
		m.Alloc(image.GetDataSize() * image.GetCount());
		if (Create(m.GetMemoryHandle(), image.GetFormat(), image.GetWidth(), image.GetHeight() * image.GetCount(), image.GetResolution()) == false)
		{
			RemoveTexture(*this);
			return false;
		}
		m.Free();
	}
	hash = image.GetHash();
	AddTexture(*this);
	return true;
}
bool XeEngine::Texture::Create(MemoryHandle h, PixelFormat format, short width_, short height_, short resolution)
{
	Destroy();
	clone = true;

	if (Video::UploadTexture(id, width_ * resolution, height_ * resolution, format, h) == false)
	{
		hash = 0;
		id = 0;
		return false;
	}

	m_format = format;
	width = width_;
	height = height_;
	m_resolution = resolution;

	fWidth = (float)(width / m_resolution);
	fHeight = (float)(height / m_resolution);

	return true;
}
void XeEngine::Texture::Upload(MemoryHandle h, short width, short height)
{
	Video::SelectTexture(id);
	Video::UploadTexture(id, width * m_resolution, height * m_resolution, m_format, h);
}
void XeEngine::Texture::Destroy()
{
	if (clone == true)
	{
		RemoveTexture(*this);
		hash = 0;
		id = 0;
		return;
	}
	Video::DeleteTexture(id);
	hash = 0;
	return;
}

void XeEngine::Texture::Draw(const Point& pos, u16 palette)
{
	/*float fIndex = float(palette) * clutLine + clutSeparator;
	VertexTexture texCoord[] =
	{
		VertexTexture(0.0f, 0.0f, fIndex),
		VertexTexture(1.0f, 0.0f, fIndex),
		VertexTexture(0.0f, 1.0f, fIndex),
		VertexTexture(1.0f, 1.0f, fIndex),
	};
	VertexPosition vertices[] =
	{    
		VertexPosition(pos.x,			pos.y,				pos.z),
		VertexPosition(pos.x + fWidth,	pos.y,				pos.z),
		VertexPosition(pos.x,			pos.y + fHeight,	pos.z),
		VertexPosition(pos.x + fWidth,	pos.y + fHeight,	pos.z),
	};

	Video::SelectTexture(GetID());
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, vertices);
	Video::RenderSend(VertexType_TexCoord, texCoord);
	Video::RenderEnd();*/
}
void XeEngine::Texture::Draw(const Point& pos, const Size& size, u16 palette)
{
	/*float fIndex = float(palette) * clutLine + clutSeparator;
	VertexTexture texCoord[] =
	{
		VertexTexture(0.0f, 0.0f, fIndex),
		VertexTexture(1.0f, 0.0f, fIndex),
		VertexTexture(0.0f, 1.0f, fIndex),
		VertexTexture(1.0f, 1.0f, fIndex),
	};
	VertexPosition vertices[] =
	{    
		VertexPosition(pos.x,				pos.y,					pos.z),
		VertexPosition(pos.x + size.width,	pos.y,					pos.z),
		VertexPosition(pos.x,				pos.y + size.height,	pos.z),
		VertexPosition(pos.x + size.width,	pos.y + size.height,	pos.z),
	};

	Video::SelectTexture(GetID());
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, vertices);
	Video::RenderSend(VertexType_TexCoord, texCoord);
	Video::RenderEnd();*/
}
void XeEngine::Texture::Draw(const Point& pos, const Point &srcpos, const Size& srcsize, u16 palette)
{
	/*float fIndex = float(palette) * clutLine + clutSeparator;
	float _vfWidth = 1.0f / fWidth;
	float _vfHeight = 1.0f / fHeight;

	VertexTexture texCoord[] =
	{
		VertexTexture(_vfWidth * (srcpos.x),					_vfHeight * (srcpos.y),						fIndex),
		VertexTexture(_vfWidth * (srcpos.x + srcsize.width),	_vfHeight * (srcpos.y),						fIndex),
		VertexTexture(_vfWidth * (srcpos.x),					_vfHeight * (srcpos.y + srcsize.height),	fIndex),
		VertexTexture(_vfWidth * (srcpos.x + srcsize.width),	_vfHeight * (srcpos.y + srcsize.height),	fIndex),
	};
	VertexPosition vertices[] =
	{    
		VertexPosition(pos.x,					pos.y,					pos.z),
		VertexPosition(pos.x + srcsize.width,	pos.y,					pos.z),
		VertexPosition(pos.x,					pos.y + srcsize.height,	pos.z),
		VertexPosition(pos.x + srcsize.width,	pos.y + srcsize.height,	pos.z),
	};

	Video::SelectTexture(GetID());
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, vertices);
	Video::RenderSend(VertexType_TexCoord, texCoord);
	Video::RenderEnd();*/
}
void XeEngine::Texture::Draw(const Point& pos, const Size& size, const Point &srcpos, const Size& srcsize, u16 palette)
{
	/*float fIndex = float(palette) * clutLine + clutSeparator;
	float _vfWidth = 1.0f / fWidth;
	float _vfHeight = 1.0f / fHeight;

	VertexTexture texCoord[] =
	{
		VertexTexture(_vfWidth * (srcpos.x),					_vfHeight * (srcpos.y),						fIndex),
		VertexTexture(_vfWidth * (srcpos.x + srcsize.width),	_vfHeight * (srcpos.y),						fIndex),
		VertexTexture(_vfWidth * (srcpos.x),					_vfHeight * (srcpos.y + srcsize.height),	fIndex),
		VertexTexture(_vfWidth * (srcpos.x + srcsize.width),	_vfHeight * (srcpos.y + srcsize.height),	fIndex),
	};
	VertexPosition vertices[] =
	{    
		VertexPosition(pos.x,				pos.y,					pos.z),
		VertexPosition(pos.x + size.width,	pos.y,					pos.z),
		VertexPosition(pos.x,				pos.y + size.height,	pos.z),
		VertexPosition(pos.x + size.width,	pos.y + size.height,	pos.z),
	};

	Video::SelectTexture(GetID());
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, vertices);
	Video::RenderSend(VertexType_TexCoord, texCoord);
	Video::RenderEnd();*/
}

short XeEngine::Texture::GetWidth() const
{
	return width;
}
short XeEngine::Texture::GetHeight() const
{
	return height;
}
short XeEngine::Texture::GetResolution() const
{
	return m_resolution;
}
void XeEngine::Texture::SetResolution(short v)
{
	m_resolution = v;
}

XeEngine::UID XeEngine::Texture::GetID() const
{
	return id;
}
XeEngine::Hash XeEngine::Texture::GetHash() const
{
	return hash;
}
XeEngine::Texture& XeEngine::Texture::operator = (const Texture& src)
{
	id = src.id;
	hash = src.hash;
	
	width = src.width;
	height = src.height;
	m_resolution = src.m_resolution;
	m_format = src.m_format;

	fWidth = src.fWidth;
	fHeight = src.fHeight;

	return *this;
}
