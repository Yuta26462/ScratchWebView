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
	SetMainWindowText("Scratchでゲームを作ろう！");

	SetWindowIconID(01);

	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする

	SetDXArchiveExtension("resource");
	SetDXArchiveKeyString("map_chips90.png");

	SetAlwaysRunFlag(true);		//常にアクティブにする

	ChangeWindowMode(FALSE);		// ウィンドウモードで起動

	SetGraphMode(1280, 720, 32);		//画面サイズの設定

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetMouseDispFlag(TRUE);

	SetDoubleStartValidFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

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
		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");
		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return 0;
	}

	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr) && ((CheckHitKey(KEY_INPUT_ESCAPE) && CheckHitKey(KEY_INPUT_RETURN)) == 0))
	{

		ClearDrawScreen();		// 画面の初期化
		//描画
		sceneMng->Draw();

		fpsManager.TimeAdjustment();

		ScreenFlip();			// 裏画面の内容を表画面に反映
	}

	return 0;
}