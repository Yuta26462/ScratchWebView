#pragma once
class OvalButton
{
private:
	int scratchLogoImage;

	int fontHandle;

	float x;
	float y;
	float rx;
	float ry;
	int posnum;
	int color;
	bool fill;
	const char* text;

	short moveCount;

public:
	OvalButton() = default;
	OvalButton(float x, float y, float rx, float ry, int posnum, int color, bool fill, const char* text = "", int fontSize = 20);
	~OvalButton();
	void Draw() const;
	bool Update();
};

