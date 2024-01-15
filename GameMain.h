#pragma once
#include "AbstractScene.h"
#include "MoleManager.h"
#include "DragAndDropObject.h"
#include "Define.h"
#include <string>

class GameMain :public AbstractScene
{
private:
	//ゲームモード
	int gameMode;

	std::shared_ptr<DragAndDropObject>dragObject;
	std::unique_ptr<MoleManager>moleManager;

	//タイマーオブジェクト
	std::unique_ptr<Timer> timer;
	//制限時間
	const float timeLimit = 30.0f;

	//フォントハンドル格納変数
	std::unordered_map<short, std::shared_ptr<int>> fonts;

	//制限時間に達したかどうか
	bool isTimeUp;

	//中央座標
	Object::Location centerLocation;
	
	//ゲーム説明画面かどうか
	bool isHelpTime;

	std::string helpText;

	bool ones;

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
