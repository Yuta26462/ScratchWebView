#include "AbstractScene.h"

#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>

int AbstractScene::GetDrawCenterX(const char* str, int font_handle, int margin) const {
	constexpr int screenX = 1280;
	std::string string(str);
	std::istringstream stream(string);
	std::string line;
	std::vector<std::string> lines;
	int maxWidth = 0;

	// 改行で分割し、各行の前後の空白を削除
	while (std::getline(stream, line)) {
		line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // 左側の空白を削除
		line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // 右側の空白を削除
		lines.push_back(line);

		// この行の幅を取得し、最大幅を更新
		int lineWidth = GetDrawFormatStringWidthToHandle(font_handle, line.c_str());
		maxWidth = max(maxWidth, lineWidth);
	}

	// 最も長い行を基準に中央揃えのX座標を計算
	if (margin >= screenX || margin <= -screenX) {
		margin = 0;
	}

	if (font_handle == 0) {
		font_handle = DX_DEFAULT_FONT_HANDLE;
	}

	const int centerX = screenX / 2 + margin - (maxWidth / 2);
	return centerX;
};
