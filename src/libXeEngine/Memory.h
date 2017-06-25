#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class EXPORT Memory
	{
	private:
		MemoryHandle memory;
		u32 size;
	protected:
	public:
		Memory(u32 size = 0);
		~Memory();

		//! \brief Allocate a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Alloc(u32 size);

		//! \brief Allocate a portion of memory initializing it to zeroes
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void AllocZero(u32 size);

		//! \brief Reallocate a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Resize(u32 size);

		//! \brief Release a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Free();

		//! \brief Get the size of the allocated memory
		//! \return Memory size
		u32 Size() const;

		//! \brief Fill the entire portion of memory with specified byte
		void Fill(unsigned char c = 0x00);

		//! \brief Copy a portion of memory
		//! \param The memory that will be copied
		//! \param The size of the memory to copy
		//! \warning If the size of the memory is more than the reals specified, it will happen a crash.
		void Copy(MemoryHandle src, u32 size);

		//! \brief Get the memory handle currently used
		//! \details The MemoryHandle can be used as a pointer
		//! \warning You can manage the memory as you want but the possibilities of crashes can be higher
		MemoryHandle GetMemoryHandle() const;

		//! \brief Transfer a portion of memory into another
		Memory& operator = (const Memory&);
	};
}