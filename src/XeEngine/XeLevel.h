#pragma once
#include "XeBase.h"
#include "XeEngineLV1.h"
#include "XeTexture.h"
#include "XeFormats.h"
#include "XeAnimation.h"

/*
256x192 16x12	16:12	192 tiles	NDS		Castlevania DOS,POR,OOE
256x224 16x14	16:14	224 tiles	SNES	Castlevania IV,ROB,SOTN
320x240 20x15	16:12	300 tiles	GENESIS	Sonic 1, 2, 3K, CD
400x256 25x16	25:16	400 tiles	MULTI	Sonic CD 2011
*/
/*
Depths:
-2.0 = Wall layer
-1.0 = Back layer
-0.5 = Object back layer
0.0  = Level layer
0.5  = Object layer
1.0  = Level layer with depth+1
1.5  = Object front layer
2.0  = Front layer
*/

/* Documentazione e specifiche (BETA) dello XeEngine
	Ogni livello è un file.
	In un livello è possibile trovare il nome del livello (tipo Green Hill, Ruined Corridors ecc),
	il numero di texture, palette, blocchi, mappe, layers.
	=== TEXTURE ===
	Una texture è un'immagine 128x128 o 256x256 nella versione 1x e 256x256 o 512x512 nella versione 2x;
	una texture inoltre è di 4 bit di profondità, ovvero che ad ogni due pixel corrisponde un byte.
	Ogni texture contiene 256 tiles, di cui il primo è solitamente vuoto. Un tile è un'immagine di 16x16.
	Il massimo numero di texture per mappa è 8. Il massimo numero di tiles per mappa è quindi 2048.
	In Sonic the Hedgehog e Megaman X il massimo numero di tiles è 1024 e in SOTN è 2048.
	=== PALETTE ===
	La palette è una tavolozza di 256 colori totali che da colore ai tiles.
	Una palette può essere dinamica, quindi se cambia un singolo colore della palette, cambieranno
	colore anche tutti i tile che la useranno in quel momento. Questo processo si chiama palette animation.
	Solitamente il primo colore di una singola palette rappresenta la trasparenza, quindi questo fa scendere
	il numero di colori utilizzati per tile da 256 a 255.
	Ogni livello ha in totale 256 palette, con un totale di 65536 colori differenti possibili per livello.
	L'insieme di tutte e 256 le palette si chiama CLUT (Colour look-up table).
	Una palette pesa 1KB ed una CLUT pesa 256KB.
	Esiste la CLUT del livello e la CLUT condivisa. Questo alza il numero di colori differenti sino a 131.072
	=== BLOCKS ===
	Un blocco è un'immagine 128x128 che è composta da 64 tiles (8 in altezza ed 8 in larghezza).
	Ogni tile selezionato nel blocco può avere diverse proprietà:
	 - Il tile da selezionare nella singola texture. Il valore varia da 0 a 255.
	 - La texture da selezionare. Il valore varia da 0 a 15.
	 - Effetto profondità. La tile può essere avanti o dietro il layer Object.
	 - CollideLR. La collisione funziona anche ai lati del tile.
	 - CollideD. La collisione funziona anche nel lato basso del tile.
	 - Effetto flip e/o mirror
	 - Palette da selezionare. Il valore varia da 0 a 255.
	 - Collisione da selezionare. Il valore varia da 0 a 255.
	La dimensione di un singolo blocco è 256 byte. Il numero massimo di blocchi è 65536.
	In Sonic the Hedgehog ci sono massimo 256 blocchi, in Megaman massimo 65536.
	Castlevania non sfrutta i blocchi data la dimensione di ogni singola stanza.
	=== MAPPE ===
	Una mappa è un pezzo del singolo livello.
	Una mappa può avere una posizione (deve pur essere localizzata da qualche parte nella mappa),
	e una dimensione in altezza e larghezza. Questi 4 elementi vengono moltiplicati per 256.
	La dimensione minima di una mappa è 256x256, la massima è di 65536x65536.
	Ogni mappa ha anche un identificativo che varia da 0 a 255. In Sonic the Hedgehog questo può
	essere usato come valore di ACT, ovvero l'atto attuale del singolo stage.
	Ogni mappa può avere sino a 4 layer differenti. (Megaman ZX ha 4 layer).
	I singoli oggetti possono essere posizionati su layer differenti ed ognuno segue le collisioni
	in base al layer presente. (Un effetto del genere è possibile vederlo in White Park 2 di Sonic 4).
	Nota molto importante è che diverse mappe possono utilizzare lo stesso layer.
	=== LAYER ===
	Un layer è come un foglio che può essere posto sopra o sotto altri layer che insieme
	formano il livello vero e proprio. I vari layer si possono muovere a velocità diverse,
	per dare l'effetto Parallax Scrolling.
	Ogni layer ha una dimensione propria. Per esempio se si vuole avere un layer che segue
	il giocatore e uno sfondo fisso, il layer di sfondo avrà dimensione 1x1 e la sua velocità X
	ed Y sarà pari a 0.
	I parametri possono essere vari:
	Velocità X ed Y. Può essere positiva o negativa. La posizione del layer è data dal prodotto
	della telecamera che segue il giocatore	correntecon la velocità di scrolling del singolo layer. 
	Si può scegliere se ogni layer può sfruttare le collisioni (per esempio i layer di sfondo
	non avranno mai collisioni e quindi non saranno minimamente processati) e se quel layer
	usa la palette condivisa (Castlevania fa uso delle palette condivise tipo nelle stanze di salvataggio).

	/=/=/=/ FORMATO DEL FILE /=/=/=/
	LevelProperties
	MapProperties, LevelProperties.mapCount
	BlockDefinition, LevelProperties.blockCount
	LayerProperties, LevelProperties.layersCount
	ClutDefinition, LevelProperties.paletteCount
	TextureDefinition, LevelProperties.textureCount
*/

