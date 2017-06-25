#include "String.h"
#include "System.h"

XeEngine::String::String()
{
	capacity = 0;
}
XeEngine::String::String(char* str)
{
	capacity = 0;
	Capacity(XeEngine::StringLength(str));
	MemoryCopy(string.GetMemoryHandle(), str, string.Size());
}
XeEngine::String::String(const char* str)
{
	capacity = 0;
	Capacity(XeEngine::StringLength((char*)str));
	MemoryCopy(string.GetMemoryHandle(), (char*)str, string.Size());
}
XeEngine::String& XeEngine::String::operator = (const String& str)
{
	string = str.string;
	return *this;
}
XeEngine::String& XeEngine::String::operator += (const String& str)
{
	u32 prev = Length();
	u32 sum = str.Length();
	Capacity(prev + sum);
	MemoryCopy((char*)string.GetMemoryHandle() + (ptrdiff_t)prev, str.ToChar(), sum + 1);
	return *this;
}
bool XeEngine::String::operator == (const String& str)
{
	if (str.Length() != Length()) return false;
	return XeEngine::MemoryCompare(ToChar(), str.ToChar(), Length()) == 0;
}
bool XeEngine::String::operator != (const String& str)
{
	return !(*this == str);
}

void XeEngine::String::Copy(const String& str)
{
	string = str.string;
}

u32 XeEngine::String::Length() const
{
	if (string.Size() == 0) return 0;
	return StringLength((char*)string.GetMemoryHandle());
}
char* XeEngine::String::ToChar() const
{
	return (char*)string.GetMemoryHandle();
}
void XeEngine::String::Capacity(u32 newsize)
{
	u32 cap = (newsize&~0x1F) + 0x20;
	if (cap > capacity)
	{
		capacity = cap;
		string.Resize(capacity);
	}
}

bool XeEngine::String::GetPath(XeEngine::String& strOut) const
{
	String tmp = String(ToChar());
	char* search = tmp.ToChar();
	char* end = search + (ptrdiff_t)(tmp.Length() - 1);
	char* foundpos = nullptr;
	while(search < end)
	{
		if (*search == '\\' || *search == '/')
		{
			foundpos = search + 1;
		}
		search++;
	}
	if (foundpos == nullptr) return false;
	*foundpos = '\0';
	strOut = String(tmp.ToChar());
	return true;
}
bool XeEngine::String::GetFilename(XeEngine::String& strOut) const
{
	String tmp;
	if (GetFilenameWithExtension(tmp) == false)
		return false;
	char* search = tmp.ToChar();
	char* end = search + tmp.Length() - 1;
	while(search < end)
	{
		if (*search == '.')
		{
			*search = '\0';
			break;
		}
		search++;
	}
	strOut = String(tmp.ToChar());
	return true;
}
bool XeEngine::String::GetFilenameWithExtension(XeEngine::String& strOut) const
{
	if (Length() > 2)
	{
		char* str = (char*)string.GetMemoryHandle();
		char *search = str + (ptrdiff_t)(Length() - 2);
		while(search > str)
		{
			if (*search == '/' || *search == '\\')
			{
				strOut = String(search + 1);
				return true;
			}
			search--;
		}
	}
	return false;
}
bool XeEngine::String::GetExtension(String& strOut) const
{
	if (Length() > 2)
	{
		char* str = (char*)string.GetMemoryHandle();
		char *search = str + (ptrdiff_t)(Length() - 2);
		while(search > str)
		{
			if (*search == '.')
			{
				strOut = String(search + 1);
				return true;
			}
			search--;
		}
	}
	return false;
}

XeEngine::Hash XeEngine::String::GetHash() const
{
	Hash r = 0;
	char* string = (char*)ToChar();
	for(int i=0; *string; i++, string++)
	{
		r ^= *string << 24;
		r ^= *string << 16;
		r ^= *string << 8;
		r ^= *string;

		r = 2 * r ^ 0x04C11DB5;
		r = 3 * r ^ 0x1278CE39;
	}
	return r;
}
