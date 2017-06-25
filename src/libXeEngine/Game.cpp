#include "Game.h"
#include "File.h"
#include "Level.h"
#include "Path.h"
#include "Graphics.h"
#include "Math.h"

int XeEngine::Game::RippleBackgroundMD[256] =
{
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000100, 
	0x00000100, 0x00000100, 0x00000100, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 
	0x00000200, 0x00000200, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000200, 
	0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000100, 0x00000100, 
	0x00000100, 0x00000100, 0x00000100, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	0x00000000, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFE00, 
	0xFFFFFE00, 0xFFFFFE00, 0xFFFFFE00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 
	0xFFFFFD00, 0xFFFFFD00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFD00, 
	0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFE00, 0xFFFFFE00, 
	0xFFFFFE00, 0xFFFFFE00, 0xFFFFFE00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000100, 
	0x00000100, 0x00000100, 0x00000100, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 
	0x00000200, 0x00000200, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 
	0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000300, 0x00000200, 
	0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000200, 0x00000100, 0x00000100, 
	0x00000100, 0x00000100, 0x00000100, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
	0x00000000, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFE00, 0xFFFFFE00, 
	0xFFFFFE00, 0xFFFFFE00, 0xFFFFFE00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 
	0xFFFFFD00, 0xFFFFFD00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 
	0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFC00, 0xFFFFFD00, 
	0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFD00, 0xFFFFFE00, 0xFFFFFE00, 
	0xFFFFFE00, 0xFFFFFE00, 0xFFFFFE00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 0xFFFFFF00, 
};
int XeEngine::Game::RippleBackground[256];
int XeEngine::Game::RippleForeground[256] =
{
	1,  1,  2,  2,  3,  3,  3,  3,  2,  2,  1,  1,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	-1,-1, -2, -2, -3, -3, -3, -3, -2, -2, -1, -1,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	1,  1,  2,  2,  3,  3,  3,  3,  2,  2,  1,  1,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

XeEngine::Game::Game()
{
	level = new Level;
	SetResolution(400, 256, 2);

	con.Log(DEBUG_LEVEL_INFO, "Game reach");

	for(size_t i = 0; i < 256; i++)
	{
		RippleBackground[i] = (int)(sin((float)i * (3.14159265358979323846 / 64.0f)) * 1024.0f);
	}
}
XeEngine::Game::~Game()
{
	delete level;
}

void XeEngine::Game::Initialize()
{
	String strStageList(pathLevel);
	strStageList += String(fileStageList);
	strStageList += String(extBin);

	if (stageList.Open(strStageList) == true)
		con.Log(DEBUG_LEVEL_INFO, "Stage list loaded");
	else
		con.Log(DEBUG_LEVEL_ERROR, "Stage list not loaded");

	level->Initialize();
}

void XeEngine::Game::Do()
{
	Graphic::SetProjection2D(m_resolutionX, m_resolutionY);
	level->UpdateLevel();
	m_frame++;
}
void XeEngine::Game::End()
{
	//XeEngine::Video::Resize(m_resolutionX * m_resolutionZ, m_resolutionY * m_resolutionZ);
	//TextureDraw();
}
void XeEngine::Game::TextureDraw()
{
	Graphic::RenderToTexture(m_texbuffer);
}
XeEngine::Level* XeEngine::Game::GetLevel()
{
	return level;
}
void XeEngine::Game::LoadGFX(const String& filename)
{
	level->gfxLevel.Create(filename);
}
void XeEngine::Game::LoadLUT(const String& filename)
{
	//
}

bool XeEngine::Game::LoadLevel(StageID id, Act act)
{
	char* name;
	stageList.Select(id);
	if (stageList.GetName(name) == true)
	{
		String str((char*)pathLevel);
		str += String(name);
		str += String((char*)extStg);

		if (level->LoadStage(str) == false)
		{
			con.Log(DEBUG_LEVEL_ERROR, "Unable to open stage %s", str);
			return false;
		}
		if (level->LoadAct(act) == false)
		{
			con.Log(DEBUG_LEVEL_ERROR, "Unable to open act %i from stage %4X", act, id);
			return false;
		}
	}
	else
	{
		con.Log(DEBUG_LEVEL_ERROR, "Stage %04X not found", id);
		return false;
	}
	return true;
}

void XeEngine::Game::ClutSolid(bool solid, bool mode16)
{
	/*u16 increment = mode16 == true ? 0x10 : colorCount;
	if (solid == true)
	{
		for(u16 i=0; i<paletteCount; i++)
		{
			for(u16 j=0; j<colorCount; j += increment)
				XeEngine::Graphic::lut[0][j + i * colorCount] |= 0xFF000000;
		}
	}
	else
	{
		for(u16 i=0; i<paletteCount; i++)
		{
			for(u16 j=0; j<colorCount; j += increment)
				XeEngine::Graphic::lut[0][j + i * colorCount] &= 0x00FFFFFF;
		}
	}*/
}

void XeEngine::Game::SetResolution(const u16 x, const u16 y, const u16 z)
{
	m_resolutionX = x;
	m_resolutionY = y;
	m_resolutionZ = z;
	m_texbuffer.Create(nullptr, VideoPixelFormat_RGBA8888, m_resolutionX, m_resolutionY, m_resolutionZ);
}

void XeEngine::Game::DrawTile(float x, float y, u16 tile, u8 palette, u8 params)
{
	float* uv = level->tileUV[tile][(params >> 1) & 3];
	float pal = clutIndexLevel + clutLine * (float)palette + clutSeparator;
	float z = (params&1) ? 0.5f : 0.0f;
	VertexPosition vertices[] =
	{    
		VertexPosition(x,			y,			z),
		VertexPosition(x + 16.0f,	y,			z),
		VertexPosition(x,			y + 16.0f,	z),
		VertexPosition(x + 16.0f,	y + 16.0f,	z),
	};
	VertexTexture texCoord[] =
	{
		VertexTexture(uv[0], uv[2], pal),
		VertexTexture(uv[1], uv[2], pal),
		VertexTexture(uv[0], uv[3], pal),
		VertexTexture(uv[1], uv[3], pal),
	};

	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, vertices);
	Video::RenderSend(VertexType_TexCoord, texCoord);
	Video::RenderEnd();
}
void XeEngine::Game::DrawChunk(float x, float y, u16 chunkID)
{
	float fx = x;
	int i, j;
	TileEntry* chx = level->chunk[chunkID];
	Video::SelectTexture(level->gfxLevel.GetID());
	for(j = 0; j < 8; j++, y += 16.0f)
	{
		x = fx;
		for(i = 0; i < 8; i++, x += 16.0f)
		{
			DrawTile(x, y, chx->Tile, chx->palette, chx->Param);
			chx++;
		}
	}
}
void XeEngine::Game::DrawLevel()
{

}
u16 XeEngine::Game::GetStageCount() const
{
	return stageList.Count();
}
void XeEngine::Game::GetStageProperties(StageProperties& stage, u16 index)
{
	StageProperties* properties;
	stageList.Select((StageID)index);
	if (stageList.GetProperties(properties) == true)
		stage = *properties;
	else
	{
		stage.id = 0;
		stage.stageActCountList = 0;
	}
}

void XeEngine::Game::GetStageIndexProperties(StageProperties& stage, u16 index)
{
	StageProperties* properties;
	stageList.SelectIndex(index);
	if (stageList.GetProperties(properties) == true)
		stage = *properties;
	else
	{
		stage.id = 0;
		stage.stageActCountList = 0;
	}
}
