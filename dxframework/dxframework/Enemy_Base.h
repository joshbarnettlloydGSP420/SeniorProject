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
#include "Object_Player.h"
#include "Level_Base.h"

#include "Enemy_Align.h"
#include "Enemy_Face.h"

// The states that the enemy can be in
enum StateType{Wander, Arrive, Flee, Attack };
enum GhostColor{ RedGhost = 1, PurpleGhost, GreenGhost, YellowGhost };

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

	// attack variable
	bool				 attackInitialized;

	// current state of the enemy
	StateType			State;

	// position of the player
	Object_Player*			player;

	// Havok
	hkpRigidBody*		rigidBody;
	hkpCharacterInput	input;

	// State Machine
	hkpCharacterState*			state;
	hkpCharacterStateManager*	manager;
	hkpCharacterContext*		context;

	// Havok Movement Variables
	float						velUD;
	float						velLR;

	// Object_Player*		havokShape;	

	// Changes the state of the enemy
	void UpdateState( StateType CurrentState, float dt );
	void PlayerCollision( float dt);

public:
	Enemy_Base(void);
	~Enemy_Base(void);

	virtual void Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, Object_Player* player);
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
	virtual void BulletCollision( float dt, Object_Player* player, gunType bulletColor);
	void OuterWallCollision( float dt, Level_Base* currentRoom );

	// Havok
	void CreateBodyObject(hkpWorld* world);
	void CreateHavokObject(hkpWorld* world);
	void EnemyInputOutput();
	void HavokMovement();
	void HavokBodyUpdate();

	// Accessors and mutators
	void			SetHealth( short newHealth ) {health = newHealth; };
	short			GetHealth() { return health; };
	bool			GetIsDead() { return isDead; };
	hkpRigidBody*	GetHavokbody() { return rigidBody; };
	void			ChangeState( StateType NewState) { State = NewState; };
	void			SetPosition( D3DXVECTOR4 newPos) { movement->setPosition( newPos); };

};

