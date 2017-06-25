#include "XeLevel.h"
#include "XeShape.h"
#include <windows.h>


#define DEFAULT_DEPTHRESOLUTION	2
#define DEFAULT_RESWIDTH	320
#define DEFAULT_RESHEIGHT	240

XeLevel::XeLevel()
{
	// Zero filling the level's memories spaces
	currentAct = 0;
	stage.Zero();
	ZeroMemory(palette, sizeof(palette));
	ZeroMemory(chunk, sizeof(chunk));
	ZeroMemory(collision, sizeof(collision));
	ZeroMemory(collisionIndex, sizeof(collisionIndex));
	ZeroMemory(object, sizeof(object));

	// Initializing the arrays
	for(int i=0; i<OBJECT_COUNT; i++)
		objcont[i].filled = 0;
	for(int i=0; i<256*CLUT_COUNT; i++)
		palette[0][i][0] = 0xFFFFFFFF;

	// Inizializing the resolution values
	depthResolution = DEFAULT_DEPTHRESOLUTION;
	resWidth	= DEFAULT_RESWIDTH;
	resHeight	= DEFAULT_RESHEIGHT;
	chunkWidth	= resWidth / TEXTURE_TILE_WIDTH;
	chunkHeight	= resHeight / TEXTURE_TILE_HEIGHT;

	// Inizializing the camera values
	cameraX = cameraY = 0;
	border.Zero();
	borderLock.Zero();
	mainobject = NULL;

	// Other stuff XD
	ZeroMemory(&level, sizeof(level));
	ZeroMemory(objlist, sizeof(objlist));
	XeEngine::File f;
	f.Open(XeEngine::String("OBJECT\\OBJLIST.BIN"), true);
	f.Read(objlist, MIN(sizeof(objlist), f.Size()));
	f.Close();

	border.left = 0;
	border.right = 0x4000;
	border.top = 0;
	border.bottom = 0x800;
	_mapSelected = 0;

	stagestarted = false;
	timelevel = 0;
}
XeLevel::~XeLevel()
{
}

// Funzioni generiche della telecamera del livello
int XeLevel::GetResolution()
{
	return resWidth | (resHeight<<16);
}
void XeLevel::SetResolution(short width, short height)
{
	resWidth = width&~15;
	resHeight = height&~15;
	chunkWidth = (width>>4)+1;
	chunkHeight = (height>>4)+1;

	memTileCache.Free();
	memTileCache.Alloc(chunkWidth*chunkHeight*sizeof(TileEntry));
	tilecache = (TileEntry*)memTileCache.GetMemoryHandle();
}
byte XeLevel::GetDepthResolution()
{
	return depthResolution;
}
void XeLevel::SetDepthResolution(byte depthResolution)
{
	this->depthResolution = depthResolution;
	LoadGFXResolution();
}

//////////////////////////////////////////////////////////////////////////
// Funzioni generiche del livello
char *XeLevel::GetLevelName()
{
	return level.name;
}
byte XeLevel::GetMapSelected()
{
	return _mapSelected;
}
void XeLevel::SetMapSelected(byte n)
{
	_mapSelected = n;
}
byte XeLevel::GetMapCount()
{
	return level.mapCount;
}
void XeLevel::ResetLevel()
{
	XeShape::FadeInit(30, 1, 0xFF000000);
}
void XeLevel::StartStage()
{
	if (stagestarted) return;
	stagestarted = true;
	PlaceObjects();
}


