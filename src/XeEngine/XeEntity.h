#pragma once
#include "XeBase.h"

#define XEENTITY_MAX_CHILDRENS 16

class XeLevel;
class XeTexture;
class GFX;
class XeEntity
{
private:
	bool texture_loaded_manually;
protected:
	XeTexture *tex;			// Texture dell'entità
	XeLevel *level;			// Puntatore al livello. Utile per conoscere i punti di collisione ed altre informazioni
	// La posizione virtuale Z. Rappresenta l'ordine in cui viene disegnato l'oggetto
	int zOrder;
	// Numero di oggetti figlio
	int nChildren;
	// L'array di puntatori verso gli oggetti figlio
	XeEntity *children[XEENTITY_MAX_CHILDRENS];
	// Puntatore all'oggetto padre
	XeEntity *parent;
	// Il tag che rappresenta l'oggetto corrente
	int tag;
	// E' visibile
	bool isVisible;
public:
	// Angolo di rotazione
	float rotation;
	// Scaling
	float scaleX, scaleY;
	// Posizione dell'oggetto
	PFloat x, y;
	float z;
	// Grandezza dell'oggetto
	short sizeWidth, sizeHeight;
	// Centro dell'oggetto
	short centerX, centerY;
	// Filtro dei colori
	XeColorF colorfilter[5];
	// Velocità dell'effetto fade
	float fadeSpeed;
public:
	XeEntity();
	~XeEntity();
	// Ottiene tramite tag l'oggetto o uno dei sotto oggetti col tag corrispondente.
	XeEntity *GetEntity(int tag);
	void AddChildren(XeEntity*, int tag);
	void AddChildren(XeEntity*, int priority, int tag);
	void RemoveFromParent();
	void RemoveChildren(int tag, bool cleanup);
	// Gestione della stampa
	virtual void Draw(short depth = 0);
	// Gestione delle coordinate
	void SetPosition(short coordx, short coordy);
	void SetCenter(short x, short y);
	void SetScale(short width, short height);
	// Gestione delle texture
	void SetGFX(GFX *gfx);
	XeTexture *GetTexture();
	void SetTexture(XeTexture *texture);
};