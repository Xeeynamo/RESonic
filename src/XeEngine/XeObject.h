#pragma once
#include "XeBase.h"
#include "XeEntity.h"
#include "XeObjectAnimation.h"
#include "XeObjectDef.h"

struct HoldPlayer
{
	int score;
	ushort ring;
	ushort lifes;
};
struct HoldRpg
{
	int maxHP, curHP;
	int maxMP, curMP;
	byte atk, def;
	byte mag, spr;
};

class XeLevel;
class XeObject : public XeEntity
{
private:
	XeLevel *level;
	char buffer[0x100];		// Usato per raccogliere informazioni sulle collisioni
public:
	ushort id;
	ushort animID;			// ID animazione
	KeyInput keys;			// Codice input
	KeyInput prevkeys;		// Codice input della chiamata precedente
	int routineStatus;

	// Variabili usate per la fisica. Esse differiscono per ogni oggetto presente nel gioco
	PFloat acceleration;	// Velocità di accelerazione, utile in giochi come Sonic. Se acceleration = maxspeed, si ottiene l'effetto come in Megaman e Castlevania
	PFloat deceleration;	// Velocità di decelerazione, utile in giochi come Sonic. Se posto a 0, si ottiene l'effetto come in Megaman e Castlevania
	PFloat friction;		// Attrito sul terreno. Utile per i giochi che sfruttano l'accelerazione. Può essere usato anche per l'effetto ghiaccio.
	PFloat minspeed;		// Velocità minima. Utile quando un personaggio non può smettere di correre (boss di Sonic Advance 2)
	PFloat maxspeed;		// Velocità massima. Oltre questa velocità, il personaggio non può andare.
	PFloat turning;			// Velocità di spostamento del personaggio da sinistra verso destra o viceversa
	PFloat gravity;			// Forza di gravità. Più è alto questo valore, più l'oggetto è pesante.
	PFloat maxgravity;		// Come nel mondo reale, un oggetto può cadere sino ad un tot di velocità massima. In Sonic questa variabile non è controllata.
	PFloat jump;			// Salto di un oggetto.
	PFloat jumpmin;			// Indica la forza del salto, necessaria per una spinta.
	PFloat airaccmin;		// Velocità minima necessaria per una spinta quando si è in aria per avere una accelerazione doppia.
	PFloat brake;			// Forza della frenata
	PFloat ducking;			// Veloctà minima per entrare in duck
	
	// Variabili interne usate per la fisica
	PFloat inertia;			// Velocità corrente
	PFloat prevx, prevy;	// X ed Y precedenti
	PFloat speedx, speedy;	// Velocità derivate da inertia in base all'angolo

	bool path;				// Percorso corrente
	char angle;				// Angolo del personaggio
	char outangle;			// Angolo in uscita usato da FindFloor/FindWall
	char slope_movelock;	// Blocca i movimenti in SlopeRepel


	ObjectHitboxRect collision;

	union
	{
		unsigned int status;
		struct
		{
			unsigned int verse			: 1;	// Quando l'oggetto guarda a sinistra
			unsigned int air			: 1;	// Quando l'oggetto è in aria
			unsigned int rolling		: 1;	// L'oggetto rotola
			unsigned int onobject		: 1;	// Quando l'oggetto è sopra un altro oggetto
			unsigned int jump			: 1;	// Quando il salto è stato eseguito
			unsigned int pushing		: 1;	// L'oggetto cerca di spostare qualcosa
			unsigned int duck			: 1;	// L'oggetto è abbassato
			unsigned int underwater		: 1;	// Quando l'oggetto è sott'acqua
			unsigned int graverse		: 1;	// Verso della gravità

			unsigned int ledge			: 1;	// L'oggetto è in bilico
			unsigned int spindash		: 1;	// Quando l'oggetto è in fase di dashing
			unsigned int controllocked	: 1;	// Controlli bloccati
			unsigned int outofscreen	: 1;	// Quando il personaggio va fuori lo schermo
			unsigned int died			: 1;	// Quando il player è "morto"
			unsigned int gone			: 1;	// L'oggetto è scomparso dal livello.
		} Status;
	};
	bool animspeed_mod;
	byte animspeed;
	short spindash_speed;
	char jumpallowed;		// Imposta quanti salti in aria può eseguire l'oggetto. Solitamente sono 1 o 2
	char jumpcounter;		// Imposta il numero di salti possibili. Ogni volta che il giocatore salta, questo viene decrementato
	char collisions;		// Collisioni avvenute

	HoldPlayer *holdPlayer;
	HoldRpg *holdRpg;
public:
	XeObjectAnimation Animation;

	XeObject(ushort id);
	~XeObject();

