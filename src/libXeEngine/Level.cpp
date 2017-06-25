#include "Graphics.h"
#include "Level.h"
#include "File.h"
#include "Path.h"
#include "Entity.h"
#include "Math.h"
#include "PaletteAnimation.h"
#include "PalAnimWrite.h"
#include "PalAnimWriteArray.h"
#include "PalAnimCycle.h"

XeEngine::Level::Level()
{
	m_levelset = 0;
	m_zone = 0;
	m_room = 0;
	m_act = 0;
	m_timer = 0;
	timerEnabled = false;
	primaryEntity = nullptr;

	resolution = 2;
	cameraX = cameraY = 0;
	map = new Map(*this);
	XeEngine::MemoryFill(chunk, sizeof(chunk));
	XeEngine::MemoryFill(hitboxFloor, sizeof(hitboxFloor));
	XeEngine::MemoryFill(hitboxWall, sizeof(hitboxWall));
	XeEngine::MemoryFill(hitboxAngle, sizeof(hitboxAngle));
	XeEngine::MemoryFill(collisionIndex, sizeof(collisionIndex));
	XeEngine::MemoryFill(layout, sizeof(layout));
	
	// Generate the UV table
	float fUVHelper = 1.0f / 64.0f;
	for(int i = 0; i < tileCount; i++)
	{
		tileUV[i][0][0] = (float)((i & 0xF) | ((i & 0x300) >> 4)) * fUVHelper;
		tileUV[i][0][1] = tileUV[i][0][0] + fUVHelper;
		tileUV[i][0][2] = (float)(((i & 0xF0) >> 4) | ((i & 0xC00) >> 6)) * fUVHelper;
		tileUV[i][0][3] = tileUV[i][0][2] + fUVHelper;

		tileUV[i][2][1] = tileUV[i][0][0];
		tileUV[i][2][0] = tileUV[i][0][1];
		tileUV[i][2][2] = tileUV[i][0][2];
		tileUV[i][2][3] = tileUV[i][0][3];

		tileUV[i][1][0] = tileUV[i][0][0];
		tileUV[i][1][1] = tileUV[i][0][1];
		tileUV[i][1][3] = tileUV[i][0][2];
		tileUV[i][1][2] = tileUV[i][0][3];

		tileUV[i][3][1] = tileUV[i][0][0];
		tileUV[i][3][0] = tileUV[i][0][1];
		tileUV[i][3][3] = tileUV[i][0][2];
		tileUV[i][3][2] = tileUV[i][0][3];
	}

	SetView(400, 256);
}
XeEngine::Level::~Level()
{
	ResetPaletteAnimation();
	delete map;
}

void XeEngine::Level::Initialize()
{
	// Crea la texture per la Color Look-up Table
	lutLevel.Create(nullptr, VideoPixelFormat_RGBA8888, colorCount, paletteCount * clutCount);
}
u8 XeEngine::Level::GetResolution() const
{
	return resolution;
}
void XeEngine::Level::SetResolution(u8 res)
{
	resolution = res;
}
void XeEngine::Level::GetView(u16& width, u16& height) const
{
	width = viewH;
	height = viewV;
}
void XeEngine::Level::SetView(u16 width, u16 height)
{
	viewH = width;
	viewV = height;
	if (viewV > 256)
		viewV = 256;
}

