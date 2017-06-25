#include "VideoD3D11.h"
#include "Window.h"

#pragma comment(lib, "d3d11.lib")

namespace XeEngine
{
	namespace VideoFramework
	{
		D3D11::D3D11(Window* window) : Video(window)
		{
			m_name = "Direct3D11";
		}
		D3D11::~D3D11()
		{

		}
		bool D3D11::_Initialize()
		{
			if (CreateDevice() == false)
			{
				m_window->ShowMessage(Window::MessageBoxType_Error, Window::MessageBoxButtons_Ok,
					"CreateDevice failed.");
				return false;
			}
			UpdateForWindowSizeChange();
			return true;
		}
		void D3D11::_SetClearColor(const float, const float, const float)
		{

		}
		void D3D11::_RenderBegin()
		{

		}
		void D3D11::_RenderEnd()
		{

		}
		void D3D11::_SendVertices(const Vertex* data, const size_t count, const Primitives primitives)
		{

		}

		bool D3D11::CreateDevice()
		{
			// Questo flag aggiunge supporto per superfici con un ordinamento dei canali dei colori diverso
			// da quello predefinito dell'API. Necessario per la compatibilità con Direct2D.
			UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
			// Se il progetto si trova in una compilazione di debug, abilita il debug tramite i livelli SDK utilizzando questo flag.
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			// Questa matrice consente di definire il set di livelli di funzionalità hardware DirectX che verrà supportato dall'applicazione.
			// Si noti che l'ordinamento deve essere mantenuto.
			// Ricordare di dichiarare il livello di funzionalità minimo richiesto nella descrizione
			// dell'applicazione. Si presuppone che tutte le applicazioni supportino 9.1 salvo laddove diversamente indicato.
			D3D_FEATURE_LEVEL featureLevels[] = 
			{
				//D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1
			};

			return( !FAILED( D3D11CreateDevice(
				nullptr,						// Specificare nullptr per usare l'adattatore predefinito.
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				creationFlags,					// Impostare i flag di compatibilità Direct2D e debug.
				featureLevels,					// Elenco di livelli di funzionalità che l'app è in grado di supportare.
				ARRAYSIZE(featureLevels),
				D3D11_SDK_VERSION,				// Impostare sempre questo su D3D11_SDK_VERSION per le applicazioni Windows Store.
				&m_device,						// Restituisce il dispositivo Direct3D creato.
				&m_featureLevel,				// Restituisce il livello di funzionalità del dispositivo creato.
				&m_context						// Restituisce il contesto immediato del dispositivo.
				) /*D3D11CreateDevice*/ ) /*FAILED*/ );
		}
		bool D3D11::CreateWindowSizeDependentResources()
		{
			m_window->GetSize(m_prevWindowSize);
			return false;
		}
		void D3D11::UpdateForWindowSizeChange()
		{
			Window::Size size;
			m_window->GetSize(size);
			if (m_prevWindowSize != size)
			{
				ID3D11RenderTargetView* nullViews[] = {nullptr};
				/*m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
				m_renderTargetView = nullptr;
				m_depthStencilView = nullptr;
				m_d3dContext->Flush();*/
				CreateWindowSizeDependentResources();
			}
		}
	}
}