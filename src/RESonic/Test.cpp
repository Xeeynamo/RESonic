#include "RESonic1.h"
#include "../libXeEngine/Sprite.h"

void RESonic1::Test()
{
	const char* szSprite1 = "TitleRing";

	static XeEngine::Texture* texRing = nullptr;

	switch (m_state)
	{
	case RESonic1::GameState_INIT:
		str = XeEngine::String(XeEngine::pathSprite);
		str += XeEngine::String(szSprite1);
		str += XeEngine::String(XeEngine::extGfx);
		level->CheckGFXResolution(str, level->GetResolution());
		texRing = new XeEngine::Texture(str);

		LoadLevel(0x0101, 0);
		XeEngine::Video::SetClearColor(0.125, 0.125, 0.125, 0.125);

		InitOk();
		break;
	case RESonic1::GameState_LOOP:
		{
			/*const float width = 400.0f;
			const float height = 240.0f;
			static XeEngine::TexVertex vertex[] =
			{
				XeEngine::TexVertex(vec2(width / 2, 00.0f), vec3(0.0f, 0.0f, 0.0f)),
				XeEngine::TexVertex(vec2(width, height), vec3(1.0f, 0.0f, 0.0f)),
				XeEngine::TexVertex(vec2(0.0f, height), vec3(0.0f, 1.0f, 0.0f)),
			};

			XeEngine::Video::RenderInit(XeEngine::VertexesStructure_TEXTURE_VERTICES, XeEngine::RenderPrimitives_TriangleStrip, 4);
			XeEngine::Video::DrawTextured(XeEngine::RenderPrimitives_TriangleStrip, vertex, sizeof(vertex) / sizeof(XeEngine::TexVertex), texRing->GetID());*/
		}
		break;
	case RESonic1::GameState_END:
		SAFE_DELETE(texRing);
		DestrOk();
		break;
	default:
		break;
	}
}