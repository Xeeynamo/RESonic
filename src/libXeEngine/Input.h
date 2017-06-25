#pragma once
#include "XeBase.h"

#define SpecialKey_ESCAPE	0x00
#define SpecialKey_RETURN	0x01
#define SpecialKey_LEFT		0x02
#define SpecialKey_UP		0x03
#define SpecialKey_RIGHT	0x04
#define SpecialKey_DOWN		0x05
#define SpecialKey_HOME		0x06
#define SpecialKey_END		0x07
#define SpecialKey_PGUP		0x08
#define SpecialKey_PGDOWN	0x09
#define SpecialKey_SPACE	0x0A
#define SpecialKey_CTRL		0x0B
#define SpecialKey_ALT		0x0C
#define SpecialKey_SHIFT	0x0D
#define SpecialKey_MENU		0x0E
#define SpecialKey_DELETE	0x0F
#define SpecialKey_F1		0x11
#define SpecialKey_F2		0x12
#define SpecialKey_F3		0x13
#define SpecialKey_F4		0x14
#define SpecialKey_F5		0x15
#define SpecialKey_F6		0x16
#define SpecialKey_F7		0x17
#define SpecialKey_F8		0x18
#define SpecialKey_F9		0x19
#define SpecialKey_F10		0x1A
#define SpecialKey_F11		0x1B
#define SpecialKey_F12		0x1C
#define SpecialKey_F13		0x1D
#define SpecialKey_F14		0x1E
#define SpecialKey_F15		0x1F

namespace XeEngine
{
	typedef u8 Key;
	typedef s16 KeyF;
	typedef u16 Keys;
	typedef u16 Rumble;
	typedef u8 KeysRepeat;

	const Keys InputKey_UP			= 0x0001;
	const Keys InputKey_DOWN		= 0x0002;
	const Keys InputKey_LEFT		= 0x0004;
	const Keys InputKey_RIGHT		= 0x0008;
	const Keys InputKey_START		= 0x0010;
	const Keys InputKey_BACK		= 0x0020;
	const Keys InputKey_L3			= 0x0040;
	const Keys InputKey_R3			= 0x0080;
	const Keys InputKey_L1			= 0x0100;
	const Keys InputKey_R1			= 0x0200;
	const Keys InputKey_L2			= 0x0400;
	const Keys InputKey_R2			= 0x0800;
	const Keys InputKey_CROSS		= 0x1000;
	const Keys InputKey_CIRCLE		= 0x2000;
	const Keys InputKey_TRIANGLE	= 0x4000;
	const Keys InputKey_SQUARE		= 0x8000;
	
	class Input
	{
	private:
		static Input** _Get();
	protected:
		const static KeysRepeat RepeatValue = 60;
		const static KeysRepeat RepeatSpeed = 4;
		const static short AnalogRange = 24576; //32768/2 + 32768/4

		Keys gInput[4];
		Keys gInputPrev[4];
		Keys gInputRepeat[4];
		KeyF lx[4], ly[4];
		KeyF rx[4], ry[4];
		KeysRepeat repeatIndex[4][16];
		bool processAnalog;

		void _ProcessAnalog();
		void _MakeInputRepeat();
		void _Keyb2Joy();
	public:
		u8 keybStatus[0x100];
		u8 keybSpecial[0x20];

		static void Set(Input*);
		static Input* Get();

		Input();
		virtual ~Input();

		void ProcessAnalog(bool);
		virtual void Update();

		bool IsKeyDown(Key);
		bool IsKeyUp(Key);
		bool IsSpecialKeyDown(Key);
		bool IsSpecialKeyUp(Key);
		Keys Peek(int player = 0);
		Keys PeekRepeat(int player = 0);
		Keys PeekNoRepeat(int player = 0);
		KeyF GetLX(int player = 0);
		KeyF GetLY(int player = 0);
		KeyF GetRX(int player = 0);
		KeyF GetRY(int player = 0);
		virtual void Vibration(Rumble left, Rumble right, int player = 0);
	};
}