#include "Map.h"
#include "Level.h"

XeEngine::Map::Map(Level& level)
{
	m_level = &level;
	layerCount[0] = layerCount[1] = layerCount[2] = layerCount[3] = 0;
}
XeEngine::Map::~Map()
{
	Unload();
}
void XeEngine::Map::Unload()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < layerCount[i]; j++)
		{
			delete[] layout[i][j];
		}
		layerCount[i] = 0;
	}
}
bool XeEngine::Map::Open(String& filename)
{
	File file;
	if (file.Open(filename) == false)
		return false;
	Unload();
	file.Read(&zone, sizeof(MapZone));
	file.Read(room, sizeof(MapRoom) * zone.roomCount);
	for(int i = 0; i < zone.roomCount; i++)
	{
		if (layerCount[0] < (room[i].layerID[0] + 1))
			layerCount[0] = (room[i].layerID[0] + 1);
		if (layerCount[1] < (room[i].layerID[1] + 1))
			layerCount[1] = (room[i].layerID[1] + 1);
		if (layerCount[2] < (room[i].layerID[2] + 1))
			layerCount[2] = (room[i].layerID[2] + 1);
		if (layerCount[3] < (room[i].layerID[3] + 1))
			layerCount[3] = (room[i].layerID[3] + 1);
	}
	for(int i = 0; i < 4; i++)
	{
		file.Read(layer[i], sizeof(MapLayer) * layerCount[i]);
	}
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < layerCount[i]; j++)
		{
			u16 size = layer[i][j].width * layer[i][j].height * 4;
			layout[i][j] = new ChunkAlloc[size];
			file.Read(layout[i][j], size * 2);
		}
	}
	return true;
}
u8 XeEngine::Map::GetRoomCount() const
{
	return zone.roomCount;
}
void XeEngine::Map::SetRoom(u8 roomIndex)
{
	if (roomIndex >= zone.roomCount)
		return;

	for(int i = 0; i < 4; i++)
	{
		if (room[roomIndex].layerID[i] != 0xFF)
		{
			m_level->layout[i] = layout[i][room[roomIndex].layerID[i]];
			m_level->layerProperties[i] = layer[i][room[roomIndex].layerID[i]];
		}
		else
		{
			m_level->layout[i] = nullptr;
			m_level->layerProperties[i].width = m_level->layerProperties[i].height = 0;
			m_level->layerProperties[i].parallaxID = 0xFF;
			m_level->layerProperties[i].dummy = 0;
		}
	}
	m_level->room = room[roomIndex];
}
void XeEngine::Map::GetMapZone(MapZone*& mapZone)
{
	mapZone = &zone;
}
bool XeEngine::Map::GetRoom(MapRoom*& mapRoom, u8 roomIndex)
{
	if (roomIndex >= zone.roomCount)
		return false;
	mapRoom = &room[roomIndex];
	return true;
}
bool XeEngine::Map::GetMapLayer(MapLayer*& mapLayer, u8 roomIndex, int layerIndex)
{
	if (roomIndex >= zone.roomCount)
		return false;
	if (layerIndex >= 4)
		return false;
	mapLayer = &layer[layerIndex][room[roomIndex].layerID[layerIndex]];
	return true;
}






MAP::MAP()
{
	XeEngine::MemoryFill(&properties, sizeof(properties));
	XeEngine::MemoryFill(layer, sizeof(layer));
	for(ptrdiff_t i=0; i < sizeof(layer) / sizeof(LayerProperties); i++)
	{
		layer[i].speedX = layer[i].speedY = 0x100;
	}
}
MAP::~MAP()
{
}

bool MAP::Load(char *filename)
{
	file.Close();
	if (!file.Open(XeEngine::String(filename)))
		return false;
	file.Read(&properties, sizeof(MapProperties));
	memLayer.Alloc(properties.layerCount * sizeof(LayerProperties));
	file.Read(layer, memLayer.Size());
	for(int i=0; i<properties.layerCount; i++)
	{
		layerdata[i].Alloc(layer[i].width*layer[i].height*sizeof(short)*4);
		file.Read(layerdata[i].GetMemoryHandle(), layerdata[i].Size());
	}
	return true;
}
bool MAP::Save(char *filename)
{
	file.Close();
	if (!file.Create(XeEngine::String(filename)))
		return false;
	file.Write(&properties, sizeof(MapProperties));
	file.Write(layer, properties.layerCount * sizeof(LayerProperties));
	for(int i=0; i<properties.layerCount; i++)
	{
		file.Write(layerdata[i].GetMemoryHandle(), layerdata[i].Size());
	}
	file.Close();
	if (!file.Open(XeEngine::String(filename)))
		return false;
	return true;
}

LayerProperties *MAP::Layer(int index)
{
	if (index >= this->properties.layerCount) return NULL;
	return layer+index;
}
void MAP::ResizeLayer(int index, int width, int height)
{
	int oldwidth = layer[index].width;
	int oldheight = layer[index].height;
	XeEngine::Memory old;
	layerdata[index] = old;
	layer[index].width = width;
	layer[index].height = height;
	layerdata[index].AllocZero(width*height*4*sizeof(XeEngine::Chunk));

	int widthdata = (width > oldwidth ? oldwidth : width)*sizeof(short)*4;
	int heightdata = height > oldheight ? oldheight : height;
	for(int i=0; i<heightdata; i++)
	{
		XeEngine::MemoryCopy((short*)layerdata[index].GetMemoryHandle() + i*width*4, (short*)old.GetMemoryHandle() + i*oldwidth*4, widthdata);
	}
}
short *MAP::GetLayer(int index)
{
	return (short*)layerdata[index].GetMemoryHandle();
}
