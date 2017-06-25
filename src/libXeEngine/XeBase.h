#pragma once
// Inclusioni standard
#include <stddef.h>
// Processo delle definizioni built-in
#if _MSC_VER < 1500
#define nullptr NULL
#endif
#ifdef _WIN32
#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS
#endif
#endif
// Inclusione dell'header di piattaforma
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif

#include "DebugConsole.h"
extern DebugConsole con;

namespace XeEngine
{
	//! \brief The Memory Handle. It is a memory pointer
	typedef void* MemoryHandle;

	//! \brief The File Handle. This is an handle that only the Operating Systen knows how to manage it
	typedef void* FileHandle;

	//! \brief Hash code
	typedef size_t Hash;

	//! \brief ID code
	typedef size_t UID;

	//! \brief A color in 32 bit
	typedef unsigned int Color32;

	//! \brief A color in 16 bit
	typedef unsigned int Color16;

	//! \brief A color in 8 bit
	typedef unsigned int Color8;

	//! \brief Pixel formats for XeEngine::Video
	enum VideoPixelFormat
	{
		VideoPixelFormat_RGBA8888	= 0,
		VideoPixelFormat_RGB888		= 1,
		VideoPixelFormat_RGBA4444	= 2,
		VideoPixelFormat_RGB5A1		= 3,
		VideoPixelFormat_RGB565		= 4,
		VideoPixelFormat_A8			= 5,
		VideoPixelFormat_AI88		= 6,
	};
	struct TileEntry
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
	unsigned char palette;			// 256 palette, per un totale di 4096 colori differenti. Si può scegliere tra i clut della mappa e i clut condivisi, per un totale di 512 clut.

	unsigned char depth		: 1;	// Se sopra o sotto il layer object
	unsigned char flip		: 1;	// Tile vista al contrario
	unsigned char mirror	: 1;	// Tile vista a specchio
	unsigned char unknow    : 1;
	unsigned char path1		: 2;
	unsigned char path2		: 2;

	unsigned int ToInt()
	{
		return *(unsigned int*)this;
	}
};
}

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


#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void*)0)
#endif
#endif


#define FLOAT_COLOR_8BIT(c)	((float)((1.0f/255.0f)*(float)(c)))

#define SAFE_DELETE(p)	if (p != nullptr) { delete p; p = nullptr; }
#define SAFE_ADELETE(p)	if (p != nullptr) { delete[] p; p = nullptr; }
#define HIPART(i)	(((i)&0xFFFF0000)>>16)
#define LOPART(i)	((i)&0xFFFF)

#ifdef DLLEXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT //__declspec(dllimport)
#endif

/*#define XE_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const;\
public: virtual void Set##funName(varType var);*/
