#include "Input.h"
#include "System.h"

XeEngine::Input** XeEngine::Input::_Get()
{
	static Input* public_ = 0;
	return &public_;
}
void XeEngine::Input::Set(Input* public_)
{
	*_Get() = public_;
}
XeEngine::Input* XeEngine::Input::Get()
{
	return *_Get();
}

XeEngine::Input::Input()
{
	processAnalog = false;
	MemoryFill(keybStatus, sizeof(keybStatus));
	MemoryFill(keybSpecial, sizeof(keybSpecial));
	Set(this);
}
XeEngine::Input::~Input()
{

}

void XeEngine::Input::ProcessAnalog(bool p)
{
	processAnalog = p;
}
void XeEngine::Input::Update()
{
	gInputPrev[0] = gInput[0];
	gInputPrev[1] = gInput[1];
	gInputPrev[2] = gInput[2];
	gInputPrev[3] = gInput[3];

	for(int i=0; i<sizeof(keybStatus); i++)
	{
		if (keybStatus[i] == 2)
		{
			keybStatus[i] = 0;
		}
	}
	for(int i=0; i<sizeof(keybSpecial); i++)
	{
		if (keybSpecial[i] == 2)
		{
			keybSpecial[i] = 0;
		}
	}
}
bool XeEngine::Input::IsKeyDown(Key k)
{
	return keybStatus[k] == 1;
}
bool XeEngine::Input::IsKeyUp(Key k)
{
	return keybStatus[k] == 2;
}
bool XeEngine::Input::IsSpecialKeyDown(Key k)
{
	return keybSpecial[k] == 1;
}
bool XeEngine::Input::IsSpecialKeyUp(Key k)
{
	return keybSpecial[k] == 2;
}
XeEngine::Keys XeEngine::Input::Peek(int player)
{
	return gInput[player%4];
}
XeEngine::Keys XeEngine::Input::PeekRepeat(int player)
{
	return gInputRepeat[player%4];
}
XeEngine::Keys XeEngine::Input::PeekNoRepeat(int player)
{
	return gInput[player%4] & ~gInputPrev[player%4];
}
XeEngine::KeyF XeEngine::Input::GetLX(int player)
{
	return lx[player % 4];
}
XeEngine::KeyF XeEngine::Input::GetLY(int player)
{
	return ly[player % 4];
}
XeEngine::KeyF XeEngine::Input::GetRX(int player)
{
	return rx[player % 4];
}
XeEngine::KeyF XeEngine::Input::GetRY(int player)
{
	return ry[player % 4];
}
void XeEngine::Input::Vibration(Rumble left, Rumble right, int player)
{

}

void XeEngine::Input::_ProcessAnalog()
{
	//if (processAnalog == false) return;

	for(int player = 0; player < 4; player++)
	{
		if (GetLX(player) >= AnalogRange)
			gInput[player] |= InputKey_RIGHT;
		else if (GetLX(player) <= -AnalogRange)
			gInput[player] |= InputKey_LEFT;

		if (GetLY(player) >= AnalogRange)
			gInput[player] |= InputKey_UP;
		else if (GetLY(player) <= -AnalogRange)
			gInput[player] |= InputKey_DOWN;
	}
}
void XeEngine::Input::_MakeInputRepeat()
{
	Keys g;
	KeysRepeat *r;
	for(int player = 0; player < 4; player++)
	{
		g = gInput[player];
		r = repeatIndex[player];
		for(int i=0; i<0x10; i++)
		{
			if ((g & 1 << i) == 0)
			{
				r[i] = 0;
				continue;
			}

			if ((g & 1 << i) == (gInputPrev[player] & 1 << i))
			{
				if (r[i] != 0)
				{
					if (r[i] < RepeatValue)
					{
						g &= ~(1 << i);
					}
					else if (r[i] >= RepeatValue + RepeatSpeed)
					{
						r[i] = RepeatValue;
					}
					else
					{
						g &= ~(1 << i);
					}
				}
				r[i] ++;

			}
			else
			{
				r[i] = 0;
			}
		}
		gInputRepeat[player] = g;
	}
}
void XeEngine::Input::_Keyb2Joy()
{
	if (IsSpecialKeyDown(SpecialKey_LEFT))
		gInput[0] |= InputKey_LEFT;
	if (IsSpecialKeyDown(SpecialKey_UP))
		gInput[0] |= InputKey_UP;
	if (IsSpecialKeyDown(SpecialKey_RIGHT))
		gInput[0] |= InputKey_RIGHT;
	if (IsSpecialKeyDown(SpecialKey_DOWN))
		gInput[0] |= InputKey_DOWN;
	if (IsSpecialKeyDown(SpecialKey_RETURN))
		gInput[0] |= InputKey_START;
	if (IsSpecialKeyDown(SpecialKey_SHIFT))
		gInput[0] |= InputKey_BACK;
}