#pragma once
#include "XeBase.h"
// Level 1
#include "Memory.h"
// Level 2
#include "Texture.h"
// Level 3
#include "Level.h"
// Level 4
#include "StageList.h"

namespace XeEngine
{
	class EXPORT Game
	{
	protected:
		static int RippleBackgroundMD[];
		static int RippleBackground[];
		static int RippleForeground[];

		StageList stageList;
		//! \brief Camera of the level
		Point camera;
		//! \brief The level attached to the game
		Level* level;
		//! \brief Holds the internal X resolution of the game
		u16 m_resolutionX;
		//! \brief Holds the internal Y resolution of the game
		u16 m_resolutionY;
		//! \brief Holds the internal X resolution of the game
		u16 m_resolutionZ;
		//! \brief Frame
		u32 m_frame;
		//! \brief The texture buffer
		Texture m_texbuffer;
	public:
		Game();
		virtual ~Game();

		//! \brief Initialize the game
		//! \warning This should be placed after Video::Initialize or this will crash
		void Initialize();

		//! \brief Execute the logic part of the game
		//! \details It execute the palette animations, updates the LUT texture
		void Do();

		//! \brief Execute the end instructions of the game
		//! \details It draw the content inside the texture buffer
		void End();

		//! \brief Use a texture as drawing device and draw it
		void TextureDraw();

		virtual void Run() = 0;

		//! \brief Get the associated level
		//! \return Returns the level
		Level* GetLevel();

		void LoadGFX(const String&);
		void LoadLUT(const String&);

		//! \brief Load a level
		//! \param Stage ID of the level
		//! \param Act of the level
		bool LoadLevel(StageID, Act);

		//! \brief Makes solid the CLUT's level
		//! \details By default, the first color of each palette is always transparent. With this you can decide to avoid this system and makes them solid
		//! \param TRUE if the CLUT will be solid, FALSE if it will be transparent
		//! \param TRUE for 16 palette in 4-bit color in a single 8-bit palette line
		//! \warning You can lose the original transparency value using this!
		void ClutSolid(bool solid, bool mode16 = false);

		//! \brief Set the game resolution and the details level
		void SetResolution(const u16, const u16, const u16);

		//! \brief Draw a tile
		//! \details This is a fast function to draw a single tile on the screen
		//! \param Coordinate X
		//! \param Coordinate y
		//! \param The Tile ID to draw
		//! \param The palette associated to the tile to draw
		//! \param 1 bit: depth, 2 bit: flip, 3 bit: mirror
		void DrawTile(float x, float y, u16 tile, u8 palette, u8 params);

		//! \brief Draw a chunk
		//! \details Fast function to draw a chunk
		//! \param Coordinate X
		//! \param Coordinate y
		//! \param The Chunk ID to draw
		void DrawChunk(float x, float y, u16 chunk);

		//! \brief Draw a level
		void DrawLevel();

		//! \brief Get the stage count
		u16 GetStageCount() const;
		//! \brief Get the stage properties
		void GetStageProperties(StageProperties&, u16 index);
		//! \brief Get the stage properties
		void GetStageIndexProperties(StageProperties&, u16 index);
	};
}
