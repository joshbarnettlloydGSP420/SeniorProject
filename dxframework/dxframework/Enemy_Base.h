#pragma once

#include "Enemy_Movement.h"
#include "RenderObject.h"
#include "Enemy_Wander.h"
#include "Enemy_Flee.h"
#include "Enemy_Attack.h"
#include "Enemy_Arrive.h"
#include "HavokCore.h"
#include "Mesh.h"
#include "PSystem.h"

#include "Enemy_Align.h"
#include "Enemy_Face.h"

#include "Enemy_SpawnMiniGhost.h"

// The states that the enemy can be in
enum StateType{Wander, Arrive, Flee, Attack, Defence };
enum GhostColor{ RedGhost, PurpleGhost, GreenGhost, YellowGhost };

class Enemy_Base
{
protected:

	// changes based on specific enemy
	bool				isDead;
	short				health;
	short				attackSpeed;
	float				attackRange;
	float				wanderRange;
	
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
	Enemy_Flee			flee;
	Enemy_Arrive		arrive;
	Enemy_Attack		attack;

	Enemy_Face			face;
	Enemy_Align			align;

	// MiniGhost variables
	Enemy_SpawnMiniGhost miniGhost;
	bool				 miniGhostInitialized;

	// attack variable
	bool				 attackInitialized;

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

	// Havok Movement Variables
	float						velUD;
	float						velLR;

	// Object_Player*		havokShape;

public:
	Enemy_Base(void);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, D3DXVECTOR4 playerPosition);
	void UpdateState( StateType CurrentState, float dt );
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
	bool CollisionDetection(hkpRigidBody* playerBody);

	// Accessors and mutators
	void		SetHealth( short newHealth ) {health = newHealth; };
	bool		GetIsDead(){ return isDead; };
	void		ChangeState( StateType NewState) { State = NewState; };

	// Havok
	void CreateBodyObject(hkpWorld* world);
	void EnemyInputOutput();
	void HavokMovement();
};

