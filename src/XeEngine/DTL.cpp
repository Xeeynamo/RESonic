#include "DTL.h"

DTL::DTL()
{
	header = NULL;
	anim = NULL;
	pattern = NULL;
	pictures = NULL;
}
DTL::~DTL()
{
	Close();
}

bool DTL::Load(char *filename)
{
	Close();

	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename), true))
		return false;
	data.Alloc(f.Size());
	f.Read(data.GetMemoryHandle(), data.Size());
	f.Close();
	header = (DTLHeader*)data.GetMemoryHandle();
	anim = (DTLAnimation*)(header+1);


	pattern = new char*[header->animationCount];
	pictures = new char*[header->animationCount];

	pattern[0] = (char*)(anim + header->animationCount);
	for(int i=1; i<header->animationCount; i++)
	{
		pattern[i] = pattern[i-1];
		while(*++pattern[i] != -1);
	}

	pictures[0] = pattern[header->animationCount-1];
	while(*(pictures[0]++) != -1);
	for(int i=1; i<header->animationCount; i++)
	{
		pictures[i] = pictures[i-1] + header->bytepertile * anim[i].count * anim[i].framesCount;
	}

	return true;
}
void DTL::Close()
{
	if (pattern) delete[] pattern;
	if (pictures) delete[] pictures;
	data.Free();
	header = NULL;
}

void DTL::Tick(XeTexture *texture)
{
	if (header == NULL) return;
	for(int i=0; i<header->animationCount; i++)
	{
		if (++anim[i].index >= anim[i].speed)
		{
			anim[i].index = 0;
			if (anim[i].framesIndex++ >= anim[i].framesCount)
			{
				anim[i].framesIndex = 0;
			}
			byte index = anim[i].dstIndex;
			texture->Upload((index&0xF)*16*header->resolution, (index&0xF0)*header->resolution, 16*anim[i].count*header->resolution, 16*header->resolution,
				anim[i].dstTexture, anim[i].dstTexture, pictures[i] + anim[i].count * anim[i].framesIndex * header->bytepertile * header->resolution);
			// 
			/*texture->Upload(0, 0, 512, 8,
				0, 1, (char*)(header) + 0xD);*/
		}
	}
}
