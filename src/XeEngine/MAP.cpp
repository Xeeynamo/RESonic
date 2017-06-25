#include "Map.h"
#include "XeLevel.h"

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
		if (layerCount[0] < room[i].fg1LayerID)
			layerCount[0] = room[i].fg1LayerID;
		if (layerCount[1] < room[i].bg1LayerID)
			layerCount[1] = room[i].bg2LayerID;
		if (layerCount[2] < room[i].fg2LayerID)
			layerCount[2] = room[i].fg2LayerID;
		if (layerCount[3] < room[i].bg2LayerID)
			layerCount[3] = room[i].bg2LayerID;
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
			layout[i][j] = new u16[size];
			file.Read(layout[i][j], size);
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
}






MAP::MAP()
{
	XeEngine::MemoryFill(&properties, sizeof(properties));
	XeEngine::MemoryFill(layer, sizeof(layer));
	for(int i=0; i<sizeof(layer) / sizeof(LayerProperties); i++)
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
	layerdata[index].AllocZero(width*height*4*sizeof(64*4));

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