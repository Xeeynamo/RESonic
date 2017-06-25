#ifdef DEBUG
#include "CSOTN.h"
#include "XeFile.h"
#include "GFX.h"
#include "LUT.h"
#include <stdio.h>

char *CSOTN_Levels[] =
{
	"ARE", "CAT", "CEN", "CHI", "DAI", "DRE", "LIB", "MAD",
	"NO0", "NO1", "NO2", "NO3", "NO4", "NP3", "NZ0", "NZ1",
	"RARE", "RCAT", "RCEN", "RCHI", "RDAI", "RLIB", "RTOP",
	"RNO0", "RNO1", "RNO2", "RNO3", "RNO4", "RNZ0", "RNZ1",
	"SEL", "ST0", "TOP", "WRP",
};

void CSOTN_TotalExport(char *file_in, char *file_out)
{
	char pathIn[0x100];
	char pathOut[0x100];
	int elements = sizeof(CSOTN_Levels)/sizeof(char*);
	for(int i=0; i<elements; i++)
	{
		sprintf_s(pathIn, "%s\\%s\\F_%s.bin", file_in, CSOTN_Levels[i], CSOTN_Levels[i]);

		sprintf_s(pathOut, "%s\\F_%s.GFX", file_out, CSOTN_Levels[i]);
		CSOTN_GFXConverter(pathIn, pathOut);
		sprintf_s(pathOut, "%s\\F_%s.LUT", file_out, CSOTN_Levels[i]);
		CSOTN_CLUTConverter(pathIn, pathOut);
	}
}

void CSOTN_GFXConverter(char *file_in, char *file_out)
{
	const int stride = 128/2;
	byte buf[stride];

	XeEngine::File fIn, fOut;
	if (!fIn.Open(XeEngine::String(file_in), true)) return;
	if (!fOut.Create(XeEngine::String(file_out))) return;

	GFXStruct gfxstruct;
	gfxstruct.width = gfxstruct.height = 256/4;
	gfxstruct.dstindex = 0;
	gfxstruct.flags = 0;
	gfxstruct.headersize = sizeof(GFXStruct);
	gfxstruct.mode = 2;
	gfxstruct.resolution = 1;
	gfxstruct.texturecount = 8;
	fOut.Write(&gfxstruct, sizeof(GFXStruct));

	for(int j=0; j<16*0x4000; j+=0x4000)
	{
		for(int i=0; i<128*128/2; i+=stride)
		{
			fIn.Seek(i+j, XeEngine::FILESEEK_SET);
			fIn.Read(buf, stride);
			fOut.Write(buf, stride);

			fIn.Seek(i+j + 0x2000, XeEngine::FILESEEK_SET);
			fIn.Read(buf, stride);
			fOut.Write(buf, stride);
		}
	}
	fOut.Close();
}
void CSOTN_CLUTConverter(char *file_in, char *file_out)
{
	int header = 0xDEC0ADDE;
	const int bufSize = 0x400;
	byte buf[bufSize];

	XeEngine::File fIn, fOut;
	if (!fIn.Open(XeEngine::String(file_in), true)) return;
	if (!fOut.Create(XeEngine::String(file_out))) return;

	LUTStruct lut;
	lut.destination = 0;
	lut.count = 0;
	lut.format = 19;
	lut.colorsperpal = 0;

	fOut.Write(&header, 4);
	fOut.Write(&lut, sizeof(LUTStruct));

	for(int i=0; i<4; i++)
	{
		fIn.Seek(0x5C00 + i*0x8000, XeEngine::FILESEEK_SET);
		fIn.Read(buf, bufSize);
		fOut.Write(buf, bufSize);

		fIn.Seek(0x7C00 + i*0x8000, XeEngine::FILESEEK_SET);
		fIn.Read(buf, bufSize);
		fOut.Write(buf, bufSize);
	}
}

#endif