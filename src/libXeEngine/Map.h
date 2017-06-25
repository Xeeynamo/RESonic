#pragma once
#include "Memory.h"
#include "File.h"

namespace XeEngine
{
	//! \brief The header of a map file
	struct MapZone
	{
		//! \brief The X position of the map
		//! \details NOTE: The position is multiplied by 256
		u16 locationX;
		//! \brief The Y position of the map
		//! \details NOTE: The position is multiplied by 256
		u16 locationY;
		//! \brief The Z position of the map
		//! \details NOTE: The position is multiplied by 256
		u16 locationZ;
		//! \brief Count of included rooms in this map
		u8 roomCount;
		union
		{
			u8 Flags;
			struct 
			{

			};
		};
	};
	//! \brief The header for each room inside a single map
	struct MapRoom
	{
		//! \brief X position multiplied by 256
		u8 x;
		//! \brief Y position multiplied by 256
		u8 y;
		//! \brief Width of the room multiplied by 256
		//! \details When the value is 0, the value is 256
		u8 width;
		//! \brief Height of the room multiplied by 256
		//! \details When the value is 0, the value is 256
		u8 height;
		//! \brief Layers to load
		//! \details The layers are primary foreground (where the main game happens), primary background, secondary foreground and secondary background
		u8 layerID[4];

		int GetLayersCount()
		{
			return layerID[0] != 0xFF ? 1 : 0 +
				layerID[1] != 0xFF ? 1 : 0 +
				layerID[2] != 0xFF ? 1 : 0 +
				layerID[3] != 0xFF ? 1 : 0;
		}
	};
	//! \brief The header for each layerinside a single map
	struct MapLayer
	{
		//! \brief Width of the layer multiplied by 256
		//! \details When the value is 0, the value is 256
		u8 width;
		//! \brief Height of the layer multiplied by 256
		//! \details When the value is 0, the value is 256
		u8 height;
		//! \brief The parallax ID associated to the layer
		u8 parallaxID;
		//! \brief Not implemented yet
		//! \warning RESERVED USE FOR FUTURE
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
		//! \param A reference to the level
		Map(Level&);
		~Map();

		//! \brief Open a MAP file
		//! \param Specify the filename
		bool Open(String&);

		//! \brief Get the room count of the current opened map
		u8 GetRoomCount() const;

		//! \brief Set a room
		//! \details This methos look's simple but it's the core that load an entire level map that will be displayed on screen
		//! \param The room's index to load
		void SetRoom(u8 roomIndex);

		//! \brief Get the properties of the current map zone
		//! \returns The structure that contains the properties of map zone
		void GetMapZone(MapZone*&);

		//! \brief Get the properties of the current map zone
		//! \param The structure that contains the properties of map room
		//! \param The room index
		//! \return If the room index specified is invalid, the return value will be false and MapRoom will not be modified
		bool GetRoom(MapRoom*&, u8 roomIndex);

		//! \brief Get the properties of the current map layer
		//! \param The structure that contains the properties of map layer
		//! \param The room index
		//! \param The layer index
		//! \return If the room index or the layer index specified is invalid, the return value will be false and MapLayer will not be modified
		bool GetMapLayer(MapLayer*&, u8 roomIndex, int layerIndex);
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