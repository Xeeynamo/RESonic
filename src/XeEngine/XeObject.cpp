#include "XeObject.h"
#include "XeLevel.h"
#include "XeObjectAnimation.h"
#include "XeScene.h"
#include <math.h>

#define COLLISION_MOVE(n, s) (n = (n&~0xFFFF) + (s<<16))

const char Angle_Data[258] =
{
	0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05,
	0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A,
	0x0A, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13,
	0x13, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15,
	0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x17, 0x17,
	0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A,
	0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C,
	0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D,
	0x1D, 0x1D, 0x1D, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F,
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,
};

void XeObject_PrintdEventRuntime(short runtime, void *param);
void XeObject_PrintdEventAnim(short anim);

XeObject::XeObject(ushort id)
{
	this->id = id;
	animID = 0;

	level = NULL;
	keys.k = prevkeys.k = 0;
	routineStatus = 0;
	//x = y = 0;
	z = 0.0f;
	prevx = prevy = 0;

	// Altre variabili
	status = 0;
	path = false;
	angle = 0x00;
	outangle = 0x00;
	slope_movelock = 0;
	jumpallowed = 8;
	jumpcounter = 0;
	animspeed_mod = false;

	// Variabili della fisica
	speedx = speedy = 0;
	inertia = 0;
	// Fisica
	acceleration = FLOAT_TO_PFLOAT(0.046875f);
	deceleration = FLOAT_TO_PFLOAT(0.5f);
	friction = FLOAT_TO_PFLOAT(0.046875f);
	minspeed = FLOAT_TO_PFLOAT(0.0f);
	maxspeed = FLOAT_TO_PFLOAT(6.0f);
	gravity = FLOAT_TO_PFLOAT(0.21875f);
	maxgravity = FLOAT_TO_PFLOAT(16.0f);
	jump = FLOAT_TO_PFLOAT(6.5f);
	jumpmin = FLOAT_TO_PFLOAT(4.0f);
	airaccmin = FLOAT_TO_PFLOAT(0.125);
	brake = FLOAT_TO_PFLOAT(4.5f);
	ducking = FLOAT_TO_PFLOAT(1.03125); // 0.53125 in Sonic 1/2
	// Collisioni
	collision.bottom = (19)<<16;
	collision.top = (19)<<16;
	collision.left = (9)<<16;
	collision.right = (9)<<16;
	// Holds
	holdPlayer = NULL;
	holdRpg = NULL;
}
XeObject::~XeObject()
{

}
void XeObject::AttachLevel(XeLevel *level)
{
	this->level = level;
}
XeLevel *XeObject::GetLevel() const
{
	return level;
}
void XeObject::DeleteMeFromLevel()
{
	if (!GetLevel()) return;
	GetLevel()->DestroyObject(this);
}
void XeObject::TakeLevelControl()
{
	if (!GetLevel()) return;
	GetLevel()->AttachEntity(this);
}

ushort XeObject::GetID() const
{
	return this->id;
}
// Controllo dell'oggetto
void XeObject::Input(KeyInput keys)
{
	this->keys.k = keys.k;
}