bool XeEngine::Level::LoadStage(String& filename)
{
	XeEngine::File f;
	if (f.Open(filename) == false)
		return false;

	int pos;
	byte size;

	f.Read(&size, 1);
	f.Read(&stage.resoultions, 1);
	f.Read(&stage.actCount, 1);
	f.Read(&stage.hideTitleCard, 1);

	stage.Free();
	stage.act = new StageAct[stage.actCount];
	stage.name = new char[size];

	f.Read(stage.name, size);
	f.Read(&pos, sizeof(pos));
	size = f.Position();
	stage.mem.Alloc(pos - size);
	f.Read(stage.mem.GetMemoryHandle(), stage.mem.Size());
	f.Seek(pos);

	for(ptrdiff_t i = 0; i < stage.actCount; i++)
	{
		for(ptrdiff_t j = 0; j < (ptrdiff_t)(sizeof(StageAct) / sizeof(char*)); j++)
		{
			unsigned short k;
			f.Read(&k, 2);
			if (k == 0xFFFF)
				((char**)&stage.act[i])[j] = (char*)"";
			else
				((char**)&stage.act[i])[j] = (char*)(k + ((char*)stage.mem.GetMemoryHandle() - size));

		}
	}
	String levelName;
	filename.GetFilename(levelName);
	size = levelName.Length() + 1;
	stage.suffix = new char[size];
	XeEngine::MemoryCopy(stage.suffix, levelName.ToChar(), size);

	return true;
}
bool XeEngine::Level::LoadAct(Act act)
{
	String tmp;
	BuildPath(tmp, act, STAGEFILE_GFX);
	{
		Image gfxImage(tmp);
		u8 resolution = gfxImage.GetResolution();
		u8 count = (u8)gfxImage.GetTextureCount();
		u8* data = (u8*)gfxImage.GetData();
		u16 size = 256 * resolution;
		gfxLevel.Create(nullptr, VideoPixelFormat_A8, 1024, 1024, resolution);
		for(int i = 0; i < count; i++)
		{
			gfxLevel.Upload(&data[size * size * i], 256 * (i & 3), 256 * (i >> 2), 256, 256);
		}
	}
	//gfxLevel.Create(tmp);

	// Reset the tile redirecting
	for(u16 i = 0; i < tileCount; i++)
	{
		tileredir[i] = i;
	}
	for(u8 i = 0; i < layersCount; i++)
	{
		layerVisible[i] = true;
	}
	screenShakeX = 0;
	screenShakeY = 0;

	BuildPath(tmp, act, STAGEFILE_LUT);
	Graphic::LoadPalette(tmp, 0, 0);
	BuildPath(tmp, act, STAGEFILE_BLK);
	LoadChunk(tmp);
	BuildPath(tmp, act, STAGEFILE_HBX);
	LoadHitbox(tmp);
	BuildPath(tmp, act, STAGEFILE_CLI);
	LoadCollisionIndex(tmp);

	BuildPath(tmp, act, STAGEFILE_MAP);
	map->Open(tmp);
	map->SetRoom(0);

	BuildPath(tmp, act, STAGEFILE_DPL);
	LoadDynamicPalette(tmp);

	XeEngine::MemoryFill(parallaxPosition, sizeof(parallaxPosition));
	XeEngine::MemoryFill(parallaxSpeed, sizeof(parallaxSpeed));
	XeEngine::MemoryFill(parallaxFactor, sizeof(parallaxFactor));

	SetTimer(0);
	SetTimerEnabled(false);
	m_act = act;
	return true;
}
bool XeEngine::Level::LoadChunk(String& filename)
{
	File file;
	if (file.Open(filename) == true)
	{
		struct BLKHeader
		{
			u16 count;
			u16 destination;
		};

		BLKHeader header;
		file.Read(&header, sizeof(BLKHeader));
		file.Read(chunk, header.count * sizeof(Chunk));
		file.Close();
		return true;
	}
	return false;
}
bool XeEngine::Level::LoadHitbox(String& filename)
{
	File file;
	if (file.Open(filename) == true)
	{
		file.Read(hitboxFloor, sizeof(hitboxFloor));
		file.Read(hitboxWall, sizeof(hitboxWall));
		file.Read(hitboxAngle, sizeof(hitboxAngle));
		file.Close();
		return true;
	}
	return false;
}
bool XeEngine::Level::LoadCollisionIndex(String& filename)
{
	File file;
	if (file.Open(filename) == true)
	{
		struct CollisionIndexHeader 
		{
			u16 count;
			u16 paths;
		};
		CollisionIndexHeader header;
		bool result = true;

		file.Read(&header, sizeof(header));
		if (header.count > tileCount || header.paths > collisionPathCount)
		{
			result = false;
		}
		else
		{
			for(u16 i = 0; i < header.paths; i++)
			{
				file.Read(collisionIndex[i], sizeof(u8) * header.count);
			}
		}
		file.Close();
		return result;
	}
	return false;
}
bool XeEngine::Level::LoadDynamicPalette(String& filename)
{
	File file;
	if (file.Open(filename) == true)
	{

		while(true)
		{
			u16 type;
			u16 count;
			u16 speed;
			file.Read(&type, 2);
			if (type == 0xFFFF)
				break;
			file.Read(&count, 2);
			file.Read(&speed, 2);
			switch(type)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				{
					PaletteSpace::CycleStruct* cycleStruct = new PaletteSpace::CycleStruct[count];
					file.Read(cycleStruct, sizeof(PaletteSpace::CycleStruct) * count);
					PaletteAnimation* paletteAnimation = new PaletteSpace::Cycle(cycleStruct, count, speed);
					paletteAnimation->AttachLUT(Graphic::lut[0]);
					listPaletteAnimation.Add(paletteAnimation);
				}
				break;
			}
		}
		file.Close();
		return true;
	}
	return false;
}
XeEngine::Act XeEngine::Level::GetCurrentAct()
{
	return m_act;
}
XeEngine::TileEntry XeEngine::Level::GetLevelTile(s16 tileX, s16 tileY, int layerID)
{
	tileX %= (layerProperties[layerID].width * 16);
	tileY %= (layerProperties[layerID].height * 16);
	/*if (tileX < 0 || tileY < 0 ||
		tileX >= layerProperties[layerID].width * 2 * 8 ||
		tileY >= layerProperties[layerID].height * 2 * 8) return chunk[0][0];*/
	if (layout[layerID] == nullptr) return chunk[0][0];
	TileEntry TileEntry = chunk[
		layout[layerID][
			(tileX >> 3) +
				((tileY >> 3) * layerProperties[layerID].width * 2)
		]
	]
	[((tileX)&7) | (((tileY)&7)<<3)];
	TileEntry.Tile = tileredir[TileEntry.Tile];
	return TileEntry;
}
u16 XeEngine::Level::GetLevelChunk(u16 chunkX, u16 chunkY, int layer)
{
	return layout[layer][chunkX + chunkY * layerProperties[layer].width * 2];
}
XeEngine::Entity* XeEngine::Level::GetPrimaryEntity()
{
	return primaryEntity;
}
void XeEngine::Level::SetPrimaryEntity(Entity* entity)
{
	primaryEntity = entity;
}
u8 XeEngine::Level::CheckGFXResolution(String& gfxName, u8 resolution)
{
	String path;
	String filename;
	String ext;

	gfxName.GetPath(path);
	gfxName.GetFilename(filename);
	gfxName.GetExtension(ext);
	for(u8 i = resolution; i > 0; i--)
	{
		String tmp = String(path.ToChar());
		tmp += filename;
		tmp += String(gfxResolution[i]);
		tmp += String(".");
		tmp += ext;
		if (XeEngine::File::Exist(tmp) == true)
		{
			gfxName = String(tmp.ToChar());
			return i;
		}
	}
	return 0;
}
void XeEngine::Level::BuildPath(String& strLevel, Act act, STAGEFILE file)
{
	strLevel = String(pathLevel);
	strLevel += String(stage.suffix);
	strLevel += String("/");
	switch(file)
	{
	case STAGEFILE_GFX:
		strLevel += String(stage.act[act].gfx);
		strLevel += String(extGfx);
		CheckGFXResolution(strLevel, resolution);
		break;
	case STAGEFILE_LUT:
		strLevel += String(stage.act[act].clut);
		strLevel += String(extLut);
		break;
	case STAGEFILE_CLI:
		strLevel += String(stage.act[act].cli);
		strLevel += String(extCli);
		break;
	case STAGEFILE_HBX:
		strLevel += String(stage.act[act].hbx);
		strLevel += String(extHbx);
		break;
	case STAGEFILE_MAP:
		strLevel += String(stage.act[act].map);
		strLevel += String(extMap);
		break;
	case STAGEFILE_BLK:
		strLevel += String(stage.act[act].blk);
		strLevel += String(extBlk);
		break;
	case STAGEFILE_RNG:
		strLevel += String(stage.act[act].rng);
		strLevel += String(extRng);
		break;
	case STAGEFILE_OBP:
		strLevel += String(stage.act[act].obp);
		strLevel += String(extObp);
		break;
	case STAGEFILE_DEF:
		strLevel += String(stage.act[act].def);
		strLevel += String(extDef);
		break;
	case STAGEFILE_DTL:
		strLevel += String(stage.act[act].dtl);
		strLevel += String(extDtl);
		break;
	case STAGEFILE_DPL:
		strLevel += String(stage.act[act].dpl);
		strLevel += String(extDpl);
		break;
	case STAGEFILE_CRD:
		strLevel += String(stage.act[act].crd);
		strLevel += String(extCrd);
		break;
	case STAGEFILE_BGM:
		strLevel += String(stage.act[act].bgm);
		strLevel += String(extBgm);
		break;
	}
}


