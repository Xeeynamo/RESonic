#pragma once
#include "XeAnimation.h"

class XeTexture;
class XeObjectAnimation
{
private:
protected:
	XeAnimation *animation;
	int wait;				// Attesa prima di avanzare verso il prossimo frame
	int frame;				// Frame corrente
	int animid;				// ID dell'animazione corrente
	int animindex;			// Indice dell'animazione corrente
	bool animover;			// Indica se l'animazione è finita o meno
	ObjectAnimation *anim;
	ObjectAnimationFrame *frames;
	ObjectFrame *framelist;
	XeObjectAnimation *child;

	ushort animqueue;

	bool lockedanimframe;
	ObjectAnimationFrame lockanimframe;
	byte lockanimspeed;
public:
	XeObjectAnimation();
	~XeObjectAnimation();

	bool IsCreated();
	void SetAnimation(XeAnimation*);					// Imposta un contenitore animazione
	void SetAnimationIndex(ushort index);				// Imposta l'ID dell'animazione
	void SetAnimationIndexQueue(ushort index);			// Imposta l'ID dell'animazione. Se c'è un'altra animazione da eseguite, la mette in coda.
	void CheckAnimQueue();
	bool IsAnimationOver();
	void LockAnimationFrame(ObjectAnimationFrame**);
	void UnlockAnimationFrame();
	void LockAnimationSpeed(int newspeed);
	void UnlockAnimationSpeed();
	void Do();											// Esegue la parte logica dell'animazione
	void Draw(XeTexture *texure, short x, short y, bool mirror = false, bool flip = false, float priority = 0.5f);
	XeRect GetRect();
};