#error "Graphic.h obsolete, please use Graphics.h"
/*
#pragma once
#include "Video.h"
#include "List.h"
#include "String.h"
#include "Texture.h"

namespace XeEngine
{
	//! \brief Entity palette entry
	//! \details An entity palette defines the palette used by a single type of identity.
	struct EntityPalette
	{
		//! \brief The ID of the entity that handles these palettes
		UID entityId;
		//! \brief The count of the entity that uses this entry
		u16 entityCount;
		//! \brief The number of palette used by the entity
		u16 count;
		//! \brief The direct position of the palette entries
		u16 page[0x10];

		//! \brief Default EntityPalette configuration
		EntityPalette()
		{
			entityId = 0;
			entityCount = 0;
			count = 0;
		}
	};

	//! \brief Handle a LUT file
	struct LUTStruct 
	{
		//! \brief How Palette this LUT holds
		byte count;
		//! \brief Destination index (not used yet)
		byte destination;
		//! \brief Format (not used yet)
		byte format;
		//! \brief 0 = 16 colors, 1 = 256 colors
		byte colorsperpal		: 1;
		//! \brief 0 = shared, 1 = level, 2 = object, 3 = object with dynamic allocation
		byte destinationtype	: 2;
		//! \brief Unused
		byte dummy				: 5;
	};

	//! \brief Used for palette debugging
	//! \details This is used to define what file is associated by a LUTStruct
	struct LUTLoaded
	{
		LUTStruct lutStruct;
		char filename[0x40];
	};

	//! \brief Structure that describes how a layer should be managed
	struct TilemapHeader
	{
		u16 posx;		//! \brief Position X of the layer
		u16 posy;		//! \brief Position Y of the layer
		u8 visible;		//! \brief If the layer is visible or not
		u8 parallax;	//! \brief Select between horizontal (false) and vertical (true) parallax
		u8 texture;		//! \brief The texture where to get the tile graphic
		u8 priority;	//! \brief Less is the priority, more higher the layer will be. Value between 0 and 7
	};

	//! \brief Structure of a single tile
	struct TileEntry
	{
		union
		{
			struct
			{
				union
				{
					unsigned short Tile;
					struct
					{
						unsigned char tile;			// Tile da selezionare nella texture. Ci sono 256 tiles per texture
						unsigned char texture;		// Texture da selezionare. Ci sono in totale 256 texture, per un totale di 65536 tiles differenti
					};
				};
				unsigned char palette;				// 256 palette, per un totale di 4096 colori differenti. Si può scegliere tra i clut della mappa e i clut condivisi, per un totale di 512 clut.

				union
				{
					unsigned char Param;
					struct
					{
						unsigned char depth		: 1;	// Se sopra o sotto il layer object
						unsigned char flip		: 1;	// Tile vista al contrario
						unsigned char mirror	: 1;	// Tile vista a specchio
						unsigned char unknow    : 1;
						unsigned char path1		: 2;
						unsigned char path2		: 2;
					};
				};
			};

			u32 ToInt;
		};

		const bool operator == (const TileEntry& src)
		{
			return ToInt == src.ToInt;
		}
		const bool operator != (const TileEntry& src)
		{
			return ToInt != src.ToInt;
		}
	};

	//! \brief Number of layers
	const u8 c_TilemapCount = 4; 
	//! \brief The tilemap width
	const u8 c_TileMapWidth = 32;
	//! \brief The tilemap height
	const u8 c_TileMapHeight = 32;
	//! \brief Distance between two layers
	const u16 c_TilemapLayerOffset = c_TileMapWidth * c_TileMapHeight;

	//! \brief How colors they are in a single palette entry
	const u16 colorCount = 0x100;
	//! \brief How palettes they are in a single CLUT (palette's page)
	const u16 paletteCount = 0x100;
	//! \brief How CLUTs they are
	const u16 clutCount = 4;
	const float clutPage = 1.0f / clutCount;
	const float clutLine = 1.0f / (paletteCount * clutCount);
	const float clutSeparator = clutLine / 2.0f;
	const float clutIndexLevel = clutPage * 0;

	typedef Color32 Palette[colorCount];
	typedef Color32 Clut[paletteCount * colorCount];

	class Graphic
	{
#ifndef PUBLIC
		// DEBUGGING AND EDITOR RELEATED STUFF
	public:
		static XeEngine::List<LUTLoaded>* lutLoaded;
#endif
	private:
		//! \brief Cache the tile position
		static VertexTexture m_vtexCache[];
		// Polygon cache configuration
		static const u16 c_cacheSize = 0x4000;
		static const u16 c_cacheIndexSize = c_cacheSize / 4 * 6;
		// Polygon cache data
		static VertexPosition m_cachePosition[];
		static VertexTexture m_cacheTexcoord[];
		static VertexColor m_cacheColor[];
		static u16 m_cacheIndicies[];
		static u16 m_cacheIndex;
		// Palette data
		static const u16 c_paletteSize = 512;
		static u16 m_paletteEntityCount;
		static EntityPalette m_paletteEntity[];
		static u8 m_paletteEntityUsed[];
		// Tilemap data
		static TilemapHeader tilemapProperties[];
		static TileEntry tilemap[];
		// Game resolution
		static u16 resWidth;
		static u16 resHeight;
	protected:
		inline static void _LoadPalette(File&, LUTStruct&, u8, u8);
		inline static void _LoadPaletteRow(File&, LUTStruct&, u8, u8);
	public:
		//! \brief Holds the Color Look-up Table
		static Clut lut[];

		//! \brief Holds the render buffer
		static Texture texBuffer;

		//! \brief Initialize the graphic system
		static void Initialize();

		//! \brief Set the projection 2D
		static void SetProjection2D(u16 width, u16 height);

		//! \brief Send the vertices
		static void SendVertex2D(VertexPosition*, VertexTexture*, VertexColor* = nullptr);

		//! \brief Draw the buffer cache
		static void Flush2D();

		//! \brief Render to texture
		static void RenderToTexture(Texture&);

		//! \brief Load a palette with Entity placement
		//! \param The Entity ID
		//! \param The palette index
		//! \return Returns the palette position
		static u16 GetEntityPalette(const UID& id, u16 index);

		//! \brief Store a palette with Entity placement
		//! \param The name of the palette file
		//! \param The Entity ID
		//! \return Returns TRUE if the file was load successfully
		static bool SetEntityPalette(const String&, const UID& id);

		//! \brief Delete a Entity palette
		//! \param The Entity ID
		static void DeleteEntityPalette(const UID& id);

		//! \brief Load a new palette from a file
		//! \param The name of the file
		//! \param The row of the palette
		//! \param The working section
		//! \return Returns TRUE if the file was load successfully
		static bool LoadPalette(String&, u8 row, u8 section);

		//! \brief Set the dimension of the screen
		static u32 SetGameScreenDimension(u16 width, u16 height);

		//! \brief Get a tile from the specified layer and from the specified position
		static void GetTile(u16 layer, u8 posx, u8 posy, TileEntry&);
		//! \brief Set a tile on the specified layer and on the specified position
		static void SetTile(u16 layer, u8 posx, u8 posy, TileEntry&);
		//! \brief Get layer settings
		static TilemapHeader& GetLayerSetting(u16 layer);
		//! \brief Draw layer
		static void DrawLayer(u16 layer);
	};
}*/