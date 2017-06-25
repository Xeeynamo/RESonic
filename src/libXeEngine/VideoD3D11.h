#pragma once
#include "Video.h"
#include "Window.h"
#include <d3d11.h>

namespace XeEngine
{
	class Window;
	namespace VideoFramework
	{
		class D3D11 : public Video
		{
		public:
			D3D11(Window*);
			~D3D11();
		private:
			ID3D11Device* m_device;
			ID3D11DeviceContext* m_context;
			D3D_FEATURE_LEVEL m_featureLevel;

			bool _Initialize();
			void _SetClearColor(const float, const float, const float);
			void _RenderBegin();
			void _RenderEnd();
			void _SendVertices(const Vertex* data, const size_t count, const Primitives primitives);
		private:
			Window::Size m_prevWindowSize;

			bool CreateDevice();
			bool CreateWindowSizeDependentResources();
			void UpdateForWindowSizeChange();
		};
	}
}