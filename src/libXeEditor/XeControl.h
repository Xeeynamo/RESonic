#pragma once
#include "../libXeEngine/XeBase.h"

namespace Editor
{
	class MainEditor;

	struct Color
	{
		union
		{
			struct 
			{
				u8 r;
				u8 g;
				u8 b;
				u8 a;
			};
			u32 color;
		};

		Color()
		{
			color = 0xFF000000;
		}
		Color(u8 r, u8 g, u8 b, u8 a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		Color(u32 color)
		{
			this->color = color;
		}
	};
	struct Position
	{
		u16 x;
		u16 y;

		Position()
		{
			x = 0;
			y = 0;
		}
		Position(u16 _x, u16 _y)
		{
			x = _x;
			y = _y;
		}
	};
	struct Size
	{
		u16 width;
		u16 height;

		Size()
		{
			width = 0;
			height = 0;
		}
		Size(u16 w, u16 h)
		{
			width = w;
			height = h;
		}
	};
}