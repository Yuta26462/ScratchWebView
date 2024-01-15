#include "Object.h"
#include "DxLib.h"

void Object::Draw() const
{
	//DrawCircle(location.x, location.y, 50, 0xff0000, TRUE);
	//DrawBox(location.x, location.y, location.x + size, location.y + size, 0xff0000, TRUE);
	DrawGraph(location.x, location.y, *image, TRUE);
}
