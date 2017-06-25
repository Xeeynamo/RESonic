#pragma once

#define XCALLBACK(i) void(*i)
#define PCALLBACK(i) void*(*i)

class IOLib
{
private:
	void *_file;

	XCALLBACK(cb_seek)(void *file, int mode, int offset);
	XCALLBACK(cb_read)(void *file, int size, void *buffer);
	XCALLBACK(cb_write)(void *file, int size, void *buffer);
public:
	IOLib();

	void SetFile(void *file);
	void SetSeek(XCALLBACK(callback_seek)(void *file, int mode, int offset));
	void SetRead(XCALLBACK(callback_read)(void *file, int size, void *buffer));
	void SetWrite(XCALLBACK(callback_write)(void *file, int size, void *buffer));

	void Seek(int mode, int offset);
	void Read(int size, void *buffer);
	void Write(int size, void *buffer);

	unsigned int CreateMagicCode(char *extension, int version);
	void WriteMagicCode(char *extension, int version);
	char CheckMagiccode(char *extension, int maxversion);
};