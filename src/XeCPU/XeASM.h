#pragma once
#include "List.h"

struct LexStat
{
	char *filename;
	char *pos;
	char *end;
	char *source;
	int lines;
	int charpos;
	enum LexMode mode;
};
struct OpCodeContainer
{
	unsigned char opcode;
	unsigned char param;
	unsigned int labelhash;
	unsigned char variable;
	int n1, n2;
};
struct LabelContainer
{
	unsigned int labelhash;
	unsigned int position;
};

class XeASM
{
private:
	unsigned char *out;
protected:
	LexStat lex;
	char buf[64];
	List<OpCodeContainer> opcodeList;
	List<LabelContainer> labelList;
	int pc;

	char *filename;
	int lasterror;
	bool SetLastError(int error);

	int Hash(char*);
	int GetOpcodeSize(OpCodeContainer*);
	int Compile(LexStat *lex);
	int Analyze(LexStat *lex);
	int Assemble(LexStat *lex);
	char *GetWord(LexStat *lex);
	int GetOpCode(char *w);
	bool ConvertWordAsNumber(LexStat *lex, int *n);
public:
	XeASM();
	~XeASM();

	// Ottiene in formato di stringa l'ultimo errore
	char *GetLastError();
	// Carica un sorgente in formato testuale da file
	bool LoadFromFile(char *filename);
	// Carica un sorgente in formato testuale da memoria
	bool LoadFromMemory(char *sourcecode);
	// Salva il sorgente compilato su file
	bool SaveToFile(char *filename);
	// Ottiene il sorgente compilato da file
	void *GetMachineCode();
};