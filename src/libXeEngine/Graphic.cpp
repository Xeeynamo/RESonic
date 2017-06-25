/*#include "Graphics.h"

#include "Matrix.h"
#include "System.h"
#include "File.h"
#include "Math.h"
#include "Texture.h"

XeEngine::VertexTexture XeEngine::Graphic::m_vtexCache[1024*1024/16/16];

XeEngine::VertexPosition XeEngine::Graphic::m_cachePosition[c_cacheSize];
XeEngine::VertexTexture XeEngine::Graphic::m_cacheTexcoord[c_cacheSize];
XeEngine::VertexColor XeEngine::Graphic::m_cacheColor[c_cacheSize];
u16 XeEngine::Graphic::m_cacheIndicies[c_cacheIndexSize];
u16 XeEngine::Graphic::m_cacheIndex;

u16 XeEngine::Graphic::m_paletteEntityCount;
XeEngine::EntityPalette XeEngine::Graphic::m_paletteEntity[c_paletteSize];
u8 XeEngine::Graphic::m_paletteEntityUsed[c_paletteSize];

XeEngine::Clut XeEngine::Graphic::lut[clutCount];
XeEngine::Texture XeEngine::Graphic::texBuffer;

XeEngine::TilemapHeader XeEngine::Graphic::tilemapProperties[XeEngine::c_TilemapCount];
XeEngine::TileEntry XeEngine::Graphic::tilemap[XeEngine::c_TilemapCount * XeEngine::c_TileMapWidth * XeEngine::c_TileMapHeight];
// Resolution
u16 XeEngine::Graphic::resWidth;
u16 XeEngine::Graphic::resHeight;

XeEngine::List<XeEngine::LUTLoaded>* XeEngine::Graphic::lutLoaded = nullptr;

void XeEngine::Graphic::Initialize()
{
	m_cacheIndex = 0;
	for(u16 i = 0, j = 0; i < c_cacheSize; i += 4)
	{
		m_cacheIndicies[j++] = i + 0;
		m_cacheIndicies[j++] = i + 1;
		m_cacheIndicies[j++] = i + 2;
		m_cacheIndicies[j++] = i + 1;
		m_cacheIndicies[j++] = i + 2;
		m_cacheIndicies[j++] = i + 3;
	}

	float uvHelper = 1.0f / 64.0f;
	for(u16 i = 0; i < sizeof(m_vtexCache) / sizeof(VertexTexture); i += 4)
	{
		m_vtexCache[i + 0].u = ((i % 16) + ((i / (16*16)) % 4)) * uvHelper;
		m_vtexCache[i + 0].v = ((i / 16) + ((i / (16*16) / 4) % 4)) * uvHelper;
		m_vtexCache[i + 1].u = m_vtexCache[i + 0].u + uvHelper;
		m_vtexCache[i + 1].v = m_vtexCache[i + 0].v;
		m_vtexCache[i + 2].u = m_vtexCache[i + 0].u;
		m_vtexCache[i + 2].v = m_vtexCache[i + 0].v + uvHelper;
		m_vtexCache[i + 3].u = m_vtexCache[i + 0].u + uvHelper;
		m_vtexCache[i + 3].v = m_vtexCache[i + 0].v + uvHelper;
	}

	m_paletteEntityCount = 0;
	MemoryFill(m_paletteEntityUsed, sizeof(m_paletteEntityUsed));
	MemoryFill(m_paletteEntity, sizeof(m_paletteEntity));

	MemoryFill(lut, sizeof(lut));

#ifndef PUBLIC
	lutLoaded = new XeEngine::List<LUTLoaded>;
#endif
}
void XeEngine::Graphic::SetProjection2D(u16 width, u16 height)
{
	Matrix m;
	Matrix::Ortho(m, 0, width, height, 0, -10.0f, +10.0f);
	Video::SetProjection(m);
}

void XeEngine::Graphic::SendVertex2D(VertexPosition* v1, VertexTexture* v2, VertexColor* v3)
{
	if (m_cacheIndex >= c_cacheSize)
	{
		Flush2D();
	}
	m_cachePosition[m_cacheIndex + 0] = v1[0];
	m_cachePosition[m_cacheIndex + 1] = v1[1];
	m_cachePosition[m_cacheIndex + 2] = v1[2];
	m_cachePosition[m_cacheIndex + 3] = v1[3];

	m_cacheTexcoord[m_cacheIndex + 0] = v2[0];
	m_cacheTexcoord[m_cacheIndex + 1] = v2[1];
	m_cacheTexcoord[m_cacheIndex + 2] = v2[2];
	m_cacheTexcoord[m_cacheIndex + 3] = v2[3];

	m_cacheIndex += 4;
}
void XeEngine::Graphic::Flush2D()
{
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES, RenderPrimitives_TriangleList, m_cacheIndex / 4 * 6);
	Video::RenderSend(VertexType_Position, m_cachePosition);
	Video::RenderSend(VertexType_TexCoord, m_cacheTexcoord);
	Video::RenderEnd(m_cacheIndicies);
	m_cacheIndex = 0;
}
void XeEngine::Graphic::RenderToTexture(Texture& texture)
{
	const VertexPosition pos[4] =
	{
		VertexPosition(-1.0f, -1.0f, 0.0f),
		VertexPosition(+1.0f, -1.0f, 0.0f),
		VertexPosition(-1.0f, +1.0f, 0.0f),
		VertexPosition(+1.0f, +1.0f, 0.0f),
	};
	const VertexTexture tex[4] =
	{
		VertexTexture(0.0f, 0.0f, 0.0f),
		VertexTexture(1.0f, 0.0f, 0.0f),
		VertexTexture(0.0f, 1.0f, 0.0f),
		VertexTexture(1.0f, 1.0f, 0.0f),
	};
	const VertexColor col[4] =
	{
		VertexColor(1.0f, 1.0f, 1.0f, 1.0f),
		VertexColor(1.0f, 1.0f, 1.0f, 1.0f),
		VertexColor(1.0f, 1.0f, 1.0f, 1.0f),
		VertexColor(1.0f, 1.0f, 1.0f, 1.0f),
	};

	Graphic::Flush2D();
	Video::SelectTexture(texture.GetID());
	Video::PaintToTexture(0, 0, texture.GetWidth() * texture.GetResolution(), texture.GetHeight() * texture.GetResolution());
	Video::Clear();
	Video::SetShader(ShaderType_Simple);
	Video::RenderInit(VertexesStructure_TEXTURE_VERTICES_COLORS, RenderPrimitives_TriangleStrip, 4);
	Video::RenderSend(VertexType_Position, (void*)pos);
	Video::RenderSend(VertexType_TexCoord, (void*)tex);
	Video::RenderSend(VertexType_Color, (void*)col);
	Video::RenderEnd();
	Video::SetShader(ShaderType_Clut);
}

u16 XeEngine::Graphic::GetEntityPalette(const UID& id, u16 index)
{
	UID start = id % c_paletteSize;
	UID i = start;
	do 
	{
		if (m_paletteEntity[i].entityId == id)
		{
			if (m_paletteEntity[i].count <= index)
			{
				index = 0;
			}
			return m_paletteEntity[i].page[index] + 0x100;
		}
	} while ((i = (i + 1) % c_paletteSize) != start);
	return 0;
}

bool XeEngine::Graphic::SetEntityPalette(const String& filename, const UID& id)
{	
	UID dst = id % c_paletteSize;
	UID idPrev = m_paletteEntity[dst].entityId;
	if (idPrev == id)
	{
		m_paletteEntity[dst].entityCount++;
		return true;
	}
	else if (idPrev != 0)
	{
		for(UID i = dst + 1; i != dst; )
		{
			UID idPrev = m_paletteEntity[i].entityId;
			if (idPrev == id)
			{
				m_paletteEntity[dst].entityCount++;
				return true;
			}
			else if (idPrev == 0)
			{
				dst = i;
			}
			else
			{
				i = (i + 1) % c_paletteSize;
			}
		}
	}

	File file;
	if (file.Open(filename) == false)
		return false;

	LUTStruct lutStruct;
	file.Read(&lutStruct, sizeof(LUTStruct));
	if (m_paletteEntityCount + lutStruct.count >= c_paletteSize)
	{
		return false;
	}

	EntityPalette entity;
	entity.entityId = id;
	entity.entityCount = 1;
	entity.count = lutStruct.count;
	for(u16 i = 0, j = 0; i < entity.count; i++)
	{
		while(m_paletteEntityUsed[j] != 0)
		{
			j++;
		}
		m_paletteEntityUsed[j] = 1;
		_LoadPaletteRow(file, lutStruct, j & 0xFF, (j + 0x100) >> 8);
		entity.page[i] = j++;
	}
	m_paletteEntity[dst] = entity;
	m_paletteEntityCount++;
	return true;
}
void XeEngine::Graphic::DeleteEntityPalette(const UID& id)
{
	UID start = id % c_paletteSize;
	UID index = start;
	do 
	{
		if (m_paletteEntity[index].entityId == id)
		{
			if (--m_paletteEntity[index].entityCount == 0)
			{
				m_paletteEntity[index].entityId = 0;
				for(u16 i = 0; i < m_paletteEntity[index].count; i++)
				{
					m_paletteEntityUsed[m_paletteEntity[index].page[i]] = 0;
				}
				m_paletteEntityCount--;
			}
			return;
		}
	} while ((index = (index + 1) % c_paletteSize) != start);
}

void XeEngine::Graphic::_LoadPaletteRow(File& file, LUTStruct& header, u8 indexDst, u8 depthDst)
{
	if (header.colorsperpal == 0)
	{
		file.Read(&lut[depthDst][indexDst * colorCount], sizeof(Palette) / 16);
	}
	else
		file.Read(&lut[depthDst][indexDst * colorCount], sizeof(Palette));
}
void XeEngine::Graphic::_LoadPalette(File& file, LUTStruct& header, u8 indexDst, u8 depthDst)
{
	if (header.colorsperpal == 0)
	{
		while(header.count--)
		{
			file.Read(&lut[depthDst][indexDst++ * colorCount], sizeof(Palette) / 16);
		}
	}
	else
		file.Read(&lut[depthDst][indexDst * colorCount], header.count * sizeof(Palette));
}
bool XeEngine::Graphic::LoadPalette(String& filename, u8 row, u8 section)
{
	File file;
	if (file.Open(filename) == true)
	{
		LUTStruct header;
		file.Read(&header, sizeof(LUTStruct));
		_LoadPalette(file, header, row, section);

#ifndef PUBLIC
		LUTLoaded _lutLoaded;
		_lutLoaded.lutStruct = header;
		MemoryCopy(_lutLoaded.filename, filename.ToChar(), MIN(sizeof(_lutLoaded.filename), filename.Length()));
		_lutLoaded.filename[filename.Length()] = '\0';
		lutLoaded->Add(_lutLoaded);
#endif
		return true;
	}
	return false;
}
u32 XeEngine::Graphic::SetGameScreenDimension(u16 width, u16 height)
{
	u32 res = 1;
	float ratio = (float)width / (float)height * 240.0f;
	resWidth = (((u16)ratio + 8) >> 4) << 4;
	resHeight = (((u16)ratio + 8) >> 4) << 4;
	if (resWidth > 400)
		resWidth = 400;
	if (resHeight >= 480)
	{
		res = 2;
	}
	resHeight = 240 * res;
	resWidth = resWidth * res;

	texBuffer.Create(nullptr, VideoPixelFormat_RGBA8888, resWidth, resHeight, res);
	return res;
}
void XeEngine::Graphic::GetTile(u16 layer, u8 posx, u8 posy, TileEntry& tile)
{
	tile = tilemap[(layer % TilemapCount) * c_TilemapLayerOffset +
		((tilemapProperties[layer].posy / 16 + posy) % c_TileMapHeight) * c_TileMapWidth +
		(tilemapProperties[layer].posx / 16 + posx % c_TileMapWidth)];
}
void XeEngine::Graphic::SetTile(u16 layer, u8 posx, u8 posy, TileEntry& tile)
{
	tilemap[layer * c_TilemapLayerOffset + posy * c_TileMapWidth + posx] = tile;
}
XeEngine::TilemapHeader& XeEngine::Graphic::GetLayerSetting(u16 layer)
{
	return tilemapProperties[layer % c_TilemapCount];
}
void XeEngine::Graphic::DrawLayer(u16 layer)
{
	TilemapHeader header = GetLayerSetting(layer);
	//if (header.visible != 0)
	{
		u16 w = (resWidth >> 4) + 1;
		u16 h = (resHeight >> 4) + 1;
		u16 e = w * h * 4;
		if (m_cacheIndex + e >= c_cacheSize)
			Flush2D();
		VertexPosition* pos = m_cachePosition + m_cacheIndex;
		VertexTexture* tex = m_cacheTexcoord + m_cacheIndex;

		const float priority = 0.0f;
		float tHelper = 16.0f;
		float tcHelper = 1.0f/256.0f;
		TileEntry tile;
		for(size_t i = layer * c_TilemapLayerOffset, iy = 0, ix; iy < h; i++, iy++)
		{
			for(ix = 0; ix < w; ix++)
			{
				//GetTile(layer, ix, iy, tile);

				pos[i + 0].x = ix * tHelper;
				pos[i + 0].y = iy * tHelper;
				pos[i + 0].z = priority;
				pos[i + 1].x = pos[i + 0].x + tHelper;
				pos[i + 1].y = pos[i + 0].y;
				pos[i + 1].z = priority;
				pos[i + 2].x = pos[i + 0].x;
				pos[i + 2].y = pos[i + 0].y + tHelper;
				pos[i + 2].z = priority;
				pos[i + 3].x = pos[i + 0].x + tHelper;
				pos[i + 3].y = pos[i + 0].y + tHelper;
				pos[i + 3].z = priority;

				tex[i + 0] = m_vtexCache[i % 4096];
				tex[i + 1].u = tex[i + 0].u + tcHelper;
				tex[i + 1].v = tex[i + 0].v;
				tex[i + 2].u = tex[i + 0].u;
				tex[i + 2].v = tex[i + 0].v + tcHelper;
				tex[i + 3].u = tex[i + 0].u + tcHelper;
				tex[i + 3].v = tex[i + 0].v + tcHelper;
			}
		}
		Flush2D();
	}
}*/