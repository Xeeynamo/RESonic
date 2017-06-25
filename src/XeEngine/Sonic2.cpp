#ifdef DEBUG
#include <stdio.h>
#include "Sonic.h"

char *sonic2_kon_levelart[] = 
{
	"s2\\art\\kosinski\\EHZ_HTZ.bin", NULL,
	"s2\\art\\kosinski\\CPZ_DEZ.bin", NULL,
	"s2\\art\\kosinski\\ARZ.bin", NULL,
	"s2\\art\\kosinski\\CNZ.bin", NULL,
	"s2\\art\\kosinski\\EHZ_HTZ.bin", "s2\\art\\kosinski\\HTZ_Supp.bin",
	"s2\\art\\kosinski\\MCZ.bin", NULL,
	"s2\\art\\kosinski\\OOZ.bin", NULL,
	"s2\\art\\kosinski\\MTZ.bin", NULL,
	"s2\\art\\kosinski\\WFZ_SCZ.bin", NULL,
	"s2\\art\\kosinski\\WFZ_SCZ.bin", "s2\\art\\kosinski\\WFZ_Supp.bin",
};
char *sonic2_kon_mapping[] = 
{
	"s2\\mappings\\16x16\\EHZ.bin",
	"s2\\mappings\\16x16\\CPZ_DEZ.bin",
	"s2\\mappings\\16x16\\ARZ.bin",
	"s2\\mappings\\16x16\\CNZ.bin",
	"s2\\mappings\\16x16\\HTZ.bin",
	"s2\\mappings\\16x16\\MCZ.bin",
	"s2\\mappings\\16x16\\OOZ.bin",
	"s2\\mappings\\16x16\\MTZ.bin",
	"s2\\mappings\\16x16\\WFZ_SCZ.bin",
};
char *sonic2_kon_mapping128[] = 
{
	"s2\\mappings\\128x128\\EHZ_HTZ.bin",
	"s2\\mappings\\128x128\\CPZ_DEZ.bin",
	"s2\\mappings\\128x128\\ARZ.bin",
	"s2\\mappings\\128x128\\CNZ.bin",
	"s2\\mappings\\128x128\\EHZ_HTZ.bin",
	"s2\\mappings\\128x128\\MCZ.bin",
	"s2\\mappings\\128x128\\OOZ.bin",
	"s2\\mappings\\128x128\\MTZ.bin",
	"s2\\mappings\\128x128\\WFZ_SCZ.bin",
};
char *sonic2_kon_colindex[] = 
{
	"s2\\collision\\EHZ and HTZ primary 16x16 collision index.bin",
	"s2\\collision\\EHZ and HTZ secondary 16x16 collision index.bin",
	"s2\\collision\\CPZ and DEZ primary 16x16 collision index.bin",
	"s2\\collision\\CPZ and DEZ secondary 16x16 collision index.bin",
	"s2\\collision\\ARZ primary 16x16 collision index.bin",
	"s2\\collision\\ARZ secondary 16x16 collision index.bin",
	"s2\\collision\\CNZ primary 16x16 collision index.bin",
	"s2\\collision\\CNZ secondary 16x16 collision index.bin",
	"s2\\collision\\EHZ and HTZ primary 16x16 collision index.bin",
	"s2\\collision\\EHZ and HTZ secondary 16x16 collision index.bin",
	"s2\\collision\\MCZ primary 16x16 collision index.bin",
	0,
	"s2\\collision\\OOZ primary 16x16 collision index.bin",
	0,
	"s2\\collision\\MTZ primary 16x16 collision index.bin",
	0,
	"s2\\collision\\WFZ and SCZ primary 16x16 collision index.bin",
	"s2\\collision\\WFZ and SCZ secondary 16x16 collision index.bin",
};
char *sonic2_kon_map[] =
{
	"s2\\level\\layout\\EHZ_1.bin",
	"s2\\level\\layout\\EHZ_2.bin",
	"s2\\level\\layout\\CPZ_1.bin",
	"s2\\level\\layout\\CPZ_2.bin",
	"s2\\level\\layout\\ARZ_1.bin",
	"s2\\level\\layout\\ARZ_2.bin",
	"s2\\level\\layout\\CNZ_1.bin",
	"s2\\level\\layout\\CNZ_2.bin",
	"s2\\level\\layout\\HTZ_1.bin",
	"s2\\level\\layout\\HTZ_2.bin",
	"s2\\level\\layout\\MCZ_1.bin",
	"s2\\level\\layout\\MCZ_2.bin",
	"s2\\level\\layout\\OOZ_1.bin",
	"s2\\level\\layout\\OOZ_2.bin",
	"s2\\level\\layout\\MTZ_1.bin",
	"s2\\level\\layout\\MTZ_2.bin",
	"s2\\level\\layout\\MTZ_3.bin",
	"s2\\level\\layout\\SCZ.bin",
	"s2\\level\\layout\\WFZ.bin",
	"s2\\level\\layout\\DEZ.bin"
};
char *sonic2_levels[] = 
{
	"S2EHZ",
	"S2CPZ",
	"S2ARZ",
	"S2CNZ",
	"S2HTZ",
	"S2MCZ",
	"S2OOZ",
	"S2MTZ",
	"S2WFZ",
};

