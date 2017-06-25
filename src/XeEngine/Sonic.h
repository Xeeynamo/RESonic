
// Sonic.cpp
bool Sonic_GFXConverter(char *dstFile, char *srcFile8x8, char *srcFileMapping);
bool Sonic_GFXConverter8BPP(char *dstFile, char *srcFile8x8, char *srcFileMapping, bool isSonic1);
bool Sonic_BlockConverter(char *dstFile, char *srcFile128, char *srcFile16, bool bpp8);
void Sonic_ColIndexConverter(char *dstFile, char *path1, char *path2);
void Sonic_MapConverter(char *dstFile, char *srcFile, int act);
void Sonic_MapConverterNEW(char *dstFile, char *srcFile, int act);
void Sonic_Chunk256Converter(char *dstChunk, char *dstLayout, char *srcBlock, char *srcChunk, char *srcLayoutFG, char *srcLayoutBG, int act, bool bpp8);
void Sonic_Chunk256ConverterNEW(char *dstChunk, char *dstLayout, char *srcBlock, char *srcChunk, char *srcLayoutFG, char *srcLayoutBG, int act, bool bpp8);
// Sonic1.cpp
void S1_GFXConverterAll();
void S1_LevelConvertAll();
// Sonic1LVL.cpp

void S1LVL_GFXConverterAll();
void S1LVL_BLKConverterAll();
void S1LVL_ColIndexConvertAll();
void S1LVL_MapConvertAll();
// Sonic2.cpp
void S2_GFXConverterAll();
void S2_BLKConverterAll();
void S2_ColIndexConvertAll();
void S2_MapConvertAll();
// SonicDec.cpp
bool KDecomp(char *SrcFile, char *DstFile, long Location, bool Moduled);
bool NDecomp(char *SrcFile, char *DstFile, long Pointer);
long EDecomp(char *SrcFile, char *DstFile, long Pointer, bool padding);