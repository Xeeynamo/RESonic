#pragma once
#include "Memory.h"
#include "Level.h"
#include "PaletteAnimation.h"

namespace XeEngine
{
	namespace PaletteSpace
	{
		struct CycleStruct
		{
			u8 srcX;
			u8 srcY;
			u8 srcLength;
			u8 order;
		};
		struct CycleCache
		{
			Color32* prev;
		};
		bool initialization;

		//! \brief A simple Palette write class
		class Cycle : public PaletteAnimation
		{
			Color32* colorArray;
			CycleStruct* description;
			CycleCache* cache;
			u16 count;
			u16 speed;
			u16 index;
		public:
			//! \details The colors will be written one per time
			Cycle(CycleStruct* description, u16 count, u16 speed)
			{
				this->description = description;
				this->count = count;
				this->speed = speed;
				this->index = speed;

				cache = nullptr;
				initialization = false;

				cache = new CycleCache[count];
				for(u16 i=0; i < count; i++)
				{
					description[i].srcX %= colorCount;
					description[i].srcY %= paletteCount;
					description[i].order %= 2;
					cache[i].prev = new Color32[description[i].srcLength];
				}
			}
			~Cycle()
			{
				if (cache != nullptr)
				{
					for(u16 i=0; i < count; i++)
					{
						SAFE_ADELETE(cache[i].prev);
					}
					SAFE_ADELETE(cache);
				}
				SAFE_ADELETE(description);
			}

			void ShiftColors(Color32* colorRange, u16 length, bool verse)
			{
				Color32 temp;

				temp = colorRange[length - 1];
				for (ptrdiff_t i = length - 1; i > 0; i--)
					colorRange[i] = colorRange[i - 1];
				colorRange[0] = temp;
			}
			void BlendShiftColors(Color32* colorRange, Color32* cache, u16 length, bool verse)
			{
				if (index == 0)
					ShiftColors(cache, length, verse);

				for(ptrdiff_t i = 1; i < length; i++)
				{
					colorRange[i] = FadeColor(cache[i], cache[i - 1], index, speed);
				}
				colorRange[0] = FadeColor(cache[0], cache[length - 1], index, speed);
			}

			void Do()
			{
				if (GetBlendEffect())
				{
					if (initialization == false)
					{
						Color32* c;
						CycleStruct* s = description;
						for(ptrdiff_t i = 0; i < count; i++, s++)
						{
							c = &color[s->srcX];
							for(ptrdiff_t j = 0; j < s->srcLength; j++)
							{
								cache[i].prev[j] = c[j];
							}
						}
						initialization = true;
					}

					if (index++ >= speed)
					{
						index = 0;
					}

					CycleStruct* s = description;
					for(ptrdiff_t i = 0; i < count; i++, s++)
					{
						BlendShiftColors(color + s->srcX, cache[i].prev, s->srcLength, s->order != 0);
					}
				}
				else
				{
					if (index++ < speed)
					{
						return;
					}
					index = 0;

					CycleStruct* s = description;
					for(ptrdiff_t i = 0; i < count; i++, s++)
					{
						ShiftColors(color + s->srcX, s->srcLength, s->order != 0);
					}
				}

				/*CycleStruct* s = description;
				if (index++ < speed)
				{
					return;
				}
				index = 0;
				if (color == nullptr)
					return;

				s = description;
				Color32 tmp;
				for(ptrdiff_t i = 0, j; i < count; i++, s++)
				{
					Color32* c = &color[s->srcX];
					if (s->order == 0)
					{
						j = s->srcLength - 1;
						tmp = c[j];
						for(; j > 0; j--)
						{
							cache[i].prev[j] = c[j] = c[j - 1];
						}
						cache[i].prev[j] = c[j] = tmp;
					}
					else
					{
						tmp = c[0];
						for(j = 0; j < s->srcLength - 1; j++)
						{
							cache[i].prev[j] = c[j] = c[j + 1];
						}
						cache[i].prev[j] = c[j] = tmp;
					}
				}*/
			}
		};
	}
}