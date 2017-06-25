#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

int main()
{
    struct GFXStruct
    {
        byte headersize;
        byte dstindex;
        byte width;
        byte height;
        byte resolution;
        byte texturecount;
        byte format;
        byte flags;
    };

    GFXStruct gfx;
    gfx.headersize = sizeof(GFXStruct);
    gfx.dstindex = 0;
    gfx.width = 128 / 4;
    gfx.height = 128 / 4;
    gfx.resolution = 1;
    gfx.texturecount = 52;
    gfx.format = 2;

    FILE* f = fopen("f_soma.gfx", "wb");
    fwrite(&gfx, sizeof(GFXStruct), 1, f);
    fclose(f);

    system("@echo off");
    for(int i = 0; i < 0x80; i++)
    {
        char cmd[0x100];
        sprintf(cmd, "copy /b f_soma.tmp + f_soma%02x.dat f_soma.gfx", i);
        system("copy /b f_soma.gfx f_soma.tmp");
        system(cmd);
        system("del f_soma.tmp");
    }
}
