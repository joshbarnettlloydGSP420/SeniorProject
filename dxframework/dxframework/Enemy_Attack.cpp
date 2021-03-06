#include "Enemy_Attack.h"


Enemy_Attack::Enemy_Attack(void)
{
	// default variables
	attackTime = 0;
	coolDown = 10.0f;

	fleeRange = 0.05f;

	targetSpeed = 0.005f;
	maxSpeed = 0.05f;
	maxAcceleration = 0.001;

	slowRadius = 0.25;
	targetRadius = 0.15;

	TimeToTarget = 0.1f;
}

Enemy_Attack::~Enemy_Attack(void)
{
}

void Enemy_Attack::Update( float dt, Enemy_Movement* movement, D3DXVECTOR4 playerPos)
{
	D3DXVECTOR4 direction = playerPos - movement->GetPosition();
	float distance = sqrt(( direction.x * direction.x) + (direction.z + direction.z));

	// if the time of the last attack is greater than 0, then countdown
	if ( attackTime > 0 )
		attackTime -= dt;
	// if it is less than 0, then set to 0
	else if ( attackTime < 0 )
		attackTime = 0;
	// if it is 0 then attack
	else if ( attackTime == 0 )
	{
		
	}

	// after the collision the flee
	else if ( distance <= fleeRange )
	{
		flee.GetSteering( movement, playerPos);
		attackTime = coolDown;
	}
}