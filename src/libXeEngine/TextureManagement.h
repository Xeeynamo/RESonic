#pragma once
#include "XeBase.h"

namespace XeEngine
{
	class Texture;
	class TextureManagement
	{
	public:
		void Initialize(u8 resolution);
	private:
		static Texture texcont[4];
	};
}