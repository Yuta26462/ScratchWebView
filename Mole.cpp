#include "Mole.h"
#include "DxLib.h"
#include "ResourceManager.h"

Mole::Mole(Location spawnLocation)
{
	location = spawnLocation;
	size = 80;
	image = ResourceManager::LoadImages(imagetype::mouse);
}

Mole::~Mole()
{

}

void Mole::Update()
{

}
