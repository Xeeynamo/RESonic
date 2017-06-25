#include "XeSystem.h"

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#include <sys\stat.h>
#else
#include <stdio.h>
#include <sys\stat.h>
#include <time.h>
#endif

inline void XeEngine::MemoryCopy(MemoryHandle dst, MemoryHandle src, size_t size)
{
	if (src == 0 || dst == 0 || size == 0) return;
	memcpy(dst, src, size);
}
inline void XeEngine::MemoryFill(MemoryHandle dst, size_t size, unsigned char value)
{
	memset(dst, value, size);
}
inline size_t XeEngine::StringLength(char* str)
{
	return strlen(str);
}

unsigned int XeEngine::System::GetTimer()
{
#ifdef WIN32
	return GetTickCount64() & 0xFFFFFFFF;
#else
	return 0;
#endif
}

//////////////////////////////////////////////////////////////////////////
// Memory management
bool XeEngine::System::MemoryAlloc(MemoryHandle& h, size_t size)
{
	h = NULL;
#ifdef WINDOWS
	h = HeapAlloc(GetProcessHeap(), 0, size);
#else
	h = malloc(size);
#endif
	return h != NULL;
}
bool XeEngine::System::MemoryAllocZero(MemoryHandle& h, size_t size)
{
	h = NULL;
#ifdef WINDOWS
	h = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
#else
	h = calloc(1, size);
#endif
	return h != NULL;
}
bool XeEngine::System::MemoryResize(MemoryHandle& h, size_t size)
{
#ifdef WINDOWS
	if (h == NULL)
		MemoryAlloc(h, size);
	else
	{
		MemoryHandle newhandle;
		newhandle = HeapReAlloc(GetProcessHeap(), 0, h, size);
		if (newhandle == NULL) return false;
		h = newhandle;
	}
#else
	h = realloc(h, size);
#endif
	return h != NULL;
}
void XeEngine::System::MemoryFree(MemoryHandle& h)
{
	if (h == NULL) return;
#ifdef WINDOWS
	HeapFree(GetProcessHeap(), 0, h);
#else
	free(mem);
#endif
	h = NULL;
}

//////////////////////////////////////////////////////////////////////////
// File management
XeEngine::FileHandle XeEngine::System::FileOpen(String& filename, bool readonly)
{
#ifdef WIN32
	FILE *f;
	if (fopen_s(&f, filename.ToChar(), readonly == true ? "rb" : "r+b") < 0)
		return NULL;
	return (XeEngine::FileHandle)f;
#else
	return fopen(filename.ToChar(), readonly == true ? "rb" : "w+b");
#endif
}
XeEngine::FileHandle XeEngine::System::FileAppend(String& filename)
{
#ifdef WIN32
	FILE *f;
	if (fopen_s(&f, filename.ToChar(), "a+") == NULL)
		return NULL;
	return (XeEngine::FileHandle)f;
#else
	return fopen(filename.ToChar(), "a+");
#endif
}
XeEngine::FileHandle XeEngine::System::FileCreate(String& filename)
{
#ifdef WIN32
	FILE *f;
	fopen_s(&f, filename.ToChar(), "w+b");
	return (XeEngine::FileHandle)f;
#else
	return fopen(filename.ToChar(), "w+b");
#endif
}
void XeEngine::System::FileClose(FileHandle& h)
{
	if (h == NULL) return;
	fclose((FILE*)h);
	h = NULL;
}
bool XeEngine::System::FileRead(FileHandle h, void* p, size_t size)
{
	if (h == NULL) return false;
	fread(p, 1, size, (FILE*)h);
	return true;
}
bool XeEngine::System::FileWrite(FileHandle h, void* p, size_t size)
{
	if (h == NULL) return false;
	fwrite(p, 1, size, (FILE*)h);
	return true;
}
bool XeEngine::System::FileSeek(FileHandle h, int position, FileSeekMode seek)
{
	if (h == NULL) return false;
	fseek((FILE*)h, position, seek);
	return true;
}
int XeEngine::System::FilePosition(FileHandle h)
{
	if (h == NULL) return -1;
	return ftell((FILE*)h);
}
int XeEngine::System::FileLength(FileHandle h)
{
	int oldpos = FilePosition(h);
	if (oldpos < 0) return oldpos;
	FileSeek(h, 0, FILESEEK_END);
	int size = FilePosition(h);
	FileSeek(h, oldpos, FILESEEK_SET);
	return size;
}
int XeEngine::System::FileLength(String& filename)
{
	struct _stat ret;
	if (_stat(filename.ToChar(), &ret) < 0) return 0;
	return ret.st_size;
}
bool XeEngine::System::FileExist(String& filename)
{
	struct _stat ret;
	return _stat(filename.ToChar(), &ret) >= 0;
}