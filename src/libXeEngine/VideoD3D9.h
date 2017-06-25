#pragma once
#include <d3d9.h>
#include "Video.h"

namespace XeEngine
{
	namespace VideoFramework
	{
		class D3D9 : public Video
		{
			static const D3DFORMAT c_pixelformat[];
			static const D3DPRIMITIVETYPE c_primitives[];
			static const char d3d9ShaderFx[];
			static const char d3d9ShaderFxPalette[];
		public:
			D3D9(Window*);
			~D3D9();
		private:

			bool _Initialize();
			void _SetClearColor(const float, const float, const float);
			void _RenderBegin();
			void _RenderEnd();
			void _SendVertices(const Vertex* data, const size_t count, const Primitives primitives);
			void _SendIndexedVertices(const Vertex* data, const u16* indices, const size_t count, const Primitives primitives);
			bool _UploadTexture(TextureID&, const u16 width, const u16 height, const PixelFormat format, void*);
			void _DeleteTexture(TextureID&);
			void _SelectTexture(TextureID&);
			void _UsePalette(const bool);
			void _SelectPalette(const TextureID&);
		private:
			LPDIRECT3D9 p_d3d9;
			LPDIRECT3DDEVICE9 p_device;
			LPDIRECT3DPIXELSHADER9 p_pixelShader;
			LPDIRECT3DPIXELSHADER9 p_pixelclutShader;
			D3DCAPS9 m_caps;
			D3DPRESENT_PARAMETERS m_pp;
			DWORD m_clearColor;
			bool m_windowed;

			void D3D9BuildPP();
			void D3D9Reset();
		};
	}
}