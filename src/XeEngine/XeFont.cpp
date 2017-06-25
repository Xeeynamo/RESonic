#include "XeFont.h"
#include <windows.h>
#include <GL/GL.h>
#pragma comment(lib, "Opengl32.lib")

XeFont::XeFont()
{
	_x = _y = 0;
	texture_ = NULL;
}
XeFont::~XeFont()
{

}

void XeFont::SetTexture(XeTexture *texture)
{
	if (!texture) return;
	texture_ = texture;
}
void XeFont::SetXY(short x, short y)
{
	_x = x;
	_y = y;
}
void XeFont::PrintText(char *str)
{
	if (!texture_) return;

	short x = 0;
	short y = 0;

	for(int i=0; str[i]; i++)
	{
		switch (str[i])
		{
		case '\t':
			x += 4;
			break;
		case '\n':
			y++;
		case '\r':
			x = 0;
			break;
		case ' ':
			x++;
			break;
		default:
			glLoadIdentity();
			glTranslatef((float)((x<<3)+_x), (float)((y<<3)+_y), 8.0f);
			texture_->Draw((str[i]&0xF)<<3, (str[i]>>4)<<3, 8, 8, 0, NULL);
			x++;
		}
	}
}