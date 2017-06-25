#pragma once
#include <math.h>
#include "Vector.h"

namespace XeEngine
{
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ABS(a) (((a) >= (0)) ? (a) : (-(a)))

	template <class T> inline const T& Min(const T& a, const T& b)
	{
		return MIN(a, b);
	}
	template <class T> inline const T& Max(const T& a, const T& b)
	{
		return MAX(a, b);
	}
	template <class T> inline T Abs(const T& a)
	{
		return ABS(a);
	}
	template <class T> inline T Sqrt(const T& a)
	{
		return (T)sqrt((float)a);
	}

	template <typename T, typename U> inline void InsertionSort(T& a, size_t length, bool order)
	{
		U tmp;
		for(size_t i = 1, j; i < length; i++)
		{
			tmp = a[i];
			j = i - 1;
			while((s32)j >= 0 && (a[j] > tmp) == order)
			{
				a[j + 1] = a[j];
				j--;
			}
			a[j + 1] = tmp;
		}
	}

	template <typename T, typename U, typename V> inline void InsertionSortWithProgram(T& a, size_t length, bool order, V (*ProgramGet)(U* t), void (*ProgramSet)(U* t, V v))
	{
		V tmp;
		for(size_t i = 1, j; i < length; i++)
		{
			tmp = ProgramGet(a[i]);
			j = i-1;
			while(j >= 0 && (ProgramGet(a[j]) > tmp) == order)
			{
				a[j + 1] = a[j];
				j--;
			}
			ProgramSet(a[j + 1], tmp);
		}
	}
}
