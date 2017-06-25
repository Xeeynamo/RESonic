#include "RESonic1.h"
#include "../libXeEngine/Sprite.h"

/*
500
520
550
560
575
583

Fade in con velocità di 20 frame
Sonic comincia ad uscire, dopo 30 frame
Sonic avanza di 8 pixel alla volta dal basso verso l'alto
Comincia l'animazione, ogni 8 frame cambia la sprite
Si ripete dal frame 7 al frame 8
*/
void RESonic1::TitleScreen()
{
	const char* szSprite1 = "TitleRing";
	const char* szSprite2 = "TitleSonic";

	static XeEngine::Sprite* titleRing = nullptr;
	static XeEngine::Sprite* titleSonic = nullptr;

	switch (m_state)
	{
	case RESonic1::GameState_INIT:
		m_frame = 0;

		titleRing = new XeEngine::Sprite();
		titleSonic = new XeEngine::Sprite();

		str = XeEngine::String(XeEngine::pathSprite);
		str += XeEngine::String(szSprite1);
		str += XeEngine::String(XeEngine::extGfx);
		level->CheckGFXResolution(str, level->GetResolution());
		titleRing->CreateTexture(new XeEngine::Texture(str));

		str = XeEngine::String(XeEngine::pathSprite);
		str += XeEngine::String(szSprite2);
		str += XeEngine::String(XeEngine::extGfx);
		level->CheckGFXResolution(str, level->GetResolution());
		titleSonic->CreateTexture(new XeEngine::Texture(str));

		str = XeEngine::String(XeEngine::pathSprite);
		str += XeEngine::String(szSprite1);
		str += XeEngine::String(XeEngine::extLut);
		titleRing->LoadPalette(str);

		str = XeEngine::String(XeEngine::pathSprite);
		str += XeEngine::String(szSprite2);
		str += XeEngine::String(XeEngine::extLut);
		titleSonic->LoadPalette(str);

		titleRing->CreateFrame(0, 0, 256, 144, 128, 72);

		titleSonic->CreateFrame(0, 0, 84, 8, 42, 38 - 68);
		titleSonic->CreateFrame(0, 0, 84, 16, 42, 38 - 60);
		titleSonic->CreateFrame(0, 0, 84, 24, 42, 38 - 52);
		titleSonic->CreateFrame(0, 0, 84, 32, 42, 38 - 44);
		titleSonic->CreateFrame(0, 0, 84, 40, 42, 38 - 36);
		titleSonic->CreateFrame(0, 0, 84, 48, 42, 38 - 28);
		titleSonic->CreateFrame(0, 0, 84, 56, 42, 38 - 20);
		titleSonic->CreateFrame(0, 0, 84, 64, 42, 38 - 12);
		titleSonic->CreateFrame(0, 0, 84, 72, 42, 38 - 4);
		titleSonic->CreateFrame(0, 0, 84, 76, 42, 38);
		titleSonic->CreateFrame(84, 0, 84, 76, 42, 38);
		titleSonic->CreateFrame(0, 76, 84, 76, 42, 38);
		titleSonic->CreateFrame(84, 76, 84, 76, 42, 38);
		titleSonic->CreateFrame(0, 152, 84, 76, 42, 38);
		titleSonic->CreateFrame(84, 152, 84, 76, 42, 38);
		titleSonic->CreateFrame(0, 228, 84, 76, 42, 38);
		titleSonic->CreateFrame(84, 228, 84, 76, 42, 38);

		titleRing->SetFrame(1);
		titleRing->SetPoint(XeEngine::Point(m_resolutionX / 2.0f, m_resolutionY / 2.0f, 1.0f));
		titleSonic->SetPoint(XeEngine::Point(m_resolutionX / 2 + 6.0f, m_resolutionY / 2.0f - 40.0f, 1.0f));

		XeEngine::Video::SetClearColor(0.0f, 0.5f, 0.875f, 1.0f);
		LoadLevel(0x0101, 0);
		level->ripple[1].Load(RippleBackground, 256);

		InitOk();
		break;
	case RESonic1::GameState_LOOP:
		XeEngine::Graphic::DrawLayer(0);
		//level->DrawLayerParallax(1);
		//level->DrawLayer(0, 0, level->cameraX, level->cameraY, 400, 256, 1);
		titleRing->Draw();
		
		if (m_frame >= 20)
		{
			if (m_frame >= 60)
			{
				if (m_frame < 68)
				{
					titleSonic->SetFrame(m_frame - 59);
				}
				else
				{
					level->cameraX += 2;

					u16 frame = 10 + (m_frame - 68) / 8;
					if (frame > 17)
					{
						frame = 16 + (frame % 2);
					}
					titleSonic->SetFrame(frame);
				}
				titleSonic->Draw();
			}
		}
		break;
	case RESonic1::GameState_END:
		SAFE_DELETE(titleSonic);
		SAFE_DELETE(titleRing);
		DestrOk();
		break;
	default:
		break;
	}
}