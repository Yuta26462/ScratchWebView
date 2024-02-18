#include "Title.h"
#include "DxLib.h"
#include "GameMain.h"
#include "ResourceManager.h"
#include "WebViewScene.h"

Title::Title()
{
	scratchLogoImage = LoadGraph("Resource/image/Scratch_logo.png");
	mouseImage = LoadGraph("Resource/image/mouseNotClick.png");
	mouseClickImage = LoadGraph("Resource/image/mouseClick.png");
	scratchCatImage = LoadGraph("Resource/image/scratch_cat.png");
	bgm = ResourceManager::LoadSounds(soundtype::title_bgm);
	button_click = ResourceManager::LoadSounds(soundtype::button_click);

	fontHandle = CreateFontToHandle("UD�f�W�^�����ȏ���", 80, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 5);
	h2FontHandle = CreateFontToHandle("UD�f�W�^�����ȏ���", 40, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 3);


	button[0] = new OvalButton(400, 300, 100, 50, 32, 0x5BECFC, true, "�N���b�N", 20);
	button[1] = new OvalButton(400, 600, 100, 50, 32, 0x5BECFC, true, "�h���b�O", 20);
	button[2] = new OvalButton(900, 450, 150, 100, 64, 0xFE684F, true, "�v���O���~���O", 40);
	SetBackgroundColor(248, 234, 206);

	//BGM�̍Đ�
	PlaySoundMem(*bgm, DX_PLAYTYPE_LOOP, FALSE);
}

Title::~Title()
{
	//�V�[���̐؂�ւ����s��ꂽ��BGM���~�߂�
	StopSoundMem(*bgm);
	DeleteSoundMem(*bgm);
	DeleteSoundMem(*button_click);

	DeleteGraph(scratchLogoImage);
	DeleteGraph(mouseImage);
	DeleteGraph(mouseClickImage);
	DeleteGraph(scratchCatImage);
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
		// SE�Đ�
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SE����I����Ă����ʐ��ڂ���B
		while (CheckSoundMem(*button_click)) {}
		return new GameMain(gamemode::clickPractice);
	}
	
	if (button[1]->Update())
	{
		// SE�Đ�
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SE����I����Ă����ʐ��ڂ���B
		while (CheckSoundMem(*button_click)) {}
		return new GameMain(gamemode::dragPractice);
	}

	if (button[2]->Update())
	{
		// SE�Đ�
		PlaySoundMem(*button_click, DX_PLAYTYPE_BACK, TRUE);
		//SE����I����Ă����ʐ��ڂ���B
		while (CheckSoundMem(*button_click)) {}
		return new WebViewScene();
	}

	return this;
}

void Title::Draw() const
{
	DrawGraph(60,70, scratchLogoImage, true);
	DrawGraph(600,200, scratchCatImage, true);

	const int mouseX = 150;
	const int mouseY = 200;
	if (animationCount < 45) {
		DrawGraph(mouseX, mouseY, mouseImage, true);
	}else{
		DrawGraph(mouseX, mouseY, mouseClickImage, true);
	}
	DrawFormatString2ToHandle(180, 400, 0xffffff, 0x5BECFC, fontHandle, "�}�E�X���K");
	button[0]->Draw();
	button[1]->Draw();
	button[2]->Draw();

	int x = 1280 / 2 - GetDrawFormatStringWidthToHandle(fontHandle, "�ŃQ�[������낤�I") / 2;
	DrawFormatString2ToHandle(x + 200, 100, 0xffffff, 0xFFAD45, fontHandle, "�ŃQ�[������낤�I");
}
