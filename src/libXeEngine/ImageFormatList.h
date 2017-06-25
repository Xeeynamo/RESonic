#pragma once
#include "GFX.h"

namespace XeEngine
{
	namespace ImageFramework
	{
		void InitializeImageFormatList()
		{
			ImageFormat format;

			format.extension = String("gfx");
			format.function = GFX;
			Image::AddImageFormat(format);
		}
	}
}