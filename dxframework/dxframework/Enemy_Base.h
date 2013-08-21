#pragma once

#include "Enemy_Movement.h"
#include "Model.h"
#include "Enemy_Wander.h"
#include "Enemy_Seek.h"

// The states that the enemy can be in
enum StateType{Wander, Seek, Flee, Attack, Guard};

class Enemy_Base
{
protected:
	// changes based on specific enemy
	bool				isDead;
	short				health;
	short				attackPower;
	short				defencePower;
	
	// Rendering Variables
	Model*				model;
	IDirect3DDevice9*	device;

	// Movement variables
	Enemy_Movement*		movement;
	Enemy_Wander		wander;
	Enemy_Seek			seek;

	// current state of the enemy
	StateType			State;

public:
	Enemy_Base(void);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice);
	void Update( float dt );
	void UpdateState( StateType CurrentState );
	void Render();
	void CollisionDetection();

	// Accessors and mutators
	D3DXVECTOR4 GetPosition();
	void		SetPosition( D3DXVECTOR4 newPosition );
	short		GetAttackDamage();
	void		SetHealth( short newHealth ) {health = newHealth};
	bool		GetIsDead(){ return isDead; };
	short		GetDefencePower();
	void		ChangeState( StateType NewState) { State = NewState; };
};

