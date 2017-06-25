#include "Memory.h"

namespace XeEngine
{
	enum STAGEFILE
	{
		//! \brief Tiles graphic
		STAGEFILE_GFX,
		//! \brief Color Look-up Table
		STAGEFILE_LUT,
		//! \brief Collision index
		STAGEFILE_CLI,
		//! \brief Collision mask
		STAGEFILE_HBX,
		//! \brief Map's layout
		STAGEFILE_MAP,
		//! \brief Chunk's layoyt
		STAGEFILE_BLK,
		//! \brief Default object placement
		STAGEFILE_RNG,
		//! \brief Objects placement
		STAGEFILE_OBP,
		//! \brief Background deformation
		STAGEFILE_DEF,
		//! \brief Dynamic tiles
		STAGEFILE_DTL,
		//! \brief Dynamic palette
		STAGEFILE_DPL,
		//! \brief Custom title card
		STAGEFILE_CRD,
		//! \brief Main BGM of the stage
		STAGEFILE_BGM,
	};

	struct StageAct
	{
		char *gfx;
		char *clut;
		char *cli;
		char *hbx;
		char *map;
		char *blk;
		char *rng;
		char *obp;
		char *def;
		char *dtl;
		char *dpl;
		char *crd;
		char *bgm;
	};

	class EXPORT Stage
	{
	public:
		Memory mem;
		StageAct* act;
		char* name;
		char* suffix;

		u8 resoultions;
		u8 actCount;
		u8 hideTitleCard;

		Stage()
		{
			act = nullptr;
			name = nullptr;
			suffix = nullptr;

			resoultions = 0;
			actCount = 0;
			hideTitleCard = 0;
		}
		~Stage()
		{
			Free();
		}
		void Free()
		{
			SAFE_ADELETE(act);
			SAFE_ADELETE(name);
			SAFE_ADELETE(suffix);
		}
	};
}