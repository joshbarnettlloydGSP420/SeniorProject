#pragma once

#include "Enemy_Movement.h"
#include "Model.h"

class Enemy_Base
{
private:
	bool		isDead;
	short		health;
	short		attackPower;
	short		defencePower;
	Enemy_Movement* movement;
	Model*		model;
	IDirect3DDevice9* device;

public:
	Enemy_Base(void);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice);
	void Update( float dt );
	void Render();
	void CollisionDetection();

	D3DXVECTOR4 GetPosition();
	void		SetPosition( D3DXVECTOR4 newPosition );
	short		GetAttackDamage();
	void		SetHealth( short newHealth );
	void		SetIsDead( bool newDeadState );
	short		GetDefencePower();
};

