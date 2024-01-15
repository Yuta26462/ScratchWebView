#pragma once
#include "Object.h"

class Mole :public Object
{
private:

public:
	Mole(Location spawnLocation);
	~Mole();

	void Update() override;
};

