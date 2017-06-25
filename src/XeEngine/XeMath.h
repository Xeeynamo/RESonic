#pragma once

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
}