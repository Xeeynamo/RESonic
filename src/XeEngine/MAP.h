#pragma once
#include "XeMemory.h"
#include "XeFile.h"

namespace XeEngine
{
	struct MapZone
	{
		u16 locationX;
		u16 locationY;
		u16 unknow;
		u8 roomCount;
		union
		{
			u8 Flags;
			struct 
			{

			};
		};
	};
	struct MapRoom
	{
		u8 x, y;
		u8 width, height;
		u8 fg1LayerID;
		u8 bg1LayerID;
		u8 fg2LayerID;
		u8 bg2LayerID;
	};
	struct MapLayer
	{
		u8 width, height;
		u8 parallaxID;
		u8 dummy;
	};

	class Level;
	class Map
	{
	private:
		Level* m_level;
		u8 layerCount[4];

		MapZone zone;
		MapRoom room[0x100];
		MapLayer layer[4][0x100];
		u16* layout[4][0x100];

		void Unload();
	public:
		//! \brief The Map requires a level to operate on it
		//! \param A referement to the level
		~Map();

		//! \brief Open a MAP file
		//! \param Specify the filename
		bool Open(String&);

		//! \brief Get the room count of the current opened map
		u8 GetRoomCount() const;

		//! \brief Set a room
		//! \details This methos look's simple but it's the core that load an entire level's map that will be displayed on screen
		//! \param The room's index to load
		void SetRoom(u8);

	};
}

struct MapProperties
{
	unsigned char posx, posy;		// Posizione della mappa * 256
	unsigned char width, height;	// Altezza e larghezza della mappa * 256
	unsigned char mapzone;			// Zona della mappa. In Castlevania corrisponde all'ID di una minizona di un livello.
	unsigned char layerCount;
	unsigned char padding06;
	unsigned char padding07;
};
struct LayerProperties
{
	unsigned char width, height;	// Altezza e larghezza del layer * 256
	char priority;
	unsigned char collisionFlag;
	short speedX, speedY;
};
class MAP
{
private:
	XeEngine::File file;
	XeEngine::Memory memLayer;
	XeEngine::Memory layerdata[8];
protected:
	XeEngine::Memory data;
	LayerProperties layer[8];
public:
	MapProperties properties;
	MAP();
	~MAP();

	bool Load(char *filename);
	bool Save(char *filename);

	LayerProperties *Layer(int index);
	void ResizeLayer(int index, int width, int height);
	short *GetLayer(int index);
};