#define PATH_LEVEL	"LEVEL"

#define TEXTURE_TILE_WIDTH	16
#define TEXTURE_TILE_HEIGHT	16
#define TEXTURE_COUNT		8
#define TILE_COUNT			(TEXTURE_TILE_WIDTH*TEXTURE_TILE_HEIGHT) * (TEXTURE_COUNT)

#define COLOR_DEPTH			32
#define PALETTE_COLORS		256
#define PALETTE_SIZE		(PALETTE_COLORS) * (COLOR_DEPTH) / 8
#define PALETTE_COUNT		256
#define PALETTESET_SIZE		(PALETTE_SIZE) * (PALETTE_COUNT)
#define CLUT_COUNT			4

#define OBJECT_LISTSIZE		1024
#define OBJECT_COUNT		512

typedef int				PFloat; // Pseudofloat
typedef unsigned int	Color;
typedef Color			Palette[PALETTE_COLORS];
typedef char			Collision[0x10];

#define R8G8B8A8_TO_R5G6B5(c) ( (((c)>>3)&0x1F) | (((c)>>5)&0x7E0) | (((c)>>8)&0xF800) )
#define R5G6B5_TO_R8G8B8A8(c) ( ((c&0x1F)<<3) |  ((c&0x7E0)<<5) |  ((c&0xF800)<<8) | 0xFF000000 )
#define R5G5B5A1_TO_R8G8B8A8(c) ( ((c&0x1F)<<3) |  ((c&0x3E0)<<6) |  ((c&0x7C00)<<9) | ((c&0x8000) ? 0xFF000000 : 0))

enum STAGEFILE
{
	STAGEFILE_GFX,	// Grafica
	STAGEFILE_LUT,	// Palette
	STAGEFILE_CLI,	// Indici delle collisioni
	STAGEFILE_HBX,	// Collisioni
	STAGEFILE_MAP,	// Mappa
	STAGEFILE_BLK,	// Chunk
	STAGEFILE_RNG,	// Disposizione dei ring
	STAGEFILE_OBP,	// Disposizione degli oggetti
	STAGEFILE_DEF,	// Deformazione dei layer
	STAGEFILE_DTL,	// Tile dinamiche
	STAGEFILE_DPL,	// Palette dinamiche
	STAGEFILE_CRD,	// Custom tile card
	STAGEFILE_BGM,	// Musica
};

