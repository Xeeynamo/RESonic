#include "VideoGL33.h"

namespace XeEngine
{
	namespace VideoFramework
	{
		GL33::GL33(Window* window) : GL(window)
		{
			m_name = "OpenGL 3.3";
		}
		GL33::~GL33()
		{

		}
	}
}