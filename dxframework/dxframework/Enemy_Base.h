#pragma once

#include "Enemy_Movement.h"
<<<<<<< HEAD
#include "Model.h"
#include "Enemy_Wander.h"
#include "Enemy_Seek.h"
=======
#include "RenderObject.h"
#include "Enemy_Wander.h"
#include "Enemy_Flee.h"
#include "Enemy_Attack.h"
#include "Enemy_Seek.h"
#include "HavokCore.h"
#include "Mesh.h"
#include "PSystem.h"
>>>>>>> origin/MartinezWorking

// The states that the enemy can be in
enum StateType{Wander, Seek, Flee, Attack, Guard};

<<<<<<< HEAD
class Enemy_Base
{
protected:
=======
enum GhostColor{ RedGhost, BlueGhost, GreenGhost, YellowGhost };

class Enemy_Base
{

private:
	// Object Creation
	void createSphereObject(hkpWorld* world);
	void createBoxObject(hkpWorld* world);
	void createCapsuleObject(hkpWorld* world);
	//void stateMachineInit();

protected:

	D3DXVECTOR4			position;
	D3DXVECTOR3			rotation;
	D3DXVECTOR3			scale;

	hkAabb				boundingBox;

>>>>>>> origin/MartinezWorking
	// changes based on specific enemy
	bool				isDead;
	short				health;
	short				attackPower;
	short				defencePower;
<<<<<<< HEAD
	
	// Rendering Variables
	Model*				model;
	IDirect3DDevice9*	device;

=======
	D3DXVECTOR4			attackRange;
	D3DXVECTOR4			wanderRange;
	
	// Rendering Variables
	RenderObject*		render;
	IDirect3DDevice9*	device;

	LPCSTR				textureName;
	GhostColor			textureNumber;

	// Mesh
	LPCSTR				meshName;
	Mesh*				objectMesh;

>>>>>>> origin/MartinezWorking
	// Movement variables
	Enemy_Movement*		movement;
	Enemy_Wander		wander;
	Enemy_Seek			seek;
<<<<<<< HEAD
=======
	Enemy_Flee			flee;
	Enemy_Attack		attack;
>>>>>>> origin/MartinezWorking

	// current state of the enemy
	StateType			State;

<<<<<<< HEAD
public:
	Enemy_Base(void);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice);
	void Update( float dt );
	void UpdateState( StateType CurrentState );
	void Render();
	void CollisionDetection();

=======
	// position of the player
	D3DXVECTOR4			playerPos;

	// Havok
	short						shape;
	hkpCharacterRigidBody*		objectBody;
	hkReal						mass;	
	hkVector4					shapeSize;
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
	Enemy_Base( short health, short attackPower, short defencePower, D3DXVECTOR4 position, LPCSTR textureName, int textureNumber);
	~Enemy_Base(void);

	void Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, D3DXVECTOR4 playerPosition );
	void UpdateState( StateType CurrentState, float dt );
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
	void CollisionDetection();

	//void CreateHavokObject(hkpWorld* world);

>>>>>>> origin/MartinezWorking
	// Accessors and mutators
	D3DXVECTOR4 GetPosition();
	void		SetPosition( D3DXVECTOR4 newPosition );
	short		GetAttackDamage();
<<<<<<< HEAD
	void		SetHealth( short newHealth ) {health = newHealth};
	bool		GetIsDead(){ return isDead; };
	short		GetDefencePower();
	void		ChangeState( StateType NewState) { State = NewState; };
=======
	void		SetHealth( short newHealth ) {health = newHealth; };
	bool		GetIsDead(){ return isDead; };
	short		GetDefencePower();
	void		ChangeState( StateType NewState) { State = NewState; };

	// Havok
	void createHavokObject(hkpWorld* world);
	void characterInputOutput();
	void havokMovement();
>>>>>>> origin/MartinezWorking
};

