#ifdef DEBUG

#include <stdio.h>
#include "Sonic.h"

char *sonic1_nem_levelart[] = 
{
	"s1\\artnem\\8x8 - GHZ1.bin",
	"s1\\artnem\\8x8 - LZ.bin",
	"s1\\artnem\\8x8 - MZ.bin",
	"s1\\artnem\\8x8 - SBZ.bin",
	"s1\\artnem\\8x8 - SLZ.bin",
	"s1\\artnem\\8x8 - SYZ.bin",
};

char *sonic1_kos_mapping[] = 
{
	"s1\\map16\\GHZ.bin",
	"s1\\map16\\LZ.bin",
	"s1\\map16\\MZ.bin",
	"s1\\map16\\SBZ.bin",
	"s1\\map16\\SLZ.bin",
	"s1\\map16\\SYZ.bin",
};
char *sonic1_level_gfx[] = 
{
	"LEVEL\\S1GHZ\\S1GHZ@1.GFX",
	"LEVEL\\S1LZ\\S1LZ@1.GFX",
	"LEVEL\\S1MZ\\S1MZ@1.GFX",
	"LEVEL\\S1SBZ\\S1SBZ@1.GFX",
	"LEVEL\\S1SLZ\\S1SLZ@1.GFX",
	"LEVEL\\S1SYZ\\S1SYZ@1.GFX",
};

void S1_GFXConverterAll()
{
	for(int i=0; i<6; i++)
	{
		char tmp1[0x80];
		char tmp2[0x80];

		printf("Extracting %s...\n", sonic1_level_gfx[i]);
		sprintf_s(tmp1, "%s_dec", sonic1_nem_levelart[i]);
		sprintf_s(tmp2, "%s_dec", sonic1_kos_mapping[i]);
		NDecomp(sonic1_nem_levelart[i], tmp1, 0);
		EDecomp(sonic1_kos_mapping[i], tmp2, 0, false);

		printf("Converting %s...\n", sonic1_level_gfx[i]);
		Sonic_GFXConverter8BPP(sonic1_level_gfx[i], tmp1, tmp2, true);
	}
}


char *sonic1_level_suffix[] =
{
	"S1GHZ", "S1MZ", "S1SYZ", "S1LZ", "S1SLZ", "S1SBZ", 
};
char *sonic1_art[] = 
{
	"8x8 - GHZ1", "8x8 - MZ", "8x8 - SYZ", "8x8 - LZ", "8x8 - SLZ", "8x8 - SBZ"
};
char *sonic1_map16[] = 
{
	"GHZ", "MZ", "SYZ", "LZ", "SLZ", "SBZ"
};
char *sonic1_map256[] = 
{
	"GHZ", "MZ (JP1)", "SYZ", "LZ", "SLZ", "SBZ (JP1)"
};
char *sonic1_background[][3] = 
{
	"GHZBG", "GHZBG", "GHZBG", 
	"MZ1BG", "MZ2BG", "MZ3BG", 
	"SYZBG (JP1)", "SYZBG (JP1)", "SYZBG (JP1)",
	"LZBG", "LZBG", "LZBG", 
	"SLZBG", "SLZBG", "SLZBG",
	"SBZ1BG", "SBZ2BG", "SBZ2BG"
};

void S1_LevelConvertAll()
{
	char srcCmpMap16[0x40];
	char srcCmpMap256[0x40];

	char dstLayout[0x40];
	char dstChunk[0x40];
	char srcBlock[0x40];
	char srcChunk[0x40];
	char srcLayoutFG[0x40];
	char srcLayoutBG[0x40];
	//char path_out
	for(int i=0; i<6; i++)
	{
		for(int j=1; j<=3; j++)
		{
			if (i == 6 && j == 3)
				return;
			printf("Decompressing %s act %i... ", sonic1_level_suffix[i], j);

			sprintf_s(dstLayout, "%s\\%s\\%s%i.%s", "LEVEL", sonic1_level_suffix[i], sonic1_level_suffix[i], j, "MAP");
			sprintf_s(dstChunk, "%s\\%s\\%s.%s", "LEVEL", sonic1_level_suffix[i], sonic1_level_suffix[i], "BLK");

			sprintf_s(srcCmpMap16, "%s\\%s\\%s.%s", "s1", "map16", sonic1_map16[i], "BIN");
			sprintf_s(srcCmpMap256, "%s\\%s\\%s.%s", "s1", "map256", sonic1_map16[i], "BIN");
			sprintf_s(srcBlock, "%s\\%s\\%s.%s_dec", "s1", "map16", sonic1_map16[i], "BIN");
			sprintf_s(srcChunk, "%s\\%s\\%s.%s_dec", "s1", "map256", sonic1_map16[i], "BIN");
			sprintf_s(srcLayoutFG, "%s\\%s\\%s%i.%s", "s1", "levels", sonic1_map16[i], j, "BIN");
			sprintf_s(srcLayoutBG, "%s\\%s\\%s.%s", "s1", "levels", sonic1_background[i][j-1], "BIN");

			EDecomp(srcCmpMap16, srcBlock, 0, false);
			KDecomp(srcCmpMap256, srcChunk, 0, false);

			printf("now converting...\n");
			//Sonic_Chunk256Converter(dstChunk, dstLayout, srcBlock, srcChunk, srcLayoutFG, srcLayoutBG, j, true);
			Sonic_Chunk256ConverterNEW(dstChunk, dstLayout, srcBlock, srcChunk, srcLayoutFG, srcLayoutBG, j, true);
		}


	}
}

#endif