struct TileEntry
{
	union
	{
		unsigned short Tile;
		struct
		{
			unsigned char tile;			// Tile da selezionare nella texture. Ci sono 256 tiles per texture
			unsigned char texture;		// Texture da selezionare. Ci sono in totale 256 texture, per un totale di 65536 tiles differenti
		};
	};
	unsigned char palette;			// 256 palette, per un totale di 4096 colori differenti. Si può scegliere tra i clut della mappa e i clut condivisi, per un totale di 512 clut.

	unsigned char depth		: 1;	// Se sopra o sotto il layer object
	unsigned char flip		: 1;	// Tile vista al contrario
	unsigned char mirror	: 1;	// Tile vista a specchio
	unsigned char unknow    : 1;
	unsigned char path1		: 2;
	unsigned char path2		: 2;

	unsigned int ToInt()
	{
		return *(unsigned int*)this;
	}
};
struct LevelProperties
{
	char name[0x20];				// Nome del livello
	unsigned char mapCount;			// Quantità di mappe
	unsigned char paletteCount;		// Quantità di palette
	unsigned char textureCount;		// Quantità di texture
	unsigned char padding23;
	unsigned short blockCount;		// Quantità di blocchi
	unsigned short layersCount;		// Quantità di layers
};
struct MapCallLayer
{
	unsigned short index;
	unsigned short priority;
};
struct ObjectLayout
{
	short x, y;
	ushort id;
	byte subid;
	byte flip		: 1;
	byte mirror		: 1;
	byte ignorex	: 1;
	byte ignorey	: 1;
	byte padding	: 4;
};
struct ObjectContainer
{
	byte filled;			// Indica se l'oggetto non è allocato o meno
	byte palette;			// Indica quale palette è occupata dall'oggetto corrente
	byte clut;				// Indica quale CLUT è occupata dall'oggetto corrente
	byte dummy;				// WTF
	short id;				// ID dell'oggetto
	u16 lru;				// Vede l'ultima volta che questo oggetto è stato utilizzato, utile per la deallocazione dinamica
	XeTexture texture;		// Contiene la texture di un oggetto
	XeAnimation animation;	// Contiene l'animazione di un oggetto
};
struct ObjectList
{
	ushort id;
	char name[0xE];
};
struct LevelRect
{
	short left, right, top, bottom;
	void Zero()
	{
		*((long long*)this) = 0;
	}
};
struct StageAct
{
	char *gfx;
	char *clut;
	char *cli;
	char *hbx;
	char *map;
	char *blk;
	char *rng;
	char *obp;
	char *def;
	char *dtl;
	char *tpl;
	char *crd;
	char *bgm;
};
struct Stage
{
	XeEngine::Memory mem;
	unsigned char resolution;
	unsigned char actcount;
	unsigned char hidetilecard;

	char *suffix;
	char *name;
	StageAct *act;

	void Zero()
	{
		resolution = 0;
		actcount = 0;
		hidetilecard = 0;
		suffix = 0;
		name = 0;
		act = 0;
	}
};


typedef TileEntry		Block[8*8];

class XeObject;
class XeLevel
{
private:
	byte _mapSelected;
	void _internal_LoadLUT(LUT *lut, Palette *pal);
protected:
	char pathcache[0x40];
public:
	// Resolution
	short resWidth;					// Risoluzione orizzontale del gioco
	short resHeight;				// Risoluzione verticale del gioco
	short chunkWidth;				// Risoluzione orizzontale del gioco espressa in chunk
	short chunkHeight;				// Risoluzione verticale del gioco espressa in chunk
	byte depthResolution;			// Profondità di risoluzione delle texture di gioco

	// Camera
	PFloat cameraX;					// Camera X del gioco
	PFloat cameraY;					// Camera Y del gioco
	LevelRect border;				// Bordi di default del livello
	LevelRect borderLock;			// Bordi di blocco del livello. Hanno una priorità maggiore di border
	XeObject *mainobject;			// L'oggetto di gioco dove verrà attaccata la telecamera

