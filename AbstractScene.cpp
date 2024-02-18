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

	// ���s�ŕ������A�e�s�̑O��̋󔒂��폜
	while (std::getline(stream, line)) {
		line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // �����̋󔒂��폜
		line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // �E���̋󔒂��폜
		lines.push_back(line);

		// ���̍s�̕����擾���A�ő啝���X�V
		int lineWidth = GetDrawFormatStringWidthToHandle(font_handle, line.c_str());
		maxWidth = max(maxWidth, lineWidth);
	}

	// �ł������s����ɒ���������X���W���v�Z
	if (margin >= screenX || margin <= -screenX) {
		margin = 0;
	}

	if (font_handle == 0) {
		font_handle = DX_DEFAULT_FONT_HANDLE;
	}

	const int centerX = screenX / 2 + margin - (maxWidth / 2);
	return centerX;
};
