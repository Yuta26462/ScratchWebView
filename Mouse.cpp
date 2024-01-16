#include "Mouse.h"
#include "DxLib.h"
#include "ResourceManager.h"

Mouse::Mouse(Location spawnLocation)
{
	location = spawnLocation;
	size = 80;
	image = ResourceManager::LoadImages(imagetype::mouse);
}

Mouse::~Mouse()
{

}

void Mouse::Update()
{

}
