#include "oval_button.h"
#include "DxLib.h"

OvalButton::OvalButton(float x, float y, float rx, float ry, int posnum, int color, bool fill, const char* text, int fontSize)
	: x(x), y(y), rx(rx), ry(ry), posnum(posnum), color(color), fill(fill), text(text)
{
	fontHandle = CreateFontToHandle("UDƒfƒWƒ^ƒ‹‹³‰È‘‘Ì", fontSize,2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, -1);
}

OvalButton::~OvalButton()
{
	DeleteFontToHandle(fontHandle);
}

void OvalButton::Draw() const
{
	if (fill == true) {
		DrawOvalAA(x, y, rx + 1, ry + 1, posnum, color + 80, false);
	}
	DrawOvalAA(x, y, rx, ry, posnum, color, fill);
	const int textX = x - GetDrawFormatStringWidthToHandle(fontHandle, text) / 2;
	const int textY = y - GetFontSizeToHandle(fontHandle) / 2;

	DrawStringToHandle(textX, textY, text, 0xffffff, fontHandle);
}

bool OvalButton::Update()
{
	int x, y;
	int mouse = GetMousePoint(&x, &y);

	color++;

	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		if (x > this->x - rx && x < this->x + rx && y > this->y - ry && y < this->y + ry)
		{
			//color += 20;
			return true;
		}
		else
		{
			//color = 0xffffff;
		}
	}
	else
	{
		//color = 0xffffff;
	}

	return false;
}