	// Tiling
	XeEngine::Memory memTileCache;			// Cache delle tiles
	TileEntry *tilecache;			// Puntatore a memTileCache

	// Stage
	char path[0x40];
	byte currentAct;
	Stage stage;					// Struttura che contiene tutto ciò che ha a che fare con lo stage ed i nomi dei file
	XeTexture texture;				// Texture contenente i tile del livello. Teoricamente non ha limite di dimensioni, ma si consiglia una risoluzione massima di 256x256x8
	Palette palette[CLUT_COUNT][PALETTE_COUNT];	// Palette del livello. 0 = shared, 1 = level, 2/3 = objects. Può essere usata per immagini a 4bpp (emulate) o ad 8bpp
	Block chunk[0x1000];				// Blocchi da 128x128 del livello. Sono formati da 64 tile e forniscono ad esse diverse impostazioni come priorità, palette ecc.
	Collision collision[0x200];		// Collisioni vere e proprie del livello. Sono 256 collisioni diverse, le seconde 256 sono le prime usate per le collisioni a muro
	byte collisionAngle[0x100];		// di collision[], qui ne vengono descritte le pendenze in formato 8-bit.
	byte collisionIndex[2][2048];	// Associa ad ogni tile del livello l'indirizzo verso la collisione. Questa funzionalità fornisce il path swapping.
	DTL dynamicTiles;				// Meccanismo che fornisce il supporto alle tile dinamiche, a che velocità devono essere eseguite ed altro
	OBP objectPlacement;			// Contiene i respawn di tutti gli oggetti.

	// Other stuff
	bool stagestarted;
	bool pause;
	int timelevel;
public:
	LevelProperties level;					// Proprietà del livello
	MAP map;								// Proprietà delle mappe associate al livello
	ObjectContainer objcont[OBJECT_COUNT];	// Contenitore degli oggetti
	ObjectList objlist[OBJECT_LISTSIZE];
	XeObject *object[OBJECT_COUNT];
public:
	XeLevel();
	~XeLevel();

	//////////////////////////////////////////////////////////////////////////
	//// XeLevelIO.cpp
	// Carica un file .STG che contiene le informazioni di un singolo livello
	void LoadStage(char *filename);
	// Carica i singoli elementi dello stage
	void LoadStageElements();
	// Carica la grafica del livello (GFX e DTL) in base alla risoluzione impostata
	void LoadGFXResolution();
	// Ottiene il percorso di un determinato file
	char *MakePath(int act, STAGEFILE file);

	void LoadLevelGFX(GFX*);
	void LoadLevelLUT(LUT*);
	void LoadSharedLUT(LUT*);
	void LoadLevelBLK(BLK*);
	void LoadLevelHBX(HBX*);
	void LoadLevelCLI(CLI *cli);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// XeLevelObject.cpp
	char LoadObject(ushort id);
	ObjectContainer *SelectObject(ushort id);
	void AttachEntity(XeObject*);
	XeObject *GetAttachedObject();
	void UpdateCamera();
	void LockCamera();
	void UnlockCamera();
	void PlaceObjects();
	void DestroyObject(XeObject*);

	// Funzioni generiche della telecamera del livello
	int GetResolution();
	void SetResolution(short width, short height);
	byte GetDepthResolution();
	void SetDepthResolution(byte depthResolution);
	// Funzioni generiche del livello
	char *GetLevelName();
	byte GetMapSelected();
	void SetMapSelected(byte);
	byte GetMapCount();
	void ResetLevel();
	void StartStage();
	// Altro
	TileEntry GetBlock(short x, short y, byte levelWidth, byte levelHeight, short *layer);
	TileEntry GetBlock(short x, short y);
	short GetBlockIndex(short x, short y);
	byte GetCollisionIndex(short x, short y);
	void GetCollision(Collision **collision, short tilex, short tiley);
	// Funzioni di disegno
	void DrawLevel();
	void DrawLayer(int layer);
};