#pragma once
#include "System.h"
#include "Memory.h"
#include "Level.h"
#include "PaletteAnimation.h"

namespace XeEngine
{
	namespace PaletteSpace
	{
		struct WriteArrayStruct
		{
			u16 source;
			u8 destX;
			u8 destY;
		};

		//! \brief A Palette Animation class that writes array
		class WriteArray : public PaletteAnimation
		{
			Memory* memColorArray;

			Color32* colorArray;
			WriteArrayStruct* description;
			u16 count;
			u16 speed;
			u16 index;
			u16 arraySize;
		public:
			//! \details The colors will be written one per time
			WriteArray(Memory& colorArray, WriteArrayStruct* description, u16 count, u16 speed, u16 arraySize)
			{
				this->memColorArray = &colorArray;
				this->description = description;
				this->count = count;
				this->speed = speed;
				this->arraySize = arraySize;
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

				WriteArrayStruct* s = description;
				for(int i=0; i<count; i++, s++)
				{
					XeEngine::MemoryCopy(&color[s->destX + s->destY * colorCount], &colorArray[s->source], arraySize);
				}
			}
		};
	}
}