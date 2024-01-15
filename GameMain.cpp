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
		moleManager = std::make_unique<MoleManager>(gamemode::clickPractice,nullptr);

		break;

	case gamemode::dragPractice:
		dragObject = std::make_shared<DragAndDropObject>();

		moleManager = std::make_unique<MoleManager>(gamemode::dragPractice,dragObject);

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
}

GameMain::~GameMain()
{
}

AbstractScene* GameMain::Update()
{
	if (isHelpTime == true)
	{
		if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		{
			isHelpTime = false;
		}
	}
	else
	{
		if (isTimeUp == false)
		{
			timer->LoopTimer(timeLimit, &SetTimeUp);

			moleManager->Update();

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
		DrawBox(80, 130, 600, 350, 0xfffbe3, TRUE);

		//�Q�[�����[�h�ɂ���ď�����ς���
		switch (gameMode)
		{
		case gamemode::clickPractice:
			/*DrawStringToHandle(100, 200, "�����ł́A�N���b�N�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�����������Ƃ��N���b�N�Ƃ����܂�\n���߂�ɏo�Ă���l�Y�~���N���b�N���Ă��܂��Ă݂悤"
				, 0xffffff, *fonts.at(fontname::text));
			DrawStringToHandle(220, 300, "-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::text));*/
			break;

		case gamemode::dragPractice:
			/*DrawStringToHandle(100, 170, "�����ł́A�h���b�O&�h���b�v�̂�񂵂イ�����܂�\n�}�E�X�̃{�^�������������邱�Ƃ��h���b�O�Ƃ���\n�h���b�O���Ƀ{�^������w���͂Ȃ����Ƃ��h���b�v�Ƃ����܂�\n�˂����h���b�O���ăl�Y�~�̂���ꏊ�ɘA��Ă���\n�h���b�v�����Ă˂��݂����܂������悤",
				0xffffff, *fonts.at(fontname::text));
			DrawStringToHandle(220, 300, "-- �N���b�N���ăX�^�[�g --", 0xffffff, *fonts.at(fontname::text));*/
			break;

		default:
			break;
		}

		

	}
	else
	{
		if (isTimeUp == false)
		{
			DrawFormatStringToHandle(0, 0, 0xffffff, *fonts.at(fontname::mainUi), "%d", 30 - static_cast<int>(timer->GetElapsedTime()));
		}
		DrawFormatStringToHandle(600, 0, 0xffffff, *fonts.at(fontname::mainUi), "%d", moleManager->GetCollectCount());

		moleManager->Draw();

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

		DrawFormatStringToHandle(245, 260, 0xffffff, *fonts.at(fontname::text), "���܂����� %d", moleManager->GetCollectCount());

		DrawStringToHandle(185, 300, "-- �N���b�N���ă^�C�g���ɖ߂� --", 0xffffff, *fonts.at(fontname::text));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);
	}
}