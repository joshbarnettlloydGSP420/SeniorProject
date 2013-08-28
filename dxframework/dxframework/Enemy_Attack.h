#pragma once

#include <d3d9.h>
#include <d3dx9.h>

	struct Bullets
	{
		D3DXVECTOR4 position;
		bool live;
		float speed;
	};

class Enemy_Attack
{
private:
	int attackTime;
	float coolDown;

	D3DXVECTOR4 position;
	D3DXVECTOR4 velocity;

	void BulletAttack(D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos);
	void ObjectThrowAttack( D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos);

public:
	Enemy_Attack(void);
	~Enemy_Attack(void);

	void Init();
	void Update( float dt, D3DXVECTOR4 enemyPos, D3DXVECTOR4 playerPos );

	D3DXVECTOR4 AttackPosition(){ return position; };
};

