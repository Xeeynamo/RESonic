#pragma once
#include "Video.h"
#include "VideoGLInit.h"

namespace XeEngine
{
	class Window;
	namespace VideoFramework
	{
		class GL : public Video
		{
			static bool LibrariesLoaded;

			static float xglVersion();
			static void xglLoadLibraries();
			static bool xglLoadLibraries12();
			static bool xglLoadLibraries13();
			static bool xglLoadLibraries14();
			static bool xglLoadLibraries15();
			static bool xglLoadLibraries20();
			static bool xglLoadLibraries21();
			static bool xglLoadLibraries30();
			static bool xglLoadLibraries31();
			static bool xglLoadLibraries32();
			static bool xglLoadLibraries33();
			static bool xglLoadLibrariesExtensions();
		protected:
			static const GLint c_pixelformat[];
			static const GLushort c_primitives[];
		public:
			GL(Window*);
			~GL();
		private:
			bool _Initialize();
			void _SetClearColor(const float, const float, const float);
			void _RenderBegin();
			void _RenderEnd();
			bool _UploadTexture(TextureID&, const u16 width, const u16 height, const PixelFormat format, void*);
			void _DeleteTexture(TextureID&);
			void _SelectTexture(TextureID&);
		private:
			HDC m_hdc;
			HGLRC m_hrc;
			GLint m_prevTexBind;

			bool GLInitialize();
			virtual bool GLVerInit();
		};
	}
}