void XeEngine::Level::UpdateLevel()
{
	ProcessCamera();
	UpdatePalette();
	UpdateParallax();
	UpdateShake();
}
void XeEngine::Level::UpdateShake()
{
	if (screenShakeX != 0)
	{
		screenShakeX = -screenShakeX;
		if (screenShakeX > 0)
		{
			screenShakeX--;
		}
	}
	if (screenShakeY != 0)
	{
		screenShakeY = -screenShakeY;
		if (screenShakeY > 0)
		{
			screenShakeY--;
		}
	}
}
void XeEngine::Level::UpdateParallax()
{
	// Parallax data
	for(int i = 0; i < 0x20; i++)
		parallaxIndex[i] = 1;
	for(int i = 0x20; i < 0x30; i++)
		parallaxIndex[i] = 2;
	for(int i = 0x30; i < 0x40; i++)
		parallaxIndex[i] = 3;
	for(int i = 0x40; i < 0x70; i++)
	{
		parallaxIndex[i] = 4;
	}
	for(int i = 0x70; i < 0x98; i++)
	{
		parallaxIndex[i] = 5;
	}
	for(int i = 0x98; i < 0x100; i++)
	{
		parallaxIndex[i] = 6 + i - 0x98;
	}
	// Parallax speed
	parallaxSpeed[0] = 0;
	parallaxSpeed[1] = 0x100;
	parallaxSpeed[2] = 0xC0;
	parallaxSpeed[3] = 0x80;
	parallaxFactor[4] = 0x60;
	parallaxFactor[5] = 0x80;
	for(int i=0; i<0x68; i++)
		parallaxFactor[6 + i] = 0x80 + i;

	s32 shakex = screenShakeX * 0x100;
	for(int i=0; i<0x100; i++)
	{
		parallaxPosition[i] += parallaxSpeed[i];
		parallaxCoords[i] = ((parallaxFactor[i] * postCameraX) + parallaxPosition[i]) % (0x20 * 0x10000);
		//parallaxCoords[i] = 0;
	}

	for(size_t i = 0; i < layersCount; i++)
	{
		if (ripple[i].size > 0)
			ripple[i].frame = (ripple[i].frame + 1) % ripple[i].size;
		else
			ripple[i].frame = 0;
	}

}
void XeEngine::Level::ProcessCamera()
{
	postCameraX = cameraX;
	postCameraY = cameraY;
	ProcessShake();
}
void XeEngine::Level::ProcessShake()
{
	postCameraX += screenShakeX;
	postCameraY += screenShakeY;
}
void XeEngine::Level::RefreshPalette()
{
	lutLevel.Upload(Graphic::lut, 0, 0, colorCount, paletteCount * clutCount);
	Video::SelectClutTexture(lutLevel.GetID());
}
void XeEngine::Level::UpdatePalette()
{
	PaletteAnimation* paletteAnimation;
	listPaletteAnimation.MoveHead();
	while(listPaletteAnimation.Next(paletteAnimation))
		paletteAnimation->Do();
	RefreshPalette();
}
void XeEngine::Level::AddPaletteAnimation(PaletteAnimation* paletteAnimation)
{
	paletteAnimation->AttachLUT(Graphic::lut[0]);
	listPaletteAnimation.Add(paletteAnimation);
}

