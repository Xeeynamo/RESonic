#pragma once
#include "XeBase.h"
#include "XeMemory.h"

enum LUTFormat
{
	LUTFormat_Unknow	= 0,
	// 8 bit per color
	LUTFormat_RGB332	= 8,
	LUTFormat_BGR233	= 9,
	LUTFormat_ARGB2222	= 10,
	LUTFormat_BGRA2222	= 11,
	// 16 bit per color
	LUTFormat_RGB565	= 16,
	LUTFormat_BGR565	= 17,
	LUTFormat_XRGB1555	= 18,
	LUTFormat_XBGR1555	= 19,
	LUTFormat_ARGB1555	= 20,
	LUTFormat_BGRA5551	= 21,
	LUTFormat_ARGB4444	= 22,
	LUTFormat_BGRA4444	= 23,
	// 24 bit per color
	LUTFormat_RGB888	= 24,
	LUTFormat_BGR888	= 25,
	LUTFormat_ARGB1887	= 26,
	LUTFormat_BGRA8871	= 27,
	// 32 bit per color
	LUTFormat_XRGB8888	= 32,
	LUTFormat_BGRX8888	= 33,
	LUTFormat_ARGB8888	= 34,
	LUTFormat_BGRA8888	= 35,
};

struct LUTStruct 
{
	byte count;			// Quantità di palette nella LUT
	byte destination;	// Indice di destinazione
	byte format;		// LUTFormat
	byte colorsperpal		: 1;	// 0 = 16 colors, 1 = 256 colors
	byte destinationtype	: 2;	// 0 = shared, 1 = level, 2 = object, 3 = object with dynamic allocation
	byte dummy				: 5;
};

class LUT
{
private:
	LUTStruct header;
	XeEngine::Memory data;
	void *lut;
	byte *blut;
	ushort *wlut;
	uint *dlut;
protected:
public:
	LUT();
	~LUT();

	bool Load(char *filename);
	uint UnpackColor(byte index, byte palette);
	short PaletteCount();
	byte DestinationIndex();
	byte Format();
	short ColorsPerPalette();
};