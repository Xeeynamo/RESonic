#pragma once
#include <stdio.h>
#include <windows.h>
#include "IOLib.h"

#define R8G8B8A8_TO_R5G6B5(c) ( (((c)>>3)&0x1F) | (((c)>>5)&0x7E0) | (((c)>>8)&0xF800) )

enum GFXMode
{
	GFXMode_Undefined = 0,
	GFXMode_Monochrome = 1,
	GFXMode_4BPP = 2,
	GFXMode_8BPP = 3,
	GFXMode_16BPP = 4,
	GFXMode_24BPP = 5,
	GFXMode_32BPP = 6,
	GFXMode_Unknow = 7,
};

struct GFXHeader
{
	unsigned char headersize;
	unsigned char dstindex;			// Indice di destinazione.
	unsigned char width;			// Single texture width = width*4
	unsigned char height;			// Maximum size: 1024x1024
	unsigned char resolution;		// Display width: Real width = width*8/resolution
	unsigned char texturecount;		// REAL image height = height*8*resolution*texturecount
	unsigned char mode;
	unsigned char compressed	: 1;
	unsigned char internalpalette	: 1;
	unsigned char unk02	: 1;
	unsigned char unk03	: 1;
	unsigned char unk04	: 1;
	unsigned char unk05	: 1;
	unsigned char unk06	: 1;
	unsigned char unk07	: 1;
};

class GFXLib : public IOLib
{
private:
	GFXHeader _header;
	char _version;
protected:
public:
	GFXLib();
	~GFXLib();

	char GetVersion();
	void SetVersion(char version);

	int GetSize();
	void SetSize(short width, short height);
	char GetResolution();
	void SetResolution(char resolution);
	unsigned char GetTextureCount();
	void SetTextureCount(unsigned char count);
	unsigned char GetDestination();
	void SetDestination(unsigned char dstindex);
	GFXMode GetGFXMode();
	void SetGFXMode(GFXMode mode);
	bool GetFlagCompressed();
	void SetFlagCompressed(bool);
	bool GetFlagInternalPalette();
	void SetFlagInternalPalette(bool);

	bool OpenGFX();
	void SaveGFX();
};