#pragma once
#include "Object.h"

class DragAndDropObject : public Object
{
public:
	//ドラッグされているかドロップされたか
	enum class Status
	{
		Drag,
		Drop
	};

private:
	//ステータス
	Status status;

	//マウス座標
	Object::Location mousePoint;

	//前回のマウス入力情報
	int oldMouseInput;

	//マウスをクリックした時のオブジェクトの座標
	Object::Location locatinStart;
	//マウスをクリックしたマウスの座標
	Object::Location mousePointStart;

	//前回のマウスの座標
	Object::Location oldMousePoint;

public:
	DragAndDropObject();
	~DragAndDropObject();

	void Update() override;
	
	Status GetStatus() { return status; }
};

