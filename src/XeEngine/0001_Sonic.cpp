#include "0001_Sonic.h"
#include "XeLevel.h"

/* NOTE:
In Sonic 1, quando Sonic entra nel tubo della Green Hill, quando inertia == 0, allora inertia = 0x20000.
In Sonic 1, quando si va in un loop, dopo aver superato la prima metà esso viene swtichato col chunk successivo.
*/

int balls = 0;

Obj0001_Sonic::Obj0001_Sonic() : XeObject(0x000F)
{
	maxrollspeed = FLOAT_TO_PFLOAT(10.0f);

	holdPlayer = new HoldPlayer;
	holdPlayer->score = 0;
	holdPlayer->ring = 0;
	holdPlayer->lifes = 3;

	colNormal = ObjectHitboxRect(9, 9, 20, 20, 10, 10);
	colRoll = ObjectHitboxRect(7, 7, 14, 14, 10, 10);
	collision = colNormal;
}
Obj0001_Sonic::~Obj0001_Sonic()
{
	delete holdPlayer;
}
void Obj0001_Sonic::Do()
{
	keys = keys;
	AnimationHandler();

	speedx &= ~0xFF;
	speedy &= ~0xFF;
	inertia &= ~0xFF;
	x &= ~0xFFFF;
	y &= ~0xFFFF;
	prevx &= ~0xFF;
	prevy &= ~0xFF;

	this;
	this->inertia;
	this->speedx;
	this->speedy;
	this->angle;
	this->x;
	this->y;

	if (Status.died)
	{
		Sonic_Died();
	}
	else if (Status.air && Status.rolling)
	{
		Sonic_Jump();
	}
	else if (Status.air)
	{
		Sonic_Air();
	}
	else if (Status.rolling)
	{
		Sonic_Rolling();
	}
	else
	{
		Sonic_OnFloor();
	}

	prevkeys.k = keys.k;
	Animation.SetAnimationIndex(animID);
	if (Animation.IsCreated())
	{
		if (animspeed_mod) Animation.LockAnimationSpeed(animspeed);
		Animation.Do();
		if (animspeed_mod) Animation.UnlockAnimationSpeed();
	}
}

void Obj0001_Sonic::Sonic_OnFloor()
{
	Sonic_AnimRunning();

	if (SpinDash()) return;
	if (Jump()) return;

	SlopeResist();
	if (keys.left & keys.right)	// Se tutti e due i pulsanti sono premuti, li annulla
		keys.left = keys.right = 0;
	else if (keys.left) MoveLeft();
	else if (keys.right) MoveRight();

	if (!(keys.left | keys.right))
	{
		LookDown();
		LookUp();
		Sonic_CheckRoll();
		Friction();
	}
	CalcSpeed();
	CheckWallsOnGround();
	Move();
	Border();
	AngleMove();
	SlopeRepel();
}
void Obj0001_Sonic::Sonic_Air()
{
	JumpHeight();
	JumpControl();
	Border();
	Fall();
	Move();
	JumpAngle();
	DoCollision();
}
void Obj0001_Sonic::Sonic_Rolling()
{
	Sonic_AnimRolling();
	//SpinDash();
	if (Jump()) return;

	RollRepel();
	RollSpeed();
	if (inertia == 0 && Status.spindash == 0)
	{
		SwitchCollision(&colNormal);
		Status.rolling = 0;
		animID = 0x0000;
	}
	CalcSpeed();
	/*if (speedx > maxrollspeed)
		speedx = maxrollspeed;
	else if (abs(speedy) > maxrollspeed)
		speedx = -maxrollspeed;*/
	CheckWallsOnGround();
	Move();
	Border();
	AngleMove();
	SlopeRepel();
}
void Obj0001_Sonic::Sonic_Jump()
{
	JumpHeight();
	JumpControl();
	JumpDecelerate();
	Border();
	Move();
	Fall();
	JumpAngle();
	DoCollision();
	animID = 0x2000;
}
void Obj0001_Sonic::Sonic_Died()
{
	animID = 0x3009;
	Status.controllocked = 1;

	switch(routineStatus)
	{
	case 0:
		angle = outangle = 0;
		Status.air = 1;
		speedx = 0;
		speedy = -0x70000;
		routineStatus = 1;
		GetLevel()->LockCamera();
	case 1:
		Fall();
		Move();
		if (y > (GetLevel()->border.bottom + 0x100) << 16)
			routineStatus = 2;
		break;
	case 2:
		Status.gone = 1;
		if (this == GetLevel()->mainobject)
		{
			GetLevel()->ResetLevel();
		}
		routineStatus = 3;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Routine di comando
void Obj0001_Sonic::Sonic_CheckRoll()
{
	if (keys.down)
	{
		if(ABS(inertia) <= ducking)
			return;
		if (keys.left | keys.right)
			return;

		SwitchCollision(&colRoll);
		Status.rolling = 1;
		animID = 0x100D;
	}
}

//////////////////////////////////////////////////////////////////////////
// Routine della fisica
void Obj0001_Sonic::RollRepel()
{
	PFloat tmp;
	if (u8(angle + 0x60) >= 0xC0)
		return;
	tmp = CalcSin(angle) * 0x50;
	if (inertia >= 0)
	{
		if (tmp >= 0)
		{
			inertia += tmp;
			return;
		}
		tmp >>= 2;
	}
	if (tmp > 0)
		tmp >>= 2;
	inertia += tmp;
}
void Obj0001_Sonic::RollSpeed()
{
	if (keys.left)
	{
		if (inertia > 0)
		{
			inertia -= deceleration/4;
			if (inertia < 0)
				inertia = 0;
		}
	}
	if (keys.right)
	{
		if (inertia < 0)
		{
			inertia += deceleration/4;
			if (inertia > 0)
				inertia = 0;
		}
	}

	friction /= 2;
	Friction();
	friction *= 2;
}

//////////////////////////////////////////////////////////////////////////
// Routine per l'animazione
void Obj0001_Sonic::Sonic_AnimRunning()
{
	if (!(keys.down | keys.up | keys.left | keys.right))
	{
		if (inertia == 0)
			animID = 0x0000;
	}
	switch(animID)
	{
	case 0x1001:	// Walking
		animspeed_mod = true;
		animspeed = 8 - XeEngine::Abs(speedx>>16);
		break;
	}
}
void Obj0001_Sonic::Sonic_AnimRolling()
{
	switch(animID)
	{
	case 0x100D:
	case 0x6300:
		animID = 0x2000;
		animspeed_mod = true;
		animspeed = XeEngine::Max(15 - XeEngine::Abs(speedx>>16), 1);
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
bool Obj0001_Sonic::Jump()
{
	if (XeObject::Jump())
	{
		SwitchCollision(&colRoll);
		return true;
	}
	return false;
}
bool Obj0001_Sonic::SpinDash()
{
	if (XeObject::SpinDash())
	{
		SwitchCollision(&colRoll);
		return true;
	}
	return false;
}
void Obj0001_Sonic::ResetOnFloor()
{
	XeObject::ResetOnFloor();
	animID = 0x1001;
	SwitchCollision(&colNormal);
}