#pragma once
#include "XeObject.h"

class Obj0001_Sonic : public XeObject
{
private:
	PFloat maxrollspeed;
	ObjectHitboxRect colNormal;
	ObjectHitboxRect colRoll;
protected:
	// Routine principali
	void Sonic_OnFloor();
	void Sonic_Air();
	void Sonic_Rolling();
	void Sonic_Jump();
	void Sonic_Died();
	// Routine di comando
	void Sonic_CheckRoll();
	// Routine della fisica
	void RollRepel();
	void RollSpeed();
	// Routine per l'animazione
	void Sonic_AnimRunning();
	void Sonic_AnimRolling();
public:
	Obj0001_Sonic();
	~Obj0001_Sonic();
	virtual void Do();
	virtual bool Jump();
	virtual bool SpinDash();
	virtual void ResetOnFloor();
};