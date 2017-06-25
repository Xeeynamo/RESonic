#pragma once
#include "XeImage.h"

enum TGADataType
{
	TGADataType_NODATA			= 0,
	TGADataType_UNCINDEX		= 1,
	TGADataType_UNCRGB			= 2,
	TGADataType_UNCMONO			= 3,
	TGADataType_ENCINDEX		= 9,
	TGADataType_ENCRGB			= 10,
	TGADataType_CMPMONO			= 11,
	TGADataType_HUFFINDEX		= 32,
	TGADataType_HUFFINDEX4PASS	= 33,
};

#pragma pack(push, 1)
typedef struct
{
	char  idLength;
	char  colormapType;
	char  dataTypeCode;
	unsigned short  colormapOrigin;
	unsigned short  colormapLength;
	char  colormapDepth;
	unsigned short  xOrigin;
	unsigned short  yOrigin;
	unsigned short  width;
	unsigned short  height;
	char  bpp;
	char  imageDescriptor;
} TGAStruct;
#pragma pack(pop)


class TGA : public XeEngine::XeImage
{
protected:
	TGAStruct tgastruct;
public:
	TGA();
	~TGA();

	bool Load(XeEngine::String&);
};