#include "CSOTN.h"

Loader::CSOTN::CSOTN()
{

}
Loader::CSOTN::~CSOTN()
{

}
void Loader::CSOTN::Convert(u32& address, CSOTNAddr type)
{
	if (address < 0x80000000)
		return;
	switch(type)
	{
	case CSOTNAddr_None:
		address -= 0x80000000;
		break;
	case CSOTNAddr_Dra:
		address -= 0x800A0000;
		break;
	case CSOTNAddr_Map:
		address -= 0x80180000;
		break;
	}
}
bool Loader::CSOTN::Open(XeEngine::String& filename)
{
	filename = XeEngine::String("X:\\Reverse\\Castlevania SOTN\\ST\\ARE\\ARE.BIN");
	if (file.Open(filename) == false)
		return false;

	mapRoomCount = 0;
	objectGfxCount = 0;
	objectCount = 0;

	file.Read(&header, sizeof(Header));
	for(int i = 0; i < sizeof(Header) / sizeof(u32); i++)
	{
		Convert(((u32*)&header)[i], CSOTNAddr_Map);
	}

	if (header.roomDefPosition != 0)
	{
		file.Read(&mapProperties, sizeof(MapProperties));
		for(mapRoomCount; ; mapRoomCount++)
		{
			file.Seek(header.roomDefPosition + (mapRoomCount * 8));
			file.Read(&mapRoom[mapRoomCount], sizeof(MapRoom));
			
			// Entity GFX loader
			mapRoom[mapRoomCount].objGfxID -= (mapRoom[mapRoomCount].objGfxID == 0 ? 0 : 1);
			file.Seek(header.objectsGfx + (mapRoom[mapRoomCount].objGfxID * 4));
			u32 gfxOffset;
			file.Read(&gfxOffset, 4);
			Convert(gfxOffset, CSOTNAddr_Map);
			file.Seek(gfxOffset);
			int end;
			file.Read(&end, 4);
			while(end != -1)
			{
				file.Read(&objectGfx[objectGfxCount], sizeof(ObjectGFX));
				// DECOMPRESS STUFF
				file.Read(&end, 4);
				file.Seek(-4, XeEngine::FILESEEK_CUR);
			}

			// Entity placement loader
			file.Seek(mapProperties.baseObjectPlacement + (mapRoom[mapRoomCount].objLayoutID * 4));
			u32	objectPlacementAddress;
			file.Read(&objectPlacementAddress, 4);
			Convert(objectPlacementAddress, CSOTNAddr_Map);
			file.Seek(objectPlacementAddress);
			while(true)
			{
				ObjectPlacement* o = &objectPlacement[objectCount];
				file.Read(o, sizeof(ObjectPlacement));
				if (!(o->x == -1 && o->y == -1))
				{
					// Add entity
				}
				else break;
			}

			if (mapRoom[mapRoomCount].tileGfxID != 0xFF)
			{
				file.Seek(header.tilesLayout + (mapRoom[mapRoomCount].layoutID * 8));
				u32 fgAddr;
				u32 bgAddr;
				file.Read(&fgAddr, 4);
				file.Read(&bgAddr, 4);
				if (!(fgAddr == 0 && bgAddr == 0))
				{
					Convert(fgAddr, CSOTNAddr_Map);
					Convert(bgAddr, CSOTNAddr_Map);
					ReadLayer(fgAddr, mapRoomLayer[mapRoomCount][0]);
					ReadLayer(bgAddr, mapRoomLayer[mapRoomCount][1]);
				}
			}
		}
	}
	return true;
}
void Loader::CSOTN::ReadLayer(u32 address, Layer& layer)
{
	u32 posTileMapProperties;
	LayerProperties layerProperties;

	file.Seek(address);
	file.Read(&address, 4);
	Convert(address, CSOTNAddr_Map);
	file.Read(&posTileMapProperties, 4);
	Convert(posTileMapProperties, CSOTNAddr_Map);
	file.Read(&layerProperties, sizeof(LayerProperties));
	file.Seek(posTileMapProperties);

	u32 posTexture;
	u32 posTile;
	u32 posPalette;
	u32 posCollision;
	file.Read(&posTexture, 4);
	file.Read(&posTile, 4);
	file.Read(&posPalette, 4);
	file.Read(&posCollision, 4);

	layer.properties = layerProperties;
	layer.layout = new MapTile[(size_t)(layerProperties.Width() * layerProperties.Height())];
	MapTile* t = layer.layout;
	for(u16 i = 0; i < layerProperties.Height(); i++)
	{
		for(u16 j = 0; j < layerProperties.Width(); j++)
		{
			MapTile tile;
			u16 masterPosition;
			file.Seek(address + (i * layerProperties.Width() * 2) + (j * 2));
			file.Read(&masterPosition, 2);
			file.Seek(masterPosition + posTexture);
			file.Read(&tile.texture, 1);
			file.Seek(masterPosition + posTile);
			file.Read(&tile.tile, 1);
			file.Seek(masterPosition + posPalette);
			file.Read(&tile.palette, 1);
			file.Seek(masterPosition + posCollision);
			file.Read(&tile.collision, 1);
			*t++ = tile;
		}
	}
}