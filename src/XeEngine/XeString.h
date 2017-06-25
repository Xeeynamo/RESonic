#pragma once
#include "XeMemory.h"

namespace XeEngine
{
	class String
	{
	private:
	protected:
		Memory string;
		size_t capacity;

		void Capacity(int newsize);
	public:
		//! \brief Initialize an empty string
		String();

		//! \brief Initialize a string from a char's pointer
		String(char*);
		
		//! \brief Copy a String to another String
		String& operator = (const String&);

		//! \brief Add to the bottom of the current string another string.
		String& operator += (const String&);

		//! \brief Get the length of the string
		//! \return Length of the string
		size_t Length() const;

		//! \brief Get the char's pointer of the string
		//! \return Char's pointer
		//! \warning This is a method that returns a pointer. If you edit the length of the string or use a deallocation on it, this class can be dangerous in terms of crashes.
		char* ToChar() const;
	};
}