#include "Enemy_Attack.h"


Enemy_Attack::Enemy_Attack(void)
{
}

Enemy_Attack::~Enemy_Attack(void)
{
}

void Enemy_Attack::Init()
{
	attackTime = 0;
	coolDown = 5.0f;
}

void Enemy_Attack::Update( float dt, D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos)
{
	
	if ( attackTime > 0 )
		attackTime -= dt;

	if ( attackTime < 0 )
		attackTime = 0;

	if ( attackTime == 0 )
	{
		//BulletAttack(enemyPos, playerPos);
		attackTime = coolDown;
	}
}

void Enemy_Attack::BulletAttack( D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos)
{
	// face the player
	D3DXVECTOR4 direction = playerPos - enemyPos;
	float distance = sqrt(( direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));

	// normalize velocity
	float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y) + (velocity.z * velocity.z));
	velocity.x /= length;
	velocity.y /= length;
	velocity.z /= length;

	// shoot a blast

	// if blast hits the player then player loses health
}

void Enemy_Attack::ObjectThrowAttack( D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos)
{
	// TODO:  if object is in range then pick up closest object
	// throw at the player
	// destroy object
}