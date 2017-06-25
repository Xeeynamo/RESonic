#pragma once
#include "XeEngineLV1.h"
#include "XeFile.h"

struct OBPHeader
{
	ushort count;
	ushort dummy;
};
struct OBPEntry
{
	ushort x;
	ushort y;
	ushort width;	// realwidth/8, personalizza la larghezza di alcuni oggetti che consentono questa funzionalità (ponti, title card, ombre ecc)
	ushort height;
	ushort id;
	ushort subid;

	ushort unknow;
	union
	{
		struct 
		{
			ushort flipX	: 1;
			ushort flipY	: 1;
			ushort absolute	: 1;	// Coordinate assolute, indipendenti dalla telecamera (tipo l'HUD)
			ushort priority : 1;	// Davanti o dietro le tile con alta priorità nel mainLayer
			ushort visible	: 1;	// L'oggetto è visibile
			ushort respawn	: 1;	// L'oggetto è abilitato al respawn (MMX)
			ushort ignorex	: 1;	// Ignora la coordinata X della collisione (EOL Signpost). Ignora anche width.
			ushort ignorey	: 1;	// Ignora la coordinata Y della collisione (Water). Ignora anche height.
		};
		ushort flags;
	};
};
class OBP
{
private:
protected:
	ushort count;
	void *data;
	XeEngine::File file;
public:
	OBPHeader header;
	OBPEntry *entries;

	OBP();
	~OBP();

	bool Load(char *filename);
	bool Save(char *filename);
	ushort GetCount();
};