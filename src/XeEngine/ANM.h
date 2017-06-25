#pragma once
#include "XeEngineLV1.h"

struct ANMHeader
{
	byte anims;		// Numero di animazioni presenti nel file
	byte type;		// 0 palette, > 0 tile
	short count;	// Elementi presenti
};
struct ANMAnimation
{
	byte speed;		// Velocità di animazione
	byte index;		// Indice. Viene incrementato di 1 quando speed viene soddisfatto. Al caricamento del file questo è 0
	byte frames;	// Quantità di fotogrammi. Quando index è >= di frames, index viene posto a 0
	byte stride;	// Distanza tra un elemento e l'altro
	short source	: 10;	// Indice sorgente dei dati. Massimo 1024
	short size		: 6;	// Grandezza degli elementi da catturare. Massimo 64
	byte destindex;	// Palette o texture di destinazione
	byte destpos;	// Colore o tile di destinazione
};

class ANM
{
private:
protected:
	XeEngine::Memory data;
	ANMHeader *header;
	ANMAnimation *anim;
	void *vdata;
public:
	ANM();
	~ANM();

	bool Load(char *filename);
	// Esegue l'animazione e copia il risultato nella palette
	void Tick(void*);
	// Esegue l'animazione
	void Tick();
	// Esegue solo un'animazione specifica
	void Tick(int animationindex);
	// Copia il risultato nella palette
	void Copy(void*);
	// Copia il risultato di un'animazione specifica nella palette
	void Copy(int animationindex, void*);
};