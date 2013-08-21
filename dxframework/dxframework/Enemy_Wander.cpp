#include "Enemy_Wander.h"


Enemy_Wander::Enemy_Wander(void)
{
	maxRotation = 1.0;
}

Enemy_Wander::~Enemy_Wander(void)
{
}

void Enemy_Wander::GetSteering(Enemy_Movement* movement)
{
	// get velocity from the vector form of orientaiton
	movement->setVelocity( MAX_SPEED * 
		movement->GetOrientationAsVector());
	// change our orientation randomly
	movement->SetRotation(RandomBinomial() * maxRotation);
}

float Enemy_Wander::RandomBinomial()
{
	float random = ((float) rand()) / (float) RAND_MAX;

	float range = 1.0 - (-1.0);  
	return (random*range) + (-1.0);
}