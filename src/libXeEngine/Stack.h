#pragma once
#include "XeBase.h"

namespace XeEngine
{
	template <class T> class EXPORT Stack
	{
	private:
		s32 top;
		s32 bottom;
		s32 elements;
		s32 capacity;
		T* stack;
	public:
		//! \brief Create a stack with fixed size.
		//! \param Specify the capacity of the stack.
		Stack(s32 capacity = 20)
		{
			top = -1;
			bottom = 0;
			elements = 0;
			if (capacity <= 0)
				return;
			this->capacity = capacity;
			stack = new T[(size_t)capacity];
		}
		~Stack()
		{
			delete[] stack;
		}

		//! \brief Check if the stack is empty.
		//! \return true if the stack is empty, false if it is not.
		bool isEmpty() const
		{
			return elements == 0;
		}
		//! \brief Get the count of elements inside the stack.
		//! \return Elements inside the stack.
		int Count() const
		{
			return elements;
		}

		//! \brief Insert an element inside the stack. If the stack is already empty, the oldest element will be replaced by the new one.
		//! \param The element that will be inserted.
		void Push(T& value)
		{
			top++;
			if (top >= capacity)
			{
				top = 0;
			}
			if (elements >= capacity)
			{
				top = bottom;
				bottom++;
			}
			else elements++;
			stack[top] = value;
		}

		//! \brief Get an element inside the stack removing it.
		bool Pop(T& value)
		{
			if (isEmpty()) return false;
			elements--;
			value = stack[top--];
			return true;
		}
		//! \brief Remove an element inside the stack without to get it
		bool Pop()
		{
			if (isEmpty())
				return false;
			elements--;
			top--;
			return true;
		}

		//! \brief Get an element inside the stack without to remove it.
		//! \return The pointer to the last element inserted.
		/*T* Peek()
		{
			if (elements == 0) return 0;
			return &stack[top];
		}*/
		void Peek(T*& value)
		{
			if (isEmpty())
				return;
			value = &stack[top];
		}
	};
}