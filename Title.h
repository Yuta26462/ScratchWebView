#pragma once
#include "AbstractScene.h"
#include "oval_button.h"

class Title :public AbstractScene
{
private:
	int scratchLogoImage;
	int scratchCatImage;
	int mouseImage;
	int mouseClickImage;

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

