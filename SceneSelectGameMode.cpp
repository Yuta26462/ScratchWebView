//#include "SceneSelectGameMode.h"
//#include "ResourceManager.h"
//#include "GameMain.h"
//#include "DxLib.h"
//
//SceneSelctGameMode::SceneSelctGameMode()
//{
//	font = ResourceManager::LoadFont(fontname::mainUi);
//	SetBackgroundColor(163, 204, 137);
//
//	textPoint[texttype::click] = { 170,230 };
//	textPoint[texttype::drag] = { 370,210 };
//}
//
//SceneSelctGameMode::~SceneSelctGameMode()
//{
//}
//
//AbstractScene* SceneSelctGameMode::Update()
//{
//	GetMousePoint(&mousePoint.x, &mousePoint.y);
//
//	if(mousePoint.x)
//
//	return this;
//}
//
//void SceneSelctGameMode::Draw() const
//{
//	DrawOval(200, 240, 70, 50, 0x00ff00, TRUE);
//	DrawOval(420, 240, 70, 50, 0x00ff00, TRUE);
//
//	DrawStringToHandle(textPoint.at(texttype::click).x, textPoint.at(texttype::click).y, "クリック", 0xffffff, *font);
//	DrawStringToHandle(textPoint.at(texttype::drag).x, textPoint.at(texttype::drag).y, "ドラッグ\n    &\nドロップ", 0xffffff, *font);
//}
