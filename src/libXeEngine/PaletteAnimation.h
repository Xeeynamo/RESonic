#pragma once
#include "XeBase.h"

namespace XeEngine
{
	struct ColorComponent
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
	};

	class Memory;
	class PaletteAnimation
	{
	protected:
		Color32* color;
		static bool m_blend;
	public:
		PaletteAnimation()
		{
			SetBlendEffect(true);
		}
		virtual ~PaletteAnimation(){}

		virtual void Do() = 0;
		void AttachLUT(Color32* _color)
		{
			color = _color;
		}
		Color32 FadeColor(Color32 sourceColor, Color32 destColor, u16 frame, u16 max)
		{
			ColorComponent tempColor;
			ColorComponent tempSource;
			ColorComponent tempDest;
			tempSource.color = sourceColor;
			tempDest.color = destColor;

			if (!max) return sourceColor; // avoid divide by zero
			if (frame < 0) frame = 0;
			if (frame > max) frame = max;

			tempColor.r = tempSource.r + (((tempDest.r - tempSource.r) * frame) / max);
			tempColor.g = tempSource.g + (((tempDest.g - tempSource.g) * frame) / max);
			tempColor.b = tempSource.b + (((tempDest.b - tempSource.b) * frame) / max);
			tempColor.a = tempSource.a + (((tempDest.a - tempSource.a) * frame) / max);

			return tempColor.color;
		}
		static bool GetBlendEffect()
		{
			return m_blend;
		}
		static void SetBlendEffect(bool blend)
		{
			m_blend = blend;
		}
	};
}