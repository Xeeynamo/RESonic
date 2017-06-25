#include "SonicMD.h"
#include "GFX.h"

bool Loader::SonicMD::ToGFX_4bpp(char* gfxFileDst, char* gfxFile8x8, char* gfxFileMapping)
{
	XeEngine::File f8, fMap, fOut;
	if (f8.Open(XeEngine::String(gfxFile8x8)) == false) return false;
	if (fMap.Open(XeEngine::String(gfxFileMapping)) == false) return false;
	if (fOut.Create(XeEngine::String(gfxFileDst)) == false) return false;
	u32 tile16Count = fMap.Size() / 8;

	u8 textureCount = (tile16Count>>8) + ((tile16Count&0xFF) ? 1 : 0);
	fOut.Seek(1024*0x80 + sizeof(GFXStruct)-1); //fseek(fOut, textureCount*256*256/2-1+sizeof(GFXStruct), SEEK_SET);
	fOut.Write(&textureCount, 1);

	GFXStruct gfxstruct;
	gfxstruct.width = gfxstruct.height = 0;
	gfxstruct.dstindex = 0;
	gfxstruct.flags = 0;
	gfxstruct.headersize = sizeof(GFXStruct);
	gfxstruct.mode = 2;
	gfxstruct.resolution = 1;
	gfxstruct.texturecount = 4;
	fOut.Seek();
	fOut.Write(&gfxstruct, sizeof(gfxstruct));

	for(u32 t = 0; t < tile16Count; t++)
	{
		unsigned char tile16[0x80];
		for(int b=0; b<4; b++)
		{
			unsigned short id;
			fMap.Read(&id, sizeof(id));
			id = ((id&0xFF)<<8) | ((id>>8)&0xFF);

			unsigned char tile8[0x20];
			f8.Seek((id&0x3FF) * sizeof(tile8));
			f8.Read(tile8, sizeof(tile8));

			for(int i=0; i<8; i++)
			{
				for(int j=0; j<4; j++)
				{
					tile8[j + i*4] = ((tile8[j + i*4]>>4)&0xF) | ((tile8[j + i*4]<<4)&0xF0);
				}
			}
			if (id & 0x0800) // Flip X
			{
				for(int i=0; i<8; i++)
				{
					for(int j=0; j<2; j++)
					{
						char tmp = tile8[j + i*4];
						tile8[j + i*4] = tile8[-j + 3 + i*4];
						tile8[-j + 3 + i*4] = tmp;
					}
					for(int j=0; j<4; j++)
					{
						tile8[j + i*4] = ((tile8[j + i*4]>>4)&0xF) | ((tile8[j + i*4]<<4)&0xF0);
					}
				}
			}
			if (id & 0x1000) // Flip Y
			{
				for(int i=0; i<4; i++)
				{
					for(int j=0; j<4; j++)
					{
						char tmp = tile8[j + i*4];
						tile8[j + i*4] = tile8[j + (-i*4 + 0x1C)];
						tile8[j + (-i*4 + 0x1C)] = tmp;
					}
				}
			}

			for(int i=0; i<8; i++)
			{
				for(int j=0; j<4; j++)
				{
					tile16[j + (b&1)*4 + i*8 + (b&2)*0x20] = tile8[j + i*4];
				}
			}
		}
		for(int i=0; i<16; i++)
		{
			int pos = i*256/2 + (t&15)*8 + (t>>4)*256*16/2;
			fOut.Seek(pos + (int)sizeof(GFXStruct));
			fOut.Write(&tile16[i * 8], 8);
		}
	}
	fOut.Close();
	fMap.Close();
	f8.Close();
	return true;
}
bool Loader::SonicMD::ToGFX_8bpp(char *dstFile, char *srcFile8x8, char *srcFileMapping, bool isSonic1)
{
	
	return false;
}
