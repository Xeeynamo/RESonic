#include "VideoGL.h"
#include "Window.h"

namespace XeEngine
{
	namespace VideoFramework
	{
		const GLint GL::c_pixelformat[] =
		{
			GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE,
			GL_RGB, GL_BGR, GL_UNSIGNED_BYTE,
			GL_RGBA, GL_BGRA, GL_UNSIGNED_SHORT_4_4_4_4,
			GL_RGB5_A1, GL_BGRA, GL_UNSIGNED_SHORT_5_5_5_1,
			GL_RGB, GL_BGR, GL_UNSIGNED_SHORT_5_6_5,
			GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE,
			GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
		};
		const GLushort GL::c_primitives[] =
		{
			GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS
		};

		GL::GL(Window* window) : Video(window)
		{
			m_name = "Virtual OpenGL";
			m_prevTexBind = -1;
		}
		GL::~GL()
		{
#ifdef PLATFORM_WINDOWS
			if (m_hdc != nullptr)
				wglMakeCurrent(NULL, NULL);
			if (m_hrc != nullptr)
				wglDeleteContext(m_hrc);
#else
#endif
		}
		bool GL::_Initialize()
		{
			if (GLInitialize() == false)
			{
				m_window->ShowMessage(Window::MessageBoxType_Error, Window::MessageBoxButtons_Ok,
					"GL initialization failed.");
				return false;
			}
			
			glEnable(GL_BLEND);
			glEnable(GL_TEXTURE_2D);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glClearDepth(1.0f);

			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_NOTEQUAL, 0.0f);

			glPixelStorei(GL_PACK_ALIGNMENT, 4);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			return GLVerInit();
		}
		bool GL::GLVerInit()
		{
			return true;
		}
		void GL::_SetClearColor(const float r, const float g, const float b)
		{
			glClearColor(r, g, b, 0.0f);
		}
		void GL::_RenderBegin()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void GL::_RenderEnd()
		{

#ifdef PLATFORM_WINDOWS
			::SwapBuffers(m_hdc);
#endif
		}
		bool GL::_UploadTexture(TextureID& id, const u16 width, const u16 height, const PixelFormat format, void* data)
		{
			if (id == 0)
			{
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				glTexImage2D(GL_TEXTURE_2D, 0, c_pixelformat[format * 3 + 0], (GLsizei)width, (GLsizei)height,
					0, c_pixelformat[format * 3 + 1], c_pixelformat[format * 3 + 2], data);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, id);
				glTexSubImage2D(GL_TEXTURE_2D, 0, (GLint)0, (GLint)0, (GLsizei)width, (GLsizei)height,
					c_pixelformat[format * 3 + 1], c_pixelformat[format * 3 + 2], data);
			}
			return true;
		}
		void GL::_DeleteTexture(TextureID& id)
		{
			if (id != 0)
			{
				glDeleteTextures(1, &id);
				id = 0;
			}
		}
		void GL::_SelectTexture(TextureID& id)
		{
			//if (m_prevTexBind != id)
			{
				m_prevTexBind = id;
				glBindTexture(GL_TEXTURE_2D, id);
			}
		}

		bool GL::GLInitialize()
		{
			// Initialize the OpenGL system
#ifdef PLATFORM_WINDOWS
			int nMyPixelFormatID;
			static PIXELFORMATDESCRIPTOR pfd = {
				sizeof (PIXELFORMATDESCRIPTOR), // strcut size 
				1,                              // Version number
				PFD_DRAW_TO_WINDOW	|			// Flags, draw to a window,
				PFD_DOUBLEBUFFER	|
				PFD_SUPPORT_OPENGL,				// use OpenGL
				PFD_TYPE_RGBA,					// RGBA pixel values
				24,								// Pixel format used
				0, 0, 0,						// RGB bits & shift sizes.
				0, 0, 0,						// Don't care about them
				0, 0,							// No alpha buffer info
				0, 0, 0, 0, 0,					// No accumulation buffer
				16,								// 32-bit depth buffer
				0,								// No stencil buffer
				0,								// No auxiliary buffers
				PFD_MAIN_PLANE,					// Layer type
				0,								// Reserved (must be 0)
				0,								// No layer mask
				0,								// No visible mask
				0								// No damage mask
			};
			m_hdc = GetDC((HWND)m_window->GetHandle());
			nMyPixelFormatID = ChoosePixelFormat(m_hdc, &pfd);
			SetPixelFormat(m_hdc, nMyPixelFormatID, &pfd);

			m_hdc = GetDC((HWND)m_window->GetHandle());
			m_hrc = wglCreateContext(m_hdc);
			wglMakeCurrent(m_hdc, m_hrc);
#else
#endif
			// Load libraries
			xglLoadLibraries();

			// Initialize the external libraries dependencies
#ifdef PLATFORM_WINDOWS
			if (wglSwapIntervalEXT != nullptr) wglSwapIntervalEXT(1);
			if (m_hdc == nullptr || m_hrc == nullptr)
				return false;
#else
#endif
			return true;
		}
	}
}