// Fisica dell'oggetto
void XeObject::Do()
{
	//
}
void XeObject::Draw()
{
	if (!tex) return;
	LayerProperties* layer = level->map.Layer(0);
	//if (layer == NULL) return;
	
	PFloat screenWidth = level->resWidth<<16;
	PFloat screenHeight = level->resHeight<<16;
	PFloat levelWidth = layer->width<<24;
	PFloat levelHeight = layer->height<<24;

	PFloat screenx, screeny;
	screenx = x - level->cameraX;
	screeny = y - level->cameraY;

	if (Animation.IsCreated())
	{
		ObjectAnimationFrame *animframe;
		Animation.LockAnimationFrame(&animframe);
		animframe->rotation += (angle * (Status.verse ? -1 : 1));
		Animation.Draw(tex, HIWORD(screenx), HIWORD(screeny), Status.verse & 1, Status.verse & 2, z);
		Animation.UnlockAnimationFrame();
	}
	else
	{
		XeEntity::Draw();
	}
}
void XeObject::CollisionObject(XeObject *o)
{
	con.Log(DEBUG_LEVEL_INFO, "%04X collide with %04X", this->id, o->id);
}
void XeObject::AnimationHandler()
{
	animspeed_mod = false;
	switch (animID)
	{
		break;
	case 0x1002:	// Running
		if (inertia < abs(maxspeed) && abs(maxspeed) > 0)
			animID = 0x1001;
		break;
	case 0x010F:
	case 0x011F:
	case 0x0013:
	case 0x0113:
		break;
	case 0x6300:
		if (inertia == 0)
			animID = 0x0000;
		break;
	default:
		if ((animID&0xF000) == 0x1000)
		{
			if (inertia == 0 && !keys.left && !keys.right)
			{
				if (((angle+0x20)&0xC0) == 0)
					animID = 0x0000;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// FUNZIONI
short XeObject::CalcSin(unsigned char angle)
{
	return (short)((sin((90.0/64*0.0174532925)*float(angle))) * 256);
}
short XeObject::CalcCos(unsigned char angle)
{
	return (short)((cos((90.0/64*0.0174532925)*float(angle))) * 256);
}
char XeObject::CalcAngle(short x, short y)
{
	char r = 0;

	short nx = abs(x);
	short ny = abs(y);
	if((nx | ny) == 0)
	{
		return 0x40;
	}

	if(ny < nx)
	{
		ny <<= 8;
		if(nx)
		{
			r = Angle_Data[(unsigned short)ny / (unsigned short)nx];
		}
		else
			ny = 0;
	}
	else
	{
		nx <<= 8;
		if(ny)
		{
			r = 0x40 - Angle_Data[(unsigned short)nx / (unsigned short)ny];
		}
		else
			nx = 0;
	}

	if(x < 0)
		r = -r + 0x80;
	if(y < 0)
		r = -r + 0x100;

	return r;
}
void XeObject::RefreshAngle(char newangle)
{
	if (newangle & 1)
	{
		newangle = angle;
		newangle += 0x20;
		newangle &= 0xC0;
		angle = newangle;
	}
	else
	{
		char tmp = newangle - angle;
		if (tmp < 0)
			tmp = -tmp;
		if (tmp < 0x20)
			angle = newangle;
	}
}

//////////////////////////////////////////////////////////////////////////
// FISICA
void XeObject::Friction()
{
	if (inertia == 0) return;
	else if (inertia > 0)
	{
		if (inertia > friction)
			inertia -= friction;
		else
			inertia = 0;
	}
	else if (inertia < 0)
	{
		if (inertia < -friction)
			inertia += friction;
		else
			inertia = 0;
	}
}
void XeObject::Fall()
{
	if (Status.air == 0)
		return;
	speedy += gravity;
	if (speedy > maxgravity)
	{
		speedy = maxgravity;
	}
}
void XeObject::CalcSpeed()
{
	speedx = (((inertia * CalcCos(angle))) >> 16) << 8;
	speedy = (((inertia * CalcSin(angle))) >> 16) << 8;
}
void XeObject::Move()
{
	//if (speedx != 0)
	{
		x = (x&~0xFFFF) + prevx + speedx;
		prevx = x&0xFFFF;
	}
	//if (speedy != 0)
	{
		y = (y&~0xFFFF) + prevy + speedy;
		prevy = y&0xFFFF;
	}
}
void XeObject::SlopeResist()
{
	PFloat tmp;
	if (inertia == 0) return;
	if (u8(angle + 0x60) >= 0xC0) return;
	tmp = CalcSin(angle) * 0x20;
	inertia += tmp&~0xFF;
	return;
}
void XeObject::SlopeRepel()
{
	if (slope_movelock == 0)
	{
		if (((angle + 0x20) & 0xC0) == 0)
			return;
		if (abs(inertia) < FLOAT_TO_PFLOAT(2.5))
		{
			inertia = 0;
			Status.air = 1;
			slope_movelock = 0x1E;
		}
	}
	else
	{
		slope_movelock--;
	}
	return;
}
void XeObject::ResetOnFloor()
{
	switch(0)
	{
	case 0:
		//animID = 0x0000; // Animazione della corsa
	case 1:
		if (Status.jump || Status.rolling)
		{
			Status.jump = 0;
			Status.rolling = 0;
			// Imposta animazione della corsa
			// Resetta le collisioni in OnFloor/Air
			jumpcounter = jumpallowed;
		}
	case 2:
		// remove from status 0xCD
		Status.air = 0;
		break;
	}
}
void XeObject::JumpHeight()
{
	if (Status.jump != 0)
	{
		if (-jumpmin > speedy)
		{
			if (!(keys.cross | keys.circle))
			{
				speedy = -jumpmin;
			}
		}
	}
}
void XeObject::JumpControl()
{
	if (keys.left)
	{
		Status.verse = 1;
		speedx -= (acceleration*2);
		if (speedx < -maxspeed)
			speedx = -maxspeed;
	}
	if (keys.right)
	{
		Status.verse = 0;
		speedx += (acceleration*2);
		if (speedx > maxspeed)
			speedx = maxspeed;
	}
}
void XeObject::JumpDecelerate()
{
	if (speedy < -jumpmin || speedy >= 0)
		return;
	PFloat prev = speedx;
	speedx -= (speedx/32);
	if (prev > 0 && speedx < 0) speedx = 0;
	else if (prev < 0 && speedx > 0) speedx = 0;
}
void XeObject::JumpAngle()
{
	if(angle == 0)
		return;
	else if (angle > 0)
	{
		angle -= 2;
		if (angle < 0)
			angle = 0;
	}
	else if (angle < 0)
	{
		angle += 2;
		if (angle > 0)
			angle = 0;
	}
	return;
}
void XeObject::WalkHD()
{
	char r, s;
	const int fieldmagnet = 0x0E;

	r = CheckFloor();
	RefreshAngle(outangle);

	// Aggiusto la posizione dell'oggetto
	if (r == 0 || r < -fieldmagnet)
	{
		// Nulla, la collisione non avviene
	}
	else if (r < 0)
	{
		// Il personaggio è "sotto" il terreno, con questo lo si rialza
		COLLISION_MOVE(y, r);
	}
	else
	{
		// Il personaggio è sopra il terreno di qualche pixel.
		// In base a fieldmagnet, viene fissato nel terreno.
		s = (speedx>>16) & 0xFF;
		if (s < 0) s = -s;
		s += 4;
		if (s >= fieldmagnet)
			s = fieldmagnet;
		if (r <= s)
		{
			// Collisione magnete avvenuta, il personaggio si appiccica al terreno.
			COLLISION_MOVE(y, r);
		}
		else
		{
			// Collisione magnete non avvenuta, il personaggio ora è in aria.
			Status.air = 1;
			Status.pushing = 0;
		}
	}
}
void XeObject::WalkVR()
{
	char s, r;
	const int fieldmagnet = 0x0E;
	r = CheckRightFloor();
	RefreshAngle(outangle);	// Aggiusto la posizione dell'oggetto
	if (r == 0 || r < -fieldmagnet)
	{
		// Nulla, la collisione non avviene
	}
	else if (r < 0)
	{
		// Il personaggio è "sotto" il terreno, con questo lo si rialza
		COLLISION_MOVE(x, r);
	}
	else
	{
		// Il personaggio è sopra il terreno di qualche pixel.
		// In base a fieldmagnet, viene fissato nel terreno.
		s = (speedy>>16) & 0xFF;
		if (s < 0) s = -s;
		s += 4;
		if (s >= fieldmagnet)
			s = fieldmagnet;
		if (r <= s)
		{
			// Collisione magnete avvenuta, il personaggio si appiccica al terreno.
			COLLISION_MOVE(x, r);
		}
		else
		{
			// Collisione magnete non avvenuta, il personaggio ora è in aria.
			Status.air = 1;
		}
	}
}
void XeObject::WalkHU()
{
	char r, s;
	const int fieldmagnet = 0x0E;

	r = CheckCeiling();
	RefreshAngle(outangle);

	// Aggiusto la posizione dell'oggetto
	if (r == 0 || r < -fieldmagnet)
	{
		// Nulla, la collisione non avviene
	}
	else if (r < 0)
	{
		// Il personaggio è "sotto" il terreno, con questo lo si rialza
		COLLISION_MOVE(y, -r);
	}
	else
	{
		// Il personaggio è sopra il terreno di qualche pixel.
		// In base a fieldmagnet, viene fissato nel terreno.
		s = (speedx>>16) & 0xFF;
		if (s < 0) s = -s;
		s += 4;
		if (s >= fieldmagnet)
			s = fieldmagnet;
		if (r <= s)
		{
			// Collisione magnete avvenuta, il personaggio si appiccica al terreno.
			COLLISION_MOVE(y, -r);
		}
		else
		{
			// Collisione magnete non avvenuta, il personaggio ora è in aria.
			Status.air = 1;
			Status.pushing = 0;
		}
	}
}
void XeObject::WalkVL()
{
	char s, r;
	char as, ar;
	const int fieldmagnet = 0x0E;

	r = FindWall((x - collision.top) ^ 0xFFFFF, y - collision.left, 1, false);
	ar = outangle;
	s = FindWall((x - collision.top) ^ 0xFFFFF, y + collision.right, 1, false);
	as = outangle;
	// Vedo quale dei due valori in uscita devo prendere
	if (s > r)
	{
		s = r;
		outangle = ar;
	}
	RefreshAngle(outangle);	// Aggiusto la posizione dell'oggetto
	if (s == 0 || s < -fieldmagnet)
	{
		// Nulla, la collisione non avviene
	}
	else if (s < 0)
	{
		// Il personaggio è "sotto" il terreno, con questo lo si rialza
		COLLISION_MOVE(x, -s);
	}
	else
	{
		// Il personaggio è sopra il terreno di qualche pixel.
		// In base a fieldmagnet, viene fissato nel terreno.
		r = (speedy>>16) & 0xFF;
		if (r < 0) r = -r;
		r += 4;
		if (r >= fieldmagnet)
			r = fieldmagnet;
		if (s <= r)
		{
			// Collisione magnete avvenuta, il personaggio si appiccica al terreno.
			COLLISION_MOVE(x, -s);
		}
		else
		{
			// Collisione magnete non avvenuta, il personaggio ora è in aria.
			Status.air = 1;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// AZIONI
void XeObject::MoveLeft()
{
	if (slope_movelock > 0) return;
	if (inertia > 0)									// Se ti vuoi muovere verso la direzione opposta,
	{
		if (Status.air == 0)							// Se Sonic è a terra
			if (inertia >= brake)						// e la sua velocità è di 4px al secondo
				animID = 0x1006;						// allora esegui l'animazione braking
		if (inertia < deceleration)						// Controlla se la velocità corrente è minore della decelerazione
		{
			inertia = -deceleration;					// Se si, allora passa al lato opposto 
		}
		else
		{
			inertia += -deceleration;					// Altrimenti decelera e basta
		}
	}
	else								// Se invece si sta andando verso la direzione giusta
	{
		Status.verse = 1;
		if (inertia > -maxspeed)
		{
			if (inertia - acceleration < -maxspeed)			// Allora vede se accelerando, si raggiungela velocità massima
			{
				animID = 0x1002;
				inertia = -maxspeed;						// Se si, la velocità è uguale alla velocità massima
			}
			else											// Altrimenti se non si è ancora raggiunta la velocità massima
			{
				animID = 0x1001;
				inertia -= acceleration;					// Altrimenti accelera normalmente
			}
		}
		else
		{
			animID = 0x1002;
		}
	}
}
void XeObject::MoveRight()
{
	if (slope_movelock > 0) return;
	if (inertia < 0)
	{
		if (Status.air == 0)							// Se Sonic è a terra
			if (inertia <= -brake)						// e la sua velocità è di 4px al secondo
				animID = 0x1006;						// allora esegui l'animazione braking
		if (inertia > -deceleration)
		{
			inertia = deceleration;
		}
		else
		{
			inertia += deceleration;
		}
	}
	else
	{
		Status.verse = 0;
		if (inertia < maxspeed)
		{
			if (inertia + acceleration > maxspeed)
			{
				animID = 0x1002;
				inertia = maxspeed;
			}
			else if (inertia < maxspeed)
			{
				animID = 0x1001;
				inertia += acceleration;
			}
		}
		else
		{
			inertia = maxspeed;
			animID = 0x1002;
		}
	}
}
bool XeObject::Jump()
{
	if (Status.spindash) return false;
	if (!(keys.cross | keys.circle)) return false;
	if (prevkeys.cross) return false;
	if (prevkeys.circle) return false;

	char r = CalcRoomOverHead(angle);
	if(r < 6) return false;
	speedx += CalcCos(angle - 0x40) * jump / 256;
	speedy += CalcSin(angle - 0x40) * jump / 256;
	Status.jump = 1;
	Status.air = 1;
	Status.rolling = 1;
	Status.pushing = 0;
	animID = 0x2000;

	return true;
}
void XeObject::LookDown()
{
	if (keys.down)
	{
		if (abs(inertia) > ducking) return;
		if (Status.air) return;
		if (Status.ledge) return;

		animID = 0x000F;
		Status.duck = true;
	}
	else if (prevkeys.down)
	{
		Status.duck = false;
		animID = 0x010F;
	}
}
void XeObject::LookUp()
{
	if (keys.up)
	{
		if (inertia) return;
		if (Status.air) return;
		if (Status.ledge) return;
		animID = 0x0013;
	}
	else if (prevkeys.up)
	{
		animID = 0x0113;
	}
}
bool XeObject::SpinDash()
{
	char dashkey = 0;
	if (keys.circle != 0 && prevkeys.circle == 0)		// Logical press
		dashkey = 1;
	else if (keys.cross != 0 && prevkeys.cross == 0)	// Logical press
		dashkey = 1;

	if (Status.spindash)
	{
		if (keys.down)
		{
			// Diminuisce la velocità dello spindash
			spindash_speed -= (spindash_speed>>5);
			if (spindash_speed < 0)
				spindash_speed = 0;
			// La aumenta se si carica lo spindash
			if (dashkey)
			{
				animID = 0x6200;
				spindash_speed += 0x200;
				if (spindash_speed > 0x800)
					spindash_speed = 0x800;
			}
		}
		else
		{
			animID = 0x6300;
			Status.spindash = 0;
			Status.rolling = 1;
			Status.duck = false;
			inertia = 0x80000 + (spindash_speed<<7);
			if (Status.verse) inertia = -inertia;
		}
		return true;
	}

	// Questa parte della routine serve per quando l'oggetto non è ancora in dashing
	if (!Status.duck) return false;
	if (!dashkey) return false;

	inertia = 0;
	Status.spindash = 1;
	spindash_speed = 0;
	animID = 0x6000;

	return true;
}
void XeObject::Kill()
{
	Status.died = 1;
	routineStatus = 0;
}

//////////////////////////////////////////////////////////////////////////
// COLLISIONI
void XeObject::SwitchCollision(ObjectHitboxRect *rect)
{
	if (collision == *rect) return;
	switch((angle+0x20)&0xC0)
	{
	case 0x00:
		y -= (rect->bottom - collision.bottom);
		break;
	case 0x40:
		x += (rect->bottom - collision.bottom);
		break;
	case 0x80:
		y += (rect->bottom - collision.bottom);
		break;
	case 0xC0:
		x -= (rect->bottom - collision.bottom);
		break;
	}
	collision = *rect;
}
bool XeObject::Collide(XeObject *o)
{
	if (o == NULL) return false;
	if (o == this) return false;
	if (y - collision.top > o->y + o->collision.bottom) return false;
	if (y + collision.bottom < o->y - o->collision.top) return false;
	if (x - collision.left > o->x + o->collision.right) return false;
	if (x + collision.right < o->x - o->collision.left) return false;
	return true;
}
void XeObject::Border()
{
	Status.outofscreen = false;
	if ((signed short)(HIWORD(x - collision.left*2)) < level->border.left)
	{
		inertia = 0;
		x = (level->border.left<<16) + collision.left*2;
	}
	else if ((signed short)HIWORD(x + collision.right) > level->border.right)
	{
		inertia = 0;
		x = (level->border.right<<16) - collision.right;
	}

	if ((signed short)HIWORD(y) < level->border.top)
	{
		Status.outofscreen = true;
		if (Status.graverse == 1)
			Kill();
	}
	else if ((signed short)HIWORD(y) > level->border.bottom)
	{
		Status.outofscreen = true;
		if (Status.graverse == 0)
			Kill();
	}
}
char XeObject::FindFloor(PFloat px, PFloat py, char flip, bool verse)
{
	short x = px>>16;
	short y = py>>16;
	TileEntry t;
	byte colIndex;
	char h;
	char block = (verse ? 0x10 : -0x10);

	// Ottiene il tile e controlla se è 0
	t = level->GetBlock(x>>4, y>>4);
	if (t.Tile == 0)
		goto loc_findfloor_notfound;
	// Ottiene l'indirizzo verso la collisione e controlla se è 0
	colIndex = level->collisionIndex[path==false][t.Tile];
	if (colIndex == 0)
		goto loc_findfloor_notfound;
	// Vede se il tile prevede la collisione da terra
	h = path ? t.path2 : t.path1;
	if (!(h&(verse ? 1 : 2)))
		goto loc_findfloor_notfound;

	outangle = level->collisionAngle[colIndex];
	// Se mirror, l'angolo è girato orizzontalmente
	if (t.mirror)
	{
		x = ~x;
		outangle = -outangle;
	}
	// Se flip, l'angolo è girato verticalmente
	if (t.flip)
	{
		outangle = -outangle + 0x80;
	}
	h = level->collision[0x000 | colIndex][x&0xF];
	// Se flip ^ t.flip, h viene invertito
	if (t.flip ^ (flip!=0))
		h = -h;
	// Se h è 0, non avviene alcuna collisione
	if (h != 0)
	{
		if (h < 0)
		{
			// Inverse
			h += (y&0xF);
			if (h < 0)
				goto loc_findfloor_blockfull;
			// Se non avviene una mazza, passa a loc_findfloor_notfound
		}
		else if (h == 0x10)
		{
loc_findfloor_blockfull:
			// Block full
			return FindFloor2(px>>16, y - block, flip, verse) - 0x10;
		}
		else
		{
			// Normal
			h += (y&0xF);
			return 0xF - h;
		}
	}

loc_findfloor_notfound:
	return FindFloor2(px>>16, y + block, flip, verse) + 0x10;
}
char XeObject::FindFloor2(short x, short y, char flip, bool verse)
{
	TileEntry t;
	byte colIndex;
	char h;

	// Ottiene il tile e controlla se è 0
	t = level->GetBlock(x>>4, y>>4);
	if (t.Tile == 0)
		goto loc_findfloor_notfound;
	// Ottiene l'indirizzo verso la collisione e controlla se è 0
	colIndex = level->collisionIndex[path==false][t.Tile];
	if (colIndex == 0)
		goto loc_findfloor_notfound;
	// Vede se il tile prevede la collisione da terra
	h = path ? t.path2 : t.path1;
	if (!(h&(verse ? 1 : 2)))
		goto loc_findfloor_notfound;

	outangle = level->collisionAngle[colIndex];
	// Se mirror, l'angolo è girato orizzontalmente
	if (t.mirror)
	{
		x = ~x;
		outangle = -outangle;
	}
	// Se flip, l'angolo è girato verticalmente
	if (t.flip)
	{
		outangle = -outangle + 0x80;
	}
	h = level->collision[0x000 | colIndex][x&0xF];
	// Se flip ^ t.flip, h viene invertito
	if (t.flip ^ (flip!=0))
		h = -h;
	// Se h è 0, non avviene alcuna collisione
	if (h != 0)
	{
		if (h < 0)
		{
			// Inverse
			h += (y&0xF);
			if (h < 0)
				return ~(y&0xF);
			// Se non avviene una mazza, passa a loc_findfloor_notfound
		}
		// Non cerco il blockfull per ovvie ragioni
		else
		{
			// Normal
			h += (y&0xF);
			return 0xF - h;
		}
	}
loc_findfloor_notfound:
	return 0xF - (y&0xF);
}
char XeObject::FindWall(PFloat px, PFloat py, char mirror, bool verse)
{
	short x = px>>16;
	short y = py>>16;
	TileEntry t;
	byte colIndex;
	char h;
	char block = (verse ? 0x10 : -0x10);

	// Ottiene il tile e controlla se è 0
	t = level->GetBlock(x>>4, y>>4);
	if (t.Tile == 0)
		goto loc_findwall_notfound;
	// Ottiene l'indirizzo verso la collisione e controlla se è 0
	colIndex = level->collisionIndex[path==false][t.Tile];
	if (colIndex == 0)
		goto loc_findwall_notfound;
	// Vede se il tile prevede la collisione da terra
	h = path ? t.path2 : t.path1;
	if (!(h&2))
		goto loc_findwall_notfound;

	outangle = level->collisionAngle[colIndex];
	// Se mirror, l'angolo è girato orizzontalmente
	if (t.mirror)
	{
		outangle = -outangle;
	}
	// Se flip, l'angolo è girato verticalmente
	if (t.flip)
	{
		y = ~y;
		outangle = -outangle + 0x80;
	}
	h = level->collision[0x100 | colIndex][y&0xF];
	// Se mirror ^ t.mirror, h viene invertito
	if (t.mirror ^ (mirror!=0))
		h = -h;
	// Se h è 0, non avviene alcuna collisione
	if (h != 0)
	{
		if (h < 0)
		{
			// Inverse
			h += (x&0xF);
			if (h < 0)
				goto loc_findwall_full;
			// Se non avviene una mazza, passa a loc_findfloor_notfound
		}
		else if (h == 0x10)
		{
loc_findwall_full:
			// Block full
			return FindWall2(x - block, py>>16, mirror, verse) - 0x10;
		}
		else
		{
			// Normal
			h += (x&0xF);
			return 0xF - h;
		}
	}

loc_findwall_notfound:
	return FindWall2(x + block, py>>16, mirror, verse) + 0x10;
}
char XeObject::FindWall2(short x, short y, char mirror, bool verse)
{
	TileEntry t;
	byte colIndex;
	char h;

	// Ottiene il tile e controlla se è 0
	t = level->GetBlock(x>>4, y>>4);
	if (t.Tile == 0)
		goto loc_findwall_notfound;
	// Ottiene l'indirizzo verso la collisione e controlla se è 0
	colIndex = level->collisionIndex[path==false][t.Tile];
	if (colIndex == 0)
		goto loc_findwall_notfound;
	// Vede se il tile prevede la collisione da terra
	h = path ? t.path2 : t.path1;
	if (!(h&2))
		goto loc_findwall_notfound;

	outangle = level->collisionAngle[colIndex];
	// Se mirror, l'angolo è girato orizzontalmente
	if (t.mirror)
	{
		outangle = -outangle;
	}
	// Se flip, l'angolo è girato verticalmente
	if (t.flip)
	{
		y = ~y;
		outangle = -outangle + 0x80;
	}
	h = level->collision[0x100 | colIndex][y&0xF];
	// Se mirror ^ t.mirror, h viene invertito
	if (t.mirror ^ (mirror!=0))
		h = -h;
	// Se h è 0, non avviene alcuna collisione
	if (h != 0)
	{
		if (h < 0)
		{
			// Inverse
			h += (x&0xF);
			if (h < 0)
				return ~(x&0xF);
		}
		else
		{
			// Normal
			h += (x&0xF);
			return 0xF - h;
		}
	}

loc_findwall_notfound:
	return 0xF - (x&0xF);
}
char XeObject::CheckFloor()
{
	char s, r;
	char as, ar;
	outangle = 3;
	r = FindFloor(x + collision.right, y + collision.bottom);
	ar = outangle;
	outangle = 3;
	s = FindFloor(x - collision.left, y + collision.bottom);
	as = outangle;

	if (s > r)
	{
		s = r;
		outangle = ar;
	}
	return s;
}
char XeObject::CheckRightFloor()
{
	char r, s;
	char ar, as;
	outangle = 3;
	r = FindWall(x + collision.bottom, y - collision.left);
	ar = outangle;
	outangle = 3;
	s = FindWall(x + collision.bottom, y + collision.right);
	as = outangle;
	// Vedo quale dei due valori in uscita devo prendere
	if (r > s)
	{
		r = s;
		outangle = as;
	}
	return r;
}
char XeObject::CheckLeftFloor()
{
	return 0;
}
char XeObject::CheckCeiling()
{
	char r, s;
	char ar, as;
	r = FindFloor(x + collision.right, (y - collision.top) ^ 0xFFFFF, 1, false);
	ar = outangle;
	s = FindFloor(x - collision.left, (y - collision.top) ^ 0xFFFFF, 1, false);
	as = outangle;

	if (s > r)
	{
		outangle = ar;
		s = r;
	}
	if (outangle & 1)
		outangle = (char)0x80;
	return s;
}
char XeObject::CheckLeftCeiling()
{
	char s, r;
	char as, ar;
	r = FindWall(x - collision.top, (y - collision.left) ^ 0xFFFFF);
	ar = outangle;
	s = FindWall(x + collision.bottom, (y - collision.left) ^ 0xFFFFF);
	as = outangle;

	if (s > r)
	{
		s = r;
		outangle = ar;
	}
	if (outangle&1)
		outangle = 0x40;
	return s;
}
char XeObject::CheckRightCeiling()
{
	char s, r;
	char as, ar;
	r = FindWall(x + collision.bottom, (y - collision.left) ^ 0xFFFFF);
	ar = outangle;
	s = FindWall(x + collision.bottom, (y + collision.right) ^ 0xFFFFF);
	as = outangle;

	if (s > r)
	{
		s = r;
		outangle = ar;
	}
	if (outangle&1)
		outangle = -0x40;
	return s;
}
char XeObject::CheckLeftWall()
{
	char r = FindWall((x - collision.wallleft) ^ 0xFFFFF, y, 1, false);
	if (outangle&1)
		outangle = 0x40;
	return r;
}
char XeObject::CheckRightWall()
{
	char r = FindWall(x + collision.wallright, y);
	if (outangle&1)
		outangle = -0x40;
	return r;
}
void XeObject::CheckWallsOnGround()
{
	char a, r;
	if (char(angle + 0x40) < 0)
		return;
	if (inertia == 0) return;
	a = (inertia > 0 ? -0x40 : 0x40) + angle;

	r = CalcRoomInFront(a);
	if (r >= 0) return;

	switch(u8((a+0x20)&0xC0))
	{
	case 0x00:
		y += (r<<16);
		break;
	case 0x40:
		x -= (r<<16);
		inertia = 0;
		Status.pushing = 1;
		break;
	case 0x80:
		y -= (r<<16);
		break;
	case 0xC0:
		x += (r<<16);
		inertia = 0;
		Status.pushing = 1;
		break;
	}
}
char XeObject::CalcRoomInFront(char angle)
{
	char r = 0;
	char bkpangle = angle;
	/*angle = (0x40 | angle) + 0x20;
	if (angle >= 0)
	{
		angle |= 0x40;
		if (angle < 0)
			angle++;
		angle += 0x1F;
	}
	else
	{
		angle = 0x40;
		if (angle < 0)
			angle--;
		angle += 0x20;
	}*/

	PFloat t_x = x;
	PFloat t_y = y;
	PFloat t_px = prevx;
	PFloat t_py = prevy;
	Move();

	switch(u8(angle&0xC0))
	{
	case 0x00:
		r = FindFloor(x + collision.wallright, y);
		if (bkpangle&1)
			outangle = 0x00;
	case 0x40:
		if (!(angle&0x38))
			y += 0x80000;
		r = CheckLeftWall();
		break;
	case 0x80:
		r = CheckSlopeDist();
		break;
	case 0xC0:
		if (!(angle&0x38))
			y += 0x80000;
		r = CheckRightWall();
	}
	x = t_x;
	y = t_y;
	prevx = t_px;
	prevy = t_py;

	return r;
}
char XeObject::CalcRoomOverHead(char angle)
{
	switch(u8((angle+0x20)&0xC0))
	{
	case 0x80:
		return CheckFloor();
	case 0xC0:
		return CheckLeftCeiling();
	case 0x00:
		return CheckCeiling();
	case 0x40:
		return CheckRightCeiling();
	}
	return 0;
}
char XeObject::CheckSlopeDist()
{
	char r = FindFloor(x, (y - collision.wallleft) ^ 0xFFFFF, true, false);
	if (outangle&1)
		outangle = (char)0x80;
	return r;
}

// Runtimes
void XeObject::RuntimeDo()
{
	XeObject_PrintdEventRuntime(0, NULL);
}
void XeObject::RuntimeCreated()
{
	XeObject_PrintdEventRuntime(1, NULL);
}
void XeObject::RuntimeDestroyed()
{
	XeObject_PrintdEventRuntime(2, NULL);
}
void XeObject::RuntimeVisible()
{
	XeObject_PrintdEventRuntime(3, NULL);
}
void XeObject::RuntimeLost()
{
	XeObject_PrintdEventRuntime(4, NULL);
}
void XeObject::RuntimeCollisionField(int collision)
{
	XeObject_PrintdEventRuntime(5, NULL);
}
void XeObject::RuntimeCollisionObject(XeObject*)
{
	XeObject_PrintdEventRuntime(6, NULL);
}

void XeObject::AngleMove()
{
	char ar, as;
	const int fieldmagnet = 0x0E;
	char prevangle = angle;

	// Adjust angle
	ar = as = 3;
	if ((char)(angle + 0x20) < 0)
	{
		prevangle = angle;
		if (prevangle < 0)
			prevangle--;
		prevangle += 0x20;
	}
	else
	{
		prevangle = angle;
		if (prevangle < 0)
			prevangle++;
		prevangle += 0x1F;
	}
	switch(prevangle & 0xC0)
	{
	case 0x00: WalkHD(); break;
	case 0x40: WalkVL(); break;
	case 0x80: WalkHU(); break;
	case 0xC0: WalkVR(); break;
	}
	return;
}
void XeObject::DoCollision()
{
	char r;
	unsigned char a;
	a = CalcAngle(speedx/256, speedy/256);
	a = (a - 0x20) & 0xC0;
	outangle = a;
	switch(a)
	{
	case 0x40:
		goto HitLeftWall;
	case 0x80:
		goto HitCeilingAndWalls;
	case 0xC0:
		goto HitRightWall;
	}

	r = CheckLeftWall();
	if (r < 0)
	{
		COLLISION_MOVE(x, -r);
		speedx = 0;
	}
	r = CheckRightWall();
	if (r < 0)
	{
		COLLISION_MOVE(x, r);
		speedx = 0;
	}

	r = CheckFloor();
	if (r >= 0)  return;
	COLLISION_MOVE(y, r);
	angle = outangle;
	ResetOnFloor();
	if ( ((outangle + 0x20) & 0x40) != 0 )
	{
		speedx = 0;
		if (speedy > 0xFC000)
			speedy = 0xFC000;
	}
	else if ( ((outangle + 0x10) & 0x20) == 0 )
	{
		speedy = 0;
		inertia = speedx;
		return;
	}
	else speedy /= 2;
	inertia = speedy;
	if (outangle < 0)
		inertia = -inertia;
	return;

HitLeftWall:
	r = CheckLeftWall();
	if (r >= 0)
	{
		r = CheckCeiling();
		if (r >= 0)
		{
			if (speedy >= 0)
			{
				r = CheckFloor();
				if (r < 0)
				{
					COLLISION_MOVE(y, r);
					angle = outangle;
					ResetOnFloor(); // 0
					speedy = 0;
					inertia = speedx;
				}
			}
		}
		else
		{
			COLLISION_MOVE(y, -r);
			if (speedy < 0)
				speedy = 0;
		}
	}
	else
	{
		COLLISION_MOVE(x, -r);
		speedx = 0;
		inertia = speedy;
	}
	return;

HitCeilingAndWalls:
	r = CheckLeftWall();
	if (r < 0)
	{
		COLLISION_MOVE(x, -r);
		speedx = 0;
	}
	r = CheckRightWall();
	if (r < 0)
	{
		COLLISION_MOVE(x, r);
		speedx = 0;
	}
	r = CheckCeiling();
	if (r < 0)
	{
		COLLISION_MOVE(y, -r);
		if ((outangle+0x20)&0x40)
		{
			angle = outangle;
			inertia = speedy;
			ResetOnFloor();
			if (angle < 0)
				inertia = -inertia;
		}
		else
		{
			speedy = 0;
		}
	}
	return;

HitRightWall:
	r = CheckRightWall();
	if (r >= 0)
	{
		r = CheckCeiling();
		if (r >= 0)
		{
			if (speedy >= 0)
			{
				r = CheckFloor();
				if (r < 0)
				{
					COLLISION_MOVE(y, r);
					angle = outangle;
					speedy = 0;
					inertia = speedx;
					ResetOnFloor(); // 0
				}
			}
		}
		else
		{
			COLLISION_MOVE(y, -r);
			if (speedy < 0)
				speedy = 0;
		}
	}
	else
	{
		COLLISION_MOVE(x, r);
		speedx = 0;
		inertia = speedy;
	}
	return;
}