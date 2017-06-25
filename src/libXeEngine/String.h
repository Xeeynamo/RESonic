#pragma once
#include "Memory.h"

namespace XeEngine
{
	class EXPORT String
	{
	private:
	protected:
		Memory string;
		u32 capacity;

		void Capacity(u32 newsize);
	public:
		//! \brief Initialize an empty string
		String();

		//! \brief Initialize a string from a char's pointer
		String(char*);

		//! \brief Initialize a string from a const char's pointer
		String(const char*);
		
		//! \brief Copy a String to another String
		String& operator = (const String&);

		//! \brief Add to the bottom of the current string another string.
		String& operator += (const String&);

		//! \brief Compare two Strings
		bool operator == (const String&);

		//! \brief Compare two Strings
		bool operator != (const String&);

		//! \brief Get the length of the string
		//! \return Length of the string
		void Copy(const String&);

		//! \brief Get the length of the string
		//! \return Length of the string
		u32 Length() const;

		//! \brief Get the char's pointer of the string
		//! \return Char's pointer
		//! \warning This is a method that returns a pointer. If you edit the length of the string or use a deallocation on it, this class can be dangerous in terms of crashes.
		char* ToChar() const;

		//! \brief Get the path if the string contains it
		//! \param The String that will handle the result
		//! \return Returns true if the string has a path
		bool GetPath(String&) const;

		//! \brief Get the filename if the string contains a path
		//! \param The String that will handle the result
		//! \return Returns true if the string has a filename inside the path
		bool GetFilename(String&) const;

		//! \brief Get the filename with its extension if the string contains a path
		//! \param The String that will handle the result
		//! \return Returns true if the string has a filename inside the path
		bool GetFilenameWithExtension(String&) const;

		//! \brief Get the extension if the string is a file name
		//! \param The String that will handle the result
		//! \return Returns true if the string has an extension
		bool GetExtension(String&) const;

		//! \brief Get the hash of the string
		//! \details The hash is a unique value for each string
		//! \return Returns the hash
		Hash GetHash() const;
	};
}
