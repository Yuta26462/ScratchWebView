#pragma once

#include <unordered_map>
#include <memory>
#include <string>

//画像名マクロ
namespace imagetype
{
	const int mouse = 0;
	const int cat = 1;
}

//音声名マクロ
namespace soundtype
{
	const int title_bgm = 1;
	const int game_main_bgm = 2;
	const int click = 3;
	const int drag_and_drop= 4;
	const int button_click = 5;
}

//フォント名マクロ
namespace fontname
{
	const int text = 0;
	const int mainUi = 1;
	const int result = 2;
}

class ResourceManager
{
public:
	//フォント情報
	struct FontInfo
	{
		//フォントの名前
		std::string fontName;
		//フォントの大きさ
		int size;
		//フォントの太さ
		int thick;
		//フォントのタイプ
		int fontType;
	};

private:
	//画像格納配列
	static std::unordered_map<short, std::shared_ptr<int>> imageContainer;

	//音声格納配列
	static std::unordered_map<short, std::shared_ptr<int>> soundContainer;

	//フォント格納配列
	static std::unordered_map<short, std::shared_ptr<int>> fontContainer;

public:
	ResourceManager();
	~ResourceManager();

	//画像読み込み、取得関数
	static std::shared_ptr<int>LoadImages(short imageId);

	//音声読み込み、取得関数
	static std::shared_ptr<int>LoadSounds(short soundId);

	//フォント読み込み、取得関数
	static std::shared_ptr<int> LoadFont(short fontId);
};

