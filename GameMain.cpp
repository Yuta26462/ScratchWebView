#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "ResourceManager.h"
#include <fstream>


GameMain::GameMain(int gamemode)
	:isTimeUp(false), isHelpTime(true), previousMouseInput(0), currentMouseInput(0), ones(true), ignoreMouseInputFrames(10)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	fonts[fontname::result] = ResourceManager::LoadFont(fontname::result);
	fonts[fontname::mainUi] = ResourceManager::LoadFont(fontname::mainUi);
	fonts[fontname::text] = ResourceManager::LoadFont(fontname::text);

	bgm = ResourceManager::LoadSounds(soundtype::game_main_bgm);
	button_click = ResourceManager::LoadSounds(soundtype::button_click);

	//�Q�[�����[�h�̐ݒ�
	gameMode = gamemode;
	std::ifstream ifs;

	switch (gameMode)
	{
	case gamemode::clickPractice:
		mouseManager = std::make_unique<MouseManager>(gamemode::clickPractice, nullptr);

		break;

	case gamemode::dragPractice:
		dragObject = std::make_shared<DragAndDropObject>();

		mouseManager = std::make_unique<MouseManager>(gamemode::dragPractice, dragObject);

		break;

	default:
		break;
	}

	while (std::getline(ifs, helpText)) {}

	timer = std::make_unique<Timer>();

	SetBackgroundColor(209, 186, 212);

	//BGM�̍Đ�
	PlaySoundMem(*bgm, DX_PLAYTYPE_LOOP, FALSE);
}

GameMain::~GameMain()
{
	//�V�[���̐؂�ւ����s��ꂽ��BGM���~�߂�
	StopSoundMem(*bgm);
}

AbstractScene* GameMain::Update()
{
	// �}�E�X�̓��͏�Ԃ��X�V
	MouseInputUpdate();

	if (isHelpTime == true)
	{
		if (IsMouseLeftClicked())
		{
			// SE�Đ����Đ�����Ă��Ȃ��ꍇ�ɍĐ�����
			if (!CheckSoundMem(*button_click)) {
				PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
			}
			// ������ʂ��\���ɂ���
			isHelpTime = false;
		}
	}
	else
	{
		if (isTimeUp == false)
		{
			timer->LoopTimer(timeLimit, &SetTimeUp);

			mouseManager->Update();

			//�Q�[�����[�h�ɂ���ď�����ς���
			switch (gameMode)
			{
			case gamemode::clickPractice:
				break;

			case gamemode::dragPractice:
				dragObject->Update();
				break;

			default:
				break;
			}
		}
		else
		{
			// �}�E�X���͂�10�t���[����������
			//ignoreMouseInputFrames = 10;
			//timer->LoopTimer(1.0f, &SetTimeUp);
			if (IsMouseLeftClicked())
			{
				// SE�Đ�
				PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
				//SE����I����Ă����ʐ��ڂ���B
				while (CheckSoundMem(*button_click)) {}
				return new Title;
			}
		}
	}

	return this;
}

void GameMain::Draw() const
{
	if (isHelpTime == true)
	{
		// �w�i�Ɏl�p���{�b�N�X��`��
		DrawBox(100, 130, 1180, 600, 0xfffbe3, TRUE);

		//�Q�[�����[�h�ɂ���ď�����ς���
		switch (gameMode)
		{
		case gamemode::clickPractice:
		{
			const std::string text = "�����ł́A�N���b�N�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�����������Ƃ��N���b�N�Ƃ����܂�\n"
				"�˂����N���b�N���ăl�Y�~�����܂������悤";
			DrawStringToHandle(GetDrawCenterX(text.c_str(), *fonts.at(fontname::mainUi)), 200, text.c_str(), 0xffffff, *fonts.at(fontname::mainUi));
			DrawStringToHandle(GetDrawCenterX("-- �N���b�N���ăX�^�[�g --", *fonts.at(fontname::mainUi)), 480,
				"-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::mainUi));
			break;
		}

		case gamemode::dragPractice:
		{
			const std::string text2 = "�����ł́A�h���b�O�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�����������܂�\n���������Ƃ��h���b�O�Ƃ����܂�\n"
				"�˂����h���b�O���ăl�Y�~�����܂������悤";
			DrawStringToHandle(GetDrawCenterX(text2.c_str(), *fonts.at(fontname::mainUi)), 170, text2.c_str(),
				0xffffff, *fonts.at(fontname::mainUi));
			DrawStringToHandle(GetDrawCenterX("-- �N���b�N���ăX�^�[�g --", *fonts.at(fontname::mainUi)), 480,
				"-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::mainUi));
			break;
		}

		default:
			break;
		}



	}
	else
	{
		if (isTimeUp == false)
		{
			DrawFormatStringToHandle(50, 50, 0xffffff, *fonts.at(fontname::mainUi), "�c�莞�ԁF%d", 30 - static_cast<int>(timer->GetElapsedTime()));
		}
		DrawFormatStringToHandle(950, 50, 0xffffff, *fonts.at(fontname::mainUi), "�߂܂������F%d", mouseManager->GetCollectCount());

		mouseManager->Draw();

		//�Q�[�����[�h�ɂ���ď�����ς���
		switch (gameMode)
		{
		case gamemode::clickPractice:

			break;

		case gamemode::dragPractice:
			dragObject->Draw();
			break;

		default:
			break;
		}
	}

	if (isTimeUp == true)
	{
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �w�i�Ɏl�p���{�b�N�X��`��
		DrawBox(100, 130, 1180, 600, 0xfffbe3, TRUE);

		DrawStringToHandle(GetDrawCenterX("TIME UP", *fonts.at(fontname::result)), 200, "TIME UP", 0xff0000, *fonts.at(fontname::result));

		const std::string resultText = "���܂������F" + std::to_string(mouseManager->GetCollectCount());
		DrawStringToHandle(GetDrawCenterX(resultText.c_str(), *fonts.at(fontname::mainUi)), 350, resultText.c_str(), 0xffffff, *fonts.at(fontname::mainUi));

		DrawStringToHandle(GetDrawCenterX("-- �N���b�N���ă^�C�g���ɖ߂� --", *fonts.at(fontname::mainUi)), 480, "-- �N���b�N���ă^�C�g���ɖ߂� --", 0xffffff, *fonts.at(fontname::mainUi));

		/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);*/
	}
}