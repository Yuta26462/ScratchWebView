#include "MoleManager.h"
#include <iostream>
#include <random>
#include "DxLib.h"
#include <Windows.h>

MoleManager::MoleManager(int gamemode, std::shared_ptr<DragAndDropObject>dragObject)
{
	/*RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);

	windowSize.x = rect.right - rect.left;
	windowSize.y = rect.bottom - rect.top;*/

	GetWindowSize(&windowSize.x, &windowSize.y);

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

	mousePoint = { 0,0 };

	oldMouseInput = 0;

	collectCount = 0;

	spawnVolume = 1;
}

MoleManager::~MoleManager()
{
	AppearanceInfomation.clear();
	AppearanceInfomation.shrink_to_fit();

	mole.clear();
	mole.shrink_to_fit();
}

void MoleManager::Update()
{
	if (gameMode == gamemode::clickPractice)
	{
		//マウス座標の取得
		GetMousePoint(&mousePoint.x, &mousePoint.y);
	}

	//何もいなければ1秒毎にスポーンさせる
	if (mole.size() == 0 && isExecutionSpawn == false)
	{
		timer->LoopTimer(1.0f, &isSpawn);

		if (isExecutionSpawn == true)
		{
			Spawn(spawnVolume);
			isExecutionSpawn = false;
		}
	}
	
	for (int i=0;i<mole.size();i++)
	{
		mole.at(i)->Update();

		Object::Location tLocation = mole.at(i)->GetLocation();

		switch (gameMode)
		{
		case gamemode::clickPractice:

			//対象をクリックすると削除する
			if ((((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && oldMouseInput == 0)
				&& tLocation.x <= mousePoint.x && mousePoint.x <= tLocation.x + mouseSize && tLocation.y <= mousePoint.y && mousePoint.y <= tLocation.y + mouseSize)
			{
				//取得数を格納
				collectCount++;

				//10スポーン分獲得したらスポーン数を増加
				if (collectCount % (10 * spawnVolume + 10) == 0)
				{
					spawnVolume++;
				}

				mole.erase(mole.begin() + i);
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
				//取得数を格納
				collectCount++;

				mole.erase(mole.begin() + i);
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

void MoleManager::Draw() const
{
	for (auto& mol : mole)
	{
		mol->Draw();
	}
}

void MoleManager::Spawn(int spawnVolume)
{
	for (int i = 0; i < spawnVolume; i++)
	{
		Object::Location spawnLocation;
		spawnLocation = GetRandomNumber();

		mole.push_back(std::make_shared<Mole>(spawnLocation));
	}
}

Object::Location MoleManager::GetRandomNumber()
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
