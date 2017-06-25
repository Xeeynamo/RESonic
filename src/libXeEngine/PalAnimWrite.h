#pragma once
#include "Memory.h"
#include "Level.h"
#include "PaletteAnimation.h"

namespace XeEngine
{
	namespace PaletteSpace
	{
		struct WriteStruct
		{
			u16 source;
			u8 destX;
			u8 destY;
		};

		//! \brief A simple Palette write class
		class Write : public PaletteAnimation
		{
			Memory* memColorArray;

			Color32* colorArray;
			WriteStruct* description;
			u16 count;
			u16 speed;
			u16 index;
		public:
			//! \details The colors will be written one per time
			Write(Memory& colorArray, WriteStruct* description, u16 count, u16 speed)
			{
				this->memColorArray = &colorArray;
				this->description = description;
				this->count = count;
				this->speed = speed;
				this->index = 0;
				this->colorArray = (Color32*)memColorArray->GetMemoryHandle();

				// Retrocompatibilità e correzione degli errori
				int size = memColorArray->Size() / 4;
				for(int i=0; i < count; i++)
				{
					description[i].source %= size;
					description[i].destX %= colorCount;
					description[i].destY %= paletteCount;
				}
			}

			void Do()
			{
				if (index++ < speed)
					return;
				index -= speed;
				if (color == nullptr)
					return;

				WriteStruct* s = description;
				for(int i=0; i<count; i++, s++)
				{
					color[s->destX + s->destY * colorCount] = colorArray[s->source];
				}
			}
		};
	}
}