#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class Memory
	{
	private:
		MemoryHandle memory;
		int size;
	protected:
	public:
		Memory(size_t size = 0);
		~Memory();

		//! \brief Allocate a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Alloc(int size);

		//! \brief Allocate a portion of memory initializing it to zeroes
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void AllocZero(int size);

		//! \brief Reallocate a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Resize(int size);

		//! \brief Release a portion of memory
		//! \details See XeEngine::XeSystem::MemoryAlloc for more informations
		void Free();

		//! \brief Get the size of the allocated memory
		//! \return Memory size
		int Size() const;

		//! \brief Fill the entire portion of memory with specified byte
		void Fill(unsigned char c = 0x00);

		//! \brief Copy a portion of memory
		//! \param The memory that will be copied
		//! \param The size of the memory to copy
		//! \warning If the size of the memory is more than the reals specified, it will happen a crash.
		void Copy(MemoryHandle src, size_t size);

		//! \brief Get the memory handle currently used
		//! \details The MemoryHandle can be used as a pointer
		//! \warning You can manage the memory as you want but the possibilities of crashes can be higher
		MemoryHandle GetMemoryHandle() const;

		//! \brief Transfer a portion of memory into another
		Memory& operator = (const Memory&);
	};
}