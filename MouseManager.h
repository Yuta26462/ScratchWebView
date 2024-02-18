#pragma once
#include "Mouse.h"
#include <vector>
#include "Timer.h"
#include <unordered_map>
#include "Define.h"
#include "DragAndDropObject.h"

class MouseManager
{
private:
	std::shared_ptr<int> click; // SE�̃n���h��
	std::shared_ptr<int> drag_and_drop; // SE�̃n���h��

	//�l�Y�~�z��
	std::vector<std::shared_ptr<Mouse>> mouse;

	//�h���b�O�I�u�W�F�N�g
	std::shared_ptr<DragAndDropObject>dragObject;

	//�X�|�[���ꏊ���
	Object::Location spawnPoint[9];

	//�o�����z��
	std::vector<Object::Location> AppearanceInfomation;

	//�^�C�}�[�I�u�W�F�N�g
	std::unique_ptr<Timer> timer;

	//�X�|�[�������邩�ǂ���
	bool isExecutionSpawn;

	//�}�E�X�J�[�\�����W
	Object::Location cursorPoint;

	//�O��̃}�E�X���͏��
	int oldMouseInput;

	//�Ώۂ��擾������
	int collectCount;
	
	//1�x�ɃX�|�[�������鐔
	int spawnVolume;

	//�Q�[�����[�h
	int gameMode;

	const int mouseSize = 80;

	//��ʂ̑傫��
	Object::Location windowSize;

public:
	MouseManager(int gamemode,std::shared_ptr<DragAndDropObject>dragObject);
	~MouseManager();

	void Update();
	void Draw() const;

	//�X�|�[���֐�
	void Spawn(int spawnVolume);
	//���������֐�
	Object::Location GetRandomNumber();

	int GetCollectCount() { return collectCount; }

	//�o���\�ɂ���֐�
	std::function<void()>isSpawn = [&]()
	{
		isExecutionSpawn = true;
	};
};

