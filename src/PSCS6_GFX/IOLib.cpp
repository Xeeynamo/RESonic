#include "IOLib.h"

IOLib::IOLib()
{
	_file = 0;
	cb_seek = 0;
	cb_read = 0;
	cb_write = 0;
}

void IOLib::SetFile(void *file)
{
	_file = file;
}
void IOLib::SetSeek(XCALLBACK(callback_seek)(void *file, int mode, int offset))
{
	cb_seek = callback_seek;
}
void IOLib::SetRead(XCALLBACK(callback_read)(void *file, int size, void *buffer))
{
	cb_read = callback_read;
}
void IOLib::SetWrite(XCALLBACK(callback_write)(void *file, int size, void *buffer))
{
	cb_write = callback_write;
}

void IOLib::Seek(int mode, int offset)
{
	cb_seek(_file, mode, offset);
}
void IOLib::Read(int size, void *buffer)
{
	cb_read(_file, size, buffer);
}
void IOLib::Write(int size, void *buffer)
{
	cb_write(_file, size, buffer);
}

unsigned int IOLib::CreateMagicCode(char *ext, int version)
{
	return (ext[0]^0xFF) | ((ext[1] ^ ext[0])<<8) | ((ext[2] ^ ext[1])<<16) | (((version | (version<<4)) ^ ext[2])<<24);
}
void IOLib::WriteMagicCode(char *extension, int version)
{
	unsigned int magiccode = CreateMagicCode(extension, version);
	Write(sizeof(magiccode), &magiccode);
}
char IOLib::CheckMagiccode(char *extension, int maxversion)
{
	unsigned int magiccode;
	Read(sizeof(magiccode), &magiccode);
	for(int i=1; i<maxversion; i++)
	{
		if (CreateMagicCode(extension, i) == magiccode)
			return i;
	}
	return 0;
}