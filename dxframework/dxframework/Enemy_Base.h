#pragma once

#include "Enemy_Movement.h"
#include "RenderObject.h"
#include "Enemy_Wander.h"
#include "Enemy_Flee.h"
#include "Enemy_Attack.h"
#include "Enemy_Seek.h"

// The states that the enemy can be in
enum StateType{Wander, Seek, Flee, Attack, Guard};

enum GhostColor{ RedGhost, BlueGhost, GreenGhost, YellowGhost };

class Enemy_Base
{
protected:
	// changes based on specific enemy
	bool				isDead;
	short				health;
	short				attackPower;
	short				defencePower;
	D3DXVECTOR4			attackRange;
	D3DXVECTOR4			wanderRange;
	
	// Rendering Variables
	RenderObject*		render;
	IDirect3DDevice9*	device;

	LPCSTR				textureName;
	GhostColor			textureNumber;

	LPCSTR				meshName;

	// Movement variables
	Enemy_Movement*		movement;
	Enemy_Wander		wander;
	Enemy_Seek			seek;
	Enemy_Flee			flee;
	Enemy_Attack		attack;

	// current state of the enemy
	StateType			State;

	// position of the player
	D3DXVECTOR4			playerPos;

	// Havok Stuff
	Object_Player*		havokShape;

public:
	Enemy_Base(void);
	Enemy_Base( short health, short attackPower, short defencePower);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, D3DXVECTOR4 playerPosition );
	void UpdateState( StateType CurrentState, float dt );
	void Render(HWND hwnd,D3DXMATRIX viewMat, D3DXMATRIX projMat);
	void CollisionDetection();

	void CreateHavokObject(hkpWorld* world);

	// Accessors and mutators
	D3DXVECTOR4 GetPosition();
	void		SetPosition( D3DXVECTOR4 newPosition );
	short		GetAttackDamage();
	void		SetHealth( short newHealth ) {health = newHealth; };
	bool		GetIsDead(){ return isDead; };
	short		GetDefencePower();
	void		ChangeState( StateType NewState) { State = NewState; };
};

