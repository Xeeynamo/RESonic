#include "XeString.h"
#include "XeSystem.h"

XeEngine::String::String()
{
	capacity = 0;
}
XeEngine::String::String(char* str)
{
	Capacity(XeEngine::StringLength(str)); //string.Alloc(strlen(str));
	MemoryCopy(string.GetMemoryHandle(), str, string.Size());
}
XeEngine::String& XeEngine::String::operator = (const String& str)
{
	string = str.string;
	return *this;
}
XeEngine::String& XeEngine::String::operator += (const String& str)
{
	int prev = string.Size();
	int sum = str.Length();
	Capacity(prev + sum); //string.Resize(prev + sum);
	MemoryCopy((char*)string.GetMemoryHandle() + prev, str.ToChar(), sum);
	return *this;
}
size_t XeEngine::String::Length() const
{
	return string.Size();
}
char* XeEngine::String::ToChar() const
{
	return (char*)string.GetMemoryHandle();
}
void XeEngine::String::Capacity(int newsize)
{
	size_t cap = (newsize&~0x1F) + 0x20;
	if (cap > Length())
	{
		capacity = cap;
		string.Resize(capacity);
	}
}