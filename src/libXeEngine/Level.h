#pragma once
#include "XeBase.h"
#include "String.h"
#include "List.h"
#include "Texture.h"
#include "Map.h"
#include "Stage.h"
#include "Graphics.h"

namespace XeEngine
{
	//! \brief Tile size in pixel
	const u16 tileSize = 16;
	//! \brief The maximum tiles count
	const u16 tileCount = 0x1000;
	//! \brief How tiles are in a chunk
	const u16 chunkSize = 8;
	//! \brief Absolute size in pixel of a chunk
	const u16 chunkSizeAbsolute = tileSize * chunkSize;
	//! \brief The maximum chunks count
	const u16 chunkCount = 0x400;
	//! \brief The maximum hitboxes count
	const u16 hitboxCount = 0x100;
	//! \brief The maximum count of collision paths
	const u16 collisionPathCount = 2;
	//! \brief The maximum size of a level in pixel
	const u16 levelSizeAbsolute = 0x8000;
	//! \brief The maximum size of a level misured in chunks
	const u16 levelSize = levelSizeAbsolute / chunkSizeAbsolute;
	//! \brief The maximum count of layers
	const u16 layersCount = 4;
	//! \brief The horizontal entity's screen range
	const u16 EntityScreenRangeH = 400;
	//! \brief The vertical entity's screen range
	const u16 EntityScreenRangeV = 300;

	//! \brief Tile size in floating point
	const float tileSizef = (float)tileSize;
	//! \brief Layer Z priority
	const float LayerZPriority[layersCount] = {+0.0f, -1.0f, +1.0f, -2.0f};

	//! \brief A single chunk container
	typedef TileEntry Chunk[chunkSize*chunkSize];
	//! \brief The space needed to addressing a chunk in a map
	typedef u16 ChunkAlloc;
	//! \brief A single hitbox descriptor
	typedef s8 Collision[tileSize];
	//! \brief Act index
	typedef u8 Act;

	class Entity;
	class PaletteAnimation;
	class EXPORT Level
	{
		friend void XeEngine::Map::SetRoom(u8);
	public:
		struct EXPORT RippleEffect
		{
			int* data;
			u16 size;
			u16 frame;

			RippleEffect()
			{
				Default();
			}
			void Default()
			{
				const static int fakedata = 0;
				Load((int*)&fakedata, 1);
			}
			void Load(int* deform, u16 length)
			{
				data = deform;
				size = length;
				frame = 0;
			}
		};

		//! \brief Holds the UV data to draw easily the tiles of the level
		//! \details 256 are tile number of tiles on a single texture; every tile can handle source and destination U and V, both with normal, flip, mirror and flip+mirror
		float tileUV[tileCount][4][4];

		//! \brief Level set (Menu, Level, Special Stage, Bonus Stage, etc.)
		int m_levelset;
		//! \brief The current zone (Green Hill Zone, Emerald Hill Zone etc)
		int m_zone;
		//! \brief The current room (Castlevania specific)
		int m_room;
		//! \brief The current act (GHZ Act 1)
		int m_act;
		//! \brief Holds the tile redirecting for tile animations; useful for dynamic tiles
		u16 tileredir[tileCount];
		//! \brief Holds the chunks of the level
		Chunk chunk[chunkCount];
		//! \brief Holds the hitbox description for floor tiles
		Collision hitboxFloor[hitboxCount];
		//! \brief Holds the hitbox description for wall tiles
		Collision hitboxWall[hitboxCount];
		//! \brief Holds the hitbox angle description
		u8 hitboxAngle[hitboxCount];
		//! \brief Holds the hitbox indexes
		u8 collisionIndex[collisionPathCount][tileCount];
		//! \brief Holds the structure that contain the entire map of the zone
		Map* map;
		//! \brief Holds the informations of the current room loaded
		MapRoom room;
		//! \brief Holds the layers properties of a room
		MapLayer layerProperties[layersCount];
		//! \brief Holds the layers visibility of a room
		bool layerVisible[layersCount];
		//! \brief Holds the layout of a room
		u16* layout[layersCount];
		//! \brief Holds all the informations about a stage that contains various Acts
		Stage stage;
		//! \brief The primary entity
		Entity* primaryEntity;
		//! \brief Holds the game's resolution
		u8 resolution;
		//! \brief Holds the horizontal viewport
		u16 viewH;
		//! \brief Holds the vertical viewport
		u16 viewV;
		//! \brief Holds the game's time
		u32 m_timer;
		//! \brief Tells if the time is enabled or not
		bool timerEnabled;
		//! \brief Holds the informations about the camera X
		s16 cameraX;
		//! \brief Holds the informations about the camera Y
		s16 cameraY;
		//! \brief Holds the informations about the camera X
		s16 postCameraX;
		//! \brief Holds the informations about the camera Y
		s16 postCameraY;
		//! \brief Holds the parallax position
		int parallaxPosition[0x100];
		//! \brief Holds the parallax speed
		int parallaxSpeed[0x100];
		//! \brief Holds the parallax factor
		int parallaxFactor[0x100];
		//! \brief Holds the final parallax coordinates
		int parallaxCoords[0x100];
		//! \brief Holds the associated lines
		u8 parallaxIndex[levelSizeAbsolute];
		//! \brief Handle the shake X value
		s8 screenShakeX;
		//! \brief Handle the shake Y value
		s8 screenShakeY;

		//! \brief Manage the tiles of the level
		Texture gfxLevel;
		//! \brief Manage the palette of the level
		Texture lutLevel;

