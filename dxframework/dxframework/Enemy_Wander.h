#pragma once

#include "Enemy_Movement.h"
#include <cstdlib>

class Enemy_Wander
{
private:
	float maxRotation;

public:
	Enemy_Wander(void);
	~Enemy_Wander(void);

	void GetSteering( Enemy_Movement* movement);

	float RandomBinomial();
};