void XeEngine::Level::ResetPaletteAnimation()
{
	PaletteAnimation* paletteAnimation;
	listPaletteAnimation.MoveHead();
	while(listPaletteAnimation.Next(paletteAnimation))
	{
		delete paletteAnimation;
	}
	listPaletteAnimation.RemoveAll();
}

u32 XeEngine::Level::GetTimer() const
{
	return m_timer;
}
void XeEngine::Level::SetTimer(u32 t)
{
	m_timer = t;
}
void XeEngine::Level::TickTimer()
{
	if (timerEnabled == true)
		m_timer++;
}
bool XeEngine::Level::GetTimerEnabled() const
{
	return timerEnabled;
}
void XeEngine::Level::SetTimerEnabled(bool enabled)
{
	timerEnabled = enabled;
}
s16 XeEngine::Level::GetCameraX() const
{
	return cameraX;
}
s16 XeEngine::Level::GetCameraY() const
{
	return cameraY;
}
void XeEngine::Level::DrawLayer(s16 positionx, s16 positiony, s16 camerax, s16 cameray, u16 width, u16 height, u8 layer)
{
	if (layer >= layersCount)
		return;
	if (layerVisible[layer] == false)
		return;

	VertexPosition pos[4];
	VertexTexture tex[4];

	// Vede qual'è l'ultima palette usata; serve per risparmiare scambi di palette
	u8 lastPaletteUsed = 0;
	// Precalcola la telecamera in tile
	s16 camtilex = camerax / tileSize;
	s16 camtiley = cameray / tileSize;
	// Imposta la texture da utilizzare
	Video::SelectTexture(gfxLevel.GetID());
		
	tex[0].w = tex[1].w = tex[2].w = tex[3].w = clutIndexLevel + clutSeparator;
	for(int j = 0; j < height; j++)
	{
		pos[0].x = -(float)((camerax % tileSize) + positionx);
		pos[0].y = (float)(-((cameray % tileSize) + positiony) + j * tileSizef);
		pos[1].x = pos[0].x + tileSizef;
		pos[1].y = pos[0].y;
		pos[2].x = pos[0].x;
		pos[2].y = pos[0].y + tileSizef;
		pos[3].x = pos[0].x + tileSizef;
		pos[3].y = pos[2].y;

		for(int i = 0; i < width; i++)
		{
			TileEntry tentry = GetLevelTile(camtilex + i, camtiley + j, layer);
			if (tentry.Tile != 0)
			{
				float* uv = tileUV[tentry.Tile][(tentry.Param / 2) & 3];
				tex[0].u = uv[0];
				tex[0].v = uv[2];
				tex[1].u = uv[1];
				tex[1].v = uv[2];
				tex[2].u = uv[0];
				tex[2].v = uv[3];
				tex[3].u = uv[1];
				tex[3].v = uv[3];

				if (tentry.palette != lastPaletteUsed)
				{
					lastPaletteUsed = tentry.palette;
					tex[0].w = tex[1].w = tex[2].w = tex[3].w = clutIndexLevel + clutLine * (float)tentry.palette + clutSeparator;
				}
				if (tentry.depth == 1)
				{
					pos[0].z = pos[1].z = pos[2].z = pos[3].z = LayerZPriority[layer] + 0.5f;
				}
				else
				{
					pos[0].z = pos[1].z = pos[2].z = pos[3].z = LayerZPriority[layer];
				}
				Graphic::SendVertex2D(pos, tex);
			}

			pos[0].x += tileSizef;
			pos[1].x += tileSizef;
			pos[2].x += tileSizef;
			pos[3].x += tileSizef;
		}
	}
	Graphic::Flush2D();
}
void XeEngine::Level::DrawLayerParallax(u8 layer)
{
	if (layer >= layersCount)
		return;
	if (layerVisible[layer] == false)
		return;

	VertexPosition pos[4];
	VertexTexture tex[4];
	// Vede qual'è l'ultima palette usata; serve per risparmiare scambi di palette
	u8 lastPaletteUsed = 0;
	// Ottiene il ripple effect the layer corrente
	RippleEffect* rippleEffect = &ripple[layer];
	// Imposta la grandezza dello spazio di rendering
	u32 renderWidth = viewH / tileSize + 1;
	s32 renderHeight = viewV / tileSize + 1;
	// Crea il filtro di precisione per il parallasse in base alla risoluzione
	u32 filter = ((u32)-1 << (9 - resolution)) & 0xFFF;
	// pixels per level texture
	float mod = 1.0f / 1024.0f;
	// Imposta la texture da utilizzare
	Video::SelectTexture(gfxLevel.GetID());
	s16 divCameraY = postCameraY / tileSize;

	// Imposta la coordinata Z del layer da stampare
	for(s32 hIndex = 0; hIndex < renderHeight; hIndex++)
	{
		pos[0].x = 0.0f;
		pos[1].x = pos[0].x + tileSizef;
		pos[1].y = pos[0].y;
		pos[2].x = pos[0].x;
		pos[2].y = pos[0].y + tileSizef;
		pos[3].x = pos[0].x + tileSizef;
		pos[3].y = pos[2].y;

		int index = hIndex * tileSize;
		for(u32 wIndex = 0; wIndex < renderWidth; wIndex++)
		{
			pos[0].y = pos[1].y = (float)(-((postCameraY) % tileSize) + hIndex * tileSize);
			pos[2].y = pos[3].y = pos[0].y + 1.0f;
			for(u32 tIndex = 0; tIndex < tileSize; tIndex++)
			{
				int line = parallaxCoords[parallaxIndex[index + tIndex]] + rippleEffect->data[(rippleEffect->frame + index + tIndex) % rippleEffect->size];

				float linef;
				if (line >= 0)
				{
					linef = (float)(line & filter) / 256.0f;
				}
				else if (line < 0)
				{
					linef = (float)(-(signed int)((-line) & filter)) / 256.0f;
				}
				line = line / 0x100 / tileSize;

				TileEntry tentry = GetLevelTile(wIndex + line, divCameraY + hIndex, layer);
				float* uv = tileUV[tentry.Tile][(tentry.Param / 2) & 3];
				tex[0].u = tex[2].u = uv[0];
				tex[0].v = tex[1].v = uv[2] + mod * tIndex;
				tex[1].u = tex[3].u = uv[1];
				tex[2].v = tex[3].v = uv[3];
				if (tentry.Param & 2)
				{
					tex[0].v = uv[2] - mod * tIndex;
					tex[1].v = tex[0].v;
					tex[2].v = tex[0].v - mod;
					tex[3].v = tex[2].v;
				}
				else
				{
					tex[0].v = uv[2] + mod * tIndex;
					tex[1].v = tex[0].v;
					tex[2].v = tex[0].v + mod;
					tex[3].v = tex[2].v;
				}
				if (tentry.palette != lastPaletteUsed)
				{
					lastPaletteUsed = tentry.palette;
					tex[0].w = tex[1].w = tex[2].w = tex[3].w = clutIndexLevel + clutLine * (float)tentry.palette + clutSeparator;
				}

				pos[0].x = pos[2].x = (float)(wIndex * tileSize - linef);
				pos[1].x = pos[3].x = pos[0].x + tileSizef;

				if (tentry.depth == 1)
				{
					pos[0].z = pos[1].z = pos[2].z = pos[3].z = LayerZPriority[layer] + 0.5f;
				}
				else
				{
					pos[0].z = pos[1].z = pos[2].z = pos[3].z = LayerZPriority[layer];
				}

				Graphic::SendVertex2D(pos, tex);
				pos[1].y = ++pos[0].y;
				pos[3].y = pos[2].y = pos[0].y + 1.0f;
			}
		}
	}
	Graphic::Flush2D();
}
