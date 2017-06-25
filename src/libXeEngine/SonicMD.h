#pragma once
#include "Memory.h"
#include "File.h"

namespace Loader
{
	class SonicMD
	{
		typedef unsigned char Tile8[0x20];
		typedef unsigned char Tile16_4[0x80];
		typedef unsigned char Tile16_8[0x100];
	public:
		bool ToGFX_4bpp(char* gfxFileDst, char* gfxFile8x8, char* gfxFileMapping);
		bool ToGFX_8bpp(char* gfxFileDst, char* gfxFile8x8, char* gfxFileMapping, bool iSonic1);
	public:
	};
}