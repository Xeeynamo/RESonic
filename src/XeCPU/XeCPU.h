#pragma once


class XeCPU
{
private:
public:
	struct OpCodeParam
	{
		union
		{
			unsigned char p;
			struct  
			{
				unsigned char type1		: 2;
				unsigned char access1	: 2;
				unsigned char type2		: 2;
				unsigned char access2	: 2;
			};
		};
	};
	struct CPU
	{
		char mem[0x200];
		union
		{
			unsigned char status;
			struct
			{
				unsigned char equal		: 1;	// Indica se nell'ultima comparazione i due numeri erano uguali
				unsigned char lower		: 1;	// Indica se nell'ultima comparazione il numero di sinistra era minore di quello di destra
				unsigned char greater	: 1;	// Indica se nell'ultima comparazione il numero di sinistra era maggiore di quello di destra
				unsigned char zero		: 1;	// Indica se nell'ultima comparazione o operazione matematica, il numero di sinistra era zero
				unsigned char retfunc	: 1;	// Indica se la funzione top chiede di restituire il controllo all'engine
				unsigned char zerodiv	: 1;	// Indica un interrupt (CAZZO!)
				unsigned char outofmem	: 1;	// Indica che è stato sforato l'array mem. Questo indica un bug
				unsigned char execute	: 1;	// TRUE se il processore virtuale è ancora in esecuzione, altrimenti è FALSE
			} Status;
		};
		short stack;
		short pc;
		short x, y;
	};

	OpCodeParam param;
	unsigned char *code;

	CPU cpu;
	unsigned char opcode;
	int param1Pos;
	int param2Pos;
	int n1;
	int n2;

	void ReadParams(int *n1, int *n2);
	void WriteParam(int n1);
	int GetParam(unsigned char type);
	void Push(int, int size);
	void Pop(char*, int size);
public:
	XeCPU();
	~XeCPU();

	// Carica un codice macchina virtuale
	void Load(char *filename);
	void Load(void *memory);
	// Inizializza il processore
	void Init();
	// Rilascia le vecchie risorse del processore
	void Clean();
	// Resetta il processore (chiama prima Clean e poi Init)
	void Reset();
	// Esegue il codice macchina virtuale. Se ritorna false, allora si è verificato un interrupt.
	bool Run();
};