		// Ripple effect
		RippleEffect ripple[layersCount];

		//! \brief A container for Palette animations
		List<PaletteAnimation*> listPaletteAnimation;
	public:
		Level();
		~Level();

		//! \brief Initialize the level engine
		//! \details Create the needed textures
		void Initialize();

		//! \brief Get the game's resolution
		u8 GetResolution() const;

		//! \brief Change the game's resolution
		//! \param Resolution to set
		//! \warning The changes will be affected only with a level's restart
		void SetResolution(u8);

		//! \brief Get the level view in pixel
		void GetView(u16& width, u16& height) const;

		//! \brief Set the level view in pixel
		//! \warning height can't be more than 256
		void SetView(u16 width, u16 height);

		//! \brief Load a file that contains the stage properties
		//! \details This doesn't load the real level
		//! \param File's name with .STG extension
		bool LoadStage(String&);

		//! \brief Load an act
		//! \details This will load the real level; it should be called after a successful call of LoadStage
		//! \param Specify the act to play
		//! \return Returns FALSE if the act couldn't be loaded, usually because the call was placed before LoadStage or the act was not found
		bool LoadAct(Act);

		//! \brief Load a new chunk descriptor from a file
		//! \param The name of the file
		//! \return Returns TRUE if the file was load successfully
		bool LoadChunk(String&);

		//! \brief Load a new hitbox descriptor from a file
		//! \param The name of the file
		//! \return Returns TRUE if the file was load successfully
		bool LoadHitbox(String&);

		//! \brief Load a new collision index descriptor from a file
		//! \param The name of the file
		//! \return Returns TRUE if the file was load successfully
		bool LoadCollisionIndex(String&);

		//! \brief Load a new dynamic palette descriptor from a file
		//! \param The name of the file
		//! \return Returns TRUE if the file was load successfully
		bool LoadDynamicPalette(String&);

		//! \brief Returns the current act
		//! \details The Act returned is the last Act passd to LoadAct
		//! \return Returns the current act
		Act GetCurrentAct();

		//! \brief Load a palette with Entity placement
		//! \param The Entity ID
		//! \param The palette index
		//! \return Returns the palette position
		u16 GetEntityPalette(const UID& id, u16 index);

		//! \brief Load a palette with Entity placement
		//! \param The name of the file
		//! \param The Entity ID
		//! \return Returns TRUE if the file was load successfully
		bool SetEntityPalette(const String&, const UID& id);

		//! \brief Delete a Entity palette
		//! \param The Entity ID
		void DeleteEntityPalette(const UID& id);

		//! \brief Get the TileEntry of the layer specified
		//! \param X coord in tile
		//! \param Y coord in tile
		//! \param The layer where the tile will be extracted
		TileEntry GetLevelTile(s16 tileX, s16 tileY, int layer);

		//! \brief Get the Chunk ID of the layer specified
		//! \param X coord in tile
		//! \param Y coord in tile
		//! \param The layer where the chunk will be extracted
		u16 GetLevelChunk(u16 tileX, u16 tileY, int layer);

		//! \brief Get the primary entity
		Entity* GetPrimaryEntity();
		//! \brief Set the primary entity
		void SetPrimaryEntity(Entity*);

		//! \brief Returns the right GFX with the existing resolution
		//! \details From the input string, it checks all the resolutions from the specified resolution to 1 and returns the found's GFX
		//! \param The path to scan. After this call, the passed param will be edited with the compatible GFX
		//! \param Maximum resolution to check
		//! \details Returns the resolution of the founed GFX
		u8 CheckGFXResolution(String&, u8);

		//! \brief Build the path for a specific level's file
		//! \param A referement to the output string
		//! \param Stage's act
		//! \param File's type
		void BuildPath(String&, Act, STAGEFILE);

		//! \brief Update all the variables
		void UpdateLevel();

		//! \brief Update the shake valeus
		void UpdateShake();

		//! \brief Update the parallx position
		void UpdateParallax();

		//! \brief Process the camera, shaking it
		void ProcessCamera();

		//! \brief Process the camera, shaking it
		void ProcessShake();

		//! \brief Update the palette
		//! \details Send the new palette to the hardware texture
		void RefreshPalette();

		//! \brief Update the palette
		//! \details It runs the palette animations and send the new palette to the hardware texture
		void UpdatePalette();

		//! \brief Add a palette animation
		//! \param The pointer to an already created PaletteAnimation
		//! \warning All the palette animations will be deleted from ResetPaletteAnimation
		void AddPaletteAnimation(PaletteAnimation*);

		//! \brief Delete all the palette animations
		void ResetPaletteAnimation();

		//! \brief Get the timer's count
		u32 GetTimer() const;
		//! \brief Set the timer's count
		void SetTimer(u32);
		//! \brief Advance the timer
		void TickTimer();
		//! \brief Check if the timer is enabled
		bool GetTimerEnabled() const;
		//! \brief Enable or disable the timer
		void SetTimerEnabled(bool);
		//! \brief Get the camera X
		s16 GetCameraX() const;
		//! \brief Get the camera Y
		s16 GetCameraY() const;

		//! \brief Draw a level's layer without to use parallax effects
		void DrawLayer(s16 positionx, s16 positiony, s16 camerax, s16 cameray, u16 width, u16 height, u8 layer);
		//! \brief Draw a level's layer using the parallax scrolling
		void DrawLayerParallax(u8 layer);
	};
}