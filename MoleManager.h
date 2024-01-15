#pragma once
#include "Mole.h"
#include <vector>
#include "Timer.h"
#include <unordered_map>
#include "Define.h"
#include "DragAndDropObject.h"

class MoleManager
{
private:
	//���O���z��
	std::vector<std::shared_ptr<Mole>> mole;

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

	//�}�E�X���W
	Object::Location mousePoint;

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
	MoleManager(int gamemode,std::shared_ptr<DragAndDropObject>dragObject);
	~MoleManager();

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

