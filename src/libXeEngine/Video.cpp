#include "Video.h"
#include "Window.h"

namespace XeEngine
{
	Video* Video::video;
	
	Video& Video::Get()
	{
		return *video;
	}

	Video::Video(Window* window)
	{
		m_name = "Null";
		m_window = window;
		video = this;
	}
	Video::~Video()
	{

	}

	size_t Video::GetVertexCount(const Primitives primitives, const size_t count)
	{
		switch (primitives)
		{
#ifndef MINIMAL_DEVICE
		case RenderType_Point: return count;
#endif
		case Primitives_LineList: return count / 2;
#ifndef MINIMAL_DEVICE
		case RenderType_LineLoop: return 0;	// ?????
#endif
		case Primitives_LineStrip: return count - 1;
		case Primitives_TriangleList: return count;
		case Primitives_TriangleStrip: return count - 2;
#ifndef MINIMAL_DEVICE
		case Type_TriangleFan: return count - 2;
		case Type_Quad: return count - 3; // ????
#endif
		}
		return 0;
	}
}