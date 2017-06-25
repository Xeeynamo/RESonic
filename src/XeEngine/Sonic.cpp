#ifdef DEBUG

#include <stdio.h>
#include "Sonic.h"
#include "GFX.h"
#include "BLK.h"
#include "MAP.h"
#include "XeLevel.h"
#include "XeFile.h"

unsigned char empty_tile[] =
{
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00,
	0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0xf0,

	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x0f, 0xf0,
	0x00, 0xf0, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xf0,

	0x0f, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0x0f, 0x00,
	0x0f, 0xf0, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 

	0x0f, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0,
	0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
};

bool Sonic_GFXConverter(char *dstFile, char *srcFile8x8, char *srcFileMapping)
{
	XeEngine::File f8, fMap, fOut;
	if (!f8.Open(XeEngine::String(srcFile8x8))) return false;
	if (!fMap.Open(XeEngine::String(srcFileMapping))) return false;
	if (!fOut.Create(XeEngine::String(dstFile))) return false;
	int tile16Count = fMap.Size()/8;

	int textureCount = (tile16Count>>8) + ((tile16Count&0xFF) ? 1 : 0);
	fOut.Seek(1024*0x80 + sizeof(GFXStruct)-1); //fseek(fOut, textureCount*256*256/2-1+sizeof(GFXStruct), SEEK_SET);
	textureCount = 0;
	fOut.Write(&textureCount, 1);

	GFXStruct gfxstruct;
	gfxstruct.width = gfxstruct.height = 0;
	gfxstruct.dstindex = 0;
	gfxstruct.flags = 0;
	gfxstruct.headersize = sizeof(GFXStruct);
	gfxstruct.mode = 2;
	gfxstruct.resolution = 1;
	gfxstruct.texturecount = 4;
	fOut.Seek();
	fOut.Write(&gfxstruct, sizeof(gfxstruct));

	for(int t=0; t<tile16Count; t++)
	{
		unsigned char tile16[0x80];
		for(int b=0; b<4; b++)
		{
			unsigned short id;
			fMap.Read(&id, sizeof(id));
			id = ((id&0xFF)<<8) | ((id>>8)&0xFF);

			unsigned char tile8[0x20];
			f8.Seek((id&0x3FF) * sizeof(tile8));
			f8.Read(tile8, sizeof(tile8));

			for(int i=0; i<8; i++)
			{
				for(int j=0; j<4; j++)
				{
					tile8[j + i*4] = ((tile8[j + i*4]>>4)&0xF) | ((tile8[j + i*4]<<4)&0xF0);
				}
			}
			if (id & 0x0800) // Flip X
			{
				for(int i=0; i<8; i++)
				{
					for(int j=0; j<2; j++)
					{
						char tmp = tile8[j + i*4];
						tile8[j + i*4] = tile8[-j + 3 + i*4];
						tile8[-j + 3 + i*4] = tmp;
					}
					for(int j=0; j<4; j++)
					{
						tile8[j + i*4] = ((tile8[j + i*4]>>4)&0xF) | ((tile8[j + i*4]<<4)&0xF0);
					}
				}
			}
			if (id & 0x1000) // Flip Y
			{
				for(int i=0; i<4; i++)
				{
					for(int j=0; j<4; j++)
					{
						char tmp = tile8[j + i*4];
						tile8[j + i*4] = tile8[j + (-i*4 + 0x1C)];
						tile8[j + (-i*4 + 0x1C)] = tmp;
					}
				}
			}

			for(int i=0; i<8; i++)
			{
				for(int j=0; j<4; j++)
				{
					tile16[j + (b&1)*4 + i*8 + (b&2)*0x20] = tile8[j + i*4];
				}
			}
		}
		for(int i=0; i<16; i++)
		{
			int pos = i*256/2 + (t&15)*8 + (t>>4)*256*16/2;
			fOut.Seek(pos + sizeof(GFXStruct));
			fOut.Write(&tile16[i*8], 8);
		}
	}
	fOut.Close();
	fMap.Close();
	f8.Close();
	return true;
}

