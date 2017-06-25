#include "XeObject.h"
#include <stdio.h>

void XeObject_PrintdEventAnim(short anim)
{

}
void XeObject_PrintdEventRuntime(short runtime, void *param)
{
	switch(runtime)
	{
	case 0:
		printf("RuntimeDo");
		break;
	case 1:
		printf("RuntimeCreated");
		break;
	case 2:
		printf("RuntimeDestroyed");
		break;
	case 3:
		printf("RuntimeVisible");
		break;
	case 4:
		printf("RuntimeLost");
		break;
	case 5:
		printf("RuntimeCollisionField");
		printf(": %s %s %s %s",
			(int)param & 1 ? "WallLeft" : "",
			(int)param & 1 ? "WallRight" : "",
			(int)param & 1 ? "Floor" : "",
			(int)param & 1 ? "Top" : "");
		break;
	case 6:
		printf("RuntimeCollisionObject");
		printf(" Tag %p", ((XeObject*)param));
		break;
	}
	printf("\n");
}