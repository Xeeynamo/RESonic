#pragma once
#include "XeSystem.h"
#include "XeString.h"
#include "XeMemory.h"

namespace XeEngine
{
	class File
	{
	public:
		//! \brief Initialize the variables to manage files
		File();
		~File();

		//! \brief Check if a file exist
		//! \param File's name
		//! \return Returns true if the file exists
		static bool Exist(String& filename);

		//! \brief Create a file from scratch
		//! \details See XeEngine::XeSystem::FileCreate for more informations
		//! \param File's name
		//! \return Returns true if the file is successfully created
		bool Create(String& filename);

		//! \brief Open an exist file
		//! \details See XeEngine::XeSystem::FileOpen for more informations
		//! \param File's name
		//! \return Returns true if the file is successfully created
		bool Open(String& filename, bool readonly = true);

		//! \brief Close the file if it was opened
		void Close();

		//! \brief Get the current size of the file
		//! \return File's size
		//! \warning If the file was not opened in readonly, the calculation of file's size can be slower
		size_t Size();

		//! \brief Get the current position of the file
		//! \return File's position
		int Position();

		//! \brief Read a portion of data
		//! \param Buffer's data
		//! \param The bytes to read
		//! \warning See XeEngine::XeSystem::FileRead to know the warnings
		void Read(void *data, size_t size);

		//! \brief Write a portion of data
		//! \details This method will not works if the file was opened in readonly mode
		//! \param Buffer's data
		//! \param The bytes to read
		//! \warning See XeEngine::XeSystem::FileWrite to know the warnings
		void Write(void *data, size_t size);

		//! \brief Write a portion of data
		//! \details See XeEngine::XeSystem::FileSeek to know more details
		//! \param The offset to move
		//! \param The seek mode
		void Seek(int offset = 0, FileSeekMode origin = FileSeekMode::FILESEEK_SET);

		//! \brief Get the entire file as XeMemory
		//! \details After the call, the file position will be at the end of the file
		//! \param The XeEngine::XeMemory
		//! \warning Be sure to avoid the Lock on big files (500MB or more).
		void Lock(Memory&);

		//! \brief Set the entire file as XeMemory
		//! \details After the call, the file position will be at the end of the file. All the previous content will be destroyed. If the file's size is more than the size of XeMemory, the old file's data will be left
		//! \param The XeEngine::XeMemory
		//! \warning Be sure to avoid the Lock on big files (500MB or more)
		void Unlock(Memory&);
	private:
		bool m_readonly;
		size_t m_filesize;
		FileHandle f;
	};
}