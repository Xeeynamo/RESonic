#include "Graphics.h"
#include "Math.h"
#include "Image.h"
#include "ImageFormatList.h"

#define COORDTO3DX(i, j)		( ( (i) - (j) / 2.0f ) / (j) * +2.0f )
#define COORDTO3DY(i, j)		( ( (i) - (j) / 2.0f ) / (j) * -2.0f )

namespace XeEngine
{
	float Graphics::ResWidth = 1.0f;
	float Graphics::ResHeight = 1.0f;
	TextureID Graphics::TexClut = 0;
	TextureID Graphics::TexBox[TextureAtlasCount];
	u16 Graphics::TexBoxResolution;
	MemoryHandle Graphics::TexBoxBuffer;
	Graphics::GraphicSurface Graphics::gfxSurface[GraphicSurfacesMaxCount];
	Vertex Graphics::verticesCache[VerticesCacheSize];
	u16 Graphics::verticesIndices[VerticesIndexSize];
	u16 Graphics::vertPosition = 0;
	u16 Graphics::vertIndexPosition = 0;
	float Graphics::selectedPalette = 0.0f;
	TextureID Graphics::texturePalette;
	MemoryHandle Graphics::clutZone;
	
	void Graphics::Initialize()
	{
		Math::Initialize();
		ImageFramework::InitializeImageFormatList();
		for(u16 i = 0; i < TextureAtlasCount; i++)
		{
			TexBox[i] = 0;
		}
		for(size_t i = 0; i < GraphicSurfacesMaxCount; i++)
		{
			GraphicSurface* gfxdesc = &gfxSurface[i];
			gfxdesc->image = nullptr;
			gfxdesc->hash = 0;
		}
		for(size_t i = 0, j = 0; i < VerticesCacheSize; i += 4)
		{
			verticesIndices[j++] = i + 0;
			verticesIndices[j++] = i + 1;
			verticesIndices[j++] = i + 2;
			verticesIndices[j++] = i + 1;
			verticesIndices[j++] = i + 2;
			verticesIndices[j++] = i + 3;
		}
		vertPosition = 0;
		vertIndexPosition = 0;

		System::MemoryAllocZero(clutZone, 256 * 256 * sizeof(u32));
		Video::UploadTexture(texturePalette, 256, 256, PixelFormat_RGBA8888, clutZone);

		TexBoxBuffer = nullptr;
		TexBoxResolution = 0;
		SetResolution(320, 240, 1);
	}
	void Graphics::Destroy()
	{
		System::MemoryFree(clutZone);
		System::MemoryFree(TexBoxBuffer);
	}
	void Graphics::CacheVertices2D(Vertex* v)
	{
		if (vertPosition + 4 > VerticesCacheSize)
		{
			//con.Log(DEBUG_LEVEL_WARNING, "%s full", vertPosition >= VerticesCacheSize ? "vertex cache" : "vertex indices");
			FlushVertices();
		}

		verticesCache[vertPosition++] = v[0];
		verticesCache[vertPosition++] = v[1];
		verticesCache[vertPosition++] = v[2];
		verticesCache[vertPosition++] = v[3];

		vertIndexPosition++;
	}
	void Graphics::FlushVertices()
	{
		Video::SelectTexture(TexBox[0]);
		Video::SendIndexedVertices(verticesCache, verticesIndices, vertIndexPosition * 2, Primitives_TriangleList);
		vertPosition = 0;
		vertIndexPosition = 0;
	}
	void Graphics::SetResolution(const u16 width, const u16 height, const u16 resolution)
	{
		ResWidth = (float)width;
		ResHeight = (float)height;

		if (TexBoxResolution != resolution)
		{
			TexBoxResolution = resolution;
			System::MemoryFree(TexBoxBuffer);
			System::MemoryAlloc(TexBoxBuffer, 1024 * TextureBufferHeight * resolution * TextureBufferBPP);
			Video::UploadTexture(TexBox[0], 1024, TextureBufferHeight, TextureBufferBPP == 4 ? PixelFormat_RGBA8888 : PixelFormat_A8, TexBoxBuffer);
			Video::SelectTexture(TexBox[0]);
		}
	}
	void Graphics::DrawSprite(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy)
	{
		float x1 = COORDTO3DX( (float)( x ), ResWidth );
		float y1 = COORDTO3DY( (float)( y ), ResHeight );
		float x2 = COORDTO3DX( (float)( x + width ), ResWidth );
		float y2 = COORDTO3DY( (float)( y + height ), ResHeight );
		float texU1 = (float)(gfxSurface[id].x + srcx) / 1024.0f;
		float texV1 = (float)(gfxSurface[id].y + srcy) / 1024.0f;
		float texU2 = (float)(width) / 1024.0f + texU1;
		float texV2 = (float)(height) / 1024.0f + texV1;

		Vertex v[] =
		{
			{ x1, y2, texU1, texV2, selectedPalette, 0xFFFFFFFF },
			{ x1, y1, texU1, texV1, selectedPalette, 0xFFFFFFFF },
			{ x2, y2, texU2, texV2, selectedPalette, 0xFFFFFFFF },
			{ x2, y1, texU2, texV1, selectedPalette, 0xFFFFFFFF },
		};

		CacheVertices2D(v);
	}
	void Graphics::DrawSpriteScaled(const GraphicID id, const short dstx, const short dsty, const short dstw, const short dsth,
		const short srcx, const short srcy, const short srcw, const short srch)
	{

	}
	void Graphics::DrawSpriteRotated(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy, const short xpivot, const short ypivot, const float rotz)
	{
		float xp = (float)( x + xpivot );
		float yp = (float)( y + ypivot );

		float x1 = (float)( x );
		float y1 = (float)( y );
		float x2 = (float)( x + width );
		float y2 = (float)( y + height );
		float texU1 = (float)(gfxSurface[id].x + srcx) / 1024.0f;
		float texV1 = (float)(gfxSurface[id].y + srcy) / 1024.0f;
		float texU2 = (float)(width) / 1024.0f + texU1;
		float texV2 = (float)(height) / 1024.0f + texV1;

		Vertex v[] =
		{
			{ 0.0f, 0.0f, texU1, texV2, selectedPalette, 0xFFFFFFFF },
			{ 0.0f, 0.0f, texU1, texV1, selectedPalette, 0xFFFFFFFF },
			{ 0.0f, 0.0f, texU2, texV2, selectedPalette, 0xFFFFFFFF },
			{ 0.0f, 0.0f, texU2, texV1, selectedPalette, 0xFFFFFFFF },
		};

		float cosrot = Math::Cosf(rotz);
		float sinrot = Math::Sinf(rotz);

		float xcos1 = (x1 - xp) * cosrot;
		float xsin1 = (x1 - xp) * sinrot;
		float ycos1 = (y1 - yp) * cosrot;
		float ysin1 = (y1 - yp) * sinrot;
		float xcos2 = (x2 - xp) * cosrot;
		float xsin2 = (x2 - xp) * sinrot;
		float ycos2 = (y2 - yp) * cosrot;
		float ysin2 = (y2 - yp) * sinrot;
			
		v[0].x = COORDTO3DX( xcos1 - ysin2 + xp, ResWidth );
		v[0].y = COORDTO3DY( xsin1 + ycos2 + yp, ResHeight );
		v[1].x = COORDTO3DX( xcos1 - ysin1 + xp, ResWidth );
		v[1].y = COORDTO3DY( xsin1 + ycos1 + yp, ResHeight );
		v[2].x = COORDTO3DX( xcos2 - ysin2 + xp, ResWidth );
		v[2].y = COORDTO3DY( xsin2 + ycos2 + yp, ResHeight );
		v[3].x = COORDTO3DX( xcos2 - ysin1 + xp, ResWidth );
		v[3].y = COORDTO3DY( xsin2 + ycos1 + yp, ResHeight );

		CacheVertices2D(v);
	}
	void Graphics::DrawSpriteRotation(const GraphicID id, const short x, const short y, const short width, const short height, const short srcx, const short srcy, const short xpivot, const short ypivot, const float rotx, const float roty, const float rotz)
	{
		if (rotx == 0 && roty == 0)
		{
			if (rotz == 0)
			{
				DrawSprite(id, x, y, width, height, srcx, srcy);
			}
			else
			{
				DrawSpriteRotated(id, x, y, width, height, srcx, srcy, xpivot, ypivot, rotz);
			}
		}
		else
		{
			if (rotz == 0)
			{
				float cosrotX = Math::Cosf(rotx);
				float cosrotY = Math::Cosf(roty);

				DrawSpriteScaled(id, (short)(cosrotX * -xpivot + x + xpivot), (short)(cosrotY * -ypivot + y + ypivot),
					(short)(cosrotX * width), (short)(cosrotY * height), srcx, srcy, width, height);
			}
			else
			{
				DrawSpriteComplete(id, x, y, width, height, srcx, srcy, width, height, xpivot, ypivot, rotx, roty, rotz, 0xFFFFFFFF);
			}
		}
	}
	void Graphics::DrawSpriteComplete(const GraphicID id, const short dstx, const short dsty, const short dstw, const short dsth,
		const short srcx, const short srcy, const short srcw, const short srch, const short pivotx, const short privoty,
		const float rotx, const float roty, const float rotz, const u32 color)
	{

	}