typedef unsigned char Tile8[0x20];
typedef unsigned char Tile16_4[0x80];
typedef unsigned char Tile16_8[0x100];
bool Sonic_GFXConverter8BPP(char *dstFile, char *srcFile8x8, char *srcFileMapping, bool isSonic1)
{
	XeEngine::File f;
	XeEngine::Memory tile8, mapping, tile16;

	short palshift = isSonic1 ? 13 : 13;

	if (!f.Open(XeEngine::String(srcFile8x8)))
	{
		printf("Unable to open %s\n", srcFile8x8);
		return false;
	}
	tile8.Alloc(f.Size());
	f.Read(tile8.GetMemoryHandle(), tile8.Size());
	f.Close();

	if (!f.Open(XeEngine::String(srcFileMapping)))
	{
		printf("Unable to open %s\n", srcFileMapping);
		return false;
	}
	mapping.Alloc(f.Size());
	f.Read(mapping.GetMemoryHandle(), mapping.Size());
	f.Close();

	Tile8 tmp8;
	Tile8 *t8 = (Tile8*)tile8.GetMemoryHandle();
	unsigned short *map = (unsigned short *)mapping.GetMemoryHandle();
	unsigned short tile16count = mapping.Size()/8;

	tile16.Alloc(tile16count * sizeof(Tile16_8));
	Tile16_8 *t16 = (Tile16_8*)tile16.GetMemoryHandle();

	for(int t=0, p, x, y, pal, tile; t<tile16count; t++)
	{
		for(p=0; p<4; p++)
		{
			map[t*4+p] = ((map[t*4+p]&0xFF)<<8) | ((map[t*4+p]>>8)&0xFF);
			pal = ((map[t*4+p]>>palshift)&3) << 4;
			tile = map[t*4+p]&0x3FF;
			if (tile*sizeof(Tile8) >= (unsigned int)tile8.Size())
			{
				XeEngine::MemoryCopy(tmp8, &empty_tile[0x20*p], 0x20);
			}
			else
			{
				XeEngine::MemoryCopy(tmp8, t8[map[t*4+p]&0x3FF], sizeof(Tile8));

				for(int i=0; i<8*4; i++)
					tmp8[i] = ((tmp8[i]>>4)&0xF) | ((tmp8[i]<<4)&0xF0);

				if (map[t*4+p] & 0x0800) // Mirror
				{
					for(y=0; y<8; y++)
					{
						for(x=0; x<2; x++)
						{
							char tmp = tmp8[x + y*4];
							tmp8[x + y*4] = tmp8[-x + 3 + y*4];
							tmp8[-x + 3 + y*4] = tmp;
						}
						for(int x=0; x<4; x++)
						{
							tmp8[x + y*4] = ((tmp8[x + y*4]>>4)&0xF) | ((tmp8[x + y*4]<<4)&0xF0);
						}
					}
				}
				if (map[t*4+p] & 0x1000) // Flip
				{
					for(y=0; y<4; y++)
					{
						for(x=0; x<4; x++)
						{
							char tmp = tmp8[x + y*4];
							tmp8[x + y*4] = tmp8[x + (-y*4 + 0x1C)];
							tmp8[x + (-y*4 + 0x1C)] = tmp;
						}
					}
				}
			}

			for(y=0; y<8; y++)
			{
				for(x=0; x<4; x++)
				{
					int pos = x*2 + y*0x10 + (p&1)*8 + (p&2)*0x40;
					t16[t][pos+0] = (tmp8[x + y*4] & 0xF) | pal;
					t16[t][pos+1] = ((tmp8[x + y*4] >> 4)&0xF) | pal;
				}
			}
		}
	}

	unsigned char zero = 0;
	int texturecount = tile16count>>8;
	if ((texturecount<<8) < tile16count) texturecount++;

	GFXStruct gfxstruct;
	gfxstruct.width = gfxstruct.height = 0;
	gfxstruct.dstindex = 0;
	gfxstruct.flags = 0;
	gfxstruct.headersize = sizeof(GFXStruct);
	gfxstruct.mode = 3;
	gfxstruct.resolution = 1;
	gfxstruct.texturecount = texturecount;

	f.Create(XeEngine::String(dstFile));
	f.Write(&gfxstruct, sizeof(GFXStruct));
	f.Seek(texturecount*0x10000 - 1, XeEngine::FILESEEK_CUR);
	f.Write(&zero, 1);
	for(int i=0, j, pos; i<tile16count; i++)
	{
		for(j=0; j<16; j++)
		{
			pos = j*256 + (i&15)*16 + (i>>4)*256*16;
			f.Seek(pos + sizeof(GFXStruct));
			f.Write(&t16[i][j*16], 16);
		}
	}
	f.Close();

	tile8.Free();
	tile16.Free();
	mapping.Free();
	return true;
}
bool Sonic_BlockConverter(char *dstFile, char *srcFile128, char *srcFile16, bool bpp8)
{
	XeEngine::File fSrc128, fSrc16, fDst;
	if (!(fSrc128.Open(XeEngine::String(srcFile128)) & fSrc16.Open(XeEngine::String(srcFile16)) & fDst.Create(XeEngine::String(dstFile))))
		return false;

	BLKHeader header;
	header.count = fSrc128.Size()/2/64;
	header.destination = 0;
	fDst.Write(&header, sizeof(header));
	for(int i=0; i<header.count*64; i++)
	{
		TileEntry tentry;

		unsigned short t;
		fSrc128.Read(&t, sizeof(t));
		t = ((t >> 8)&0xFF) | ((t&0xFF)<<8);
		tentry.Tile = t&0x3FF;
		if (tentry.Tile == 1)
			tentry = tentry;
		tentry.mirror = (t&0x400) ? 1 : 0;
		tentry.flip = (t&0x800) ? 1 : 0;
		tentry.path1	= (t>>12);
		tentry.path2	= (t>>14);
		tentry.unknow	= 0;
		
		fSrc16.Seek((t&0x3FF)*sizeof(t)*4, XeEngine::FILESEEK_SET);
		fSrc16.Read(&t, sizeof(t));
		t = ((t >> 8)&0xFF) | ((t&0xFF)<<8);
		if (bpp8) tentry.palette = 0;
		else tentry.palette = (t>>13)&3;
		tentry.depth = (t>>15)&1;

		fDst.Write(&tentry, sizeof(tentry));
	}
	return true;
}
void Sonic_ColIndexConverter(char *dstFile, char *path1, char *path2)
{
	int size;
	byte index[2048];
	XeEngine::File fp1, fp2, f;
	if (!f.Create(XeEngine::String(dstFile))) return;

	short colCount = 2048;
	byte paths = 2;
	byte unknow = 0;
	f.Write(&colCount, sizeof(colCount));
	f.Write(&paths, sizeof(paths));
	f.Write(&unknow, sizeof(unknow));

	XeEngine::MemoryFill(index, sizeof(index));

	if (fp1.Open(XeEngine::String(path1)))
	{
		size = fp1.Size();
		fp1.Read(index, size);
	}
	f.Write(index, sizeof(index));
	fp1.Close();

	XeEngine::MemoryFill(index, 2048);
	if (fp2.Open(XeEngine::String(path2)))
	{
		size = fp2.Size();
		fp2.Read(index, size);
	}
	f.Write(index, sizeof(index));
	fp2.Close();
}
void Sonic_MapConverter(char *dstFile, char *srcFile, int act)
{
	const int layercount = 2;
	const int mapwidth = 0x4000/0x100;
	const int mapheight = 0x800/0x100;
	XeEngine::File dst, src;
	if (!dst.Create(XeEngine::String(dstFile))) return;
	if (!src.Open(XeEngine::String(srcFile))) return;

	MapProperties map;
	map.posx = 0;
	map.posy = 0;
	map.width = mapwidth;
	map.height = mapheight;
	map.mapzone = act;
	map.layerCount = layercount;
	map.padding06 = map.padding07 = 0;
	dst.Write(&map, sizeof(map));

	for(int i=0; i<map.layerCount; i++)
	{
		LayerProperties layer;
		layer.width = mapwidth;
		layer.height = mapheight;
		layer.speedX = layer.speedY = 0x100;
		layer.collisionFlag = 0;
		layer.priority = i == 0 ? 0 : -1;
		dst.Write(&layer, sizeof(layer));
	}
	for(int l=0; l<layercount; l++)
	{
		byte rawmap[mapwidth*2];
		short mapdata[mapwidth*2 * mapheight*2];

		for(int j=0; j<mapheight*2; j++)
		{
			src.Seek(j * 0x100 + l*0x80, XeEngine::FILESEEK_SET);
			src.Read(rawmap, sizeof(rawmap));
			for(int i=0; i<mapwidth*2; i++)
			{
				mapdata[(i&1) + (i/2)*4 + (j/2)*mapwidth*4 + (j&1)*2] = rawmap[i];
			}
		}
		dst.Write(mapdata, sizeof(mapdata));
	}
	dst.Close();
	src.Close();
}
void Sonic_MapConverterNEW(char *dstFile, char *srcFile, int act)
{
	const int layercount = 2;
	const int mapwidth = 0x4000/0x100;
	const int mapheight = 0x800/0x100;
	XeEngine::File dst, src;
	if (!dst.Create(XeEngine::String(dstFile))) return;
	if (!src.Open(XeEngine::String(srcFile))) return;

	XeEngine::MapZone mapZone;
	mapZone.locationX = 0;
	mapZone.locationY = 0;
	mapZone.roomCount = 1;
	mapZone.unknow = 0;
	mapZone.Flags = 0;
	dst.Write(&mapZone, sizeof(XeEngine::MapZone));

	XeEngine::MapRoom mapRoom;
	mapRoom.bg1LayerID = 0;
	mapRoom.fg1LayerID = 0;
	mapRoom.fg2LayerID = 0xFF;
	mapRoom.bg2LayerID = 0xFF;
	mapRoom.x = 0;
	mapRoom.y = 0;
	mapRoom.width = mapwidth;
	mapRoom.height = mapheight;
	dst.Write(&mapRoom, sizeof(XeEngine::MapRoom));

	for(int i=0; i<2; i++)
	{
		XeEngine::MapLayer layer;
		layer.width = mapwidth;
		layer.height = mapheight;
		layer.dummy = 0;
		layer.parallaxID = 0xFF;
		dst.Write(&layer, sizeof(layer));
	}

	for(int l=0; l<layercount; l++)
	{
		byte rawmap[mapwidth * 2];
		short mapdata[mapwidth * 2];

		for(int j=0; j<mapheight*2; j++)
		{
			src.Seek(j * 0x100 + l*0x80, XeEngine::FILESEEK_SET);
			src.Read(rawmap, sizeof(rawmap));
			for(int i = 0; i < mapwidth * 2; i++)
				mapdata[i] = rawmap[i];
			dst.Write(mapdata, sizeof(mapdata));
		}
	}
	dst.Close();
	src.Close();
}


