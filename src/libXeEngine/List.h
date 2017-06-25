#pragma once

namespace XeEngine
{
	template <class T> class EXPORT List
	{
	private:
		struct Node
		{
			T value;
			struct Node *next;
			struct Node *prev;
		};

		size_t count;
		Node dummy;
		Node *cursor;

		void Initialize()
		{
			count = 0;
			dummy.next = &dummy;
			dummy.prev = &dummy;
			cursor = &dummy;
		}
		void Reset()
		{
			Node* c = dummy.next;
			while(c != &dummy)
			{
				c = c->next;
				delete c->prev;
			}
		}
	public:
		List()
		{
			Initialize();
		}
		~List()
		{
			Reset();
		}

		//! \brief Get the elements count inside the list
		//! \return Elements count
		size_t Count() const
		{
			return count;
		}

		//! \brief Check if the end of the list is reached
		//! \return True if the end of the list is reached
		bool EndOfList() const
		{
			return cursor == &dummy;
		}

		//! \brief Add an element after the current position
		//! \param Value to add
		void Add(T value)
		{
			Node* node = new Node;
			node->value = value;
			node->prev = cursor;
			node->next = cursor->next;
			cursor->next = node;
			cursor = node;
			if (cursor->next == &dummy)
				dummy.prev = cursor;
			count++;
		}

		//! \brief Delete the element with that value
		//! \param It will be deleted the first element found with that value; the search starts from the Head
		//! \return Returns true if the value was found and deleted, false if nothing happens
		bool Remove(T value)
		{
			Node* c = dummy.next;
			while(c != &dummy)
			{
				if (c->value == value)
				{
					c->prev->next = c->next;
					c->next->prev = c->prev;
					if (cursor == c)
						cursor = cursor->prev;
					delete c;
					count--;
					return true;
				}
				c = c->next;
			}
			return false;
		}

		//! \brief Delete the element on the specified position
		//! \param The position to delete
		//! \return Returns true if the value was found and deleted, false if nothing happens
		bool RemoveAt(size_t position)
		{
			if (position >= Count()) return false;

			Node* c = dummy.next;
			for(size_t i = 0; c != &dummy; i++)
			{
				if (i == position)
				{
					c->prev->next = c->next;
					c->next->prev = c->prev;
					if (cursor == c)
						cursor = cursor->prev;
					delete c;
					count--;
					return true;
				}
				c = c->next;
			}
			return false;
		}

		//! \brief Remove all the elements
		void RemoveAll()
		{
			Reset();
			Initialize();
		}

		//! \brief Move to the head of the list
		void MoveHead()
		{
			cursor = dummy.next;
		}

		//! \brief Move to the tail of the list
		void MoveTail()
		{
			cursor = dummy.prev;
		}

		//! \brief Get the current value from the current position as a pointer without to move
		//! \param The pointer to the value that will handle the return value
		//! \return Returns false if the end of the list was reached
		bool Pointer(T* value)
		{
			if (EndOfList()) return false;
			value = &cursor->value;
			cursor = cursor->next;
			return true;
		}

		//! \brief Get the current value from the current position and increase the cursor by one step
		//! \param The referement to the value that will handle the return value
		//! \return Returns false if the end of the list was reached
		bool Next(T& value)
		{
			if (EndOfList()) return false;
			value = cursor->value;
			cursor = cursor->next;
			return true;
		}

		//! \brief Get the current value from the current position and decrease the cursor by one step
		//! \param The referement to the value that will handle the return value
		//! \return Returns false if the end of the list was reached
		bool Prev(T& value)
		{
			if (EndOfList()) return false;
			value = cursor->value;
			cursor = cursor->prev;
			return true;
		}

		//! \brief Search a value and returns its index
		//! \details The cursor's value will not be modified; if the element was not found, the reference value will not be modified
		//! \param The value to search
		//! \param The reference of the value that will handle the position of the found's element
		//! \return Returns true if the value was found
		bool Search(const T& value, int& position)
		{
			T v;
			int pos = -1;
			Node *tmp = cursor;
			MoveHead();
			while(Next(v))
			{
				pos++;
				if (v == value)
				{
					position = pos;
					cursor = tmp;
					return true;
				}
			}
			cursor = tmp;
			return false;
		}

		//! \brief Copy the current list on another list
		//! \details The cursor's value of the current will not be modified; the destination's cursor will be moved to the head
		//! \param The list that will receive the copy
		void Copy(const List& dst)
		{
			Node* tmp = cursor;
			dst.RemoveAll();
			MoveHead();
			while(EndOfList() == false)
			{
				T value;
				Next(value);
				dst.Add(value);
			}
			dst.MoveHead();
			cursor = tmp;
		}

		//! \brief Get an element by the index
		//! \details You can specify a negative value to navigate from the tail to the head; If index is greater than Count(), the index will be wrapped
		T& operator [] (ptrdiff_t  index)
		{
			Node* c;
			index %= count;
			c = dummy.next;
			for(ptrdiff_t  i=0; i < index; i++)
				c = c->next;
			return c->value;
		}
	};
}