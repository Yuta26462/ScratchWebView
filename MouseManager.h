#pragma once
#include "Mouse.h"
#include <vector>
#include "Timer.h"
#include <unordered_map>
#include "Define.h"
#include "DragAndDropObject.h"

class MouseManager
{
private:
	std::shared_ptr<int> click; // SEのハンドル
	std::shared_ptr<int> drag_and_drop; // SEのハンドル

	//ネズミ配列
	std::vector<std::shared_ptr<Mouse>> mouse;

	//ドラッグオブジェクト
	std::shared_ptr<DragAndDropObject>dragObject;

	//スポーン場所情報
	Object::Location spawnPoint[9];

	//出現情報配列
	std::vector<Object::Location> AppearanceInfomation;

	//タイマーオブジェクト
	std::unique_ptr<Timer> timer;

	//スポーンさせるかどうか
	bool isExecutionSpawn;

	//マウスカーソル座標
	Object::Location cursorPoint;

	//前回のマウス入力情報
	int oldMouseInput;

	//対象を取得した数
	int collectCount;
	
	//1度にスポーンさせる数
	int spawnVolume;

	//ゲームモード
	int gameMode;

	const int mouseSize = 80;

	//画面の大きさ
	Object::Location windowSize;

public:
	MouseManager(int gamemode,std::shared_ptr<DragAndDropObject>dragObject);
	~MouseManager();

	void Update();
	void Draw() const;

	//スポーン関数
	void Spawn(int spawnVolume);
	//乱数生成関数
	Object::Location GetRandomNumber();

	int GetCollectCount() { return collectCount; }

	//出現可能にする関数
	std::function<void()>isSpawn = [&]()
	{
		isExecutionSpawn = true;
	};
};

