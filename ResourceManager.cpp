#include "ResourceManager.h"
#include "DxLib.h"
#include <iostream>

std::unordered_map<short, std::shared_ptr<int>> ResourceManager::imageContainer;
std::unordered_map<short, std::shared_ptr<int>> ResourceManager::soundContainer;
std::unordered_map<short, std::shared_ptr<int>> ResourceManager::fontContainer;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

std::shared_ptr<int> ResourceManager::LoadImages(short imageId)
{
	if (imageContainer.find(imageId) != imageContainer.end())
	{
		return imageContainer.at(imageId);
	}

	std::string filePath = "Resource/image/";
	std::string imageName;

	switch (imageId)
	{
	case imagetype::cat:
		filePath += "cat";
		break;

	case imagetype::mouse:
		filePath += "mouse";
		break;

	default:
		break;
	}

	filePath += ".png";
	int image = LoadGraph(filePath.c_str());

	imageContainer[imageId] = std::make_shared<int>(LoadGraph(filePath.c_str()));

	return imageContainer.at(imageId);
}

std::shared_ptr<int> ResourceManager::LoadSounds(short soundId)
{
	if (soundContainer.find(soundId) != soundContainer.end())
	{
		return soundContainer.at(soundId);
	}

	std::string filePath = "Resource/sound/";
	std::string soundName;

	switch (soundId)
	{
	case soundtype::title_bgm:
		filePath += "bgm/title";
		break;

	case soundtype::game_main_bgm:
		filePath += "bgm/game_main";
		break;

	case soundtype::click:
		filePath += "se/click";
		break;

	case soundtype::drag_and_drop:
		filePath += "se/drag_and_drop";
		break;

	case soundtype::button_click:
		filePath += "se/button_click";
		break;

	default:
		break;
	}

	filePath += ".mp3";
	int sound = LoadSoundMem(filePath.c_str());

	soundContainer[soundId] = std::make_shared<int>(LoadSoundMem(filePath.c_str()));

	return soundContainer.at(soundId);
}

std::shared_ptr<int> ResourceManager::LoadFont(short fontId)
{
	FontInfo fontInfo;

	switch (fontId)
	{
	case fontname::text:
		fontInfo.fontName = "UD デジタル 教科書体 N-B";
		fontInfo.size = 15;
		fontInfo.thick = 3;
		fontInfo.fontType = DX_FONTTYPE_ANTIALIASING_EDGE_8X8;
		break;

	case fontname::mainUi:
		fontInfo.fontName = "UD デジタル 教科書体 N-B";
		fontInfo.size = 40;
		fontInfo.thick = 10;
		fontInfo.fontType = DX_FONTTYPE_ANTIALIASING_EDGE_8X8;
		break;

	case fontname::result:
		fontInfo.fontName = "UD デジタル 教科書体 N-B";
		fontInfo.size = 70;
		fontInfo.thick = 10;
		fontInfo.fontType = DX_FONTTYPE_ANTIALIASING_EDGE_8X8;
		break;

	default:
		break;
	}

	if (fontContainer.find(fontId) != fontContainer.end())
	{
		return fontContainer.at(fontId);
	}

	fontContainer[fontId] = std::make_shared<int>(CreateFontToHandle(fontInfo.fontName.c_str(), fontInfo.size, fontInfo.size, fontInfo.fontType));

	return fontContainer.at(fontId);
}

