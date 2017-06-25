#pragma once
#include "XeEngineLV1.h"
#include "XeTexture.h"

struct DTLHeader
{
	byte animationCount;
	byte resolution;
	short bytepertile;
};
struct DTLAnimation
{
	byte count;
	byte speed;
	byte index;
	byte framesCount;
	byte framesIndex;
	byte pattern;
	byte dstIndex;
	byte dstTexture;
};

class DTL
{
private:
protected:
	XeEngine::Memory data;
	DTLHeader *header;
	DTLAnimation *anim;

	char **pattern;
	char **pictures;
public:
	DTL();
	~DTL();

	bool Load(char *filename);
	void Close();
	void Tick(XeTexture*);
};