#pragma once
#include "Video.h"
#include "System.h"

namespace XeEngine
{
	class Image;
	class Graphics
	{
		// Dimensione massima delle textuers atlas (la dimensione è cubica)
		static const u16 TextureBufferHeight = 1024; // **** CAMBIARE IL NOME IN TextureBufferSize
		// Profondità di colore. 8BPP per quando si vuole usare il CLUT, 32BPP se invece no.
		static const u16 TextureBufferBPP = 8 / 8;
		// Numero di texture atlas presenti
		static const u16 TextureAtlasCount = 16;
		// Dimensione minima di una texture
		static const u16 TexBoxMinSize = 16;
		// Dimensione massima di una texture
		static const u16 TexBoxMaxSize = TextureBufferHeight;
		// Numero massimo delle superfici 
		static const u16 GraphicSurfacesMaxCount = 512;
		// Quantità di indici per i vertici 2D bufferizzati. Non può superare 0xFFFC.
		static const int VerticesIndexSize = (0xFFFC / 6) * 6;
		static const int VerticesCacheSize = VerticesIndexSize / 6 * 4;

		struct GraphicSurface
		{
			Image* image;
			Hash hash;
			u16 width;
			u16 height;
			u16 x;
			u16 y;
		};
	public:
		typedef UID GraphicID;

		static const GraphicID ImageNull = (UID)(-1);

		// Risoluzione interna di gioco
		static float ResWidth;
		static float ResHeight;
		// L'ID della texture del Color Look-Up Table
		static TextureID TexClut;
		// Gli ID delle textures atlas
		static TextureID TexBox[];
		// Risoluzione interna della texture atlas
		static u16 TexBoxResolution;
		// Buffer di memoria dell'intera area di memoria della texture
		static MemoryHandle TexBoxBuffer;
		// Descrizione delle singole superfici delle immagini contenute nelle textures atlas
		static GraphicSurface gfxSurface[];
		// Cache dei vertici
		static Vertex verticesCache[];
		// Indici che descrivono l'ordine dei vertici 2D
		static u16 verticesIndices[];
		// Numero dei vertici 2D inseriti
		static u16 vertPosition;
		// Numero dei triangoli 2D inseriti
		static u16 vertIndexPosition;
		// Palette corrente
		static float selectedPalette;
		// ID della texture
		static TextureID texturePalette;
		// Zona di memoria dove è locata la palette
		static MemoryHandle clutZone;
		
		// Inizializza il sistema Graphics
		static void Initialize();
		// Libera la memoria dal sistema Graphics
		static void Destroy();

		// Gestione cache
		static void CacheVertices2D(Vertex*);
		static void FlushVertices();

		// Gestione vertici 2D
		static void SetResolution(const u16 width, const u16 height, const u16 res);
		static void DrawSprite(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy);
		static void DrawSpriteScaled(const GraphicID id, const short dstx, const short dsty, const short dstw, const short dsth,
			const short srcx, const short srcy, const short srcw, const short srch);
		static void DrawSpriteRotated(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy, const short xpivot, const short ypivot, const float rotz);
		static void DrawSpriteRotation(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy, const short xpivot, const short ypivot, const float rotx, const float roty, const float rotz);
		static void DrawSpriteComplete(const GraphicID id, const short dstx, const short dsty, const short dstw, const short dsth,
			const short srcx, const short srcy, const short srcw, const short srch, const short pivotx, const short privoty,
			const float rotx, const float roty, const float rotz, const u32 color);

		// Gestione palette
		static void SelectPalette(const u8 index);
		static u32* GetPalette(u16 x, u16 y);
		static void RefreshPalette();

		// Gestione textures

		//! \brief Genera un elenco di macrotextures che funzioneranno da box che conterrà texture singole
		//! \returns Ritorna la dimensione in byte della texture. Ritorna 0 se la textuer non è stata creata
		//! \details Le dimensioni consigliate sono multipli di 1024 e come count massimo 16
		static size_t GenerateTextures(u16 width, u16 height, u32 count);

		//! \brief Aggiunge un'immagine al sistema di texture management
		static GraphicID AddImage(const char* filename);

		//! \brief Rimuove un'immagine a partire dal nome del suo file
		static void RemoveImage(const char* filename);

		//! \brief Rimuove un'immagine a partire dal suo ID
		static void RemoveImageFromID(GraphicID id);

		//! \brief Vede se la dimensione verticale / orizzontale di un'immagine è corretta
		//! \details Le dimensioni valide sono multipli di 2 da 16 a 1024
		static bool CheckImageSize(u16 size);

		//! \brief Riordina le immagini caricate nel texture management
		static void SortImages();

		//! \brief Effettua l'upload delle textures. Richiede prima il loro riordinamento via SortImages()
		static void UploadImages();
	};
}