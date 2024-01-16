#pragma once
#include "Object.h"

class Mouse :public Object
{
private:

public:
	Mouse(Location spawnLocation);
	~Mouse();

	void Update() override;
};

