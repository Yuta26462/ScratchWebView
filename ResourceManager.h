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

	//フォント格納配列
	static std::unordered_map<short, std::shared_ptr<int>> fontContainer;

public:
	ResourceManager();
	~ResourceManager();

	//画像読み込み、取得関数
	static std::shared_ptr<int>LoadImages(short imageId);

	//フォント読み込み、取得関数
	static std::shared_ptr<int> LoadFont(short fontId);
};

