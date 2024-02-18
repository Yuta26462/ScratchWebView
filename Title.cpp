#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "ResourceManager.h"
#include "WebViewScene.h"

Title::Title()
{
	mouseImage = LoadGraph("Resource/image/mouseNotClick.png");
	mouseClickImage = LoadGraph("Resource/image/mouseClick.png");
	catImage = LoadGraph("Resource/image/cat2.png");
	bgm = ResourceManager::LoadSounds(soundtype::title_bgm);
	button_click = ResourceManager::LoadSounds(soundtype::button_click);

	fontHandle = CreateFontToHandle("UDデジタル教科書体", 80, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 5);
	h2FontHandle = CreateFontToHandle("UDデジタル教科書体", 40, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 3);


	button[0] = new OvalButton(400, 300, 100, 50, 32, 0x5BECFC, true, "クリック", 20);
	button[1] = new OvalButton(400, 600, 100, 50, 32, 0x5BECFC, true, "ドラッグ", 20);
	button[2] = new OvalButton(900, 450, 150, 100, 64, 0xFE684F, true, "プログラミング", 40);
	SetBackgroundColor(248, 234, 206);

	//BGMの再生
	PlaySoundMem(*bgm, DX_PLAYTYPE_LOOP, FALSE);
}

Title::~Title()
{
	//シーンの切り替えが行われたらBGMを止める
	StopSoundMem(*bgm);

	DeleteGraph(mouseImage);
	DeleteGraph(mouseClickImage);
	DeleteGraph(catImage);
	DeleteFontToHandle(fontHandle);
	delete button[0];
	delete button[1];
	delete button[2];
}

AbstractScene* Title::Update()
{

	if(animationCount < 90){
		animationCount++;
	}
	else {
			animationCount = 0;
	}

	if (button[0]->Update())
	{
		// SE再生
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SEが鳴り終わってから画面推移する。
		while (CheckSoundMem(*button_click)) {}
		return new GameMain(gamemode::clickPractice);
	}
	
	if (button[1]->Update())
	{
		// SE再生
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SEが鳴り終わってから画面推移する。
		while (CheckSoundMem(*button_click)) {}
		return new GameMain(gamemode::dragPractice);
	}

	if (button[2]->Update())
	{
		// SE再生
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SEが鳴り終わってから画面推移する。
		while (CheckSoundMem(*button_click)) {}
		return new WebViewScene();
	}

	return this;
}

void Title::Draw() const
{
	DrawGraph(600,200, catImage, true);

	const int mouseX = 150;
	const int mouseY = 200;
	if (animationCount < 45) {
		DrawGraph(mouseX, mouseY, mouseImage, true);
	}else{
		DrawGraph(mouseX, mouseY, mouseClickImage, true);
	}
	DrawFormatString2ToHandle(180, 400, 0xffffff, 0x5BECFC, fontHandle, "マウス練習");
	button[0]->Draw();
	button[1]->Draw();
	button[2]->Draw();

	DrawFormatString2ToHandle(GetDrawCenterX("スクラッチでゲームを作ろう！", fontHandle), 100, 0xffffff, 0xFFAD45, fontHandle, "スクラッチでゲームを作ろう！");
}
