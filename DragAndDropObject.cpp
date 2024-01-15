#include "DragAndDropObject.h"
#include "DxLib.h"
#include "ResourceManager.h"

DragAndDropObject::DragAndDropObject()
{
	image = ResourceManager::LoadImages(imagetype::cat);

	location = { 320,240 };
	locatinStart = { 0,0 };

	size = 80;

	mousePoint = { 0,0 };
	mousePointStart = { 0,0 };
	oldMousePoint = { 0,0 };

	status = Status::Drop;

	oldMouseInput = 0;
}

DragAndDropObject::~DragAndDropObject()
{

}

void DragAndDropObject::Update()
{
	GetMousePoint(&mousePoint.x, &mousePoint.y);

	if ((((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && oldMouseInput == 0)
		&& location.x <= mousePoint.x && mousePoint.x <= location.x + size && location.y <= mousePoint.y && mousePoint.y <= location.y + size)
	{
		locatinStart = location;
		mousePointStart = mousePoint;

		status = Status::Drag;
	}

	//マウス左ボタンを離すとドロップ状態にする
	if (((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)/* && oldMouseInput != 0*/)
	{
		status = Status::Drop;
	}

	//ドラッグ状態
	if (status == Status::Drag)
	{
		Object::Location adjustmentLocation;
		adjustmentLocation.x = mousePointStart.x - locatinStart.x;
		adjustmentLocation.y = mousePointStart.y - locatinStart.y;

		location.x = mousePoint.x - adjustmentLocation.x;
		location.y = mousePoint.y - adjustmentLocation.y;
	}

	oldMousePoint = mousePoint;
	oldMouseInput = GetMouseInput();
}