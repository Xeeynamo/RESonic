#pragma once

namespace XeEngine
{
	//! \brief The Memory Handle. It is a memory pointer
	typedef void* MemoryHandle;

	//! \brief The File Handle. This is an handle that only the Operating Systen knows how to manage it
	typedef void* FileHandle;
}

#include "List.h"
#include "Stack.h"
#include "DebugConsole.h"
extern DebugConsole con;

typedef signed char		sbyte;
typedef signed char		s8;
typedef unsigned char	byte;
typedef unsigned char	u8;
typedef signed short	sshort;
typedef signed short	s16;
typedef unsigned short	ushort;
typedef unsigned short	u16;
typedef signed int		sint;
typedef signed int		s32;
typedef unsigned int	uint;
typedef unsigned int	u32;
typedef unsigned int	Color;

#ifndef NULL
#define NULL 0
#endif

#define SAFE_DELETE(p)	if (p) { delete p; p = NULL; }
#define SAFE_ADELETE(p)	if (p) { delete[] p; p = NULL; }
#define FLOAT_COLOR_8BIT(c)	((float)((1.0/255.0)*(float)(c)))


#ifndef OPENGL_TYPE
#define OPENGL_TYPE OPENGL_TYPE_GL
#endif

#define CLAMP(i, min, max) (MIN(MAX(i, min), max))
#define SWAP32(i) ((i>>24) | (i<<24) | ((i>>8)&0xFF00) | ((i&0xFF00)<<8))
#define SWAP24(i) ((i&0xFF000000) | ((i&0xFF)<<16) | (i&0xFF00) | ((i&0xFF0000)>>16))
#define PFLOAT_TO_SHORT(i)	((i) / 65536)
#define PFLOAT_TO_FLOAT(i)	((float)(i) / 65536.0f)
#define FLOAT_TO_PFLOAT(i)	((PFloat)((i) * 65536.0f))
#define MAKERGB(r, g, b) MAKEARGB(0xFF, r, g, b)
#define MAKEARGB(a, r, g, b) ((a<<24)|(b<<16)|(g<<8)|(r<<0))

typedef int				PFloat; // Pseudofloat

union KeyInput
{
	struct
	{
		short up		: 1;
		short down		: 1;
		short left		: 1;
		short right		: 1;

		short cross		: 1;
		short circle	: 1;
		short square	: 1;
		short triangle	: 1;

		short trigL1	: 1;
		short trigR1	: 1;
		short trigL2	: 1;
		short trigR2	: 1;

		short trigL3	: 1;
		short trigR3	: 1;
		short select	: 1;
		short start		: 1;
	};
	short k;
};

struct XeColorF
{
	float r;
	float g;
	float b;
	float a;

	void Identity()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}
};

struct XeRect
{
	PFloat left, right, top, bottom;
	short Left()	{ return left / 0x10000; }
	short Right()	{ return right / 0x10000; }
	short Top()		{ return top / 0x10000; }
	short Bottom()	{ return bottom / 0x10000; }
};