//#pragma once
//#include "AbstractScene.h"
//#include <unordered_map>
//#include <memory>
//#include <windef.h>
//#include "Object.h"
//
//namespace texttype
//{
//	const int click = 0;
//	const int drag = 1;
//}
//
//class SceneSelctGameMode :public AbstractScene
//{
//private:
//	//フォントハンドル格納変数
//	std::shared_ptr<int> font;
//
//	//マウス座標
//	Object::Location mousePoint;
//	//テキストの座標
//	std::unordered_map<short,Object::Location> textPoint;
//
//public:
//	SceneSelctGameMode();
//	~SceneSelctGameMode();
//
//	AbstractScene* Update() override;
//	void Draw() const override;
//};
//
