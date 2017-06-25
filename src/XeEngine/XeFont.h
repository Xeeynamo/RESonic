#pragma once
#include "XeTexture.h"

class XeFont
{
private:
	XeTexture *texture_;
	short _x, _y;
public:
	XeFont();
	~XeFont();

	void SetTexture(XeTexture*);
	void SetXY(short x, short y);
	void PrintText(char*);
};