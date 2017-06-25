#pragma once
#include "XeBase.h"

namespace XeEngine
{
	template <class T>
	class EXPORT Geometry2
	{
	public:
		T x, y;
	public:
		Geometry2()
		{
			x = 0;
			y = 0;
		}
		Geometry2(T x, T y)
		{
			Set(x, y);
		}
		void Set(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		Geometry2<T>& operator = (const XeEngine::Geometry2<T>& src)
		{
			Set(src.x, src.y);
			return *this;
		}
		bool operator == (const XeEngine::Geometry2<T>& src)
		{
			if (x == src.x && y == src.y) return true;
			return false;
		}
		bool operator != (const XeEngine::Geometry2<T>& src)
		{
			if (x == src.x && y == src.y) return false;
			return true;
		}
		Geometry2<T>& operator *= (const XeEngine::Geometry2<T>& src)
		{
			Set(x * src.x, y * src.y);
			return *this;
		}
		Geometry2<T>& operator /= (const XeEngine::Geometry2<T>& src)
		{
			Set(x / src.x, y / src.y);
			return *this;
		}
		Geometry2<T>& operator *= (const float& src)
		{
			Set(x * src, y * src);
			return *this;
		}
		Geometry2<T>& operator /= (const float& src)
		{
			Set(x / src, y / src);
			return *this;
		}
	};
	template <class T>
	class EXPORT Geometry3
	{
	public:
		T x, y, z;
	public:
		Geometry3(T x, T y, T z)
		{
			Set(x, y, z);
		}
		void Set(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Geometry3& operator = (const XeEngine::Geometry3& src)
		{
			Set(src.x, src.y, src.z);
			return *this;
		}
		bool operator == (const XeEngine::Geometry3& src)
		{
			if (x == src.x && y == src.y && z == src.z) return true;
			return false;
		}
		bool operator != (const XeEngine::Geometry3& src)
		{
			if (x == src.x && y == src.y && z == src.z) return false;
			return true;
		}
		Geometry3& operator *= (const XeEngine::Geometry3& src)
		{
			Set(x * src.x, y * src.y, z);
			return *this;
		}
		Geometry3& operator /= (const XeEngine::Geometry3& src)
		{
			Set(x / src.x, y / src.y, z);
			return *this;
		}
		Geometry3& operator *= (const float& src)
		{
			Set(x * src, y * src, z);
			return *this;
		}
		Geometry3& operator /= (const float& src)
		{
			Set(x / src, y / src, z);
			return *this;
		}
	};
}