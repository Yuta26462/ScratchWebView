#include "GameMain.h"
#include "DxLib.h"
#include "Title.h"
#include "ResourceManager.h"
#include <fstream>


GameMain::GameMain(int gamemode)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	fonts[fontname::result] = ResourceManager::LoadFont(fontname::result);
	fonts[fontname::mainUi] = ResourceManager::LoadFont(fontname::mainUi);
	fonts[fontname::text] = ResourceManager::LoadFont(fontname::text);

	//�Q�[�����[�h�̐ݒ�
	gameMode = gamemode;
	std::ifstream ifs;

	switch (gameMode)
	{
	case gamemode::clickPractice:
		mouseManager = std::make_unique<MouseManager>(gamemode::clickPractice,nullptr);

		break;

	case gamemode::dragPractice:
		dragObject = std::make_shared<DragAndDropObject>();

		mouseManager = std::make_unique<MouseManager>(gamemode::dragPractice,dragObject);

		break;

	default:
		break;
	}

	while (std::getline(ifs, helpText)){}

	timer = std::make_unique<Timer>();

	SetBackgroundColor(209, 186, 212);
	
	GetWindowSize(&centerLocation.x, &centerLocation.y);

	isHelpTime = true;
	isTimeUp = false;

	mouseInputLog = GetMouseInput();
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	if (isHelpTime == true)
	{
		//�}�E�X���͏��
		int mouseInput;
		int mouseX;
		int mouseY;
		int logType;

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			if (mouseInputLog == NULL)
			{
				isHelpTime = false;
			}
		}

		mouseInputLog = GetMouseInput();

		//if (GetMouseInputLog2(&mouseInput, &mouseX, &mouseY, &logType, TRUE) == 0)
		//{
		//	if ((mouseInput & MOUSE_INPUT_LEFT) != 0)
		//	{
		//		//isHelpTime = false;
		//	}
		//}
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
			timer->LoopTimer(1.0f, &SetTimeUp);

			if (isTimeUp == false && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
			{
				
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
		DrawBox(170, 120, 1110, 600, 0xfffbe3, TRUE);

		//�Q�[�����[�h�ɂ���ď�����ς���
		switch (gameMode)
		{
		case gamemode::clickPractice:
			DrawStringToHandle(180, 200, "�����ł́A", 0xffffff, *fonts.at(fontname::text));
			DrawStringToHandle(345, 200, "�N���b�N", 0xff0000, *fonts.at(fontname::text));
			DrawStringToHandle(484, 200, "�̂�񂵂イ�����܂��B", 0xffffff, *fonts.at(fontname::text));
			/*DrawStringToHandle(180, 200, "�����ł́A�N���b�N�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�����������Ƃ��N���b�N�Ƃ����܂�\n���߂�ɏo�Ă���l�Y�~���N���b�N���Ă��܂��Ă݂悤"
				, 0xffffff, *fonts.at(fontname::text));
			DrawStringToHandle(220, 300, "-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::text));*/
			break;

		case gamemode::dragPractice:
			DrawStringToHandle(100, 170, "�����ł́A�h���b�O&�h���b�v�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�������������邱�Ƃ��h���b�O�Ƃ���\n�h���b�O���Ƀ{�^������w���͂Ȃ����Ƃ��h���b�v�Ƃ����܂�\n�˂����h���b�O���ăl�Y�~�̂���ꏊ�ɘA��Ă���\n�h���b�v�����Ă˂��݂����܂������悤",
				0xffffff, *fonts.at(fontname::text));
			DrawStringToHandle(220, 300, "-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::text));
			break;

		default:
			break;
		}

		

	}
	else
	{
		if (isTimeUp == false)
		{
			int time = static_cast<int>(timer->GetElapsedTime());
			if (30 < time)
			{
				time = 30;
			}
			DrawFormatStringToHandle(0, 0, 0xffffff, *fonts.at(fontname::mainUi), "%d", 30 - time);
		}
		DrawFormatStringToHandle(600, 0, 0xffffff, *fonts.at(fontname::mainUi), "%d", mouseManager->GetCollectCount());

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
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawBox(100, 130, 540, 350, 0xfffbe3, TRUE);

		DrawStringToHandle(175, 170, "TIME UP", 0xff0000, *fonts.at(fontname::result));

		DrawFormatStringToHandle(245, 260, 0xffffff, *fonts.at(fontname::text), "���܂����� %d", mouseManager->GetCollectCount());

		DrawStringToHandle(185, 300, "-- �N���b�N���ă^�C�g���ɖ߂� --", 0xffffff, *fonts.at(fontname::text));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);
	}
}