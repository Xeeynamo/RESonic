#pragma once
#include "XeBase.h"
#include "Vector.h"

#define MINIMAL_DEVICE

namespace XeEngine
{
	typedef UID TextureID;

	enum Primitives
	{
		//! \brief Draw a sequence of disconnected lines with their beginning and end
		Primitives_LineList			= 1,
		//! \brief Draw a sequence of lines, where the next dot is connected with the prev dot
		Primitives_LineStrip		= 2,
		//! \brief Draw a sequence of disconnected triangles
		Primitives_TriangleList		= 3,
		//! \brief Draw a sequence of triangles where the last two vertices are the first two vertices of the 3 vertices
		Primitives_TriangleStrip	= 4,

#ifndef MINIMAL_DEVICE
		//! \brief Draw a sequence of dots
		Primitives_Point			= 0,
		//! \brief Draw a sequence of triangles where the first vertices is connected with all the other triangles
		Primitives_TriangleFan		= 5,
#endif
	};
	enum PixelFormat
	{
		PixelFormat_RGBA8888	= 0,
		PixelFormat_RGB888		= 1,
		PixelFormat_RGBA4444	= 2,
		PixelFormat_RGB5A1		= 3,
		PixelFormat_RGB565		= 4,
		PixelFormat_A8			= 5,
		PixelFormat_AI88		= 6,
	};
	struct Vertex
	{
		float x, y;
		float u, v;
		float palette;
		u32 color;
	};

	class Window;
	class Video
	{
		static Video* video;
	public:
		static Video& Get();

		Video(Window* window);
		virtual ~Video();

		static size_t GetVertexCount(const Primitives primitives, const size_t count);

		static inline const char* GetDeviceName() { return Get()._GetDeviceName(); }
		static inline bool Inizialize() { return Get()._Initialize(); }
		static inline void SetClearColor(const float r, const float g, const float b) { return Get()._SetClearColor(r, g, b); }
		static inline void RenderBegin() { Get()._RenderBegin(); }
		static inline void RenderEnd() { Get()._RenderEnd(); }
		static inline void SendVertices(const Vertex* data, const size_t count, const Primitives primitives) { Get()._SendVertices(data, count, primitives); }
		static inline void SendIndexedVertices(const Vertex* data, const u16* indices, const size_t count, const Primitives primitives) { Get()._SendIndexedVertices(data, indices, count, primitives); }
		static inline bool UploadTexture(TextureID& id, const u16 width, const u16 height, const PixelFormat format, void* data) { return Get()._UploadTexture(id, width, height, format, data); }
		static inline void DeleteTexture(TextureID& id) { Get()._DeleteTexture(id); }
		static inline void SelectTexture(TextureID id) { Get()._SelectTexture(id); }
		static inline void UsePalette(const bool use) { Get()._UsePalette(use); }
		static inline void SelectPalette(const TextureID& id) { Get()._SelectPalette(id); }
	protected:
		const char* m_name;
		Window* m_window;

		const char* _GetDeviceName() const { return m_name; }
		virtual bool _Initialize(){ return true; }
		virtual void _SetClearColor(const float, const float, const float){};
		virtual void _RenderBegin(){}
		virtual void _RenderEnd(){}
		virtual void _SendVertices(const Vertex*, const size_t, const Primitives){}
		virtual void _SendIndexedVertices(const Vertex*, const u16*, const size_t, const Primitives){}
		virtual bool _UploadTexture(TextureID&, const u16, const u16, const PixelFormat, void*){ return true; }
		virtual void _DeleteTexture(TextureID&){}
		virtual void _SelectTexture(TextureID&){}
		virtual void _UsePalette(const bool){};
		virtual void _SelectPalette(const TextureID&){};

	};
}