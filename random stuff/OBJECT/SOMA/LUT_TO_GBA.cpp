#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    FILE* f = fopen(argv[1], "r+b");
    FILE* o = fopen("out.bin", "w+b");

    unsigned int color;
    fseek(f, 4, SEEK_SET);
    while(fread(&color, sizeof(color), 1, f))
    {
        unsigned short out = ((((color >> 0) & 0xFF) >> 3) << 0) |
            ((((color >> 8) & 0xFF) >> 3) << 5) |
            ((((color >> 16) & 0xFF) >> 3) << 10);
        fwrite(&out, sizeof(out), 1, o);
    }
}
