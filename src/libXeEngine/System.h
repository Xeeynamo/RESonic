#pragma once
#include "XeBase.h"
#include "String.h"

namespace XeEngine
{
	enum FileSeekMode
	{
		//! \brief Move from the beginning of the file. Only positive position.
		FILESEEK_SET = 0,
		//! \brief Move from the current position of the file. Positive and negative position can be specified.
		FILESEEK_CUR = 1,
		//! \brief Move from the end of the file. Positive and negative position can be specified.
		FILESEEK_END = 2,
	};
	enum Language
	{
		LANGUAGE_ENGLISH	= 0,
		LANGUAGE_ITALIAN	= 1,
		LANGUAGE_FRENCH		= 2,
		LANGUAGE_GERMAN		= 3,
		LANGUAGE_SPANISH	= 4,
		LANGUAGE_JAPANESE	= 5,
	};
	enum MessageBoxType
	{
		MessageBoxType_Error,
		MessageBoxType_Warning,
		MessageBoxType_Info,
	};

	extern void MemoryCopy(MemoryHandle dst, MemoryHandle src, u32 size);
	extern void MemoryFill(MemoryHandle dst, u32 size, unsigned char value = 0);
	extern int MemoryCompare(MemoryHandle dst, MemoryHandle src, u32 size);
	extern u32 StringLength(const char*);
	extern void StringCopy(char*, const char*);

	Language GetLanguage();
	void Delay(u32 millisecond);

	//! \brief A class that manage system functions in secure and simple way
	class EXPORT System
	{
	public:
		//! \brief Get the timer in a single integer value with a millisecond's precision.
		//! \details The return value is system-dependent and usually it uses localized time.
		//! \return System's timer.
		static unsigned int GetTimer();

		//! \brief Launch a messagebox
		static void MessageBox(MessageBoxType, char*);

		//! \brief Allocate a portion of memory
		//! \details The memory will not be initialized
		//! \param The Memory Handle that will handles the memory
		//! \param The size of the memory to allocate
		//! \return Returns true if the memory is successfully allocated
		//! \warning Be sure to not specify a big amount of memory or to not pass a MemoryHandle that handle another portion of memory
		static bool MemoryAlloc(MemoryHandle&, u32);

		//! \brief Allocate a portion of memory
		//! \details The memory will be initialized to zeroes
		//! \param The Memory Handle that will handles the memory
		//! \param The size of the memory to allocate
		//! \return Returns true if the memory is successfully allocated
		//! \warning Be sure to not specify a big amount of memory or to not pass a MemoryHandle that handle another portion of memory
		static bool MemoryAllocZero(MemoryHandle&, u32);

		//! \brief Resize a portion of memory
		//! \details If the memory handle was not previously allocated, it will be allocated with this method
		//! \param The Memory Handle that currently handles the memory
		//! \param The new size of the memory
		//! \return Returns true if the memory is successfully reallocated with the new size
		//! \warning Be sure to not specify a big amount of memory. This operation can be slow
		static bool MemoryResize(MemoryHandle&, u32);

		//! \brief Free a portion of memory
		//! \details The content on that portion of memory will be deleted
		//! \warning Be sure to not pass an invalid/not initialized MemoryHandle.
		static void MemoryFree(MemoryHandle&);

		//! \brief Open a file
		//! \details It can only open a file that it exist already
		//! \param File's name
		//! \param Define if the file will be opened in read-only
		//! \return Return an handle of the opened file; if FileHandle is NULL, the file was not open
		static FileHandle FileOpen(const String& filename, bool readonly = true);

		//! \brief Open a file and put the position at its end
		//! \details If the file doesn't exist, it will be created from scratch.
		//! \param File's name
		//! \return Return an handle of the opened file; if FileHandle is NULL, the file was not open
		static FileHandle FileAppend(const String& filename);

		//! \brief Create a file
		//! \details With this, the file will be created. If a file with the same name already exists, it will be completely replaced
		//! \param File's name
		//! \return Return an handle of the opened file; if FileHandle is NULL, the file was not open
		//! \warning Be sure when you use this method because it will delete forever the existing file
		static FileHandle FileCreate(const String& filename);

		//! \brief Close a file
		//! \details Close a file from the specified handle if it's really an opened file; after this, the handle will be put to NULL
		//! \param The handle of the file that you want to close
		//! \warning Be sure to pass a valid handle or you will have a crash
		static void FileClose(FileHandle&);

		//! \brief Read the content from a file
		//! \param File's handle
		//! \param Memory's pointer correctly allocated with enough size.
		//! \param The size in bytes to read. This value shouldn't be more than the pointer's size
		//! \return Returns true if the reading operation was successfully completed
		//! \warning If the size exceed the remains bytes, the rests of the memory will be filled with padding data; be totally sure that the pointer's size isn't less than the size to read or you will have a crash.
		static bool FileRead(FileHandle, void*, u32);

		//! \brief Write the content to a file
		//! \details This method works only with FileOpen with readonly = false, FileAppend and FileCreate
		//! \param File's handle
		//! \param Memory's pointer correctly allocated.
		//! \param The size in bytes to write. This value shouldn't be more than the pointer's size
		//! \return Returns true if the writing operation was successfully completed
		//! \warning Be totally sure that the pointer's size isn't less than the size to write or you will have a crash.
		static bool FileWrite(FileHandle, void*, u32);

		//! \brief Move the position between the file specified
		//! \details You can specify a position greater than the file's size; in that case, with FileWrite, the file will be streched
		//! \param File's handle
		//! \param The position to set or move; it can be a negative value to backward trough the file
		//! \param The mode of seeking
		//! \return Returns true if the seeking operation was successfully completed
		static bool FileSeek(FileHandle, int position, FileSeekMode);

		//! \brief Returns the current position of the file
		//! \param File's handle
		//! \return File's position; a negative number means an error
		static int FilePosition(FileHandle);

		//! \brief Returns the file's size in byte of the file specified
		//! \param File's handle
		//! \return File's size; a negative number means an error
		//! \warning This method is slower than int FileLength(String&)
		static int FileLength(FileHandle);

		//! \brief Returns the file's size in byte of the file specified
		//! \param File's name
		//! \return File's size; a negative number means an error
		static int FileLength(const String& filename);

		//! \brief Check if the specified file exists
		//! \param File's name
		//! \return Returns true if the file exists
		static bool FileExist(const String& filename);

		//! \brief Get the length of a string
		//! \details The length is not including the end-string character
		//! \warning Be sure to not pass an invalid/not initialized pointer
		static u32 StringLength(char*);
	};
}
