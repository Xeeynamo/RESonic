#pragma once
#include "XeImage.h"

typedef struct
{
	byte headersize;
	byte dstindex;
	byte width;
	byte height;
	byte resolution;
	byte texturecount;
	byte mode;
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
} GFXStruct;

class GFX : public XeEngine::XeImage
{
protected:
	GFXStruct gfxstruct;
public:
	GFX();
	~GFX();

	bool Load(XeEngine::String&);
	void *GetTexturePointer();
	int Count();
	int DestinationIndex();
};