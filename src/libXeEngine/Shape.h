#pragma once
#include "Video.h"
#include "Color.h"

namespace XeEngine
{
	class Shape
	{
	private:
	public:
		static void Initialize();

		static void SetColor(unsigned int);
		static void SetColorArray(unsigned int, unsigned int, unsigned int, unsigned int);
		static void DrawRect(float x, float y, float z, float width, float height);
		static void FillRect(float x, float y, float z, float width, float height);
	};
}