#include "System.h"

#define _CRT_SECURE_NO_WARNINGS
#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#include <sys\stat.h>
#else
#include <stdio.h>
#include <sys\stat.h>
#include <time.h>
#endif


inline void XeEngine::MemoryCopy(MemoryHandle dst, MemoryHandle src, u32 size)
{
	if (src == 0 || dst == 0 || size == 0) return;
	memcpy(dst, src, (u32)size);
}
inline void XeEngine::MemoryFill(MemoryHandle dst, u32 size, unsigned char value)
{
	memset(dst, value, (u32)size);
}
inline int XeEngine::MemoryCompare(MemoryHandle dst, MemoryHandle src, u32 size)
{
	return memcmp(dst, src, (u32)size);
}
inline u32 XeEngine::StringLength(const char* str)
{
	return (u32)strlen(str);
}
inline void XeEngine::StringCopy(char* str1, const char* str2)
{
	strcpy(str1, str2);
}

unsigned int XeEngine::System::GetTimer()
{
#ifdef PLATFORM_WINDOWS
#ifdef MVCPP
	return GetTickCount64() & 0xFFFFFFFF;
#else
	return GetTickCount() & 0xFFFFFFFF;
#endif
#elif PLATFORM_LINUX
	timeval curr;
	gettimeofday(&curr, NULL);
	return curr;
#elif PLATFORM_APPLE
	timeval curr;
	gettimeofday(&curr, NULL);
	return curr;
#else
	return 0;
#endif
}
void XeEngine::System::MessageBox(MessageBoxType type, char* str)
{
#ifdef PLATFORM_WINDOWS
	DWORD msgType;
	char* caption;
	switch(type)
	{
	case MessageBoxType_Error:
		msgType = MB_OK | MB_ICONERROR;
		caption = "Error";
		break;
	case MessageBoxType_Warning:
		msgType = MB_OK | MB_ICONWARNING;
		caption = "Warning";
		break;
	case MessageBoxType_Info:
		msgType = MB_OK | MB_ICONINFORMATION;
		caption = "Information";
		break;
	}
	::MessageBox(nullptr, str, caption, msgType);
#elif PLATFORM_LINUX
	GtkMessageType msgType;
	switch(type)
	{
	case MessageBoxType_Error:
		msgType = GTK_MESSAGE_ERROR;
		break;
	case MessageBoxType_Warning:
		msgType = GTK_MESSAGE_WARNING;
		break;
	case MessageBoxType_Info:
		msgType = GTK_MESSAGE_INFO;
		break;
	}
	GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, msgType, GTK_BUTTONS_OK, string);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	g_idle_add(idle, NULL);
	gtk_main();
#elif PLATFORM_APPLE
	SInt16 ret;
	Str255 msg;
	c2pstrcpy(msg, string);
	switch(type)
	{
	case MessageBoxType_Error:
		StandardAlert(kAlertStopAlert, msg, NULL, NULL, &ret);
		break;
	case MessageBoxType_Warning:
		StandardAlert(kAlertCautionAlert, msg, NULL, NULL, &ret);
		break;
	case MessageBoxType_Info:
		StandardAlert(kAlertNoteAlert, msg, NULL, NULL, &ret);
		break;
	}
#endif
}

XeEngine::Language XeEngine::GetLanguage()
{
	LCID localeID = GetUserDefaultLCID();
	switch(localeID & 0xFF)
	{
	case LANG_ITALIAN:
		return LANGUAGE_ITALIAN;
	case LANG_FRENCH:
		return LANGUAGE_FRENCH;
	case LANG_GERMAN:
		return LANGUAGE_GERMAN;
	case LANG_SPANISH:
		return LANGUAGE_SPANISH;
	case LANG_JAPANESE:
		return LANGUAGE_JAPANESE;
	case LANG_ENGLISH:
	default:
		return LANGUAGE_ENGLISH;
	}
}

void XeEngine::Delay(u32 millisecond)
{
#ifdef WIN32
	Sleep(millisecond);
#endif
}

//////////////////////////////////////////////////////////////////////////
// Memory management
bool XeEngine::System::MemoryAlloc(MemoryHandle& h, u32 size)
{
	h = NULL;
#ifdef WINDOWS
	h = HeapAlloc(GetProcessHeap(), 0, size);
#else
	h = malloc((size_t)size);
#endif
	return h != NULL;
}
bool XeEngine::System::MemoryAllocZero(MemoryHandle& h, u32 size)
{
	h = NULL;
#ifdef WINDOWS
	h = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
#else
	h = calloc(1, (size_t)size);
#endif
	return h != NULL;
}
bool XeEngine::System::MemoryResize(MemoryHandle& h, u32 size)
{
	if (h == NULL)
		MemoryAlloc(h, size);
	else
	{
		MemoryHandle newhandle;
#ifdef WINDOWS
		newhandle = HeapReAlloc(GetProcessHeap(), 0, h, size);
#else
		newhandle = realloc(h, (size_t)size);
#endif
		if (newhandle == NULL) return false;
		h = newhandle;
	}
	return h != NULL;
}
void XeEngine::System::MemoryFree(MemoryHandle& h)
{
	if (h == NULL) return;
#ifdef WINDOWS
	HeapFree(GetProcessHeap(), 0, h);
#else
	free(h);
#endif
	h = NULL;
}

//////////////////////////////////////////////////////////////////////////
// File management
XeEngine::FileHandle XeEngine::System::FileOpen(const String& filename, bool readonly)
{
#ifdef MVCPP
	FILE *f;
	if (fopen_s(&f, filename.ToChar(), readonly == true ? "rb" : "r+b") < 0)
		return NULL;
	return (XeEngine::FileHandle)f;
#else
	return fopen(filename.ToChar(), readonly == true ? "rb" : "w+b");
#endif
}
XeEngine::FileHandle XeEngine::System::FileAppend(const String& filename)
{
#ifdef MVCPP
	FILE *f;
	if (fopen_s(&f, filename.ToChar(), "a+") == NULL)
		return NULL;
	return (XeEngine::FileHandle)f;
#else
	return fopen(filename.ToChar(), "a+");
#endif
}
XeEngine::FileHandle XeEngine::System::FileCreate(const String& filename)
{
#ifdef MVCPP
	FILE *f = NULL;
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
bool XeEngine::System::FileRead(FileHandle h, void* p, u32 size)
{
	if (h == NULL) return false;
	fread(p, 1, (size_t)size, (FILE*)h);
	return true;
}
bool XeEngine::System::FileWrite(FileHandle h, void* p, u32 size)
{
	if (h == NULL) return false;
	fwrite(p, 1, (size_t)size, (FILE*)h);
	return true;
}
bool XeEngine::System::FileSeek(FileHandle h, int position, FileSeekMode seek)
{
	if (h == NULL) return false;
#ifdef x64
	_fseeki64((FILE*)h, (long long)position, seek);
#else
	fseek((FILE*)h, position, seek);
#endif
	return true;
}
int XeEngine::System::FilePosition(FileHandle h)
{
	if (h == NULL) return -1;
#ifdef x64
	return (int)_ftelli64((FILE*)h);
#else
	return ftell((FILE*)h);
#endif
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
int XeEngine::System::FileLength(const String& filename)
{
	struct _stat ret;
	if (_stat(filename.ToChar(), &ret) < 0) return 0;
	return ret.st_size;
}
bool XeEngine::System::FileExist(const String& filename)
{
	struct _stat ret;
	return _stat(filename.ToChar(), &ret) >= 0;
}
u32 XeEngine::System::StringLength(char* str)
{
	return (u32)strlen(str);
}
