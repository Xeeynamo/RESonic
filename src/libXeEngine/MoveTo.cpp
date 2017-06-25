#include "MoveTo.h"
#include "Node.h"

XeEngine::Actions::MoveTo::MoveTo(Point& p, float speed)
{
	dst = p;
	this->speed = speed;
	speedX = 0.0f;
	speedY = 0.0f;
	frameTotal = (short)(speed * 60.0f);
	frameCurrent = 0;
}
bool XeEngine::Actions::MoveTo::Do()
{
	if (!node) return false;
	if (frameCurrent >= frameTotal)
	{
		cur.x = dst.x;
		cur.y = dst.y;
		node->SetPoint(cur);
		return false;
	}
	frameCurrent++;
	cur.x += speedX;
	cur.y += speedY;
	node->SetPoint(cur);
	return true;
}
void XeEngine::Actions::MoveTo::AttachNode(Node* node)
{
	Action::AttachNode(node);
	node->GetPoint(cur);

	speedX = (dst.x - cur.x) / (speed * 60.0f);
	speedY = (dst.y - cur.y) / (speed * 60.0f);
}