//////////////////////////////////////////////////////////////////////////
// Chunk256 to Chunk128
typedef TileEntry Chunk[0x40];
typedef unsigned short Chunk256[0x100];
struct ChunkConverted
{
	unsigned short chunk128[4];

	void Zero()
	{
		chunk128[0] = chunk128[1] = chunk128[2] = chunk128[3] = 0;
	}
};
bool CompareChunks(Chunk c1, Chunk c2)
{
	for(int i=0; i<0x40; i++)
	{
		if (c1[i].ToInt() != c2[i].ToInt())
			return false;
	}
	return true;
}
TileEntry BlockToTileS1(unsigned short data, unsigned short *block, bool bpp8)
{
	TileEntry tentry;

	data = ((data >> 8)&0xFF) | ((data&0xFF)<<8);
	tentry.Tile		= (data&0x3FF);
	tentry.mirror	= (data&0x0800) ? 1 : 0;
	tentry.flip		= (data&0x1000) ? 1 : 0;
	tentry.path1	= (data>>13);
	tentry.path2	= (data>>13);
	tentry.unknow	= 0;

	data = ((block[tentry.Tile*4+0] >> 8)&0xFF) | ((block[tentry.Tile*4+0]&0xFF)<<8);
	if (bpp8) tentry.palette = 0;
	else tentry.palette = (data>>13)&3;
	tentry.depth = (data>>15)&1;

	return tentry;
}
TileEntry BlockToTileS2(unsigned short data, unsigned short *block, bool bpp8)
{
	TileEntry tentry;

	data = ((data >> 8)&0xFF) | ((data&0xFF)<<8);
	tentry.Tile		= (data&0x3FF);
	tentry.mirror	= (data&0x0400) ? 1 : 0;
	tentry.flip		= (data&0x0800) ? 1 : 0;
	tentry.path1	= (data>>12);
	tentry.path2	= (data>>14);
	tentry.unknow	= 0;

	if (data&0x0400)
		tentry.mirror = tentry.mirror;

	data = ((block[tentry.Tile*4] >> 8)&0xFF) | ((block[tentry.Tile*4]&0xFF)<<8);
	if (bpp8) tentry.palette = 0;
	else tentry.palette = (data>>13)&3;
	tentry.depth = (data>>15)&1;

	return tentry;
}
void Sonic_Chunk256Converter(char *dstChunk, char *dstLayout, char *srcBlock, char *srcChunk, char *srcLayoutFG, char *srcLayoutBG, int act, bool bpp8)
{
	XeEngine::File f;
	XeEngine::Memory mFront, mBack;
	int chunkscount = 0;
	int chunk256count;
	Chunk256 chunk256tmp;

	XeEngine::Memory block_mem(0x400 * 4 * sizeof(unsigned short));
	XeEngine::Memory chunk_mem(0x400 * sizeof(Chunk));
	XeEngine::Memory chunk256_mem(0x100 * sizeof(ChunkConverted));

	unsigned short *block = (unsigned short*)block_mem.GetMemoryHandle();
	Chunk *chunk = (Chunk*)chunk_mem.GetMemoryHandle();
	ChunkConverted *chunk256 = (ChunkConverted*)chunk256_mem.GetMemoryHandle();

	XeEngine::MemoryFill(block, sizeof(block));
	if (!f.Open(XeEngine::String(srcBlock)))
	{
		printf("%s not found :(...", srcBlock);
		return;
	}
	f.Read(block, f.Size());

	XeEngine::MemoryFill(chunk, sizeof(chunk));
	chunk256[chunkscount++].Zero();
	if (!f.Open(XeEngine::String(srcChunk)))
	{
		printf("%s not found :(...", srcChunk);
		return;
	}
	chunk256count = f.Size()/sizeof(Chunk256) + 1;
	for(int i=1; i<chunk256count; i++)
	{
		f.Read(&chunk256tmp, sizeof(Chunk256));
		for(int j=0; j<4; j++)
		{
			for(int y=0; y<8; y++)
			{
				for(int x=0; x<8; x++)
				{
					chunk[chunkscount][y*8 + x] = BlockToTileS1(chunk256tmp[y*16 + x + ((j&1)*0x08) + ((j>>1)*0x80)], block, bpp8);
				}
			}
			for(int k=0; k<chunkscount+1; k++)
			{
				if (CompareChunks(chunk[k], chunk[chunkscount]))
				{
					chunk256[i].chunk128[j] = k;

					if (k == chunkscount)
						chunkscount++;		// Il chunk attuale non è stato trovato nei precedenti generati
					k = chunkscount;		// Sostanzialmente esce dal ciclo for al termine delle prossime operazioni
				}
			}
		}
	}
	f.Close();

	short dummy = 0;
	f.Create(XeEngine::String(dstChunk));
	f.Write(&chunkscount, 2);
	f.Write(&dummy, 2);
	f.Write(chunk, sizeof(Chunk) * chunkscount);
	f.Close();


	//////////////////////////////////////////////////////////////////////////
	// Layout
	const int layercount = 2;
	unsigned char mapWidth;
	unsigned char mapHeight;
	unsigned char backWidth;
	unsigned char backHeight;

	if (!f.Open(XeEngine::String(srcLayoutFG)))
	{
		printf("%s not found :(...", srcLayoutFG);
		return;
	}
	mFront.Alloc(f.Size() - 2);
	f.Read(&mapWidth, 1); mapWidth++;
	f.Read(&mapHeight, 1); mapHeight++;
	f.Read(mFront.GetMemoryHandle(), mFront.Size());
	f.Close();

	if (!f.Open(XeEngine::String(srcLayoutBG)))
	{
		printf("%s not found :(...", srcLayoutBG);
		return;
	}
	mBack.Alloc(f.Size() - 2);
	f.Read(&backWidth, 1); backWidth++;
	f.Read(&backHeight, 1); backHeight++;
	f.Read(mBack.GetMemoryHandle(), mBack.Size());
	f.Close();

	f.Create(XeEngine::String(dstLayout));

	MapProperties map;
	map.posx = 0;
	map.posy = 0;
	map.width = mapWidth;
	map.height = mapHeight;
	map.mapzone = act;
	map.layerCount = layercount;
	map.padding06 = map.padding07 = 0;
	f.Write(&map, sizeof(map));

	for(int i=0; i<map.layerCount; i++)
	{
		LayerProperties layer;
		layer.width = i == 0 ? mapWidth : backWidth;
		layer.height = i == 0 ? mapHeight : backHeight;
		layer.speedX = i == 0 ? 0x100 : 0x80;
		if (i == 1)
			layer.speedY = (unsigned short)(((float)backHeight / (float)map.height * 256.0f));
		else
			layer.speedY = 0x100;
		layer.collisionFlag = 0;
		layer.priority = i == 0 ? 0 : -1;
		f.Write(&layer, sizeof(layer));
	}
	for(int l=0; l<layercount; l++)
	{
		unsigned char mapwidth = l == 0 ? mapWidth : backWidth;
		unsigned char mapheight = l == 0 ? mapHeight : backHeight;
		unsigned char *data = l == 0 ? (unsigned char*)mFront.GetMemoryHandle() : (unsigned char*)mBack.GetMemoryHandle();

		for(int i=0; i<mapwidth*mapheight; i++)
		{
			ChunkConverted c = chunk256[data[i]&0x7F];
			f.Write(&c.chunk128[0], 2);
			f.Write(&c.chunk128[1], 2);
			f.Write(&c.chunk128[2], 2);
			f.Write(&c.chunk128[3], 2);
		}
	}
	f.Close();
}
void Sonic_Chunk256ConverterNEW(char *dstChunk, char *dstLayout, char *srcBlock, char *srcChunk, char *srcLayoutFG, char *srcLayoutBG, int act, bool bpp8)
{
	XeEngine::File f;
	XeEngine::Memory mFront, mBack;
	int chunkscount = 0;
	int chunk256count;
	Chunk256 chunk256tmp;

	XeEngine::Memory block_mem(0x400 * 4 * sizeof(unsigned short));
	XeEngine::Memory chunk_mem(0x400 * sizeof(Chunk));
	XeEngine::Memory chunk256_mem(0x100 * sizeof(ChunkConverted));

	unsigned short *block = (unsigned short*)block_mem.GetMemoryHandle();
	Chunk *chunk = (Chunk*)chunk_mem.GetMemoryHandle();
	ChunkConverted *chunk256 = (ChunkConverted*)chunk256_mem.GetMemoryHandle();

	if (!f.Open(XeEngine::String(srcBlock)))
	{
		printf("%s not found :(...", srcBlock);
		return;
	}
	f.Read(block, f.Size());

	XeEngine::MemoryFill(block, block_mem.Size());
	XeEngine::MemoryFill(chunk, chunk_mem.Size());
	XeEngine::MemoryFill(chunk256, chunk256_mem.Size());
	chunk256[chunkscount++].Zero();
	if (!f.Open(XeEngine::String(srcChunk)))
	{
		printf("%s not found :(...", srcChunk);
		return;
	}
	chunk256count = f.Size()/sizeof(Chunk256) + 1;
	for(int i=1; i<chunk256count; i++)
	{
		f.Read(&chunk256tmp, sizeof(Chunk256));
		for(int j=0; j<4; j++)
		{
			for(int y=0; y<8; y++)
			{
				for(int x=0; x<8; x++)
				{
					chunk[chunkscount][y*8 + x] = BlockToTileS1(chunk256tmp[y*16 + x + ((j&1)*0x08) + ((j>>1)*0x80)], block, bpp8);
				}
			}
			for(int k=0; k<chunkscount+1; k++)
			{
				if (CompareChunks(chunk[k], chunk[chunkscount]))
				{
					chunk256[i].chunk128[j] = k;

					if (k == chunkscount)
						chunkscount++;		// Il chunk attuale non è stato trovato nei precedenti generati
					k = chunkscount;		// Sostanzialmente esce dal ciclo for al termine delle prossime operazioni
				}
			}
		}
	}
	f.Close();

	short dummy = 0;
	f.Create(XeEngine::String(dstChunk));
	f.Write(&chunkscount, 2);
	f.Write(&dummy, 2);
	f.Write(chunk, sizeof(Chunk) * chunkscount);
	f.Close();


	//////////////////////////////////////////////////////////////////////////
	// Layout
	const int layercount = 2;
	unsigned char mapWidth;
	unsigned char mapHeight;
	unsigned char backWidth;
	unsigned char backHeight;

	if (!f.Open(XeEngine::String(srcLayoutFG)))
	{
		printf("%s not found :(...", srcLayoutFG);
		return;
	}
	mFront.Alloc(f.Size() - 2);
	f.Read(&mapWidth, 1); mapWidth++;
	f.Read(&mapHeight, 1); mapHeight++;
	f.Read(mFront.GetMemoryHandle(), mFront.Size());
	f.Close();

	if (!f.Open(XeEngine::String(srcLayoutBG)))
	{
		printf("%s not found :(...", srcLayoutBG);
		return;
	}
	mBack.Alloc(f.Size() - 2);
	f.Read(&backWidth, 1); backWidth++;
	f.Read(&backHeight, 1); backHeight++;
	f.Read(mBack.GetMemoryHandle(), mBack.Size());
	f.Close();

	f.Create(XeEngine::String(dstLayout));

	XeEngine::MapZone mapZone;
	mapZone.locationX = 0;
	mapZone.locationY = 0;
	mapZone.roomCount = 1;
	mapZone.unknow = 1;
	mapZone.Flags = 1;
	f.Write(&mapZone, sizeof(XeEngine::MapZone));

	XeEngine::MapRoom mapRoom;
	mapRoom.bg1LayerID = 0;
	mapRoom.fg1LayerID = 0;
	mapRoom.fg2LayerID = 0xFF;
	mapRoom.bg2LayerID = 0xFF;
	mapRoom.x = 0;
	mapRoom.y = 0;
	mapRoom.width = mapWidth;
	mapRoom.height = mapHeight;
	f.Write(&mapRoom, sizeof(XeEngine::MapRoom));

	for(int i=0; i<2; i++)
	{
		XeEngine::MapLayer layer;
		layer.width = i == 0 ? mapWidth : backWidth;
		layer.height = i == 0 ? mapHeight : backHeight;
		layer.dummy = 0;
		layer.parallaxID = 0xFF;
		f.Write(&layer, sizeof(layer));
	}
	for(int l=0; l<2; l++)
	{
		unsigned char mapwidth = l == 0 ? mapWidth : backWidth;
		unsigned char mapheight = l == 0 ? mapHeight : backHeight;
		unsigned char *data = l == 0 ? (unsigned char*)mFront.GetMemoryHandle() : (unsigned char*)mBack.GetMemoryHandle();

		for(int i = 0; i < mapheight * 2; i++)
		{
			for(int j = 0; j < mapwidth; j++)
			{
				ChunkConverted c = chunk256[data[j + (i / 2) * mapwidth]&0x7F];
				if ((i & 1) == 0)
				{
					f.Write(&c.chunk128[0], 2);
					f.Write(&c.chunk128[1], 2);
				}
				else
				{
					f.Write(&c.chunk128[2], 2);
					f.Write(&c.chunk128[3], 2);
				}
			}
		}
	}
	f.Close();
}

#endif