	/////////////////////////////////////////////
	// Gestione palette
	void Graphics::SelectPalette(const u8 index)
	{
		selectedPalette = (float)index / 256.0f/* + ( 1.0f / 512.0f )*/;
	}
	u32* Graphics::GetPalette(u16 x, u16 y)
	{
		return &(((u32*)clutZone)[x + y * 256]);
	}
	void Graphics::RefreshPalette()
	{
		Video::UploadTexture(texturePalette, 256, 256, PixelFormat_RGBA8888, clutZone);
		Video::SelectPalette(texturePalette);
	}


	/////////////////////////////////////////////
	// Gestione textures
	
	size_t Graphics::GenerateTextures(u16 width, u16 height, u32 count)
	{
		if (count >= GraphicSurfacesMaxCount)
			return 0;
		// PSEUDOCODE
		for(u32 i = 0; i < count; i++)
		{
			// Video::CreateTexture(TexBox[i], width, height, format A8);
		}
		return width * height * count;
	}
	Graphics::GraphicID Graphics::AddImage(const char* filename)
	{
		Hash hash = String(filename).GetHash();
		if (hash != 0)
		{
			for(GraphicID i = 0; i < GraphicSurfacesMaxCount; i++)
			{
				if (gfxSurface[i].hash != 0)
				{
					/*if (gfxSurface[i].hash == hash)
					{
						return i;
					}*/
				}
				else
				{
					Image* image = new Image(filename);
					if (CheckImageSize(image->GetWidth()) == false ||
						CheckImageSize(image->GetHeight()) == false)
					{
						delete image;
						return -1;
					}
					gfxSurface[i].image = image;
					gfxSurface[i].hash = hash;
					gfxSurface[i].width = image->GetWidth();
					gfxSurface[i].height = image->GetHeight();
					gfxSurface[i].y = -1;
					return i;
				}
			}
		}
		return ImageNull;
	}
	void Graphics::RemoveImage(const char* filename)
	{
		Hash hash = String(filename).GetHash();
		for(GraphicID i = 0; i < GraphicSurfacesMaxCount; i++)
		{
			if (gfxSurface[i].hash == hash)
			{
				RemoveImageFromID(i);
				return;
			}
		}
	}
	void Graphics::RemoveImageFromID(GraphicID id)
	{
		if (id == ImageNull)
			return;
		delete gfxSurface[id].image;
		gfxSurface[id].hash = 0;
	}
	bool Graphics::CheckImageSize(u16 size)
	{
		for(u16 i = 16; i <= 1024; i = i << 1)
		{
			if (i == size)
				return true;
		}
		return false;
	}
	void Graphics::SortImages()
	{
		/* Questo algoritmo consente di riordinare in modo efficiente le textures del gioco in una texture atlas.
		 * === Descrizione variabili
		 * > MaxTexturesPerAtlas contiene il numero massimo di textures disponibili per ogni Atlas.
		 * > order è un array di dimensione N textures (numero texture massime) che contiene gli indici in base
		 * all'ordine di grandezza delle varie superfici.
		 * > index contiene l'indice corrente delle superfici ordinate ed anche il numero di superfici valide trovate.
		 * === Descrizione funzionalità
		 * Il primo ciclo invalida la posizione X ed Y di tutte le superfici.
		 * Il secondo ciclo riordina le superfici dalla grandezza più grande a quella più piccola, riempendo
		 * l'array order.
		 * Il terzo ciclo assegna la posizione delle superfici nel corretto ordine.
		 */

		u16 index = 0;
		u16 order[GraphicSurfacesMaxCount];

		for(u16 i = 0; i < GraphicSurfacesMaxCount; i++)
		{
			gfxSurface[i].x = -1;
			gfxSurface[i].y = 0;
		}
		for(u16 i = 0; i < GraphicSurfacesMaxCount; i++)
		{
			u16 biggerSurfaceIndex = GraphicSurfacesMaxCount;
			u16 biggerSurfaceSize = 0;

			for (u16 j = 0; j < GraphicSurfacesMaxCount; j++)
			{
				if ( (gfxSurface[j].hash != 0) && (gfxSurface[j].x == (u16)-1) )
				{
					if ( gfxSurface[j].width + gfxSurface[j].height > biggerSurfaceSize )
					{
						biggerSurfaceIndex = j;
						biggerSurfaceSize = gfxSurface[j].width + gfxSurface[j].height;
					}
				}
			}

			if ( biggerSurfaceIndex != GraphicSurfacesMaxCount )
			{
				gfxSurface[biggerSurfaceIndex].x = 0;
				order[index++] = biggerSurfaceIndex;
			}
			else
			{
				// All the surfaces was analyzed.
				i = GraphicSurfacesMaxCount;
				continue;
			}
		}
		if (index == 0)
			return;

		gfxSurface[order[0]].x = 0;
		gfxSurface[order[0]].y = 0;

		for(u16 i = 1; i < index; i++)
		{
			u16 currentSurface = order[i];

			gfxSurface[currentSurface].y = 0;

			int loop = 0;
			while(loop == 0)
			{
				loop = 1;

				for(u16 j = 0; j < GraphicSurfacesMaxCount; j++)
				{
					if ((((gfxSurface[j].x > -1) && (j != currentSurface)) && ((gfxSurface[currentSurface].x < (gfxSurface[j].x + gfxSurface[j].width)) && (gfxSurface[currentSurface].x >= gfxSurface[j].x))) && (gfxSurface[currentSurface].y < (gfxSurface[j].y + gfxSurface[j].height)))
					{
						loop = 0;
						gfxSurface[currentSurface].x += gfxSurface[currentSurface].width;
						if ((gfxSurface[currentSurface].x + gfxSurface[currentSurface].width) > 1024)
						{
							gfxSurface[currentSurface].x = 0;
							gfxSurface[currentSurface].y += gfxSurface[currentSurface].height;
						}
						j = GraphicSurfacesMaxCount;
					}
					continue;
				}
				continue;
			}
			continue;
		}
		return;
	}
	void Graphics::UploadImages()
	{
		int i = 0;
		while(gfxSurface[i].hash != 0)
		{
			Image* image = gfxSurface[i].image;
			u16 width = gfxSurface[i].width;
			u16 height = gfxSurface[i].height;

			char* buf = (char*)TexBoxBuffer + (gfxSurface[i].x + (gfxSurface[i].y * TextureBufferHeight)) * TextureBufferBPP;
			for(int j = 0; j < height; j++)
			{
				image->Read(buf, width * TextureBufferBPP);
				buf = buf + 1024 * TextureBufferBPP;
			}
			image->Rewind();
			i++;
		}

		Image debug;
		debug.Create("debug.gfx", 1024, 1024, TextureBufferBPP == 4 ? PixelFormat_RGBA8888 : PixelFormat_A8);
		debug.Write(TexBoxBuffer, 1024 * TextureBufferHeight * TexBoxResolution * TextureBufferBPP);
		if (Video::UploadTexture(TexBox[0], 1024, 1024, TextureBufferBPP == 4 ? PixelFormat_RGBA8888 : PixelFormat_A8, TexBoxBuffer) == false)
			con.Log(DEBUG_LEVEL_WARNING, "Video::UploadTexture failed");
	}
}