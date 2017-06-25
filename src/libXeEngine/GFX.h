#pragma once
#include "Image.h"

namespace XeEngine
{
	namespace ImageFramework
	{
		struct GFXStruct
		{
			byte headersize;
			byte dstindex;
			byte width;
			byte height;
			byte resolution;
			byte texturecount;
			byte format;
			union
			{
				struct Flags
				{
					byte compressed		: 1;
					byte includepalette	: 1;
					byte unk2			: 1;
					byte unk3			: 1;
					byte unk4			: 1;
					byte unk5			: 1;
					byte unk6			: 1;
					byte unk7			: 1;
				};
				byte flags;
			};
		};
		bool GFX(Image&, void*, size_t);
	}
}