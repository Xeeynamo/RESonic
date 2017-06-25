#include "XeObject.h"

class Obj0010_Ring : public XeObject
{
private:
	bool ingame;
public:
	Obj0010_Ring();
	~Obj0010_Ring();
	virtual void Do();
	virtual void CollisionObject(XeObject*);
};