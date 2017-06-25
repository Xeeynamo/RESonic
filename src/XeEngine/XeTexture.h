#pragma once
#include "XeImage.h"
#define INVALID_TEXTURE 0xFFFFFFFF

enum
{
	XeVertexAttrib_Position,
	XeVertexAttrib_Color,
	XeVertexAttrib_Texture,

	XeVertexAttrib_MAX
};
enum
{
	XeVertexFlag_None		= 0,
	XeVertexFlag_Position	= 1 << 0,
	XeVertexFlag_Color		= 1 << 1,
	XeVertexFlag_Texture	= 1 << 2,
	
	XeVertexFlag_PosColorTex = (XeVertexFlag_Position | XeVertexFlag_Color | XeVertexFlag_Texture)
};
struct XeTexture_Vertex
{
	float x, y, z;
	float u, v, w;
	float r, g, b, a;
};

class XeTexture
{
protected:
	// ID della texture, assegnata automaticamente da GL
	unsigned int _id;
	// Larghezza, altezza e profondità della texture reale
	short width, height, depth;	
	// Larghezza ed altezza della texture reale espressa in floating point
	float vfWidth, vfHeight;
	// Formato della texture
	XeEngine::XeTexturePixelFormat format;

	char textureres;
	float depthf;
	float posx, posy, posz;

	// Cache
	float vertices[8];
	XeTexture_Vertex vertexblock[4];

	XeEngine::Memory vertexCache;		// Cache di memoria dove vengono memorizzati i vertici
	int cachestate;				// Stato della cache. 1 se la cache è pronta per ospitare nuovi dati, 0 se è stata svuotata o inutilizzata.
	int vertexwritten;			// Numero di vertici scritti
public:
	XeTexture();
	~XeTexture();
	
	// Crea una texture a partire da una classe XeImage.
	bool Create(XeEngine::XeImage*);

	// Crea una texture passando parametri grezzi.
	// Si consiglia dei valori di potenze di due in width ed height
	// data può essere null nel caso si vuole fare l'upload della texture in un secondo momento.
	bool Create(short width, short height, short depth, XeEngine::XeTexturePixelFormat format, void *data);
	
	// Distrugge la texture corrente. Dopo questa, tutte le altre operazioni divengono invalide.
	void Destroy();

	// Upload a portion of a texture
	void Upload(short dstx, short dsty, short width, short height, short dstz, short depth, void *data);

	// Ottiene l'ID della texture
	int GetID();

	// Ottiene la larghezza della texture reale
	short GetWidth();
	// Ottiene l'altezza della texture reale
	short GetHeight();
	// Ottiene la larghezza della texture reale
	short GetDepth();
	// Ottiene la larghezza della texture virtuale
	short GetVirtualWidth();
	// Ottiene l'altezza della texture virtuale
	short GetVirtualHeight();

	// Ottiene il valore della risoluzione della texture virtuale
	char GetResolution();
	// Imposta il valore della risoluzione della texture virtuale
	void SetResolution(int resolution);

	// Imposta la posizione della texture prima del rendering
	void SetPosition(short x, short y, float z);
	// Stampa l'intera texture nell'area indicata
	void Draw(short depth = 0);
	// Stampa una parte della texture.
	void Draw(short srcx, short srcy, short width, short height, short depth = 0, XeColorF *filter = NULL);

	void CacheStart(int vertexCount);
	void CacheEnd();
};