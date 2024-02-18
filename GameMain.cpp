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

	//ゲームモードの設定
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

	//BGMの再生
	PlaySoundMem(*bgm, DX_PLAYTYPE_LOOP, FALSE);
}

GameMain::~GameMain()
{
	//シーンの切り替えが行われたらBGMを止める
	StopSoundMem(*bgm);
}

AbstractScene* GameMain::Update()
{
	// マウスの入力状態を更新
	MouseInputUpdate();

	if (isHelpTime == true)
	{
		if (IsMouseLeftClicked())
		{
			// SE再生が再生されていない場合に再生する
			if (!CheckSoundMem(*button_click)) {
				PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
			}
			// 説明画面を非表示にする
			isHelpTime = false;
		}
	}
	else
	{
		if (isTimeUp == false)
		{
			timer->LoopTimer(timeLimit, &SetTimeUp);

			mouseManager->Update();

			//ゲームモードによって処理を変える
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
			// マウス入力を10フレーム無視する
			//ignoreMouseInputFrames = 10;
			//timer->LoopTimer(1.0f, &SetTimeUp);
			if (IsMouseLeftClicked())
			{
				// SE再生
				PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
				//SEが鳴り終わってから画面推移する。
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
		// 背景に四角いボックスを描画
		DrawBox(100, 130, 1180, 600, 0xfffbe3, TRUE);

		//ゲームモードによって処理を変える
		switch (gameMode)
		{
		case gamemode::clickPractice:
		{
			const std::string text = "ここでは、クリックのれんしゅうをします\nマウスのボタンを押すことをクリックといいます\n"
				"ねこをクリックしてネズミをつかまえさせよう";
			DrawStringToHandle(GetDrawCenterX(text.c_str(), *fonts.at(fontname::mainUi)), 200, text.c_str(), 0xffffff, *fonts.at(fontname::mainUi));
			DrawStringToHandle(GetDrawCenterX("-- クリックしてスタート --", *fonts.at(fontname::mainUi)), 480,
				"-- クリックしてスタート --", 0xffffff, *fonts.at(fontname::mainUi));
			break;
		}

		case gamemode::dragPractice:
		{
			const std::string text2 = "ここでは、ドラッグのれんしゅうをします\nマウスのボタンを押したまま\n動かすことをドラッグといいます\n"
				"ねこをドラッグしてネズミをつかまえさせよう";
			DrawStringToHandle(GetDrawCenterX(text2.c_str(), *fonts.at(fontname::mainUi)), 170, text2.c_str(),
				0xffffff, *fonts.at(fontname::mainUi));
			DrawStringToHandle(GetDrawCenterX("-- クリックしてスタート --", *fonts.at(fontname::mainUi)), 480,
				"-- クリックしてスタート --", 0xffffff, *fonts.at(fontname::mainUi));
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
			DrawFormatStringToHandle(50, 50, 0xffffff, *fonts.at(fontname::mainUi), "残り時間：%d", 30 - static_cast<int>(timer->GetElapsedTime()));
		}
		DrawFormatStringToHandle(950, 50, 0xffffff, *fonts.at(fontname::mainUi), "捕まえた数：%d", mouseManager->GetCollectCount());

		mouseManager->Draw();

		//ゲームモードによって処理を変える
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

		// 背景に四角いボックスを描画
		DrawBox(100, 130, 1180, 600, 0xfffbe3, TRUE);

		DrawStringToHandle(GetDrawCenterX("TIME UP", *fonts.at(fontname::result)), 200, "TIME UP", 0xff0000, *fonts.at(fontname::result));

		const std::string resultText = "つかまえた数：" + std::to_string(mouseManager->GetCollectCount());
		DrawStringToHandle(GetDrawCenterX(resultText.c_str(), *fonts.at(fontname::mainUi)), 350, resultText.c_str(), 0xffffff, *fonts.at(fontname::mainUi));

		DrawStringToHandle(GetDrawCenterX("-- クリックしてタイトルに戻る --", *fonts.at(fontname::mainUi)), 480, "-- クリックしてタイトルに戻る --", 0xffffff, *fonts.at(fontname::mainUi));

		/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);*/
	}
}