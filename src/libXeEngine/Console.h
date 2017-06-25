#pragma once

enum ConsoleColor
{
	ConsoleColor_Black	= 0,
	ConsoleColor_Blue	= 1,
	ConsoleColor_Green	= 2,
	ConsoleColor_Cyan	= 3,
	ConsoleColor_Red	= 4,
	ConsoleColor_Purple	= 5,
	ConsoleColor_Yellow	= 6,
	ConsoleColor_White	= 7,
	ConsoleColor_LightBlack		= 8,
	ConsoleColor_LightBlue		= 9,
	ConsoleColor_LightGreen		= 10,
	ConsoleColor_LightCyan		= 11,
	ConsoleColor_LightRed		= 12,
	ConsoleColor_LightPurple	= 13,
	ConsoleColor_LightYellow	= 14,
	ConsoleColor_LightWhite		= 15,
};

class Console
{
private:
	void *fConsole;
	void *hConsoleOut;
protected:
public:
	Console();
	~Console();

	// Crea una console
	void Create();
	// Distrugge una console già creata
	void Destroy();
	// Ottiene la dimensione del buffer della console
	void GetBufferSize(short *x, short *y);
	// Imposta la dimensione del buffer della console
	void SetBufferSize(short x, short y);
	// Cancella il contenuto della console
	void Clear();
	// Imposta le coordinate del cursore
	void SetXY(short x, short y);
	// Imposta il colore della console
	void SetColor(ConsoleColor background, ConsoleColor foreground);
	// Stampa un messaggio
	void Print(char *string, ...);
};