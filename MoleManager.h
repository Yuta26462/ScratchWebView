#pragma once
#include "Mole.h"
#include <vector>
#include "Timer.h"
#include <unordered_map>
#include "Define.h"
#include "DragAndDropObject.h"

class MoleManager
{
private:
	//モグラ配列
	std::vector<std::shared_ptr<Mole>> mole;

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

	//マウス座標
	Object::Location mousePoint;

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
	MoleManager(int gamemode,std::shared_ptr<DragAndDropObject>dragObject);
	~MoleManager();

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

