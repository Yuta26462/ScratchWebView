#include "MouseManager.h"
#include <iostream>
#include <random>
#include "DxLib.h"
#include <Windows.h>

#include "ResourceManager.h"

MouseManager::MouseManager(int gamemode, std::shared_ptr<DragAndDropObject>dragObject)
{

	click = ResourceManager::LoadSounds(soundtype::click);
	drag_and_drop = ResourceManager::LoadSounds(soundtype::drag_and_drop);

	gameMode = gamemode;

	if (dragObject != nullptr)
	{
		this->dragObject = dragObject;
	}

	int i = 0;
	int j = 0;
	for (auto& spPoint : spawnPoint)
	{
		spPoint.x = i * 200 + 100;
		spPoint.y = j * 150 + 100;
		j++;
		if (2 < j)
		{
			j = 0;
			i++;
		}
	}

	timer = std::make_unique<Timer>();
	isExecutionSpawn = false;

	cursorPoint = { 0,0 };

	oldMouseInput = 0;

	collectCount = 0;

	spawnVolume = 1;
}

MouseManager::~MouseManager()
{
	AppearanceInfomation.clear();
	AppearanceInfomation.shrink_to_fit();

	mouse.clear();
	mouse.shrink_to_fit();
}

void MouseManager::Update()
{
	if (gameMode == gamemode::clickPractice)
	{
		//マウスカーソル座標の取得
		GetMousePoint(&cursorPoint.x, &cursorPoint.y);
	}

	//何もいなければ1秒毎にスポーンさせる
	if (mouse.size() == 0 && isExecutionSpawn == false)
	{
		timer->LoopTimer(1.0f, &isSpawn);

		if (isExecutionSpawn == true)
		{
			Spawn(spawnVolume);
			isExecutionSpawn = false;
		}
	}
	
	for (int i=0;i<mouse.size();i++)
	{
		mouse.at(i)->Update();

		Object::Location tLocation = mouse.at(i)->GetLocation();

		switch (gameMode)
		{
		case gamemode::clickPractice:

			//対象をクリックすると削除する
			if ((((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && oldMouseInput == 0)
				&& tLocation.x <= cursorPoint.x && cursorPoint.x <= tLocation.x + mouseSize && tLocation.y <= cursorPoint.y && cursorPoint.y <= tLocation.y + mouseSize)
			{
				// SEを再生
				PlaySoundMem(*click, DX_PLAYTYPE_BACK, TRUE);

				//取得数を格納
				collectCount++;

				//10スポーン分獲得したらスポーン数を増加
				if (collectCount % (10 * spawnVolume + 10) == 0)
				{
					spawnVolume++;
				}

				mouse.erase(mouse.begin() + i);
				AppearanceInfomation.erase(AppearanceInfomation.begin() + i);
				i--;

			}
			break;

		case gamemode::dragPractice:

			Object::Location dLocation = dragObject->GetLocation();
			int dSize;
			dSize = dragObject->GetSize();

			if (dragObject->GetStatus() == DragAndDropObject::Status::Drop
				&& tLocation.x <= dLocation.x + dSize && dLocation.x <= tLocation.x + mouseSize
				&& tLocation.y <= dLocation.y + dSize && dLocation.y <= tLocation.y + mouseSize)
			{
				// SEを再生
				PlaySoundMem(*drag_and_drop, DX_PLAYTYPE_BACK, TRUE);

				//取得数を格納
				collectCount++;

				mouse.erase(mouse.begin() + i);
				AppearanceInfomation.erase(AppearanceInfomation.begin() + i);
				i--;
			}

			break;

		default:
			break;
		}

		
	}

	oldMouseInput = GetMouseInput();
}

void MouseManager::Draw() const
{
	for (auto& mol : mouse)
	{
		mol->Draw();
	}
}

void MouseManager::Spawn(int spawnVolume)
{
	for (int i = 0; i < spawnVolume; i++)
	{
		Object::Location spawnLocation;
		spawnLocation = GetRandomNumber();

		mouse.push_back(std::make_shared<Mouse>(spawnLocation));
	}
}

Object::Location MouseManager::GetRandomNumber()
{
	Object::Location spawnPoint;

	//乱数の生成範囲
	std::random_device rnd;
	std::mt19937 mt(rnd());

	int count = 0;
	//重複しているかどうか
	bool isDuplication = true;

	//既に出現している場所と被っていたら繰り返す
	while (isDuplication == true)
	{
		std::uniform_int_distribution<> randNumX(80,1180);
		spawnPoint.x = randNumX(mt);

		std::uniform_int_distribution<> randNumY(80,600);
		spawnPoint.y = randNumY(mt);

		isDuplication = false;

		if (gameMode == gamemode::dragPractice
			&& dragObject->GetLocation().x - dragObject->GetSize() <= spawnPoint.x && spawnPoint.x <= dragObject->GetLocation().x + dragObject->GetSize() * 2
			&& dragObject->GetLocation().y - dragObject->GetSize() <= spawnPoint.y && spawnPoint.y <= dragObject->GetLocation().y + dragObject->GetSize() * 2)
		{
			isDuplication = true;
		}

		if (isDuplication == false)
		{
			for (auto& apInfo : AppearanceInfomation)
			{
				if (apInfo.x == spawnPoint.x && apInfo.y == spawnPoint.y)
				{
					isDuplication = true;
				}
			}
		}
	}

	AppearanceInfomation.push_back(spawnPoint);

	return spawnPoint;
}
