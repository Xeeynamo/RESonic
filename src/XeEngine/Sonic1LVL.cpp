#ifdef DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Sonic.h"

const char *sonic1lvl = "S1LVL\\""S1";
const char *sonic1lvl_list[8] =
{
	"GHZ", "MZ", "SYZ",
	"LZ", "SLZ", "SBZ",
	"FZ", "END"
};

void S1LVL_GFXConverterAll()
{
	char pathIn8[0x100];
	char pathInBlocks[0x100];
	char pathOut[0x100];

	char pathIn8_dec[0x100];
	char pathInBlocks_dec[0x100];

	for(int i=6; i<8; i++)
	{
		for(int j=1; j<=3; j++)
		{
			printf("Decompressing %s act %i.", sonic1lvl_list[i], j);
			sprintf(pathIn8, "%s%s%i\\Tiles.bin", sonic1lvl, sonic1lvl_list[i], j);
			sprintf(pathInBlocks, "%s%s%i\\Blocks.bin", sonic1lvl, sonic1lvl_list[i], j);
			sprintf(pathOut, "LEVEL\\S1%s\\S1%s_act%i.GFX", sonic1lvl_list[i], sonic1lvl_list[i], j);

			sprintf(pathIn8_dec, "%s_dec", pathIn8);
			sprintf(pathInBlocks_dec, "%s_dec", pathInBlocks);
			KDecomp(pathIn8, pathIn8_dec, 0, false);
			printf(".");
			KDecomp(pathInBlocks, pathInBlocks_dec, 0, false);
			printf(".");

			printf("Converting %s...\n", pathOut);
			Sonic_GFXConverter(pathOut, pathIn8_dec, pathInBlocks_dec);
		}
	}
}
void S1LVL_BLKConverterAll()
{
	char pathInChunks[0x100];
	char pathInBlocks[0x100];
	char pathOut[0x100];

	char pathInChunks_dec[0x100];
	char pathInBlocks_dec[0x100];

	for(int i=0; i<8; i++)
	{
		for(int j=1; j<=3; j++)
		{
			printf("Decompressing %s act %i.", sonic1lvl_list[i], j);
			sprintf(pathInChunks, "%s%s%i\\Chunks.bin", sonic1lvl, sonic1lvl_list[i], j);
			sprintf(pathInBlocks, "%s%s%i\\Blocks.bin", sonic1lvl, sonic1lvl_list[i], j);
			sprintf(pathOut, "LEVEL\\S1%s\\S1%s_act%i.BLK", sonic1lvl_list[i], sonic1lvl_list[i], j);

			sprintf(pathInChunks_dec, "%s_dec", pathInChunks);
			sprintf(pathInBlocks_dec, "%s_dec", pathInBlocks);
			KDecomp(pathInChunks, pathInChunks_dec, 0, false);
			printf(".");
			KDecomp(pathInBlocks, pathInBlocks_dec, 0, false);
			printf(".");

			printf("Converting %s...\n", pathOut);
			Sonic_BlockConverter(pathOut, pathInChunks_dec, pathInBlocks_dec, false);
		}
	}
}
void S1LVL_ColIndexConvertAll()
{
	char pathIn[0x100];
	char pathOut[0x100];

	char pathIn_dec[0x100];

	for(int i=0; i<8; i++)
	{
		printf("Decompressing %s.", sonic1lvl_list[i]);
		sprintf(pathIn, "%s%s%i\\Indexes1.bin", sonic1lvl, sonic1lvl_list[i], 1);
		sprintf(pathOut, "LEVEL\\S1%s\\S1%s.CLI", sonic1lvl_list[i], sonic1lvl_list[i]);

		sprintf(pathIn_dec, "%s_dec", pathIn);
		KDecomp(pathIn, pathIn_dec, 0, false);
		printf("..");

		printf("Converting %s...\n", pathOut);
		Sonic_ColIndexConverter(pathOut, pathIn_dec, pathIn_dec);
	}
}
void S1LVL_MapConvertAll()
{
	char pathIn[0x100];
	char pathOut[0x100];

	char pathIn_dec[0x100];

	for(int i=0; i<8; i++)
	{
		for(int j=1; j<=3; j++)
		{
			printf("Decompressing %s.", sonic1lvl_list[i]);
			sprintf(pathIn, "%s%s%i\\Layout.bin", sonic1lvl, sonic1lvl_list[i], j);
			sprintf(pathOut, "LEVEL\\S1%s\\S1%s%i.MAP", sonic1lvl_list[i], sonic1lvl_list[i], j);

			sprintf(pathIn_dec, "%s_dec", pathIn);
			KDecomp(pathIn, pathIn_dec, 0, false);
			printf("..");

			printf("Converting %s...\n", pathOut);
			Sonic_MapConverter(pathOut, pathIn_dec, j);
		}
	}
}

#endif