//////////////////////////////////////////////////////////////////////////
// Funzioni di iterazione con gli oggetti
inline TileEntry XeLevel::GetBlock(short x, short y, byte levelWidth, byte levelHeight, short *layer)
{
	if (x < 0 || y < 0) return chunk[0][0];
	return chunk[
		layer[
			((x&8)>>3) +				// Carica il blocco 1 se i è un multiplo di 8, altrimenti il blocco 0
			(
				((x&~0xF)>>2)			// Carica il muro i/16
				% (levelWidth<<2)		// Filtra la larghezza per la ripetizione (simile a S3K)
			) +  
			((y&8)>>2) +				// Carica il blocco 2 se j è un multiplo di 8, altrimenti il blocco 0
			(
				((y&~0xF)>>2)
				% (levelHeight<<2)		// Filtra l'altezza per la ripetizione (S3K)
			) * levelWidth				// Carica il muro j/16
		]
	]
	[((x)&7) | (((y)&7)<<3)];
}
TileEntry XeLevel::GetBlock(short x, short y)
{
	short *layer = map.GetLayer(0);
	LayerProperties *prop = map.Layer(0);
	if (prop == NULL) {
		TileEntry t;
		t.Tile = 0;
		return t;
	}
	return GetBlock(x, y, prop->width, prop->height, layer);
}
short XeLevel::GetBlockIndex(short x, short y)
{
	return GetBlock(x, y).Tile;
}
byte XeLevel::GetCollisionIndex(short x, short y)
{
	return collisionIndex[0][GetBlockIndex(x, y)];
}
void XeLevel::GetCollision(Collision **c, short x, short y)
{
	*c = &collision[GetCollisionIndex(x, y)];
}
//////////////////////////////////////////////////////////////////////////
// Funzioni di disegno
void XeLevel::DrawLevel()
{
	DrawLayer(0);
}
void XeLevel::DrawLayer(int layer)
{
	/*// Caching the tiles
	memTileCache.Fill(0);
	short *layer = map->GetLayer(layer);
	short stride = map->Layer(layer)->width;
	short layerCameraX = cameraX>>20;
	short layerCameraY = cameraY>>20;
	short blockWidth = blkWidth;
	short blockHeight = blkHeight;
	if (blockWidth+layerCameraX > map->Layer(layer)->width<<4) blockWidth = (map->Layer(layer)->width<<4) - layerCameraX;
	if (blockHeight+layerCameraY > map->Layer(layer)->height<<4) blockHeight = (map->Layer(layer)->height<<4) - layerCameraY;

	for(int j=layerCameraY; j<blockHeight+layerCameraY; j++)
	{
		for(int i=layerCameraX; i<blockWidth+layerCameraX; i++)
		{
			short src1 = ((i&8)>>3) + ((i&~0xF)>>2) + ((j&8)>>2) + (((j&~0xF)>>2)*stride);
			short src2 = ((i)&7) | (((j)&7)<<3);
			src1 = src2;
			tilecache[i-layerCameraX + (j-layerCameraY)*blockWidth] = block[layer [((i&8)>>3) + ((i&~0xF)>>2) + ((j&8)>>2) + (((j&~0xF)>>2)*stride)] ] [((i)&7) | (((j)&7)<<3) ];
		}
	}
	// Rendering
	short prevPalette = -1;
	TileEntry tileblock;
	effect.UseProgram(true);
	effect.SetProperties(1);
	effect.SetClutTexture(levelLUT.GetID());
	effect.SetTexture();
	_scene->SetPosition(-(HIWORD(cameraX)&15), -(HIWORD(cameraY)&15));
	for(int j=0; j<_gameblockHeight; j++)
	{
		for(int i=0; i<_gameblockWidth; i++)
		{
			tileblock = tilecache[i + j*_gameblockWidth];
			if (tileblock.palette != prevPalette)
			{
				prevPalette = tileblock.palette;
				effect.SetClutIndex(prevPalette);
			}
			_scene->Push();
			_scene->MovePosition(8, 8);
			_scene->SetScale(tileblock.mirror ? -1.0f : 1.0f, tileblock.flip ? -1.0f : 1.0f);
			_scene->MovePosition(-8, -8);
			texture[tileblock.texture].Draw((tileblock.tile&0xF)<<4, tileblock.tile&0xF0, 16, 16, NULL);
			_scene->Pop();
			_scene->MovePosition(16, 0);
		}
		_scene->MovePosition(-16*_gameblockWidth, 16);
	}*/
}