	// Imposta il livello nell'oggetto. Un oggetto teoricamente non può esistere senza livello.
	void AttachLevel(XeLevel*);
	// Ottiene il livello corrente associato all'oggetto
	XeLevel *GetLevel() const;
	// Cancella l'oggetto corrente dal livello
	void DeleteMeFromLevel();
	// Comunica al livello che è l'entità corrente a prendere il controllo del livello. Può farlo solo un oggetto alla volta
	void TakeLevelControl();
	// Ottiene l'ID del livello
	ushort GetID() const;

	// Controllo dell'oggetto
	void Input(KeyInput keys);		// Input dei tasti
	virtual void Do();				// Routine principale
	virtual void Draw();			// Disegna l'oggetto
	virtual void CollisionObject(XeObject *o);
	virtual void AnimationHandler();// Qui vengono gestite tutte le animazioni di default del gioco

	// Funzioni
	short CalcSin(unsigned char angle);
	short CalcCos(unsigned char angle);
	char CalcAngle(short x, short y);
	void RefreshAngle(char newangle);

	// Fisica
	virtual void Friction();		// Rallenta l'oggetto fino a fermarlo, agendo sulla variabile inertia. Non funziona se inertia è uguale a minspeed.
	virtual void Fall();			// Fa cadere un oggetto. Agisce grazie a gravity. Non funziona se Status.air == 0.
	virtual void CalcSpeed();		// Calcola speedx e speedy in base ad inertia ed angle.
	virtual void Move();			// Muove il personaggio in base a speedx e speedy.
	virtual void SlopeResist();		// Rallenta o velocizza il personaggio in base a salite o discese.
	virtual void SlopeRepel();		// Fa scivolare un personaggio sulle salite troppo ripide.
	virtual void ResetOnFloor();	// Resetta alcuni parametri se l'oggetto collide col terreno
	virtual void JumpHeight();		// Controlla la forza del salto
	virtual void JumpControl();		// Controllo del salto
	virtual void JumpDecelerate();	// Decelerazione di speedx durante il salto
	virtual void JumpAngle();		// Riposizionamento durante il salto
	virtual void WalkHD();			// Horizontal Down
	virtual void WalkVR();			// Vertical Right
	virtual void WalkHU();			// Horizontal Up
	virtual void WalkVL();			// Vertical Left

	// Azioni
	virtual void MoveLeft();		// Muove l'oggetto verso sinistra.
	virtual void MoveRight();		// Muove l'oggetto verso destra.
	virtual bool Jump();			// Fa saltare l'oggetto
	virtual void LookDown();		// Quando l'oggetto è rivolto verso il basso
	virtual void LookUp();			// Quando l'ogetto è rivolto verso l'alto
	virtual bool SpinDash();		// Quando l'oggetto è in dashing
	virtual void Kill();						// Uccide l'oggetto

	// Collisioni
	virtual void SwitchCollision(ObjectHitboxRect*);
	virtual bool Collide(XeObject*);
	virtual void Border();			// Resetta la posizione del personaggio in base ai bordi del livello.
	char FindFloor(PFloat x, PFloat y, char flip = 0, bool verse = true);
	char FindFloor2(short x, short y, char flip = 0, bool verse = true);
	char FindWall(PFloat x, PFloat y, char mirror = 0, bool verse = true);
	char FindWall2(short x, short y, char mirror = 0, bool verse = true);

	char CheckFloor();			// Distanza tra il personaggio ed il pavimento (0°)
	char CheckRightFloor();		// Distanza tra il personaggio ed il pavimento (90°)
	char CheckLeftFloor();		// Distanza tra il personaggio ed il pavimento (270°)
	char CheckCeiling();		// Distanza tra il personaggio ed il soffitto
	char CheckLeftCeiling();	// Distanza tra il personaggio ed il soffitto (90°)
	char CheckRightCeiling();	// Distanza tra il personaggio ed il soffitto (270°)

	char CheckLeftWall();		// Distanza tra il personaggio ed il muro di sinistra
	char CheckRightWall();		// Distanza tra il personaggio ed il muro di destra
	void CheckWallsOnGround();	// Distanza tra il personaggio ed il muro (ALL°)

	char CalcRoomInFront(char angle);
	char CalcRoomOverHead(char angle);
	char CheckSlopeDist();

	// Fisica dell'oggetto
	virtual void AngleMove();					// Controlla le collisioni
	virtual void DoCollision();

	// Runtimes
	virtual void RuntimeDo();
	virtual void RuntimeCreated();
	virtual void RuntimeDestroyed();
	virtual void RuntimeVisible();
	virtual void RuntimeLost();
	virtual void RuntimeCollisionField(int collision);
	virtual void RuntimeCollisionObject(XeObject*);
};