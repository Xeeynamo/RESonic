#pragma once
#include "XeBase.h"

class ObjectHitboxRect
{
public:
	PFloat left, right, top, bottom, wallleft, wallright;

	ObjectHitboxRect(short left = 0, short right = 0, short top = 0, short bottom = 0, short wallleft = 0, short wallright = 0)
	{
		this->left = left<<16;
		this->right = right<<16;
		this->top = top<<16;
		this->bottom = bottom<<16;
		this->wallleft = wallleft<<16;
		this->wallright = wallright<<16;
	}
	ObjectHitboxRect &operator = (const ObjectHitboxRect &dest)
	{
		if (this != &dest)
		{
			this->left = dest.left;
			this->right = dest.right;
			this->top = dest.top;
			this->bottom = dest.bottom;
			this->wallleft = dest.wallleft;
			this->wallright = dest.wallright;
		}
		return *this;
	}
	bool operator == (const ObjectHitboxRect& o)
	{
		return (this->left == o.left) &&
			(this->right == o.right) &&
			(this->top == o.top) &&
			(this->bottom == o.bottom) &&
			(this->wallleft == o.wallleft) &&
			(this->wallright == o.wallright);
	}
	bool operator != (const ObjectHitboxRect& o)
	{
		return (this->left != o.left) ||
			(this->right != o.right) ||
			(this->top != o.top) ||
			(this->bottom != o.bottom) ||
			(this->wallleft != o.wallleft) ||
			(this->wallright != o.wallright);
	}

	short Left()		{ return left / 0x10000; }
	short Right()		{ return right / 0x10000; }
	short Top()			{ return top / 0x10000; }
	short Bottom()		{ return bottom / 0x10000; }
	short WallLeft()	{ return left / 0x10000; }
	short WallRight()	{ return right / 0x10000; }
};