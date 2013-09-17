#pragma once

#include "Enemy_Movement.h"
#include "RenderObject.h"
#include "Enemy_Wander.h"
#include "Enemy_Flee.h"
#include "Enemy_Attack.h"
#include "Enemy_Seek.h"
#include "HavokCore.h"
#include "Mesh.h"
#include "PSystem.h"

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

	LPCWSTR				textureName;
	GhostColor			textureNumber;

	// Mesh
	LPCWSTR				meshName;
	Mesh*				objectMesh;

	// Movement variables
	Enemy_Movement*		movement;
	Enemy_Wander		wander;
	Enemy_Seek			seek;
	Enemy_Flee			flee;
	Enemy_Attack		attack;

	D3DXVECTOR3			rotation;
	D3DXVECTOR3			scale;

	// current state of the enemy
	StateType			State;

	// position of the player
	D3DXVECTOR4			playerPos;

	// Havok
	hkpCharacterRigidBody*		rigidBody;
	hkpCharacterInput			input;

	// State Machine
	hkpCharacterState*			state;
	hkpCharacterStateManager*	manager;
	hkpCharacterContext*		context;

	// Movement Variables
	float						velUD;
	float						velLR;

	// Gun
	PSystem*					enemyPsys;

	// Object_Player*		havokShape;

public:
	Enemy_Base(void);
	Enemy_Base( short health, short attackPower, short defencePower, D3DXVECTOR4 position);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, D3DXVECTOR4 playerPosition );
	void UpdateState( StateType CurrentState, float dt );
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
	void CollisionDetection();

	// Accessors and mutators
	D3DXVECTOR4 GetPosition();
	void		SetPosition( D3DXVECTOR4 newPosition ){ movement->setPosition( newPosition); };
	short		GetAttackDamage();
	void		SetHealth( short newHealth ) {health = newHealth; };
	bool		GetIsDead(){ return isDead; };
	short		GetDefencePower();
	void		ChangeState( StateType NewState) { State = NewState; };

	// Havok
	void CreateBodyObject(hkpWorld* world);
	void EnemyInputOutput();
	void HavokMovement();
};

