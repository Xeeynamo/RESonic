#include "XeObject.h"

class Obj001A_Pathswap : public XeObject
{
public:
	Obj001A_Pathswap();
	~Obj001A_Pathswap();
	virtual void Do();
	virtual void CollisionObject(XeObject*);
};