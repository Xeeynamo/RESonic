#pragma once
#include "VideoGL.h"

namespace XeEngine
{
	class Window;
	namespace VideoFramework
	{
		class GL33 : public GL
		{
		public:
			GL33(Window*);
			~GL33();
		private:
		};
	}
}