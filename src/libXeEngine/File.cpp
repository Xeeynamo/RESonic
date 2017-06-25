#include "File.h"
#include "XeBase.h"

XeEngine::File::File()
{
	f = NULL;
	m_filesize = 0;
	m_readonly = true;
}
XeEngine::File::~File()
{
	Close();
}

bool XeEngine::File::Exist(const String& filename)
{
	return System::FileExist(filename);
}

bool XeEngine::File::Create(const String& filename)
{
	Close();
	f = System::FileCreate(filename);
	m_readonly = false;
	return true;
}
bool XeEngine::File::Open(const String& filename, bool readonly)
{
	Close();
	f = System::FileOpen(filename, readonly);
	if (f == NULL) return false;
	m_readonly = readonly;
	if (m_readonly == true)
	{
		m_filesize = System::FileLength(f);
	}
	return true;
}
void XeEngine::File::Close()
{
	System::FileClose(f);
}

u32 XeEngine::File::Size()
{
	if (!m_readonly)
	{
		return System::FileLength(f);
	}
	return m_filesize;
}
int XeEngine::File::Position()
{
	return System::FilePosition(f);
}
void XeEngine::File::Read(void *data, u32 size)
{
	System::FileRead(f, data, size);
}
void XeEngine::File::Write(void *data, u32 size)
{
	System::FileWrite(f, data, size);
}

void XeEngine::File::Seek(int offset, FileSeekMode origin)
{
	System::FileSeek(f, offset, origin);
}

void XeEngine::File::Lock(Memory& m)
{
	int size = Size();
	if (size == 0) return;
	m.Alloc(size);
	Seek();
	Read(m.GetMemoryHandle(), size);
}
void XeEngine::File::Unlock(Memory& m)
{
	Seek();
	if (m_readonly == true) return;
	Write(m.GetMemoryHandle(), m.Size());
}
