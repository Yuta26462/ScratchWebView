#include "DxLib.h"
#include "FpsManager.h"
#include "SceneManager.h"
#include "Title.h"
#include "GameMain.h"
#include "WebViewScene.h"
#include "Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Scratch�ŃQ�[������낤�I");

	SetWindowIconID(01);

	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���

	SetDXArchiveExtension("resource");
	SetDXArchiveKeyString("map_chips90.png");

	SetAlwaysRunFlag(true);		//��ɃA�N�e�B�u�ɂ���

	ChangeWindowMode(FALSE);		// �E�B���h�E���[�h�ŋN��

	SetGraphMode(1280, 720, 32);		//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetMouseDispFlag(TRUE);

	SetDoubleStartValidFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SceneManager* sceneMng;
	FpsManager fpsManager;

	try
	{
		//sceneMng = new SceneManager((AbstractScene*)new GameMain(gamemode::clickPractice));
		//sceneMng = new SceneManager((AbstractScene*)new WebViewScene);
		sceneMng = new SceneManager((AbstractScene*)new Title());
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);
		//�t�@�C���I�[�v��
		fopen_s(&fp, "ErrLog.txt", "a");
		//�G���[�f�[�^�̏�������
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr) && ((CheckHitKey(KEY_INPUT_ESCAPE) && CheckHitKey(KEY_INPUT_RETURN)) == 0))
	{

		ClearDrawScreen();		// ��ʂ̏�����
		//�`��
		sceneMng->Draw();

		fpsManager.TimeAdjustment();

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}

	return 0;
}