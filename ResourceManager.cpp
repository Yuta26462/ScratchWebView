#include "ResourceManager.h"
#include "DxLib.h"
#include <iostream>

std::unordered_map<short, std::shared_ptr<int>> ResourceManager::imageContainer;
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

std::shared_ptr<int> ResourceManager::LoadFont(short fontId)
{
	FontInfo fontInfo;

	switch (fontId)
	{
	case fontname::text:
		fontInfo.fontName = "UD デジタル 教科書体 N-B";
		fontInfo.size = 35;
		fontInfo.thick =3;
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

