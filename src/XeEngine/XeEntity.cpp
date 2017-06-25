#include "XeEntity.h"
#include "XeLevel.h"
#include "XeScene.h"
#include "XeTexture.h"
#include "GFX.h"

XeEntity::XeEntity()
{
	XeEngine::MemoryFill(this, sizeof(XeEntity));
	colorfilter[0].Identity();
	colorfilter[1].Identity();
	colorfilter[2].Identity();
	colorfilter[3].Identity();
	colorfilter[4].Identity();
	scaleX = scaleY = 1.0f;
	zOrder = XEENTITY_MAX_CHILDRENS / 2;					// Lo zOrder è al centro
	tag = -1;

	texture_loaded_manually = 0;
	tex = NULL;
}
XeEntity::~XeEntity()
{
	RemoveFromParent();										// Rimuore l'entità corrente dall'entità padre
	for(int i=0; i<XEENTITY_MAX_CHILDRENS; i++)				// Per ogni entità figlio
	{
		if (!children[i]) continue;							// Se l'entità figlio corrente è vuota, salta
		children[i]->parent = NULL;							// altrimenti setta il padre dell'entità figlio a NULL
	}
	if (texture_loaded_manually == false)
		SAFE_DELETE(tex);
}

XeEntity *XeEntity::GetEntity(int tag)
{
	if (this->tag == tag) return this;						// Se l'entità corrente ha il tag, ritorna se stessa
	for(int i=0; i<XEENTITY_MAX_CHILDRENS; i++)				// Per ogni entità figlio
	{
		if (children[i] != NULL)							// Inanzitutto vede se è nulla
		{
			if (children[i]->tag == tag)					// Se non lo è vede se il tag è quello selezionato
				return children[i];							// Se o è, torna quell'oggetto
		}
	}
	return NULL;											// Se non trova il tag, ritorna NULL
}
void XeEntity::AddChildren(XeEntity* o, int tag)
{
	AddChildren(o, zOrder-1, tag);							// Crea un figlio con la priorità z più bassa di this di default
}
void XeEntity::AddChildren(XeEntity* o, int priority, int tag)
{
	if (!o) return;											// Se non è specificato nessun oggetto, evita il crash
	for(int i=0; i<XEENTITY_MAX_CHILDRENS; i++)				// Per ogni oggetto figlio
	{
		if (!children[i])									// Se è vuoto
		{
			children[i] = o;								// allora eredita il figlio
			children[i]->parent = this;						// mette come padre se stesso al figlio
			return;											// Nothing's more to do :D
		}
		else if (children[i]->zOrder > priority)			// o.o
		{
			for(int j=XEENTITY_MAX_CHILDRENS-1; j>i; j--)
			{
				children[j] = children[j-1];
			}
			children[i] = o;
			children[i]->parent = this;
			return;
		}
	}
}
void XeEntity::RemoveFromParent()
{
	if (!parent) return;
	for(int i=0; i<XEENTITY_MAX_CHILDRENS; i++)
	{
		if (parent->children[i]->tag != this->tag) continue;
		parent->RemoveChildren(this->tag, false);
	}
}
void XeEntity::RemoveChildren(int tag, bool cleanup)
{
	for(int i=0; i<XEENTITY_MAX_CHILDRENS; i++)
	{
		if (!children[i]) continue;						// Se non esiste nessun altro elemento, continua {*esci direttamente*}
		if (children[i]->tag != tag) continue;			// Se l'elemento corrente non ha il tag selezionato, continua col ciclo for

		if (cleanup) delete children[i];				// Se il flag cleanup è selezionato, cancella l'oggetto figlio
		else children[i]->parent = NULL;				// Altrimenti lo dissocia semplicemente
		for(int j=i; j<XEENTITY_MAX_CHILDRENS-1; j++)	// Prende gli elementi che si trovano da adesso in poi
		{
			children[j] = children[j+1];				// E li sposta in una posizione indietro
		}
		children[XEENTITY_MAX_CHILDRENS-1] = NULL;		// L'ultimo elemento potrebbe rimanere pieno, quindi si azzera
		return;											// Non c'è niente più da fare, si può uscire senza problemi
	}
}

// Gestione della stampa
void XeEntity::Draw(short depth)
{
	PFloat screenWidth = level->resWidth<<16;
	PFloat screenHeight = level->resHeight<<16;
	PFloat levelWidth = level->map.Layer(0)->width<<24;
	PFloat levelHeight = level->map.Layer(0)->height<<24;

	XeScene::SetPosition(HIWORD(x), HIWORD(y), 0.0f);
	tex->Draw(0);
}
// Gestione delle coordinate
inline void XeEntity::SetPosition(short coordx, short coordy)
{
	x = coordx;
	y = coordy;
}
inline void XeEntity::SetCenter(short x, short y)
{
	centerX = x;
	centerY = y;
}
inline void XeEntity::SetScale(short width, short height)
{
	scaleX = (float)width / 32.0f;
	scaleY = (float)height / 32.0f;
}
// Gestione delle texture
void XeEntity::SetGFX(GFX *gfx)
{
	if (!gfx) return;
	if (texture_loaded_manually == true)
	{
		texture_loaded_manually = false;
		tex = NULL;
	}
	if (!tex) tex = new XeTexture;
	tex->Create(gfx);
}
XeTexture *XeEntity::GetTexture()
{
	return tex;
}
void XeEntity::SetTexture(XeTexture *texture)
{
	if (texture_loaded_manually == false)
	{
		SAFE_DELETE(tex);
		texture_loaded_manually = true;
	}
	tex = texture;
}