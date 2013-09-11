#include "Enemy_Attack.h"
#include "enemyGun.h"

Enemy_Attack::Enemy_Attack(void)
{
	// Initialize the particle system.
	D3DXMATRIX psysWorld;
	D3DXMatrixIdentity(&psysWorld);


	//bullets/gun
	AABB psysBox;
	psysBox.maxPt = D3DXVECTOR3(INFINITY, INFINITY, INFINITY);
	psysBox.minPt = D3DXVECTOR3(-INFINITY, -INFINITY, -INFINITY);
	
	// Accelerate due to gravity.  However, since the bullets travel at 
	// such a high velocity, the effect of gravity of not really observed.
	enemyParticle = new enemyGun("gun.fx", "GunTech", "bolt3.dds", D3DXVECTOR3(0, -9.8f, 0), psysBox, 100, -1.0f);
	enemyParticle->setWorldMtx(psysWorld);    
	enemyParticle->setEnemyPos(D3DXVECTOR3(position.x, position.y, position.z));
}

Enemy_Attack::~Enemy_Attack(void)
{
}

void Enemy_Attack::Init()
{
	//// Initialize the particle system.
	//D3DXMATRIX psysWorld;
	//D3DXMatrixIdentity(&psysWorld);


	////bullets/gun
	//AABB psysBox;
	//psysBox.maxPt = D3DXVECTOR3(INFINITY, INFINITY, INFINITY);
	//psysBox.minPt = D3DXVECTOR3(-INFINITY, -INFINITY, -INFINITY);
	//
	//// Accelerate due to gravity.  However, since the bullets travel at 
	//// such a high velocity, the effect of gravity of not really observed.
	//enemyParticle = new enemyGun("gun.fx", "GunTech", "bolt2.dds", D3DXVECTOR3(0, -9.8f, 0), psysBox, 100, -1.0f);
	//enemyParticle->setWorldMtx(psysWorld);   

	attackTime = 0;
	coolDown = 5.0f;
}

void Enemy_Attack::Update( float dt, D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos)
{
	
	//if ( attackTime > 0 )
	//	attackTime -= dt;

	//if ( attackTime < 0 )
	//	attackTime = 0;

	//if ( attackTime == 0 )
	//{
	//	//BulletAttack(enemyPos, playerPos);
	//	attackTime = coolDown;
	//}
	enemyParticle->update(dt);
	BulletAttack(enemyPos, playerPos, dt);

}

void Enemy_Attack::BulletAttack( D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos, float dt)
{
	// face the player
	D3DXVECTOR4 direction = playerPos - enemyPos;
	float distance = sqrt(( direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));

	// normalize velocity
	float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y) + (velocity.z * velocity.z));
	velocity.x /= length;
	velocity.y /= length;
	velocity.z /= length;
/*
	 shoot a blast
	static float delay = 0.0f;
	if(delay <= 0.0f)
	{
		delay = 0.3f;
		enemyParticle->addParticle();
	}
	delay -= dt;*/

	// if blast hits the player then player loses health
}

void Enemy_Attack::ObjectThrowAttack( D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos)
{
	// TODO:  if object is in range then pick up closest object
	// throw at the player
	// destroy object
}
void Enemy_Attack::Render(HWND hwnd)
{
	enemyParticle->draw(hwnd);
}