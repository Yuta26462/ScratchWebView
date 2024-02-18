#pragma once
#include <DxLib.h>

#include "AbstractScene.h"
#include "MouseManager.h"
#include "DragAndDropObject.h"
#include "Define.h"
#include <string>

class GameMain :public AbstractScene
{
private:
	//�Q�[�����[�h
	int gameMode;

	int previousMouseInput; // �O�t���[���̃}�E�X���͏�Ԃ��L�^
	int currentMouseInput;  // ���݂̃t���[���̃}�E�X���͏�Ԃ��L�^
	int ignoreMouseInputFrames; // �}�E�X���͂𖳎�����t���[������ݒ�

	std::shared_ptr<int> bgm; // BGM�̃n���h��
	std::shared_ptr<int> button_click; // SE�̃n���h��


	std::shared_ptr<DragAndDropObject>dragObject;
	std::unique_ptr<MouseManager>mouseManager;

	//�^�C�}�[�I�u�W�F�N�g
	std::unique_ptr<Timer> timer;
	//��������
	const float timeLimit = 30.0f;

	//�t�H���g�n���h���i�[�ϐ�
	std::unordered_map<short, std::shared_ptr<int>> fonts;

	//�������ԂɒB�������ǂ���
	bool isTimeUp;

	//�������W
	//Object::Location centerLocation;
	
	//�Q�[��������ʂ��ǂ���
	bool isHelpTime;

	std::string helpText;

	bool ones;

	// �}�E�X�̍��N���b�N�������ꂽ���ǂ���
	bool IsMouseLeftClicked() const
	{
		// ���͖����t���[����0���傫���ꍇ�́A���͂𖳎�
		if (ignoreMouseInputFrames > 0) {
			return false; // ���͂𖳎�
		}

		// ���݂̃t���[���ō��N���b�N����Ă��邩�ǂ���
		const bool isLeftButtonPressedNow = (currentMouseInput & MOUSE_INPUT_LEFT) != 0;
		// �O�t���[���ō��N���b�N����Ă��Ȃ��������ǂ���
		const bool wasLeftButtonNotPressedBefore = (previousMouseInput & MOUSE_INPUT_LEFT) == 0;

		// ���݂̃t���[���ō��N���b�N����Ă��āA�O�t���[���ō��N���b�N����Ă��Ȃ�������true��Ԃ�
		return isLeftButtonPressedNow && wasLeftButtonNotPressedBefore;
	}

	void MouseInputUpdate()
	{
		// ���͖����t���[����0���傫���ꍇ�́A�t���[�������炷
		if (ignoreMouseInputFrames > 0)
		{
			ignoreMouseInputFrames--;
		}

		// �O�t���[���̏�Ԃ��X�V
		previousMouseInput = currentMouseInput;
		// ���݂̃}�E�X��Ԃ��擾
		currentMouseInput = GetMouseInput();
	}

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
