#pragma once
#include "AbstractScene.h"
#include "MoleManager.h"
#include "DragAndDropObject.h"
#include "Define.h"
#include <string>

class GameMain :public AbstractScene
{
private:
	//�Q�[�����[�h
	int gameMode;

	std::shared_ptr<DragAndDropObject>dragObject;
	std::unique_ptr<MoleManager>moleManager;

	//�^�C�}�[�I�u�W�F�N�g
	std::unique_ptr<Timer> timer;
	//��������
	const float timeLimit = 30.0f;

	//�t�H���g�n���h���i�[�ϐ�
	std::unordered_map<short, std::shared_ptr<int>> fonts;

	//�������ԂɒB�������ǂ���
	bool isTimeUp;

	//�������W
	Object::Location centerLocation;
	
	//�Q�[��������ʂ��ǂ���
	bool isHelpTime;

	std::string helpText;

	bool ones;

public:
	GameMain(int gamemode);
	~GameMain();

	AbstractScene* Update() override;
	void Draw() const override;

	//�^�C�A�b�v�ɂ���
	std::function<void()>SetTimeUp = [&]()
	{
		isTimeUp = !isTimeUp;
	};
};
