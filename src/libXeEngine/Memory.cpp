#include "Memory.h"
#include "System.h"

XeEngine::Memory::Memory(u32 size)
{
	memory = 0;
	this->size = size;
	if (size != 0) Alloc(size);
}
XeEngine::Memory::~Memory()
{
	Free();
}

void XeEngine::Memory::Alloc(u32 size)
{
	Free();
	this->size = System::MemoryAlloc(memory, size) ? size : 0;
}
void XeEngine::Memory::AllocZero(u32 size)
{
	Free();
	this->size = System::MemoryAllocZero(memory, size) ? size : 0;
}
void XeEngine::Memory::Free()
{
	System::MemoryFree(memory);
	this->size = 0;
}
void XeEngine::Memory::Resize(u32 size)
{
	this->size = System::MemoryResize(memory, size) ? size : this->size;
}
void XeEngine::Memory::Fill(unsigned char c)
{
	MemoryFill(GetMemoryHandle(), Size(), c);
}
u32 XeEngine::Memory::Size() const
{
	return size;
}
void XeEngine::Memory::Copy(XeEngine::MemoryHandle src, u32 size)
{
	Free();
	Alloc(size);
	MemoryCopy(GetMemoryHandle(), src, size);
}
XeEngine::MemoryHandle XeEngine::Memory::GetMemoryHandle() const
{
	return memory;
}

XeEngine::Memory& XeEngine::Memory::operator = (const Memory& src)
{
	Copy(src.GetMemoryHandle(), src.Size());
	return *this;
}