#pragma once
#include "Object.h"

class DragAndDropObject : public Object
{
public:
	//�h���b�O����Ă��邩�h���b�v���ꂽ��
	enum class Status
	{
		Drag,
		Drop
	};

private:
	//�X�e�[�^�X
	Status status;

	//�}�E�X���W
	Object::Location mousePoint;

	//�O��̃}�E�X���͏��
	int oldMouseInput;

	//�}�E�X���N���b�N�������̃I�u�W�F�N�g�̍��W
	Object::Location locatinStart;
	//�}�E�X���N���b�N�����}�E�X�̍��W
	Object::Location mousePointStart;

	//�O��̃}�E�X�̍��W
	Object::Location oldMousePoint;

public:
	DragAndDropObject();
	~DragAndDropObject();

	void Update() override;
	
	Status GetStatus() { return status; }
};

