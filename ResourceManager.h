#pragma once

#include <unordered_map>
#include <memory>
#include <string>

//�摜���}�N��
namespace imagetype
{
	const int mouse = 0;
	const int cat = 1;
}

//�t�H���g���}�N��
namespace fontname
{
	const int text = 0;
	const int mainUi = 1;
	const int result = 2;
}

class ResourceManager
{
public:
	//�t�H���g���
	struct FontInfo
	{
		//�t�H���g�̖��O
		std::string fontName;
		//�t�H���g�̑傫��
		int size;
		//�t�H���g�̑���
		int thick;
		//�t�H���g�̃^�C�v
		int fontType;
	};

private:
	//�摜�i�[�z��
	static std::unordered_map<short, std::shared_ptr<int>> imageContainer;

	//�t�H���g�i�[�z��
	static std::unordered_map<short, std::shared_ptr<int>> fontContainer;

public:
	ResourceManager();
	~ResourceManager();

	//�摜�ǂݍ��݁A�擾�֐�
	static std::shared_ptr<int>LoadImages(short imageId);

	//�t�H���g�ǂݍ��݁A�擾�֐�
	static std::shared_ptr<int> LoadFont(short fontId);
};

