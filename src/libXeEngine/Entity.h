#pragma once
#include "Node.h"
#include "Graphics.h"

namespace XeEngine
{
	class Entity : public Node
	{
		struct Frame
		{
			short x, y;
			short w, h;
			short cx, cy;
			short pal;
		};
	public:
		Entity();
		~Entity();
		
		//! \brief Stampa i figli e se stesso
		void SelfDraw();

		//! \brief Imposta una texture che fungerà da spritesheet
		void AttachTexture(const Graphics::GraphicID);
		//! \brief Cancella la texture impostata con AttachTexture
		Graphics::GraphicID RemoveTexture();

		//! \brief Crea un frame di animazione
		void CreateFrame(short srcx, short srcy, short width, short height, short centerx, short centery, short palette = 0);
		//! \brief Imposta un frame di animazione
		void SetFrame(u16);
		//! \brief Cancella tutti i frame di animazione
		void DeleteAllFrames();

		Color GetColor() const;
		void SetColor(Color);
		float GetOpacity() const;
		void SetOpacity(float);
	private:
		List<Frame> m_frames;
		Graphics::GraphicID m_gfxid;
		Frame m_curframe;
		Color m_color;
	};
}