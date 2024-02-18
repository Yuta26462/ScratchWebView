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
	//ゲームモード
	int gameMode;

	int previousMouseInput; // 前フレームのマウス入力状態を記録
	int currentMouseInput;  // 現在のフレームのマウス入力状態を記録
	int ignoreMouseInputFrames; // マウス入力を無視するフレーム数を設定

	std::shared_ptr<int> bgm; // BGMのハンドル
	std::shared_ptr<int> button_click; // SEのハンドル


	std::shared_ptr<DragAndDropObject>dragObject;
	std::unique_ptr<MouseManager>mouseManager;

	//タイマーオブジェクト
	std::unique_ptr<Timer> timer;
	//制限時間
	const float timeLimit = 30.0f;

	//フォントハンドル格納変数
	std::unordered_map<short, std::shared_ptr<int>> fonts;

	//制限時間に達したかどうか
	bool isTimeUp;

	//中央座標
	//Object::Location centerLocation;
	
	//ゲーム説明画面かどうか
	bool isHelpTime;

	std::string helpText;

	bool ones;

	// マウスの左クリックが押されたかどうか
	bool IsMouseLeftClicked() const
	{
		// 入力無視フレームが0より大きい場合は、入力を無視
		if (ignoreMouseInputFrames > 0) {
			return false; // 入力を無視
		}

		// 現在のフレームで左クリックされているかどうか
		const bool isLeftButtonPressedNow = (currentMouseInput & MOUSE_INPUT_LEFT) != 0;
		// 前フレームで左クリックされていなかったかどうか
		const bool wasLeftButtonNotPressedBefore = (previousMouseInput & MOUSE_INPUT_LEFT) == 0;

		// 現在のフレームで左クリックされていて、前フレームで左クリックされていなかったらtrueを返す
		return isLeftButtonPressedNow && wasLeftButtonNotPressedBefore;
	}

	void MouseInputUpdate()
	{
		// 入力無視フレームが0より大きい場合は、フレームを減らす
		if (ignoreMouseInputFrames > 0)
		{
			ignoreMouseInputFrames--;
		}

		// 前フレームの状態を更新
		previousMouseInput = currentMouseInput;
		// 現在のマウス状態を取得
		currentMouseInput = GetMouseInput();
	}

public:
	GameMain(int gamemode);
	~GameMain();

	AbstractScene* Update() override;
	void Draw() const override;

	//タイアップにする
	std::function<void()>SetTimeUp = [&]()
	{
		isTimeUp = !isTimeUp;
	};
};
