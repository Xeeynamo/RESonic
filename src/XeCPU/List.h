#pragma once

template <class T> class List
{
private:
	typedef struct _InternalList
	{
		T value;
		struct _InternalList *prev;
		struct _InternalList *next;
	} InternalList;

	InternalList *list;
	InternalList *listIndex;
	int count;
public:
	List()
	{
		list = 0;
		listIndex = 0;
		count = 0;
	}
	~List()
	{
		InternalList *l = list;
		while(l)
		{
			InternalList *tmp = l;
			l = l->next;
			delete tmp;
		}
	}

	int Count()
	{
		return count;
	}
	void Add(T value)
	{
		InternalList *l = list;
		if (count)
		{
			do
			{
				if (l->next)
					l = l->next;
				else
				{
					l->next = new InternalList;
					l->next->prev = l;
					l = l->next;
					l->value = value;
					l->next = 0;
					l = 0;
					count++;
					return;
				}
			} while(l);
		}
		else
		{
			list = new InternalList;
			list->value = value;
			list->prev = 0;
			list->next = 0;
			listIndex = list;
			count++;
		}
	}
	void Remove(T value)
	{
		if (!count) return;
		InternalList *l = list;
		if (l->value == value)
		{
			list = list->next;
			list->prev = 0;
			delete l;
			return;
		}
		do
		{
			if (l->next)
			{
				if (l->next->value == value)
				{
					InternalList *lx = l->next->next;
					lx->prev = l;
					delete l->next;
					l->next = lx;
					return;
				}
				l = l->next;
			}
		} while(l);
	}
	bool Get(int index, T *value)
	{
		if (index >= count) return false;
		if (index < 0) return false;
		if (!value) return false;
		InternalList *l = list;
		for(int i=0; i<index; i++)
		{
			if (!l->next) return false;
			l = l->next;
		}
		*value = l->value;
		return true;
	}
	void Set(int index, T value)
	{
		if (index >= count) return false;
		if (index < 0) return false;
		if (!value) return false;
		InternalList *l = list;
		for(int i=0; i<index; i++)
		{
			if (!l->next) return;
			l = l->next;
		}
		l->value = *value;
	}
	int Search(T value)
	{
		InternalList *l = list;
		int index = 0;
		while(l)
		{
			if (l->value == value) return index;
			if (!l->next) return -1;
			l = l->next;
			index++;
		}
		return -1;
	}
	void Top(T value)
	{
		if (count < 2) return;
		InternalList *ltop = 0;
		InternalList *l = list;
		if (l->value == value)				// Se il primo valore della lista è quello da mettere in cima
		{
			list = list->next;				// Allora toglilo dalla lista come primo elemento
			ltop = l;						// e memorizzalo in ltop
		}
		do
		{
			if (l->next)								// Se il prossimo elemento della lista è pieno
			{											// allora continua la verifica
				if (l->next->value == value)			// Se il prossimo elemento è quello che stiamo cercando 
				{
					if (!l->next->next) return;			// Se il valore da mettere in cima è già in cima, allora esce
					ltop = l->next;						// ltop diventa l'elemento successivo alla lista
					l->next->next->prev = l;			// l'elemento successivo a quello trovato punterà ad l invece che al valore trovato
					l->next = l->next->next;			// l'elemento successivo di l diventerà l'elemento successivo di quello trovato
				}
				l = l->next;							// passa alla lista successiva
			}
			else if (ltop)					// Altrimenti se ltop è stato trovato
			{
				ltop->next = 0;				// fa in modo di non far esistere nessuna lista dopo ltop
				l->next = ltop;				// l'ultimo elemento della lista ora diventa il penultimo e punta a ltop
				ltop->prev = l;				// l'elemento precedente di ltop, è il penultimo elemento
				return;						// la funzione non necessità più di continuare, quindi esce
			}
			else return;					// se non è stato trovato ltop, esce
		} while(1);
	}

	void First()
	{
		listIndex = list;
	}
	void Last()
	{
		First();
		if (!listIndex) return;
		while(listIndex->next)
		{
			listIndex = listIndex->next;
		}
	}
	bool Prev(T *v)
	{
		if (!listIndex) return false;
		*v = listIndex->value;
		listIndex = listIndex->prev;
		return true;
	}
	bool Next(T *v)
	{
		if (!listIndex) return false;
		*v = listIndex->value;
		listIndex = listIndex->next;
		return true;
	}
	T *GetNext()
	{
		if (!listIndex) return false;
		T *v = &listIndex->value;
		listIndex = listIndex->next;
		return v;
	}
};