void S2_GFXConverterAll()
{
	char tmp1[0x80];
	char tmp2[0x80];
	char outname[0x80];

	for(int i=0; i<9; i++)
	{
		sprintf_s(tmp1, "%s_dec", sonic2_kon_levelart[i*2]);
		sprintf_s(tmp2, "%s_dec", sonic2_kon_mapping[i]);
		KDecomp(sonic2_kon_levelart[i*2], tmp1, 0, false);
		KDecomp(sonic2_kon_mapping[i], tmp2, 0, false);

		sprintf_s(outname, "LEVEL\\%s\\%s@1.%s", sonic2_levels[i], sonic2_levels[i], "GFX");
		printf("%s\n", outname);
		Sonic_GFXConverter8BPP(outname, tmp1, tmp2, false);
	}
}
void S2_BLKConverterAll()
{
	char tmp1[0x80];
	char tmp2[0x80];
	char outname[0x80];

	for(int i=0; i<9; i++)
	{
		sprintf_s(tmp1, "%s_dec", sonic2_kon_mapping128[i]);
		sprintf_s(tmp2, "%s_dec", sonic2_kon_mapping[i]);
		KDecomp(sonic2_kon_mapping128[i], tmp1, 0, false);
		KDecomp(sonic2_kon_mapping[i], tmp2, 0, false);

		sprintf_s(outname, "LEVEL\\%s\\%s.%s", sonic2_levels[i], sonic2_levels[i], "BLK");
		printf("%s\n", outname);
		Sonic_BlockConverter(outname, tmp1, tmp2, true);
	}
}
void S2_ColIndexConvertAll()
{
	char tmp1[0x80];
	char tmp2[0x80];
	char outname[0x80];

	for(int i=0; i<9; i++)
	{
		char *t1 = tmp1;
		char *t2 = tmp2;

		if (sonic2_kon_colindex[i*2+0])
		{
			sprintf_s(tmp1, "%s_dec", sonic2_kon_colindex[i*2+0]);
			KDecomp(sonic2_kon_colindex[i*2+0], tmp1, 0, false);
		}
		else t1 = NULL;

		if (sonic2_kon_colindex[i*2+1])
		{
			sprintf_s(tmp2, "%s_dec", sonic2_kon_colindex[i*2+1]);
			KDecomp(sonic2_kon_colindex[i*2+1], tmp2, 0, false);
		}
		else t1 = NULL;

		sprintf_s(outname, "LEVEL\\%s\\%s.%s", sonic2_levels[i], sonic2_levels[i], "CLI");
		printf("%s\n", outname);
		Sonic_ColIndexConverter(outname, t1, t2);
	}
}
void S2_MapConvertAll()
{
	char tmp[0x80];
	char outname[0x80];

	for(int i=0; i<8*2; i++)
	{
		sprintf_s(outname, "LEVEL\\%s\\%s%i.MAP", sonic2_levels[i/2], sonic2_levels[i/2], (i&1)+1);
		sprintf_s(tmp, "%s_dec", sonic2_kon_map[i]);
		KDecomp(sonic2_kon_map[i], tmp, 0, false);
		printf("Converting %s...", outname);
		Sonic_MapConverterNEW(outname, tmp, (i&1)+1);
		printf("!\n");
	}
}

#endif