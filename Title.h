#pragma once
#include <memory>

#include "AbstractScene.h"
#include "oval_button.h"

class Title :public AbstractScene
{
private:
	int scratchLogoImage;
	int scratchCatImage;
	int mouseImage;
	int mouseClickImage;
	std::shared_ptr<int> bgm; // BGM�̃n���h��
	std::shared_ptr<int> button_click; // SE�̃n���h��

	int fontHandle;
	int h2FontHandle;
	OvalButton* button[3];

	int animationCount;

public:
	Title();
	~Title();

	AbstractScene* Update() override;
	void Draw() const override;
};

