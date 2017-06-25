#pragma once
#include "Video.h"
#include "Color.h"
#include "List.h"
#include "Node.h"
#include "Matrix.h"
#include "String.h"

namespace XeEngine
{
	class Texture;
	class Effect;
	class Sprite : public XeEngine::Node
	{
		struct SpriteFrame
		{
			float startx;
			float starty;
			float endx;
			float endy;
			float centerx;
			float centery;
			float palette;
			float width;
			float height;

			SpriteFrame()
			{
				startx = starty = 0.0f;
				endx = endy = 1.0f;
				centerx = centery = 0.5f;
				palette = 0.0f;
				width = height = 256.0f;
			}
			SpriteFrame(float sx, float sy, float ex, float ey, float cx, float cy, float p, float w, float h)
			{
				startx = sx;
				starty = sy;
				endx = ex;
				endy = ey;
				centerx = cx;
				centery = cy;
				palette = p;
				width = w;
				height = h;
			}
		};
	private:
		bool created_texture;
		bool created_palette;
		float m_opacity;
		List<SpriteFrame> m_listFrame;
		u16 m_frame;

		float m_texWidth, m_texHeight, m_texDepth;
	protected:
		Texture* m_texture;

		Vertex v[4];
	public:
		Sprite();
		~Sprite();

		//! \brief Destroy the sprite
		void Destroy();
		//! \brief Draw itself and own childs
		void SelfDraw();

		void AttachTexture(Texture&);
		void CreateTexture(Texture*);
		void LoadPalette(String&);

		//! \brief Ottiene il colore usato come filtro
		void GetColor(Color&) const;
		//! \brief Imposta un colore di filtro
		void SetColor(const Color&);
		//! \brief Ottiene il livello di trasparenza
		float GetOpacity() const;
		//! \brief Imposta il livello di trasparenza
		void SetOpacity(float);

		//! \brief Crea un frame
		void CreateFrame(short srcx, short srcy, short width, short height, short centerx, short centery, short palette = 0);
		//! \brief Imposta un frame
		void SetFrame(u16);
	};
}
